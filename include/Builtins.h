/*
 * builtins.h
 *
 *  Created on: May 14, 2018
 *      Author: Sascha Wanninger
 */

#ifndef _BUILTINS_H_
#define _BUILTINS_H_

/* Forward declarations */
struct lval;
struct lenv;
typedef struct lval lval;
typedef struct lenv lenv;

typedef lval*(*lbuiltin)(lenv*, lval*);

lval* builtin(lval* a, char* func);
lval* builtin_head(lenv* e, lval* a);
lval* builtin_cons(lenv* e, lval* a);
lval* builtin_len(lenv* e, lval* a);
lval* builtin_tail(lenv* e, lval* a);
lval* builtin_list(lenv* e, lval* a);
lval* builtin_join(lenv* e, lval* a);
lval* builtin_eval(lenv* e, lval* a);
lval* builtin_add(lenv* e, lval* a);
lval* builtin_sub(lenv* e, lval* a);
lval* builtin_mul(lenv* e, lval* a);
lval* builtin_div(lenv* e, lval* a);
lval* builtin_modulo(lenv* e, lval* a);
lval* builtin_local_def(lenv* e, lval* a);
lval* builtin_global_def(lenv* e, lval* a);
lval* builtin_set(lenv* e, lval* a);
lval* builtin_exit(lenv* e, lval* a);
lval* builtin_lambda(lenv* e, lval* a);
lval* builtin_gt(lenv* e, lval* a);
lval* builtin_lt(lenv* e, lval* a);
lval* builtin_ge(lenv* e, lval* a);
lval* builtin_le(lenv* e, lval* a);
lval* builtin_eq(lenv* e, lval* a);
lval* builtin_ne(lenv* e, lval* a);
lval* builtin_if(lenv* e, lval* a);
lval* builtin_or(lenv* e, lval* a);
lval* builtin_and(lenv* e, lval* a);
lval* builtin_not(lenv* e, lval* a);
lval* builtin_load(lenv* e, lval* a);
lval* builtin_require(lenv* e, lval* a);
lval* builtin_load_internal(lenv* e, lval* a);
lval* builtin_error(lenv* e, lval* a);
lval* builtin_print(lenv* e, lval* a);
lval* builtin_type(lenv* e, lval* a);
lval* builtin_readstr(lenv* e, lval* a);
lval* builtin_writestr(lenv* e, lval* a);
lval* builtin_fun(lenv* e, lval* a);
lval* builtin_env(lenv* e, lval* a);
lval* builtin_strToNum(lenv* e, lval* a);
lval* builtin_numToStr(lenv* e, lval* a);
lval* builtin_input(lenv* e, lval* a);
lval* builtin_system(lenv* e, lval* a);
lval* builtin_indexOf(lenv* e, lval* a);
lval* builtin_substring(lenv* e, lval* a);
lval* builtin_strlen(lenv* e, lval* a);
lval* builtin_append(lenv* e, lval* a);
lval* builtin_fileOpen(lenv* e, lval* a);
lval* builtin_fileClose(lenv* e, lval* a);
lval* builtin_readchar(lenv* e, lval* a);
lval* builtin_writechar(lenv* e, lval* a);
lval* builtin_chdir(lenv* e, lval* a);

#endif /* _BUILTINS_H_ */
