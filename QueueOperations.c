#include <stdio.h>
#include <limits.h>
#define MAXQUEUESIZE 5

struct Queue
{
	int front, rear;
	int arr[MAXQUEUESIZE];
} queue;

void enqueue()
{
    if (queue.rear == MAXQUEUESIZE - 1)
    printf("Queue Overflow.\n");
    
    else
    {
        if (queue.front == - 1) queue.front = 0;

        int new_element;
        scanf("%d", &new_element);
        queue.arr[++queue.rear] = new_element;
    }
    
} 
 
void dequeue()
{
    if (queue.front == - 1)
    {
        printf("Queue Underflow \n");
        return ;
    }
    else
    {
        printf("Element deleted from queue is : %d\n", queue.arr[queue.front]);
        ++queue.front;

        if (queue.front > queue.rear) queue.front = queue.rear = -1;
    }
} 

 
void display()
{
    if (queue.front == - 1)
        printf("Queue is empty \n");
    else
    {
        printf("Queue is : \n");
        for (int i = queue.front; i <= queue.rear; i++)
            printf("%d ", queue.arr[i]);
        printf("\n");
    }
}

void main()
{
	int choice;
	int elem;
	queue.front = queue.rear = -1;
	
	
	do{
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 1  :  enqueue(); break;
			case 2  :  dequeue(); break;
			case 3  :  display(); break;
			default :  choice = 0;
		}
	}while(choice);
}
