/**
 * container.c
 * @author Patrick Skinner, Cassidy Mowat, Luke Biggs
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include "container.h"
#include "mylib.h"
#include "flexarray.h"
#include "rbt.h"

/* Setup a struct for the container */
struct containerrec {
	container_t type;
	void *contents;
};

/**
 * Creates a new container and set the type,
 * either a flexarray or red black tree.
 *
 * @param type desired for the container
 *
 * @return c the freshly created container.
 */
container container_new(container_t type){
	container c = emalloc(sizeof *c);
	c->type = type;
	if (c->type == RED_BLACK_TREE) {
		c->contents = rbt_new();
	} else {
		c->contents = flexarray_new();
	}
	return c;
}

/**
 * Adds a word to the container using the appropriate method,
 * depending on whether a red black tree or flexarray has
 * been chosen as the container type.
 *
 * @param c the container to be added to.
 * @param word to be added.
 */
void container_add(container c, char *word) {
	if (c->type == RED_BLACK_TREE) {
		c->contents = rbt_insert(c->contents, word);
		c->contents = rbt_fix_root(c->contents);
	} else {
		flexarray_append(c->contents, word);
	}
}

/**
 * Prints the contents of a container, calling the appropriate red
 * black tree, or flexarray print method.
 *
 * @param c the container to be printed.
 */
void container_print(container c) {
	if (c->type == RED_BLACK_TREE){
		rbt_print(c->contents);
	} else {
		flexarray_print(c->contents);
	}
}

/**
 * Searches the contents of a container for a given value,
 * returning the result of either the red black tree's search
 * method or flex array's is present method.
 *
 * @param c the container to be searched.
 * @param word to be searched for.
 */
int container_search(container c, char *word){
	if (c->type == RED_BLACK_TREE) {
		return rbt_search(c->contents, word);
	} else {
		return is_present(c->contents, word);
	}
}

