/*
 * Curl.h
 *
 *  Created on: May 18, 2020
 *      Author: Sascha Wanninger
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <curl/curl.h>

lval* curl_checkErrCode(lenv* e, lval* a);
lval* curl_url2file(lenv* e, lval* a);