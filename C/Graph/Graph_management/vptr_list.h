#ifndef _VPTR_LIST_H
#define _VPTR_LIST_H
#include<stdio.h>
#include<stdlib.h>
#include"graph.h"

#define VPTR_LIST_EMPTY    7
#define VPTR_QUEUE_EMPTY   VPTR_LIST_EMPTY

typedef struct vptr_list_node vptr_node_t;
typedef vptr_node_t vptr_list_t;
typedef vptr_list_t vptr_stack_t;
typedef vptr_list_t vptr_queue_t;
typedef vptr_list_t vptr_priority_queue_t;

struct vptr_list_node
{
    vnode_t* vnode_ptr;

    struct vptr_list_node* next;
    struct vptr_list_node* prev;
};


/* vptr list routines */
vptr_list_t* create_vptr_list(void);
status_t vptr_insert_end(vptr_list_t* p_vptr_list, vnode_t* pv_node);
status_t vptr_insert_start(vptr_list_t* p_vptr_list, vnode_t* pv_node);
status_t vptr_get_start(vptr_list_t* p_vptr_list, vnode_t** ppv_node);
status_t vptr_get_end(vptr_list_t* p_vptr_list, vnode_t** ppv_node);
status_t vptr_pop_start(vptr_list_t* p_vptr_list, vnode_t** ppv_node);
status_t vptr_pop_end(vptr_list_t* p_vptr_list, vnode_t** ppv_node);
status_t vptr_is_list_empty(vptr_list_t* p_vptr_list);
status_t vptr_destroy_list(vptr_list_t** pp_vptr_list);

/* vertical pointer list management auxillary routines */
static vptr_node_t* vptr_get_node(vnode_t* p_vnode);
static void vptr_generic_insert(vptr_node_t* p_beg, vptr_node_t* p_mid, vptr_node_t* p_end);
static void vptr_geneirc_delete(vptr_node_t* p_vptr_delete_node);
static vptr_node_t* vptr_search_node(vptr_list_t* p_vptro_list, vnode_t* pv_search_node);

/* vertical pointer stack interface routines*/
vptr_stack_t* vptr_create_stack(void);
status_t vptr_stack_push(vptr_stack_t* p_vptr_stack, vnode_t* pv_new_node);
status_t vptr_stack_pop(vptr_stack_t* p_vptr_stack, vnode_t** ppv_delete_node);
status_t vptr_stack_top(vptr_stack_t* p_vptr_stack, vnode_t** ppv_delete_node);
status_t vptr_is_stack_empty(vptr_stack_t* p_vptr_stack);
status_t vptr_destroy_stack(vptr_stack_t** pp_vptr_stack);

/* vertical pointer queue interface routines */
vptr_queue_t* vptr_create_queue(void);
status_t vptr_enqueue(vptr_queue_t* p_vptr_queue, vnode_t* pv_new_node);
status_t vptr_dequeue(vptr_queue_t* p_vptr_queue, vnode_t** ppv_delete_node);
status_t vptr_is_queue_empty(vptr_queue_t* p_vptr_queue);
status_t vptr_destroy_queue(vptr_queue_t** p_vptr_queue); 

/* vertical pointer priority queue interface routines */
vptr_priority_queue_t* vptr_create_priority_queue(void);
status_t vptr_priority_enqueue(vptr_priority_queue_t* p_vptr_queue, vnode_t* pv_new_node);
status_t vptr_priority_dequeue_min(vptr_priority_queue_t* p_vptr_queue, vnode_t** ppv_delete_node);
status_t vptr_priority_is_queue_empty(vptr_priority_queue_t* p_vptr_queue);
status_t vptr_destroy_priority_queue(vptr_priority_queue_t** p_vptr_queue); 
#endif