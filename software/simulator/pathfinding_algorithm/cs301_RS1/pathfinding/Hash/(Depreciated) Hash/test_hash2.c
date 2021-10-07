#include <stdio.h>
#include "hash.h"

// This case uses the generated methods.

// instantiate structs and methods
KHASH_MAP_INIT_INT(myBucket, int)   

// Alternatively, the namesake for the khash structs and methods may be used
// as a part of the method calls, removing the need to pass the name into
// the function
int main()
{
    int ret = 0;
    khint_t k;  
    kh_myBucket_t *h = kh_init_myBucket();

    int x = 3;
    int y = 4;
    int key = hash_gen(x, y);

    k = kh_put_myBucket(h, key, &ret);
    kh_val(h, k) = 30;

    key = hash_gen(y, x);
    k = kh_put_myBucket(h, key, &ret);
    kh_val(h, k) = 40;

    printf("%d", kh_val(h, k));
    kh_destroy_myBucket(h); 
}