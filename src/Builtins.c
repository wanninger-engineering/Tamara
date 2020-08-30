/*
 * builtins.c
 *
 *  Created on: May 14, 2018
 *      Author: Sascha Wanninger
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "basicTypes.h"
#include "ParserDefinition.h"
#include "Builtins.h"
#include "Lval.h"
#include "Environment.h"

/* Local functions */
lval* builtin_var(lenv* e, lval* a, const char* func);
lval* builtin_ord(lenv* e, lval* a, const char* op);
lval* builtin_logical(lenv* e, lval* a, const char* op);
lval* builtin_cmp(lenv* e, lval* a, const char* op);


lval* builtin_op(lenv* e, lval* a, const char* op)
{
	PARAM_NOT_USED(e);
	/* ensure all arguments are numbers */
	for (int i = 0; i < a->count; i++)
	{
	  LASSERT_TYPE(op, a, i, LVAL_NUM);
	}

	/* Pop the first element */
	lval * x = lval_pop(a, 0);

	/* if no arguments and sub then perform unary negation */
	if ((strcmp(op, "-") == 0) && a->count == 0)
	{
		x->num = -x->num;
	}

	/* while there are still elements remaining */
	while (a->count > 0)
	{
		/* pop the next element */
		lval* y = lval_pop(a, 0);

		if (strcmp(op, "+") == 0) { x->num += y->num; }
		if (strcmp(op, "-") == 0) { x->num -= y->num; }
		if (strcmp(op, "*") == 0) { x->num *= y->num; }
		if (strcmp(op, "/") == 0)
		{
			if (y->num == 0)
			{
				lval_del(x);
				lval_del(y);
				x = lval_err("MathError", "Division by zero"); break;
			}
			x->num /= y->num;
		}
		 if (strcmp(op, "min") == 0) { x->num = (x->num < y->num) ? x->num : y->num ; }
		 if (strcmp(op, "max") == 0) { x->num = (x->num > y->num) ? x->num : y->num; }
 		if (strcmp(op, "^") == 0) { x->num = pow(x->num, y->num); }
 		if (strcmp(op, "%") == 0)  { x->num =  ((int)x->num) % ((int) y->num); }

		lval_del(y);
	}

	lval_del(a);
	return x;
}

lval* builtin_env(lenv* e, lval* a)
{
  /* Check Error Conditions */
  LASSERT_NUM("env", a, 0);

  unsigned int i = 0;
  lval* result = lval_qexpr();
  for(i = 0; i < e->count; i++)
  {
    lval_add(result, lval_str(e->syms[i]));
  }

  return result;
}

lval* builtin_fun(lenv* e, lval* a)
{
  /* Check Error Conditions */
  LASSERT_NUM("defun", a, 2);
  LASSERT_TYPE("defun", a, 0, LVAL_QEXPR);
  LASSERT_TYPE("defun", a, 1, LVAL_QEXPR);
  LASSERT_NOT_EMPTY("defun", a, 0);

  /* Build correct Q-expression */
  /* get the first element of first argument */
  lval* signature = lval_pop(a, 0);
  lval* body = lval_pop(a, 0);

  lval* func = lval_pop(signature, 0);
  lval* funcName = lval_add(lval_qexpr(), func);
  lval* formals = signature;
  lval* lambda = lval_add(lval_qexpr(), lval_lambda(e, formals, body));

  /* Concatenate the q expression for the symbol and the lambda definition */
  return builtin_local_def(e, lval_join(lval_add(lval_qexpr(), funcName), lambda));

}

lval* builtin_strlen(lenv* e, lval* a)
{
  LASSERT_NUM("strlen", a, 1);
  LASSERT_TYPE("strlen", a, 0, LVAL_STR);
  
  PARAM_NOT_USED(e);

  lval* v = lval_num(strlen(a->cell[0]->str));
  lval_del(a);

  return v;
}

lval* builtin_numToStr(lenv* e, lval* a)
{
  LASSERT_NUM("num->str", a, 1);
  LASSERT_TYPE("num->str", a, 0, LVAL_NUM);
  
  PARAM_NOT_USED(e);

  char str[12];
  int num = (int) a->cell[0]->num;
  sprintf(str, "%d", num);
  lval* v = lval_str(str);
  lval_del(a);

  return v;
}

lval* builtin_strToNum(lenv* e, lval* a)
{
  LASSERT_NUM("str->num", a, 1);
  LASSERT_TYPE("str->num", a, 0, LVAL_STR);
  
  PARAM_NOT_USED(e);

  lval* v = lval_num(atof(a->cell[0]->str));
  lval_del(a);

  return v;
}

lval* builtin_indexOf(lenv* e, lval* a)
{
  LASSERT_NUM("indexOf", a, 2);
  LASSERT_TYPE("indexOf", a, 0, LVAL_STR);
  LASSERT_TYPE("indexOf", a, 1, LVAL_STR);
  
  PARAM_NOT_USED(e);

  lval* v = lval_num(strcspn(a->cell[0]->str, a->cell[1]->str));
  lval_del(a);

  return v;

}

lval* builtin_substring(lenv* e, lval* a)
{
  LASSERT_NUM("substring", a, 3);
  LASSERT_TYPE("substring", a, 0, LVAL_STR);
  LASSERT_TYPE("substring", a, 1, LVAL_NUM);
  LASSERT_TYPE("substring", a, 2, LVAL_NUM);
  
  PARAM_NOT_USED(e);

  lval* inStr = lval_pop(a, 0);
  lval* firstIndex = lval_pop(a, 0);
  lval* lastIndex = lval_pop(a, 0);
  lval* v = NULL;

  if (lastIndex->num > strlen(inStr->str))
  {
    v = lval_err("StringError", "Index %f is given but string size is %d", lastIndex->num, strlen(inStr->str));
  }
  else
  {
    char* buffer = malloc(lastIndex->num - firstIndex->num + 1);
    memset(buffer, 0 ,lastIndex->num - firstIndex->num + 1);
    memcpy(buffer, &inStr->str[(int)firstIndex->num], lastIndex->num - firstIndex->num);
    v = lval_str(buffer);
    free(buffer);
  }
  lval_del(inStr);
  lval_del(firstIndex);
  lval_del(lastIndex);
  lval_del(a);

  return v;

}

lval* builtin_input(lenv* e, lval* a)
{
  PARAM_NOT_USED(e);	
  
  if(a->count > 0)
  {
    LASSERT_NUM("input", a, 1);
    LASSERT_TYPE("input", a, 0, LVAL_STR);
    lval_print(lval_pop(a, 0));
  }

  char str[512];

  fgets(str, 512, stdin);
  str[strcspn(str, "\n")] = 0;

  lval* v = lval_str(str);
  lval_del(a);

  return v;

}


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

lval* builtin_head(lenv* e, lval* a)
{
  /* Check Error Conditions */
  LASSERT_NUM("head", a, 1);
  LASSERT_TYPE("head", a, 0, LVAL_QEXPR);
  LASSERT_NOT_EMPTY("head", a, 0);
  
  PARAM_NOT_USED(e);

  /* Otherwise take first argument */
  lval* v = lval_take(a, 0);

  /* Delete all elements that are not head and return */
  while(v->count > 1)
  {
    lval_del(lval_pop(v, 1));
  }
  return v;
}



lval* builtin_cons(lenv* e, lval* a)
{
  /* Check Error Conditions */
  LASSERT_NUM("cons", a, 2);
  LASSERT_TYPE("cons", a, 0, LVAL_QEXPR);
  LASSERT_NOT_EMPTY("cons", a, 0);
  
  PARAM_NOT_USED(e);

  lval* val = lval_pop(a, 0);
  lval* v = lval_pop(a, 0);

  v->count++;
  v->cell = realloc(v->cell, sizeof(lval*) * (v->count));
  memmove(&v->cell[1], &v->cell[0], sizeof(lval*) * (v->count - 1));
  v->cell[0] = val;

  return v;
}


lval* builtin_len(lenv* e, lval* a)
{
  LASSERT_NUM("len", a, 1);
  LASSERT_TYPE("len", a, 0, LVAL_QEXPR);
  LASSERT_NOT_EMPTY("len", a, 0);
  
  PARAM_NOT_USED(e);

  lval* l = lval_num(a->cell[0]->count);

  return l;
}

lval* builtin_tail(lenv* e, lval* a)
{
  /* Check Error Conditions */
  LASSERT_NUM("tail", a, 1);
  LASSERT_TYPE("tail", a, 0, LVAL_QEXPR);
  LASSERT_NOT_EMPTY("tail", a, 0);

  PARAM_NOT_USED(e);

  /* Take first argument */
  lval* v = lval_take(a, 0);

  /* Delete first element and return */
  lval_del(lval_pop(v, 0));
  return v;
}

lval* builtin_list(lenv* e, lval* a)
{
  PARAM_NOT_USED(e);
  a->type = LVAL_QEXPR;
  return a;
}

lval* builtin_eval(lenv* e, lval* a)
{
  LASSERT_NUM("eval", a, 1);
  LASSERT_TYPE("eval", a, 0, LVAL_QEXPR);

  lval* x = lval_take(a, 0);
  x->type = LVAL_SEXPR;
  return lval_eval(e, x);
}

lval* builtin_readstr(lenv* e, lval* a)
{
  char* delim = NULL;
  char stdDelimiter[2] = " \0";
  
  PARAM_NOT_USED(e);

  if ( a->count > 1)
  {
    LASSERT_NUM("str->qexpr", a, 2);
    LASSERT_TYPE("str->qexpr", a, 0, LVAL_STR);
    LASSERT_TYPE("str->qexpr", a, 1, LVAL_STR);
    delim = a->cell[1]->str;
  }
  else
  {
    LASSERT_NUM("str->qexpr", a, 1);
    LASSERT_TYPE("str->qexpr", a, 0, LVAL_STR);
    delim = stdDelimiter;
  }
      

  
  lval* ret = lval_qexpr();
  char* str = NULL;

  while((str = strsep(&a->cell[0]->str, delim)) != NULL)
  {
    lval* sym = lval_sym(str);

    lval_add(ret, sym);
  }

  return ret;
}

lval* builtin_writestr(lenv* e, lval* a)
{
  LASSERT_TYPE("qexpr->str", a, 0, LVAL_QEXPR);
  PARAM_NOT_USED(e);

  /* standard delimiter */
  char* delim = NULL;
  char stdDelimiter[2] = " \0";
  if(a->count > 1)
  {
   delim = a->cell[1]->str;
  }
  else
  {
   delim = stdDelimiter;
  }

  if(a->count > 0)
  {
   if(a->cell[0]->count == 0)
   {
    return lval_str("");
   }
   else
   {
    int size = a->cell[0]->count;
    char * stringbuffer = NULL;
    for (int i = 0; i < size; i++)
    {

     char* appendstr = NULL;
     if (stringbuffer!= NULL)
      appendstr = malloc(strlen(stringbuffer) + strlen(a->cell[0]->cell[i]->sym) + strlen(delim) + 1);
     else
      appendstr = malloc(strlen(a->cell[0]->cell[i]->sym) + 1);

     appendstr[0] = '\0';

     if (stringbuffer != NULL)
     {
      strcat(appendstr, stringbuffer);
      strcat(appendstr, delim);
     }
     strcat(appendstr, a->cell[0]->cell[i]->sym);

     if (stringbuffer != NULL)
      free(stringbuffer);
     stringbuffer = appendstr;
    }
    return lval_str(stringbuffer);
  }
 }
 else
 {
  return lval_str("");
 }

}

lval* builtin_append(lenv* e, lval* a)
{
  LASSERT_NUM("append", a, 2);
  LASSERT_TYPE("append", a, 0, LVAL_STR);
  LASSERT_TYPE("append", a, 1, LVAL_STR);
  
  PARAM_NOT_USED(e);

  lval* str1 = lval_pop(a, 0);
  lval* str2 = lval_pop(a, 0);
  
  char* appended = malloc(strlen(str1->str) + strlen(str2->str) + 1);
  appended[0] = 0;

  strcat(appended, str1->str);
  strcat(appended, str2->str);

  lval* v = lval_str(appended);
  free(appended);
  lval_del(str1);
  lval_del(str2);

  return v;
}

lval* builtin_join(lenv* e, lval* a)
{
  LASSERT(a, a->count > 0,  "IncorrectNumberArgs", "Function 'join' got no parameters");
  PARAM_NOT_USED(e);
  
  for (int i = 0; i < a->count; i++)
  {
    LASSERT_TYPE("join", a, i, LVAL_QEXPR);
  }

  lval* x = lval_pop(a, 0);

  while (a->count)
  {
    x = lval_join(x, lval_pop(a, 0));
  }

  lval_del(a);
  return x;
}

lval* builtin_exit(lenv* e, lval* a) {
  lenv_toKill(e);

  return a;
}

lval* builtin_add(lenv* e, lval* a) {
  return builtin_op(e, a, "+");
}

lval* builtin_sub(lenv* e, lval* a) {
  return builtin_op(e, a, "-");
}

lval* builtin_mul(lenv* e, lval* a) {
  return builtin_op(e, a, "*");
}

lval* builtin_div(lenv* e, lval* a) {
  return builtin_op(e, a, "/");
}

lval* builtin_modulo(lenv* e, lval* a) {
  return builtin_op(e, a, "%");
}

lval* builtin_local_def(lenv* e, lval* a) {
  return builtin_var(e, a, "def");
}

lval* builtin_global_def(lenv* e, lval* a) {
  return builtin_var(e, a, "put");
}

lval* builtin_set(lenv* e, lval* a) {
  return builtin_var(e, a, "set");
}

lval* builtin_gt(lenv* e, lval* a) {
  return builtin_ord(e, a, ">");
}

lval* builtin_lt(lenv* e, lval* a) {
  return builtin_ord(e, a, "<");
}

lval* builtin_ge(lenv* e, lval* a) {
  return builtin_ord(e, a, ">=");
}

lval* builtin_le(lenv* e, lval* a) {
  return builtin_ord(e, a, "<=");
}

lval* builtin_or(lenv* e, lval* a) {
  return builtin_logical(e, a, "||");
}

lval* builtin_and(lenv* e, lval* a) {
  return builtin_logical(e, a, "&&");
}

lval* builtin_not(lenv* e, lval* a) {
  LASSERT_NUM("not", a, 1);
  LASSERT_TYPE("not", a, 0, LVAL_BOOL);
  
  PARAM_NOT_USED(e);

  bool r;
  if (a->cell[0]->num == true)
  {
    r = false;
  }
  else
  {
    r = true;
  }
  lval_del(a);
  return lval_bool(r);
}


lval* builtin_ord(lenv* e, lval* a, const char* op) {
  LASSERT_NUM(op, a, 2);
  LASSERT_TYPE(op, a, 0, LVAL_NUM);
  LASSERT_TYPE(op, a, 1, LVAL_NUM);
  
  PARAM_NOT_USED(e);

  bool r;
  if (strcmp(op, ">")  == 0) {
    r = (a->cell[0]->num >  a->cell[1]->num);
  }
  if (strcmp(op, "<")  == 0) {
    r = (a->cell[0]->num <  a->cell[1]->num);
  }
  if (strcmp(op, ">=") == 0) {
    r = (a->cell[0]->num >= a->cell[1]->num);
  }
  if (strcmp(op, "<=") == 0) {
    r = (a->cell[0]->num <= a->cell[1]->num);
  }
  lval_del(a);
  return lval_bool(r);
}

lval* builtin_logical(lenv* e, lval* a, const char* op) {
  LASSERT_NUM(op, a, 2);
  LASSERT_TYPE(op, a, 0, LVAL_BOOL);
  LASSERT_TYPE(op, a, 1, LVAL_BOOL);
  
  PARAM_NOT_USED(e);

  bool r;
    if (strcmp(op, "||")  == 0) {
      r = (a->cell[0]->num ||  a->cell[1]->num);
    }
    if (strcmp(op, "&&")  == 0) {
      r = (a->cell[0]->num &&  a->cell[1]->num);
    }

    lval_del(a);
    return lval_bool(r);
}

lval* builtin_cmp(lenv* e, lval* a, const char* op) {
  LASSERT_NUM(op, a, 2);
  PARAM_NOT_USED(e);
  
  bool r;
  if (strcmp(op, "==") == 0) {
    r =  lval_eq(a->cell[0], a->cell[1]);
  }
  if (strcmp(op, "!=") == 0) {
    r = !lval_eq(a->cell[0], a->cell[1]);
  }
  lval_del(a);
  return lval_bool(r);
}

lval* builtin_eq(lenv* e, lval* a) {
  return builtin_cmp(e, a, "==");
}

lval* builtin_ne(lenv* e, lval* a) {
  return builtin_cmp(e, a, "!=");
}

lval* builtin_print(lenv* e, lval* a) {
  PARAM_NOT_USED(e);

  /* Print each argument followed by a space */
  for (int i = 0; i < a->count; i++) {
    lval_print(a->cell[i]); putchar(' ');
  }

  /* Print a newline and delete arguments */
  putchar('\n');
  lval_del(a);

  return lval_sexpr();
}

lval* builtin_type(lenv* e, lval* a)
{
  LASSERT_NUM("type", a, 1);
  PARAM_NOT_USED(e);
  
  lval* typestring = lval_str(ltype_name(a->cell[0]->type));
  lval_del(a);

  return typestring;
}

lval* builtin_error(lenv* e, lval* a) {
  PARAM_NOT_USED(e);

  lval* err = NULL;
  /*error takes an optional second parameter */
  if (a->count > 1)
  {
    LASSERT_NUM("error", a, 2);
    LASSERT_TYPE("error", a, 0, LVAL_STR);
    LASSERT_TYPE("error", a, 1, LVAL_STR);
    err = lval_err(a->cell[0]->str, a->cell[1]->str);
  }
  else
  {
    LASSERT_NUM("error", a, 1);
    LASSERT_TYPE("error", a, 0, LVAL_STR);
    /* Construct Error from first argument */
    err = lval_err(a->cell[0]->str, "");
  }

  /* Delete arguments and return */
  lval_del(a);
  return err;
}


lval* builtin_require(lenv* e, lval* a) {
  LASSERT_NUM("require", a, 1);
  LASSERT_TYPE("require", a, 0, LVAL_STR);
  PARAM_NOT_USED(e);

  const int pathSizeMax = 4096;
  char* stdLibPath = (char*)malloc(pathSizeMax);
  unsigned int readPathSize = readlink("/proc/self/exe", stdLibPath, pathSizeMax);
  /* Add a terminator to use it as a string as readlink doesn't do that */
  stdLibPath[readPathSize - 6] = '\0';

  if (readPathSize < (4096 - sizeof(a->cell[0]->str)))
  {
    DEBUG_OUT("Standard lib path %s\n", stdLibPath);
    strcat(stdLibPath, a->cell[0]->str);
    /* Argument list with a single argument, the filename */
    lval* args = lval_add(lval_sexpr(), lval_str(stdLibPath));

    /* Pass to builtin load and get the result */
    lval* x = builtin_load(e, args);

    free(stdLibPath);
    return x;
  }
  else
  {
    free(stdLibPath);
    return lval_err("PathError", "");
  }
}


lval* builtin_load_internal(lenv* e, lval* a) {
  LASSERT_NUM("load_internal", a, 1);
  LASSERT_TYPE("load_internal", a, 0, LVAL_STR);

  lenv_register(e, a->cell[0]->str);

  lval_del(a);
  return lval_sexpr();
}


lval* builtin_load(lenv* e, lval* a) {
  LASSERT_NUM("load", a, 1);
  LASSERT_TYPE("load", a, 0, LVAL_STR);
  PARAM_NOT_USED(e);

  /* Parse File given by string name */
  mpc_result_t r;
  if (mpc_parse_contents(a->cell[0]->str, Tama, &r)) {

    /* Read contents */
    lval* expr = lval_read(r.output);
    mpc_ast_delete(r.output);

    /* Evaluate each Expression */
    while (expr->count) {
      lval* x = lval_eval(e, lval_pop(expr, 0));
      /* If Evaluation leads to error print it */
      if (x->type == LVAL_ERR) { lval_println(x); }
      lval_del(x);
    }

    /* Delete expressions and arguments */
    lval_del(expr);
    lval_del(a);

    /* Return empty list */
    return lval_sexpr();

  } else {
    /* Get Parse Error as String */
    char* err_msg = mpc_err_string(r.error);
    mpc_err_delete(r.error);

    /* Create new error message using it */
    lval* err = lval_err("LoadError", "Could not load Library %s", err_msg);
    free(err_msg);
    lval_del(a);

    /* Cleanup and return error */
    return err;
  }
}

lval* builtin_if(lenv* e, lval* a) {
  LASSERT_NUM("if", a, 3);
  LASSERT_TYPE("if", a, 0, LVAL_BOOL);
  LASSERT_TYPE("if", a, 1, LVAL_QEXPR);
  LASSERT_TYPE("if", a, 2, LVAL_QEXPR);
  PARAM_NOT_USED(e);

  /* Mark Both Expressions as evaluable */
  lval* x;
  a->cell[1]->type = LVAL_SEXPR;
  a->cell[2]->type = LVAL_SEXPR;

  if (a->cell[0]->num) {
    /* If condition is true evaluate first expression */
    x = lval_eval(e, lval_pop(a, 1));
  } else {
    /* Otherwise evaluate second expression */
    x = lval_eval(e, lval_pop(a, 2));
  }

  /* Delete argument list and return */
  lval_del(a);
  return x;
}

lval* builtin_var(lenv* e, lval* a, const char* func) {
  LASSERT(a, a->count > 0, "Function '%s' got no parameters", func);
  LASSERT_TYPE(func, a, 0, LVAL_QEXPR);

  lval* result = NULL;
  lval* syms = a->cell[0];
  for (int i = 0; i < syms->count; i++) {
    LASSERT(a, (syms->cell[i]->type == LVAL_SYM),
      "Function '%s' cannot define non-symbol. "
      "Got %s, Expected %s.", func,
      ltype_name(syms->cell[i]->type),
      ltype_name(LVAL_SYM));
  }

  LASSERT(a, (syms->count == a->count-1),
    "Function '%s' passed too many arguments for symbols. "
    "Got %i, Expected %i.", func, syms->count, a->count-1);

  for (int i = 0; i < syms->count; i++) {
    /* If 'set' define in globally. If 'def' define in locally */
    if (strcmp(func, "put") == 0) {
      lenv_def(e, syms->cell[i], a->cell[i+1]);
    }

    if (strcmp(func, "def")   == 0) {
      lenv_put(e, syms->cell[i], a->cell[i+1]);
    }
    
    if (strcmp(func, "set")   == 0) {
      result = lenv_set(e, syms->cell[i], a->cell[i+1]);
    }
    else
    {
      result = lval_sexpr();
    }
  }

  lval_del(a);
  return result;
}

lval* builtin_lambda(lenv* e, lval* a) {
  /* Check Two arguments, each of which are Q-Expressions */
  LASSERT_NUM("lambda", a, 2);
  LASSERT_TYPE("lambda", a, 0, LVAL_QEXPR);
  LASSERT_TYPE("lambda", a, 1, LVAL_QEXPR);

  /* Check first Q-Expression contains only Symbols */
  for (int i = 0; i < a->cell[0]->count; i++) {
    LASSERT(a, (a->cell[0]->cell[i]->type == LVAL_SYM),
      "Cannot define non-symbol. Got %s, Expected %s.",
      ltype_name(a->cell[0]->cell[i]->type),ltype_name(LVAL_SYM));
  }

  /* Pop first two arguments and pass them to lval_lambda */
  lval* formals = lval_pop(a, 0);
  lval* body = lval_pop(a, 0);
  lval_del(a);

  return lval_lambda(e, formals, body);
}


lval* builtin_fileOpen(lenv* e, lval* a)
{
  LASSERT_NUM("fileOpen", a, 2);
  LASSERT_TYPE("fileOpen", a, 0, LVAL_STR);
  LASSERT_TYPE("fileOpen", a, 1, LVAL_STR);

  return lval_file(a->cell[0]->str, a->cell[1]->str);
}

lval* builtin_fileClose(lenv* e, lval* a)
{
  LASSERT_NUM("fileClose", a, 1);
  LASSERT_TYPE("fileClose", a, 0, LVAL_FILE);

  lval* result;
  
  if (a->cell[0]->file == NULL)
  {
      result = lval_err("FileIO", "Not a file");
  }
  else
  {
      fclose(a->cell[0]->file);
      result = lval_sexpr();
  }
  lval_del(a);
  return result;
}

lval* builtin_readchar(lenv* e, lval* a)
{
  LASSERT_NUM("readchar", a, 1);
  LASSERT_TYPE("readchar", a, 0, LVAL_FILE);

  int characterRead;
  char readString [2];
  lval* result;

  characterRead = fgetc(a->cell[0]->file);

  if (characterRead == EOF)
  {
    result = lval_err("FileIO","EOF");
  }
  else
  {
    readString[0] = (char)characterRead;
    readString[1] = '\0';
    result = lval_str(readString);
  }
  lval_del(a);
  return result;
}

lval* builtin_writechar(lenv* e, lval* a)
{
  LASSERT_NUM("writechar", a, 2);
  LASSERT_TYPE("writechar", a, 0, LVAL_FILE);
  LASSERT_TYPE("writechar", a, 1, LVAL_STR);
	
  lval* result = NULL;

  putc(a->cell[1]->str[0], a->cell[0]->file);
  result = lval_copy(a->cell[0]);
  
  lval_del(a);
  
  return result;
}
