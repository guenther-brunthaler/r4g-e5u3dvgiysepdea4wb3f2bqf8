/*
 * Implementation of a context-environment as a trivial hash table.
 *
 * (c) 2013 by Guenther Brunthaler <gb_about_gnu@gmx.net>.
 * This program is free software.
 * Distribution is permitted under the terms of the LGPLv3.
 */


#ifdef HAVE_CONFIG_H
   #include "config.h"
#endif

#define DUMP_TABLE 0

#if DUMP_TABLE
   #include "r4gstdio_tsq4kr2x9qnr3sh1jgkaaf8qg.h"
   #include <inttypes.h>
#endif
#include "r4g_internals.h"
#include "r4g_u0ywydbuiziuzssqsi5l0mdid.h"
#include "r4gmem_8czm5ri1pjjnj3lr8wqq0a6li.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


struct bucket {
   uint_least32_t const *key;
   void *value;
};

struct r4g_env {
   struct bucket *table;
   uint_fast32_t bitmask, allocatable_entries;
};


#if DUMP_TABLE
   extern void r4g_dump_assocs(r4g *xc) {
      struct r4g_internal *fc= (struct r4g_internal *)xc;
      struct r4g_env *e= fc->env;
      uint_fast32_t i;
      r4ga_printf(
            xc
         ,  "table = %p, bitmask = %#" PRIxFAST32
            ", allocatable_entries = %" PRIuFAST32 "\n"
         ,  e->table, e->bitmask, e->allocatable_entries
      );
      for (i= 0; i <= e->bitmask; ++i) {
         r4ga_printf(xc, "[%" PRIuFAST32 "] = {key=", i);
         if (e->table[i].key) {
            r4ga_printf(xc, "%" PRIxFAST32, *e->table[i].key);
         } else {
            r4ga_fputs(xc, "NONE", stdout);
         }
         r4ga_fputs(xc, " @ ", stdout);
         if (e->table[i].key) {
            r4ga_printf(xc, "%p", e->table[i].key);
         } else {
            r4ga_fputs(xc, "NULL", stdout);
         }
         r4ga_fputs(xc,", value=", stdout);
         if (e->table[i].value) {
            r4ga_printf(xc,"%p", e->table[i].value);
         } else {
            r4ga_fputs(xc, "NULL", stdout);
         }
         r4ga_puts(xc, "}");
      }
      r4ga_puts(xc, "");
   }
#endif


static void grow_table(r4g *xc, struct r4g_env *env) {
   uint_fast32_t nc, oc, nm, ae;
   struct bucket *nt, *ob;
   {
      size_t nwbytes;
      nt= r4ga_malloc(
         xc, nwbytes= (nc= (oc= env->bitmask + 1) << 1) * sizeof *nt
      );
      (void)memset(nt, 0, nwbytes);
   }
   ae= nc >> 1;
   nm= nc - 1;
   ob= env->table;
   while (oc--) {
      if (ob->key) {
         struct bucket *nb;
         uint_fast32_t i;
         /* Locate next free slot after the entry's collision chain. */
         for (i= *ob->key & nm; (nb= nt + i)->key; i= (i + 1) & nm) ;
         /* Move contents of old bucket <ob> into new table. */
         *nb= *ob;
         assert(ae > 0); /* There should always be enough free space. */
         --ae; /* Another table entry consumed. */
      }
      ++ob;
   }
   /* Get rid of old table. */
   #ifndef NDEBUG
      (void)memset(
         env->table, 0xff, (env->bitmask + 1) * sizeof *env->table
      );
   #endif
   free(env->table);
   /* Set parameters for new table. */
   env->table= nt;
   env->bitmask= nm;
   env->allocatable_entries= ae;
}


static void free_environment(r4g *xc, void *context_environment) {
   struct r4g_internal *fc= (struct r4g_internal *)xc;
   struct r4g_env *env;
   assert(fc);
   env= fc->env;
   assert(env);
   fc->env= 0; /* Detach from context. */
   #ifdef NDEBUG
      (void)context_environment;
   #else
      /* Only a single environment can exist at any specific point in time. */
      assert(env == context_environment);
   #endif
   if (env->table) {
      #ifndef NDEBUG
         /* Ensure crash if someone tries to dereference those pointers. */
         (void)memset(
            env->table, 0xff, (env->bitmask + 1) * sizeof *env->table
         );
      #endif
      free(env->table);
      env->table= 0; /* Now it is "clear" :-) */
   }
   #ifndef NDEBUG
      /* Ensure maximum damage if someone still tries to access it. */
      env->bitmask= (uint_least32_t)INT32_C(-1);
   #endif
   free(env);
}


static void **lookup(r4g *xc, uint_least32_t const *key) {
   struct r4g_internal *fc= (struct r4g_internal *)xc;
   struct r4g_env *env;
   assert(fc);
   if (!(env= fc->env)) {
      /* No environment yet. Create it. */
      env= r4ga_malloc(xc, sizeof *env);
      env->table= 0;
      #ifndef NDEBUG
         env->bitmask= 0;
      #endif
      r4g_add(xc, free_environment, fc->env= env);
      #ifdef NDEBUG
         /* Needs to be a power of 2. Note that only half of the entries
          * will actually be available before the table needs to grow. */
         #define INITIAL_TABLE_ENTRIES 32
      #else
         /* Will grow more often - better test case for debugging. */
         #define INITIAL_TABLE_ENTRIES 1
      #endif
      {
         size_t table_bytes;
         env->table= r4ga_malloc(
            xc, table_bytes= INITIAL_TABLE_ENTRIES * sizeof *env->table
         );
         /*
          * I *refuse* to use calloc(): It needs to perform a *multiplication*
          * internally. Yuck!
          */
         (void)memset(env->table, 0, table_bytes);
      }
      env->bitmask= INITIAL_TABLE_ENTRIES - 1;
      env->allocatable_entries= INITIAL_TABLE_ENTRIES / 2;
   }
   restart:
   {
      uint_fast32_t h= *key, bitmask= env->bitmask, i;
      struct bucket *t= env->table, *b;
      for (
            i= h & bitmask
         ;  (b= env->table + i)->key != key
         ;  i= (i + 1) & bitmask
      ) {
         if (!b->key) {
            /* End of collision chain. Not found. */
            if (env->allocatable_entries-- == 0) {
               grow_table(xc, env);
               goto restart;
            }
            /* Add new entry at current free slot. */
            b->key= key;
            assert(b->value == 0); /* Array was initially zeroed out. */
            break;
         }
      }
      /* Found or newly created. */
      return &b->value;
   }
}


/**
 * Returns a context environment item set by r4g_assoc() or NULL if no such
 * item exists. The context environment will be created as a resource unless
 * it already exists.
 */
extern void *r4g_lookup(r4g *xc, uint_least32_t const *rand_key) {
   return *lookup(xc, rand_key);
}


/**
 * Stores a context environment item. The item is represented by
 * related_data, and is allowed to be NULL. Only the pointer to the data
 * is stored; the caller has to ensure that data remains available it if need
 * to be dereferenced later.
 *
 * The address of rand_key together with its value represents the key for the
 * lookup. Like related_data, only the pointer is stored in the context
 * environment, and it is the caller's duty to ensure the key remains
 * accessible as long as the context environment exists.
 * The context environment will be created by this function as a resource
 * unless it already exists.
 *
 * The value stored at the address of the key should be a random number.
 * A simple way is to initialize a static constant with a random number
 * and use the constant's address as the key pointer. Like this:
 *
 * static uint_least32_t const mykey= UINT32_C(0x06d5fb3e);
 *
 * Using a good random number generator for generating the values helps
 * minimize collisions on lookup, speeding it up.
 */
extern void r4g_assoc(
   r4g *xc, uint_least32_t const *rand_key, void *related_data
) {
   *lookup(xc, rand_key)= related_data;
}
