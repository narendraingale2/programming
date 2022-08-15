#ifndef _GRAPH_H
#define _GRAPH_H
#include<stdio.h>

/* Symbolic constants */
#define SUCCESS 1

#define TRUE 1
#define FALSE 0

#define HLIST_DATA_NOT_FOUND 2
#define VLIST_DATA_NOT_FOUND HLIST_DATA_NOT_FOUND

#define G_VERTEX_EXIST   3
#define G_EDGE_EXIST     4
#define G_INVALID_VERTEX 5
#define G_INVALID_EDGE   6

#define V_LIST_EMPTY     7
#define H_LIST_EMPTY     V_LIST_EMPTY

/* typedef */
typedef struct gaph graph_t;

typedef struct hnode hnode_t;
typedef hnode_t hlist_t;

typedef struct vnode vnode_t;
typedef vnode_t vlist_t;

typedef enum color color_t;

typedef int status_t;
typedef int vertex_t;
typedef int Bool;

typedef struct vptr_node vptr_node_t;
typedef vptr_node vptr_list_t;
typedef vptr_list_t vptr_queue_t;
typedef vptr_list_t vptr_stack_t;
typedef vptr_list_t vptr_priority_queue_t;



struct hnode
{
    vertex_t v;

    double w;
    struct hnode* next;
    struct vnode* prev;
};

struct vnode
{
    vertex_t v;
    
    struct vnode* next;
    struct vnode* prev;
    
    hlist_t* ph_adj_list;
    
    color_t color;
    double priority_field;
    struct vnode* pv_pred;

};

struct graph
{
    int nr_vertex;
    int nr_edges;
    struct vnode* v_list;
};

/* Graph client facing interfaces/apis */

graph_t create_graph(void);
status_t add_vertex(graph_t* g, vertex_t v);
status_t add_edge(graph_t* g, vertex_t v_start, vertex_t v_end);
status_t remove_vertex(graph_t* g, vertex_t v);
status_t remove_edge(graph_t* g, vertex_t v_start, vertex_t v_end);
void print_graph(graph_t* g, const char* msg);
status_t destroy_graph(graph_t** pp_g);

/* Graph- BFS and DFS  */
void dfs(graph_t* g);
void bfs(graph_t* g, vertex_t s);

static void dfs_visit(graph_t* g, vnode_t* pv_u);
static void reset(graph_t* g);

/* shortest path algorithms */
void dijkstra(graph_t* g, vertex_t s);

/* auxillary routine of dijekstra algo*/
static void initialize_single_source(graph_t* g, vnode_t* pv_s);

/* Minimum spanning tree alogirithms */
void prims(graph_t* g, vertex_t r);
void print_mst(graph_t* g, vertex_t r);

/* vertical list management fucntions */
vlist_t* v_create_list();
status_t v_insert_end(vlist_t* pv_list, vertex_t v);

/* Vertical list management auxillary functins */

static void v_generic_insert(vnode_t* pv_start, vnode_t* pv_mid, vnode_t* pv_end);
static void v_generic_delete(vnode_t* p_delete_node);
static vnode_t* v_search_node(vlist_t* pv_list, vertex_t v);
static vnode_t* v_get_node(vertex_t v);

/* vertical list management fucntions */
hlist_t* h_create_list();
status_t h_insert_end(hlist_t* pv_list, vnode_t* v);

/* horizontal list management auxillary functions */
static void h_generic_insert(hnode_t* ph_start, hnode_t* ph_mid, hnode_t* pv_end);
static void h_generic_delete(hnode_t* h_delete_node);
static hnode_t* h_search_node(hlist_t* ph_list, vertex_t v);
static hnode_t* h_get_node(vnode_t* v);

/* vertical node pointer list management interface routines */
vptr_list_t* vptr_create_list();
status_t vptr_insert_end(vptr_list_t pvptr_list, vnode_t* pv_new_node);
status_t vptr_insert_start(vptr_list_t pvptr_list, vnode_t* pv_new_node);
status_t vptr_get_start(vptr_list_t* pvptr_list, vnode_t** ppv_start_node);
status_t vptr_get_end(vptr_list_t* pvptr_list, vnode_t** ppv_end_node);
status_t vptr_pop_start(vptr_list_t* pvptr_list, vnode_t** ppv_start_node);
status_t vptr_pop_end(vptr_list_t* pvptr_list, vnode_t** ppv_end_node);
static vptr_node* vptr_get_node(vnode_t* v);

/* vertical node pointer list auxillary functions */
static void vptr_generic_insert(vptr_node_t* p_beg, vptr_node_t* p_mid, vptr_node_t* p_end);
static void vptr_generic_delete(vptr_node_t* p_delete_node);
static vptr_node_t* vptr_get_node(vnode_t* pv_new_node);
static vptr_node_t* vptr_search_node(vptr_list_t* p_vptr_list, vnode_t* pv);

/* Stack management routines */
vptr_stack_t* vptr_create_stack(void);
status_t vptr_push(vptr_stack_t* p_vptr_stack, vnode_t* pv_new_node);
status_t vptr_pop(vptr_stack_t* p_vptr_stack, vnode_t** ppv_node);
status_t vptr_top(vptr_stack_t* p_vptr_stack, vnode_t** pp_vnode);
Bool vptr_is_stack_empty(vptr_stack_t* pp_vptr_stack);
status_t vptr_destroy_stack(vptr_stack_t** p_vptr_stack);

/* Priority Queue of vertical node pointers */
vptr_priority_queue_t* vptr_create_queue(void);
status_t vptr_priority_enqueue(vptr_priority_queue_t* p_vptr_queue, vnode_t* pv_node);
status_t vptr_priority_dequeue_min(vptr_priority_queue_t* p_vptr_queue, vnode_t** ppv_node);
status_t vptr_priority_peek(vptr_priority_queue_t* p_vptr_queue, vnode_t** ppv_node);
Bool vptr_is_queue_emptry(vptr_priority_queue_t* p_vptr_queue);
status_t vptr_destroy_queue(vptr_priority_queue_t** pp_vptr_stack);

/* auzxillary routines */

void* xcalloc(size_t nr_elements, size_t size_per_element);
#endif
