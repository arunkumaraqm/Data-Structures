#include <stdio.h>
#include "StackOperationsHeader.h"

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
	stack.push = my_push;
	stack.pop = my_pop;
	stack.display = my_display;
	stack.constructor = my_constructor;
	
	stack.constructor();
	
	
	do{
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 1  :  read_elem(&elem);
					   stack.push(elem);
					   break;
					
			case 2  :  stack.pop();
					   break;
					
			case 3  :  stack.display();
					   break;
					
			default :  choice = 4;
		}
	}while(choice != 4);
}
