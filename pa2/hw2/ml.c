#include <stdio.h>
#include <stdlib.h>

double** multiplyMatrix(double** matA, double** matB, int r1, int c1, int r2, int c2, double** result);
double** transposeMatrix(double **mat, int row, int col, double** matTran);
double** inverseMatrix(double** matA, int dimension, double** matI);

//I WASNT ABLE TO FIGURE OUT HOW TO CALL THE POINTERS WITH THE METHODS AND EQUAL THEM TO THE RETURN VALUE OF THE METHOD 
//SO I PUT THE POINTERS WITHIN THE METHOD
//I WASNT SURE IF I WAS ABLE TO DO THIS BUT I HOPE I WAS

//Copy of methods given
// int main(int argc, char** argv){

//     // your code goes here
	
// 	return 0;
// }

// double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2)
// {
//     double** result=malloc(r1*sizeof(double*)); 
    
//     // your code goes here
    
//     return result;
// }


// double** transposeMatrix(double** mat, int row, int col)
// {
  
// 	double** matTran=malloc(col*sizeof(double*)); 
    
//     // your code goes here
    
//     return matTran;        
// }


// double** inverseMatrix(double **matA, int dimension)
// {

//     double** matI=malloc(dimension*sizeof(double*)); 

//     // your code goes here
    
// 	return matI;
// }


void helper1Print(double** ptr, int x, int y) {

	int i;
	int j;

	for (i = x-1; i >= 0; i--) {
		for (j = 0; j < y; j++) {
			if (j == y-1) {
				printf("%0.0lf\n",ptr[i][j]);
				break;
			}
			printf("%0.0lf	",ptr[i][j]);
		}
	}
}

double** multiplyMatrix(double** matA, double** matB, int r1, int c1, int r2, int c2, double** result) { 
	//double** result=malloc(r1*sizeof(double*)); 
	int i;
	int j;
	int x;
	int y = r2 - 1;
	double total = 0;

	for (i = r1 - 1; i >= 0; i--) {
		for (j = 0; j < c2; j++) {
			for (x = 0; x < c1; x++) {
				total = total + (matA[i][x] * matB[y][j]);
				y--;
			}

			result[i][j] = total;
			y = r2-1;
			total = 0;
		}
	}
	return result;
}

// double** print(double ** matrix, int row, int col){
// 	for (i = row-1; i >= 0; i--) {
// 		for (j = col-1; j >= 0; j--) {		
// 	}
// }

double** transposeMatrix(double** mat, int row, int col, double** matTran) {	// Finds the Transpose of a Matrix
	//double** matTran=malloc(col*sizeof(double*));
	int i;
	int j;
	int x = 0;
	int y = 0;
	for (i = row - 1; i >= 0; i--) {
		for (j = col - 1; j >= 0; j--) {
			matTran[x][y] = mat[i][j];
			x++;
		}

		y++;
		x = 0;
	}
	return matTran;
}

double** inverseMatrix(double** matA, int dimension, double** matI) {
	//double** matI=malloc(dimension*sizeof(double*)); 
	double** ptr = malloc(dimension * sizeof(double*));
	int i;
	int j;

	for (i = 0; i < dimension; i++) {
		ptr[i] = malloc(sizeof(double) * dimension * 2);
	}

	int x = (dimension * 2) - 1;
	int y = 0;
	int z;
	int increment = 0;
	double d;
	double q;

	for (i = 0; i < dimension; i++) {
		for (j = 0; j < dimension * 2; j++) {
			if (j < dimension) {
				ptr[i][j] = matA[i][j];
			}else{
				if (j != x) {
					ptr[i][j] = 0;
				} else {
					ptr[i][j] = 1;
					y = 1;
				}
			}
		}
		if (y == 1) {
			x--;
		}
	}
	
	y = 0;

	for (i = dimension - 1; i >= 0; i--) {
		if (i < dimension - 1) {
			for (j = 0; j < y; j++) {
				if (ptr[i][j] != 0) {
					increment = 1;
				}
			}
			if (increment == 1) {
				for (j = 0; j < y; j++) {
					int x2;

					if (ptr[i][j] != 0) {
						z = dimension - 1 - j;

						if (ptr[z][j] == ptr[i][j]) {
							for (x2 = j; x2 < dimension * 2; x2++) {
								ptr[i][x2] = ptr[i][x2] - ptr[z][x2];
							}
						}else{
							d = ptr[i][j];

							for (x2 = j; x2 < dimension * 2; x2++) {
								ptr[i][x2] = ptr[i][x2] - (d * ptr[z][x2]);
							}
						}
					}
				}
			}
		}
		if (ptr[i][y] != 1) {
			q = ptr[i][y];

			for (j = 0; j < dimension*2; j++) {
				if (ptr[i][j] != 0) {
					ptr[i][j] = ptr[i][j] / q;
				}
			}
		}
		y++;
	}
	
	y = dimension - 2;

	for (i = 1; i < dimension; i++) {
		increment = 0;
		for (j = dimension - 1; j > y; j--) {
			if (ptr[i][j] != 0) {
				increment = 1;
			}
		}
		if (increment == 1) {
			for (j = dimension - 1; j > y; j--) {
				int x3;
				if (ptr[i][j] != 0) {
					int z = dimension - 1 - j;

					if (ptr[z][j] == ptr[i][j]) {
						for (x3 = j; x3 < dimension * 2; x3++) {
							ptr[i][x3] = ptr[i][x3] - ptr[z][x3];
						}
					}else{
						double d = ptr[i][j];

						for (x3 = j; x3 < dimension * 2; x3++) {
							ptr[i][x3] = ptr[i][x3] - (d * ptr[z][x3]);
						}
					}
				}
			}
		}
		y--;
	}
	
	for (i = 0; i < dimension; i++) {
		for (j = dimension; j < dimension * 2; j++) {
			matI[i][j-dimension] = ptr[i][j];
		}
	}
	return matI;
}

int main(int argc, char** argv) {
	if (argc != 3) {
		return 0;
	}

	FILE* file = fopen(argv[1], "r");

	if (file == NULL){
		return 0;
	} 

	int x;
	int y;
	int i;
	int j;
	int a;
	double d;

	fscanf(file, "%d\n", &x);
	x = x + 1;

	fscanf(file, "%d\n", &y);

	
	double** matrixA = malloc(y * sizeof(double*));	
	double** matrixB = malloc(y * sizeof(double*));

	for (i = 0; i < y; i++) {
		matrixA[i] = malloc(sizeof(double) * x);
	}
	
	for (i = 0; i < y; i++) {
		matrixB[i] = malloc(sizeof(double));
	}
	
	for (i = 0; i < y; i++) {
		matrixA[i][0] = 1;
	}
	
	for (i = y - 1; i >= 0; i--) {			
		for (j = 0; j < x; j++) {
			if (j != x - 1) {
				fscanf(file, "%lf,", &d);
				matrixA[i][j+1] = d;

			}else{
				fscanf(file, "%lf\n", &d);
				matrixB[i][0] = d;
			}
		}
	}

	fclose(file);
	
	FILE* file2 = fopen(argv[2], "r");

	if (file2 == NULL){
		return 0;
	}

	fscanf(file2, "%d\n", &a);
	
	double** matrixA2 = malloc(sizeof(double*) * a);	

	for (i = 0; i < a; i++) {
		matrixA2[i] = malloc(sizeof(double) * x);
	}
	
	for (i = 0; i < a; i++) {
		matrixA2[i][0] = 1;
	}
	
	for (i = a - 1; i >= 0; i--) {			
		for (j = 0; j < x - 1; j++) {
			if (j != x - 2) {
				fscanf(file2, "%lf,", &d);
				matrixA2[i][j+1] = d;

			}else{
				fscanf(file2, "%lf\n", &d);
				matrixA2[i][j + 1] = d;
			}
		}
	}

	fclose(file2);
						
	double** matrixTranspose = malloc(sizeof(double*) * x);	
	double** matrixTransposeTimesmatrixA = malloc(sizeof(double*) * x);		
	double** matrixInverse = malloc(sizeof(double*) * x);	
	double** matrixInverseTimesmatrixTranspose = malloc(sizeof(double*) * x);	
	double **mitmtTimesMatrixB = malloc(sizeof(double*) * y);		
	double **resultQ = malloc(sizeof(double*) * a);	

	for (i = 0; i < x; i++) {
		matrixTranspose[i] = malloc(sizeof(double) * y);
	}

	for (i = 0; i < x; i++) {
		matrixTransposeTimesmatrixA[i] = malloc(sizeof(double) * x);
	}
	
	for (i = 0; i < x; i++) {
		matrixInverse[i] = malloc(sizeof(double) * x);
	}
	
	for (i = 0; i < x; i++) {
		matrixInverseTimesmatrixTranspose[i] = malloc(sizeof(double) * y);
	}

	for (i = 0; i < y; i++) {
		mitmtTimesMatrixB[i] = malloc(sizeof(double));
	}

	for (i = 0; i < a; i++) {
		resultQ[i] = malloc(sizeof(double));
	}
	
	transposeMatrix(matrixA, y, x, matrixTranspose);
	multiplyMatrix(matrixTranspose, matrixA, x, y,y, x, matrixTransposeTimesmatrixA);
	inverseMatrix(matrixTransposeTimesmatrixA, x, matrixInverse);
	multiplyMatrix(matrixInverse, matrixTranspose, x, x, x, y, matrixInverseTimesmatrixTranspose);
	multiplyMatrix(matrixInverseTimesmatrixTranspose, matrixB, x, y, y, 1, mitmtTimesMatrixB);
	multiplyMatrix(matrixA2, mitmtTimesMatrixB, a, x, x, 1, resultQ);
	helper1Print(resultQ, a, 1);

	//solves for it
	//now to free everything

	//for(i = 0; i , demension; i++){
	// 	free(matrix[i]);
	// }
	// free(matrix);
	
	for (i = 0; i < y; i++){
		free(matrixA[i]);
	}
	free(matrixA);

	for (i = 0; i < x; i++){
		free(matrixTranspose[i]);
	}
	free(matrixTranspose);

	for (i = 0; i < x; i++){
		free(matrixTransposeTimesmatrixA[i]);
	}
	free(matrixTransposeTimesmatrixA);

	for (i = 0; i < x; i++){
		free(matrixInverse[i]);
	}
	free(matrixInverse);

	for (i = 0; i < x; i++){
		free(matrixInverseTimesmatrixTranspose[i]);
	}
	free(matrixInverseTimesmatrixTranspose);

	for (i = 0; i < y; i++){
		free(matrixB[i]);
	}
	free(matrixB);

	for (i = 0; i < y; i++){
		free(mitmtTimesMatrixB[i]);
	}
	free(mitmtTimesMatrixB);

	for (i = 0; i < a; i++){
		free(matrixA2[i]);
	}
	free(matrixA2);

	for (i = 0; i < a; i++){
		free(resultQ[i]);
	}
	free(resultQ);

	return 0;
}