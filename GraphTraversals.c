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
// STACK AND ITS OPERATIONS
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

int l_display(int size, int* arr){ //Temp

	for(;size > 0; --size, ++arr) printf("%d ", *arr);
	printf("End.\n");
}

//--------------------------------
// GRAPH AND ITS OPERATIONS
typedef struct Graph{

	bool adj_mat[MAXVERTICES][MAXVERTICES];
	int noof_verts;
	
} Graph;

void g_constructor(Graph *graph){

	graph->noof_verts = 0;
	memset(&graph->adj_mat[0][0], 0, sizeof(bool) * MAXVERTICES * MAXVERTICES);

	/*
	int i, j;
	for (i = 0; i < MAXVERTICES; ++i)
	for (j = 0; j < MAXVERTICES; ++j)
			graph->adj_mat[i][j] = 0;*/
}

bool g_add_vert(Graph* graph){

	graph->noof_verts++;
	if (graph->noof_verts == MAXVERTICES){

		graph->noof_verts--; 
		return 0;
	}
	return 1;
}

bool g_add_edge(Graph *graph, int one, int two){

	if (one == two || 
		one >= graph->noof_verts || 
		two >= graph->noof_verts){

		return 0;
	}
	graph->adj_mat[one][two] = graph->adj_mat[two][one] = 1; 
	return 1;
}

void g_print_adj_mat(Graph *graph){

	int i, j;
	for (i = 0; i < graph->noof_verts; ++i, printf("\n"))
	for (j = 0; j < graph->noof_verts; ++j)
	printf("%d ", graph->adj_mat[i][j]);
}

void breadth_first_traversal(Graph* graph){

	Queue que;
	q_constructor(&que);
	#define track_queue() l_display((q_isempty(&que))? 0: que.rear - que.front + 1, que.arr + que.front	); //
	track_queue();
	int visited[graph->noof_verts];
	for (int i = 0; i < graph->noof_verts; visited[i++] = 0);
	
	int cur;

	while(1){

		if (q_isempty(&que)){

			cur = l_find(graph->noof_verts, visited, 0);
			//printf("found cur at %d\n", cur);//
			if (cur == -1) break;
			else{

				printf("\n%d ", cur);
				visited[cur] = 1;
				//printf("Visited: ");//
				//l_display(graph->noof_verts, visited);//
			}
		}
		else{

			cur = q_dequeue(&que);
			//track_queue();//
			printf("%d ", cur);
		}

		for (int i = 0; i < graph->noof_verts; ++i){ // Can be optimized?

			if (visited[i] != 1 && graph->adj_mat[i][cur]){

				q_enqueue(&que, i);
				visited[i] = 1;
				//printf("Visited: ");//
				//l_display(graph->noof_verts, visited);//
				//printf("\n");//

				//printf(" cur = %d i = %d\n", cur, i);//
				//track_queue();//	
			}
		}
	}
}

void main(){

	Graph graph;
	g_constructor(&graph);
	g_print_adj_mat(&graph);
	breadth_first_traversal(&graph);
	
}
/*

	g_add_vert(&graph);
	g_add_vert(&graph);
	g_add_vert(&graph);
	g_add_vert(&graph);
	g_add_vert(&graph);
	g_add_vert(&graph);
	g_add_vert(&graph);
	g_add_vert(&graph);
	g_add_vert(&graph);
	g_add_vert(&graph);
	g_add_vert(&graph);
	g_add_vert(&graph);
	printf("%d\n", graph.noof_verts);//
	g_add_edge(&graph, 0, 3);
	g_add_edge(&graph, 9, 3);
	g_add_edge(&graph, 4, 3);
	g_add_edge(&graph, 2, 3);
	g_add_edge(&graph, 1, 4);
	g_add_edge(&graph, 1, 2);
	g_add_edge(&graph, 2, 5);
	g_add_edge(&graph, 5, 6);
	g_add_edge(&graph, 5, 7);
	g_add_edge(&graph, 2, 7);
	g_add_edge(&graph, 2, 8);
	g_add_edge(&graph, 5, 8);
	g_add_edge(&graph, 7, 8);
	g_add_edge(&graph, 10, 11);
*/
