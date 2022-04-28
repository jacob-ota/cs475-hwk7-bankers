
// TODO: function prototypes of vector and matrix operations
int *cloneVector(int *vector, int *copyInto);
bool compareMatrices(int **maxMatrix, int **allocMatrix);
bool compareResources(int **allocMatrix, int *resourceArray);
bool compareNeedWork(int *needArray, int *workArray);
int **createNeedMatrix(int **maxMatrix, int **allocMatrix, int **needMatrix);
int *createAllocTotal(int *allocTotal, int **allocMatrix);
int *subResourceAlloc(int *resourceArray, int *allocTotal);
int *createNewWork(int *workArray, int *alloc);
void printMatrix(int **matrix);