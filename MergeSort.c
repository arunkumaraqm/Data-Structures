// Binary search on an array of integers
#include <stdio.h>
#include <stdlib.h>

void read_arr(int size, int* arr){

	for (; size > 0; --size, ++arr){
	
		scanf("%d", arr);
	}
}

int* merge_arrays(int sizeone, int sizetwo, int* one){

	int* res = calloc(sizeone + sizetwo);
	int* two = one + sizeone;
	int i = 0, j = 0;
	
	while (i < sizeone && j < sizetwo){
	
		if (one[i] < two[i]){
		
			res[cur] = one[i];
			++cur; ++i;
		}
		
		else{
		
			res[cur] = two[j];
			++cur; ++j;
		}
	}
	
	while (i < sizeone){
	
		res[cur] = one[i];
		++cur; ++i;
	}
	
	while (j < sizetwo){
	
		res[cur] = two[j];
		++cur; ++j;
	}
	
	return res;
}

int merge_sort(int end, int* arr){

	if (end > 0){
		
		mid = (beg + end) / 2;
		merge_sort(mid, arr);
		merge_sort(end - mid, arr + mid + 1); 
		int* res = merge_arrays(mid + 1, arr, end - mid + 1, arr + mid + 1);
		arr = res; //Will this work though?
	}
}
void main(){

	int size;
	scanf("%d", &size);
	
	int *arr = calloc(size, sizeof(int));
	read_arr(size, arr);
	
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























