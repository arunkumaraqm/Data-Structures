#include <stdio.h>
#include <stdbool.h> // For bool data type
#include <string.h> // For memset 
#define MAXVERTICES 100

//----------------------
// QUEUE AND ITS OPERATIONS
typedef struct Queue
{
	int front, rear;
	int arr[MAXVERTICES];
} Queue;

void q_constructor(Queue* que){

	que->front = que->rear = -1;
}
void q_enqueue(Queue* que, int new_element)
{
    if (que->front == - 1) que->front = 0;
    que->arr[++que->rear] = new_element;   
} 
 
int q_dequeue(Queue* que)
{
    int temp = que->arr[que->front++];
	if (que->front > que->rear) que->front = que->rear = -1;
	return temp;
}

bool q_isempty(Queue *que){

	return (que->front == -1);
}

//-----------------------
// STACK AND ITS OPERATIONS - IGNORE ALL OF THIS
typedef struct Stack
{
	int top;
	int arr[MAXVERTICES];
} Stack;

void s_constructor(Stack* stack){

	stack->top = -1;
}

void s_push(Stack* stack, int new_element)
{
	stack->arr[++stack->top] = new_element;	
}

int s_pop(Stack* stack)
{
	return stack->arr[stack->top--];
}

bool s_isempty(Stack* stack){

	return (stack->top == -1);
}
//--------------------------------
// LIST / ARRAY AND ITS OPERATIONS

int l_find(int size, int* arr, int search_elem){ // Linear search using sentinel

	if (size == 0) return -1;
	int i, temp = arr[size - 1];
	arr[size - 1] = search_elem;
	
	for (i = 0; arr[i] != search_elem; ++i);
	if (i == size - 1){

		if (temp == search_elem) return size - 1;
		else return -1;
	}
	else return i;
}
/*
int l_display(int size, int* arr){ //Temp

	for(;size > 0; --size, ++arr) printf("%d ", *arr);
	printf("End.\n");
}*/

//--------------------------------
// GRAPH AND ITS OPERATIONS
typedef struct Graph{

	bool adj_mat[MAXVERTICES][MAXVERTICES];
	int noof_verts;
	
} Graph;

void g_constructor(Graph *graph){

	graph->noof_verts = 0;
	memset(&graph->adj_mat[0][0], 0, sizeof(bool) * MAXVERTICES * MAXVERTICES); // Sets all elements to zero. However, it is a risky function for non char data types; would not advise usage. 
}

// Adds one vertex
bool g_add_vert(Graph* graph){

	graph->noof_verts++;
	if (graph->noof_verts == MAXVERTICES){

		graph->noof_verts--; 
		return 0;
	}
	return 1;
}

// Adds one edge between two given vertices
bool g_add_edge(Graph *graph, int one, int two){

	if (one == two || // Self loops shouldn't exist
		one >= graph->noof_verts || // Checking whether vertex is present in the graph
		two >= graph->noof_verts ||
		graph->adj_mat[one][two] == 1) // Parallel edges shouldn't exist
	{

		return 0;
	}

	// 1 in the adjacency matrix signifies presence of an edge
	graph->adj_mat[one][two] = graph->adj_mat[two][one] = 1; 
	return 1;
}

// Prints adjacency matrix - this function isn't used anywhere
void g_print_adj_mat(Graph *graph){

	int i, j;
	for (i = 0; i < graph->noof_verts; ++i, printf("\n"))
	for (j = 0; j < graph->noof_verts; ++j)
	printf("%d ", graph->adj_mat[i][j]);
}

// Traverses through the graph using BFS
void breadth_first_traversal(Graph* graph){

	Queue que;
	q_constructor(&que);

	// Creating and initalizing visited array to all zeros
	int visited[graph->noof_verts];
	for (int i = 0; i < graph->noof_verts; visited[i++] = 0);
	
	int cur;

	while(true){ 

		// If queue is empty, find the next connected component in the graph.
		// If there is no other connected component, graph has been fully traversed.
		if (q_isempty(&que)){

			cur = l_find(graph->noof_verts, visited, 0);
			
			if (cur == -1) break;
			else{

				printf("\n%d ", cur); // Starting traversal here
				visited[cur] = 1;
			}
		}

		// If the queue isn't empty, dequeue and print vertex label.
		else{

			cur = q_dequeue(&que);
			printf("%d ", cur);
		}

		// Add that current vertex's adjacent vertices to the queue and mark them as visited.
		for (int i = 0; i < graph->noof_verts; ++i){ 

			if (visited[i] != 1 && graph->adj_mat[i][cur]){

				q_enqueue(&que, i);
				visited[i] = 1;
			}
		}
	}
	printf("\n");
}
	
void recursive_depth_first_traversal(Graph *graph, int start, int* visited){

	printf("%d ", start);

	visited[start] = 1;

	for (int i = 0; i < graph->noof_verts; ++i){ 

		if (graph->adj_mat[i][start] && !visited[i]){

			// Recursive DFS on each of the current vertex's adjacent vertices.
			recursive_depth_first_traversal(graph, i, visited);	
		}
	}
}

// Traverses the graph using DFS.
void depth_first_traversal(Graph *graph){

	int visited[graph->noof_verts], cur;
	for (int i = 0; i < graph->noof_verts; visited[i++] = 0);

	
	// Every iteration traverses one connected component of the graph.
	while(true){

		cur = l_find(graph->noof_verts, visited, 0);
		if (cur == -1) break; // No more connected components
		else recursive_depth_first_traversal(graph, cur, visited);	
		printf("\n");	
	}
}

void main(){

	Graph graph;
	g_constructor(&graph);
	char choice;

	do{

		scanf(" %c", &choice);
		switch(choice){

		case 'a': {	
					int noof_verts;
					scanf("%d", &noof_verts);
					for (; noof_verts > 0; --noof_verts) g_add_vert(&graph); 
				} break;
				
		case 'b': {
					int one, two;
					scanf("%d %d", &one, &two);
					if (g_add_edge(&graph, one, two) == 0) 
						printf("Multigraphs are not accomodated.\n");
				} break;
				
		case 'c': printf("BFT:\n"); breadth_first_traversal(&graph); break;
				
		case 'd': printf("DFT:\n"); depth_first_traversal(&graph); break;

		default: choice = 0;
		
		}

	}while(choice != 0);
}
/*
#
a 1
c 
d
z

bfs: 0
dfs: 0

#
a 4
c
d
z

bfs: 0 \n 1 \n 2 \n 3
dfs: the same
#
a 3
b 0 1
c
d
z

bfs: 0 1 \n 2
dfs: 0 1 \n 2

#
a 5
b 1 2
b 2 3
b 3 4
b 4 1
c
d 
z

bfs: 0 \n 1 2 4 3
dfs: 0 \n 1 2 3 4

#
a 5
b 0 1
b 0 3
b 0 2 
b 1 4
b 4 3
b 2 3
c
d 
z

bfs: 0 1 2 3 4 
dfs: 0 1 4 3 2

#
a 5 
b 0 1
b 0 3
b 1 2
b 3 2
b 2 4
b 3 4
c
d
z

bfs: 0 1 3 2 4
dfs: 0 1 2 3 4

a 12
b 0 3	
b 9 3
b 4 3
b 2 3
b 1 4
b 1 2
b 2 5
b 5 6
b 5 7
b 2 7
b 2 8
b 5 8
b 7 8
b 10 11
c
d
z

bfs: 0 3 2 4 9 1 5 7 8 6 \n 10 11
dfs:0 3 2 1 4 5 6 7 8 9 \n 10 11
*/
