/* declarations related to banker's algorithm */
bool safetyAlgo(int *resources, int **alloc, int **need);
bool isFinished(int *finished);
int indexUnfinished(int *finished, int counter);
bool isidxUnfinished(int *finished, int counter);