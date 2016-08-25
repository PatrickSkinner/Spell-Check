/**
 * rbt.h
 * @author Patrick Skinner, Cassidy Mowat, Luke Biggs
 */

#ifndef RBT_H_


typedef enum { RED, BLACK } rbt_colour;
typedef struct rbt_node *rbt;


extern void rbt_free(rbt r);
extern rbt rbt_insert(rbt r, char *str);
extern int rbt_search(rbt r, char *key);
extern rbt rbt_new();
extern rbt rbt_fix_root(rbt r);
extern void rbt_print(rbt r);


#endif