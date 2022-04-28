#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"
#include "banker.h"

extern int NRES;  // number of resource types
extern int NPROC; // number of processes

int main(int argc, char *argv[])
{
  // TODO: attempt to open scenario file and scan data into allocated structures

  //---------FILE HANDELING------------
  if (argc == 1)
  {
    printf("Please enter in a file to be analyzed\n");
    exit(0);
  }
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL)
  {
    printf("File does not exist. Try again!\n");
    exit(0);
  }
  int *resourceArray; // hold the resources
  int **maxMatrix;    // hold the max matrix
  int **allocMatrix;  // hold the allocation matrix
  fscanf(fp, "%d", &NRES);
  fscanf(fp, "%d", &NPROC);
  int nextRes;
  // create the array of resources
  resourceArray = (int *)malloc(NRES * sizeof(int)); // malloc the resource Array
  for (int i = 0; i < NRES; i++)
  {
    fscanf(fp, "%d", &nextRes);
    resourceArray[i] = nextRes;
  }
  // malloc both the matricies
  maxMatrix = (int **)malloc(NPROC * sizeof(int *));
  allocMatrix = (int **)malloc(NPROC * sizeof(int *));
  for (int i = 0; i < NPROC; i++)
  {
    maxMatrix[i] = (int *)malloc(NRES * sizeof(int));
    allocMatrix[i] = (int *)malloc(NRES * sizeof(int));
  }
  // create the matrix for the max matrix
  for (int i = 0; i < NPROC; i++)
  {
    for (int j = 0; j < NRES; j++)
    {
      fscanf(fp, "%d", &nextRes);
      maxMatrix[i][j] = nextRes;
    }
  }
  // create the matrix for the allocation matrix
  for (int i = 0; i < NPROC; i++)
  {
    for (int j = 0; j < NRES; j++)
    {
      fscanf(fp, "%d", &nextRes);
      allocMatrix[i][j] = nextRes;
    }
  }

  //-----------SANITY CHECKS-------------

  // error message if the allocated resources exceed the total resources
  if (compareResources(allocMatrix, resourceArray) == false)
  {
    printf("Integrity test failed: allocated resources exceed total resources\n");
    exit(0);
  }
  // error message if max exceeds thread needs
  if (compareMatrices(maxMatrix, allocMatrix) == false)
  {
    exit(0);
  }

  // TODO: Run banker's safety algorithm
  // create the need matrix
  int **needMatrix;
  needMatrix = (int **)malloc(NPROC * sizeof(int *));
  for (int i = 0; i < NPROC; i++)
  {
    needMatrix[i] = (int *)malloc(NRES * sizeof(int));
  }
  needMatrix = createNeedMatrix(maxMatrix, allocMatrix, needMatrix);
  safetyAlgo(resourceArray, allocMatrix, needMatrix);
  return 0;
}