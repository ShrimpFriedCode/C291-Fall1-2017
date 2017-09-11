/* Instructions:
 *
 *1. Following on from what you have learnt in class today, write a program to return the grade associated with a range of marks.

  2. The range of marks and the associated grades are as follows:
     a. 91-100 = A
     b. 81-90 = B
     c. 71-80 = C
     d. less than or equal to 70 is a fail grade and should be given an F
     e. greater than 100 is invalid and your code should print "Invalid"
  
  3. Use the skeleton code provided below to create a new function "printGrade" with its appropriate 
     data type for input of marks. For example, printGrade(<data type> marks). 
  
  4. Use print statements in your function to display the grade. For example, if the input marks is 77, the output should read: 

	"Your grade is : C"

  5. Please adhere to standard C syntax conventions and use comments to explain your code. Failure to do so will result in a penalty.
 *
 *
 * */


#include<stdio.h>

int printGrade(int marks){//take user's current grade mark

	if(marks > 100){
		printf("Invalid.");//if greater than 100, invalid grade
	}
	else if(marks >= 91){
		printf("Your grade is : A");//if greater than or equal to 91, and less than 101, grade must be A
	}
	else if(marks >= 81){
		printf("Your grade is : B");//if greater than/equal to 81, and less than 91, grade must be B
	}
	else if(marks >= 71){
		printf("Your grade is : C");//of greater than/equal to 71, and less than 81, grade must be C
	}
	else{
		printf("Your grade is : F");//else, it must be F
	}

}

int main(void){
	char ch;//initialize response char
	int marks;//initialize student marks
	do{//while the user has not agreed to exit
		printf("Enter marks : " );//prompt user for input
		scanf(" %d", &marks);//assign user input
		printGrade(marks);//determine and print their letter grade
		printf("\nDo you want to continue? (Y/N)");//ask if user wants to exit
		scanf(" %c",&ch); //do not modify this.
	}while(ch == 'y'|| ch == 'Y');//if yes, continue
	return 0;
}








