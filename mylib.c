/**
 * mylib.c
 * @author Patrick Skinner, Cassidy Mowat, Luke Biggs
 */


#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "mylib.h"

/**
 * Method used to allocate memory with included
 * error checking code.
 *
 * @param s the amount of memory needed
 */
void *emalloc(size_t s){
	void *result = malloc(s);
	if (result == NULL){
		fprintf(stderr, "memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

/**
 * Method used to reallocate memory with included
 * error checking code.
 *
 * @param p a pointer that needs to be reallocated.
 * @param s the amount of memory needed.
 */
void *erealloc(void *p, size_t s){
	void *result = realloc(p, s);
	if (NULL == result){
		fprintf(stderr, "memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

/**
 * Method used to retrive words from a file,
 *
 * @param s pointer storing input.
 * @param limit of the word size.
 * @param stream to read from. 
 */
int getword(char *s, int limit, FILE *stream) {
	int c;
	char *w = s;
	assert(limit > 0 && s != NULL && stream != NULL);
	/* skip to the start of the word */
	while (!isalnum(c = getc(stream)) && EOF != c)
		;
	if (EOF == c) {
		return EOF;
	}
	else if (--limit > 0) { /* reduce limit by 1 to allow for the \0 */
		*w++ = tolower(c);
	}
	while (--limit > 0) {
		if (isalnum(c = getc(stream))) {
			*w++ = tolower(c);
		}
		else if ('\'' == c) {
			limit++;
		}
		else {
			break;
		}
	}
	*w = '\0';
	return w - s;
}