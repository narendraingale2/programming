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
    unsigned long long int len = 0;
    
    p_bst = create_bst();
    printf("Tree has been created successfully\n");
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

    status = bst_max(p_bst);
    printf("Max = %d\n", status);

    status =  bst_min(p_bst);
    printf("Min = %d\n", status);
    preorder_r(p_bst);
    postorder_r(p_bst);
    inorder_r(p_bst);

    status = bst_search(p_bst, 85);
    assert(status == SUCCESS);
    status = bst_search(p_bst, 80);
    assert(status == TREE_DATA_NOT_FOUND);

    status = bst_remove(p_bst, 85);
    assert(status == SUCCESS);
    status = bst_search(p_bst, 85);
    assert(status == TREE_DATA_NOT_FOUND);
    inorder_r(p_bst);

    status = bst_insert(p_bst, 3);
    assert(status == SUCCESS);
    status = bst_search(p_bst, 3);
    assert(status == SUCCESS);
    inorder_r(p_bst);

    len = bst_get_nr_elements(p_bst);
    printf("Length of tree is %llu \n", len);

    status = bst_remove(p_bst, 3);
    assert(status == SUCCESS);
    status = bst_search(p_bst, 3);
    assert(status == TREE_DATA_NOT_FOUND);
    printf("Removal of 3 test case successful\n");
    
    status = bst_insert(p_bst, 85);
    assert(status == SUCCESS);
    status = bst_search(p_bst, 85);
    assert(status == SUCCESS);
    printf("Addition of 85 test case successful\n");

    for(i=0; i<sizeof(data)/sizeof(int); i++)
    {
        status = bst_remove(p_bst, data[i]);
        assert(status == SUCCESS);
    }
    printf("Remove all test case successful\n");
    status = bst_is_empty(p_bst);
    assert(status == TRUE);
    printf("Isempty test case successful\n");

    len = bst_get_nr_elements(p_bst);
    assert(len == 0);
    printf("Length test case successful\n");

    for(i=0; i<sizeof(data)/sizeof(int); i++)
    {
        status = bst_insert(p_bst, data[i]);
        assert(status == SUCCESS);
    }
    printf("Added back all the elements. Trying destroy now \n");
    printf("Calling non recursive in order walk\n");
    inorder(p_bst);
    printf("Calling pre-order walk\n");
    preorder(p_bst);
    preorder_r(p_bst);
    printf("Calling post-order walk\n");
    postorder(p_bst);
    postorder_r(p_bst);
    destroy_bst(&p_bst);
    assert(p_bst == NULL);
    printf("Tree has been destroyed successfully\n");
    printf("Testcase implemented .......\n");
    return(SUCCESS);

}