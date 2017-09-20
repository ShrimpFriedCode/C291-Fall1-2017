#include <stdio.h>

int main(void){
	long value1 = 200000, value2;
	
	long *lPtr;//A
	lPtr = &value1;//B
	
	printf("Value pointed to by lPtr : %ld\n", *lPtr);//C

	value2 = *lPtr;//D
	
	printf("Value of value2 : %ld\n", value2);//E

	printf("Address of value1 : %p\n", &value1);//F

	printf("Address stored in lPtr : %p\n", lPtr);//G
	//This value is the same as &value1
}
