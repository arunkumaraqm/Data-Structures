// Linear search on a matrix

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int valid_input(){ // provides integer input

	int val; char follow;  
	int read = scanf( "%d%c", &val, &follow );
/*
	if (read == 2 )
	{
  		if ( isspace( follow ) )
  		{
    // input is an integer followed by whitespace, accept
    		return val;
  		}
  		else
  		{
    // input is an integer followed by non-whitespace, reject
    		printf("Invalid input."); exit(0); 
  		}
	}	
	else if ( read == 1 )
	{
  // input is an integer followed by EOF, accept
  		return val;
	}
	else
	{
  	// input is not an integer, reject
  		printf("Invalid input."); exit(0);
	}*/

	if ( (read == 2 && isspace(follow)) ||
		  read == 1){

		return val;
	}

  	printf("Invalid input."); exit(0);
}

void read_mat(int rows, int cols, int *mat)
{
	int size = rows * cols;
	for( int i = 0; i < size; ++i, ++mat )
		*mat = valid_input();
}

void write_mat(int rows, int cols, int mat[rows][cols])
{
	printf("\n");
	int i, j;
	for( i = 0; i < rows; ++i, printf("\n") )
	for( j = 0; j < cols; ++j )
		printf("%d ", mat[i][j]);
}

int* linear_search(int rows, int cols, int* mat, int item)
{
	int i, j;
	
	for (i = 0; i < rows; ++i){
	
		for(j = 0; j < cols; ++j, ++mat ){

			if (item == *mat){

				int *position = calloc(2, sizeof(int));
				position[0] = i;
				position[1] = j;
				return position;
			}
		}
	} 

	return NULL;
}

void main()
{
	int rows, cols;
	rows = valid_input();
	cols = valid_input();
	
	int mat[rows][cols];
	read_mat(rows, cols, &mat[0][0]);
	write_mat(rows, cols, mat);

	int item = valid_input();
	int* position = linear_search(rows, cols, &mat[0][0], item);
	if (position == NULL)	printf("Item not found.\n");
	else{
		printf("Position = [%d, %d]", position[0], position[1]);
		free(position);}
}
