#include <stdio.h>

void read_mat(int rows, int cols, int *mat)
{
	int size = rows * cols;
	int *cur = mat;
	for( int i = 0; i < size; ++i, ++cur )
		scanf("%d", cur);
}

void write_mat(int rows, int cols, int *mat)
{
	printf("\n");
	int *cur = mat, i, j;
	for( i = 0; i < rows; ++i, printf("\n") )
	for( j = 0; j < cols; ++j, ++cur )
		printf("%d ", *cur);
}

int convert_to_sparse( int rows, int cols, int *mat, int *sparse_mat)
{
	int i, j, noof_nz = 0; // no. of non-zero elements
	int limit = (rows * cols) / 3;
	int *cur_mat = mat, *cur_sparse_mat = sparse_mat;

	for( i = 0; i < rows; ++i )
	for( j = 0; j < cols; ++j, ++cur_mat )
	if( *cur_mat )
	{
		if( noof_nz < limit )		
		{
	/*
			sparse_mat[noof_nz][0] = i;
			sparse_mat[noof_nz][1] = j;
			sparse_mat[noof_nz][2] = *cur_mat;
	*/
			*(cur_sparse_mat++) = i;
			*(cur_sparse_mat++) = j;
			*(cur_sparse_mat++) = *cur_mat;

			noof_nz += 1; 
		}

		else
		{
			return -1;
		}
	}
	return noof_nz;
}

void main()
{
	int rows, cols;
	scanf("%d", &rows);
	scanf("%d", &cols);

	//int mat[rows][cols], sparse_mat[(rows * cols) / 3][3];
	int *mat, *sparse_mat;
	mat = (int*) malloc(sizeof(int) * rows * cols);
	sparse_mat = (int*) malloc(sizeof(int) * rows * cols);
	
	read_mat(rows, cols, mat);
	
	int noof_nz = convert_to_sparse(rows, cols, mat, sparse_mat);

	if( noof_nz == -1 )
		printf("\nMatrix is not sparse.");
	
	else
		write_mat(noof_nz, 3, sparse_mat);

	printf("\n");	

	free(mat);
	free(sparse_mat);
}












