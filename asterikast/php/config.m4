PHP_ARG_ENABLE(konference,
	[whether to enable the konference extension],
	[  --enable-konference	enable konference support])

if test $PHP_KONFERENCE != "no"; then
	PHP_SUBST(KONFERENCE_SHARED_LIBADD)
	PHP_NEW_EXTENSION(konference, konference.c, $ext_shared)
fi
