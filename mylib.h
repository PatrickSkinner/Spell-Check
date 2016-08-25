/**
 * mylib.h
 * @author Patrick Skinner, Cassidy Mowat, Luke Biggs
 */

#ifndef MYLIB_H_
#define MYLIB_H_

#include <stddef.h>

extern int getword(char *s, int limit, FILE *stream);
extern void *emalloc(size_t);
extern void *erealloc(void *, size_t);

#endif