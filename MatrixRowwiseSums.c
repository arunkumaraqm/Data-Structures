// To calculate sum of each row in an integer matrix

#include <stdio.h>
#include <stdlib.h>

void read_mat(int rows, int cols, int *mat)
{
	int size = rows * cols;
	for( int i = 0; i < size; ++i, ++mat )
		scanf("%d", mat);
}

void write_mat(int rows, int cols, int mat[rows][cols])
{
	printf("\n");
	int i, j;
	for( i = 0; i < rows; ++i, printf("\n") )
	for( j = 0; j < cols; ++j )
		printf("%d ", mat[i][j]);
}

void calculate_row_sums(int rows, int cols, int* mat)
{
	int *sum, i, j;
	sum = calloc(cols, sizeof(int));
	
	for (i = 0; i < rows; ++i){
	
		for(j = 0; j < cols; ++j, ++mat ){

			sum[i] += *mat;
		}

		printf("\n%d", sum[i]);
	} 
	free(sum);
}

void main()
{
	int rows, cols;
	scanf("%d", &rows);
	scanf("%d", &cols);
	
	int mat[rows][cols];
	read_mat(rows, cols, &mat[0][0]);
	write_mat(rows, cols, mat);
	calculate_row_sums(rows, cols, &mat[0][0]);
	
	
}
