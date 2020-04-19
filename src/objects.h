#ifndef OBJECTS_H
#define OBJECTS_H

#include "symbol.h"
#include "stddef.h"

#define integerp(x)        ((x) != NULL && (x)->type == NUMBER)
#define floatp(x)          ((x) != NULL && (x)->type == FLOAT)
#define symbolp(x)         ((x) != NULL && (x)->type == SYMBOL)
#define stringp(x)         ((x) != NULL && (x)->type == STRING)
#define characterp(x)      ((x) != NULL && (x)->type == CHARACTER)
#define streamp(x)         ((x) != NULL && (x)->type == STREAM)

#define nil                NULL
#define car(x)             (((object *) (x))->car)
#define cdr(x)             (((object *) (x))->cdr)
#define first(x)           (((object *) (x))->car)
#define second(x)          (car(cdr(x)))
#define cddr(x)            (cdr(cdr(x)))
#define third(x)           (car(cdr(cdr(x))))
#define push(x, y)         ((y) = cons((x),(y)))
#define pop(y)             ((y) = cdr(y))


typedef struct sobject {
  union {
    struct {
      sobject *car;
      sobject *cdr;
    };
    struct {
      unsigned int type;
      union {
        symbol_t name;
        int integer;
      };
    };
  };
} object;

//enum
enum type { ZERO=0, SYMBOL=2, NUMBER=4, STREAM=6, CHARACTER=8, FLOAT=10, STRING=12, PAIR=14 };  // STRING and PAIR must be last

// Make each type of object

object *number (int n);

object *character (char c);

object *cons (object *arg1, object *arg2);

object *symbol (symbol_t name);

object *newsymbol (symbol_t name);

object *stream (unsigned char streamtype, unsigned char address);

int issymbol (object *obj, symbol_t n);

int checkinteger (symbol_t name, object *obj);

int checkchar (symbol_t name, object *obj);

int eq (object *arg1, object *arg2);

bool consp (object *x);
bool atom (object *x);
bool listp (object *x);
bool improperp (object *x);
#endif
