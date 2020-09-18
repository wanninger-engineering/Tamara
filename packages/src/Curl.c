/*
 * Curl.c
 *
 *  Created on: May 18, 2020
 *      Author: Sascha Wanninger
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <curl/curl.h>

#include "basicTypes.h"
#include "ParserDefinition.h"
#include "Curl.h"
#include "Lval.h"
#include "Environment.h"

lval* curl_checkErrCode(lenv* e, lval* a) {
    LASSERT_NUM("curl_checkErrCode", a, 1);
    LASSERT_TYPE("curl_checkErrCode", a, 0, LVAL_STR);
    PARAM_NOT_USED(e);

    CURL *curl;
    CURLcode res;
    long code;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, a->cell[0]->str);
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
        res = curl_easy_perform(curl);
        curl_easy_getinfo(curl,CURLINFO_HTTP_CODE,&code);
        curl_easy_cleanup(curl);
    }
    return lval_num((double) code);
}

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}
 
lval* curl_url2file(lenv* e, lval* a) {
  LASSERT_NUM("curl_url2file", a, 2);
  LASSERT_TYPE("curl_url2file", a, 0, LVAL_STR);
  LASSERT_TYPE("curl_url2file", a, 1, LVAL_STR);
  PARAM_NOT_USED(e);
  CURL *curl_handle;
  FILE *pagefile;
  lval* result;
 
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* init the curl session */ 
  curl_handle = curl_easy_init();
 
  /* set URL to get here */ 
  curl_easy_setopt(curl_handle, CURLOPT_URL, a->cell[0]->str);
 
  /* Switch on full protocol/debug output while testing */ 
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 0L);
 
  /* disable progress meter, set to 0L to enable it */ 
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
 
  /* send all data to this function  */ 
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
 
  /* open the file */ 
  pagefile = fopen(a->cell[1]->str, "wb");
  if(pagefile) {
 
    /* write the page body to this file handle */ 
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);
 
    /* get it! */ 
    curl_easy_perform(curl_handle);
 
    /* close the header file */ 
    fclose(pagefile);
    result = lval_sexpr();
  }
  else
  {
    result = lval_err("FileIO", "File could not be opened");
  }
 
  /* cleanup curl stuff */ 
  curl_easy_cleanup(curl_handle);
 
  curl_global_cleanup();
  
  return result;
}
