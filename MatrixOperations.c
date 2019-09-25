#include  <stdio.h>

int add(int one, int two){ return one + two; }

int subtract(int one, int two){ return one - two;}

typedef int (*operation) (int, int);

int add_or_subtract(char aors, int rows, int cols, int *one, int *two, 
					int *result){

	operation calc = (aors == 'a')? add: subtract;

	int i, size = rows * cols;
	for (i = 0; i < size; ++i)
		*(result + i) = calc( *(one + i), *(two + i) );

}

void input_mat(int rows, int cols, int mat[rows][cols])
{
        int i, j;
        for(i = 0; i < rows; ++i)
                for(j = 0; j < cols; scanf("%d", &mat[i][j]), ++j);
}

void output_mat(int rows, int cols, int mat[rows][cols])
{
        int i, j;
        for(i = 0; i < rows; printf("\n"), ++i)
                for(j = 0; j < cols; printf("%d ", mat[i][j]), ++j);
}

void multiply(int rows1, int rows2, int cols2, int mat1[rows1][rows2], int mat2[rows2][cols2], 
              int result[rows1][cols2])
{
        int i, j, k, *cur = &result[0][0];
        
        for(i = 0; i < rows1; ++i)
        {
                for(j = 0; j < cols2; ++j, ++cur)
                {
                        for(*cur = 0, k = 0; k < rows2; ++k)
                        {
                                *cur +=  mat1[i][k] * mat2[k][j];
                        }                       
                }
        }

}

void main()
{
	int rows1, cols1;
	scanf("%d%d", &rows1, &cols1);
	int one[rows1][cols1];
	input_mat(rows1, cols1, one);	
	
	int rows2, cols2;
	scanf("%d%d", &rows2, &cols2);
	int two[rows2][cols2];
	input_mat(rows2, cols2, two);

	int choice;
	scanf("%d", &choice);

	if(choice == 1 || choice == 2){
		if(rows1 != rows2 || cols1 != cols2){
			printf("The two matrices are not compatible for addition/subtraction.\n");
			return;
    	}

		int result[rows1][cols1];
    	add_or_subtract('a' - 1 + choice, rows1, cols1, one, two, result);
		output_mat(rows1, cols1, result);    
	}
	else{
		if(rows2 != cols1){
			printf("The two matrices are not compatible for multiplication.\n");
			return;
		}

		int result[rows1][cols2];
    	multiply(rows1, rows2, cols2, one, two, result);
		output_mat(rows1, cols2, result);
	}
	
}


