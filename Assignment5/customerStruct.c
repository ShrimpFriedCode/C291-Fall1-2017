#include <stdio.h>
#include <string.h>
int main(){
struct customer{
	char lastName[15];
	char firstName[15];
	unsigned int customerNumber;
	struct{
		char phoneNumber[11];
		char address[50];
		char city[15];
		char state[3];
		char zipCode[6];
		}personal;
	}customerRecord, *customerPtr;
	customerPtr = &customerRecord;

//a
strcpy(customerRecord.lastName, "Anderson");
//

printf("%s\n", (customerRecord.lastName));

//b
printf("%s\n", (customerPtr->lastName));

//C
strcpy(customerRecord.firstName, "Ethan");

printf("%s\n", (customerRecord.firstName));

//d

printf("%s\n", (customerPtr->firstName));

//e

printf("%d\n", customerRecord.customerNumber);

//f

printf("%d\n", (customerPtr->customerNumber));

//g
strcpy(customerRecord.personal.phoneNumber, "18121234567");

printf("%s\n", customerRecord.personal.phoneNumber);

//h
printf("%s\n", (customerPtr->personal.phoneNumber));

//i
printf("%p\n", &customerRecord.personal);

//j
printf("%p\n", &customerPtr->personal);

//k
strcpy(customerRecord.personal.city, "Bloomington");

printf("%s\n", customerRecord.personal.city);

//l
printf("%s\n", (customerPtr->personal.city));

//m
strcpy(customerRecord.personal.state, "IND");

printf("%s\n", customerRecord.personal.state);

//n
printf("%s\n", (customerPtr->personal.state));

//o
strcpy(customerRecord.personal.zipCode, "123456");

printf("%s\n", customerRecord.personal.zipCode);

//p
printf("%s\n", (customerPtr->personal.zipCode));

}
