PHP_ARG_ENABLE(version, whether to enable Version support,
[ --enable-version   Enable Version support])
if test "$PHP_VERSION" = "yes"; then
  AC_DEFINE(HAVE_VERSION, 1, [Whether you have Version])
  PHP_NEW_EXTENSION(version, src/version.c, $ext_shared)
fi
