// Binary search on an array of integers
#include <stdio.h>
#include <stdlib.h>

void read_arr(int size, int* arr){

	for (; size > 0; --size, ++arr){
	
		scanf("%d", arr);
	}
}

int binary_search(int beg, int end, int* arr, int item){

	if (beg > end) return -1;
	
	int mid = (beg + end) / 2;
	
	if (arr[mid] < item){
	
		return binary_search(mid + 1, end, arr, item);
	}
	else if (arr[mid] > item){
	
		return binary_search(beg, mid - 1, arr, item);
	}
	else{
	
		return mid;
	}
}
void main(){

	int size;
	scanf("%d", &size);
	
	int arr[size];
	read_arr(size, arr);
	
	int item;
	scanf("%d", &item);
	
	// Indices start from zero
	int position = binary_search(0 , size-1, arr, item);
	if (position == -1){
	
		printf("Not found.\n");
	}
	else{
	
		printf("Found at %d.\n", position);
	}
}

/*
Test 1:

5
10 20 30 40 50
40

Test 2:

0
70

Test 3:

1
60
60

Test 4:

6
10 21 32 43 65 90
90


*/






















