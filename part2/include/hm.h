#include "mythread.h"
#include "list.h"
#define SZ 4096

struct hashmap_element_s {
  char *key;
  void *data;
};

struct hashmap_s {
  struct list* table[SZ];
  struct lock* lk[SZ];
};


int hashmap_create(struct hashmap_s *const out_hashmap);   // Initialize a hashmap
int hashmap_put(struct hashmap_s *const hashmap, const char* key, void* data);   // Set value of the key as data in hashmap. You can use any method to resolve conflicts. Also write your own hashing function
void* hashmap_get(struct hashmap_s *const hashmap, const char* key);    // Fetch value of a key from hashmap
void hashmap_iterator(struct hashmap_s* const hashmap, 
                        int (*f)(struct hashmap_element_s *const));  // Execute argument function on each key-value pair in hashmap

int acquire_bucket(struct hashmap_s *const hashmap, const char* key);   // Acquire lock on a hashmap slot
int release_bucket(struct hashmap_s *const hashmap, const char* key);   // Release acquired lock
