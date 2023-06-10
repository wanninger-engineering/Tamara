/*
 * Math.c
 *
 *  Created on: June 10, 2023
 *      Author: Sascha Wanninger
 */
 
#include "genann_package.h"

genann *ann = NULL;


lval* genann_package_init(lenv* e, lval* a)
{
	LASSERT_NUM("genann->init", a, 4);
 	LASSERT_TYPE("genann->init", a, 0, LVAL_NUM);
  	LASSERT_TYPE("genann->init", a, 1, LVAL_NUM);
	LASSERT_TYPE("genann->init", a, 2, LVAL_NUM);
	LASSERT_TYPE("genann->init", a, 3, LVAL_NUM);

	int inputs = (int) a->cell[0]->num;
	int hidden_layers = (int) a->cell[1]->num;
	int hidden = (int) a->cell[2]->num;
	int outputs = (int) a->cell[3]->num;

	
	if (ann != NULL)
	{
		genann_free(ann);
	}
	ann = genann_init(inputs, hidden_layers, hidden, outputs);
	
	lval_del(a);

	lval* result = lval_object(ann);
	return result;
}