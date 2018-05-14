#include<time.h>
#include<unistd.h>
#include <stdio.h>
#include <stdlib.h>

void matrixMultiply(int n, int **A, int **B, int **C);
void initialize_matrix(int ** mat, int n);

int main(void){
	clock_t start_t;
	clock_t end_t;
	int n = 2000;


	int **A; 
	int **B;  
	int **C;


	A = (int**)malloc(n * sizeof(int*));
	for (int index=0;index<n;++index){
    	A[index] = (int*)calloc(n, sizeof(int));
	}

	B = (int**)malloc(n * sizeof(int*));
	for (int index=0;index<n;++index){
    	B[index] = (int*)calloc(n, sizeof(int));
	}

	C = (int**)malloc(n * sizeof(int*));
	for (int index=0;index<n;++index){
    	C[index] = (int*)calloc(n, sizeof(int));
	}


	start_t = clock();
	matrixMultiply(n, A, B, C);
	end_t = clock();
    printf("\ntime elapsed is %f\n",(double)(end_t - start_t)/CLOCKS_PER_SEC);
    free(A);
    free(B);
    free(C);
	return 0;
}

// void initialize_matrix(int ** mat, int n){
// 	mat = (int**)malloc(n * sizeof(int*));
// 	for (int index=0;index<n;++index){
//     	mat[index] = (int*)calloc(n, sizeof(int));
// 	}
// }



void matrixMultiply(int n, int **A, int **B, int **C){
	for(int i=0; i<n;i++){
		for(int j=0; j <n;j++){
			int sum = 0;
			for (int k=0;k<n;k++){
				sum = sum+A[i][k]*B[k][j];
			}
			C[i][j]= sum;
		}
	}
} 

void transpose(int **mat){
	mat_copy = (int**)malloc(n * sizeof(int*));
	for (int index=0;index<n;++index){
    	mat_copy[index] = (int*)calloc(n, sizeof(int));
	}
}


}
