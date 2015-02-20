/*Physics 91 SI, 2013
 *Stanford University
 *Julian Kates-Harbeck
 *
 *This program implements timed matrix multiplication and matrix addition on an N by N square matrix of random numbers, where N is read in as the single command line argument*/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>



/*This function computes the index into a 2D matrix laid out in contiguous memory

Indexing such as

Matrix[i][j]

can be accomplished by using

Matrix[ idx(N,i,j) ] .

Note that the order of the two indices matters! The first index gives the row and the second index gives the column.
*/
int idx(int size,int index1, int index2) {
	return index1*size + index2;
}


/*This function multiplies 2 N by N*/
void matmul(float* mat1, float* mat2, float* result,int N) {
	for(int i = 0; i<N;i++) {
		for(int j = 0; j<N;j++) {
			result[idx(N,i,j)] = 0;
			for(int k = 0; k<N; k++) {
				result[idx(N,i,j)] += mat1[idx(N,i,k)]*mat2[idx(N,k,j)];
			}
		}

	}
}


/*This function adds 2 N by N matrices*/
void matsum(float* mat1, float* mat2, float* result, int N) {
	
	for(int i = 0; i<N;i++) {
		for(int j = 0; j<N;j++) {
			result[idx(N,j,i)] = mat1[idx(N,j,i)] + mat2[idx(N,j,i)];
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



/*parse the command line for N, the matrix size*/
int parse(int argc, const char *argv[]) {
	int N = 0;
	if(argc == 2) {
		N = atoi(argv[1]);
	}
	else {
		printf("Invalid arguments. Provide one argument: the size of the matrices as an integer.");
		exit(0);
	}
	return N;
}



int main(int argc, const char *argv[]){
	
/*Read in the matrix size from the command line*/
	int N = parse(argc,argv);	

/*Allocate the memory to store the matrices. Each one is an N by N matrix of floats*/

    float* mat1 = malloc(sizeof(float)*N*N);
    float* mat2 = malloc(sizeof(float)*N*N);
    float* result = malloc(sizeof(float)*N*N);
	
/*fill the two matrices with random numbers*/
	fill_matrices(mat1,mat2,N);	

/*+++++++++++++++++Timing+++++++++++++++++++++++*/

	clock_t start = clock();

/**********************Beginning of Computation****************************/

/*This is where the actual computation happens.
 *Uncomment the operation that you want to run.*/
	
	//matmul( mat1, mat2, result, N);
	matsum( mat1, mat2, result, N);

/*************************End of Computation*******************************/



	printf("Time elapsed: %f milliseconds\n",( (double) clock() - start)*1000/CLOCKS_PER_SEC);

/*++++++++++++++++End of timing+++++++++++++++++++*/
	
/*Free the memory allocated at the beginning*/
	free(mat1);
	free(mat2);
	free(result);
	return 0;
}	

