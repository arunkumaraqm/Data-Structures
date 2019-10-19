// To read and add polynomials using linked list

#include <stdio.h>
#include <stdlib.h> // For malloc()
#define flag(n) printf("Flag %d.\n", n)

#define free_and_null(ptr) {free(ptr); ptr = NULL;}

struct Node{

	float coeff; // Stands for coefficient
	int expo;
	struct Node* next;	
};

// Aliasing struct Node* to NodePointer
typedef struct Node* NodePointer;

typedef struct CircularList{

	NodePointer tail;
}CircularList;

void create_first(CircularList* list){

	NodePointer cur = list->tail;
	cur = malloc(sizeof cur);
	cur->expo = 50;
	cur->next = cur;
	list->tail = cur;
}

// To free all memory at the end of main
void destructor(CircularList* list){

	if (list->tail == NULL) return;

	NodePointer past = NULL, cur = NULL;

	// Loop iterates from tail.next or head to penultimate node
	for (cur = list->tail->next; cur != list->tail; ){

		past = cur;
		cur = cur->next;
		free_and_null(past);
	}

	free_and_null(list->tail); 
}

void display_polynomial(CircularList* list){

	if (list->tail == NULL){ // List empty condition
	
		printf("Zero.\n");
	}
/*	else if (list->tail->next == list->tail){ // One node condition
	
		printf("%fx^%d + ", list->tail->coeff, list->tail->expo);
	}
*/	else{ // Normal condition
		
		NodePointer cur = list->tail->next; 
		printf("Display: "); // 
		
		//for has been changed to a do-while because loop condition was already checked 
		do{
		
			printf("%fx^%d + ", cur->coeff, cur->expo); //temp modif
			cur = cur->next;	
		}while (cur != list->tail->next);	
	}
}

void read_polynomial(CircularList* polynomial){

	float local_coeff; int local_expo;
	char yn;

	polynomial->tail = malloc(sizeof polynomial->tail);
	NodePointer cur = polynomial->tail;
	NodePointer past = NULL;	
	
	
	scanf("%f %d %c", &local_coeff, &local_expo, &yn);

	if(local_coeff){
	
		// Inserting first node
		cur->coeff = local_coeff;
		cur->expo = local_expo;
		cur->next = cur;
	}

//TODO: What about when local_coeff is zero?
		
	while (yn == 'Y' || yn == 'y'){

		scanf("%f %d %c", &local_coeff, &local_expo, &yn);

		if(local_coeff){
		
			// Inserting at the end of the circular list
			past = cur;
			cur = NULL;
			cur = malloc(sizeof cur);
			cur->coeff = local_coeff;
			cur->expo = local_expo;
			cur->next = past->next;
			past->next = cur; 
		}
	}
	polynomial->tail = cur; // tail was pointing to that first node until now

}

CircularList* add_polynomials(CircularList* one, CircularList* two){

	
}
void main(){

	CircularList* one = malloc(sizeof one);
	one->tail = NULL;
	read_polynomial(one);
	display_polynomial(one);
	
	CircularList* two = malloc(sizeof two);
	two->tail = NULL;
	read_polynomial(two);
	display_polynomial(two);
	
	sum = add_polynomials(one, two);
	display_polynomial(sum);
	
	destructor(one);
	destructor(two);
	destructor(sum);
}


















