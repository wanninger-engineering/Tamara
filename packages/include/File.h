
#ifdef PACKAGE_FILE

#ifndef _FILE_H_
#define _FILE_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "basicTypes.h"
#include "ParserDefinition.h"
#include "Lval.h"
#include "Environment.h"


lval* builtin_fileOpen(lenv* e, lval* a);

lval* builtin_fileClose(lenv* e, lval* a);

lval* builtin_readchar(lenv* e, lval* a);

lval* builtin_writechar(lenv* e, lval* a);
#endif

#endif