// To read and add polynomials using circular linked list

#include <stdio.h>
#include <stdlib.h> // For malloc()

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
	char yn = 'y'; // yn stands for yes or no -- 'y' or 'Y' for yes, anything else for no
				   // It contains the answer to "Do you want to continue?"

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

// Copies data into node
void insert_term(NodePointer node, float coeff, int expo){

	node->coeff = coeff;
	node->expo = expo;
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
	// This loop terminates when we run out of nodes on either one or two
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

			else{

				// Getting rid of the node that we allocated at the beginning of the loop
				NodePointer past;
				for (past = sum_head; past->next != sum; past = past->next);
				free_and_null(sum);
				sum = past;
			}
			
			one = one->next; two = two->next;
		}		
	}

	// For any nodes remaining in one
	while (one != first_head){

		sum->next = allocate();
		sum = sum->next;
		insert_term(sum, one->coeff, one->expo);
		one = one->next;
	}

	// For any nodes remaining in two
	while (two != second_head){

		sum->next = allocate();
		sum = sum->next;
		insert_term(sum, two->coeff, two->expo);
		two = two->next;
	}

	// Making the linked list circular
	sum->next = sum_head;
	
	// Packing sumhead inside a box called temp (CircularList) and returning the box.
	CircularList* temp = malloc(sizeof *temp);
	temp->tail = sum;
	return temp;
}

// Driver function
void main(){

	// Getting the first polynomial
	CircularList* one = malloc(sizeof *one);
	one->tail = NULL;
	read_polynomial(one);
	display_polynomial(one);//

	// Getting the second polynomial
	CircularList* two = malloc(sizeof *two);
	two->tail = NULL;
	read_polynomial(two);
	display_polynomial(two);//

	// Adding them and storing the result in sum
	CircularList* sum = add_polynomials(one, two);
	display_polynomial(sum);

	// Freeing all the heap memory we used
	destructor(sum); free_and_null(sum); 
	destructor(one); free_and_null(one);
	destructor(two); free_and_null(two);
}

/*

TEST CASES

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

	Test 9: 
5x5 + 4x4 + 3x3 -2x2
5x7 + 6x6 + 3x4 + 3x3 + 2x2 + 1x1 + 8x0

Input
5 5 y 4 4 y 3 3 y -2 2 n
5 7 y 6 6 y 3 4 y 3 3 y 2 2 y 1 1 y 8 0 n

Output
5x7 + 6x6 + 5x5 + 7x4 + 6x3 + 1x1 + 8x0

	Test 10:
5x5 + 3x3 + 2x1 + 1x0
- 5x5 - 3x3 - 2x1 - 1x0

Input
5 5 y 3 3 y 2 1 y 1 0 n
-5 5 y -3 3 y -2 1 y -1 0 n

Output
0x0

	Test 11:
4.10x5 + 3.20x3 + 5.33x1 + 7.67x0
5x6 + 8.1x5 - 3.34x3 + 4.46x1

Input
4.10 5 y 3.20 3 y 5.33 1 y 7.67 0 n
5 6 y 8.1 5 y -3.34 3 y 4.46 1 n

Output
5x6 + 12.2x5 - 0.14x3 + 9.79x1 + 7.67x0


*/

















