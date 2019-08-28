// A precursor to SparseMatrixAddition

#include <stdio.h>

void read_arr(int size, int arr[])
{
	int *cur = arr;
	for( int i = 0; i < size; ++i, ++cur)
		scanf("%d", cur);
}

void write_mat(int rows, int cols, int *mat)
{
	printf("\n");
	int *cur = mat, i, j;

	if( !rows || !cols ) 
	{
		printf("Empty matrix.\n");
	}
	
	for( i = 0; i < rows; ++i, printf("\n") )
	for( j = 0; j < cols; ++j, ++cur )
		printf("%d ", *cur);
}

int convert_to_sparse( int size, int arr[], int sparse_arr[][2])
{
	int noof_nz = 0;
	for(int i = 0; i < size; ++i)
		if(arr[i])
		{
			sparse_arr[noof_nz][0] = i;
			sparse_arr[noof_nz][1] = arr[i];
			++noof_nz;	
		}
	printf("%d ", noof_nz);//	
	return noof_nz;
}

void copy (int rows, int cols, int* tohere, int* fromhere)
{
	int area = rows * cols;
	int *one = fromhere;
	int *two = tohere;
	
	for( int i = 0; i < area; ++i, ++one, ++two )
		*two = *one;
}

int add( int size_one, int sparse_arr_one[][2], int size_two, int sparse_arr_two[][2], int *sum )
{
	int *cur_one;
	int *cur_two;
	int *cur_sum = sum;
	int size_sum = 0;

	//If sparse_arr_one is empty
	if( !size_one )
	{
		copy( size_two, 2, sum, sparse_arr_two );
		return size_two;
	}

	
	//If sparse_arr_two is empty
	if( !size_two )
	{
		copy( size_one, 2, sum, sparse_arr_one );
		return size_one;
	}

	//Algorithm only works when size_one <= size_two
	//if( size_one >= size_two )
	if( sparse_arr_one[size_one-1][0] >= sparse_arr_two[size_two-1][0] )
	{
	    if(size_one != 0)
	    {
		    cur_one = sparse_arr_one;
	    	cur_two = sparse_arr_two;
	    }
	}
	else
	{
		cur_one = sparse_arr_two;
		cur_two = sparse_arr_one;
		int temp = size_one;
		size_one = size_two;
		size_two = temp;
	}

	int i, j = 0;

	for( i = 0; i < size_one; ++i, cur_one += 2 )
	{
		// cur_one is the position, cur_one+1 is the value

		//any elements in the sparse two which lie between previous cur one and present cur one are 		inserted to sum
		for( ; *cur_two < *cur_one; cur_two += 2 )
		{
			*cur_sum = *cur_two;
			*(cur_sum + 1) = *(cur_two + 1);
			cur_sum += 2;
			size_sum++; 
			//printf("%d %d %d \n", *cur_two, *(cur_two+1), i);//
		}

		if( *cur_two == *cur_one )
		{
			*cur_sum = *cur_one;
			*(cur_sum + 1) = *(cur_one + 1) + *(cur_two + 1); //Actual addition happens only here
			//printf("%d %d %d %d %d \n", *cur_one, *(cur_one + 1), *cur_two, *(cur_two+1), i);//
			cur_two += 2; 
			cur_sum += 2;
			size_sum++;
		}
		else
		{
			*cur_sum = *cur_one;
			*(cur_sum + 1) = *(cur_one + 1);
			cur_sum += 2;
			size_sum++;
			//printf("%d %d %d \n", *cur_one, *(cur_one+1), i);//
		}
	}

	return size_sum;
} 

/*Broken code
int add( int size_one, int sparse_arr_one[][2], int size_two, int sparse_arr_two[][2], int sum[][2] )
{
    int *cur_one = sparse_arr_one;
	int *cur_two = sparse_arr_two;
	int *cur_sum = sum;
	int size_sum = 0;
	int i, j;
	int limit_one = sparse_arr_one[size_one - 1][0];
	int limit_two = sparse_arr_two[size_two - 1][0];

    while(*cur_one <= limit_one)
    {
        while(*cur_one <= *cur_two)
        {
			*cur_sum = *cur_two;
			*(cur_sum + 1) = *(cur_two + 1);
			cur_sum += 2;
			size_sum++; 

            cur_two += 2;
            printf("\nFlag one"); //
        }        

		if( *cur_two == *cur_one )
		{
			*cur_sum = *cur_one;
			*(cur_sum + 1) = *(cur_one + 1) + *(cur_two + 1); //Actual addition happens only here
			cur_sum += 2;
			size_sum++;

			cur_two += 2; 
		}

        cur_one += 2;
            printf("\nFlag two"); //
    }
    
    while(*cur_two <= limit_two)
    {
        *cur_sum = *cur_two;
		*(cur_sum + 1) = *(cur_two + 1);
	    cur_sum += 2;
	    size_sum++; 

        cur_two += 2;
            printf("\nFlag three"); //
    }
}
*/
void main()
{
	int size;
	scanf("%d", &size);

	int arr_one[size];
	int arr_two[size];

	read_arr(size, arr_one);
	read_arr(size, arr_two);

	int sparse_arr_one[size][2];
	int sparse_arr_two[size][2];

	int size_one = convert_to_sparse(size, arr_one, sparse_arr_one);
	int size_two = convert_to_sparse(size, arr_two, sparse_arr_two);
	
	int sparse_sum[size_one + size_two][2];
	int size_sum = add(size_one, sparse_arr_one, size_two, sparse_arr_two, sparse_sum);
	write_mat(size_sum, 2, sparse_sum);
}
