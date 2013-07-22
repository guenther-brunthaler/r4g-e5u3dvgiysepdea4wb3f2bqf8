/*
 * (c) 2013 by Guenther Brunthaler.
 * This source file is free software.
 * Distribution is permitted under the terms of the LGPLv3.
 */


#ifdef HAVE_CONFIG_H
   #include "config.h"
#endif
#include <stdlib.h>
#include <string.h>
#include "r4g_u0ywydbuiziuzssqsi5l0mdid.h"
#include "r4gmem_8czm5ri1pjjnj3lr8wqq0a6li.h"


extern char *r4g_strdup(r4g *xc, char const *ephemeral_string) {
   size_t bytes;
   char *s= r4g_malloc(xc, bytes= strlen(ephemeral_string) + sizeof(char));
   (void)memcpy(s, ephemeral_string, bytes);
   return s;
}
