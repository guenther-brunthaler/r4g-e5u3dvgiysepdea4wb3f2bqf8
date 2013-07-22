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
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>


static void free_context(r4g *xc, void *related_data) {
   struct r4g_internal *fc;
   int ok, self, failure_exit_code;
   assert(related_data);
   fc= (struct r4g_internal *)related_data;
   ok= xc->ok;
   self= xc == &fc->xc; /* Are we are deallocating ourselves? */
   failure_exit_code= fc->failure_exit_code;
   assert(fc->num_resources == 0);
   if (fc->reserved_resources) free(fc->resources);
   if (fc->destruction_notification) {
      /*
       * Inform next outer currently executing r4g_free() that
       * it must stop processing immediately because its xc has just been
       * destroyed. That instance is expected to have saved the
       * notification address of the next outer instance and replicate the
       * notification there, if any.
       */
      *fc->destruction_notification= 1;
   }
   #ifndef NDEBUG
      (void)memset(fc, (int)(char)(unsigned)-1, sizeof *fc);
   #endif
   free(fc);
   if (ok) return;
   if (self) exit(failure_exit_code);
   r4g_die(xc, "Unhandled exception in nested resource context!");
}


extern r4g *r4g_create(int error_exit_code) {
   struct r4g_internal *fc;
   if (!(fc= malloc(sizeof *fc))) exit(error_exit_code);
   #ifndef NDEBUG
      (void)memset(fc, (int)(char)(unsigned)-1, sizeof *fc);
   #endif
   fc->destruction_notification= 0;
   fc->xc.ok= 1;
   fc->resources= 0;
   fc->num_resources= fc->reserved_resources= 0;
   fc->failure_exit_code= error_exit_code;
   r4g_add(&fc->xc, free_context, fc);
   return &fc->xc;
}


extern void r4g_free(r4g *xc, size_t keep_num_resources) {
   struct r4g_internal *fc= (struct r4g_internal *)xc;
   int *outer_notification= fc->destruction_notification;
   int destroyed= 0;
   fc->destruction_notification= &destroyed;
   while (fc->num_resources > keep_num_resources) {
      r4g_resource *r= fc->resources + --fc->num_resources;
      /* This call could destroy xc! */
      (*r->cleanup)(xc, r->data);
      if (destroyed) {
         if (outer_notification) {
            /*
             * Notify next instance that the context has already been
             * destroyed.
             */
            *outer_notification= destroyed;
         }
         return; /* Return because there is nothing more to free. */
      }
   }
   assert(!destroyed);
   /* Restore saved previous notification. */
   fc->destruction_notification= outer_notification;
}


extern void r4g_add(
   r4g *xc, r4g_deallocator cleanup, void *related_data
) {
   struct r4g_internal *fc= (struct r4g_internal *)xc;
   if (fc->num_resources >= fc->reserved_resources) {
      void *r;
      size_t wanted;
      for (wanted= 1; wanted <= fc->num_resources; ) wanted<<= 1;
      if (!(r= realloc(fc->resources, wanted * sizeof *fc->resources))) {
         int *outer_notification= fc->destruction_notification;
         int destroyed= 0;
         int failure_exit_code= fc->failure_exit_code;
         fc->destruction_notification= &destroyed;
         if (xc->ok) {
            xc->suppressed_errors= 0;
            xc->ok= 0;
         } else {
            unsigned nse= xc->suppressed_errors + 1;
            if (nse > xc->suppressed_errors) xc->suppressed_errors= nse;
         }
         (void)fprintf(
               stderr,
               "Could not enlarge resource vector to %lu entries!\n"
            ,  (unsigned long)wanted
         );
         (*cleanup)(xc, related_data); /* Might destroy xc! */
         if (destroyed) {
            if (outer_notification) *outer_notification= destroyed;
            exit(failure_exit_code);
         }
         /* Should never return because of unhandled exception. */
         r4g_free(xc, 0);
         /* But if someone handled the exception, terminate anyway. */
         exit(failure_exit_code);
      }
      fc->resources= r;
      fc->reserved_resources= wanted;
   }
   {
      r4g_resource *r= fc->resources + fc->num_resources++;
      r->cleanup= cleanup;
      r->data= related_data;
   }
}


extern void r4g_die(r4g *xc, char const *msg, ...) {
   struct r4g_internal *fc;
   int failure_exit_code;
   assert(xc);
   fc= (struct r4g_internal *)xc;
   failure_exit_code= fc->failure_exit_code;
   if (xc->ok) {
      xc->suppressed_errors= 0;
      xc->ok= 0;
      va_list arg;
      va_start(arg, msg);
      (void)vfprintf(stderr, msg, arg);
      va_end(arg);
      (void)fputc('\n', stderr);
   } else {
      unsigned nse= xc->suppressed_errors + 1;
      if (nse > xc->suppressed_errors) xc->suppressed_errors= nse;
   }
   r4g_free(xc, 0); /* Should never return because of unhandled exception. */
   /* But if someone handled the exception, terminate anyway. */
   exit(failure_exit_code);
}
