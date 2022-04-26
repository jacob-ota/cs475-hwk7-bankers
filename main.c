#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

int main(int argc, char *argv[])
{
  // TODO: attempt to open scenario file and scan data into allocated structures
  FILE *fp = fopen(argv[1], "r");
  int NRES; 	// number of resource types
  int NPROC;	// number of processes
  int *resourceArray; //hold the resources
  int **maxMatrix; //hold the max matrix
  int **allocMatrix; //hold the allocation matrix
  fscanf(fp, "%d", &NRES);
  fscanf(fp, "%d", &NPROC);
  int nextRes;
  //create the array of resources
  resourceArray = (int *) malloc(NRES * sizeof(int)); //malloc the resource Array
  for(int i = 0; i < NRES; i++) {
    fscanf(fp, "%d", &nextRes);
    resourceArray[i] = nextRes;
  }
  //malloc both the matricies
  maxMatrix = (int **)malloc(NPROC * sizeof(int *));
  allocMatrix = (int **)malloc(NPROC * sizeof(int *));
  for(int i = 0; i < NPROC; i++) {
    maxMatrix[i] = (int *)malloc(NRES * sizeof(int));
    allocMatrix[i] = (int *)malloc(NRES * sizeof(int));
  }
  //create the matrix for the max matrix
  for(int i = 0; i < NPROC; i++) {
    for(int j = 0; j < NRES; j++) {
      fscanf(fp, "%d", &nextRes);
      maxMatrix[i][j] = nextRes;
    }
  }
  //create the matrix for the allocation matrix
  for(int i = 0; i < NPROC; i++) {
    for(int j = 0; j < NRES; j++) {
      fscanf(fp, "%d", &nextRes);
      allocMatrix[i][j] = nextRes;
    }
  }
  // TODO: Run banker's safety algorithm


  return 0;
}