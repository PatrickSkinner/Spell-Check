/**
 * rbt.c
 * @author Patrick Skinner, Cassidy Mowat, Luke Biggs
 *
 * This program represents a red black tree abstract data type.
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rbt.h"
#include "mylib.h"

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

/* method declarations */
static rbt rbt_fix(rbt r);
static rbt left_rotate(rbt r);
static rbt right_rotate(rbt r);

/* Setup a struct for the red black tree */
struct rbt_node {
	char *key;
	rbt_colour colour;
	rbt left;
	rbt right;
};

/**
 * The method used to create a new empty node.
 */
rbt rbt_new(){
	return NULL;
}

/**
 * The method used to insert a value into the red black tree.
 * If the RBT is empty, the correct amount of memory is allocated
 * and the key is inserted. Otherwise, depending on the size of
 * the value, the insert method is recursively called on either the left
 * or right subtree. Before returning the RBT, the fix method is
 * invoked the ensure the tree's structure remains correct.
 *
 * @param r the tree to add too.
 * @param key the value to add.
 *
 * @return the complete red black tree.
 */
rbt rbt_insert(rbt r, char *key){
	int compare;
	if (r == NULL){
		r = emalloc(sizeof *r);
		r->key = emalloc((strlen(key) + 1) * sizeof key[0]);
		strcpy(r->key, key);
		r->left = rbt_new();
		r->right = rbt_new();
		r->colour = RED;
	} else {
		compare = strcmp(r->key, key);
		if (compare < 0){
			r->right = rbt_insert(r->right, key);
		} else {
			r->left = rbt_insert(r->left, key);
		}
	}
	r = rbt_fix(r);
	return r;
}

/**
 * The method used to print the values of a red black tree.
 *
 * @param r the red black tree to be printed.
 */
void rbt_print(rbt r){
	if (r == NULL) return;
	printf("%s ", r->key);
	rbt_print(r->left);
	rbt_print(r->right);
}

/**
 * A method invoked by the fix method, right
 * rotating the tree to fix its structure.
 *
 * @param r the tree to rotate
 */
static rbt right_rotate(rbt r){
 	rbt temp;
	temp = r;
	r = temp->left;
	temp->left = r->right;
	r->right = temp;
	return r;
}

/**
 * A method invoked by the fix method, left
 * rotating the tree to fix its structure.
 *
 * @param r the tree to rotate
 */
static rbt left_rotate(rbt r){
	rbt temp;
	temp = r;
	r = temp->right;
	temp->right = r->left;
	r->left = temp;
	return r;
}

/**
 * A method used to keep the structure of the tree correct
 * when a new item has been inserted. Members of the tree are
 * coloured red or black, and the right and left rotate methods
 * are invoked until structure is correct again.
 *
 * @param r the tree to fix.
 */
static rbt rbt_fix(rbt r){
	if(IS_RED(r->left) && IS_RED(r->left->left)){
		if(IS_RED(r->right)){
			/*Case 1*/
			r->colour = RED;
			r->right->colour = BLACK;
			r->left->colour = BLACK;
		} else {
			/*Case 2*/
			r = right_rotate(r);
			r->colour = BLACK;
			r->right->colour = RED;
		}
	}
	if(IS_RED(r->left) && IS_RED(r->left->right)){
		if(IS_RED(r->right)){
			/*Case 3*/
			r->colour = RED;
			r->right->colour = BLACK;
			r->left->colour = BLACK;
		} else {
			/*Case 4*/
			r->left = left_rotate(r->left);
			r = right_rotate(r);
			r->colour = BLACK;
			r->right->colour= RED;
		}
	}
	if(IS_RED(r->right) && IS_RED(r->right->left)){
		if(IS_RED(r->left)){
			/*Case 5*/
			r->colour = RED;
			r->right->colour = BLACK;
			r->left->colour = BLACK;
		} else {
			/*Case 6*/
			r->right = right_rotate(r->right);
			r = left_rotate(r);
			r->colour = BLACK;
			r->left->colour = RED;
		}
	}
	if(IS_RED(r->right) && IS_RED(r->right->right)){
		if(IS_RED(r->left)){
			/*Case 7*/
			r->colour = RED;
			r->right->colour = BLACK;
			r->left->colour = BLACK;
		} else {
			/*Case 8*/
			r = left_rotate(r);
			r->colour = BLACK;
			r->left->colour = RED;
		}
	}

	return r;
}

/**
 * The method to search for a value in the red black tree.
 * If the key is equal to the value being looked at, 1
 * is returned to indicate success, otherwise
 * the search method is recursively called upon the left or right
 * subtree depending on whether the value is smaller or larger.
 *
 * @param r the tree to search.
 * @param key the value to search for.
 */
int rbt_search(rbt r, char *key){
   int compare;

   if (r == NULL){
      return 0;
   } else if ((compare = strcmp(r->key, key)) == 0){
      return 1;
   } else if (compare < 0){
      return rbt_search(r->right, key);
   } else {
      return rbt_search(r->left, key);
   }
}

/**
 * The method to set the root of a free to black
 *
 * @param r the tree to modify.
 */
rbt rbt_fix_root(rbt r){
	r->colour = BLACK;
	return r;
}

/**
 * The method used to free the memory from a red black tree.
 *
 * @param r the red black tree to free.
 */
void rbt_free(rbt r) {
	rbt_free(r->left);
	rbt_free(r->right);
	free(r->key);
	free(r);
}
