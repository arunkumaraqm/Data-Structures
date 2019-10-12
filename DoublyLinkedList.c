// Implementation of basic operations in a doubly linked list
// No tail pointer is used

#include <stdio.h>
#include <stdlib.h> // For malloc()

int read_element(){
	
	int element;
	scanf("%d", &element);
	return element;
}

struct Node{

	int data;
	struct Node* prev;
	struct Node* next;	
};

// Aliasing struct Node* to NodePointer
typedef struct Node* NodePointer;

void display(NodePointer* list){

	// Display will look like 10 -> 20 -> 30 -> NULL
	printf("Linked List: ");
	
	for (NodePointer cur = *list; cur != NULL; cur = cur->next){
	
		printf("%d -> ", cur->data);
	}
	
	printf("NULL\n");
}

void constructor(NodePointer* list){
	
	*list = NULL;
}

// To free all memory at the end of main
void destructor(NodePointer* list){
	
	NodePointer cur;
	
	while (*list != NULL){
		
		cur = *list;
		*list = (*list)->next;
		free(cur);
	}
}

void insert_front(NodePointer* list){

	// List empty condition
	if ((*list) == NULL){
	
		*list = malloc(sizeof (*list));
		(*list)->data = read_element();
		(*list)->prev = (*list)->next = NULL;
		return;
	}

	// Creating new_element
	NodePointer new_element = malloc(sizeof new_element);
	new_element->data = read_element();
	new_element->prev = NULL;
	new_element->next = *list;

	// Setting new_element as first element
	(*list)->prev = new_element ;
	*list = new_element;

}

void delete_front(NodePointer* list){

	// List empty condition
	if (*list == NULL){
	 
		printf("Cannot delete from an empty list.\n"); 
	}

	// List has only one element condition
	else if ((*list)->next == NULL){

		free(*list);
		*list = NULL;
	}

	// Normal condition
	else{

		*list = (*list)->next;
		free((*list)->prev);
		(*list)->prev = NULL;
	}
}


void insert_rear(NodePointer* list){

	// List empty condition
	if ((*list) == NULL){
	
		*list = malloc(sizeof (*list));
		(*list)->data = read_element();
		(*list)->prev = (*list)->next = NULL;
		return;
	}

	// Creating new_element
	NodePointer new_element = malloc(sizeof new_element);
	new_element->data = read_element();
	new_element->next = NULL; // new_element->prev will be given a value soon

	// Getting cur to the last node
	NodePointer cur;
	for (cur = *list; cur->next; cur = cur->next);

	// Adding the new element at the end
	cur->next = new_element; 
	new_element->prev = cur;
}

void delete_rear(NodePointer* list){

	// List empty condition
	if (*list == NULL){
	 
		printf("Cannot delete from an empty list.\n"); 
	}

	// List has only one element condition
	else if ((*list)->next == NULL){

		free(*list);
		*list = NULL;
	}

	// Normal condition
	else{

		NodePointer cur;
		for (cur = *list; cur->next->next; cur = cur->next);
	
		free(cur->next);
		cur->next = NULL;
	}
}

void main(){

	NodePointer list;
	constructor(&list);
	
	int choice;

	do{
	
	scanf("%d", &choice);
	switch (choice){
	
		case 1: display(&list); break;
		
		case 2: insert_front(&list); break;
		
		case 3: insert_rear(&list); break;
		
		case 4: delete_front(&list); break;
		
		case 5: delete_rear(&list); break;
		
		default: choice = 0; // The while condition fails
	}
	} while(choice);
	
	destructor(&list); // To free all memory in the linked list
}
