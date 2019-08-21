#include <stdio.h>
#include <math.h>
#include <limits.h>


void main()
{
	int number;
	scanf('%d", &number);
	char str[(int)(log10(INT_MAX)) + 3];
	sprintf(str, "%d", number);
	printf("%s", str);
}