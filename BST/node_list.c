#include<stdio.h>
#include<stdlib.h>
#include"node_list.h"


ptrbst_list_t* create_ptrbst_list(void)
{
    ptrbst_list_t* p_list = NULL;
    p_list = ptrbst_get_node(NULL);
    p_list->next = p_list;
    p_list->prev = p_list;
}

status_t ptrbst_insert_end(ptrbst_list_t* p_list, bst_node_t* p_node)
{
    ptrbst_generic_insert(p_list->prev, ptrbst_get_node(p_node), p_list);
    return(SUCCESS);
}

status_t ptrbst_remove_end(ptrbst_list_t* p_list, bst_node_t** p_node)
{
    if(ptrbst_list_is_empty(p_list) == TRUE)
        return(LIST_EMPTY); 
        
    *p_node = p_list->prev->p_bst;
    ptrbst_generic_delete_node(p_list->prev);
    return(SUCCESS);
}

status_t destroy_ptrbst_list(ptrbst_list_t** pp_list)
{
    ptrbst_list_t* p_list = NULL;
    ptrbst_node_t* p_run = NULL;
    ptrbst_node_t* p_run_next = NULL;

    p_list = *pp_list;
    for(p_list = p_list->next; p_list != p_list; p_list = p_run_next)
    {
        p_run_next = p_run -> next;
        free(p_run);
    }    
    free(p_list);
    pp_list = NULL;
    return(SUCCESS);
}

status_t ptrbst_list_is_empty(ptrbst_list_t* p_list)
{
    return(p_list->prev == p_list && p_list->next == p_list);
}

static void ptrbst_generic_insert(ptrbst_node_t* p_beg, ptrbst_node_t* p_mid, ptrbst_node_t* p_end)
{
    p_mid->next = p_end;
    p_mid->prev = p_beg;
    p_beg->next = p_mid;
    p_end->prev = p_mid;
}

static ptrbst_node_t* ptrbst_get_node(bst_node_t* p_bst_node)
{
    ptrbst_node_t* p_new_node = NULL;
    p_new_node = (ptrbst_node_t*)xcalloc(1, sizeof(ptrbst_node_t));
    p_new_node ->next = NULL;
    p_new_node ->prev = NULL;
    p_new_node ->p_bst = p_bst_node;
    return(p_new_node);
}

static void ptrbst_generic_delete_node(ptrbst_node_t* p_delete_node)
{
    p_delete_node->prev->next = p_delete_node->next;
    p_delete_node->next->prev = p_delete_node->prev;
    free(p_delete_node);
}

ptrbst_stack_t* create_ptrbst_stack()
{
    ptrbst_list_t* p_stack = NULL;
    p_stack = create_ptrbst_list();
    return(p_stack);
}

status_t ptrbst_stack_push(ptrbst_stack_t* p_stack, bst_node_t* p_bst_node)
{
    return(ptrbst_insert_end(p_stack, p_bst_node));
}

status_t ptrbst_stack_pop(ptrbst_stack_t* p_stack, bst_node_t** p_bst_node)
{
   return(ptrbst_remove_end(p_stack, p_bst_node)); 
}
status_t ptrbst_stack_is_empty(ptrbst_stack_t* p_stack)
{
    return(ptrbst_list_is_empty(p_stack));
}
status_t destroy_ptrbst_stack(ptrbst_stack_t** p_stack)
{
    destroy_ptrbst_list(p_stack);
}

void* xcalloc(size_t nr_elements, size_t size_per_element)
{
    void* p = NULL;

    p = calloc(nr_elements, size_per_element);
    if(p == NULL)
    {
        fprintf(stderr, "Calloc: fatal: out of virtual memory \n");
        exit(EXIT_FAILURE);
    }
    return(p);
}
