#ifndef _LIST_H
#define _LIST_H 
typedef struct node node_t;
typedef struct linked_list list_t;
typedef int data_t;
typedef int status_t;
typedef int len_t;
typedef int bool;

#define SUCCESS 1
#define TRUE    1
#define FALSE   0

#define LIST_DATA_NOT_FOUND 2
#define LIST_EMPTY          3

struct node
{
    int data;
    struct node* prev;
    struct node* next;
};

struct linked_list
{
    int size;
    struct node* p_head_node;
};
// Client end interface functions
list_t* create_list();

status_t insert_start(list_t* p_list, data_t new_data);
status_t insert_end(list_t* p_list, data_t new_data);
status_t insert_after(list_t* p_list, data_t s_data, data_t new_data);
status_t insert_before(list_t* p_list, data_t s_data, data_t new_data);

status_t get_start(list_t* p_list, data_t* p_start_data);
status_t get_end(list_t* p_list, data_t* p_end_data);
status_t pop_start(list_t* p_list, data_t* p_start_data);
status_t pop_end(list_t* p_list, data_t* p_end_data);

status_t remove_start(list_t* p_list);
status_t remove_end(list_t* p_list);
status_t remove_data(list_t* p_list, data_t r_data);

bool is_list_empty(list_t* p_list);
bool find_in_list(list_t* p_list, data_t f_data);
bool length_list(list_t* p_list); 

list_t* reverse_list(list_t* p_list);
status_t reverse_list_m(list_t* p_list); 

status_t destroy_list(list_t** p_list);

// Inter list

list_t* concat_list_imm(list_t* p_list1, list_t* p_list2);
status_t* concat_list(list_t* p_list1, list_t* p_list2);


// List internal functions
static void generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end);
static void generic_delete(node_t* p_delete);
static node_t* get_node(data_t data);
static node_t* search_node(node_t* p_head, data_t s_data);
static void* xcalloc(size_t nr_elements, size_t size_per_element);
#endif
