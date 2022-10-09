#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "rb_tree.h"

int main(void)
{
    rbtree_t* p_rb = NULL;
    status_t status;
    int i;
    data_t arr[50];

    for(i = 0; i<50 ; i++)  
        arr[i] = rand();
    
    p_rb = create_rbtree();
    printf("Tree created \n");
    for(i = 0; i<50; i++)
        assert(rbtree_insert(p_rb, arr[i])==SUCCESS);
    printf("Inserted all records\n");
    
    printf("H = %d\n", rbtree_get_height(p_rb));
    inorder_walk(p_rb);

    for( i = 0; i< 50 ; i = i +1)
    {
        status = rbtree_delete(p_rb, arr[i]);
        assert(status == SUCCESS);
        printf("%d: Removed data: %d\n", i, arr[i]);
        printf("Remaining nodes = %d, H = %d\n", 50 - (i+1), rbtree_get_height(p_rb));
    }

    status = destroy_rbtree(&p_rb);
    assert(status == SUCCESS && p_rb == NULL);

    exit(EXIT_SUCCESS);
}