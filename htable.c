/**
 * htable.c
 * @author Patrick Skinner, Cassidy Mowat, Luke Biggs
 *
 * This program represents a hash table abstract data type.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"
#include "container.h"

#define HASH_SIZE 2

/* Setup a struct for the hash table */
struct htablerec {
	char **keys;
	container *cont;
	int *frequencies;
	int num_keys;
	int capacity;
	container_t type;
};

/**
 * Converts a word to an integer to be stored in the hash table.
 *
 * @param word the word to be converted to an int.
 *
 * @return an unsigned int to be used as an index.
 */
static unsigned int htable_word_to_int(char *word) {
	unsigned int result = 0;
	while (*word != '\0') {
		result = (*word++ + 31 * result);
	}
	return result;
}

static unsigned int htable_step(htable h, unsigned int i_key) {
	return 1 + (i_key % (h->capacity - 1));
}

/**
 * The method used to create a new hash table.
 * It sets the capacity and type of container to be used.
 *
 * @return result a new hash table.
 */
htable htable_new(int capacity, container_t type){
	int i;
	htable hash = emalloc(sizeof *hash);
	hash->capacity = capacity;
	hash->num_keys = 0;
	hash->keys = emalloc(capacity * sizeof hash->keys[0]);
	hash->frequencies = emalloc(capacity * sizeof hash->frequencies[0]);
	hash->cont = emalloc(capacity * sizeof hash->cont[0]);
	hash->type = type;

	for (i = 0; i < capacity; i++){
		hash->keys[i] = NULL;
		hash->frequencies[i] = 0;
		hash->cont[i] = NULL;
	}
	return hash;
}

/**
 * The method used to add strings to a hash table.
 * The first two characters of the string are used to hash.
 *
 * @param h the hash table to add into.
 * @param str the string to be added.
 */
int htable_insert(htable h, char *str){

	char str2[HASH_SIZE];
	int i;
	int collision = 0;
	int step;

	strncpy(str2, str, HASH_SIZE);
	i = htable_word_to_int(str2) % h->capacity;
	step = htable_step(h, i);

	while (collision < h->capacity){
		if (h->keys[i] == NULL){
			h->keys[i] = emalloc(HASH_SIZE * sizeof *str);
			strcpy(h->keys[i], str2);
			h->frequencies[i] = 1;
			h->cont[i] = container_new(h->type);
			container_add(h->cont[i], str);
			h->num_keys++;
			return 1;
		}
		if (0 == strcmp(h->keys[i], str2)){
			h->frequencies[i]++;
			container_add(h->cont[i], str);
			return h->frequencies[i];
		}
		i += step;
		collision++;
		i = i % h->capacity;
	}
	return 0;
}

/**
 * The method uses a double hashing function to determine
 * whether a given value exists in the hashtable.
 *
 * @param h the hash table to search into.
 * @param str the string to be searched for.
 */
int htable_search(htable h, char *str){

	int collisions = 0;
	char str2[HASH_SIZE];
	int i;
	int step;

	strncpy(str2, str, HASH_SIZE);
	i = htable_word_to_int(str2) % h->capacity;
	step  = htable_step(h, i);

	while (h->keys[i] != NULL && collisions < h->capacity){
		if (strcmp(h->keys[i], str2) == 0){
			return container_search(h->cont[i], str);
		}
		collisions++;
		i += step;
	}
	return 0;
}

/**
 * The method used to print the values of a hash table.
 *
 * @param h the hash table to be printed.
 */
void htable_print(htable h){
	int i;
	for (i = 0; i < h->capacity; i++){
		if (0 != h->frequencies[i]){
			container_print(h->cont[i]);
			printf("\n");
		}
	}
}

/**
 * The method used to free the memory from a hash table.
 *
 * @param h the hash table to free.
 */
void htable_free(htable h){
	int i;
	for (i = 0; i < h->capacity; i++){
		free(h->keys[i]);
	}
	free(h->cont);
	free(h->keys);
	free(h->frequencies);
	free(h);
}
