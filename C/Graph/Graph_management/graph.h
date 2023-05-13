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
#define G_CORRUPTED      7 

#define V_LIST_EMPTY     8
#define H_LIST_EMPTY     V_LIST_EMPTY

/* typedef */
typedef struct graph graph_t;

typedef struct hnode hnode_t;
typedef hnode_t hlist_t;

typedef struct vnode vnode_t;
typedef vnode_t vlist_t;

typedef enum color color_t;

typedef int status_t;
typedef int vertex_t;
typedef int Bool;

enum color{
	WHITE = 0, 
	GRAY, 
	BLACK
}; 

struct hnode
{
    vnode_t* pv_node;

    double w;
    struct hnode* next;
    struct hnode* prev;
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

graph_t* create_graph(void);
status_t add_vertex(graph_t* g, vertex_t v);
status_t add_edge(graph_t* g, vertex_t v_start, vertex_t v_end,double w);
status_t remove_vertex(graph_t* g, vertex_t v);
status_t remove_edge(graph_t* g, vertex_t v_start, vertex_t v_end);
void print_graph(graph_t* g, const char* msg);
status_t destroy_graph(graph_t** pp_g);

/* Graph- BFS and DFS  */
void dfs();
void dfs_visit(vnode_t* u);
int bfs(graph_t* g, vertex_t s);

static void reset(graph_t* g);

/* shortest path algorithms */
status_t dijkstra(graph_t* g, vertex_t s);

/* auxillary routine of dijekstra algo*/
static void initialize_single_source(graph_t* g, vnode_t* pv_s);
static void relax(vnode_t* u, vnode_t* v, double w);
void print_shortest_path(graph_t *g, vnode_t* pv_node);
void print_all_shortest_path(graph_t* g);

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
status_t h_insert_end(hlist_t* pv_list, vnode_t* v, double w);

/* horizontal list management auxillary functions */
static void h_generic_insert(hnode_t* ph_start, hnode_t* ph_mid, hnode_t* ph_end);
static void h_generic_delete(hnode_t* h_delete_node);
static hnode_t* h_search_node(hlist_t* ph_list, vertex_t v);
static hnode_t* h_get_node(vnode_t* v, double w);


/* auzxillary routines */

void* xcalloc(size_t nr_elements, size_t size_per_element);
#endif