/**
 * container.c
 * @author Patrick Skinner, Cassidy Mowat, Luke Biggs
 *
 * This program represents a flexarray abstract data type.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "flexarray.h"

/* Setup a struct for the flexarray */
struct flexarrayrec {
	int capacity;
	int itemcount;
	char **items;
};

/**
 * The method used to create a new flexarray.
 * It sets the initial capacity and allocates the memory required.
 *
 * @return result a new empty flexarray.
 */
flexarray flexarray_new(){
	flexarray result = emalloc(sizeof *result);
	result->capacity = 2;
	result->itemcount = 0;
	result->items = emalloc (result->capacity * sizeof result->items[0]);
	return result;
}

/**
 * The method used to add items to a flexarray,
 * doubling the capacity if required.
 *
 * @param f the flexarray to add into.
 * @param input the string to be added.
 */
void flexarray_append(flexarray f, char *input){
	if (f->itemcount == f->capacity){
		f->capacity += f->capacity;
		f->items = erealloc(f->items, f->capacity * sizeof f->items[0]);
	}
	f->items[f->itemcount] = emalloc((strlen(input) + 1) * sizeof *input);
	strcpy(f->items[f->itemcount], input);
	f->itemcount++;
}

/**
 * The method used to print the contents of the flexarray.
 *
 * @param f the flexarray to add into.
 */
void flexarray_print(flexarray f){
	int i;
	for (i=0; i < f->itemcount; i++){
		printf("%s ", f->items[i]);
	}
}

/**
 * The method determining if an item is in the flexarray,
 * returning 1 if it is, or 0 if it is not.
 *
 * @param f the flexarray to search.
 * @param input the value to search for.
 */
int is_present(flexarray f, char *input){
	int i;
	for(i = 0; i < f->itemcount; i++){
		if (strcmp (f->items[i], input) == 0){
			return 1;
		}
	}
	return 0;
}

/**
 * The method used to free the memory from a flexarray.
 *
 * @param f the flexarray to free.
 */
void flexarray_free(flexarray f){
	free(f->items);
	free(f);
}
