/*
 * Implement a global environment as a hash table.
 *
 * (c) 2013 by Guenther Brunthaler <gb_about_gnu@gmx.net>.
 * This program is free software.
 * Distribution is permitted under the terms of the LGPLv3.
 */


#ifdef HAVE_CONFIG_H
   #include "config.h"
#endif
#include "r4g_internals.h"
#include "r4g_u0ywydbuiziuzssqsi5l0mdid.h"
#include "r4gmem_8czm5ri1pjjnj3lr8wqq0a6li.h"
#include "r4gstdio_tsq4kr2x9qnr3sh1jgkaaf8qg.h"
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>


struct rstate {
   int rbuf, left;
};


static void randomfill(struct rstate *st, void *target, size_t bytes) {
   register rbuf= st->rbuf, left= st->left;
   while (bytes--) {
      if (left < UCHAR_MAX) {
         rbuf= rand(); left= RAND_MAX;
         assert(left >= UCHAR_MAX);
      }
      *(unsigned char *)target++= (unsigned char)rbuf;
      rbuf>>= CHAR_BIT;
      left>>= CHAR_BIT;
   }
   st->rbuf= rbuf; st->left= left;
}


int main(int argc, char **argv) {
   r4g *xc;
   (void)argc; (void)argv;
   xc= r4g_create(EXIT_FAILURE);
   {
      #define TEST_ENTRIES 1000000
      uint_least32_t *keys= r4g_malloc(xc, TEST_ENTRIES * sizeof *keys);
      uint_least32_t *pert= r4g_malloc(xc, TEST_ENTRIES * sizeof *pert);
      void **values= r4g_malloc(xc, TEST_ENTRIES * sizeof *values);
      uint_fast32_t i;
      int rnd, left= 0;
      struct rstate r;
      (void)memset(&r, 0, sizeof r);
      srand(0);
      for (i= 0; i < TEST_ENTRIES; ++i) {
         int st;
         pert[i]= i;
         randomfill(&r, keys + i, sizeof *keys);
         randomfill(&r, values + i, sizeof *values);
      }
      for (i= 0; i < TEST_ENTRIES; ++i) {
         uint_least64_t jbuf;
         uint_fast32_t j;
         uint_least32_t h;
         randomfill(&r, &jbuf, sizeof jbuf);
         j= jbuf % TEST_ENTRIES;
         h= pert[i]; pert[i]= pert[j]; pert[j]= h;
         r4g_assoc(xc, keys + i, values[i]);
      }
      for (i= 0; i < TEST_ENTRIES; ++i) {
         uint_fast32_t j= pert[i];
         void *got= r4g_lookup(xc, keys + j);
         if (got != values[j]) {
            r4g_die(
               xc, "Oh no!"
            );
         }
      }
      #if 0
         dump_table(xc);
      #endif
   }
   r4g_free(xc, 0);
   return EXIT_SUCCESS;
}
