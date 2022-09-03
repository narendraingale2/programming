#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<math.h>
#include"graph.h"
#include"vptr_list.h"



graph_t* create_graph(void)
{
    vlist_t* pv_list = NULL;
    graph_t* g = NULL;

    g = (graph_t*)xcalloc(1,sizeof(graph_t));
    g->nr_edges = 0;
    g->nr_vertex = 0;
    g->v_list = v_create_list();

    return(g);
}

status_t add_vertex(graph_t* g, vertex_t v)
{
    vlist_t* pv_list = NULL;
    pv_list = g->v_list;
    v_insert_end(pv_list, v);
    
    g->nr_vertex += 1;
    return(SUCCESS);
}

status_t add_edge(graph_t* g, vertex_t v_start, vertex_t v_end, double w)
{
    vlist_t* pv_list = NULL;
    vnode_t* pv_start = NULL;
    vnode_t* pv_end = NULL;
    hnode_t* ph_start_end = NULL;
    hnode_t* ph_end_start = NULL;

    pv_list = g->v_list;

    pv_start = v_search_node(pv_list, v_start);
    if(pv_start == NULL)
        return(G_INVALID_VERTEX);
    
    pv_end = v_search_node(pv_list, v_end);
    if(pv_end == NULL)
        return(G_INVALID_VERTEX);

    ph_start_end = h_search_node(pv_end->ph_adj_list, v_start);
    ph_end_start = h_search_node(pv_start->ph_adj_list, v_end);

    if(ph_start_end != NULL && ph_end_start != NULL)
        return(G_EDGE_EXIST);

    if((ph_start_end != NULL) ^ (ph_end_start != NULL))
        return(G_CORRUPTED);
    
    h_insert_end(pv_start->ph_adj_list, pv_end, w);
    h_insert_end(pv_end->ph_adj_list, pv_start, w);
    g->nr_edges += 1;
    
    return(SUCCESS);
}

status_t remove_vertex(graph_t* g, vertex_t v)
{
    vnode_t* p_vdelete_node = NULL;
    hlist_t* p_hlist = NULL;
    hnode_t* p_hrun = NULL;
    hnode_t* p_hrun_next = NULL;
    hnode_t* p_hdelete_node = NULL;
    vnode_t* p_vnode_search = NULL;

    p_vdelete_node = v_search_node(g->v_list, v);
    if(p_vdelete_node == NULL)
        return(G_INVALID_VERTEX);

    p_hlist = p_vdelete_node ->ph_adj_list;

    for(p_hrun = p_hlist->next; p_hrun != p_hlist; p_hrun = p_hrun_next)
    {
        p_hrun_next = p_hrun ->next;
        p_vnode_search = p_hrun -> pv_node;
        p_hdelete_node = h_search_node(p_hrun->pv_node->ph_adj_list, v);
        h_generic_delete(p_hdelete_node);
        free(p_hrun);
        g->nr_edges -= 1;
    }
    free(p_hlist);
    v_generic_delete(p_vdelete_node);
    g->nr_vertex -= 1;
    return(SUCCESS);
}

status_t remove_edge(graph_t* g, vertex_t v_start, vertex_t v_end)
{
    
    vnode_t* pv_node_start;
    vnode_t* pv_node_end;

    hnode_t* ph_start_end_node;
    hnode_t* ph_end_start_node;

    pv_node_start = v_search_node(g->v_list, v_start);
    
    if(pv_node_start == NULL)
        return(G_INVALID_VERTEX);

    pv_node_end = v_search_node(g->v_list, v_end);
    if(pv_node_end == NULL)
        return(G_INVALID_VERTEX);

    ph_start_end_node = h_search_node(pv_node_end->ph_adj_list, v_start);
    ph_end_start_node = h_search_node(pv_node_start->ph_adj_list, v_end);

    if(ph_start_end_node == NULL && ph_end_start_node == NULL)
        return(G_INVALID_EDGE);
    
    if((ph_end_start_node != NULL) ^ (ph_start_end_node != NULL))
        return(G_CORRUPTED);

    
    h_generic_delete(ph_end_start_node);
    h_generic_delete(ph_start_end_node);
    g->nr_edges -= 1;

    return(SUCCESS);
}

void print_graph(graph_t* g, const char* msg)
{
    vnode_t* pv_run = NULL;
    hnode_t* ph_run = NULL;

    puts(msg);
    printf("Number of vertices=%d and Number of edges = %d\n",g->nr_vertex, g->nr_edges);
    for(pv_run = g->v_list->next; pv_run != g->v_list; pv_run = pv_run->next)
    {
        printf("[%d]\t->\t",pv_run->v);
        for(ph_run = pv_run->ph_adj_list->next; ph_run != pv_run->ph_adj_list; ph_run = ph_run->next)
        {
           printf("[%d]<->", ph_run->pv_node->v);
        }
        puts("[END]");
    }
}

status_t destroy_graph(graph_t** pp_g)
{

    vnode_t* pv_run = NULL;
    vnode_t* pv_run_next = NULL;
    hnode_t* ph_run = NULL;
    hnode_t* ph_run_next = NULL;
    
    for(pv_run = (*pp_g)->v_list->next; pv_run != (*pp_g)->v_list; pv_run = pv_run_next )
    {
        pv_run_next = pv_run -> next;
        for(ph_run = pv_run->ph_adj_list->next; ph_run != pv_run->ph_adj_list; ph_run = ph_run_next)        
        {
            ph_run_next = ph_run -> next;
            free(ph_run);
        }
        free(pv_run->ph_adj_list);
        free(pv_run);
    }
    free((*pp_g)->v_list);
  free(*pp_g);
  pp_g = NULL;

  return(SUCCESS);

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
    return(NULL);
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

    return(p_new_node);
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

void reset(graph_t* g)
{
    vnode_t* pv_run = NULL;
    for(pv_run = g->v_list->next; pv_run != g->v_list->next; pv_run = pv_run->next )
        pv_run->color = WHITE;
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
            if(ph_run->pv_node->v == v)
            {
                return(ph_run);
            }
    }

    return(NULL);
}

static hnode_t* h_get_node(vnode_t* v, double w)
{
    hnode_t* p_new_node = NULL;
    p_new_node = (hnode_t*)xcalloc(1,sizeof(hnode_t));
    p_new_node -> pv_node = v;
    p_new_node -> next = NULL;
    p_new_node -> prev = NULL;
    p_new_node -> w = w;

    return(p_new_node);
}

void* xcalloc(size_t nr_elements, size_t size_per_element)
{
    void* p = NULL;

    p = calloc(nr_elements, size_per_element);
    if(p==NULL)
    {
        fprintf(stderr, "Unable to allocate memory: OutOf virtual address");
        exit(EXIT_FAILURE);
    }
    return(p);
}


void dfs(struct graph* g)
{
    vnode_t* pv_run = NULL;
    reset(g);

    printf("Starting DFS ....\n");
    printf("[START]->");
    for(pv_run = g->v_list->next; pv_run != g->v_list; pv_run = pv_run->next)
    {
        if(pv_run->color == WHITE)
            dfs_visit(pv_run);
    }
    printf("[END]\n");
}

void dfs_visit(vnode_t* pv_u)
{
    hnode_t* ph_run = NULL;

    printf("[%d]<->", pv_u->v);
    pv_u->color = GRAY;

    for(ph_run = pv_u->ph_adj_list->next; ph_run != pv_u->ph_adj_list; ph_run = ph_run->next)
    {
        if(ph_run->pv_node->color == WHITE)
            dfs_visit(ph_run->pv_node);
    }
    pv_u->color = BLACK;

}

int bfs(graph_t* g, vertex_t s)
{
    vnode_t* pv_run = NULL;
    hnode_t* ph_run = NULL;
    vptr_queue_t* p_queue = NULL;
    status_t status = 0;

    reset(g);

    p_queue = vptr_create_queue();
    pv_run = v_search_node(g->v_list, s);
    pv_run->color = GRAY;
    if(pv_run == NULL)
        return(G_INVALID_VERTEX);
    status = vptr_enqueue(p_queue,pv_run);
    assert(status == SUCCESS);
    status = vptr_is_queue_empty(p_queue);
    printf("[START]<->");
    while (vptr_is_queue_empty(p_queue) != TRUE)
    {
    
       pv_run = NULL;
       status = vptr_dequeue(p_queue,&pv_run);
       assert(status == SUCCESS);
       
       printf("[%d]<->", pv_run->v);
       for(ph_run = pv_run->ph_adj_list->next; ph_run != pv_run->ph_adj_list; ph_run = ph_run->next)
       {
        if(ph_run->pv_node->color == WHITE)
        {
            ph_run->pv_node->color = GRAY;
            status = vptr_enqueue(p_queue, ph_run->pv_node);
            assert(status == SUCCESS);
        }
       }
    }
    free(p_queue);
    printf("[END]\n");
}

void dijkstra(graph_t* g, vertex_t s)
{
    printf("Working on dijkstra alog.........\n");
}