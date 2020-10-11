#include "System.h"


lval* builtin_system(lenv* e, lval* a)
{
  LASSERT_NUM("system", a, 1);
  LASSERT_TYPE("system", a, 0, LVAL_STR);
  
  PARAM_NOT_USED(e);

  lval* v = lval_num(system(a->cell[0]->str));
  lval_del(a);

  return v;
}

lval* builtin_chdir(lenv* e, lval* a)
{
  LASSERT_NUM("str->num", a, 1);
  LASSERT_TYPE("str->num", a, 0, LVAL_STR);
  
  PARAM_NOT_USED(e);

  int res = chdir(a->cell[0]->str);
  lval* v = lval_num((double) res);
  lval_del(a);

  return v;
}
