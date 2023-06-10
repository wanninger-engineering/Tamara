/*
 * Math.h
 *
 *  Created on: June 10, 2023
 *      Author: Sascha Wanninger
 */

#ifndef _GENANN_PACKAGE_H_
#define _GENANN_PACKAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "basicTypes.h"
#include "ParserDefinition.h"
#include "Lval.h"
#include "Environment.h"

#include "genann/genann.h"

lval* genann_package_init(lenv* e, lval* a);

#endif