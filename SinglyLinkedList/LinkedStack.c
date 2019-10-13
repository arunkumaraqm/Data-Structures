// Linked List implementation of Stack data structure

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

void display(MyNode* list){ // Added a list empty condition and changed display pattern
	
	// Checks if list is empty
	if(!*list){
	
		printf("Empty.\n");
		return;
	}
	
	MyNode cur;
	
	for (cur = *list; cur != NULL; cur = cur->next){
	
		printf("%d\n", cur->data);
	}
}

void constructor(MyNode* list){
	
	*list = NULL;
}


// To free all memory at the end of main
void destructor(MyNode* list){
	
	MyNode previous_node;
	
	while (*list != NULL){
		
		previous_node = *list;
		*list = (*list)->next;
		free(previous_node);
	}
}
void push(MyNode* list){

	MyNode new_element = malloc(sizeof new_element);
	if (new_element == NULL){
	
		printf("\nStack is full because heap memory allocation failed.");
		return;
	}
	new_element->data = read_element();
	new_element->next = *list;
	*list = new_element;
}

void pop(MyNode* list){

	// Checks if list is empty
	if(!*list){
	
		printf("Empty.\n");
		return;
	}

	MyNode temp = *list;
	*list = (*list)->next;
	free(temp);
}

void main(){

	MyNode list;
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
		
		case 1: push(&list); break;
		
		case 2: pop(&list); break;
	
		case 3: display(&list); break;
		
		default: choice = 0; // The while condition fails
	}
	} while(choice);
	
	destructor(&list); // To free all memory in the linked list
}





