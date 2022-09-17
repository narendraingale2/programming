#ifndef _RBTREE_H
#define _RBTREE_H
#include<stdio.h>

#define SUCCESS                1
#define RBTREE_DATA_NOT_FOUND  2
#define TRUE                   1
#define FALSE                  0

typedef struct rb_node rbnode_t;
typedef struct rb_tree rbtree_t;
typedef enum color color_t;
typedef int data_t;
typedef int status_t;

enum color
{
    RED,
    BLACK
};

struct rb_node{

    int data;
    struct rbtree_node* left;
    struct rbtree_node* right;
    struct rbree_node* parent;
    enum color color;
};

struct rb_tree{
    struct rbtree_node* p_root;
    unsigned long long nr_nodes;  
};

rbtree_t* create_rbtree(void);
status_t rbtree_insert(rbtree_t* p_rbtree, data_t data);
status_t rbtree_delete(rbnode_t* p_rbtee, data_t data);
status_t rbtree_find(rbnode_t* p_rbtree, data_t data);
unsigned int rbtree_get_hight(rbnode_t* p_rbtree);
status_t destroy_rbtree(rbtree_t** p_rbtree);

void preorder_walk(rbtree_t* p_rbtree);
void inorder_walk(rbtree_t* p_rbtree);
void postorder_walk(rbtree_t* p_rbtree);


#endif