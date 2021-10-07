
# Hash

  C hash implementation based on khash.

  This is a modified version of TJ's C hash implementation to use int keys instead of a string.

## Example

```c
hash_t *hash = hash_new();
hash_set(hash, "name", "tobi");
hash_set(hash, "species", "ferret");
hash_set(hash, "age", "2");

hash_each(hash, {
  printf("%d: %s\n", key, (char*) val);
});

hash_free(hash);
```

yields:

```
species: ferret
age: 2
name: tobi
```

## API

### hash_t

  The hash type.

### hash_t *hash_new()

  Allocate and initialize a new hash.

### hash_free(hash_t *self)

  Free the hash, you must free values appropriately.

### unsigned int hash_size(hash_t *self)

  Return the number of values in the hash table.

### void hash_clear(hash_t *self)

  Remove all values from the hash.

### void hash_set(hash_t *self, intkey, void *val);

  Set `key` to `val`.

### void *hash_get(hash_t *self, intkey);

  Get value for `key` or __NULL__.  

### int hash_has(hash_t *self, intkey);

  Check if the hash contains `key`.

### void hash_del(hash_t *self, intkey);

  Remove `key` from the hash.

### hash_each(hash_t *self, block)

  A macro for iterating key/value pairs.

```c
hash_each(users, {
  printf("%d: %s\n", key, (char*) val);
})
```

### hash_each_key(hash_t *self, block)

  A macro for iterating keys only.

```c
hash_each_key(users, {
  printf("%d\n", key);
})
```

### hash_each_val(hash_t *self, block)

  A macro for iterating values only.

```c
hash_each_val(users, {
  printf("%d\n", (char*) val);
})
```

