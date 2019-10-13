// To read and add polynomials using linked list

#include <stdio.h>
#include <stdlib.h> // For malloc()

struct Node{

	float coeff; // Stands for coefficient
	int expo;
	struct Node* next;	
};

// Aliasing struct Node* to NodePointer
typedef struct Node* NodePointer;

void display_polynomial(NodePointer* polynomial);//

// Inserts a new element into a sorted list
void insert_term(NodePointer* polynomial, float new_coeff, int new_expo){

	// Empty list condition
	if ((*polynomial) == NULL){

		(*polynomial) = malloc(sizeof (*polynomial));
		(*polynomial)->coeff = new_coeff;
		(*polynomial)->expo = new_expo;
		(*polynomial)->next = NULL;

		return;
	}

	NodePointer *cur = polynomial;
	NodePointer *past; *past = NULL;
	
	do{
		
		// If another term is found with the same expo as the new input, add those coeffs
		// But if the sum is zero, delete that node
		if (cur->expo == new_expo){

			cur->coeff += new_coeff;

			if (cur->coeff == 0){

				past->next = cur->next;
				free(cur);
				cur = cur->next;
			}
		}
		
		else{

			// We're keeping the linked list sorted in descending order
			// We're inserting the new term right before the term with a lower exponent
			if (cur->expo < new_expo){

				NodePointer new_node = malloc(sizeof new_node);
				new_node->expo = new_expo;
				new_node->coeff = new_coeff;
				new_node->next = cur;
				past->next = new_node;
			}

			// Loop updation
			past = cur;
			cur = cur->next;
		}
	} while(cur != NULL);
}

void read_polynomial(NodePointer* polynomial){

	float local_coeff;
	int local_expo;
	char yn;
	
	do{

		scanf("%f %d %c", &local_coeff, &local_expo, &yn);

		if(local_coeff) insert_term(polynomial, local_coeff, local_expo);

		display_polynomial(polynomial);//
	} while(yn == 'y' || yn == 'Y');

}

void display_polynomial(NodePointer* polynomial){

	for (NodePointer cur = *polynomial; cur != NULL; cur = cur->next){
	
		printf("%fx^%d + ", cur->coeff, cur->expo);
	}
	
	printf("0\n");
}

void constructor(NodePointer* list){
	
	*list = NULL;
}

// To free all memory at the end of main
void destructor(NodePointer* list){
	
	NodePointer previous_node;
	
	while (*list != NULL){
		
		previous_node = *list;
		*list = (*list)->next;
		free(previous_node);
	}
}

void main(){

	NodePointer polynomial;
	constructor(&polynomial);
	read_polynomial(&polynomial);
	display_polynomial(&polynomial);
	destructor(&polynomial);
}



















