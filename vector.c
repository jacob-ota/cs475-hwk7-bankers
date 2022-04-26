#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"

// TODO - Define vector and matrix operations
int NPROC;
int NRES;
int *resourceArrayCopy; //hold the resources deep copy

/**
 * Clone (deep copy) vectors/matrices
 * 
 * @param vector the vector of the resource array
 */
void cloneVector(int *vector) {
    resourceArrayCopy = (int *) malloc(NRES * sizeof(int)); //malloc the resource Array
    for(int i = 0; i < NRES; i++) {
        resourceArrayCopy[i] = vector[i];
    }
}

/**
 * Compare the max matrix and the alloc matrix
 * 
 * @param maxMatrix the matrix that holds the max demand for each resource type
 * @param allocMatrix the matrix that holds every threads need/allocation
 * 
 * @return true if each threads needs do not exceed the max demands, false otherwise 
 */
bool compareMatrices(int **maxMatrix, int **allocMatrix) {
    for(int i = 0; i < NPROC; i++) {
        for(int j = 0; j < NRES; j++) {
            if(maxMatrix[i][j] < allocMatrix[i][j]) {
                printf("Integrity test failed: allocated resources exceed demand for Thread %d\n", i);
                printf("Need %d of resource %d\n", maxMatrix[i][j] - allocMatrix[i][j], j);
                return false;
            }
        }
    }
    return true;
}

/**
 * Compare the alloc matrix with the copied resource array
 * 
 * @param allocMatrix the matrix that holds every threads need/allocation
 * 
 * @return true if the allocated resources do not exceed the total number of resources, false otherwise 
 */
bool compareResources(int **allocMatrix) {
    for(int i = 0; i < NPROC; i++) {
        for(int j = 0; j < NRES; j++) {
            if(allocMatrix[i][j] > resourceArrayCopy[j]) {
                return false;
            }
        }
    }
    return true;
}


/**
 * Add/Subtract two vectors/matrices
 * 
 */


/**
 * Print the contents of the vector/matrices
 * 
 */
void printMatrix(int **matrix) {
    for(int i = 0; i < NPROC; i++) {
        for(int j = 0; j < NRES; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}