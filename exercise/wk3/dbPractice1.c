#include <stdio.h> //include for print and scan

double average(double num_scores, double sum)//take sum and number of elements that create sum
{
        return sum / num_scores;//divide
}

int sum(int num_scores, int arr[])//take number of elements in arr[] which is our values
{
    int sumN = 0;//initialize the sum
    int i;//initialize itterator
    for (i=0; i<num_scores; i++)//itterate through arr
            sumN += arr[i];//add values to sum
    return sumN;//return
}

int main() 
{   
	int numberOfVal; //initialize the number of values dependent on user input
        printf( "Debugging Practice 1 - Quiz 3, Q3\n\n");//print title
	printf( "Please enter the number of values to be used: ");//query user
	scanf(" %d", &numberOfVal);//get user input
	int values[numberOfVal];//create array of size numberOfVal
	int i;//initialize itterator
	for (i=0; i<numberOfVal; i++){
		printf("Enter value number %d : ", (i+1)); //ask user for nth values
        	scanf(" %d", &values[i]);//assign

	}
	
    double sigma = sum(numberOfVal, values);//get the sum of all numbers in values[]
    double avg = average(numberOfVal, sigma);//get the average
    printf( "The average of %f / %d is: %f\n",sigma, numberOfVal, avg );//print results 
    return 0;
}

