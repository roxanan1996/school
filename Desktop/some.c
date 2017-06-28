
#include <stdio.h>


int main () {
	
	int x = 5;
	float f = 1.2;
	double d = 1.2;
	int a;
	a = x == (int) (float) x;
	printf("1: %d\n", a);
	
	a = x == (int) (double) x;
	printf("2: %d\n", a);

	a = f == (float) (double) f;
	printf("3: %d\n", a);

	a = d == (double) (float) d;
	printf("2: %d\n", a);
	
	a = d == (float) d;
	printf("4: %d\n", a);


	a = f ==  -(-f);
	printf("5: %d\n", a);
	
	a = 2/3 == 2/3.0;
	
	printf("5: %d\n", a);
}