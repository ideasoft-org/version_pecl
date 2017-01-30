#ifndef PHP_VERSION_H
 #define PHP_VERSION_H 1
 #define PHP_VERSION_VERSION "1.0"
 #define PHP_VERSION_EXTNAME "version"

 PHP_FUNCTION(version_check);
 PHP_FUNCTION(version_template);
 PHP_FUNCTION(version_left_join);


 extern zend_module_entry version_module_entry;
 #define phpext_version_ptr &version_module_entry
#endif
