/*
 * Do nothing. But do it in a clean, proper way.
 *
 * Version 2020.20
 * (c) 2013-2020 by Guenther Brunthaler <gb_about_gnu@gmx.net>.
 * This program is free software.
 * Distribution is permitted under the terms of the LGPLv3.
 */


#ifdef HAVE_CONFIG_H
   #include "config.h"
#endif
#include <r4g/r4g_u0ywydbuiziuzssqsi5l0mdid.h>
#include <stdlib.h>
#include <stddef.h>

static int retval= EXIT_FAILURE;

/* The resource cleanup handler sets up a successful return code. */
static void retval_setter_destructor(void) {
   R4G_DEFINE_INIT_RPTR(struct minimal_resource, *r=, dtor);
   r4g.rlist= r->saved;
   retval= EXIT_SUCCESS;
}

int main(int argc, char **argv) {
   struct minimal_resource retval_setter; /* A resource to be used. */
   (void)argc; (void)argv;
   /* Set up and register resource. */
   retval_setter.dtor= &retval_setter_destructor;
   retval_setter.saved= r4g.rlist;
   r4g.rlist= &retval_setter.dtor;
   release_c1();
   return retval;
}
