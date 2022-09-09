#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"bst.h"

int main(void)
{
    bst_t* p_bst = NULL;
    int data[] = {100, 150, 75, 200, 125, 85, 50, 65, 130};
    int data_np[] = {-100, 2004, 3453, -45635, 3456, 363535};
    int i;
    int status;
    
    p_bst = create_bst();

    status = bst_max(p_bst);

    if(status == TREE_EMPTY)
        printf("bst_max: Tree is empty \n");
    
    status = bst_min(p_bst);
    if(status == TREE_EMPTY)
        printf("bst_min: Tree is empty \n");
    
    for(i=0; i<sizeof(data)/sizeof(int); i++)
    {
        status = bst_insert(p_bst, data[i]);
        assert(status == SUCCESS);
    }
    printf("Testcase implemented .......");
    return(SUCCESS);

}