/*
 * Curl.h
 *
 *  Created on: May 18, 2020
 *      Author: Sascha Wanninger
 */

#ifdef PACKAGE_CURL

#ifndef _CURL_H_
#define _CURL_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#include "basicTypes.h"
#include "ParserDefinition.h"
#include "Lval.h"
#include "Environment.h"


#include <curl/curl.h>

lval* curl_checkErrCode(lenv* e, lval* a);
lval* curl_url2file(lenv* e, lval* a);
#endif
#endif