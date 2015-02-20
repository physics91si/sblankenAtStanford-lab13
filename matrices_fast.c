/*Physics 91 SI
 *Stanford University
 *Julian Kates-Harbeck
 *
 *This file is an optimized version of matrices.c
 */


#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/*This function computes the index into a 2D matrix laid out in contiguous memory

A call like

Matrix[i][j]

is equivalent to

Matrix[ index(N,i,j) ] .

Note that the order of the two indices matters! The first index gives the row and the second index gives the column.
*/
int idx(int size,int index1, int index2) {
	return index1*size + index2;
}

void transpose(float* orig, float* store, int N) {
	for(int i = 0; i<N;i++) {
		for(int j = 0; j<N;j++) {
			orig[idx(N,i,j)] = store[idx(N,j,i)];
		}
	}
}

/*This function multiplies 2 N by N*/
void matmul(float* mat1, float* mat2, float* result,int N) {
	float* tmp = malloc(sizeof(float)*N*N);
	float sum = 0;
	transpose(mat2,tmp,N);	
	for(int i = 0; i<N;i++) {
		for(int j = 0; j<N;j++) {
			sum = 0;
			for(int k = 0; k<N; k++) {
				sum += mat1[idx(N,i,k)]*tmp[idx(N,j,k)];
			}
			result[idx(N,i,j)] = sum;
		}

	}
	free(tmp);
}



/*This function adds 2 N by N matrices*/
void matsum(float* mat1, float* mat2, float* result, int N) {
	int ix = 0;	
	for(int i = 0; i<N;i++) {
		for(int j = 0; j<N;j++) {
			ix = idx(N,i,j);
			result[ix] = mat1[ix] + mat2[ix];
		}
	}

}

/*fill the two matrices with random numbers*/
void fill_matrices(float* mat1, float* mat2, int N) {
	for(int i = 0; i<N;i++) {
		for(int j = 0; j<N;j++) {
			mat1[idx(N,i,j)] = rand();
			mat2[idx(N,i,j)] = rand();
		}
	}
}

int main(int argc, const char *argv[]){
	int N = 0;	
	if(argc == 2) {
		N = atoi(argv[1]);
	}
	else {
		printf("Invalid arguments. Provide one argument: the size of the matrices as an integer.");
		exit(0);
	}

/*Allocate the memory to store the matrices. Each one is an N by N matrix of floats*/

    float* mat1 = malloc(sizeof(float)*N*N);
    float* mat2 = malloc(sizeof(float)*N*N);
    float* result = malloc(sizeof(float)*N*N);
	
/*fill the two matrices with random numbers*/
	fill_matrices(mat1,mat2,N);	

/*+++++++++++++++++++++++++++++++++Timing++++++++++++++++++++++++++++++++++++++++++*/

	clock_t start = clock();

/*Uncomment the operation that you want to run*/	
	matmul( mat1, mat2, result, N);
	//matsum( mat1, mat2, result, N);


	printf("Time elapsed: %f milliseconds\n",( (double) clock() - start)*1000/CLOCKS_PER_SEC);

/*+++++++++++++++++++++++++++++++End of timing+++++++++++++++++++++++++++++++++++++*/
	free(mat1);
	free(mat2);
	free(result);
	return 0;
}	
