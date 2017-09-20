#include <stdio.h>

int main(void){

	int SIZE = 5, i, j = 2;//A
	unsigned int values[SIZE];
	for(i = 0; i < SIZE; i++){
		values[i] = j;
		j+=2;
	}

	unsigned int *vPtr;//B
	
	for(i = 0;i < SIZE; i++){//C
		printf("%d\n", values[i]);
	}

	vPtr = values; vPtr = &values[0];//D

	for(i = 0; i < SIZE;i++){//E
		printf("%d\n", *(vPtr+i));
	} 

	for(i = 0; i < SIZE; i++){//F
		printf("%d\n", *(values+i));
	}

	for(i = 0; i < SIZE; i++){//G
		printf("%d\n", vPtr[i]);
	}

	unsigned int h;
	h = values[4], h = *(values+4), h = vPtr[4], h = *(vPtr+4);//H
	printf("The 5th element in values is: %d\n", h); 

	//I: The address would be 1002506, the values would be 8
	//J: The referenced address is 1002500, the values would be 2
}
