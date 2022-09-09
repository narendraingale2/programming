#include<stdio.h>
#include<stdlib.h>
#include"bst.h"

bst_t* create_bst(void)
{
    bst_t* p_bst;
    p_bst = (bst_t*)malloc(sizeof(bst_t));
    if(p_bst == NULL)
    {
        fprintf(stderr, "malloc:fatal:out of virtual memmor \n");
        exit(EXIT_FAILURE);
    }
    p_bst->nr_nodes = 0;
    p_bst->p_root_node = NULL; 

}

status_t bst_insert(bst_t* p_bst, data_t new_element)
{
    bst_node_t* p_run = NULL;
    bst_node_t* p_new_node = NULL;

    
    p_run = p_bst -> p_root_node;
    p_new_node = get_bst_node(new_element);
    if(p_run == NULL)
    {
        p_bst ->p_root_node = p_new_node;
        p_bst -> nr_nodes += 1;
        return(SUCCESS);
    }
    while (1)
    {
       if(new_element <= p_run ->data)
       {
            if(p_run -> left == NULL)
            {
                p_run->left = p_new_node;
                p_new_node -> parent = p_run;
                p_bst -> nr_nodes += 1;
                return(SUCCESS);
            }
            else
            {
                p_run = p_run -> left;
            }
        
       } 
       else
       {
            if(p_run -> right == NULL)
            {
                p_run -> right = p_new_node;
                p_new_node -> parent = p_run;
                p_bst-> nr_nodes += 1;
                return(SUCCESS);
            }
            else
                p_run = p_run -> right;
       }
    }
}


status_t bst_remove(bst_t* p_bst, data_t r_data)
{

}

status_t bst_search(bst_t* p_bst, data_t searh_data)
{
    return(search_node(p_bst,searh_data) != NULL);
}

status_t bst_is_empty(bst_t* p_bst)
{
    return(p_bst -> p_root_node == NULL);
}

data_t bst_max(bst_t* p_bst)
{
    bst_node_t* p_run = NULL;
    for(p_run = p_bst ->p_root_node; p_run->right != NULL; p_run = p_run->right);

    return(p_run->data);
}

data_t bst_min(bst_t* p_bst)
{
    bst_node_t* p_run = NULL;
    for(p_run = p_bst ->p_root_node; p_run->left != NULL; p_run = p_run->left);

    return(p_run->data);
}
unsigned long long int bst_get_nr_elements(bst_t* p_bst)
{
    return(p_bst->nr_nodes);
}

status_t destroy_bst(bst_t** p_bst)
{
    destroy_node((*p_bst)->p_root_node);
    free(*p_bst);
    p_bst = NULL;
}

bst_node_t* get_bst_node(data_t data)
{
    bst_node_t* p_new_node = NULL;
    p_new_node = (bst_node_t*)malloc(sizeof(bst_node_t));
    p_new_node->data = data;
    p_new_node->left = NULL;
    p_new_node->right = NULL;
    p_new_node->parent = NULL;
}


bst_node_t* search_node(bst_t* p_bst, data_t searh_data)
{
    bst_node_t* p_run = NULL;

    p_run = p_bst->p_root_node;

    while (p_run != NULL)
    {
        if(p_run -> data == searh_data)
            return(p_run);

        if(searh_data <= p_run)
            p_run = p_run -> left;
        else
            p_run = p_run -> right;    
    }

   return(NULL); 
}

void destroy_node(bst_node_t* p_root_node)
{
    if(p_root_node != NULL)
    {
        destroy_node(p_root_node->left);
        destroy_node(p_root_node->right);
        free(p_root_node);
    }
}