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
/*
void display_polynomial(CircularList* polynomial);//

void read_polynomial(CircularList* polynomial){

	float local_coeff;
	int local_expo;
	char yn;

	do{
	
	while(yn == 'y' || yn == 'Y'){

		scanf("%f %d %c", &local_coeff, &local_expo, &yn);

		if(local_coeff) insert_term(polynomial, local_coeff, local_expo);

		display_polynomial(polynomial);//
	}

}

void display_polynomial(NodePointer* polynomial){

	for (NodePointer cur = *polynomial; cur != NULL; cur = cur->next){
	
		printf("%fx^%d + ", cur->coeff, cur->expo);
	}
	
	printf("0\n");
}
*/

void create_first(CircularList* list){

	flag(20);
	list->tail = malloc(sizeof list->tail);
	list->tail->expo = 50;
	list->tail->next = NULL;
	flag(21);
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

void main(){

	CircularList* polynomial = malloc(sizeof polynomial);
	polynomial->tail = NULL;
	
	create_first(polynomial);
	(polynomial->tail == NULL )? printf("Yes"): printf("No"); 
	destructor(polynomial);
}



















