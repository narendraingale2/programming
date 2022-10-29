#include <stdio.h>
#include<stdlib.h>
#include<assert.h>

#include "avl.h"

avl_tree_t* create_avl_tree(void)
{
    avl_tree_t* p_tree = NULL;
    p_tree = xcalloc(1, sizeof(avl_tree_t));
    p_tree->p_root_node = NULL;
    p_tree->nr_elements = 0;
    return(p_tree);
}

status_t insert_into_avl_tree(avl_tree_t* p_avl_tree, data_t new_data)
{

}

status_t remove_data_from_avl_tree(avl_tree_t* p_avl_tree, data_t r_data)
{

}

bool find_data_in_avl_tree(avl_tree_t* p_avl_tree, data_t f_data)
{
    return (search_avl_tree_nodelevel(p_avl_tree, f_data) != NULL);
}

void inorder_walk(avl_tree_t* p_avl_tree)
{
    printf("[START]<->");
    inoreder_walk_nodelevel(p_avl_tree->p_root_node);
    puts("[END]");
}

unsigned long get_height_of_avl_tree(avl_tree_t* p_tree)
{
    return(get_hight_node_level(p_tree->p_root_node));
}

status_t get_avl_max(avl_tree_t* p_avl_tree, data_t* p_max_data)
{
    avl_node_t* p_avl_node = NULL;

    if(p_avl_tree->p_root_node == NULL)
        return(AVL_TREE_EMPTY);
    
    p_avl_node = get_avl_max_node(p_avl_tree->p_root_node);
    *p_max_data = p_avl_node -> data;
    return(SUCCESS);
}

status_t get_avl_min(avl_tree_t* p_avl_tree, data_t* p_min_data)
{
    avl_node_t* p_avl_node = NULL;
    if(p_avl_tree->p_root_node == NULL)
        return(AVL_TREE_EMPTY);

    p_avl_node = get_avl_min_node(p_avl_tree->p_root_node);
    *p_min_data = p_avl_node -> data;
    return(SUCCESS);
}