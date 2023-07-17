#include<stdio.h>
#include"LIST.h"

list_t* create_list()
{
    list_t* p_list = NULL;
    node_t* p_head_node = NULL;

    p_list = xcalloc(1,sizeof(list_t));
    p_head_node = get_node(-1);
    p_head_node -> next = p_head_node;
    p_head_node -> prev = p_head_node;
    p_list -> p_head_node = p_head_node;
    p_list -> size = 0;

    return p_list;
}

status_t insert_start(list_t* p_list, data_t data)
{
   generic_insert(p_list->p_head_node, get_node(data), p_list->p_head_node->next);
   return SUCCESS; 
}

status_t insert_end(list_t* p_list, data_t data)
{
    generic_insert(p_list->p_head_node->prev, get_node(data),p_list->p_head_node);
    return SUCCESS;
}

status_t insert_after(list_t* p_list, data_t s_data, data_t new_daa)
{
    node_t* s_node = NULL;
    s_node = search_node(p_list->p_head_node,s_data);
    
    if(s_node == NULL)
        return (LIST_DATA_NOT_FOUND);

    generic_insert(s_node, get_node(new_daa), s_node->next);
    p_list -> size++;
    
    return SUCCESS;
}

status_t insert_before(list_t* p_list, data_t s_data, data_t new_data)
{
    node_t* s_node = NULL;
    s_node = search_node(p_list-> p_head_node, s_data);

    if(s_node == NULL)
        return(LIST_DATA_NOT_FOUND);

    generic_insert(s_node->prev,get_node(new_data), s_node);
    p_list -> size++;

    return SUCCESS;
}

status_t get_start(list_t* p_list, data_t* p_start_data)
{
    if(is_list_empty == TRUE)
        return LIST_EMPTY;
    
    *p_start_data = p_list -> p_head_node -> next -> data;
    
    return(SUCCESS);
}

status_t get_end(list_t* p_list,data_t* p_end_data)
{
    if(is_list_empty == TRUE)
        return LIST_EMPTY;

    *p_end_data = p_list -> p_head_node -> prev -> data;
    
    return(SUCCESS);
}

status_t pop_start(list_t* p_list, data_t* p_start_data)
{

    if(is_list_empty == TRUE)
        return LIST_EMPTY;
    
    *p_start_data = p_list -> p_head_node -> next -> data;
    generic_delete(p_list->p_head_node->next);
    
    p_list -> size--;
    return(SUCCESS);
}

status_t pop_end(list_t* p_list, data_t* p_end_data)
{
    
    if(is_list_empty == TRUE)
        return LIST_EMPTY;

    *p_end_data = p_list -> p_head_node -> prev -> data;
    generic_delete(p_list->p_head_node->prev);
    
    p_list -> size--;
    return(SUCCESS);
}


status_t remove_start(list_t* p_list)
{
    if(is_list_empty == TRUE)
        return LIST_EMPTY;
    
    generic_delete(p_list->p_head_node->next);
    return(SUCCESS);
}

status_t remove_end(list_t* p_list)
{
    if(is_list_empty == TRUE)
        return LIST_EMPTY;

    generic_delete(p_list->p_head_node->prev);
    return(SUCCESS);
}

status_t remove_data(list_t* p_list, data_t r_data)
{
    node_t* p_searched_node;

    p_searched_node = search_node(p_list -> p_head_node, r_data);

    if(p_searched_node == NULL)
        return LIST_DATA_NOT_FOUND;

    generic_delete(p_searched_node);
    return SUCCESS;
}

bool is_list_empty(list_t* p_list)
{
    return(p_list->p_head_node->prev == p_list->p_head_node && p_list->p_head_node->next == p_list -> p_head_node);
}

bool find_in_list(list_t* p_list, data_t f_data)
{

}
bool length_list(list_t* p_list)
{
    return p_list -> size;
}

list_t* reverse_list(list_t* p_list)
{
    node_t* p_run;
    list_t* p_rev_list;
    data_t data;
    
    p_rev_list = create_list();

    for(p_run = p_list ->p_head_node->next; p_run -> next != p_list->p_head_node; p_run = p_run -> prev)
        insert_start(p_list,p_run->data);
    
    return p_rev_list;
}

status_t reverse_list_m(list_t* p_list); 

status_t destroy_list(list_t** p_list);