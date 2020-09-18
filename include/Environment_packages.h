#ifndef _ENVIRONMENT_PACKAGES_H_
#define _ENVIRONMENT_PACKAGES_H_

#include "Environment.h"

void lenv_reg_file(lenv* e);
void lenv_reg_curl(lenv* e);
void lenv_reg_math(lenv* e);
#ifdef PACKAGE_OS
void lenv_reg_os(lenv* e);
#endif

#endif /* _ENVIRONMENT_H_ */
