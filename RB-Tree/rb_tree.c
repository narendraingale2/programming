#include<stdio.h>
#include<stdlib.h>
#include <math.h>

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

void preorder_node_level_walk(rbnode_t* p_rbnode, rbnode_t* nil)
{
    if(p_rbnode != nil)
    {
        printf("[%d]", p_rbnode->data);
        preorder_node_level_walk(p_rbnode->left, nil);
        preorder_node_level_walk(p_rbnode->right, nil);
    }
}

void inorder_node_level_walk(rbnode_t* p_rbnode, rbnode_t* nil)
{
    if(p_rbnode != nil)
    {
        inorder_node_level_walk(p_rbnode->left, nil);
        printf("[%d]", p_rbnode->data);
        inorder_node_level_walk(p_rbnode->right, nil);
    }
}

void destroy_node_level(rbnode_t* p_root_node, rbnode_t* nil)
{
    if(p_root_node != nil)
    {
        destroy_node_level(p_root_node->left, nil);
        destroy_node_level(p_root_node->right, nil);
        free(p_root_node);
    }
}
void postorder_node_level_walk(rbnode_t* p_rbnode, rbnode_t* nil)

{
    if(p_rbnode != nil)
    {
        postorder_node_level_walk(p_rbnode->left, nil);
        postorder_node_level_walk(p_rbnode->right, nil);
        printf("[%d]", p_rbnode->data);
    }
}

status_t rbtree_insert(rbtree_t* p_rbtree, data_t data)
{
    rbnode_t* p_run = NULL;
    rbnode_t* z = NULL;
    
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
                z->parent = p_run;
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
                z->parent = p_run;
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

void rb_insert_fixup(rbtree_t* p_rbtree, rbnode_t* z)
{
    rbnode_t* y = NULL;

    while (z->parent->color == RED)
    {
       if(z->parent == z->parent->parent->left) 
       {
            y = z->parent->parent->right;
            if(y->color == RED)
            {
                z->parent->color = BLACK;               // case 1
                y->color = BLACK;                       // case 1
                z->parent->parent->color = RED;         // case 1
                z = z->parent->parent;                  // case 1
            }
            else
            {
                if(z == z->parent->right)
                {
                    z = z -> parent;                    // case 2
                    left_rotate(p_rbtree, z);           // case 2
                }
                z->parent->color = BLACK;                     // case 3
                z->parent->parent->color = RED;               // case 3
                right_roatate(p_rbtree, z->parent->parent);   // case 3
            }
       }
       else
       {
        y = z->parent->parent->left;
        if(y->color == RED)
        {
            z->parent->color = BLACK;                   // case 1
            y->color = BLACK;                           // case 1
            z->parent->parent->color = RED;             // case 1
            z = z->parent->parent;                      // case 1
        }
        else
        {
            if(z == z->parent->left)
            {
                z = z->parent;                          // case 2
                right_roatate(p_rbtree, z);             // case 2
            }
            z->parent->color = BLACK;                   // case 3
            z->parent->parent->color = RED;             // case 3
            left_rotate(p_rbtree, z->parent->parent);   // case 3
        }
       }
    }
    p_rbtree -> p_root_node ->color = BLACK;
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
        y_original_color = y -> color;

        if(z->left == p_rbtree -> p_nil)
        {
            x = z -> right;
            rb_transplant(p_rbtree, z, z->right);
        }
        else if(z->right == p_rbtree -> p_nil)
        {
            x = z->left;
            rb_transplant(p_rbtree, z, z->left);
        }
        else
        {
            y = get_rb_min_node(p_rbtree, z->right);
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

        if( y_original_color == BLACK && x != p_rbtree -> p_nil)
            rb_remove_fixup(p_rbtree, x);

        return(SUCCESS);
}

void left_rotate(rbtree_t* p_rbtree, rbnode_t* x)
{
    rbnode_t* y = NULL;

    /*part1*/
    y = x->right;
    x->right = y -> left;
    if(y->left != p_rbtree->p_nil)
        y->left->parent = x;

    y->parent = x->parent;
    if(x->parent == p_rbtree->p_nil)
        p_rbtree->p_root_node = y;
    else if(x == x-> parent->left)
        x->parent->left = y;
    else if(x == x->parent->right)
        x->parent->right = y;
    
    /* part 3*/
    y -> left = x;
    x->parent = y;
}

void right_roatate(rbtree_t* p_rbtree, rbnode_t* x)
{
    rbnode_t* y = NULL;

    y = x->left;
    x->left = y->right;
    if(y->right != p_rbtree->p_nil)
        y->right->parent = x;
    
    y->parent = x->parent;
    if(x->parent == p_rbtree->p_nil)
        p_rbtree->p_root_node = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else if(x == x->parent->right)
        x->parent->right = y;
    
    y->right = x;
    x->parent = y;
}

void rb_remove_fixup(rbtree_t* p_rbtree, rbnode_t* x)
{
    rbnode_t* w = p_rbtree->p_nil;
    while(x != p_rbtree->p_root_node && x -> color == BLACK)
    {
        if(x == x->parent->left)
        {
            w = x -> parent -> right;
            if(w->color == RED)
            {
                w -> color = BLACK;
                x -> parent -> color = RED;
                left_rotate(p_rbtree, x -> parent);
                w = x->parent->right;
            }
            
            if(w = p_rbtree -> p_nil)
            {
                x = x -> parent;
                continue;
            }

            if(w -> left -> color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if(w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_roatate(p_rbtree, w);
                    w = x->parent->right;
                }
                 w -> color = x -> parent -> color;
                 x -> parent -> color = BLACK ;
                 w -> right -> color = BLACK;
                 left_rotate(p_rbtree, x ->parent);
                 x = p_rbtree->p_root_node;
            }
        }
        else
        {
            w = x -> parent -> left;
            if(w -> color == RED)
            {
                w -> color = BLACK;
                x -> parent -> color = RED;
                right_roatate(p_rbtree, x->parent);
                w = x -> parent -> left;
            }

            if( w == p_rbtree ->p_nil)
            {
                x = x->parent;
                continue;
            }
            if(w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if(w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(p_rbtree, w);
                    w = x ->parent->left;
                }
                
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_roatate(p_rbtree, x->parent);
                x = p_rbtree-> p_root_node;
            }
        }
    }
    x->color = BLACK;
    
}

void rb_transplant(rbtree_t* p_rbtree, rbnode_t* u, rbnode_t* v)
{
    if(u->parent == p_rbtree->p_nil)
        p_rbtree->p_root_node = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else if(u == u->parent->right)
        u->parent->right = v;
    
    if(v!=p_rbtree->p_nil)
        v->parent = u->parent;
}

status_t get_rb_max(rbtree_t* p_rbtree, int* p_max)
{
    rbnode_t* p_max_node = NULL;

    p_max_node = get_rb_max_node(p_rbtree);
    if(p_max_node == NULL)
        return RBTREE_DATA_NOT_FOUND;
    *p_max = p_max_node ->data ; 
    return SUCCESS;
}

status_t get_rb_min(rbtree_t* p_rbtree, int* p_min)
{
    rbnode_t* p_min_node = NULL;

    p_min_node = get_rb_min_node(p_rbtree, p_rbtree->p_root_node);
    if(p_min_node == NULL)
        return RBTREE_DATA_NOT_FOUND;
    *p_min = p_min_node ->data ; 
    return SUCCESS;
}

unsigned int rbtree_get_height(rbtree_t* p_rbtree)
{
    return(get_height_level(p_rbtree,p_rbtree->p_root_node));
}

unsigned int get_height_level(rbtree_t* p_rbtree, rbnode_t* p_node)
{
    if(p_node == p_rbtree->p_nil)
        return 0;

    return (max(get_height_level(p_rbtree, p_node->left),get_height_level(p_rbtree, p_node->right)) + 1);
    
}

rbnode_t* get_rb_max_node(rbtree_t* p_rbtree)
{
    rbnode_t* p_run;
    p_run = p_rbtree -> p_root_node;
    while (p_run->right != p_rbtree->p_nil)
        p_run = p_run->right;

    return(p_run); 
}

rbnode_t* get_rb_min_node(rbtree_t* p_rbtree, rbnode_t* p_root_node)
{
    rbnode_t* p_run;
    p_run = p_root_node;
    while (p_run->left != p_rbtree->p_nil)
        p_run = p_run->left;

    return(p_run); 
}

status_t rbtree_find(rbtree_t* p_rbtree, data_t data)
{
    return(search_rb_node(p_rbtree, data) != p_rbtree->p_nil);
}

rbnode_t* search_rb_node(rbtree_t* p_rbtree, data_t search_data)
{
    rbnode_t* p_run;
    
    p_run = p_rbtree ->p_root_node;

    while (p_run != p_rbtree->p_nil)
    {
        if(p_run->data == search_data)
            return(p_run);
        else if(search_data <= p_run -> data)
            p_run = p_run -> left;
        else
            p_run = p_run -> right;
    }

    return(p_run);
}

rbnode_t* get_rbnode(data_t new_data, rbnode_t* nil)
{
    rbnode_t* p_new_node = NULL;
    p_new_node = (rbnode_t*)xcalloc(1,sizeof(rbnode_t));
    p_new_node -> data = new_data;
    p_new_node -> left = nil;
    p_new_node -> right = nil;
    p_new_node -> parent = nil;
    return p_new_node;
}

void* xcalloc(size_t nr_elements, size_t size_per_element)
{
    void* p = NULL;

    p = calloc(nr_elements, size_per_element); 
    if (p == NULL)
    {
        fprintf(stderr, "Fatal error: Out of memory ");
        exit(3);
    }
    
    return(p);
}
