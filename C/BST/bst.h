#ifndef _BST_H
#define _BST_H
#include<stdio.h>

typedef struct bst_node bst_node_t;
typedef struct bst bst_t;
typedef int data_t;
typedef int status_t;

#define TRUE  1
#define FALSE 2

#define SUCCESS             1
#define TREE_EMPTY          2      
#define TREE_DATA_NOT_FOUND 3
#define TREE_NO_SUCCESSOR   4
#define TREE_NO_PREDECESSOR 5

enum color
{
    WHITE=0,
    GREY,
    BLACK
};

struct bst_node
{
    int data;
    struct bst_node* left;
    struct bst_node* right;
    struct bst_node* parent; 
    enum color c;
};

struct bst
{
    unsigned long int nr_nodes;
    struct bst_node* p_root_node;
};

/* Basic tree interface routines */
bst_t* create_bst(void);
status_t bst_insert(bst_t* p_bst, data_t new_element);
status_t bst_remove(bst_t* p_bst, data_t r_data);
status_t bst_search(bst_t* p_bst, data_t searh_data);
status_t bst_is_empty(bst_t* p_bst);
data_t bst_max(bst_t* p_bst);
data_t bst_min(bst_t* p_bst);
void bst_reset(bst_t* p_bst);
unsigned long long int bst_get_nr_elements(bst_t* p_bst);
status_t destroy_bst(bst_t** p_bst);

/* in/pre/post order walks */
void preorder(bst_t* p_bst);
void postorder(bst_t* p_bst);
void inorder(bst_t* p_bst);

/* in/pre/post order walks */
void preorder_r(bst_t* p_bst);
void postorder_r(bst_t* p_bst);
void inorder_r(bst_t* p_bst);

/* in/pre/post order predecessor */
data_t bst_inorder_predecessor(bst_t* p_bst, data_t ext_data, int* p_succ_data);
data_t bst_postorder_predecessor(bst_t* p_bst, data_t ext_data, int* p_succ_data);
data_t bst_preorder_predecessor(bst_t* p_bst, data_t ext_data, int* p_succ_data);

/* in/pre/post order successor */
data_t bst_inorder_successor(bst_t* p_bst, data_t ext_data, int* p_succ_data);
data_t bst_postorder_successor(bst_t* p_bst, data_t ext_data, int* p_succ_data);
data_t bst_preorder_successor(bst_t* p_bst, data_t ext_data, int* p_succ_data);


/* helper routines */
void transplant(bst_t* p_bst, bst_node_t* u, bst_node_t* v);
bst_node_t* get_bst_node(data_t data);
bst_node_t* search_node(bst_t* p_bst, data_t search_data);
void destroy_node(bst_node_t* p_root_node);
void preorder_node(bst_node_t* p_root_node);
void inorder_node(bst_node_t* p_root_node);
void postorder_node(bst_node_t* p_root_node);
void reset_color(bst_node_t* p_root_node);

/* in/pre/post order predecessor */
bst_node_t* inorder_predecessor(bst_node_t* p_node);
bst_node_t* postorder_predecessor(bst_node_t* p_node);
bst_node_t* preorder_predecessor(bst_node_t* p_node);

/* in/pre/post order successor */
bst_node_t* inorder_successor(bst_node_t* p_node);
bst_node_t* postorder_successor(bst_node_t* p_node);
bst_node_t* preorder_successor(bst_node_t* p_node);
#endif