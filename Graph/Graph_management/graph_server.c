#include<stdio.h>
#include<assert.h>
#include"graph.h"
#include<stdlib.h>
#include<math.h>



graph_t create_graph(void);
status_t add_vertex(graph_t* g, vertex_t v);
status_t add_edge(graph_t* g, vertex_t v_start, vertex_t v_end);
status_t remove_vertex(graph_t* g, vertex_t v);
status_t remove_edge(graph_t* g, vertex_t v_start, vertex_t v_end);
void print_graph(graph_t* g, const char* msg);
status_t destroy_graph(graph_t** pp_g)
{

}

/* vertical list management fucntions */
vlist_t* v_create_list()
{
    vlist_t* pv_list = NULL;

    pv_list = v_get_node(-1);
    pv_list->next = pv_list;
    pv_list->prev = pv_list;

    pv_list->ph_adj_list = NULL;
    return pv_list;
}

status_t v_insert_end(vlist_t* pv_list, vertex_t v)
{
    v_generic_insert(pv_list->prev, v_get_node(v),pv_list);
    return(SUCCESS);
}

/* Vertical list management auxillary functins */

static void v_generic_insert(vnode_t* pv_start, vnode_t* pv_mid, vnode_t* pv_end)
{
    pv_mid ->next = pv_end;
    pv_mid->prev = pv_start;
    pv_start -> next = pv_mid;
    pv_end -> prev = pv_mid;
}

static void v_generic_delete(vnode_t* pv_delete_node)
{
    pv_delete_node->next->prev = pv_delete_node->prev;
    pv_delete_node->prev->next = pv_delete_node->next;
    free(pv_delete_node);
}

static vnode_t* v_search_node(vlist_t* pv_list, vertex_t v)
{
    vnode_t* pv_run = NULL;
    for(pv_run = pv_list->next; pv_run != pv_list; pv_run = pv_run->next)
    {
        if(pv_run->v ==v)
        {
            return(pv_run);
        }
    }
}

static vnode_t* v_get_node(vertex_t v)
{
    vnode_t* p_new_node = NULL;

    p_new_node = (vnode_t*)xcalloc(1,sizeof(vnode_t));
    p_new_node->v = v;
    p_new_node->color = WHITE;
    p_new_node->priority_field = INFINITY;
    p_new_node->pv_pred = NULL;
    p_new_node->ph_adj_list = h_create_list();
}

/* vertical list management fucntions */
hlist_t* h_create_list()
{
    hlist_t* ph_list;
    ph_list = h_get_node(NULL, -1);
    ph_list->next = ph_list;
    ph_list->prev = ph_list;
    return(ph_list);
}

status_t h_insert_end(hlist_t* pv_list, vnode_t* v, double w)
{
    h_generic_insert(pv_list->prev,h_get_node(v,w), pv_list);
    return(SUCCESS);
}

/* horizontal list management auxillary functions */
static void h_generic_insert(hnode_t* ph_start, hnode_t* ph_mid, hnode_t* ph_end)
{
    ph_mid->next = ph_end;
    ph_mid->prev = ph_start;
    ph_start->next = ph_mid;
    ph_end->prev = ph_mid;
}

static void h_generic_delete(hnode_t* ph_delete_node)
{
    ph_delete_node->next->prev = ph_delete_node->prev;
    ph_delete_node->prev->next = ph_delete_node->next;
    free(ph_delete_node);
}

static hnode_t* h_search_node(hlist_t* ph_list, vertex_t v)
{
    hnode_t* ph_run = NULL;
    for(ph_run = ph_list->next; ph_run != ph_list; ph_run = ph_run -> next)
    {
            if(ph_run -> v == v)
            {
                return(ph_run);
            }
    }

    return(ph_run);
}

static hnode_t* h_get_node(vnode_t* v, double w)
{
    hnode_t* p_new_node = NULL;
    p_new_node = (hnode_t*)xcalloc(1,sizeof(vnode_t));
    p_new_node -> v = v;
    p_new_node -> next = NULL;
    p_new_node -> prev = NULL;
    p_new_node -> w = w;
}

void* xcalloc(size_t nr_elements, size_t size_per_element)
{
    void* p = NULL;

    p = calloc(nr_elements, size_per_element);
    if(p==NULL)
    {
        sprintf(stderr, "Unable to allocate memory: OutOf virtual address");
        exit(EXIT_FAILURE);
    }
    return(p);
}