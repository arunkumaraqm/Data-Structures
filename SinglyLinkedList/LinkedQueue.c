// Linked List implementation of Queue data structure

#include <stdio.h>
#include <stdlib.h> // For malloc()

int read_element(){
	
	int element;
	scanf("%d", &element);
	return element;
}

struct Node{

	int data;
	struct Node* next;	
};

// Aliasing struct Node* to MyNode
typedef struct Node* MyNode;

typedef struct List{
	
	MyNode front;
	MyNode rear;
}List;

void display(List* list){ // Added a list empty condition and changed display pattern
	
	// Checks if list is empty
	if(!list->front){
	
		printf("Empty.\n");
		return;
	}
	
	MyNode cur;
	
	for (cur = list->front; cur != NULL; cur = cur->next){
	
		printf("%d ", cur->data);
	}
	printf("\n");
}

void constructor(List* list){
	
	list->front = list->rear = NULL;
}


// To free all memory at the end of main
void destructor(List* list){
	
	MyNode previous_node;
	
	while (list->front != NULL){
		
		previous_node = list->front;
		list->front = (list->front)->next;
		free(previous_node);
	}
	
	list->rear = NULL;
}
void enqueue(List* list){

	MyNode new_element = malloc(sizeof new_element);
	if (new_element == NULL){
	
		printf("\nQueue is full because heap memory allocation failed.");
		return;
	}
	new_element->data = read_element();
	new_element->next = NULL;
	
	if(!list->rear){
		list->front = list->rear = new_element;
	}
	else{
		list->rear->next = new_element;
		list->rear = list->rear->next;
	}
}

void dequeue(List* list){

	// Checks if list is empty
	if (!list->front){
	
		printf("Empty.\n");
		return;
	}
	if (list->front == list->rear){
	
		list->rear = NULL;
	}

	MyNode temp = list->front;
	list->front = (list->front)->next;
	free(temp);
}

void main(){

	List list;
	constructor(&list);
	
	int choice;

	// Tip: While inserting elements, do not use numbers 1-9, so as to avoid confusion.


	// Why am I passing &list to every function?
	// Every function takes in a MyNode* or a struct Node**.
	// This is so that every modification made to list's memory address is retained.
	// If I just passed MyNode and the function did list = list->next, 
	// list will go back to its original value in the main.
	// Some functions do not modify list but I'm maintaining uniformity.

	do{
	scanf("%d", &choice);
	switch (choice){
		
		case 1: enqueue(&list); break;
		
		case 2: dequeue(&list); break;
	
		case 3: display(&list); break;
		
		default: choice = 0; // The while condition fails
	}
	} while(choice);
	
	destructor(&list); // To free all memory in the linked list
}





