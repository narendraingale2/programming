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
    enum color color;

    struct rb_node* left;
    struct rb_node* right;
    struct rb_node* parent;
};

struct rb_tree{
    struct rb_node* p_root_node;
    struct rb_node* p_nil;
    unsigned long long nr_nodes;  
};

rbtree_t* create_rbtree(void);
status_t rbtree_insert(rbtree_t* p_rbtree, data_t data);
status_t rbtree_delete(rbtree_t* p_rbtee, data_t data);
status_t rbtree_find(rbtree_t* p_rbtree, data_t data);
unsigned int rbtree_get_hight(rbnode_t* p_rbtree);
status_t destroy_rbtree(rbtree_t** pp_rbtree);

void preorder_walk(rbtree_t* p_rbtree);
void inorder_walk(rbtree_t* p_rbtree);
void postorder_walk(rbtree_t* p_rbtree);

status_t get_rb_max(rbtree_t* p_rbtree, int* p_max);
status_t get_rb_min(rbtree_t* p_rbtree, int* p_min);

status_t get_rb_inorder_successor(rbtree_t* p_rbtree, data_t search_data);
status_t get_rb_inorder_predecessor(rbtree_t* p_rbtree, data_t search_data);

/* Auxillary routines */
rbnode_t* search_rb_node(rbtree_t* p_rbtree, data_t search_data);
void rb_insert_fixup(rbtree_t* p_rbtree, rbnode_t* z);
void rb_remove_fixup(rbtree_t* p_rbtree, rbnode_t* z);
void rb_transplant(rbtree_t* p_rbtree, rbnode_t* u, rbnode_t* v);

void left_rotate(rbtree_t* p_rbtree, rbnode_t* x);
void right_roatate(rbtree_t* p_rbtree, rbnode_t* x);

unsigned int get_height_level(rbtree_t* p_rbtree, rbnode_t* p_node);
void preorder_node_level_walk(rbnode_t* p_rbnode, rbnode_t* nil);
void inorder_node_level_walk(rbnode_t* p_rbnode, rbnode_t* nil);
void postorder_node_level_walk(rbnode_t* p_rbnode, rbnode_t* nil);

void destroy_node_level(rbnode_t* p_root_node, rbnode_t* nil);

rbnode_t* get_rb_max_node(rbtree_t* p_rb_tree);
rbnode_t* get_rb_min_node(rbtree_t* p_rb_tree, rbnode_t* p_root_node);

rbnode_t* get_rbnode(data_t new_data, rbnode_t* nil);
void* xcalloc(size_t nr_elements, size_t size_per_element);

#endif