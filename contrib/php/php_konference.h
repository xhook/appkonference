#ifndef PHP_KONFERENCE_H
#define PHP_KONFERENCE_H

#define PHP_KONFERENCE_EXTNAME	"konference"
#define PHP_KONFERENCE_EXTVER "1.0"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

extern zend_module_entry konference_module_entry;
#define php_konference_ptr &konference_module_entry

#endif
