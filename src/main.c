#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#ifdef LINUX
#include <readline/readline.h>
#include <readline/history.h>
#endif

#include "mpc.h"
#include "ParserDefinition.h"
#include "Environment.h"
#define INPUT_BUFFER_SIZE (2048)

/* Standard library loader function */
void loadStandardLibrary(lenv* e);

#ifndef LINUX
/* Declare a buffer for user input of size 2048 */
static char buffer[INPUT_BUFFER_SIZE];

char* readline(char* prompt)
{
  fputs(prompt, stdout);
  fgets(buffer, INPUT_BUFFER_SIZE, stdin);
   char* cpy = malloc (strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
} 

void add_history(char* unused) {}
#endif


int main(int argc, char** argv)
{
  double result = 0.0;
  initParserDefinition();
  lenv* e = lenv_new();
  lenv_add_builtins(e);

  loadStandardLibrary(e);

  /* Supplied with list of files */
  if (argc >= 2) {

    /* loop over each supplied filename (starting from 1) */
    for (int i = 1; i < argc; i++) {

      /* Argument list with a single argument, the filename */
      lval* args = lval_add(lval_sexpr(), lval_str(argv[i]));

      /* Pass to builtin load and get the result */
      lval* x = builtin_load(e, args);

      /* If the result is an error be sure to print it */
      if (x->type == LVAL_ERR) { lval_println(x); }
      lval_del(x);
    }
  }
  else
  {
    /* Print Version and Exit Information */
    puts("Tamara Interpreter Version 1.0.0");
    puts("Use Ctrl-c or (exit) to Exit\n");
    /* In a never ending loop */
    while (e->toKill == 0)
    {
      char* input = readline("tami>");
      add_history(input);

      /* Attempt to parse the user input */
      mpc_result_t parserResult;
      if (mpc_parse("<stdin>", input, Tama, &parserResult)) {
        lval* x = lval_eval(e, lval_read(parserResult.output));
        lval_println(x);
        result = x->num;
        lval_del(x);
        mpc_ast_delete(parserResult.output);
        }
      else {
        mpc_err_print(parserResult.error);
        mpc_err_delete(parserResult.error);
      }

      free(input);
    }
  }

  lenv_del(e);
  cleanupParserDefinition();
  return result;
}

void loadStandardLibrary(lenv* e)
{
  const int pathSizeMax = 4096;
  char stdLibName[10] = "StdLib.ta";
  char* stdLibPath = (char*)malloc(pathSizeMax);
  unsigned int readPathSize = readlink("/proc/self/exe", stdLibPath, pathSizeMax);
  /* Add a terminator to use it as a string as readlink doesn't do that */
  stdLibPath[readPathSize] = '\0';

  if (readPathSize < (4096 - sizeof(stdLibName)))
  {
    DEBUG_OUT("Standard lib path %s\n", stdLibPath);
    strcat(stdLibPath, stdLibName);
    /* Argument list with a single argument, the filename */
    lval* args = lval_add(lval_sexpr(), lval_str(stdLibPath));

    /* Pass to builtin load and get the result */
    lval* x = builtin_load(e, args);

    /* If the result is an error be sure to print it */
    if (x->type == LVAL_ERR) { lval_println(x); }
    lval_del(x);
  }
  free(stdLibPath);
}
