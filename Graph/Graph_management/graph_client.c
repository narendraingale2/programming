#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"graph.h"

struct edge{
    vertex_t v_start;
    vertex_t v_end;
    double w;
};

void test_graph_management(void);
void test_dfs(void);

int main(void)
{
    test_graph_management();
    test_dfs();
    return(EXIT_SUCCESS);
}

void test_graph_management(void)
{
    graph_t* g = NULL;
    int i;
    vertex_t v;
    int status;

    struct edge E[] = 	{
			{1, 6, 2.0}, {1, 2, 1.0}, {2, 7, 5.0}, {2, 3, 2.0}, 
			{6, 7, 3.0}, {5, 7, 2.0}, {7, 3, 1.0}, {7, 8, 3.0}, 
			{3, 8, 3.0}, {5, 8, 4.0}, {5, 4, 2.0}, {3, 4, 1.0} 
		}; 
    printf("===============Testing Graph management.=====================\n");
    g = create_graph(); 
    printf("Graph created successfully.... \n");
    printf("Adding vertices...\n");
    for(v = 1; v <= 8; v++)
    {
        add_vertex(g,v);
    }
    printf("Added vertices. \n");

    print_graph(g,"Graph after adding vertex");

    printf("Adding edges....\n");
    for(i=0; i<12; i++)
    {
        status = add_edge(g,E[i].v_start, E[i].v_end, E[i].w);
        assert(status == SUCCESS);
    }
    printf("Edges added successfully.......");
    print_graph(g, "Printing graph after adding edges...");

    printf("Testing remove edge(1,6)....\n");
    status = remove_edge(g,1,6);
    assert(status == SUCCESS);
    printf("Edge removed successfully...........\n");
    print_graph(g, "Printing graph after removing edge (1,6)...");

    printf("Testing remove edge(1,6)....\n");
    status = remove_edge(g,5,7);
    assert(status == SUCCESS);
    printf("Edge removed successfully...........\n");
    print_graph(g, "Printing graph after removing edge (5,7)...");

    printf("Testing removal of non existing edge(1,4)....\n");
    status = remove_edge(g, 1, 4);

    assert(status == G_INVALID_EDGE);
    print_graph(g, "Printing graph after removing edge (1,4)");

    printf("Testing removal of non existing vertex 9\n");
    status = remove_vertex(g,9);
    assert(status == G_INVALID_VERTEX);

    printf("Testing removal of vertex 1\n");
    status = remove_vertex(g,1);
    assert(status == SUCCESS);
    print_graph(g,"After removing vertex 1");

    printf("Testing removal of vertex 2\n");
    status = remove_vertex(g,2);
    assert(status == SUCCESS);

    print_graph(g,"After removing vertex 2");
    destroy_graph(&g);
    printf("Graph destroyed sucessfully...\n");
    printf("==========Graph management testing completed successfull======\n");
}

void test_dfs(void)
{
    graph_t* g = NULL;
    int i;
    vertex_t v;
    int status;

    struct edge E[] = 	{
			{1, 6, 2.0}, {1, 2, 1.0}, {2, 7, 5.0}, {2, 3, 2.0}, 
			{6, 7, 3.0}, {5, 7, 2.0}, {7, 3, 1.0}, {7, 8, 3.0}, 
			{3, 8, 3.0}, {5, 8, 4.0}, {5, 4, 2.0}, {3, 4, 1.0} 
		}; 
    printf("========== Testing DFS ========================================\n");
    g = create_graph(); 
    printf("Graph created successfully.... \n");
    printf("Adding vertices...\n");
    for(v = 1; v <= 8; v++)
    {
        add_vertex(g,v);
    }
    printf("Added vertices. \n");

    print_graph(g,"Graph after adding vertex");

    printf("Adding edges....\n");
    for(i=0; i<12; i++)
    {
        status = add_edge(g,E[i].v_start, E[i].v_end, E[i].w);
        assert(status == SUCCESS);
    }
    printf("Edges added successfully.......\n");
    print_graph(g, "printing graph after adding edges");
    printf("========Visiting DFS now ==============\n");
    dfs(g);
    destroy_graph(&g);
    
}