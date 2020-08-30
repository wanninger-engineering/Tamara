#include <math.h>
#include "Lval.h"
#include "Environment.h"


lval* lval_call(lenv* e, lval* f, lval* a) {

  /* If Builtin then simply apply that */
  if (f->builtin) { return f->builtin(e, a); }

  /* Record Argument Counts */
  int given = a->count;
  int total = f->formals->count;

  /* Add reference to calling parent environment */
  f->env->par = e;

  /* While arguments still remain to be processed */
  while (a->count) {

    /* If we've ran out of formal arguments to bind */
    if (f->formals->count == 0) {
      lval_del(a); return lval_err("FuncTooManyArgs",
        "Function passed too many arguments. "
        "Got %i, Expected %i.", given, total);
    }

    /* Pop the first symbol from the formals */
    lval* sym = lval_pop(f->formals, 0);

    /* Special Case to deal with '&' */
    if (strcmp(sym->sym, "&") == 0) {

      /* Ensure '&' is followed by another symbol */
      if (f->formals->count != 1) {
        lval_del(a);
        return lval_err("FuncFormatInvalid", "Function format invalid. "
          "Symbol '&' not followed by single symbol.");
      }

      /* Next formal should be bound to remaining arguments */
      lval* nsym = lval_pop(f->formals, 0);
      lenv_put(f->env, nsym, builtin_list(e, a));
      lval_del(sym); lval_del(nsym);
      break;
    }

    /* Pop the next argument from the list */
    lval* val = lval_pop(a, 0);

    /* Bind a copy into the function's environment */
    lenv_put(f->env, sym, val);

    /* Delete symbol and value */
    lval_del(sym); lval_del(val);
  }

  /* Argument list is now bound so can be cleaned up */
  lval_del(a);

  /* If all formals have been bound evaluate */
  if (f->formals->count == 0) {

    /* Evaluate and return */
    return builtin_eval(
      f->env, lval_add(lval_sexpr(), lval_copy(f->body)));
  } else {
    /* Otherwise return partially evaluated function */
    return lval_copy(f);
  }

}

lval* lval_eval(lenv* e, lval* v)
{
  if (v->type == LVAL_SYM)
  {
    lval* x = lenv_get(e, v);
    lval_del(v);
    return x;
  }
	if (v->type == LVAL_SEXPR)
	{
		return lval_eval_sexpr(e, v);
	}
	/* All other lval types remain the same */
	return v;
}

lval* lval_pop(lval* v, int i)
{
	/* find the item at "i" */
	lval* x = v->cell[i];
	
	/* shift memory after the item at "i" over the top */
	 memmove(&v->cell[i], &v->cell[i+1],
	sizeof(lval*) * (v->count - i - 1));

	
	/* decrease the count */
	v->count--;
	
	/* Reallocate the memory used */
	v->cell = realloc(v->cell, sizeof(lval*) * v->count);
	return x;
}





lval* lval_take(lval* v, int i)
{
	lval* x = lval_pop(v, i);
	lval_del(v);
	return x;
}



lval* lval_join(lval* x, lval* y)
{
  /* For each cell in 'y' add it to 'x' */
  while(y->count)
  {
    x = lval_add(x, lval_pop(y, 0));
  }

  lval_del(y);
  return x;
}

lval* lval_eval_sexpr(lenv* e, lval* v)
{
	/* evaluate the children */
	for(int i = 0; i < v->count; i++)
	{
		v->cell[i] = lval_eval(e, v->cell[i]);
	}
	
	/* error checking */
	for (int i = 0; i < v->count; i++)
	{
	  if ((v->cell[i]->type == LVAL_ERR)
	      && (v->cell[0]->type != LVAL_FUN))
	    {
	      return lval_take(v, i);
	    }
	}
	
	/* empty expression */
	if (v->count == 0 )
	{
		return v;
	}
	
	lval* f = lval_pop(v, 0);
	if (f->type != LVAL_FUN) {
	  return f;
	}

	lval* result = lval_call(e, f, v);
	lval_del(f);
	return result;
}

static void lval_expr_print(lval* v, char open, char close);
/* Inlined constructors for LVALs */
/* Construct a new number LVAL */
lval* lval_num(double x)
{
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_NUM;
  v->num = x;
  return v;
}

/* Construct a new boolean LVAL */
lval* lval_bool(bool x)
{
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_BOOL;
  v->num = x;
  return v;
}

/* Construct a new error LVAL */
lval* lval_err(const char* err, const char* fmt, ...) {
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_ERR;

  /* Create a va list and initialize it */
  va_list va;
  va_start(va, fmt);

  /* Allocate 64 bytes for the error name and 512 bytes of space for the info*/
  v->err = malloc(64);
  v->str = malloc(512);

  /* printf error name in string */
  snprintf(v->err, 63, "%s", err);
  /* printf the error info string with a maximum of 511 characters */
  vsnprintf(v->str, 511, fmt, va);

  /* Reallocate to number of bytes actually used */
  v->err = realloc(v->err, strlen(v->err)+1);
  v->str = realloc(v->str, strlen(v->str)+1);

  /* Cleanup our va list */
  va_end(va);

  return v;
}
/* Construct a new symbol LVAL */
lval* lval_sym(const char* s)
{
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_SYM;
  v->sym = malloc(strlen(s) + 1);
  strcpy(v->sym, s);
  v->cell = NULL;
  return v;
}

/* Construct a new sexpr LVAL */
lval* lval_sexpr(void)
{
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_SEXPR;
  v->count = 0;
  v->cell = NULL;
  return v;
}

/* A pointer to a new empty Qexpr lval */
lval* lval_qexpr(void)
{
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_QEXPR;
  v->count = 0;
  v->cell = NULL;
  return v;
}

lval* lval_fun(lbuiltin func)
{
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_FUN;
  v->builtin = func;
  return v;
}

lval* lval_lambda(lenv* e, lval* formals, lval* body) {
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_FUN;

  /* Set Builtin to Null */
  v->builtin = NULL;

  /* Build new environment */
  v->env = lenv_new();
  v->env->par = e;

  /* Set Formals and Body */
  v->formals = formals;
  v->body = body;
  return v;
}

lval* lval_str(const char* s) {
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_STR;
  v->str = malloc(strlen(s) + 1);
  strcpy(v->str, s);
  return v;
}

lval* lval_file(const char* name, const char* mode)
{
    lval* v = malloc(sizeof(lval));
    v->type = LVAL_FILE;
    v->file = fopen(name, mode);
    if (v->file == NULL)
    {
      lval_del(v);
      v = lval_err("FileIO", "File could not be opened or created");
    }
    return v;
}
  

int lval_eq(lval* x, lval* y) {

  int result = 0;
  /* Different Types are always unequal */
  if (x->type != y->type)
  { 
  	result = 0;
  }
  else
  {
    /* Compare Based upon type */
    switch (x->type) {
      /* Compare Number Value */
      case LVAL_BOOL:
      case LVAL_NUM: 
        result = (x->num == y->num);
        break;

      /* Compare String Values */
      case LVAL_ERR: 
        result = (strcmp(x->err, y->err) == 0);
        break;
      case LVAL_SYM: 
        result = (strcmp(x->sym, y->sym) == 0);
        break;

      /* If builtin compare, otherwise compare formals and body */
      case LVAL_FUN:
        if (x->builtin || y->builtin) {
          result = (x->builtin == y->builtin);
        } else {
          result = (lval_eq(x->formals, y->formals)
            && lval_eq(x->body, y->body));
        }
        break;

      /* If list compare every individual element */
      case LVAL_QEXPR:
      case LVAL_SEXPR:
        if (x->count != y->count) 
        { 
        	result = 0; 
        }
        else
        {
          result = 1;
    	  for (int i = 0; (i < x->count) && (result == 1); i++) {
            /* If any element not equal then whole list not equal */
            if (!lval_eq(x->cell[i], y->cell[i])) 
            { 
            	result = 0;
            }
          }
        }
      break;
      case LVAL_STR: 
      	result = (strcmp(x->str, y->str) == 0);
      	break;
      default:
    	result = 0;
    	break;
    }
  }
  return result;
}

void lval_del(lval* v)
{
  switch(v->type)
  {
  case LVAL_NUM: 
    break;

  case LVAL_ERR:
    free(v->err);
    free(v->str);
    break;
  case LVAL_SYM: 
    free(v->sym);
    break;
  case LVAL_QEXPR:
  case LVAL_SEXPR:
    for (int i = 0; i < v->count; i++)
    {
      lval_del(v->cell[i]);
    }
    free(v->cell);
    break;
  case LVAL_FUN:
    if (!v->builtin) {
      lenv_del(v->env);
      lval_del(v->formals);
      lval_del(v->body);
    }
    break;
  case LVAL_STR: 
    free(v->str);
    break;
  case LVAL_FILE:
    break;
  default:
	/* No default required as lval freed afterwards*/
	break;
  }
  free(v);
}


lval* lval_read_num(mpc_ast_t* t)
{
  errno = 0;
  double x = strtof(t->contents, NULL);
  return errno != ERANGE ? lval_num(x) : lval_err("InvalidValue", "invalid number");
}

lval* lval_read_boolean(mpc_ast_t* t)
{
  lval* bool;
  if (strcmp(t->contents, "#t") == 0)
  {
    bool = lval_bool(true);
  }
  else if (strcmp(t->contents, "#f") == 0)
  {
    bool = lval_bool(false);
  }
  else
  {
    bool = lval_err("InvalidValue", "invalid boolean value");
  }

  return bool;
}

lval* lval_read_str(mpc_ast_t* t) {
  /* Cut off the final quote character */
  t->contents[strlen(t->contents)-1] = '\0';
  /* Copy the string missing out the first quote character */
  char* unescaped = malloc(strlen(t->contents+1)+1);
  strcpy(unescaped, t->contents+1);
  /* Pass through the unescape function */
  unescaped = mpcf_unescape(unescaped);
  /* Construct a new lval using the string */
  lval* str = lval_str(unescaped);
  /* Free the string and return */
  free(unescaped);
  return str;
}

lval* lval_read(mpc_ast_t* t)
{
  /* if symbol or number return conversion to that type */
  if (strstr(t->tag, "number"))
  {
    return lval_read_num(t);
  }
  if (strstr(t->tag, "bool"))
  {
    return lval_read_boolean(t);
  }
  if (strstr(t->tag, "symbol"))
  {
    return lval_sym(t->contents);
  }
  /* if root (>) or sexpr then create empty list */
  lval* x = NULL;
  if (strcmp(t->tag, ">") == 0)
  {
    x = lval_sexpr();
  }
  if (strstr(t->tag, "sexpr") )
  {
    x = lval_sexpr();
  }
  if (strstr(t->tag, "qexpr"))
  {
    x = lval_qexpr();
  }
  if (strstr(t->tag, "string"))
  {
    return lval_read_str(t);
  }
      
  DEBUG_OUT("tag: %s\n", t->tag);
  
  /* fill this list with any valid expression contained within */
  for (int i = 0; i < t->children_num-1; i++)
  {
    if (strcmp(t->children[i]->contents, "(") == 0)
    {
      continue;
    }
    if (strcmp(t->children[i]->contents, ")") == 0)
    {
      continue;
    }
    if (strcmp(t->children[i]->contents, "[") == 0)
    {
      continue;
    }
    if (strcmp(t->children[i]->contents, "]") == 0)
    {
      continue;
    }
    if (strcmp(t->children[i]->tag, "regex") == 0)
    {
      continue;
    }
    if (strstr(t->children[i]->tag, "comment"))
    {
      continue;
    }
    x = lval_add(x, lval_read(t->children[i]));
  }
  return x;
}

lval* lval_add(lval* v, lval* x)
{
  v->count++;
  v->cell = realloc(v->cell, sizeof(lval *) * v->count);
  v->cell[v->count - 1] = x;
  return v;
}


lval* lval_copy(lval* v)
{
  lval* x = malloc(sizeof(lval));
  x->type = v->type;

  switch(v->type)
  {
    /* Copy functions and numbers directly */
    case LVAL_FUN:
      if (v->builtin) {
        x->builtin = v->builtin;
      } else {
        x->builtin = NULL;
        x->env = lenv_copy(v->env);
        x->formals = lval_copy(v->formals);
        x->body = lval_copy(v->body);
      }
    break;
    case LVAL_NUM:
    case LVAL_BOOL:
      x->num = v->num; break;

    /* Copy strings using malloc and strcpy */
    case LVAL_ERR:
      x->err = malloc(strlen(v->err) +1);
      strcpy(x->err, v->err);
      x->str = malloc(strlen(v->str) +1);
      strcpy(x->str, v->str);
      break;
    case LVAL_SYM:
      x->sym = malloc(strlen(v->sym) +1);
      strcpy(x->sym, v->sym);
      break;

    /* Copy lists by copying each sub-expression */
    case LVAL_SEXPR:
    case LVAL_QEXPR:
      x->count = v->count;
      x->cell = malloc(sizeof(lval*) * x->count);
      for (int i = 0; i < x->count; i++) {
	x->cell[i] = lval_copy(v->cell[i]);
      }
    break;
    case LVAL_STR: 
      x->str = malloc(strlen(v->str) + 1);
      strcpy(x->str, v->str);
      break;
  case LVAL_FILE:
      x->file = v->file;
      break;
    default:
	  /* On internal error, free the lval and create a new LVAL_ERR */
      free(x);
      x = lval_err("InternalError", "Type unknown");
      break;
  }

  return x;
}


void lval_expr_print(lval* v, char open, char close)
{
  DEBUG_OUT("EXPR PRINT\n");
  putchar(open);
  for (int i = 0; i < v->count; i++)
  {
    /* print value contained within */
    lval_print(v->cell[i]);
    /* dont print trailing space if last element */
    if ( i != (v->count - 1)) 
    {
      putchar(' ');
    }
  }
  
  putchar(close);
}

void lval_print_str(lval* v) {
  printf("%s", v->str);
}

void lval_print(lval* v)
{
  switch (v->type)
  {
    case LVAL_NUM:
      printf("%f", v->num);
      break;
    case LVAL_BOOL:
      if (((int)v->num) == true)
      {
        printf("#t");
      }
      else
      {
        printf("#f");
      }
      break;
    case LVAL_ERR:
      printf("Error: %s  %s", v->err, v->str);
      break;
    case LVAL_SYM:
      printf("%s", v->sym);
      break;
    case LVAL_SEXPR:
      lval_expr_print(v, '(', ')');
      break;
    case LVAL_STR:
      lval_print_str(v);
      break;
    case LVAL_QEXPR:
      lval_expr_print(v, '[', ']');
      break;
    case LVAL_FUN:
      if (v->builtin) {
        printf("<builtin>");
      } else {
        printf("(lambda "); lval_print(v->formals);
        putchar(' '); lval_print(v->body); putchar(')');
      }
      break;
  case LVAL_FILE:
      printf("<File Handle>");
      break;
    default:
      break;
  }
}
void lval_println(lval* v)
{
  lval_print(v); putchar('\n');
}


const char* ltype_name(int t) {
  switch(t) {
  case LVAL_FUN: return "Function";
  case LVAL_NUM: return "Number";
  case LVAL_ERR: return "Error";
  case LVAL_SYM: return "Symbol";
  case LVAL_SEXPR: return "S-Expression";
  case LVAL_QEXPR: return "Q-Expression";
  case LVAL_BOOL: return "Boolean";
  case LVAL_STR: return "String";
  case LVAL_FILE: return "<File>";
  default: return "Unknown";
  }
}
