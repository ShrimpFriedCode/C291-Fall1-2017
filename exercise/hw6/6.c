#include <stdio.h>


int main(){

int selector = 0;
int split[7];
int length[7];
char* list[7];
int number = 0;
int i = 0;

int n1, n2, n3, n4, n5, n6, n7;

char two[3] = {'A', 'B', 'C'};
char three[3] = {'D', 'E', 'F'};
char four[3] = {'G', 'H', 'I'};
char five[3] = {'J', 'K', 'L'};
char six[3] = {'M', 'N', 'O'};
char seven[4] = {'P', 'Q', 'R', 'S'};
char eight[3] = {'T', 'U', 'V'};
char nine[4] = {'W', 'X', 'Y', 'Z'};
char empty[1] = {""};

printf("Please enter a seven digit number : \n");
scanf("%7d", &number);

while (number > 0){

	int digit = number % 10;
	split[i] = digit;
	number /= 10;
	i++;
}

int first = 0;
int last = 6;
int temp;

while(first < last){

	temp = split[first];
	split[first] = split[last];
	split[last] = temp;
	first++;
	last--;
}

for(i = 0; i < 7; i++){

	if(split[i] == 7 || split[i] == 9){
		length[i] = 4;	
	}
	else if(split[i] == 0 || split[i] == 1){
		length[i] = 1;
	}
	else{
		length[i] = 3;
	}

	switch(split[i]){

		case 2:
			list[i] = two;
			break;
		case 3:
			list[i] = three;
			break;
		case 4:
			list[i] = four;
			break;
		case 5:
			list[i] = five;
			break;
		case 6:
			list[i] = six;
			break;
		case 7:
			list[i] = seven;
			break;
		case 8:
			list[i] = eight;
			break;
		case 9:
			list[i] = nine;
			break;
		default:
			list[i] = empty;
	}

}

FILE *nums;
nums = fopen("words.txt", "w+");


char word[7];

for(n1 = 0; n1 < length[0]; n1++){
	word[0] = list[0][n1];
	for(n2 = 0; n2 < length[1]; n2++){
		word[1] = list[1][n2];
		for(n3 = 0; n3 < length[2]; n3++){
			word[2] = list[2][n3];
			for(n4 = 0; n4 < length[3]; n4++){
				word[3] = list[3][n4];
				for(n5 = 0; n5 < length[4]; n5++){
					word[4] = list[4][n5];
					for(n6 = 0; n6 < length[5]; n6++){
						word[5] = list[5][n6];
						for(n7 = 0; n7 < length[6]; n7++){
							word[6] = list[6][n7];
							
							for(i = 0; i < 7; i++){
								fputc(word[i], nums);
							}
							putc('\n', nums);
						}
					}
				}
			}
		}
	}
}

}
