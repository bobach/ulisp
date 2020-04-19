#include "function.h"
#include "eval.h"
#include "ulisp/core.h"
#include "ulisp/tf.h"
#include "ulisp/arithmetic.h"
#include "ulisp/list.h"
#include "ulisp/arduinoproc.h"
#include "ulisp/bitwise.h"
#include "ulisp/core.h"
#include "ulisp/edit.h"
#include "ulisp/lchar.h"
#include "ulisp/library.h"
#include "ulisp/list.h"
#include "ulisp/number.h"
#include "ulisp/prettyprint.h"
#include "ulisp/sp.h"
#include "ulisp/string.h"
#include "ulisp/system.h"
#include "ulisp/tf.h"

const char string0[] PROGMEM = "nil";
const char string1[] PROGMEM = "t";
const char string2[] PROGMEM = "nothing";
const char string3[] PROGMEM = "&optional";
const char string4[] PROGMEM = "&rest";
const char string5[] PROGMEM = "lambda";
const char string6[] PROGMEM = "let";
const char string7[] PROGMEM = "let*";
const char string8[] PROGMEM = "closure";
const char string9[] PROGMEM = "special_forms";
const char string10[] PROGMEM = "quote";
const char string11[] PROGMEM = "defun";
const char string12[] PROGMEM = "defvar";
const char string13[] PROGMEM = "setq";
const char string14[] PROGMEM = "loop";
const char string15[] PROGMEM = "return";
const char string16[] PROGMEM = "push";
const char string17[] PROGMEM = "pop";
const char string18[] PROGMEM = "incf";
const char string19[] PROGMEM = "decf";
const char string20[] PROGMEM = "setf";
const char string21[] PROGMEM = "dolist";
const char string22[] PROGMEM = "dotimes";
const char string23[] PROGMEM = "trace";
const char string24[] PROGMEM = "untrace";
const char string25[] PROGMEM = "for-millis";
const char string26[] PROGMEM = "with-serial";
const char string27[] PROGMEM = "with-i2c";
const char string28[] PROGMEM = "with-spi";
const char string29[] PROGMEM = "with-sd-card";
const char string30[] PROGMEM = "tail_forms";
const char string31[] PROGMEM = "progn";
const char string32[] PROGMEM = "if";
const char string33[] PROGMEM = "cond";
const char string34[] PROGMEM = "when";
const char string35[] PROGMEM = "unless";
const char string36[] PROGMEM = "case";
const char string37[] PROGMEM = "and";
const char string38[] PROGMEM = "or";
const char string39[] PROGMEM = "functions";
const char string40[] PROGMEM = "not";
const char string41[] PROGMEM = "null";
const char string42[] PROGMEM = "cons";
const char string43[] PROGMEM = "atom";
const char string44[] PROGMEM = "listp";
const char string45[] PROGMEM = "consp";
const char string46[] PROGMEM = "symbolp";
const char string47[] PROGMEM = "streamp";
const char string48[] PROGMEM = "eq";
const char string49[] PROGMEM = "car";
const char string50[] PROGMEM = "first";
const char string51[] PROGMEM = "cdr";
const char string52[] PROGMEM = "rest";
const char string53[] PROGMEM = "caar";
const char string54[] PROGMEM = "cadr";
const char string55[] PROGMEM = "second";
const char string56[] PROGMEM = "cdar";
const char string57[] PROGMEM = "cddr";
const char string58[] PROGMEM = "caaar";
const char string59[] PROGMEM = "caadr";
const char string60[] PROGMEM = "cadar";
const char string61[] PROGMEM = "caddr";
const char string62[] PROGMEM = "third";
const char string63[] PROGMEM = "cdaar";
const char string64[] PROGMEM = "cdadr";
const char string65[] PROGMEM = "cddar";
const char string66[] PROGMEM = "cdddr";
const char string67[] PROGMEM = "length";
const char string68[] PROGMEM = "list";
const char string69[] PROGMEM = "reverse";
const char string70[] PROGMEM = "nth";
const char string71[] PROGMEM = "assoc";
const char string72[] PROGMEM = "member";
const char string73[] PROGMEM = "apply";
const char string74[] PROGMEM = "funcall";
const char string75[] PROGMEM = "append";
const char string76[] PROGMEM = "mapc";
const char string77[] PROGMEM = "mapcar";
const char string78[] PROGMEM = "mapcan";
const char string79[] PROGMEM = "+";
const char string80[] PROGMEM = "-";
const char string81[] PROGMEM = "*";
const char string82[] PROGMEM = "/";
const char string83[] PROGMEM = "truncate";
const char string84[] PROGMEM = "mod";
const char string85[] PROGMEM = "1+";
const char string86[] PROGMEM = "1-";
const char string87[] PROGMEM = "abs";
const char string88[] PROGMEM = "random";
const char string89[] PROGMEM = "max";
const char string90[] PROGMEM = "min";
const char string91[] PROGMEM = "/=";
const char string92[] PROGMEM = "=";
const char string93[] PROGMEM = "<";
const char string94[] PROGMEM = "<=";
const char string95[] PROGMEM = ">";
const char string96[] PROGMEM = ">=";
const char string97[] PROGMEM = "plusp";
const char string98[] PROGMEM = "minusp";
const char string99[] PROGMEM = "zerop";
const char string100[] PROGMEM = "oddp";
const char string101[] PROGMEM = "evenp";
const char string102[] PROGMEM = "integerp";
const char string103[] PROGMEM = "numberp";
const char string104[] PROGMEM = "char";
const char string105[] PROGMEM = "char-code";
const char string106[] PROGMEM = "code-char";
const char string107[] PROGMEM = "characterp";
const char string108[] PROGMEM = "stringp";
const char string109[] PROGMEM = "string=";
const char string110[] PROGMEM = "string<";
const char string111[] PROGMEM = "string>";
const char string112[] PROGMEM = "sort";
const char string113[] PROGMEM = "string";
const char string114[] PROGMEM = "concatenate";
const char string115[] PROGMEM = "subseq";
const char string116[] PROGMEM = "read-from-string";
const char string117[] PROGMEM = "princ-to-string";
const char string118[] PROGMEM = "prin1-to-string";
const char string119[] PROGMEM = "logand";
const char string120[] PROGMEM = "logior";
const char string121[] PROGMEM = "logxor";
const char string122[] PROGMEM = "lognot";
const char string123[] PROGMEM = "ash";
const char string124[] PROGMEM = "logbitp";
const char string125[] PROGMEM = "eval";
const char string126[] PROGMEM = "globals";
const char string127[] PROGMEM = "locals";
const char string128[] PROGMEM = "makunbound";
const char string129[] PROGMEM = "break";
const char string130[] PROGMEM = "read";
const char string131[] PROGMEM = "prin1";
const char string132[] PROGMEM = "print";
const char string133[] PROGMEM = "princ";
const char string134[] PROGMEM = "terpri";
const char string135[] PROGMEM = "read-byte";
const char string136[] PROGMEM = "read-line";
const char string137[] PROGMEM = "write-byte";
const char string138[] PROGMEM = "write-string";
const char string139[] PROGMEM = "write-line";
const char string140[] PROGMEM = "restart-i2c";
const char string141[] PROGMEM = "gc";
const char string142[] PROGMEM = "room";
const char string143[] PROGMEM = "save-image";
const char string144[] PROGMEM = "load-image";
const char string145[] PROGMEM = "cls";
const char string146[] PROGMEM = "pinmode";
const char string147[] PROGMEM = "digitalread";
const char string148[] PROGMEM = "digitalwrite";
const char string149[] PROGMEM = "analogread";
const char string150[] PROGMEM = "analogwrite";
const char string151[] PROGMEM = "delay";
const char string152[] PROGMEM = "millis";
const char string153[] PROGMEM = "sleep";
const char string154[] PROGMEM = "edit";
const char string155[] PROGMEM = "pprint";
const char string156[] PROGMEM = "pprintall";
const char string157[] PROGMEM = "require";
const char string158[] PROGMEM = "list-library";

const tbl_entry_t lookup_table[] PROGMEM = {
  { string0, NULL, 0, 0 },
  { string1, NULL, 0, 0 },
  { string2, NULL, 0, 0 },
  { string3, NULL, 0, 0 },
  { string4, NULL, 0, 0 },
  { string5, NULL, 0, 127 },
  { string6, NULL, 0, 127 },
  { string7, NULL, 0, 127 },
  { string8, NULL, 0, 127 },
  { string9, NULL, NIL, NIL },
  { string10, sp_quote, 1, 1 },
  { string11, sp_defun, 0, 127 },
  { string12, sp_defvar, 2, 2 },
  { string13, sp_setq, 2, 126 },
  { string14, sp_loop, 0, 127 },
  { string15, sp_return, 0, 127 },
  { string16, sp_push, 2, 2 },
  { string17, sp_pop, 1, 1 },
  { string18, sp_incf, 1, 2 },
  { string19, sp_decf, 1, 2 },
  { string20, sp_setf, 2, 126 },
  { string21, sp_dolist, 1, 127 },
  { string22, sp_dotimes, 1, 127 },
  { string23, sp_trace, 0, 1 },
  { string24, sp_untrace, 0, 1 },
  { string25, sp_formillis, 1, 127 },
  { string26, sp_withserial, 1, 127 },
  { string27, sp_withi2c, 1, 127 },
  { string28, sp_withspi, 1, 127 },
  { string29, sp_withsdcard, 2, 127 },
  { string30, NULL, NIL, NIL }, 
  { string31, tf_progn, 0, 127 },
  { string32, tf_if, 2, 3 },
  { string33, tf_cond, 0, 127 },
  { string34, tf_when, 1, 127 },
  { string35, tf_unless, 1, 127 },
  { string36, tf_case, 1, 127 },
  { string37, tf_and, 0, 127 },
  { string38, tf_or, 0, 127 },
  { string39, NULL, NIL, NIL },
  { string40, fn_not, 1, 1 },
  { string41, fn_not, 1, 1 },
  { string42, fn_cons, 2, 2 },
  { string43, fn_atom, 1, 1 },
  { string44, fn_listp, 1, 1 },
  { string45, fn_consp, 1, 1 },
  { string46, fn_symbolp, 1, 1 },
  { string47, fn_streamp, 1, 1 },
  { string48, fn_eq, 2, 2 },
  { string49, fn_car, 1, 1 },
  { string50, fn_car, 1, 1 },
  { string51, fn_cdr, 1, 1 },
  { string52, fn_cdr, 1, 1 },
  { string53, fn_caar, 1, 1 },
  { string54, fn_cadr, 1, 1 },
  { string55, fn_cadr, 1, 1 },
  { string56, fn_cdar, 1, 1 },
  { string57, fn_cddr, 1, 1 },
  { string58, fn_caaar, 1, 1 },
  { string59, fn_caadr, 1, 1 },
  { string60, fn_cadar, 1, 1 },
  { string61, fn_caddr, 1, 1 },
  { string62, fn_caddr, 1, 1 },
  { string63, fn_cdaar, 1, 1 },
  { string64, fn_cdadr, 1, 1 },
  { string65, fn_cddar, 1, 1 },
  { string66, fn_cdddr, 1, 1 },
  { string67, fn_length, 1, 1 },
  { string68, fn_list, 0, 127 },
  { string69, fn_reverse, 1, 1 },
  { string70, fn_nth, 2, 2 },
  { string71, fn_assoc, 2, 2 },
  { string72, fn_member, 2, 2 },
  { string73, fn_apply, 2, 127 },
  { string74, fn_funcall, 1, 127 },
  { string75, fn_append, 0, 127 },
  { string76, fn_mapc, 2, 127 },
  { string77, fn_mapcar, 2, 127 },
  { string78, fn_mapcan, 2, 127 },
  { string79, fn_add, 0, 127 },
  { string80, fn_subtract, 1, 127 },
  { string81, fn_multiply, 0, 127 },
  { string82, fn_divide, 2, 127 },
  { string83, fn_divide, 1, 2 },
  { string84, fn_mod, 2, 2 },
  { string85, fn_oneplus, 1, 1 },
  { string86, fn_oneminus, 1, 1 },
  { string87, fn_abs, 1, 1 },
  { string88, fn_random, 1, 1 },
  { string89, fn_maxfn, 1, 127 },
  { string90, fn_minfn, 1, 127 },
  { string91, fn_noteq, 1, 127 },
  { string92, fn_numeq, 1, 127 },
  { string93, fn_less, 1, 127 },
  { string94, fn_lesseq, 1, 127 },
  { string95, fn_greater, 1, 127 },
  { string96, fn_greatereq, 1, 127 },
  { string97, fn_plusp, 1, 1 },
  { string98, fn_minusp, 1, 1 },
  { string99, fn_zerop, 1, 1 },
  { string100, fn_oddp, 1, 1 },
  { string101, fn_evenp, 1, 1 },
  { string102, fn_integerp, 1, 1 },
  { string103, fn_numberp, 1, 1 },
  { string104, fn_char, 2, 2 },
  { string105, fn_charcode, 1, 1 },
  { string106, fn_codechar, 1, 1 },
  { string107, fn_characterp, 1, 1 },
  { string108, fn_stringp, 1, 1 },
  { string109, fn_stringeq, 2, 2 },
  { string110, fn_stringless, 2, 2 },
  { string111, fn_stringgreater, 2, 2 },
  { string112, fn_sort, 2, 2 },
  { string113, fn_stringfn, 1, 1 },
  { string114, fn_concatenate, 1, 127 },
  { string115, fn_subseq, 2, 3 },
  { string116, fn_readfromstring, 1, 1 },
  { string117, fn_princtostring, 1, 1 },
  { string118, fn_prin1tostring, 1, 1 },
  { string119, fn_logand, 0, 127 },
  { string120, fn_logior, 0, 127 },
  { string121, fn_logxor, 0, 127 },
  { string122, fn_lognot, 1, 1 },
  { string123, fn_ash, 2, 2 },
  { string124, fn_logbitp, 2, 2 },
  { string125, fn_eval, 1, 1 },
  { string126, fn_globals, 0, 0 },
  { string127, fn_locals, 0, 0 },
  { string128, fn_makunbound, 1, 1 },
  { string129, fn_break, 0, 0 },
  { string130, fn_read, 0, 1 },
  { string131, fn_prin1, 1, 2 },
  { string132, fn_print, 1, 2 },
  { string133, fn_princ, 1, 2 },
  { string134, fn_terpri, 0, 1 },
  { string135, fn_readbyte, 0, 2 },
  { string136, fn_readline, 0, 1 },
  { string137, fn_writebyte, 1, 2 },
  { string138, fn_writestring, 1, 2 },
  { string139, fn_writeline, 1, 2 },
  { string140, fn_restarti2c, 1, 2 },
  { string141, fn_gc, 0, 0 },
  { string142, fn_room, 0, 0 },
  { string143, fn_saveimage, 0, 1 },
  { string144, fn_loadimage, 0, 1 },
  { string145, fn_cls, 0, 0 },
  { string146, fn_pinmode, 2, 2 },
  { string147, fn_digitalread, 1, 1 },
  { string148, fn_digitalwrite, 2, 2 },
  { string149, fn_analogread, 1, 1 },
  { string150, fn_analogwrite, 2, 2 },
  { string151, fn_delay, 1, 1 },
  { string152, fn_millis, 0, 0 },
  { string153, fn_sleep, 1, 1 },
  { string154, fn_edit, 1, 1 },
  { string155, fn_pprint, 1, 2 },
  { string156, fn_pprintall, 0, 0 },
  { string157, fn_require, 1, 1 },
  { string158, fn_listlibrary, 0, 0 },
};

// Table lookup functions

int builtin (char* n) {
  int entry = 0;
  while (entry < ENDFUNCTIONS) {
    #if defined(__AVR_ATmega4809__) || defined(__AVR_ATtiny3216__)
    if (strcasecmp(n, (char*)lookup_table[entry].string) == 0)
    #else
    if (strcasecmp_P(n, (char*)pgm_read_word(&lookup_table[entry].string)) == 0)
    #endif
      return entry;
    entry++;
  }
  return ENDFUNCTIONS;
}


intptr_t lookupfn (symbol_t name) {
  #if defined(__AVR_ATmega4809__) || defined(__AVR_ATtiny3216__)
  return (intptr_t)lookup_table[name].fptr;
  #else
  return pgm_read_word(&lookup_table[name].fptr);
  #endif
}

uint8_t lookupmin (symbol_t name) {
  #if defined(__AVR_ATmega4809__) || defined(__AVR_ATtiny3216__)
  return lookup_table[name].min;
  #else
  return pgm_read_byte(&lookup_table[name].min);
  #endif
}

uint8_t lookupmax (symbol_t name) {
  #if defined(__AVR_ATmega4809__) || defined(__AVR_ATtiny3216__)
  return lookup_table[name].max;
  #else
  return pgm_read_byte(&lookup_table[name].max);
  #endif
}

char *lookupbuiltin (symbol_t name) {
  char *buffer = SymbolTop;
  #if defined(__AVR_ATmega4809__) || defined(__AVR_ATtiny3216__)
  strcpy(buffer, (char *)(lookup_table[name].string));
  #else
  strcpy_P(buffer, (char *)(pgm_read_word(&lookup_table[name].string)));
  #endif
  return buffer;
}
