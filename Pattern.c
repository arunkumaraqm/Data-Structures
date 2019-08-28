#include <stdio.h>

void pattern(int noof_rows, int noof_cols, int mat[noof_rows][noof_cols])
{
	int i, j, adj, cur_num = 1; 
	int row = noof_rows - 1, col = noof_cols - 1;
	int area = noof_rows * noof_cols;
	
	i = 0;
	for( adj = 1; cur_num < area; ++adj )
	{
		for( j = adj - 1; j <= col - (adj - 1); ++j )
			mat[i][j] = cur_num++;
		--j;

		for( i = adj; i <= row - (adj - 1); ++i )
			mat[i][j] = cur_num++;
		--i;

		for( j = col - adj; j >= adj - 1; --j )
			mat[i][j] = cur_num++;
		++j;

		for( i = row - adj; i >= adj; --i )
			mat[i][j] = cur_num++;
		++i;
	}	
}

void write_mat(int noof_rows, int noof_cols, int mat[noof_rows][noof_cols])
{
	int i, j;
	for( i = 0; i < noof_rows; ++i )
	{
		for( j = 0; j < noof_cols; ++j )
		{	
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}

void main()
{
	int noof_rows, noof_cols;
	scanf("%d", &noof_rows);
	scanf("%d", &noof_cols);
	printf("\n");

	int mat[noof_rows][noof_cols];
	pattern(noof_rows, noof_cols, mat);
	write_mat(noof_rows, noof_cols, mat);	
}