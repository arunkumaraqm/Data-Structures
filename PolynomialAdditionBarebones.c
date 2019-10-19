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

// To free all memory of the linked list at the end of main
void destructor(CircularList* list){

	if (list->tail == NULL){ flag(10);return;}

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
		
	NodePointer cur = list->tail->next->next; 

	// Iterates from second element to penultimate element
	// Remember first element is zero
	
	while (cur != list->tail){
		printf("%fx^%d + ", cur->coeff, cur->expo); 
		cur = cur->next;	
	}
	// Prints last element. Had to take it out of the loop because of the plus symbol.
	printf("%fx^%d\n", cur->coeff, cur->expo); 		
	
}

void read_polynomial(CircularList* polynomial){

	float local_coeff; int local_expo;
	char yn = 'y';

	polynomial->tail = malloc(sizeof *polynomial->tail);
	NodePointer cur = polynomial->tail;
	NodePointer past = NULL;	
	
	// Inserting first node - contains zero
	cur->coeff = 0;
	cur->expo = 0;
	cur->next = cur;
		
	while (yn == 'Y' || yn == 'y'){

		scanf("%f %d %c", &local_coeff, &local_expo, &yn);

		if(local_coeff){
		
			// Inserting at the end of the circular list
			past = cur;
			cur = NULL;
			cur = malloc(sizeof *cur);
			cur->coeff = local_coeff;
			cur->expo = local_expo;
			cur->next = past->next;
			past->next = cur; 
		}
	}
	polynomial->tail = cur; // tail was pointing to that first node until now

}

/*
CircularList* add_polynomials(CircularList* first_polynomial, CircularList* second_polynomial){

	NodePointer one = first_polynomial->tail;
	NodePointer two = second_polynomial->tail;
	
	one = one->next; two = two->next;
	
	while( one != first_polynomial->tail 
		&& two != second_polynomial->tail){

		if 
	}
	
	// Packing sum inside a box called temp (CircularList) and returning the box.
	CircularList* temp = malloc(sizeof *temp);
	temp->tail = sum;
	return temp;
}
*/
void main(){

	CircularList* one = malloc(sizeof *one);
	one->tail = NULL;
	read_polynomial(one);
	display_polynomial(one);
	/*
	CircularList* two = malloc(sizeof *two);
	two->tail = NULL;
	read_polynomial(two);
	display_polynomial(two);
	
	CircularList* sum = add_polynomials(one, two);
	display_polynomial(sum);
	
	destructor(sum);  
	destructor(one); free_and_null(one);
	destructor(two); free_and_null(two);
	//free_and_null(sum);
	*/
	destructor(one);//
}

/*

Test 1:
5x2 + 6x1 + 9x0
5x2 + 6x1 + 10x0

Input
5 2 y 6 1 y 9 0 n
5 2 y 6 1 y 10 0 n


 0 1 n 0 1 n
*/

















