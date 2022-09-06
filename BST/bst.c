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

