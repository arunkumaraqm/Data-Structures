// Merge sort on an array of integers
#include <stdio.h>

// Read and write functions
void read_arr(int size, int* arr){

	for (; size > 0; --size, ++arr){
	
		scanf("%d", arr);
	}
}
void write_arr(int size, int* arr){

	for (; size > 0; --size, ++arr){
	
		printf("%d ", *arr);
	}
	printf("\n");
}

// Function to copy one array onto another
void copy(int size, int* from, int* to){

	for (int i = 0; i < size; ++i)
		to[i] = from[i];
}

// The actual merge sort
void merge_sort(int beg, int mid, int end, int* arr){

	int sizeone = (mid) - (beg) + 1;
	int sizetwo = (end) - (mid + 1) + 1;
	int cur = beg, i = 0, j = 0;

	// Copying the two halves into one and two respectively so that the original array can be modified
	int one[sizeone], two[sizetwo];
	copy(sizeone, arr + beg, one);
	copy(sizetwo, arr + mid + 1, two); 

	
	while (i < sizeone && j < sizetwo){
	
		if (one[i] < two[j]){
		
			arr[cur] = one[i];
			++cur; ++i;
		}
		
		else{
		
			arr[cur] = two[j];
			++cur; ++j;
		}
	}

	// For remaining elements (if any) in one
	while (i < sizeone){
	
		arr[cur] = one[i];
		++cur; ++i;
	}
	
	// For remaining elements (if any) in two
	while (j < sizetwo){
	
		arr[cur] = two[j];
		++cur; ++j;
	}

}

void split_and_merge(int beg, int end, int* arr){

	if(beg < end){ // beg is only equal to end when there is one element 

		int mid = (beg + end)/2;
		split_and_merge(beg, mid, arr);
		split_and_merge(mid + 1, end, arr);
		merge_sort(beg, mid, end, arr);
	}
}

#define MERGE_SORT(size, arr) split_and_merge(0, size - 1, arr)

void main(){

	int size;
	scanf("%d", &size);
	
	int arr[size];
	read_arr(size, arr);

	MERGE_SORT(size, arr);
	write_arr(size, arr);	
}

/*
Test 1
0

Test 2
1
60

Test 3
2
60 50

Test 4
2
50 60

Test 5
5
10 20 30 40 50

Test 6
5
10 40 20 30 50

Test 7
5
50 40 30 20 10

Test 8
50
50 59 23 83 79 32 16 60 87 61 84 45 5 13 62 96 12 51 75 53 42 14 39 92 80 30 34 24 8 98 69 55 6 22 15 11 48 47 28 72 43 7 1 57 82 36 18 71 26 89

*/
