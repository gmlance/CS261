 /*
 * In this file, you will write the structures and functions needed to
 * implement a hash table.  Feel free to implement any helper functions
 * you need in this file to implement a hash table.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */

#include <stdlib.h>
#include <stdint.h>

#include "dynarray.h"
#include "list.h"
#include "hash_table.h"


/*
 * This is the structure that represents a hash table.  You must define
 * this struct to contain the data needed to implement a hash table.
 */
struct ht {
  struct list** hash;
  int size;
  int capacity;
};

struct hash_data {
  void* key;
  void* value;
};

#define CAPACITY_INIT 10

/*
 * This function should allocate and initialize an empty hash table and
 * return a pointer to it.
 */
struct ht* ht_create(){
    //struct list* list = malloc(sizeof(struct list));
    struct ht* ht = malloc(sizeof(struct ht));
    ht -> size = 0;
    ht -> capacity = CAPACITY_INIT;
    ht -> hash = malloc(sizeof(struct list*) * ht -> capacity);
    for (int i = 0; i < ht -> capacity; i++) {
      ht -> hash[i] = list_create();
    }
  
    return ht;
}

/*
 * This function should free the memory allocated to a given hash table.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the hash table.  That is the responsibility of the caller.
 *
 * Params:
 *   ht - the hash table to be destroyed.  May not be NULL.
 */
void ht_free(struct ht* ht){
    for (int i = 0; i < ht -> capacity; i++) {
      list_free(ht->hash[i]);
    }
    free(ht -> hash);
    free(ht);
    return;
}

/*
 * This function should return 1 if the specified hash table is empty and
 * 0 otherwise.
 *
 * Params:
 *   ht - the hash table whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if ht is empty and 0 otherwise.
 */
int ht_isempty(struct ht* ht){
  return ht->size <= 0;
}


/*
 * This function returns the size of a given hash table (i.e. the number of
 * elements stored in it, not the capacity).
 */
int ht_size(struct ht* ht){
    return ht->size;
}


/*
 * This function takes a key, maps it to an integer index value in the hash table,
 * and returns it. The hash algorithm is totally up to you. Make sure to consider
 * Determinism, Uniformity, and Speed when design the hash algorithm
 *
 * Params:
 *   ht - the hash table into which to store the element.  May not be NULL.
 *   key - the key of the element to be stored
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */
int ht_hash_func(struct ht* ht, void* key, int (*convert)(void*)){
    int conv = convert(key);
    
    return (conv * 13) % ht -> capacity;
}


/*
 * This function should insert a given element into a hash table with a
 * specified key.  Note that you cannot have two same keys in one hash table. 
 * This function is passed a function pointer that is used to convert the key (void*) 
 * to a unique hashcode (int). 
 * Resolution of collisions is requried, use either chaining or open addressing.
 * If using chaining, double the number of buckets when the load factor is >= 4
 * If using open addressing, double the array capacity when the load factor is >= 0.75
 * load factor = (number of elements) / (hash table capacity)
 *
 * Params:
 *   ht - the hash table into which to insert an element.  May not be NULL.
 *   key - the key of the element
 *   value - the value to be inserted into ht.
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */

void ht_insert(struct ht* ht, void* key, void* value, int (*convert)(void*)){
    void* lookup = ht_lookup(ht, key, convert);
    if (lookup != NULL) {
      return;
    }
  
    ht->size++;
    if(ht->size/ht-> capacity >= 4){
      int oldCap = ht->capacity;
      ht -> capacity *= 2;

      struct list **ht_new = malloc(sizeof(struct list*) * ht -> capacity);

      //starting off new lists
      for (int i = 0; i < ht->capacity; i++) {
        ht_new[i] = list_create();
      }

      //go through old and freshly insert all old data into new
      for (int i = 0; i < oldCap; i++) {
        //traverse each hash table to grab values
        int curr = 0;
        struct hash_data* data = NULL;
        while ((data = list_get(ht->hash[i], curr)) != NULL) {
          int hash_value = ht_hash_func(ht, data->key, convert);
          list_insert(ht_new[hash_value], data);
          curr++;
        }
      }

      ht->hash = ht_new;
    }

    //insert the new one
    struct hash_data* data = malloc(sizeof(struct hash_data));
    data->key = key;
    data->value = value;
    int hash_value = ht_hash_func(ht, data->key, convert);
    list_insert(ht->hash[hash_value], data);
}


/*
 * This function should search for a given element in a hash table with a
 * specified key provided.   
 * This function is passed a function pointer that is used to convert the key (void*) 
 * to a unique hashcode (int). 
 * If the key is found, return the corresponding value (void*) of the element,
 * otherwise, return NULL
 *
 * Params:
 *   ht - the hash table into which to loop up for an element.  May not be NULL.
 *   key - the key of the element to search for
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */
void* ht_lookup(struct ht* ht, void* key, int (*convert)(void*)){
    int hash_value = ht_hash_func(ht, key, convert);
    int curr = 0;
    struct hash_data* data = NULL;
    while ((data = list_get(ht->hash[hash_value], curr)) != NULL) {
      if (convert(data->key) == convert(key)) {
        return data->value;
      }
      curr++;
    }
    return NULL;
}

//helper function
void* ht_lookup_data(struct ht* ht, void* key, int (*convert)(void*)){
    int hash_value = ht_hash_func(ht, key, convert);
    int curr = 0;
    struct hash_data* data = NULL;
    while ((data = list_get(ht->hash[hash_value], curr)) != NULL) {
      if (convert(data->key) == convert(key)) {
        return data;
      }
      curr++;
    }
    return NULL;
}

int hashdata_compare(void* data1, void* data2) {
  return data1 != data2;
}


/*
 * This function should remove a given element in a hash table with a
 * specified key provided.   
 * This function is passed a function pointer that is used to convert the key (void*) 
 * to a unique hashcode (int). 
 * If the key is found, remove the element and return, otherwise, do nothing and return 
 *
 * Params:
 *   ht - the hash table into which to remove an element.  May not be NULL.
 *   key - the key of the element to remove
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */
void ht_remove(struct ht* ht, void* key, int (*convert)(void*)){
    ht->size--;

    int hash_value = ht_hash_func(ht, key, convert);
    void* found = ht_lookup_data(ht, key, convert);
    list_remove(ht->hash[hash_value], found, hashdata_compare);
    free(found);
} 
