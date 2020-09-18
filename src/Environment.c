/*
 * Environment.c
 *
 *  Created on: May 14, 2018
 *      Author: Sascha Wanninger
 */

#include "Environment.h"
#include "Builtins.h"
#include "Lval.h"



lenv* lenv_new(void)
{
  lenv* e = malloc(sizeof(lenv));
  e->count = 0;
  e->par = NULL;
  e->syms = NULL;
  e->vals = NULL;
  e->toKill = 0;
  return e;
}


void lenv_del(lenv* e)
{
  for (unsigned int i = 0; i < e->count; i++)
  {
    free(e->syms[i]);
    lval_del(e->vals[i]);
  }

  free(e->syms);
  free(e->vals);
  free(e);
}


lval* lenv_get(lenv* e, lval* k) {

  for (unsigned int i = 0; i < e->count; i++) {
    if (strcmp(e->syms[i], k->sym) == 0) {
      return lval_copy(e->vals[i]);
    }
  }

  /* If no symbol check in parent otherwise error */
  if (e->par) {
    return lenv_get(e->par, k);
  } else {
    return lval_err("UnboundSymbol", " '%s'", k->sym);
  }
}

/* Local definition */
void lenv_put(lenv* e, lval* k, lval* v)
{
  /* Iterate over all items in environment */
  /* This is to see if variable already exists */
  for (unsigned int i = 0; i< e->count; i++)
  {
    /* If variable is found delete item at that position
     * and replace with variable supplied by user */
    if(strcmp(e->syms[i], k->sym) == 0)
    {
      lval_del(e->vals[i]);
      e->vals[i] = lval_copy(v);
      return;
    }
  }

  /* If no existing entry found allocate space for new entry */
  e->count++;
  e->vals = realloc(e->vals, sizeof(lval*) * e->count);
  e->syms = realloc(e->syms, sizeof(char*) * e->count);

  /* Copy contents of lval and symbol string into new location */
  e->vals[e->count-1] = lval_copy(v);
  e->syms[e->count-1] = malloc(strlen(k->sym)+1);
  strcpy(e->syms[e->count-1], k->sym);
}

lval* lenv_set(lenv* e, lval* k, lval* v)
{
  /* Iterate over all items in environment */
  /* This is to see if variable already exists */
  for (unsigned int i = 0; i< e->count; i++)
  {
    /* If variable is found delete item at that position
     * and replace with variable supplied by user */
    if(strcmp(e->syms[i], k->sym) == 0)
    {
      lval_del(e->vals[i]);
      e->vals[i] = lval_copy(v);
      return lval_copy(v);
    }
  }

  if(e->par != NULL)
  {
    return lenv_set(e->par, k, v);
  }
  else
  {
    return lval_err("SymbolNotFound", "%s not found", k->sym);
  }
}


/* Global definition */
void lenv_def(lenv* e, lval* k, lval* v) {
  /* Iterate till e has no parent */
  while (e->par) { e = e->par; }
  /* Put value in e */
  lenv_put(e, k, v);
}


lenv* lenv_copy(lenv* e) {
  lenv* n = malloc(sizeof(lenv));
  n->par = e->par;
  n->count = e->count;
  n->syms = malloc(sizeof(char*) * n->count);
  n->vals = malloc(sizeof(lval*) * n->count);
  for (unsigned int i = 0; i < e->count; i++) {
    n->syms[i] = malloc(strlen(e->syms[i]) + 1);
    strcpy(n->syms[i], e->syms[i]);
    n->vals[i] = lval_copy(e->vals[i]);
  }
  return n;
}


void lenv_add_builtin(lenv* e, const char* name, lbuiltin func) {
  lval* k = lval_sym(name);
  lval* v = lval_fun(func);
  lenv_put(e, k, v);
  lval_del(k); lval_del(v);
}

void lenv_add_builtins(lenv* e) {
  /* List Functions */
  lenv_add_builtin(e, "list", builtin_list);
  lenv_add_builtin(e, "head", builtin_head);
  lenv_add_builtin(e, "tail", builtin_tail);
  lenv_add_builtin(e, "eval", builtin_eval);
  lenv_add_builtin(e, "join", builtin_join);
  lenv_add_builtin(e, "cons", builtin_cons);
  lenv_add_builtin(e, "len",  builtin_len);
  lenv_add_builtin(e, "exit",  builtin_exit);

  /* Mathematical Functions */
  lenv_add_builtin(e, "+", builtin_add);
  lenv_add_builtin(e, "-", builtin_sub);
  lenv_add_builtin(e, "*", builtin_mul);
  lenv_add_builtin(e, "/", builtin_div);
  lenv_add_builtin(e, "mod", builtin_modulo);

  /* Comparison Functions */
  lenv_add_builtin(e, "if", builtin_if);
  lenv_add_builtin(e, "==", builtin_eq);
  lenv_add_builtin(e, "!=", builtin_ne);
  lenv_add_builtin(e, ">",  builtin_gt);
  lenv_add_builtin(e, "<",  builtin_lt);
  lenv_add_builtin(e, ">=", builtin_ge);
  lenv_add_builtin(e, "<=", builtin_le);

  /* Logical functions */
  lenv_add_builtin(e, "||", builtin_or);
  lenv_add_builtin(e, "or", builtin_or);
  lenv_add_builtin(e, "&&", builtin_and);
  lenv_add_builtin(e, "and", builtin_and);
  lenv_add_builtin(e, "not", builtin_not);
  lenv_add_builtin(e, "!", builtin_not);


  /* Variable Functions */
  lenv_add_builtin(e, "put",  builtin_global_def);
  lenv_add_builtin(e, "=",  builtin_local_def);
  lenv_add_builtin(e, "def",  builtin_local_def);
 lenv_add_builtin(e, "set",   builtin_set);
  lenv_add_builtin(e, "defun",   builtin_fun);

  /* Functions */
  lenv_add_builtin(e, "lambda", builtin_lambda);

  lenv_add_builtin(e, "load", builtin_load);
  lenv_add_builtin(e, "load-internal", builtin_load_internal);
  lenv_add_builtin(e, "require", builtin_require);
  lenv_add_builtin(e, "error", builtin_error);
  lenv_add_builtin(e, "print", builtin_print);
  lenv_add_builtin(e, "type", builtin_type);
  lenv_add_builtin(e, "str->qexpr", builtin_readstr);
  lenv_add_builtin(e, "qexpr->str", builtin_writestr);
  lenv_add_builtin(e, "str->num", builtin_strToNum);
  lenv_add_builtin(e, "num->str", builtin_numToStr);
  lenv_add_builtin(e, "input", builtin_input);
  lenv_add_builtin(e, "indexOf", builtin_indexOf);
  lenv_add_builtin(e, "strlen", builtin_strlen);
  lenv_add_builtin(e, "substring", builtin_substring);
  lenv_add_builtin(e, "append", builtin_append);

  lenv_add_builtin(e, "env",   builtin_env);
}


void lenv_toKill(lenv* e)
{
  e->toKill = 1;
}
