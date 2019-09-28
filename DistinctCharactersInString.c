#include <stdio.h>
#include <string.h> // For strlen()
#include <stdlib.h> // For calloc()

// Returns 1 if str contains item
int contains(char* str, char item){

	// Pointer increment as opposed to array subscripting to avoid using i
	for ( ; *str; ++str ){

		if (*str == item){
			return 1;
		}
	}

	return 0;
}

// All distinct characters from str and added to new_str
void unique(char* str, char* new_str){ 

	char* cur = new_str; // cur is short for current

	// Pointer increment as opposed to array subscripting to avoid using i
	for ( ; *str; ++str ){

		if ( !contains(new_str, *str) ){

			*cur = *str;
			++cur;
		}
	}
}

void main(){

	char str[50];
	scanf("%s", str);
	
	int	len = strlen(str);
	char *new_str = calloc( len, sizeof(char) );
	if ( !new_str ) return; // Heap memory unavailable

	unique(str, new_str);
	printf("%s", new_str);

	free(new_str);
}
