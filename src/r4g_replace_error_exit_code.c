/*
 * (c) 2013 by Guenther Brunthaler.
 * This source file is free software.
 * Distribution is permitted under the terms of the LGPLv3.
 */


#ifdef HAVE_CONFIG_H
   #include "config.h"
#endif
#include "r4g_u0ywydbuiziuzssqsi5l0mdid.h"
#include "r4g_internals.h"


extern void r4g_replace_error_exit_code(r4g *xc, int error_exit_code) {
   struct r4g_internal *fc= (struct r4g_internal *)xc;
   fc->failure_exit_code= error_exit_code;
}
