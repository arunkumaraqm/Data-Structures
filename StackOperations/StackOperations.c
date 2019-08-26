#include <stdio.h>
#include "StackOperationsHeader.h"

// StackDataType is declared in the custom header file
StackDataType stack;

void my_constructor()
{
	stack.top = -1;
}

void read_elem( int* element )
{
	scanf("%d", element);
}

void my_push( int element )
{
	// Stack full condition
	if( stack.top + 1 == MAXSTACKSIZE )
		printf("\nStack Overflow.");

	else
	{
		stack.top ++;
		stack.arr[stack.top] = element;
	}
			
}

int my_pop()
{
	// Stack empty condition
	if( stack.top == -1 )
	{
		printf("\nStack Underflow.");
		return 0; //To be changed
	}
	else
	{
		printf("\n%d", stack.arr[stack.top]);// 
		return stack.arr[stack.top--];
	}
}

void my_display()
{
	int i;
	for( i = stack.top; i > -1; --i )
	{
		printf("%d ", stack.arr[i]);
	}
}

void main()
{
	int choice;
	int elem;
	
	// Initializing the function pointers to the functions in this file
	stack.push = my_push;
	stack.pop = my_pop;
	stack.display = my_display;
	stack.constructor = my_constructor;
	
	// Essentially stackInitialize
	stack.constructor();
	
	// Menu
	do{
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 1  :  read_elem(&elem); // Just might be too small of a method to call.
				   stack.push(elem);
				   break;
					
			case 2  :  stack.pop();
				   break;
					
			case 3  :  stack.display();
				   break;
					
			default :  choice = 4; // This initialization is to solely dissatisfy the while condition.
		}
	}while(choice != 4);
}
