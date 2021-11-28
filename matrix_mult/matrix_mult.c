//PROGRAM FOR 5X5 MATRIX MULTIPLICATION 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int i,j,k;
	int N=5;
	int A[N][N];
	int B[N][N];
	srand(time(0));
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
			A[i][j] = rand() % 10;
	}

	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
			B[i][j] = 0;
	}

	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			for(k=0;k<N;k++)
				B[i][j] += A[i][k] * A[k][j];
		}
	}
	
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%6d\t",B[i][j]);
		}
		printf("\n");
	}
}
