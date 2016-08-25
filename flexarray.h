/**
 * flexarray.h
 * @author Patrick Skinner, Cassidy Mowat, Luke Biggs
 */

#ifndef FLEXARRAY_H_
#define FLEXARRAY_H_

typedef struct flexarrayrec *flexarray;
   
extern flexarray flexarray_new();
extern void flexarray_append(flexarray f, char *input);
extern void flexarray_print(flexarray f);
extern int is_present(flexarray f, char *input);
extern void flexarray_free(flexarray f);

#endif