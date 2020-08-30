/*
 * Environment.h
 *
 *  Created on: May 14, 2018
 *      Author: test
 */

#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include "Lval.h"

struct lenv {
  lenv* par;
  unsigned int count;
  char** syms;
  lval** vals;
  int toKill;
};

struct lenv_packages{
  char* name;
  void (*reg_fun) (lenv* e);
};
  
lenv* lenv_new(void);
void lenv_del(lenv* e);
lval* lenv_get(lenv* e, lval* k);
void lenv_add_builtins(lenv* e);
void lenv_put(lenv* e, lval* k, lval* v);
void lenv_def(lenv* e, lval* k, lval* v);
lval* lenv_set(lenv* e, lval* k, lval* v);
lenv* lenv_copy(lenv* e);
void lenv_toKill(lenv* e);

void lenv_register(lenv* e, char* name);
void lenv_reg_file(lenv* e);
void lenv_reg_curl(lenv* e);
void lenv_reg_math(lenv* e);
void lenv_reg_os(lenv* e);

#endif /* _ENVIRONMENT_H_ */
