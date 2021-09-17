#include <stdio.h>
#include "hash.h"

// This case uses the base methods as defined in khash.h

// instantiate structs and methods
KHASH_MAP_INIT_INT(m32, int)     

// kh_end(h) is the end iterator, often indicates absent hash values.
# define HASH_ABSENT(h) kh_end(h)

int main() {
    // ret is used to capture returned value (ie. 0, 1, -1).
    // is_missing is a flag
    int ret, is_missing, key;
    int value = 0;

    khint_t k;                          // iterator variable, used to introspect into hashed values
    khash_t(m32) *h = kh_init(m32);     // allocate a hash table

    // insert a value into a hashmap bucket
    key = 5;
    k = kh_put(m32, h, key, &ret);        // insert a key to the hash table
    // if (!ret) kh_del(m32, h, k);
    kh_value(h, k) = 10;                // set the value

    // fetching a value from a hashmap bucket
    key = 10;
    k = kh_get(m32, h, key);             // query the hash table
    is_missing = (k == kh_end(h));      // test if the key is present

    if (!is_missing) 
    {
        k = kh_get(m32, h, key);
        value = kh_value(h, k);
        printf("Value is: %d \n", value);
    } else {
        printf("No entry found with key: %d\n", key);
    }

    key = 4;
    kh_value(h, kh_put(m32, h, key, &ret)) = 20;
    key = 6;
    kh_value(h, kh_put(m32, h, key, &ret)) = 12;

    // removing a key-value pair (you need to get the k iterator first)
    key = 4;
    k = kh_get(m32, h, key);
    kh_del(m32, h, k);                  // remove a key-value pair

    // Looping through a hashmap table
    printf("Values in the hash table are:");
    for (k = kh_begin(h); k != kh_end(h); ++k) // traverse
    {
        if (kh_exist(h, k))             // test if a bucket contains data
        {
             printf(" %d", kh_value(h, k));
        }                 
    }  
   
    kh_destroy(m32, h);                 // deallocate the hash table
    return 0;
}