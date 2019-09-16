#include <stdio.h>
#include <limits.h>
#define capacity 5

struct Deque
{
	int left;
	int right;
	int arr[capacity];
};

int read_element()
{
	int element;
	scanf("%d", &element);
	return element;
}

int is_empty(struct Deque* deque)
{
	return deque->left == -1;
}

// This function is never used.
int is_full(struct Deque* deque)
{
	return (deque->left == 0 && deque->right == capacity - 1);
}

void constructor(struct Deque* deque)
{
	deque->left = deque->right = -1;
}


void insert_left(struct Deque* deque)
{	
	if (deque->left == 0)
	{
		if(deque->right == capacity - 1)
		{
			printf("\nQueue Full.");
			return;
		}	
		else 
		{
			printf("\nNo more insertions to the left possible.");
			return;	
		}
	}
	
	else if (is_empty(deque))
	{
		deque->left = deque->right = 0;
	}
	     
	else
	{
		deque->left -= 1;
	}
	
	deque->arr[deque->left] = read_element();
}

void insert_right(struct Deque* deque)
{
	if (deque->right == capacity - 1)
	{
		if (deque->left == 0)
		{	
			printf("\nQueue Full.");
			return;
		}

		else 
		{
			printf("\nNo more insertions to the right possible.");
			return;	
		}
	}
		
	else if (is_empty(deque))
	{
		deque->left = deque->right = 0;
	}
	     
	else
	{
		deque->right += 1;
	}
	
	deque->arr[deque->right] = read_element();
}

int delete_left(struct Deque* deque) 
{
	if (is_empty(deque))
	{
		printf("\nQueue Empty.");
		return INT_MIN;
	}
	
	int element = deque->arr[deque->left];
	
	if (deque->left == deque->right)
	{
		deque->left = deque->right = -1;
	}
	else 
	{
		deque->left+=1;
	}
	
	return element;
}

int delete_right(struct Deque* deque) 
{
	if (is_empty(deque))
	{
		printf("\nQueue Empty.");
		return INT_MIN;
	}
	
	int element = deque->arr[deque->right];
	
	if (deque->left == deque->right)
	{
		deque->left = deque->right = -1;
	}
	else 
	{
		deque->right-=1;
	}
	
	return element;
}

void display(struct Deque* deque)
{
	int i;
	
	printf("\nContents of deque: ");
	
	if( is_empty(deque) )
	{
		printf("None");
		return;
	}
	
	for( i = deque->left; i <= deque->right; ++i )
	{
		printf("%d ", deque->arr[i]);
	}
}

void main()
{
	int choice;
	int deleted_element;
	struct Deque deque;
	
	constructor(&deque);
	
	do{
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 1  :  insert_left(&deque);
					   break;
			case 2  :  insert_right(&deque);
					   break;
			case 3  :  deleted_element = delete_left(&deque);
					   if( deleted_element != INT_MIN ) printf("\nDeleted Element: %d", deleted_element);
					   break;
			case 4  :  deleted_element = delete_right(&deque);
					   if( deleted_element != INT_MIN ) printf("\nDeleted Element: %d", deleted_element);
					   break;
			case 5  :  display(&deque);
					   break;   
			default :  choice = 6;
		}
		
		printf("\n");
		
	}while(choice != 6);


}
