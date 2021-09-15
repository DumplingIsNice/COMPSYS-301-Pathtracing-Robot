
//
// hash.c
//
// Copyright (c) 2012 TJ Holowaychuk <tj@vision-media.ca>
//

#include "hash.h"
// #define TEST_HASH

/*
 * Set hash `key` to `val`.
 */

inline void
hash_set(hash_t *self, int key, void *val) {
  int ret;
  khiter_t k = kh_put(ptr, self, key, &ret);
  kh_value(self, k) = val;
}

/*
 * Get hash `key`, or NULL.
 */

inline void *
hash_get(hash_t *self, int key) {
  khiter_t k = kh_get(ptr, self, key);
  return k == kh_end(self) ? NULL : kh_value(self, k);
}

/*
 * Check if hash `key` exists.
 */

inline int
hash_has(hash_t *self, int key) {
  khiter_t k = kh_get(ptr, self, key);
  return kh_exist(self, k);
}

/*
 * Remove hash `key`.
 */

void
hash_del(hash_t *self, int key) {
  khiter_t k = kh_get(ptr, self, key);
  kh_del(ptr, self, k);
}

// tests

#ifdef TEST_HASH

#include <stdio.h>
#include <assert.h>
#include <string.h>

int
main(){

  hash_t *hash = hash_new();
  hash_set(hash, 1, "tobi");
  hash_set(hash, 2, "ferret");
  hash_set(hash, 3, "2");

  hash_each(hash, {
  printf("%d: %s\n", key, (int ) val);
  });

  hash_free(hash);
  return 0;
}

#endif