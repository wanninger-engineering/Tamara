#include "Environment_packages.h"

#ifdef PACKAGE_FILE
#include "Curl.h"
#endif

#ifdef PACKAGE_MATH
#include "Maths.h"
#endif

#ifdef PACKAGE_FILE
#include "File.h"
#endif

#ifdef PACKAGE_OS
#include "System.h"
#endif

struct lenv_packages packages []=
  {
#ifdef PACKAGE_FILE
   { "file", lenv_reg_file},
#endif
   
#ifdef PACKAGE_CURL
   { "curl", lenv_reg_curl},
#endif
   
#ifdef PACKAGE_MATH
   { "math", lenv_reg_math},
#endif
   
#ifdef PACKAGE_OS
   { "os", lenv_reg_os}
#endif
  };


void lenv_register(lenv* e, char* name)
{
  int i = 0;
  for (i=0; i<(sizeof(packages)/sizeof(struct lenv_packages)); i++)
    {
      if (strcmp(name, packages[i].name) == 0)
	{
	  (*packages[i].reg_fun)(e);
	}
    }
}


#ifdef PACKAGE_FILE
void lenv_reg_file(lenv* e)
{
  lenv_add_builtin(e, "file->open", builtin_fileOpen);
  lenv_add_builtin(e, "file->close", builtin_fileClose);
  lenv_add_builtin(e, "file->readchar", builtin_readchar);
  lenv_add_builtin(e, "file->writechar", builtin_writechar);
}
#endif

#ifdef PACKAGE_CURL
void lenv_reg_curl(lenv* e)
{
  lenv_add_builtin(e, "curl->check", curl_checkErrCode);
  lenv_add_builtin(e, "curl->url2file", curl_url2file);
}
#endif

#ifdef PACKAGE_MATH
void lenv_reg_math(lenv* e)
{
  lenv_add_builtin(e, "math->rand", math_rand);
}
#endif

#ifdef PACKAGE_OS
void lenv_reg_os(lenv* e)
{
  lenv_add_builtin(e, "system",   builtin_system);
  lenv_add_builtin(e, "chdir", builtin_chdir);
}
#endif
