#include "arithmetic.h"
#include "../objects.h"
#include "../function.h"
#include "../error.h"
#include <Arduino.h>

object *fn_add (object *args, object *env) {
  (void) env;
  int result = 0;
  while (args != NULL) {
    int temp = checkinteger(ADD, car(args));
    #if defined(checkoverflow)
    if (temp < 1) { if (INT_MIN - temp > result) error2(ADD, overflow); }
    else { if (INT_MAX - temp < result) error2(ADD, overflow); }
    #endif
    result = result + temp;
    args = cdr(args);
  }
  return number(result);
}

object *fn_subtract (object *args, object *env) {
  (void) env;
  int result = checkinteger(SUBTRACT, car(args));
  args = cdr(args);
  if (args == NULL) {
    #if defined(checkoverflow)
    if (result == INT_MIN) error2(SUBTRACT, overflow);
    #endif
    return number(-result);
  }
  while (args != NULL) {
    int temp = checkinteger(SUBTRACT, car(args));
    #if defined(checkoverflow)
    if (temp < 1) { if (INT_MAX + temp < result) error2(SUBTRACT, overflow); }
    else { if (INT_MIN + temp > result) error2(SUBTRACT, overflow); }
    #endif
    result = result - temp;
    args = cdr(args);
  }
  return number(result);
}

object *fn_multiply (object *args, object *env) {
  (void) env;
  int result = 1;
  while (args != NULL){
    #if defined(checkoverflow)
    signed long temp = (signed long) result * checkinteger(MULTIPLY, car(args));
    if ((temp > INT_MAX) || (temp < INT_MIN)) error2(MULTIPLY, overflow);
    result = temp;
    #else
    result = result * checkinteger(MULTIPLY, car(args));
    #endif
    args = cdr(args);
  }
  return number(result);
}

object *fn_divide (object *args, object *env) {
  (void) env;
  int result = checkinteger(DIVIDE, first(args));
  args = cdr(args);
  while (args != NULL) {
    int arg = checkinteger(DIVIDE, car(args));
    if (arg == 0) error2(DIVIDE, PSTR("division by zero"));
    #if defined(checkoverflow)
    if ((result == INT_MIN) && (arg == -1)) error2(DIVIDE, overflow);
    #endif
    result = result / arg;
    args = cdr(args);
  }
  return number(result);
}

object *fn_mod (object *args, object *env) {
  (void) env;
  int arg1 = checkinteger(MOD, first(args));
  int arg2 = checkinteger(MOD, second(args));
  if (arg2 == 0) error2(MOD, PSTR("division by zero"));
  int r = arg1 % arg2;
  if ((arg1<0) != (arg2<0)) r = r + arg2;
  return number(r);
}

object *fn_oneplus (object *args, object *env) {
  (void) env;
  int result = checkinteger(ONEPLUS, first(args));
  #if defined(checkoverflow)
  if (result == INT_MAX) error2(ONEPLUS, overflow);
  #endif
  return number(result + 1);
}

object *fn_oneminus (object *args, object *env) {
  (void) env;
  int result = checkinteger(ONEMINUS, first(args));
  #if defined(checkoverflow)
  if (result == INT_MIN) error2(ONEMINUS, overflow);
  #endif
  return number(result - 1);
}

object *fn_abs (object *args, object *env) {
  (void) env;
  int result = checkinteger(ABS, first(args));
  #if defined(checkoverflow)
  if (result == INT_MIN) error2(ABS, overflow);
  #endif
  return number(abs(result));
}

object *fn_random (object *args, object *env) {
  (void) env;
  int arg = checkinteger(RANDOM, first(args));
  return number(random(arg));
}

object *fn_maxfn (object *args, object *env) {
  (void) env;
  int result = checkinteger(MAXFN, first(args));
  args = cdr(args);
  while (args != NULL) {
    int next = checkinteger(MAXFN, car(args));
    if (next > result) result = next;
    args = cdr(args);
  }
  return number(result);
}

object *fn_minfn (object *args, object *env) {
  (void) env;
  int result = checkinteger(MINFN, first(args));
  args = cdr(args);
  while (args != NULL) {
    int next = checkinteger(MINFN, car(args));
    if (next < result) result = next;
    args = cdr(args);
  }
  return number(result);
}

object *fn_noteq (object *args, object *env) {
  (void) env;
  while (args != NULL) {   
    object *nargs = args;
    int arg1 = checkinteger(NOTEQ, first(nargs));
    nargs = cdr(nargs);
    while (nargs != NULL) {
       int arg2 = checkinteger(NOTEQ, first(nargs));
       if (arg1 == arg2) return nil;
       nargs = cdr(nargs);
    }
    args = cdr(args);
  }
  return tee;
}

object *fn_numeq (object *args, object *env) {
  (void) env;
  int arg1 = checkinteger(NUMEQ, first(args));
  args = cdr(args);
  while (args != NULL) {
    int arg2 = checkinteger(NUMEQ, first(args));
    if (!(arg1 == arg2)) return nil;
    arg1 = arg2;
    args = cdr(args);
  }
  return tee;
}

object *fn_less (object *args, object *env) {
  (void) env;
  int arg1 = checkinteger(LESS, first(args));
  args = cdr(args);
  while (args != NULL) {
    int arg2 = checkinteger(LESS, first(args));
    if (!(arg1 < arg2)) return nil;
    arg1 = arg2;
    args = cdr(args);
  }
  return tee;
}

object *fn_lesseq (object *args, object *env) {
  (void) env;
  int arg1 = checkinteger(LESSEQ, first(args));
  args = cdr(args);
  while (args != NULL) {
    int arg2 = checkinteger(LESSEQ, first(args));
    if (!(arg1 <= arg2)) return nil;
    arg1 = arg2;
    args = cdr(args);
  }
  return tee;
}

object *fn_greater (object *args, object *env) {
  (void) env;
  int arg1 = checkinteger(GREATER, first(args));
  args = cdr(args);
  while (args != NULL) {
    int arg2 = checkinteger(GREATER, first(args));
    if (!(arg1 > arg2)) return nil;
    arg1 = arg2;
    args = cdr(args);
  }
  return tee;
}

object *fn_greatereq (object *args, object *env) {
  (void) env;
  int arg1 = checkinteger(GREATEREQ, first(args));
  args = cdr(args);
  while (args != NULL) {
    int arg2 = checkinteger(GREATEREQ, first(args));
    if (!(arg1 >= arg2)) return nil;
    arg1 = arg2;
    args = cdr(args);
  }
  return tee;
}

object *fn_plusp (object *args, object *env) {
  (void) env;
  int arg = checkinteger(PLUSP, first(args));
  if (arg > 0) return tee;
  else return nil;
}

object *fn_minusp (object *args, object *env) {
  (void) env;
  int arg = checkinteger(MINUSP, first(args));
  if (arg < 0) return tee;
  else return nil;
}

object *fn_zerop (object *args, object *env) {
  (void) env;
  int arg = checkinteger(ZEROP, first(args));
  return (arg == 0) ? tee : nil;
}

object *fn_oddp (object *args, object *env) {
  (void) env;
  int arg = checkinteger(ODDP, first(args));
  return ((arg & 1) == 1) ? tee : nil;
}

object *fn_evenp (object *args, object *env) {
  (void) env;
  int arg = checkinteger(EVENP, first(args));
  return ((arg & 1) == 0) ? tee : nil;
}
