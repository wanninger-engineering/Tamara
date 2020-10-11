/*
 * Math.h
 *
 *  Created on: June 4, 2020
 *      Author: Sascha Wanninger
 */

#ifndef _MATHS_H_
#define _MATHS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "basicTypes.h"
#include "ParserDefinition.h"
#include "Lval.h"
#include "Environment.h"

lval* math_rand(lenv* e, lval* a);

#endif
