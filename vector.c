#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"

// TODO - Define vector and matrix operations
int NPROC;
int NRES;

/**
 * Clone (deep copy) vectors/matrices
 *
 * @param vector the vector of the resource array
 *
 * @return a int array of the copied vector
 */
int *cloneVector(int *vector, int *copyInto)
{
    for (int i = 0; i < NRES; i++)
    {
        copyInto[i] = vector[i];
    }
    return copyInto;
}

/**
 * Compare the max matrix and the alloc matrix
 *
 * @param maxMatrix the matrix that holds the max demand for each resource type
 * @param allocMatrix the matrix that holds every threads need/allocation
 *
 * @return true if each threads needs do not exceed the max demands, false otherwise
 */
bool compareMatrices(int **maxMatrix, int **allocMatrix)
{
    //compare the matrices if max at a certain spot is lower than alloc print out an error message
    for (int i = 0; i < NPROC; i++)
    {
        for (int j = 0; j < NRES; j++)
        {
            if (maxMatrix[i][j] < allocMatrix[i][j])
            {
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
 * @param resourceArray the resource array
 *
 * @return true if the allocated resources do not exceed the total number of resources, false otherwise
 */
bool compareResources(int **allocMatrix, int *resourceArray)
{
    //if alloc at any spot is greater than its resource available then it is false
    for (int i = 0; i < NPROC; i++)
    {
        for (int j = 0; j < NRES; j++)
        {
            if (allocMatrix[i][j] > resourceArray[j])
            {
                return false;
            }
        }
    }
    return true;
}

/**
 * Compare the need array with the work array
 *
 * @param needArray a given thread in the need matrix
 * @param workArray compare with the work array
 *
 * @return true if the needArray is less than or equal to the workArray, false otherwise
 */
bool compareNeedWork(int *needArray, int *workArray)
{
    //if the need array at i is greater than the work array at i then it is false
    for (int i = 0; i < NRES; i++)
    {
        //checks if need[i] <= work
        if (needArray[i] > workArray[i])
        {
            return false;
        }
    }
    return true;
}

/**
 * Subtract two vectors/matrices to create the Need Matrix
 *
 * @param maxMatrix the max Matrix
 * @param allocMatrix the alloc matrix
 * @param needMatrix the need Matrix to be initialized by adding the other matricies
 *
 * @return the Need Matrix
 */
int **createNeedMatrix(int **maxMatrix, int **allocMatrix, int **needMatrix)
{
    for (int i = 0; i < NPROC; i++)
    {
        //create the need matrix by subtracting the max matrix by the alloc matrix
        for (int j = 0; j < NRES; j++)
        {
            needMatrix[i][j] = maxMatrix[i][j] - allocMatrix[i][j];
        }
    }
    return needMatrix;
}

/**
 * Add up all alloc matrix resources to get an alloc total
 *
 * @param alloctotal the max Matrix
 * @param allocMatrix the alloc matrix
 * 
 * @return the alloctotal array
 */
int *createAllocTotal(int *allocTotal, int **allocMatrix)
{
    for(int i = 0; i < NPROC; i++) {
        for(int j = 0; j < NRES; j++) {
            allocTotal[j] += allocMatrix[i][j];
        }
    }
    return allocTotal;
}

/**
 * Subtract the resource array from the alloc total to get the available resources 
 * 
 * @param resourceArray the resource array
 * @param allocTotal the total of allocated resources
 * 
 * @return the updated resource array
 */
int *subResourceAlloc(int *resourceArray, int *allocTotal) {
    for(int i = 0; i < NRES; i++) {
        resourceArray[i] -= allocTotal[i];
    }
    return resourceArray;
}

/**
 * Add two vectors to create the new work
 *
 * @param workArray the work Array
 * @param alloc the alloc array
 *
 * @return the new work array
 */
int *createNewWork(int *workArray, int *alloc)
{
    //work += alloc[i]
    for (int i = 0; i < NRES; i++)
    {
        workArray[i] += alloc[i];
    }
    return workArray;
}

/**
 * Print the contents of the vector/matrices
 *
 */
void printMatrix(int **matrix)
{
    for (int i = 0; i < NPROC; i++)
    {
        for (int j = 0; j < NRES; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}