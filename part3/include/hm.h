/**
 * @file hm.h
 * @brief Implements a hash map data structure using a list for collision resolution and locks for synchronization
*/

#ifndef MYHASHMAP_H
#define MYHASHMAP_H

#include "mythread.h"
#include "list.h"

/**
 * @struct hashmap_element_s
 * @brief A structure to represent a element of the hashmap
*/
struct hashmap_element_s {
  char *key; /**< A pointer to represent the string */
  void *data; /**< A pointer to represent data in the hashmap. */
};

/**
 * @struct hashmap_s
 * @brief A structure to represent a hash map
*/
struct hashmap_s {
struct list* table[4096];/**< An array of pointers to linked lists for storing key-value pairs. */ 
struct lock* lk[4096];/**< An array of locks for synchronization of access to each slot in the hash map. */
};

/**
 * @brief A function to calculate the hash value for a given key
 * @param s A string representing the key
 * @return The calculated hash value
*/
int hash_fun(const char *s);

/**
 * @brief A function to create a hash map
 * @param out_hashmap A pointer to the hash map to be created
 * @return 0 if successful, or an error code if an error occurred.
*/
int hashmap_create(struct hashmap_s *const out_hashmap);

/**
 * @brief A function to add a key-value pair to the hash map
 * @param hashmap A pointer to the hash map to add the key-value pair to
 * @param key A string representing the key of the key-value pair to be added
 * @param data A pointer to the data of the key-value pair to be added
 * @return 0 if successful, or an error code if an error occurred.
*/
int hashmap_put(struct hashmap_s *const hashmap, const char* key, void* data);

/**
 * @brief A function to get the data of a key-value pair from the hash map
 * @param hashmap A pointer to the hash map to get the data from
 * @param key A string representing the key of the key-value pair to get the data of
 * @return A pointer to the data of the key-value pair, or NULL if the key is not found
*/
void* hashmap_get(struct hashmap_s *const hashmap, const char* key);

/**
 * @brief A function to iterate over all key-value pairs in the hash map and execute a given function on each pair
 * @param hashmap A pointer to the hash map to iterate over
 * @param f A function to execute on each key-value pair
*/
void hashmap_iterator(struct hashmap_s* const hashmap, int (*f)(struct hashmap_element_s *const));

/**
 * @brief A function to acquire a lock on a slot in the hash map
 * @param hashmap A pointer to the hash map to acquire the lock on
 * @param key A string representing the key of the slot to acquire the lock on
 * @return 0 if successful, or an error code if an error occurred.
 * \hidecallergraph
 * \hidecallgraph
*/
int acquire_bucket(struct hashmap_s *const hashmap, const char* key);

/**
 * @brief A function to release a lock on a slot in the hash map
 * @param hashmap A pointer to the hash map to release the lock on
 * @param key A string representing the key of the slot to release the lock on
 * @return 0 if successful, or an error code if an error occurred.
*/
int release_bucket(struct hashmap_s *const hashmap, const char* key);
#endif