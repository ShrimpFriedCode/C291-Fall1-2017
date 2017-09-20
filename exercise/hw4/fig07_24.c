// Fig. 7.24: fig07_24.c
// Card shuffling and dealing.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define SUITS 4
#define FACES 13
#define CARDS 52

// prototypes
void shuffle(unsigned int wDeck[][FACES]); // shuffling modifies wDeck
void deal(unsigned int wDeck[][FACES], const char *wFace[], 
   const char *wSuit[], int v[], int s[]); // dealing doesn't modify the arrays
void sort(int v[], int s[]);
int pair(int v[]);
int twoPair(int v[]);
int threeOfKind(int v[]);
int fourOfKind(int v[]);
int flush(int s[]);
int straight(int v[]);

int main(void)
{

   int values[5];
   int suitss[5];
   // initialize deck array
   unsigned int deck[SUITS][FACES] = { 0 };

   srand(time(NULL)); // seed random-number generator

   shuffle(deck); // shuffle the deck

   // initialize suit array                       
   const char *suit[SUITS] =            
      {"Hearts", "Diamonds", "Clubs", "Spades"};
   
   // initialize face array                   
   const char *face[FACES] =
      {"Ace", "Deuce", "Three", "Four",         
       "Five", "Six", "Seven", "Eight",         
       "Nine", "Ten", "Jack", "Queen", "King"};

   deal(deck, face, suit, values, suitss); // deal the deck

	sort(values, suitss);  	

	if(pair(values) == 1){
		printf("Pair found");
	}
	if(twoPair(values) == 1){
		printf("two pair found");
	}
	if(threeOfKind(values) == 1){
		printf("Three of a kind found");
	}
	if(fourOfKind(values) == 1){
		printf("Four of a kind");
	}
	if(flush(suitss) == 1){
		printf("Flush found");
	}
	if(straight(values) == 1){
		printf("Straight found");
	}
} 

// shuffle cards in deck
void shuffle(unsigned int wDeck[][FACES])
{
int card;
   // for each of the cards, choose slot of deck randomly
   for (card = 1; card <= CARDS; ++card) {
      size_t row; // row number
      size_t column; // column number

      // choose new random location until unoccupied slot found
      do {                                                        
         row = rand() % SUITS;                                   
         column = rand() % FACES;                             
      } while(wDeck[row][column] != 0); // end do...while

      // place card number in chosen slot of deck
      wDeck[row][column] = card;
   } 
}

// deal cards in deck
void deal(unsigned int wDeck[][FACES], const char *wFace[],
   const char *wSuit[], int v[], int s[])
{

int card, row, column;
   // deal each of the cards
   for (card = 1; card <= 5; ++card) {
      // loop through rows of wDeck
      for (row = 0; row < SUITS; ++row) {
         // loop through columns of wDeck for current row
         for (column = 0; column < FACES; ++column) {
            // if slot contains current card, display card
            if (wDeck[row][column] == card) {
               printf("%5s of %-8s%c", wFace[column], wSuit[row],
                  card % 2 == 0 ? '\n' : '\t');	 // 2-column format
		
		bool equal = (strcmp(wFace[column], wFace[0]) == 0); 
		
		if((strcmp(wFace[column], wFace[0])) == 0){//A
			v[card-1] = 1;
		}
		else if((strcmp(wFace[column], wFace[1])) == 0){//D
			v[card-1] = 2;
		}
		else if((strcmp(wFace[column], wFace[2])) == 0){//T
			v[card-1] = 3;
		}
		else if((strcmp(wFace[column], wFace[3])) == 0){//four
                        v[card-1] = 4;
                }
		else if((strcmp(wFace[column], wFace[4])) == 0){//five
                        v[card-1] = 5;
                }
		else if((strcmp(wFace[column], wFace[5])) == 0){//six
                        v[card-1] = 6;
                }
		else if((strcmp(wFace[column], wFace[6])) == 0){//seven
                        v[card-1] = 7;
                }
	 	else if((strcmp(wFace[column], wFace[7])) == 0){//eight
                        v[card-1] = 8;
                }
		else if((strcmp(wFace[column], wFace[8])) == 0){//nine
                        v[card-1] = 9;
                }
		else if((strcmp(wFace[column], wFace[9])) == 0){//ten
                        v[card-1] = 10;
                }
		else if((strcmp(wFace[column], wFace[10])) == 0){//J
                        v[card-1] = 11;
                }
		else if((strcmp(wFace[column], wFace[11])) == 0){//Q
                        v[card-1] = 12;
                }
		else{//K
			v[card-1] = 13;
		}
		
		if((strcmp(wSuit[row], wSuit[0])) == 0){//H
			s[card-1] = 1;
		}
		else if((strcmp(wSuit[row], wSuit[1])) == 0){//D
                        s[card-1] = 2;
                }
		else if((strcmp(wSuit[row], wSuit[2])) == 0){//C
                        s[card-1] = 3;
                }
		else if((strcmp(wSuit[row], wSuit[3])) == 0){//S
			s[card-1] = 4;
		}
		} 
         } 
      } 
   } 
}

void sort(int v[], int s[]){

	int i, j;
	for(i = 0; i < 5; i++){
		for(j = 0; j < 4; j++){
			if(v[j] > v[j+1]){
				int t = v[j];
				int ts = s[j];
				v[j] = v[j+1];
				s[j] = s[j+1];
				v[j+1] = t;
				s[j+1] = ts;
			}
		}
	}

}

int pair(int v[]){

int i, j, b = 0;

for(i = 0; i < 5; i++){
	for(j = i+1; j < 5; j++){
		if(v[i] == v[j] && i != j){
			b = 1;
		}
	
		}
	}
return b;
}

int threeOfKind(int v[]){

int i, j, b = 0;

for(i = 0; i < 5; i++){
        for(j = i+1; j < 5; j++){
                if(v[i] == v[j] && i != j){
                	if(j != 4){
				if(v[i] == v[j+1]){
					b = 1;
				}
			}
                }

                }
        }
return b;
}

int twoPair(int v[]){
int b = 0;

if(v[0] == v[1]){
	if(v[2] == v[3] && v[0] != v[3]){
		b = 1;
	}
	else if(v[3] == v[4] && v[0] != v[4]){
		b = 1;
	}
}
else if(v[1] == v[2]){
	if(v[3] == v[4] && v[1] != v[3]){
		b = 1;
	}
}
return b;
}

int fourOfKind(int v[]){
int b;

if(v[0] == v[1] == v[2] == v[3]){
	b = 1;
}
else if(v[1] == v[2] == v[3] == v[4]){
	b = 1;
}
return b;
}

int flush(int s[]){
int b  = 0;
if(s[0] == s[1] == s[2] == s[3] == s[4]){
	b = 1;
}
return b;
}

int straight(int v[]){
int b = 0;

if(v[0] == 1){
	if((v[2] == (v[1]+1) && v[3] == (v[2]+1) && v[4] == (v[3]+1) && (v[4]+1) == 14) || (v[1] == (v[0]+1) && v[2] == (v[1]+1) && v[3] == (v[2]+1) && v[4] == (v[3]+1))){
		b = 1;
	} 
}
else if((v[1] == (v[0]+1) && v[2] == (v[1]+1) && v[3] == (v[2]+1) && v[4] == (v[3]+1))){
	b = 1;
}
return b;
}

