
int main(void) 
{   
    int size=5, Matrix1[size][size];
	for (int i=0; i<1; i++) 
 	    for (int j=0; j<size; j++) 
            Matrix1[i][j]=i+j;
	display(int Matrix1[][]);
    return 0.0;
}

void display(int Matrix1[][], int size)
{   
    int size = 6;
	for (int i=0; i<size; i++) {
 	    for (int j=0; j<size; j++) 
            printf("%d ,", Matrix1[i][j]);
        printf("\n");
        }
    return;
}
