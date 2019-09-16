#include <stdio.h>
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

void insert_left(struct Stack* deque)
{
	printf("\nInside insert left");//
	if( is_full(deque) )
		printf("\nQueue full.");
	
	else
	{
		struct Stack* second_stack;
		constructor(second_stack);
		
		while( is_empty(deque) )
		{
				push(second_stack, pop(deque) );
		}
		
		push(deque, read_element());
		printf("\nInserted.");//
		
		while ( is_empty(second_stack) )
		{
				push(deque, pop(second_stack) );
		}
		
		deque->top += 1;
	}	
}

void insert_right(struct Stack* deque)
{
	printf("\nInside insert right");//
	if( is_full(deque) )
		printf("\nQueue full.");
	
	else
	{
		push(deque, read_element());
	}	
}

int delete_left(struct Stack* deque) 
{
	if( is_empty(deque) )
	{
		printf("\nQueue empty.");
		return INT_MIN; 
	}
	
	else
	{
		struct Stack* second_stack;
		constructor(second_stack);
		
		while( is_empty(deque) )
		{
				push(second_stack, pop(deque) );
		}
		
		int deleted_element = pop(second_stack);
		
		while ( is_empty(second_stack) )
		{
				push(deque, pop(second_stack) );
		}
		
		deque->top -= 1;
		
		return deleted_element;
	}	
}

int delete_right(struct Stack* deque) 
{
	if( is_empty(deque) )
	{
		printf("\nQueue empty.");
		return INT_MIN; 
	}
	return pop(deque);
}

void display(struct Stack* deque)
{
	int i;
	
	printf("\nContents of deque: ");
	
	if( is_empty(deque) )
	{
		printf("None");
		return;
	}
	
	for( i = 0; i <= deque->top; ++i )
	{
		printf("%d ", deque->arr[i]);
	}
}

void main()
{
	int choice;
	int deleted_element;
	struct Stack deque;
	
	constructor(&deque);
	
	do{
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 1  :  	printf("\nEntering case 1");
						insert_left(&deque);
						printf("\nExiting case 1");
					   break;
			case 2  :  	printf("\nEntering case 2");
						insert_right(&deque);
						printf("\nExiting case 2");
			case 3  :  deleted_element = delete_left(&deque);
					   if( deleted_element != INT_MIN ) printf("\nDeleted Element: %d", deleted_element);
					   break;
			case 4  :  deleted_element = delete_right(&deque);
					   if( deleted_element != INT_MIN ) printf("\nDeleted Element: %d", deleted_element);
					   break;
			case 5  :  display(&deque);
					   break;   
			default :  choice = 6;
		}
		
		printf("\n");
		
	}while(choice != 6);
}
