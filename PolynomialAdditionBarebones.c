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

	if (list->tail == NULL){ // List empty condition
	
		printf("Zero.\n");
	}
	
	else{ // Normal condition
		
		NodePointer cur = list->tail->next; 
		printf("Display: "); // 
		
		//for has been changed to a do-while because loop condition was already checked 
		do{
		
			printf("%fx^%d + ", cur->coeff, cur->expo); 
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
	
	// This do while is just for the first node
	do{
		scanf("%f %d %c", &local_coeff, &local_expo, &yn);

		if(local_coeff){
	
			// Inserting first node
			cur->coeff = local_coeff;
			cur->expo = local_expo;
			cur->next = cur;
		}
	
		// local_coeff is zero and user wants to exit
		else if (yn != 'Y' && yn != 'y'){
	
			free_and_null(polynomial->tail);
			return;
		}
	
		else{
		
			continue;
		}
	
	}while (0);
		
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

CircularList* add_polynomials(const CircularList* first_polynomial, const CircularList* second_polynomial){

	NodePointer one = first_polynomial->tail;
	NodePointer two = second_polynomial->tail;
	
	// When one or both of the polynomials are empty
	if (one == NULL){
		
		return second_polynomial;
	}
	else if (two == NULL){
	
		return first_polynomial;
	}
	
	//
	//one = one->next; two = two->next;
	
	
	// Packing sum inside a box called temp (CircularList) and returning the box.
	/*CircularList* temp = malloc(sizeof temp);
	temp->tail = sum;
	return temp;*/
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
	
	CircularList* sum = add_polynomials(one, two);
	display_polynomial(sum);
	
	flag(3);
	destructor(sum); free_and_null(sum); 
	flag(4);
	destructor(one); free_and_null(one);
	
	flag(5);destructor(two); free_and_null(two);
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

















