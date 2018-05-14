#include<time.h>
#include<unistd.h>
#include <stdio.h>
#include <stdlib.h>

void matrixMultiply(int n, int **A, int **B, int **C);
void initialize_matrix(int ** mat, int n);
void transpose(int **mat, int n);
void rowMultiply(int n, int **A, int **B, int **C);
void loop4Unfold(int n, int **A, int **B, int **C);
void loop8Unfold(int n, int **A, int **B, int **C);
void loop16Unfold(int n, int **A, int **B, int **C);
void blocked_multiply(int n, int ** A, int **B_M, int **C, int B);
void row_blocked_multiply(int n, int ** A, int **B_M, int **C, int B);
void row_4_blocked_multiply(int n, int ** A, int **B_M, int **C, int B);
void row_8_blocked_multiply(int n, int ** A, int **B_M, int **C, int B);
void row_16_blocked_multiply(int n, int ** A, int **B_M, int **C, int B);


int main(void){
	clock_t start_t;
	clock_t end_t;
	int n = 2000;


	int **A; 
	int **B;  
	int **C;

	srand(time(NULL));

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



	for (int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			A[i][j] = rand();
			B[i][j] = rand();
			C[i][j] = rand();
		}
	}	


	start_t = clock();
	transpose(B, n);
	row_16_blocked_multiply(n, A, B, C, 25);
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


void transpose(int **mat, int n){
	int ** mat_copy;
	mat_copy = (int**)malloc(n * sizeof(int*));
	for (int index=0; index<n;++index){
    	mat_copy[index] = (int*)calloc(n, sizeof(int));
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			mat_copy[i][j] = mat[i][j];
		}
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			mat[i][j] = mat_copy[j][i];
		}
	}

	free(mat_copy);

}

void rowMultiply(int n, int **A, int **B, int **C){
	for(int i=0; i<n; i++){
		for(int j=0; j <n;j++){
			int sum = 0;
			for (int k=0;k<n;k++){
				sum = sum+A[i][k]*B[j][k];
			}
			C[i][j]= sum;
		}
	}
}



void loop4Unfold(int n, int **A, int **B, int **C){
	for(int i=0; i<n;i++){
		int sum = 0;
		for(int j=0; j <n;j++){
			sum = 0;
			for (int k=0;k<n; k += 4){
				sum = sum+A[i][k]*B[k][j];
				sum = sum+A[i][k + 1]*B[k + 1][j];
				sum = sum+A[i][k + 2]*B[k + 2][j];
				sum = sum+A[i][k + 3]*B[k + 3][j];

			}
			C[i][j]= sum;
		}
	}
}


void loop8Unfold(int n, int **A, int **B, int **C){
	for(int i=0; i<n;i++){
		int sum = 0;
		for(int j=0; j <n;j++){
			sum = 0;
			for (int k=0;k<n; k += 8){
				sum = sum+A[i][k]*B[k][j];
				sum = sum+A[i][k + 1]*B[k + 1][j];
				sum = sum+A[i][k + 2]*B[k + 2][j];
				sum = sum+A[i][k + 3]*B[k + 3][j];
				sum = sum+A[i][k + 4]*B[k + 4][j];
				sum = sum+A[i][k + 5]*B[k + 5][j];
				sum = sum+A[i][k + 6]*B[k + 6][j];
				sum = sum+A[i][k + 7]*B[k + 7][j];

			}
			C[i][j]= sum;
		}
	}
}



void loop16Unfold(int n, int **A, int **B, int **C){
	for(int i=0; i<n;i++){
		int sum = 0;
		for(int j=0; j <n;j++){
			sum = 0;
			for (int k=0;k<n; k += 16){
				sum = sum+A[i][k]*B[k][j];
				sum = sum+A[i][k + 1]*B[k + 1][j];
				sum = sum+A[i][k + 2]*B[k + 2][j];
				sum = sum+A[i][k + 3]*B[k + 3][j];
				sum = sum+A[i][k + 4]*B[k + 4][j];
				sum = sum+A[i][k + 5]*B[k + 5][j];
				sum = sum+A[i][k + 6]*B[k + 6][j];
				sum = sum+A[i][k + 7]*B[k + 7][j];
				sum = sum+A[i][k + 8]*B[k + 8][j];
				sum = sum+A[i][k + 9]*B[k + 9][j];
				sum = sum+A[i][k + 10]*B[k + 10][j];
				sum = sum+A[i][k + 11]*B[k + 11][j];
				sum = sum+A[i][k + 12]*B[k + 12][j];
				sum = sum+A[i][k + 13]*B[k + 13][j];
				sum = sum+A[i][k + 14]*B[k + 14][j];
				sum = sum+A[i][k + 15]*B[k + 15][j];

			}
			C[i][j]= sum;
		}
	}
}

void blocked_multiply(int n, int ** A, int **B_M, int **C, int B){
	for(int bi = 0; bi < n; bi += B){
		for(int bj = 0; bj < n; bj += B){
			for(int bk = 0; bk < n; bk += B){
				for(int i = 0; i < B; i ++){
					for(int j = 0; j < B; j++){
						int sum = C[bi + i][bj + j];
						for(int k = 0; k < B;k++){
							sum += A[bi + i][bk + k] * B_M[bk + k][bj + j];
						}
						C[bi + i][bj + j] = sum;
					}
				}
			}
		}
	}
}


void row_blocked_multiply(int n, int ** A, int **B_M, int **C, int B){
	for(int bi = 0; bi < n; bi += B){
		for(int bj = 0; bj < n; bj += B){
			for(int bk = 0; bk < n; bk += B){
				for(int i = 0; i < B; i ++){
					for(int j = 0; j < B; j++){
						int sum = C[bi + i][bj + j];
						for(int k = 0; k < B;k++){
							sum += A[bi + i][bk + k] * B_M[bj + j][bk + k];
						}
						C[bi + i][bj + j] = sum;
					}
				}
			}
		}
	}
}



void row_4_blocked_multiply(int n, int ** A, int **B_M, int **C, int B){
	for(int bi = 0; bi < n; bi += B){
		for(int bj = 0; bj < n; bj += B){
			for(int bk = 0; bk < n; bk += B){
				for(int i = 0; i < B; i ++){
					for(int j = 0; j < B; j++){
						int sum = C[bi + i][bj + j];
						for(int k = 0; k <= B - 4;k+= 4){
							sum += A[bi + i][bk + k] * B_M[bk + k][bj + j];
							sum += A[bi + i][bk + k + 1] * B_M[bk + k + 1][bj + j];
							sum += A[bi + i][bk + k + 2] * B_M[bk + k + 2][bj + j];
							sum += A[bi + i][bk + k + 3] * B_M[bk + k + 3][bj + j];

						}
						C[bi + i][bj + j] = sum;
					}
				}
			}
		}
	}
}


void row_8_blocked_multiply(int n, int ** A, int **B_M, int **C, int B){
	for(int bi = 0; bi < n; bi += B){
		for(int bj = 0; bj < n; bj += B){
			for(int bk = 0; bk < n; bk += B){
				for(int i = 0; i < B; i ++){
					for(int j = 0; j < B; j++){
						int sum = C[bi + i][bj + j];
						for(int k = 0; k <= B - 8;k+= 8){
							sum += A[bi + i][bk + k] * B_M[bk + k][bj + j];
							sum += A[bi + i][bk + k + 1] * B_M[bk + k + 1][bj + j];
							sum += A[bi + i][bk + k + 2] * B_M[bk + k + 2][bj + j];
							sum += A[bi + i][bk + k + 3] * B_M[bk + k + 3][bj + j];
							sum += A[bi + i][bk + k + 4] * B_M[bk + k + 4][bj + j];
							sum += A[bi + i][bk + k + 5] * B_M[bk + k + 5][bj + j];
							sum += A[bi + i][bk + k + 6] * B_M[bk + k + 6][bj + j];							sum += A[bi + i][bk + k + 1] * B_M[bk + k + 1][bj + j];
							sum += A[bi + i][bk + k + 7] * B_M[bk + k + 7][bj + j];
						}
						C[bi + i][bj + j] = sum;
					}
				}
			}
		}
	}
}


void row_16_blocked_multiply(int n, int ** A, int **B_M, int **C, int B){
	for(int bi = 0; bi < n; bi += B){
		for(int bj = 0; bj < n; bj += B){
			for(int bk = 0; bk < n; bk += B){
				for(int i = 0; i < B; i ++){
					for(int j = 0; j < B; j++){
						int sum = C[bi + i][bj + j];
						for(int k = 0; k <= B - 16;k+= 16){
							sum += A[bi + i][bk + k] * B_M[bk + k][bj + j];
							sum += A[bi + i][bk + k + 1] * B_M[bk + k + 1][bj + j];
							sum += A[bi + i][bk + k + 2] * B_M[bk + k + 2][bj + j];
							sum += A[bi + i][bk + k + 3] * B_M[bk + k + 3][bj + j];
							sum += A[bi + i][bk + k + 4] * B_M[bk + k + 4][bj + j];
							sum += A[bi + i][bk + k + 5] * B_M[bk + k + 5][bj + j];
							sum += A[bi + i][bk + k + 6] * B_M[bk + k + 6][bj + j];							sum += A[bi + i][bk + k + 1] * B_M[bk + k + 1][bj + j];
							sum += A[bi + i][bk + k + 7] * B_M[bk + k + 7][bj + j];
							sum += A[bi + i][bk + k + 8] * B_M[bk + k + 8][bj + j];
							sum += A[bi + i][bk + k + 9] * B_M[bk + k + 9][bj + j];
							sum += A[bi + i][bk + k + 10] * B_M[bk + k + 10][bj + j];
							sum += A[bi + i][bk + k + 11] * B_M[bk + k + 11][bj + j];
							sum += A[bi + i][bk + k + 12] * B_M[bk + k + 12][bj + j];
							sum += A[bi + i][bk + k + 13] * B_M[bk + k + 13][bj + j];							sum += A[bi + i][bk + k + 1] * B_M[bk + k + 1][bj + j];
							sum += A[bi + i][bk + k + 14] * B_M[bk + k + 14][bj + j];
							sum += A[bi + i][bk + k + 15] * B_M[bk + k + 15][bj + j];
						}
						C[bi + i][bj + j] = sum;
					}
				}
			}
		}
	}
}





