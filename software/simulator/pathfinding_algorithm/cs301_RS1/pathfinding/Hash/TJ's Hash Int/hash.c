
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

#define POS_X 4
#define POS_Y 3

#define KEY_1 1234
#define KEY_2 4321
#define KEY_3 987654

void
test_hash_set() {
  hash_t *hash = hash_new();
  assert(0 == hash_size(hash));

  hash_set(hash, KEY_1, "tobi");
  hash_set(hash, KEY_2, "ferret");
  assert(2 == hash_size(hash));

  assert(0 == strcmp("tobi", hash_get(hash, KEY_1)));
  assert(0 == strcmp("ferret", hash_get(hash, KEY_2)));

  hash_free(hash);
}

void
test_hash_get() {
  hash_t *hash = hash_new();
  hash_set(hash, KEY_1, "bar");
  assert(0 == strcmp("bar", hash_get(hash, KEY_1)));
  assert(NULL == hash_get(hash, KEY_2));

  hash_free(hash);
}

void
test_hash_has() {
  hash_t *hash = hash_new();
  hash_set(hash, KEY_1, "bar");
  assert(1 == hash_has(hash, KEY_1));
  assert(0 == hash_has(hash, KEY_2));
}

void
test_hash_size() {
  hash_t *hash = hash_new();
  assert(0 == hash_size(hash));
  hash_set(hash, KEY_1, "bar");
  assert(1 == hash_size(hash));
  hash_set(hash, KEY_2, "baz");
  assert(2 == hash_size(hash));
}

void
test_hash_del() {
  hash_t *hash = hash_new();
  hash_set(hash, KEY_1, "bar");
  assert(1 == hash_has(hash, KEY_1));
  assert(0 == hash_has(hash, KEY_2));
  hash_del(hash, KEY_1);
  hash_del(hash, KEY_2);
  assert(0 == hash_has(hash, KEY_1));
}

void
test_hash_clear() {
  hash_t *hash = hash_new();
  hash_set(hash, KEY_1, "bar");
  hash_set(hash, KEY_2, "baz");
  hash_set(hash, KEY_3, "jaz");
  assert(3 == hash_size(hash));
  hash_clear(hash);
  assert(0 == hash_size(hash));
}

void
test_hash_each() {
  hash_t *hash = hash_new();
  hash_set(hash, KEY_1, "tj");
  hash_set(hash, KEY_2, "25");

  int keys[2];
  void *vals[2];
  int n = 0;

  hash_each(hash, {
    keys[n] = key;
    vals[n] = val;
    n++;
  });

  assert((KEY_2 == keys[0]) || (KEY_1 == keys[0]));
  assert((KEY_2 == keys[1]) || (KEY_1 == keys[1]));
  assert(0 == strcmp("25", vals[0]) || 0 == strcmp("tj", vals[0]));
  assert(0 == strcmp("25", vals[1]) || 0 == strcmp("tj", vals[1]));
}

void
test_hash_each_key() {
  hash_t *hash = hash_new();
  hash_set(hash, KEY_1, "tj");
  hash_set(hash, KEY_2, "25");

  int keys[2];
  int n = 0;

  hash_each_key(hash, {
    keys[n++] = key;
  });

  assert((KEY_2 == keys[0]) || (KEY_1 == keys[0]));
  assert((KEY_2 == keys[1]) || (KEY_1 == keys[1]));
}

void
test_hash_each_val() {
  hash_t *hash = hash_new();
  hash_set(hash, KEY_1, "tj");
  hash_set(hash, KEY_2, "25");

  void *vals[2];
  int n = 0;

  hash_each_val(hash, {
    vals[n++] = val;
  });

  assert(0 == strcmp("25", vals[0]) || 0 == strcmp("tj", vals[0]));
  assert(0 == strcmp("25", vals[1]) || 0 == strcmp("tj", vals[1]));
}

int
main(){

  test_hash_set();
  test_hash_get();
  test_hash_has();
  test_hash_del();
  test_hash_size();
  test_hash_clear();
  test_hash_each();
  test_hash_each_key();
  test_hash_each_val();

  hash_t *hash = hash_new();

  char* a = "gog";

  hash_set(hash, 1, "tobi");
  hash_set(hash, 2, "ferret");
  hash_set(hash, 3, a);

  hash_each(hash, {
    printf("%d: %s\n", key, (int ) val);
  });

  hash_free(hash);
  return 0;
}

#endif