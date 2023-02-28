
#include <stdio.h>
#include "hm.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include "mythread.h"

struct hashmap_s hashmap;

int printer(struct hashmap_element_s *const e) {
    int* count = (int*) e->data;
    printf("key %s, count %d\n", e->key, *count);
    return 0;
}

int main(int argc, char** argv) {
    hashmap_create(&hashmap);
    printf("Testing hashmap!\n");
    printf("Iterate empty hashmap!\n");
    hashmap_iterator(&hashmap, printer);
    printf("Done iterate empty hashmap!\n");

    char* key1 = "hello\0";
    int* c1 = (int*) malloc(sizeof(int));
    *c1 = 23;
    hashmap_put(&hashmap, key1, c1);
    hashmap_iterator(&hashmap, printer);

    char* key = "world\0";
    int* c = (int*) malloc(sizeof(int));
    *c = 24;
    hashmap_put(&hashmap, key, c);

    char* key2 = "hello\0";
    int* c2 = (int*) malloc(sizeof(int));
    *c2 = 2;
    hashmap_put(&hashmap, key2, c2);
    hashmap_iterator(&hashmap, printer);
    printf("Testing hashmap done!\n\n");

    return 0;
}