#include<stdio.h>

#include"rb_tree.h"

rbtree_t* create_rbtree(void)
{
    rbtree_t* p_rbtree = (rbtree_t*)xcalloc(1,sizeof(rbtree_t));
    p_rbtree ->nr_nodes = 0;
    p_rbtree->p_nil = (rbnode_t*)xcalloc(1, sizeof(rbnode_t));
    p_rbtree->p_nil->color = BLACK;
    p_rbtree->p_nil->data = -1;
    p_rbtree->p_nil->left = NULL;
    p_rbtree->p_nil->right = NULL;
    p_rbtree->p_nil->parent = NULL;
    p_rbtree->p_root_node = p_rbtree->p_nil;
    return(p_rbtree); 
}

status_t destroy_rbtree(rbtree_t** pp_rbtree)
{
    rbtree_t* p_rbtree = *pp_rbtree;
    destroy_node_level(p_rbtree->p_root_node, p_rbtree->p_nil);
    free(p_rbtree->p_nil);
    free(p_rbtree);

    *pp_rbtree = NULL;
    return(SUCCESS);
}

void preorder_walk(rbtree_t* p_rbtree)
{
    puts("Preorder walk ->");
    printf("[START]<->");
    preorder_node_level_walk(p_rbtree->p_root_node, p_rbtree->p_nil);
    puts("[END]");
}

void inorder_walk(rbtree_t* p_rbtree)
{
    puts("Inorder walk ->");
    printf("[START]<->");
    inorder_node_level_walk(p_rbtree->p_root_node, p_rbtree->p_nil);
    puts("[END]");
}

void postorder_walk(rbtree_t* p_rbtree)
{
    puts("postorder walk ->");
    printf("[START]<->");
    postorder_node_level_walk(p_rbtree->p_root_node, p_rbtree->p_nil);
    puts("[END]");
}

status_t rbtree_insert(rbtree_t* p_rbtree, data_t data)
{
    rbnode_t* p_run;
    rbnode_t* z;
    
    p_run = p_rbtree->p_root_node;

    z = get_rbnode(data, p_rbtree->p_nil);

    if(p_run == p_rbtree->p_nil)
    {
        p_rbtree -> p_root_node = z;
        p_rbtree->nr_nodes += 1;
        rb_insert_fixup(p_rbtree, z);
        return(SUCCESS);
    }
    
    while (TRUE)
    {
        if(data <= p_run->data)
        {
            if(p_run->left == p_rbtree -> p_nil)
            {
                p_run -> left = z;
                break;
            }
            else
                p_run = p_run -> left;
        }
        else
        {
            if(p_run->right == p_rbtree ->p_nil)
            {
                p_run -> right = z;
                break;
            }
            else
                p_run = p_run -> right;
        }
    }

    p_rbtree->nr_nodes += 1;
    rb_insert_fixup(p_rbtree, z);
    return(SUCCESS);
}

status_t rbtree_delete(rbtree_t* p_rbtree, data_t data)
{
        rbnode_t* z = p_rbtree -> p_nil; // Node to be deleted
        rbnode_t* y = p_rbtree -> p_nil; // inorder successor which will replace node to be deleted
        rbnode_t* x = p_rbtree -> p_nil; // address of root of subtree which will need fixup
        color_t y_original_color;

        z = search_rb_node(p_rbtree, data);
        if( z == p_rbtree ->p_nil)
            return(RBTREE_DATA_NOT_FOUND);
        
        y = z;
        y_original_color = z -> color;

        if(z->left == p_rbtree -> p_nil)
        {
            x = z -> right;
            rb_transplant(p_rbtree, z, z->right);
        }
        else if(z->right == p_rbtree -> p_nil)
        {
            x = z->left;
            rb_transplant(p_rbtree, z, z->right);
        }
        else
        {
            y = get_rb_min(p_rbtree);
            y_original_color = y->color;
            x = y->right;
            if(y -> parent == z)
                x -> parent = y;
            else
            {
                rb_transplant(p_rbtree, y, y->right);
                y -> right = z->right;
                y -> right ->parent = y;
            }
            rb_transplant(p_rbtree, z, y);
            y -> left = z -> left;
            y -> left-> parent = y;
            y -> color = z->color;
        }

        if( y_original_color == BLACK)
            rb_remove_fixup(p_rbtree, x);
        
        return(SUCCESS);
}

status_t get_rb_max(rbtree_t* p_rbtree)
{
    rbnode_t* p_run;
    p_run = p_rbtree -> p_root_node;
    while (p_run->right != p_rbtree->p_nil)
        p_run = p_run->right;

    return(p_run); 
}

status_t get_rb_min(rbtree_t* p_rbtree)
{
    rbnode_t* p_run;
    p_run = p_rbtree -> p_root_node;
    while (p_run->left != p_rbtree->p_nil)
        p_run = p_run->left;

    return(p_run); 
}

status_t rbtree_find(rbtree_t* p_rbtree, data_t data)
{
    return(search_rb_node(p_rbtree->p_root_node, data) != p_rbtree->p_nil);
}

rbnode_t* search_rb_node(rbtree_t* p_rbtree, data_t search_data)
{
    rbnode_t* p_run;
    
    p_run = p_rbtree ->p_root_node;

    while (p_run != p_rbtree->p_nil)
    {
        if(p_run->data == search_data)
            return(p_run);
        else if(p_run -> data < search_data)
            p_run = p_run -> left;
        else
            p_run = p_run -> right;
    }

    return(p_run);
}