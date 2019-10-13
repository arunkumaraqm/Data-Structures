//Insertion and Deletion at Any Position

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

void display(MyNode* list){
	
	MyNode cur;

	// Display will look like 10 -> 20 -> 30 -> NULL
	printf("Linked List: ");
	
	for (cur = *list; cur != NULL; cur = cur->next){
	
		printf("%d -> ", cur->data);
	}
	
	printf("NULL\n");
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

void insert_front(MyNode* list){

	MyNode new_element = malloc(sizeof new_element);
	if (new_element == NULL){
	
		printf("\nHeap memory allocation failed.");
		return;
	}
	new_element->data = read_element();
	new_element->next = *list;
	*list = new_element;
}

void insert_any_position(MyNode* list){

	// Position starts from zero
	int position;
	scanf("%d", &position);
	
	if (position == 0){
		
		insert_front(list);
		return;	
	}
	
	int i;
	MyNode prev, cur = *list;

	// Navigates to 'position' position in linked list. 
	for (i = 0; i < position; ++i){

		// For when the linked list runs out before reaching position 
		if (cur == NULL) break;
		
		prev = cur;
		cur = cur->next;
	}
	
	if (i == position){

		// prev points to ('position' - 1)th node
		// cur points to the node after that
		insert_front(&cur); // So, inserting new node in the front of cur does the trick
		prev->next = cur; // Now, prev->next stores the address of the newly inserted node
	}

	// cur reached NULL before i reached position
	else{
	
		printf("Position exceeds size of linked list.\n");
	}
}

void delete_any_position(MyNode* list){

	if (*list == NULL){
	
		printf("Empty.\n");
		return;
	}
	
	// Position starts from zero
	int position;
	scanf("%d", &position);
	
	if (position == 0){
		
		MyNode temp = *list;
		*list = (*list)->next;
		free(temp);
		return;	
	}
	
	int i;
	MyNode prev, cur = *list;

	// Navigates to 'position' position in linked list. 
	for (i = 0; i < position; ++i){

		// For when the linked list runs out before reaching position 
		if (cur == NULL) break;
		
		prev = cur;
		cur = cur->next;
	}
	
	if (i == position && cur != NULL){

		// prev points to ('position' - 1)th node
		// cur points to the node after that
		cur = cur->next;
		free(prev->next);
		prev->next = cur;		
	}

	// cur reached NULL before i reached position
	else{
	
		printf("Position exceeds size of linked list.\n");
	}
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
		
		case 1: insert_any_position(&list); break;
		
		case 2: delete_any_position(&list); break;
		
		case 3: display(&list); break;
		
		default: choice = 0; // The while condition fails
	}
	} while(choice);
	
	destructor(&list); // To free all memory in the linked list
}





