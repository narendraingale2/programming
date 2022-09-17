#include<stdio.h>
#include<stdlib.h>
#include"bst.h"
#include"node_list.h"

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
    return(p_bst);

}

status_t bst_insert(bst_t* p_bst, data_t new_element)
{
    bst_node_t* p_run = NULL;
    bst_node_t* p_new_node = NULL;

    
    p_run = p_bst -> p_root_node;
    p_new_node = get_bst_node(new_element);
    if(p_run == NULL)
    {
        printf("Inserted root node\n");
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
    bst_node_t* p_delete_node = NULL;
    bst_node_t* w = NULL;


    p_delete_node = search_node(p_bst,r_data);

    if(p_delete_node == NULL)
        return(TREE_DATA_NOT_FOUND);
    
    if(p_delete_node->left == NULL)
    {
        if(p_delete_node ->parent == NULL)
            p_bst->p_root_node = p_delete_node->right;
        
        else if(p_delete_node->parent->left == p_delete_node)
            p_delete_node->parent->left = p_delete_node -> right;
        else
            p_delete_node->parent->right = p_delete_node -> right;
        
        if(p_delete_node ->right != NULL)
            p_delete_node -> right -> parent = p_delete_node->parent;

    }
    else if(p_delete_node -> right == NULL)
    {
        if(p_delete_node -> parent == NULL)
            p_bst->p_root_node = p_delete_node->left;
        
        else if(p_delete_node->parent->left == p_delete_node)
            p_delete_node->parent->left = p_delete_node -> left;
        else
            p_delete_node->parent->right = p_delete_node -> left;
        
        if(p_delete_node ->left != NULL)
            p_delete_node -> left -> parent = p_delete_node->parent;
    }
    else
    {
        w = p_delete_node -> right;
        while (w -> left != NULL)
           w = w->left; 
        
        if(w != p_delete_node -> right)
        {
            w->parent->left = w->right;
            if(w->right != NULL)
                w->right->parent = w->parent;
            
            w->right = p_delete_node -> right;
            w->right->parent = w;
        }
        if(p_delete_node ->parent == NULL)
            p_bst->p_root_node = w;
        else if(p_delete_node == p_delete_node ->parent->left)
            p_delete_node->parent->left = w;
        else
            p_delete_node->parent->right = w;
        
        w->parent = p_delete_node -> parent;
        w->left = p_delete_node -> left;
        w->left->parent = w;
    }

    p_bst->nr_nodes -= 1;
    free(p_delete_node);
    p_delete_node = NULL;

    return(SUCCESS);
        
}

void bst_reset(bst_t* p_bst)
{
    reset_color(p_bst->p_root_node);
}

status_t bst_search(bst_t* p_bst, data_t searh_data)
{
    if(search_node(p_bst,searh_data) != NULL)
        return SUCCESS;
    
    return TREE_DATA_NOT_FOUND;
}

status_t bst_is_empty(bst_t* p_bst)
{
    return(p_bst -> p_root_node == NULL);
}

data_t bst_max(bst_t* p_bst)
{
    bst_node_t* p_run = NULL;
    if(bst_is_empty(p_bst) == TRUE)
        return TREE_EMPTY;

    for(p_run = p_bst ->p_root_node; p_run->right != NULL; p_run = p_run->right);

    return(p_run->data);
}

data_t bst_min(bst_t* p_bst)
{
    bst_node_t* p_run = NULL;
    if(bst_is_empty(p_bst) == TRUE)
        return TREE_EMPTY;

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
    *p_bst = NULL;
    return(SUCCESS);
}

/* in/pre/post order walks */
void preorder_r(bst_t* p_bst)
{
    puts("Preorder Walk ->");
    preorder_node(p_bst->p_root_node);
    puts("[END]");
}

void postorder_r(bst_t* p_bst)
{
    puts("Postorder Walk ->");
    postorder_node(p_bst->p_root_node);
    puts("[END]");
}

void inorder_r(bst_t* p_bst)
{
    puts("inorder Walk ->");
    inorder_node(p_bst->p_root_node);
    puts("[END]");
}

bst_node_t* get_bst_node(data_t data)
{
    bst_node_t* p_new_node = NULL;
    p_new_node = (bst_node_t*)malloc(sizeof(bst_node_t));
    p_new_node->data = data;
    p_new_node->left = NULL;
    p_new_node->right = NULL;
    p_new_node->parent = NULL;
    return p_new_node;
}


bst_node_t* search_node(bst_t* p_bst, data_t searh_data)
{
    bst_node_t* p_run = NULL;

    p_run = p_bst->p_root_node;

    while (p_run != NULL)
    {
        if(p_run -> data == searh_data)
            return(p_run);

        if(searh_data <= p_run->data)
            p_run = p_run -> left;
        else
            p_run = p_run -> right;    
    }

   return(NULL); 
}

void reset_color(bst_node_t* p_root_node)
{
    if(p_root_node != NULL)
    {
        reset_color(p_root_node->left);
        reset_color(p_root_node->right);
        p_root_node ->c = WHITE;
    }
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

void preorder_node(bst_node_t* p_root_node)
{
    if(p_root_node != NULL)
    {
        printf("[%d]<->", p_root_node->data);
        preorder_node(p_root_node->left);
        preorder_node(p_root_node->right);
    }
}


void inorder_node(bst_node_t* p_root_node)
{
    if(p_root_node != NULL)
    {
        inorder_node(p_root_node->left);
        printf("[%d]<->", p_root_node->data);
        inorder_node(p_root_node->right);
    }
}

void postorder_node(bst_node_t* p_root_node)
{
    if(p_root_node != NULL)
    {
        postorder_node(p_root_node->left);
        postorder_node(p_root_node->right);
        printf("[%d]<->", p_root_node->data);
    }
}
/* in/pre/post order walks */
void preorder(bst_t* p_bst)
{
    bst_node_t* p_run;
    ptrbst_stack_t* p_stack;
    p_stack = create_ptrbst_stack();

    p_run = p_bst->p_root_node;
    if(p_run != NULL)
        ptrbst_stack_push(p_stack, p_run);
    
    printf("[START]<->"); 
    while (ptrbst_stack_is_empty(p_stack) != TRUE)
    {
        p_run = NULL;
        ptrbst_stack_pop(p_stack, &p_run);
        printf("[%d]<->", p_run->data);
        
        if(p_run->right != NULL)
            ptrbst_stack_push(p_stack,p_run->right);
        
        if(p_run ->left != NULL)
            ptrbst_stack_push(p_stack,p_run->left);
        

    }
    puts("[END]");

}

void postorder(bst_t* p_bst)
{
    bst_node_t* p_run;
    ptrbst_stack_t* p_stack;
    p_stack = create_ptrbst_stack();
    p_run = p_bst ->p_root_node;
    printf("[START]<->");

    while (p_run != NULL || ptrbst_stack_is_empty(p_stack) != TRUE)
    {
        if(p_run != NULL)
        {
            ptrbst_stack_push(p_stack, p_run);
            p_run = p_run -> left;
        }
        else
        {
            ptrbst_stack_peek(p_stack, &p_run);
            if(p_run ->right == NULL || p_run->right->c == GREY)
            {
                printf("[%d]<->",p_run->data);
                p_run->c = GREY;
                ptrbst_stack_pop(p_stack, &p_run);
                p_run = NULL;
            }
            else
                p_run = p_run->right;
        }
        
    }
    puts("[END]");
}

void inorder(bst_t* p_bst)
{
    bst_node_t* p_run;
    ptrbst_stack_t* p_stack;
    p_stack = create_ptrbst_stack();

    p_run = p_bst->p_root_node;

    printf("[START]<->");
    while (TRUE)
    {
        while (p_run != NULL)
        {
            ptrbst_stack_push(p_stack, p_run);
            p_run = p_run -> left;
        }
        if(ptrbst_stack_pop(p_stack, &p_run) == STACK_EMPTY)
            break;
        
        printf("[%d]<->", p_run->data);
        p_run = p_run->right;
    }
    puts("[END]");
}


data_t bst_inorder_predecessor(bst_t* p_bst, data_t ext_data, int* p_pred_data)
{
    bst_node_t* p_pred_node = NULL;
    bst_node_t* p_node = NULL;

    p_node = search_node(p_bst, ext_data);
    if(p_node == NULL)
        return TREE_DATA_NOT_FOUND;

    p_pred_node = inorder_predecessor(p_node);
    if(p_pred_node == NULL)
        return(TREE_NO_PREDECESSOR);
    
    *p_pred_data = p_pred_node->data;
    return(SUCCESS);
}

bst_node_t* inorder_predecessor(bst_node_t* p_node)
{
    bst_node_t* p_run;
    bst_node_t* x;
    bst_node_t* y;

    p_run = p_node;
    if(p_run->left != NULL)
    {
        p_run = p_node->left;
        while (p_run->right != NULL)
            p_run = p_run ->right;
        
        return(p_run);
    }
    else
    {
        x = p_run;
        y = p_run->parent;
        while (y != NULL && x == y->left)
        {
           x = y;
           y = y->parent; 
        }
       return(y); 
    }
}

data_t bst_inorder_successor(bst_t* p_bst, data_t ext_data, int* p_succ_data)
{
    bst_node_t* p_succ_node = NULL;
    bst_node_t* p_node = NULL;

    p_node = search_node(p_bst, ext_data);
    if(p_node == NULL)
        return TREE_DATA_NOT_FOUND;

    p_succ_node = inorder_successor(p_node);
    if(p_succ_node == NULL)
        return(TREE_NO_PREDECESSOR);
    
    *p_succ_data = p_succ_node->data;
    return(SUCCESS);
}

bst_node_t* inorder_successor(bst_node_t* p_node)
{
    bst_node_t* p_run;
    bst_node_t* x;
    bst_node_t* y;

    p_run = p_node;
    if(p_run->right != NULL)
    {
        p_run = p_node->right;
        while (p_run->left != NULL)
            p_run = p_run ->left;
        
        return(p_run);
    }
    else
    {
        x = p_run;
        y = p_run->parent;
        while (y != NULL && x == y->right)
        {
           x = y;
           y = y->parent; 
        }
       return(y); 
    }
}

int bst_postorder_predecessor(struct bst* p_bst, int ext_data, int* p_pred_data)
{

  struct bst_node* p_ext_node = NULL;
  struct bst_node* p_pred_node = NULL;

  p_ext_node = search_node(p_bst, ext_data);
  
  if(p_ext_node == NULL)
    return(TREE_DATA_NOT_FOUND);
  
  p_pred_node = postorder_predecessor(p_ext_node);
  
  if (p_pred_node == NULL)
    return(TREE_NO_PREDECESSOR);
  *p_pred_data = p_pred_node->data;
  return(SUCCESS);
}

struct bst_node* postorder_predecessor(struct bst_node* p_node)
{
  struct bst_node* x;
  struct bst_node* y;
  
  if(p_node->right != NULL) // If it has right child then right node is predecessor. 
    return p_node->right;
  
  if(p_node ->left != NULL && p_node->right == NULL) // If it's right is NULL and has left child then left is predecessor
    return p_node->left;
  /* If it is right child of its parent then its left sibling is prececessor. 
  */
  if(p_node->parent->right == p_node && p_node->parent->left != NULL) 
    return p_node->parent->left;
  /*
  Go uptill you find parent who has left subtree and y is right child of x
  */
  x = p_node;
  y = p_node->parent;
  while(y!=NULL)
  {
     if(y->left != NULL && x == y->right)
        return y->left;
      
      x = y;
      y = y -> parent;
  }
  return NULL; 
}

int bst_preorder_successor(struct bst* p_bst, int ext_data, int* p_pred_data)
{
  struct bst_node* p_ext_node;
  struct bst_node* p_succ_node;

  if(p_bst->p_root_node == NULL)
    return(TREE_EMPTY);
  
  p_ext_node = search_node(p_bst, ext_data);
  if(p_ext_node == NULL)
    return(TREE_DATA_NOT_FOUND);

  p_succ_node = preorder_successor(p_ext_node);
  
  if(p_succ_node == NULL)
    return(TREE_NO_SUCCESSOR);

  *p_pred_data = p_succ_node->data;
  
  return(SUCCESS);

}

struct bst_node* preorder_successor(struct bst_node* p_node)
{
  struct bst_node* x;
  struct bst_node* y;

  if(p_node->left != NULL) // If it has left child then left child is successor
    return(p_node->left);
  else if(p_node->left == NULL && p_node -> right != NULL) // If it do not have left child then right node is successor
    return p_node->right;
  else
  {
    /*
    This will be child node. 
    Go level up until you dont find parent who has right child. And x is left node
    You should be at step where y-> right should not be null and x is left child of y.
    */
    x = p_node;
    y = p_node->parent;
    while(y!=NULL)
    {
      if(y->right != NULL && x == y->left)
        return y->right;
      
      x = y;
      y = y -> parent;
    } 
  }
}

int bst_preorder_predecessor(struct bst* p_bst, int ext_data, int* p_pred_data)
{
  struct bst_node* p_ext_node = NULL;
  struct bst_node* p_pred_node = NULL;

  p_ext_node = search_node(p_bst, ext_data);
  
  if(p_ext_node == NULL)
    return(TREE_DATA_NOT_FOUND);
  
  p_pred_node = preorder_predecessor(p_ext_node);
  
  if (p_pred_node == NULL)
    return(TREE_NO_PREDECESSOR);
  *p_pred_data = p_pred_node->data;
  return(SUCCESS);


}


struct bst_node* preorder_predecessor(struct bst_node* p_node)
{
  struct bst_node* p_run;

  if(p_node -> parent != NULL)// check if it is root node
  {
    if(p_node->parent->left == p_node) // If it is left child then parent is predecessor 
      return p_node->parent;
    if(p_node->parent->left == NULL) // Now it is right child. If its parent's left is NULL then parent is prececessor
      return p_node->parent; 
    /*
    If it is left child and its parent's left subtree is present then
    p_run is parent's left
    step 1: Go to right most node of subtree. (p_run = p_run->right)
    step 2: if right most node has left subtree then p_run = p_run -> left again GOTO step 1.

    In short: Find out right most node who does not have left node. 
    */

    p_run = p_node -> parent -> left;
    
    while (p_run->right != NULL )
    {
      p_run = p_run -> right;
      if(p_run->right == NULL && p_run->left != NULL)
        p_run = p_run->left;
    }
        
    return p_run;
  }
  
}

int bst_postorder_successor(struct bst* p_bst, int ext_data, int* p_pred_data)
{
  struct bst_node* p_ext_node;
  struct bst_node* p_succ_node;

  if(p_bst->p_root_node == NULL)
    return(TREE_EMPTY);
  
  p_ext_node = search_node(p_bst, ext_data);
  if(p_ext_node == NULL)
    return(TREE_DATA_NOT_FOUND);

  p_succ_node = postorder_successor(p_ext_node);
  
  if(p_succ_node == NULL)
    return(TREE_NO_SUCCESSOR);

  *p_pred_data = p_succ_node->data;
  
  return(SUCCESS);

}

bst_node_t* postorder_successor(bst_node_t* p_node)
{
    bst_node_t *x, *y;
    bst_node_t* p_run;

    p_run = p_node;
    if(p_run->parent == NULL)
        return(NULL);
    
    if(p_run->parent->right == p_run)
        return(p_run->parent);
    else
    {
        p_run = p_run->parent;
        while (p_run ->right != NULL)
        {
            p_run = p_run -> right;
            while (p_run->left != NULL)
                p_run = p_run->left; 
        }
        
        return p_run;
    }
}