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

void insert_term(NodePointer node, float coeff, int expo){

	node->coeff = coeff;
	node->expo = expo;
}

// Temp
void display(NodePointer list){
	
	// Display will look like 10 -> 20 -> 30 -> NULL
	printf("Linked List: ");
	
	for (NodePointer cur = list; cur != NULL; cur = cur->next){
	
		printf("%f, %d -> ", cur->coeff, cur->expo);
	}
	
	printf("NULL\n");
}

#define allocate() malloc(sizeof(struct Node))

CircularList* add_polynomials(CircularList* first_polynomial, CircularList* second_polynomial){

	NodePointer first_head = first_polynomial->tail->next, one = first_head->next;
	NodePointer second_head = second_polynomial->tail->next, two = second_head->next;

	// Creating a first node for sum_head, which is always zero
	NodePointer sum_head = allocate(), sum = sum_head;
	sum_head->expo = sum_head->coeff = 0;

	// one starts from second element and goes till last element
	// Rememeber that the first element is always zero
	// Same is the case with two
	while (one != first_head && two != second_head){

		sum->next = allocate();
		sum = sum->next;
		
		if (one->expo > two->expo){

			insert_term(sum, one->coeff, one->expo);
			one = one->next;
		}
		
		else if (one->expo < two->expo){

			insert_term(sum, two->coeff, two->expo);
			two = two->next;
		}
		
		else{ // when both exponents are equal

			if (one->coeff + two->coeff != 0)
				insert_term(sum, one->coeff + two->coeff, one->expo);
				// TODO: When the sum is zero, don't allocate another node for sum-next
			one = one->next; two = two->next;
		}

		display(sum_head);
		
	}

	while (one != first_head){

		sum->next = allocate();
		sum = sum->next;
		insert_term(sum, one->coeff, one->expo);
		one = one->next;
	}
	
	while (two != second_head){

		sum->next = allocate();
		sum = sum->next;
		insert_term(sum, two->coeff, two->expo);
		two = two->next;
	}

	sum->next = sum_head;
	
	// Packing sumhead inside a box called temp (CircularList) and returning the box.
	CircularList* temp = malloc(sizeof *temp);
	temp->tail = sum;
	return temp;
}

void main(){

	CircularList* one = malloc(sizeof *one);
	one->tail = NULL;
	read_polynomial(one);
	display_polynomial(one);
	
	CircularList* two = malloc(sizeof *two);
	two->tail = NULL;
	read_polynomial(two);
	display_polynomial(two);
	
	CircularList* sum = add_polynomials(one, two);
	display_polynomial(sum);
	
	destructor(sum); free_and_null(sum); 
	destructor(one); free_and_null(one);
	destructor(two); free_and_null(two);
}

/*

	Test 1:
0x1
0x2

Input 
0 1 n
0 2 n

Output
0x0


	Test 2:
0x1
0x2 + 0x1 + 0x0

Input 
0 1 n
0 2 y 0 1 y 0 0 n

Output
0x0

	Test 3:
0x3
5x2 + 6x1 + 7x0

Input
0 3 n
5 2 y 6 1 y 7 0 n

Output
5x2 + 6x1 + 7x0

	Test 4:
50x5
6x3 + 5x1 + 7x0

Input
50 5 n
6 3 y 5 1 y 7 0 n

Output
50x2 + 6x3 + 5x1 + 7x0

	Test 5:
6x3 + 5x1 + 7x0
50x5

Input
6 3 y 5 1 y 7 0 n
50 5 n

Output
50x2 + 6x3 + 5x1 + 7x0


	Test 6:
5x2 + 6x1 + 9x0
5x2 + 6x1 + 10x0

Input
5 2 y 6 1 y 9 0 n
5 2 y 6 1 y 10 0 n

Output
10x2 + 12x1 + 19x0


	Test 7:
5x5 + 3x3 + 2x1 + 1x0
4x4 + 2x2 + 3x1

Input
5 5 y 3 3 y 2 1 y 1 0 n
4 4 y 2 2 y 3 1 n

Output
5x5 + 4x4 + 3x3 + 2x2 + 5x1 + 1x0

	Test 8:
4x5 + 3x3 + 5x1 + 7x0
5x6 + 8x5 -3x3 + 4x1

Input
4 5 y 3 3 y 5 1 y 7 0 n
5 6 y 8 5 y -3 3 y 4 1 n

Output
5x6 + 12x5 + 9x1 + 7x0

*/

















