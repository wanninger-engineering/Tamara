#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "basicTypes.h"
#include "ParserDefinition.h"
#include "Lval.h"
#include "Environment.h"

lval* builtin_chdir(lenv* e, lval* a);
lval* builtin_system(lenv* e, lval* a);


#endif
