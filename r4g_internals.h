/*
 * #include "r4g_internals.h"
 *
 * (c) 2013 by Guenther Brunthaler.
 * This source file is free software.
 * Distribution is permitted under the terms of the LGPLv3.
 */


#include "r4g_u0ywydbuiziuzssqsi5l0mdid.h"
#include <stddef.h>


struct r4g_internal {
   r4g xc;
   r4g_resource *resources;
   size_t num_resources, reserved_resources;
   int failure_exit_code;
   int *destruction_notification;
};
