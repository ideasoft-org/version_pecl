#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_version.h"
#include <glib.h>

static zend_function_entry version_functions[] = {
    PHP_FE(version_check, NULL)
    PHP_FE(version_left_join, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry version_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_VERSION_EXTNAME,
    version_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    PHP_VERSION_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_VERSION
ZEND_GET_MODULE(version)
#endif


PHP_FUNCTION(version_check)
{

    RETURN_STRING("Version module.\n");
};


PHP_FUNCTION(version_left_join)
{

    zval* h1;
    zval* h2;
    zval* by_key_left;
    zval* by_key_right;

    zval* new_key;
    
    zval* data1;
    zval* data2;

    HashTable* ht1;
    HashTable* ht2;

    zend_ulong   num_idx1;
    zend_string* str_idx1;

    zend_ulong   num_idx2;
    zend_string* str_idx2;
      
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzzzz", &h1, &h2, &by_key_left, &by_key_right, &new_key) == FAILURE) { 
        RETURN_NULL();
    }

    if (Z_TYPE_P(h1) != IS_ARRAY) {
        RETURN_NULL();
    } 

    if (Z_TYPE_P(h2) != IS_ARRAY) {
        RETURN_NULL();
    } 

    if (Z_TYPE_P(by_key_left) != IS_STRING) {
        RETURN_NULL();
    } 

    if (Z_TYPE_P(by_key_right) != IS_STRING) {
        RETURN_NULL();
    } 

    if (Z_TYPE_P(new_key) != IS_STRING) {
        RETURN_NULL();
    } 



    ht1 = Z_ARRVAL_P(h1);
    ht2 = Z_ARRVAL_P(h2);


    ZEND_HASH_FOREACH_KEY_VAL(ht1, num_idx1, str_idx1, data1)
    
        if (Z_TYPE_P(data1) == IS_OBJECT) {


            zval join_results;

            array_init(&join_results);

            add_property_zval_ex(data1 ,Z_STRVAL_P(new_key), strlen(Z_STRVAL_P(new_key)), &join_results);


            zval* search_key;
            zval* search_key2;

            search_key = zend_std_read_property(data1, by_key_left, IS_STRING, NULL, NULL);

            ZEND_HASH_FOREACH_KEY_VAL(ht2, num_idx2, str_idx2, data2)

                if (Z_TYPE_P(data1) == IS_OBJECT) {
                    search_key2 = zend_std_read_property(data2, by_key_right, IS_STRING, NULL, NULL);

                    if (Z_LVAL_P(search_key) == Z_LVAL_P(search_key2)) {
                        zend_hash_next_index_insert_new(Z_ARRVAL_P(&join_results),data2);
                    }
                }

            ZEND_HASH_FOREACH_END();

        }
    ZEND_HASH_FOREACH_END();


    //RETURN_STRING(Z_STRVAL_P(tpl)); 
};



