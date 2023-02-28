#include "../include/mythread.h"
#include "../include/list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SZ 4096
#define pp 53

struct hashmap_element_s {
  char *key;
  void *data;
};

struct tuple {
  const char *key;
  void *data;
};

struct hashmap_s {
  struct list* table[SZ];
  struct lock* lk[SZ];
};

int hash_fun(const char *s) {
  int hashed_val = 0;
  int expo = 1;
  for (int i = 0; i < strlen(s); i++) {
    hashed_val = (hashed_val + (expo * abs((int)(s[i]))) % SZ) % SZ;
    expo = (expo * pp) % SZ;
  }
  return hashed_val;
}


int hashmap_create(struct hashmap_s *const out_hashmap){
  for(int i = 0; i < 4096; i++){
    out_hashmap->table[i] = list_new();
    out_hashmap->lk[i]=lock_new();
  }
  return 0;
}

int hashmap_put(struct hashmap_s *const hashmap, const char* key, void* data){
  int place = hash_fun(key);
  struct listentry *e;
  e = hashmap->table[place]->head;
  while(e != NULL){
    if (strcmp(((struct tuple* )(e->data))->key,key)==0){
      list_rm(hashmap->table[place], e);
      break;
    }
    e = e->next;
  }
  struct hashmap_element_s* list_data = (struct hashmap_element_s*)malloc(sizeof(struct hashmap_element_s));
  char * c2 = (char *)malloc(strlen(key)*sizeof(char));
  strcpy(c2,key);
  list_data->key = c2;
  list_data->data = (void*)data;
  list_add(hashmap->table[place], (void* )(list_data));
  return 0;
}

void* hashmap_get(struct hashmap_s *const hashmap, const char* key){
  int place = hash_fun(key);
  struct listentry *e;
  e = hashmap->table[place]->head;
  while(e != NULL){
    if (strcmp(((struct tuple* )(e->data))->key, key)==0){
      return (void*)(((struct hashmap_element_s* )(e->data))->data);
    }
    e = e->next;
  }
  return NULL;

}    // Fetch value of a key from hashmap

void hashmap_iterator(struct hashmap_s* const hashmap, int (*f)(struct hashmap_element_s *const)){
  for(int i = 0; i < 4096; i++){
    struct listentry *e; 
    e = hashmap->table[i]->head;
    while(e != NULL){
      f(e->data);
      e = e->next;
    }
  }
}
// Execute argument function on each key-value pair in hashmap

int acquire_bucket(struct hashmap_s *const hashmap, const char* key){
  int place = hash_fun(key);
  lock_acquire(hashmap->lk[place]);
  return 0;

}   // Acquire lock on a hashmap slot
int release_bucket(struct hashmap_s *const hashmap, const char* key){
  int place = hash_fun(key);
  lock_release(hashmap->lk[place]);
  return 0;
}   // Release acquired lock