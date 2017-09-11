#include <stdio.h>//include statement for print statements

int size;//initialize global var size

int display(int matrix1[][size])//take in the martrix array
{   
    int i; int j;//initlialize itterators
    for (i=0; i<size; i++) {
        for (j=0; j<size; j++){
            printf("%d, ", matrix1[i][j]);//print the current martix index
	    }
	printf("\n");//new line for new array row
    }
    return 0;
}

int main()
{
    int i;
    int j;//initialize itterators
    size = 5;//set size
    int Matrix1[size][size];//create new square matrix
    for (i=0; i<size; i++){
        for (j=0; j<size; j++){
            Matrix1[i][j]= i+j;//set values of matrix
	}
    }
    display(Matrix1);//display the matrix
    return 0;
}

