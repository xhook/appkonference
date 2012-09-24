#include "php_konference.h"
#include "ext/standard/info.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/mman.h>

#include "php_ini.h"

PHP_INI_BEGIN()
	PHP_INI_ENTRY("konference.file", "/tmp/speaker-scoreboard", PHP_INI_SYSTEM, NULL)
	PHP_INI_ENTRY("konference.size", "4096", PHP_INI_SYSTEM, NULL)
PHP_INI_END()

static char *speaker_scoreboard;
static size_t speaker_scoreboard_size;
static char *speaker_scoreboard_file;

PHP_FUNCTION(is_speaking)
{
	long score_id;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &score_id) == FAILURE) {
		RETURN_NULL();
	}
	RETVAL_BOOL(*(speaker_scoreboard + score_id));
	return;
}

static zend_function_entry php_konference_functions[] = {
	PHP_FE(is_speaking, NULL)
	{ NULL, NULL, NULL }
};

PHP_MINIT_FUNCTION(konference)
{
	REGISTER_INI_ENTRIES();

	speaker_scoreboard_file = INI_STR("konference.file");
	speaker_scoreboard_size = INI_INT("konference.size");

	int fd = open(speaker_scoreboard_file,O_RDONLY);

	if ( fd > -1 ) {
		if ( (speaker_scoreboard = (char*)mmap(NULL, speaker_scoreboard_size, PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED ) {
			php_printf("konference module unable to mmap scoreboard file!?\n");
		}
		close(fd);
	}
	else {
		php_printf("konference module unable to open speaker scoreboard file!?\n");
	}
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(konference)
{
	UNREGISTER_INI_ENTRIES();

	if ( speaker_scoreboard ) {
		munmap(speaker_scoreboard, speaker_scoreboard_size);
	}
	return SUCCESS;
}

PHP_MINFO_FUNCTION(konference)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "konference support", "enabled");
	php_info_print_table_row(2, "konference version", PHP_KONFERENCE_EXTVER);
	php_info_print_table_end();
	DISPLAY_INI_ENTRIES();
}

zend_module_entry konference_module_entry = {
	STANDARD_MODULE_HEADER,
	PHP_KONFERENCE_EXTNAME,
	php_konference_functions,
	PHP_MINIT(konference),
	PHP_MSHUTDOWN(konference),
	NULL,
	NULL,
	PHP_MINFO(konference),
	PHP_KONFERENCE_EXTVER,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_KONFERENCE
ZEND_GET_MODULE(konference)
#endif
