// Implement deque using stack

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define capacity 5

struct Stack
{
	int top;
	int arr[capacity];
};

int read_element()
{
	int element;
	scanf("%d", &element);
	return element;
}

int is_empty(struct Stack* deque)
{
	return deque->top == -1;
}

int is_full(struct Stack* deque)
{
	return deque->top == capacity - 1;
}

// Initialization for top of stack; this function is called always after declaration of a Deque obj
void constructor(struct Stack* deque)
{
	deque->top = -1;
}

void push(struct Stack* deque, int element)
{	
		deque->top += 1;
		deque->arr[deque->top] = element;			
}

int pop(struct Stack* deque)
{
		return deque->arr[deque->top--];
}

// Costly insert left
void insert_left(struct Stack* deque)
{
	if( is_full(deque) )
		printf("Queue full.\n");
	
	else
	{
		struct Stack* second_stack = (struct Stack*) malloc(sizeof (struct Stack));
		constructor(second_stack);

		// Move all elements from deque to second_stack
		while( !is_empty(deque) )
		{
				push(second_stack, pop(deque) );
		}

		// Add new element to deque
		push(deque, read_element());

		// Move all the other elements back from second_stack to deque
		while ( !is_empty(second_stack) )
		{
				push(deque, pop(second_stack) );
		}

		free(second_stack);
		
	}	
}

void insert_right(struct Stack* deque)
{
	if( is_full(deque) )
		printf("Queue full.\n");
	
	else
	{
		push(deque, read_element());
	}	
}

// Costly delete left
int delete_left(struct Stack* deque) 
{
	if( is_empty(deque) )
	{
		printf("Queue empty.\n");
		return INT_MIN; 
	}
	
	else
	{
		struct Stack* second_stack = (struct Stack*) malloc(sizeof (struct Stack));
		constructor(second_stack);

		// Move all the elements from deque to second_stack
		while( !is_empty(deque) )
		{
				push(second_stack, pop(deque) );
		}

		// Delete the element which was the leftmost / bottom most on deque
		int deleted_element = pop(second_stack);

		// Move all the elements back from second_stack to deque
		while ( !is_empty(second_stack) )
		{
				push(deque, pop(second_stack) );
		}
			
		free(second_stack);
		return deleted_element;
	}	
}

int delete_right(struct Stack* deque) 
{
	if( is_empty(deque) )
	{
		printf("Queue empty.\n");
		return INT_MIN; 
	}
	return pop(deque);
}

void display(struct Stack* deque)
{
	int i;
	
	printf("Contents of deque: ");
	
	if( is_empty(deque) )
	{
		printf("None\n");
		return;
	}
	
	for( i = 0; i <= deque->top; ++i )
	{
		printf("%d ", deque->arr[i]);
	}
	printf("\n");
}

void main()
{
	int choice;
	int deleted_element;
	struct Stack deque;
	
	constructor(&deque);
	
	do{
		scanf("%d", &choice);

		// Display of deleted elements has been commented for convenience
		switch(choice)
		{
			case 1  :  insert_left(&deque);
				   break;
			case 2  :  insert_right(&deque);
				   break;
			case 3  :  deleted_element = delete_left(&deque);
			//	   if( deleted_element != INT_MIN ) printf("Deleted Element: %d\n", deleted_element);
				   break;
			case 4  :  deleted_element = delete_right(&deque);
			//	  	if( deleted_element != INT_MIN ) printf("Deleted Element: %d\n", deleted_element);
				   break;
			case 5  :  display(&deque);
				   break;   
			default :  choice = 6;
		}
		
	}while(choice != 6);
}
