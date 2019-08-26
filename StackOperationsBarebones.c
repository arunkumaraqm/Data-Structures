#include <stdio.h>
#define MAXSTACKSIZE 7

struct Stack
{
	int top;
	int arr[MAXSTACKSIZE];
} stack;

void read_elem( int* element )
{
	scanf("%d", element);
}

void push( int element )
{
	
	if( stack.top + 1 == MAXSTACKSIZE )
		printf("\nStack Overflow.");

	else
	{
		stack.top ++;
		stack.arr[stack.top] = element;
	}
			
}

int pop()
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

void display()
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
	stack.top = -1;
	
	
	do{
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 1  :  read_elem(&elem);
					   push(elem);
					   break;
					
			case 2  :  pop();
					   break;
					
			case 3  :  display();
					   break;
					
			default :  choice = 4;
		}
	}while(choice != 4);
}
