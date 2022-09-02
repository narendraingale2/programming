#include<stdio.h>
#include<stdlib.h>
#include"vptr_list.h"


/* vptr list routines */
vptr_list_t* create_vptr_list(void)
{
    vptr_node_t* p_vptr_list = NULL;
    p_vptr_list = vptr_get_node(NULL);
    p_vptr_list->next = p_vptr_list;
    p_vptr_list->prev = p_vptr_list;
    return(p_vptr_list);
}

status_t vptr_insert_end(vptr_list_t* p_vptr_list, vnode_t* pv_node)
{
    vptr_generic_insert(p_vptr_list->prev, vptr_get_node(pv_node), p_vptr_list);
    return(SUCCESS);
}

status_t vptr_insert_start(vptr_list_t* p_vptr_list, vnode_t* pv_node)
{
    vptr_generic_insert(p_vptr_list, vptr_get_node(pv_node), p_vptr_list->next);
    return(SUCCESS);
}

status_t vptr_get_start(vptr_list_t* p_vptr_list, vnode_t** ppv_node)
{
    if(vptr_is_list_empty(p_vptr_list) == TRUE)
    {
        return(VPTR_LIST_EMPTY);   
    }

    *ppv_node = p_vptr_list->next->vnode_ptr;
    return(SUCCESS);
}

status_t vptr_get_end(vptr_list_t* p_vptr_list, vnode_t** ppv_node)
{

    if(vptr_is_list_empty(p_vptr_list) == TRUE)
    {
        return(VPTR_LIST_EMPTY);   
    }

    *ppv_node = p_vptr_list->prev->vnode_ptr;
    return(SUCCESS);
}

status_t vptr_pop_start(vptr_list_t* p_vptr_list, vnode_t** ppv_node)
{
    if(vptr_is_list_empty(p_vptr_list) == TRUE)
    {
        return(VPTR_LIST_EMPTY);   
    }

    *ppv_node = p_vptr_list->next->vnode_ptr;
    vptr_geneirc_delete(p_vptr_list->next);
    return(SUCCESS);
}

status_t vptr_pop_end(vptr_list_t* p_vptr_list, vnode_t** ppv_node)
{
    if(vptr_is_list_empty(p_vptr_list) == TRUE)
    {
        return(VPTR_LIST_EMPTY);   
    }

    *ppv_node = p_vptr_list->prev->vnode_ptr;
    vptr_geneirc_delete(p_vptr_list->prev);
    return(SUCCESS);
}

status_t vptr_is_list_empty(vptr_list_t* p_vptr_list)
{
    return(p_vptr_list->next == p_vptr_list && p_vptr_list->prev == p_vptr_list);
}

status_t vptr_destroy_list(vptr_list_t** pp_vptr_list)
{
    vptr_list_t* p_vptr_list=NULL;
    vptr_node_t* p_run = NULL;
    vptr_node_t* p_run_next = NULL;

    p_vptr_list = *pp_vptr_list;
    for(p_run = p_vptr_list->next; p_run != p_vptr_list; p_run = p_run_next)
    {
        p_run_next = p_run->next;
        free(p_run);
    }    
    return(SUCCESS);
}



/* vertical pointer list management auxillary routines */
static vptr_node_t* vptr_get_node(vnode_t* p_vnode)
{
    vptr_node_t* p = NULL;
    p = (vptr_node_t*)xcalloc(1,sizeof(vptr_node_t));
    p->next = NULL;
    p->prev = NULL;
    p->vnode_ptr = p_vnode;
    return(p);
}

static void vptr_generic_insert(vptr_node_t* p_beg, vptr_node_t* p_mid, vptr_node_t* p_end)
{
    p_mid -> next = p_end;
    p_mid -> prev = p_beg;
    p_beg -> next = p_mid;
    p_end -> prev = p_mid;
}

static void vptr_geneirc_delete(vptr_node_t* p_vptr_delete_node)
{
    p_vptr_delete_node->prev->next = p_vptr_delete_node->next;
    p_vptr_delete_node->next->prev = p_vptr_delete_node->prev;
    free(p_vptr_delete_node);
}

static vptr_node_t* vptr_search_node(vptr_list_t* p_vptr_list, vnode_t* pv_search_node)
{
    vptr_node_t* p_vptr_run_node = NULL;

    for(p_vptr_run_node = p_vptr_list->next; p_vptr_run_node != p_vptr_list; p_vptr_run_node = p_vptr_run_node ->  next)
    {
        if(p_vptr_run_node->vnode_ptr == pv_search_node)
        {
            return p_vptr_run_node;
        }
    }

    return(NULL);
}


/* vertical pointer stack interface routines*/
vptr_stack_t* vptr_create_stack(void)
{
    return create_vptr_list();
}

status_t vptr_stack_push(vptr_stack_t* p_vptr_stack, vnode_t* pv_new_node)
{
    return(vptr_insert_end(p_vptr_stack, pv_new_node));
}

status_t vptr_stack_pop(vptr_stack_t* p_vptr_stack, vnode_t** ppv_delete_node)
{
    return(vptr_pop_end(p_vptr_stack, ppv_delete_node));
}

status_t vptr_stack_top(vptr_stack_t* p_vptr_stack, vnode_t** ppv_delete_node)
{
    return(vptr_get_end(p_vptr_stack, ppv_delete_node));
}

status_t vptr_is_stack_empty(vptr_stack_t* p_vptr_stack)
{
    return(vptr_is_list_empty(p_vptr_stack));
}

status_t vptr_destroy_stack(vptr_stack_t** pp_vptr_stack)
{
    return vptr_destroy_list(pp_vptr_stack);
}

/* vertical pointer queue interface routines */
vptr_queue_t* vptr_create_queue(void)
{
    return(create_vptr_list());
}

status_t vptr_enqueue(vptr_queue_t* p_vptr_queue, vnode_t* pv_new_node)
{
    return(vptr_insert_end(p_vptr_queue,pv_new_node));
}

status_t vptr_dequeue(vptr_queue_t* p_vptr_queue, vnode_t** ppv_delete_node)
{
    return(vptr_pop_start(p_vptr_queue, ppv_delete_node));
}

status_t vptr_is_queue_empty(vptr_queue_t* p_vptr_queue)
{
    return vptr_is_list_empty(p_vptr_queue);
}

status_t vptr_destroy_queue(vptr_queue_t** p_vptr_queue) 
{
    return vptr_destroy_list(p_vptr_queue);
}


/* vertical pointer priority queue interface routines */
vptr_priority_queue_t* vptr_create_priority_queue(void)
{
    return(create_vptr_list());
}

status_t vptr_priority_enqueue(vptr_priority_queue_t* p_vptr_queue, vnode_t* pv_new_node)
{
    return(vptr_insert_end(p_vptr_queue,pv_new_node));
}

status_t vptr_priority_dequeue_min(vptr_priority_queue_t* p_vptr_queue, vnode_t** ppv_delete_node)
{
   vptr_node_t* p_vptr_min_node = NULL;
   vptr_node_t* p_vptr_run_node = NULL;

   if(vptr_is_list_empty(p_vptr_queue) == TRUE)
   {
    *ppv_delete_node = NULL;
    return(VPTR_QUEUE_EMPTY);
   }
   
   p_vptr_min_node = p_vptr_queue->next;

   for(p_vptr_run_node = p_vptr_queue->next; p_vptr_run_node != p_vptr_queue; p_vptr_run_node = p_vptr_run_node -> next)
   {
    if(p_vptr_run_node -> vnode_ptr -> priority_field < p_vptr_min_node->vnode_ptr->priority_field)
    {
        p_vptr_min_node = p_vptr_run_node;
    }
   } 

   *ppv_delete_node = p_vptr_min_node ->vnode_ptr;
   vptr_geneirc_delete(p_vptr_min_node);
   return(SUCCESS);
}

status_t vptr_priority_is_queue_empty(vptr_priority_queue_t* p_vptr_queue)
{
    return vptr_is_list_empty(p_vptr_queue);
}

status_t vptr_destroy_priority_queue(vptr_priority_queue_t** p_vptr_queue)
{
    return vptr_destroy_list(p_vptr_queue);
}