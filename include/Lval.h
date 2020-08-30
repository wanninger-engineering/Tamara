#ifndef _LVAL_H_
#define _LVAL_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"
#include "Builtins.h"

typedef enum { false, true } bool;

/* Definitions for DEBUG output */
#define DEBUG_FLAG (0)
#define DEBUG_OUT if(DEBUG_FLAG) printf

#define LASSERT(args, cond, error, fmt, ...)	\
  if (!(cond)) { \
    lval* err = lval_err(error, fmt, ##__VA_ARGS__);	\
    lval_del(args); \
    return err; \
  }


#define LASSERT_TYPE(func, args, index, expect) \
  LASSERT(args, args->cell[index]->type == expect, \
	  args->cell[index]->type == LVAL_ERR ?args->cell[index]->err : "TypeError",  \
    args->cell[index]->type == LVAL_ERR ?args->cell[index]->str : "Function '%s' passed incorrect type for argument %i. Got %s, Expected %s.", \
    func, index, ltype_name(args->cell[index]->type), ltype_name(expect))

#define LASSERT_NUM(func, args, num) \
  LASSERT(args, args->count == num, \
    "IncorrectNumberArgs",  \
"Function '%s' passed incorrect number of arguments. Got %i, Expected %i.", \
    func, args->count, num)

#define LASSERT_NOT_EMPTY(func, args, index) \
  LASSERT(args, args->cell[index]->count != 0, \
    "EmptyListError", \
    "Function '%s' passed [] for argument %i.", func, index);


/* lval types */
enum { LVAL_NUM, LVAL_ERR, LVAL_SYM, LVAL_STR, LVAL_SEXPR, LVAL_QEXPR, LVAL_FUN, LVAL_BOOL, LVAL_FILE };

/* lval struct */
typedef struct lval{
  int type;

  /* Basic */
  double num;
  char* err;
  char* sym;
  char* str;
  FILE* file;

  /* Function */
  lbuiltin builtin;
  lenv* env;
  lval* formals;
  lval* body;
  
  /* Expression */
  int count;
  struct lval** cell;
} lval;

/* error types */
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

/* Exported functions */
void lval_print(lval* v);
void lval_println(lval* v);
lval* lval_eval(lenv* e, lval* v);
lval* lval_call(lenv* e, lval* f, lval* a);

/* constructors for LVALs */
lval* lval_num(double x);
lval* lval_err(const char* err, const char* fmt, ...);
lval* lval_sym(const char* s);
lval* lval_sexpr(void);
lval* lval_qexpr(void);
lval* lval_fun(lbuiltin func);
lval* lval_lambda(lenv* e, lval* formals, lval* body);
lval* lval_bool(bool x);
lval* lval_str(const char* s);
lval* lval_file(const char* path, const char* mode);



lval* lval_read(mpc_ast_t* t);
void lval_del(lval* v);

lval* lval_read_num(mpc_ast_t* t);

lval* lval_join(lval* x, lval* y);

int lval_eq(lval* x, lval* y);
lval* lval_add(lval* v, lval* x);
lval* lval_eval_sexpr(lenv* e, lval* v);
lval* lval_pop(lval* v, int i);
lval* lval_take(lval* v, int i);
lval* lval_copy(lval* v);

const char* ltype_name(int t);

#endif /* _LVAL_H_ */
