#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "rb_tree.h"

int main(void)
{
    rbtree_t* p_rb = NULL;
    status_t status;
    int i;
//    data_t arr[5];

  //  for(i = 0; i<50 ; i++)  
  //      arr[i] = rand();
    
    data_t arr[10]= {10, 23, 2, 11, 12, 24, 4, 6, 9, 77} ;
    p_rb = create_rbtree();
    printf("Tree created \n");
    for(i = 0; i<10; i++)
    {   
        printf("Inserting %d\n",arr[i]);
        assert(rbtree_insert(p_rb, arr[i])==SUCCESS);
    }
    printf("Inserted all records\n");
    
    printf("H = %d\n", rbtree_get_height(p_rb));
    inorder_walk(p_rb);

    for( i = 0; i< 10 ; i = i +1)
    {
        status = rbtree_delete(p_rb, arr[i]);
        assert(status == SUCCESS);
        printf("%d: Removed data: %d\n", i, arr[i]);
        printf("Remaining nodes = %d, H = %d\n", 10 - (i+1), rbtree_get_height(p_rb));
    }

    status = destroy_rbtree(&p_rb);
    assert(status == SUCCESS && p_rb == NULL);
    printf("Tree destroyed successfully");

    exit(EXIT_SUCCESS);
}