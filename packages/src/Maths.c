/*
 * Math.c
 *
 *  Created on: June 4, 2020
 *      Author: Sascha Wanninger
 */
 
#include "Maths.h"


lval* math_rand(lenv* e, lval* a)
{
	LASSERT_NUM("math->rand", a, 0);
	
	unsigned int randomNumber = rand();
	lval* result = lval_num((double) randomNumber);
	
	lval_del(a);
	return result;
}