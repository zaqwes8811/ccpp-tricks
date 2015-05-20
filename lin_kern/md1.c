#include <linux/init.h>
#include <linux/module.h>

#include "md.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR( "...");

/// /// ///

char* md1_data = "Hello world!";

extern char* md1_proc( void ) {
    return md1_data;
}

// private
static char* md1_local( void ) {
    return md1_data;
}

extern char* md1_noexport( void ) {
   return md1_data;
}

// !! part Kernel API - all exported names
//
// Make names known kernel
//
// loading order can be matter
//
// Kernel ref count modules what use it. Can't remove module
//   if somewhat use it
EXPORT_SYMBOL( md1_data );
EXPORT_SYMBOL( md1_proc );

/// /// ///

// "+ ..." My module - help find in journal
static
int
__init md_init( void ) {
   printk( "+ module md1 start!\n" );
   return 0;
}

static
void  // return nothing
__exit md_exit( void ) {
   printk( "+ module md1 unloaded!\n" );
}

module_init( md_init );
module_exit( md_exit );

/// /// ///
