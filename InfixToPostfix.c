//Program to convert infix expression to postfix expression

// TODO: Add code to validate the input expression

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSTACKSIZE 15 //Caution

struct Expression
{
	int top;
	char arr[MAXSTACKSIZE];
};

// Returns 0 if symbol isn't an operator
// Returns precedence if symbol is an operator
int is_operator ( char symbol )
{
	if ( symbol == '^' ) return 3;
	else if ( symbol == '/' || symbol == '*' ) return 2;
	else if ( symbol == '+' || symbol == '-' ) return 1;
	else return 0;
}

int is_operand ( char symbol )
{
	return (symbol >= 'a' && symbol <= 'z');
}

void push ( struct Expression *stack, char element )
{
	stack->top ++;
	stack->arr[stack->top] = element;
			
}

char pop ( struct Expression *stack )
{
	return stack->arr[stack->top--];
}

char peek ( struct Expression *stack )
{
	return stack->arr[stack->top];
}

void my_constructor ( struct Expression *stack )
{
	stack->top = -1;	
}

void read_expression ( struct Expression *input )
{
	scanf ( "%s", input->arr );
	input->top = strlen ( input->arr ) - 1;  
	// TODO: Check if len exceeds MAXSTACKSIZE - 1
}

void write_expression ( struct Expression *output )
{
	for ( int i = 0; i <= output->top; ++i )
	{
		printf( "%c", output->arr[i] );
	}
	printf( "\n" );
}


void infix_to_postfix ( struct Expression *input, struct Expression *output )
{
	struct Expression *stack = malloc ( sizeof stack );
	my_constructor ( stack );
	
	push ( stack, '(' );
	push ( input, ')' );

	int input_size = input->top + 1;
	
	char *cur = input->arr;
	int precedence_of_cur;

	// This for loop uses the condition i < input_size instead of checking whether stack is empty	
	for( int i = 0; i < input_size; ++i, ++cur)	
	{		
		if ( *cur == '(' )
		{
			push ( stack, *cur );
		} 
		
		else if ( *cur == ')' )
		{
			// This loop may be slightly inefficient.
			while ( peek ( stack ) != '(' )
			{
				push ( output, pop ( stack ) );
			}
			
			pop ( stack ); // The ')' itself is removed			
		}
		
		else if ( is_operand ( *cur ) )
		{
			push ( output, *cur );
		}

		// Assignment and non-zero check happening in this condition
		else if ( precedence_of_cur = is_operator ( *cur ))
		{			
			while ( is_operator ( peek ( stack ) ) >= precedence_of_cur )
			{
				push ( output, pop ( stack ) );
			}
			
				push ( stack, *cur );
		}
	
		printf("\nSymbol Scanned: %c", *cur);//
		printf("\nStack: "); write_expression ( stack );//
		printf("Output: "); write_expression ( output );//

	}
	
	free ( stack );
}

void main()
{
	struct Expression inputx, outputy;
	my_constructor ( &inputx );
	my_constructor ( &outputy );

	read_expression ( &inputx );
	infix_to_postfix ( &inputx, &outputy );

	printf("\nFinal Output:"); write_expression ( &outputy );
}
