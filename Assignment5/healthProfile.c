//Ethan Anderson

#include <stdio.h>
#include <string.h>


struct healthProfile{//struct for HP

	char fname[15], lname[15], gender;
	int height;
	int weight;
		struct dob{

			int month;
			int day;
			int year;

		}DOB;//accessor for dob struct
};

typedef struct healthProfile HealthProfile; //set as type


void setHP(HealthProfile *ret, char firstn[], char lastn[], char gen, int h, int w, int mon, int da, int ye){
	
	strncpy(ret->fname, firstn, 15);//copy arrays over

	strncpy(ret->lname, lastn, 15);
	
	ret->gender = gen;//copy gender char
	
	ret->height = h;//copy h, w
	ret->weight = w;
	
	ret->DOB.month = mon;//copt dob data
	ret->DOB.day = da;
	ret->DOB.year = ye;
	
}

int getAge(HealthProfile *hp){

	return 2017 - hp->DOB.year;//subtract current year by birth year for age

}

int maxHr(HealthProfile *hp){

	return 220 - getAge(hp);//forumula for heart rate

}

int * targetHr(HealthProfile *hp){

	static int range[2];
	int maxH = maxHr(hp);//add range as array for ease of printf use

	range[0] = maxH * .5;
	range[1] = maxH * .85;
	
	return range;
}

int getBMI(HealthProfile *hp){

	return (hp->weight * 703)/(hp->height * hp->height);//formula for BMI
}

int main(){



//prompt

char userF[15];
printf("Please enter your first name : ");
scanf(" %s", &userF);

char userL[15];
printf("Please enter your last name : ");
scanf(" %s", &userL); 
	
char gen;
printf("Please enter first letter of your gender : ");
scanf(" %c", &gen);

int d;
printf("Please enter day you were born (numeric) : ");
scanf(" %d", &d);

int m;
printf("Please enter month you were born (numeric) : ");
scanf(" %d", &m);

int y;
printf("Please enter year you were born (numeric) : ");
scanf(" %d", &y);

int h;
printf("Please enter your height in Inches : ");
scanf(" %d", &h);

int w;
printf("Please enter your weight in pounds : ");
scanf(" %d", &w);

HealthProfile userHP;//create new HP

HealthProfile *userPtr = &userHP;//create pointer

setHP(userPtr, userF, userL, gen, h, w, m, d, y);//update HP with user input

printf("\nYour age is : %d\n", getAge(userPtr));//print statements

printf("Your BMI is : %d\n", getBMI(userPtr));

printf("Your maximum heart rate is : %d\n", maxHr(userPtr));

printf("Your target heart rate is between %d and %d\n\n\n", targetHr(userPtr)[0], targetHr(userPtr)[1]);

printf("BMI VALUES\nUnderweight: \tless than 18.5\nNormal: \tbetween 18.5 and 24.9\nOverweight: \tbetween 25 and 29.9\nObese: \t\t30 or greater\n\n\n");//BMI chart

}
