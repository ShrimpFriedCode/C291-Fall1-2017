/* main.c --- 
 *
 * Filename: main.c
 * Description: Basic C program to print out hello world! 
 * Author: Adeel Bhutta, Ethan Anderson
 *
*/

#include <stdio.h>
#include <unistd.h>

int main(void) {

  printf("Hello World!\n"); 
  int pos = 0;
  while(10 > pos){
    sleep(1);
    printf(".\n");
}

return(0);

}
