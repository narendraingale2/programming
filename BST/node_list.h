#ifndef _NODE_LIST_H
#define _NODE_LIST_H
#include<stdio.h>
#include<stdlib.h>
#include"bst.h"

typedef struct ptrbst_list_node ptrbst_node_t;
typedef ptrbst_node_t ptrbst_list_t;
typedef ptrbst_list_t ptrbst_stack_t; 

#define LIST_DATA_NOT_FOUND 6
#define LIST_EMPTY 7
#define STACK_EMPTY LIST_EMPTY 

struct ptrbst_list_node
{
    struct bst_node* p_bst;
    struct ptrbst_list_node* next;
    struct ptrbst_list_node* prev;
};

ptrbst_list_t* create_ptrbst_list(void);
status_t ptrbst_insert_end(ptrbst_list_t* p_list, bst_node_t* p_node);
status_t ptrbst_remove_end(ptrbst_list_t* p_list, ptrbst_node_t** p_node);
status_t destroy_ptrbst_list(ptrbst_list_t** pp_list);
status_t ptrbst_list_is_empty(ptrbst_list_t* p_list);

static void ptrbst_generic_insert(ptrbst_node_t* p_beg, ptrbst_node_t* p_mid, ptrbst_node_t* p_end);
static ptrbst_node_t* ptrbst_get_node(bst_node_t* p_bst_node);
static void ptrbst_generic_delete_node(ptrbst_node_t* p_delete_node);

ptrbst_stack_t* create_ptrbst_stack();
status_t ptrbst_stack_push(ptrbst_stack_t* p_stack, bst_node_t* p_bst_node);
status_t ptrbst_stack_pop(ptrbst_stack_t* p_stack, bst_node_t** p_bst_node);
status_t ptrbst_stack_is_empty(ptrbst_stack_t* p_stack);
status_t destroy_ptrbst_stack(ptrbst_stack_t** p_stack);

void* xcalloc(size_t nr_elements, size_t size_per_element);

#endif
