#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int** matrix;
int matrixSize;

// Function prototypes
void determinent(void);
void output(void);
int cofactor(int row, int col);
void freeMatrix(int** matrix, int size);
int determinantOfMatrix(int** matrix, int size);
int** createSubMatrix(int** matrix, int size, int excluding_row, int excluding_col);

int main(void) {
    printf("Enter the size of the matrix: ");
    scanf("%d", &matrixSize);
    
    matrix = (int**)malloc(matrixSize * sizeof(int*));
    for (int i = 0; i < matrixSize; i++)
        matrix[i] = (int*)malloc(matrixSize * sizeof(int));
        
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            printf("Enter value for row [%d] column [%d]: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }
    
    output();
    determinent();
    
    // Free allocated memory
    freeMatrix(matrix, matrixSize);
    
    return 0;
}

void output(void) {
    printf("Matrix:\n");
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            printf("     %d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void determinent(void) {
    int det = determinantOfMatrix(matrix, matrixSize);
    printf("Determinant of the matrix = %d\n", det);
}

int determinantOfMatrix(int** matrix, int size) {
    if (size == 1) {
        return matrix[0][0];
    }
    
    if (size == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    int det = 0;
    for (int col = 0; col < size; col++) {
        int** subMatrix = createSubMatrix(matrix, size, 0, col);
        det += pow(-1, col) * matrix[0][col] * determinantOfMatrix(subMatrix, size - 1);
        freeMatrix(subMatrix, size - 1);
    }
    
    return det;
}

int** createSubMatrix(int** matrix, int size, int excluding_row, int excluding_col) {
    int** subMatrix = (int**)malloc((size - 1) * sizeof(int*));
    for (int i = 0; i < size - 1; i++)
        subMatrix[i] = (int*)malloc((size - 1) * sizeof(int));
    
    int rowOffset = 0, colOffset = 0;
    for (int i = 0; i < size; i++) {
        if (i == excluding_row) {
            rowOffset = 1;
            continue;
        }
        colOffset = 0;
        for (int j = 0; j < size; j++) {
            if (j == excluding_col) {
                colOffset = 1;
                continue;
            }
            subMatrix[i - rowOffset][j - colOffset] = matrix[i][j];
        }
    }
    
    return subMatrix;
}

void freeMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
