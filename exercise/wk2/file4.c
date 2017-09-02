/*Debugging quiz - File No: 4 */
/* This program should perform the duties of a basic calculator */
// Check for possible logical errors and rectify them 

#include <stdio.h>

int main(){
	char input;
	float num1, num2, result;
	printf("Welcome to the Calculator\nOperation choices:\tAddition(A)\n\t\t\tSubtraction(S)\n\t\t\tMultiplication(M)\n\t\t\tDivision(D)\nEnter choice: ");
	scanf(" %c", &input);
	if(input == 'A' || input == 'S' || input == 'M' || input == 'D'){
		printf("Enter both numbers in required sequence:\n");
		printf("Enter number 1: ");
		scanf(" %f", &num1);
		printf("Enter number 2: ");
		scanf(" %f", &num2);
		switch(input){
			case 'A': result = num1 + num2;
          			break;
			case 'S': result = num1 - num2;
          			break;
			case 'M': result = num1 * num2;
          			break;
			case 'D': if(num2 != 0 || num2 != 0.0){
				result = num1 / num2;
				}
				else{
				printf("Cannot divide by zero.\n");
				}		//Are there any logical errors possible? If so, how will you solve it? 
	 			break; 			  
			default: break;
		}
		if(input == 'D' && num2 == 0){
			printf("No answer due to invalid input.\n");	
		}
		else{
			printf("The answer = %f\n", result);
		}
	}
	else{
		printf("Please choose a valid operation\n");
	}
	return(0);
}
