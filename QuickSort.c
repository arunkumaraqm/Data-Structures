// Quick sort on an array of integers
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

// Quick sort function 
// Partitioning is done in the same function
void quick_sort(int beg, int end, int* arr){

	if (beg < end){

		// Here, pivot is chosen as the median element
		int i = beg, j = end, pivot = arr[(beg + end)/2];
		
		while (1){

			while (arr[i] < pivot) ++i;
			while (arr[j] > pivot) --j;

			if (i == j){

				quick_sort(beg, i - 1, arr); // Quick sort on the first partition
				quick_sort(i + 1, end, arr); // Quick sort on the second partition
				break;
			}
			
			else{

				// Swap using xor
				arr[i] = arr[i] ^ arr[j];
				arr[j] = arr[i] ^ arr[j];
				arr[i] = arr[i] ^ arr[j];
			}
		}
	}
}

#define QUICK_SORT(size, arr) quick_sort(0, size - 1, arr)

void main(){

	int size;
	scanf("%d", &size);
	
	int arr[size];
	read_arr(size, arr);

	QUICK_SORT(size, arr);
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




