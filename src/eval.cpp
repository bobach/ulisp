// Main evaluator
#include "eval.h"

#include <stdint.h>
#include "error.h"
#include "function.h"
#include "io.h"
#include "objects.h"
#include "gstring.h"
#include "tracing.h"
#include "gc.h"
#include "symbol.h"
#include "env.h"
#include "ulisp/tf.h"
#include "flags.h"

char BreakLevel = 0;

object *closure (int tc, symbol_t name, object *state, object *function, object *args, object **env) {
  int trace = 0;
  if (name) trace = tracing(name);
  if (trace) {
    indent(TraceDepth[trace-1]<<1, pserial);
    pint(TraceDepth[trace-1]++, pserial);
    pserial(':'); pserial(' '); pserial('('); pstring(symbolname(name), pserial);
  }
  object *params = first(function);
  function = cdr(function);
  // Dropframe
  if (tc) {
    if (*env != NULL && car(*env) == NULL) {
      pop(*env);
      while (*env != NULL && car(*env) != NULL) pop(*env);
    } else push(nil, *env);
  }
  // Push state
  while (state != NULL) {
    object *pair = first(state);
    push(pair, *env);
    state = cdr(state);
  }
  // Add arguments to environment
  boolean optional = false;
  while (params != NULL) {
    object *value;
    object *var = first(params);
    if (symbolp(var) && var->name == OPTIONAL) optional = true;  
    else {
      if (consp(var)) {
        if (!optional) error(name, PSTR("invalid default value"), var);
        if (args == NULL) value = eval(second(var), *env);
        else { value = first(args); args = cdr(args); }
        var = first(var);
        if (!symbolp(var)) error(name, PSTR("illegal optional parameter"), var); 
      } else if (!symbolp(var)) {
        error2(name, PSTR("illegal parameter"));     
      } else if (var->name == AMPREST) {
        params = cdr(params);
        var = first(params);
        value = args;
        args = NULL;
      } else {
        if (args == NULL) {
          if (optional) value = nil; 
          else {
            if (name) error2(name, PSTR("has too few arguments"));
            else error2(0, PSTR("function has too few arguments"));
          }
        } else { value = first(args); args = cdr(args); }
      }
      push(cons(var,value), *env);
      if (trace) { pserial(' '); printobject(value, pserial); }
    }
    params = cdr(params);  
  }
  if (args != NULL) {
    if (name) error2(name, PSTR("has too many arguments"));
    else error2(0, PSTR("function has too many arguments"));
  }
  if (trace) { pserial(')'); pln(pserial); }
  // Do an implicit progn
  if (tc) push(nil, *env);
  return tf_progn(function, *env);
}

object *apply (symbol_t name, object *function, object *args, object *env) {
  if (symbolp(function)) {
    symbol_t fname = function->name;
    checkargs(fname, args);
    return ((fn_ptr_type)lookupfn(fname))(args, env);
  }
  if (consp(function) && issymbol(car(function), LAMBDA)) {
    function = cdr(function);
    object *result = closure(0, 0, NULL, function, args, &env);
    return eval(result, env);
  }
  if (consp(function) && issymbol(car(function), CLOSURE)) {
    function = cdr(function);
    object *result = closure(0, 0, car(function), cdr(function), args, &env);
    return eval(result, env);
  }
  error(name, PSTR("illegal function"), function);
  return NULL;
}


uint8_t End;

object *eval (object *form, object *env) {
  int TC=0;
  EVAL:
  yield(); // Needed on ESP8266 to avoid Soft WDT Reset
  // Enough space?
  if (End != 0xA5) error2(0, PSTR("Stack overflow"));
  if (Freespace <= WORKSPACESIZE>>4) gc(form, env);
  // Escape
  if (tstflag(ESCAPE)) { clrflag(ESCAPE); error2(0, PSTR("Escape!"));}
  #if defined (serialmonitor)
  if (!tstflag(NOESC)) testescape();
  #endif
  
  if (form == NULL) return nil;

  if (integerp(form) || floatp(form) || characterp(form) || stringp(form)) return form;

  if (symbolp(form)) {
    symbol_t name = form->name;
    if (name == NIL) return nil;
    object *pair = value(name, env);
    if (pair != NULL) return cdr(pair);
    pair = value(name, GlobalEnv);
    if (pair != NULL) return cdr(pair);
    else if (name <= ENDFUNCTIONS) return form;
    error(0, PSTR("undefined"), form);
  }
  
  // It's a list
  object *function = car(form);
  object *args = cdr(form);

  if (function == NULL) error(0, PSTR("illegal function"), nil);
  if (!listp(args)) error(0, PSTR("can't evaluate a dotted pair"), args);

  // List starts with a symbol?
  if (symbolp(function)) {
    symbol_t name = function->name;

    if ((name == LET) || (name == LETSTAR)) {
      int TCstart = TC;
      object *assigns = first(args);
      object *forms = cdr(args);
      object *newenv = env;
      push(newenv, GCStack);
      while (assigns != NULL) {
        object *assign = car(assigns);
        if (!consp(assign)) push(cons(assign,nil), newenv);
        else if (cdr(assign) == NULL) push(cons(first(assign),nil), newenv);
        else push(cons(first(assign),eval(second(assign),env)), newenv);
        car(GCStack) = newenv;
        if (name == LETSTAR) env = newenv;
        assigns = cdr(assigns);
      }
      env = newenv;
      pop(GCStack);
      form = tf_progn(forms,env);
      TC = TCstart;
      goto EVAL;
    }

    if (name == LAMBDA) {
      if (env == NULL) return form;
      object *envcopy = NULL;
      while (env != NULL) {
        object *pair = first(env);
        if (pair != NULL) push(pair, envcopy);
        env = cdr(env);
      }
      return cons(symbol(CLOSURE), cons(envcopy,args));
    }
    
    if (name < SPECIAL_FORMS) error2((int)function, PSTR("can't be used as a function"));

    if ((name > SPECIAL_FORMS) && (name < TAIL_FORMS)) {
      return ((fn_ptr_type)lookupfn(name))(args, env);
    }

    if ((name > TAIL_FORMS) && (name < FUNCTIONS)) {
      form = ((fn_ptr_type)lookupfn(name))(args, env);
      TC = 1;
      goto EVAL;
    }
  }
        
  // Evaluate the parameters - result in head
  object *fname = car(form);
  int TCstart = TC;
  object *head = cons(eval(car(form), env), NULL);
  push(head, GCStack); // Don't GC the result list
  object *tail = head;
  form = cdr(form);
  int nargs = 0;

  while (form != NULL){
    object *obj = cons(eval(car(form),env),NULL);
    cdr(tail) = obj;
    tail = obj;
    form = cdr(form);
    nargs++;
  }
    
  function = car(head);
  args = cdr(head);
 
  if (symbolp(function)) {
    symbol_t name = function->name;
    if (name >= ENDFUNCTIONS) error(0, PSTR("not valid here"), fname);
    if (nargs<lookupmin(name)) error2(name, PSTR("has too few arguments"));
    if (nargs>lookupmax(name)) error2(name, PSTR("has too many arguments"));
    object *result = ((fn_ptr_type)lookupfn(name))(args, env);
    pop(GCStack);
    return result;
  }
      
  if (consp(function) && issymbol(car(function), LAMBDA)) {
    form = closure(TCstart, fname->name, NULL, cdr(function), args, &env);
    pop(GCStack);
    int trace = tracing(fname->name);
    if (trace) {
      object *result = eval(form, env);
      indent((--(TraceDepth[trace-1]))<<1, pserial);
      pint(TraceDepth[trace-1], pserial);
      pserial(':'); pserial(' ');
      printobject(fname, pserial); pfstring(PSTR(" returned "), pserial);
      printobject(result, pserial); pln(pserial);
      return result;
    } else {
      TC = 1;
      goto EVAL;
    }
  }

  if (consp(function) && issymbol(car(function), CLOSURE)) {
    function = cdr(function);
    form = closure(TCstart, fname->name, car(function), cdr(function), args, &env);
    pop(GCStack);
    TC = 1;
    goto EVAL;
  } 
  
  error(0, PSTR("illegal function"), fname); return nil;
}


// Read/Evaluate/Print loop
void repl (object *env) {
  for (;;) {
    randomSeed(micros());
    gc(NULL, env);
    #if defined (printfreespace)
    pint(Freespace, pserial);
    #endif
    if (BreakLevel) {
      pfstring(PSTR(" : "), pserial);
      pint(BreakLevel, pserial);
    }
    pfstring(PSTR("> "), pserial);
    object *line = read(gserial);
    if (BreakLevel && line == nil) { pln(pserial); return; }
    if (line == (object *)KET) error2(0, PSTR("unmatched right bracket"));
    push(line, GCStack);
    pfl(pserial);
    line = eval(line, env);
    pfl(pserial);
    printobject(line, pserial);
    pop(GCStack);
    pfl(pserial);
    pln(pserial);
  }
}
