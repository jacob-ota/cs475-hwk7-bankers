#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"
#include "banker.h"

// TODO - Safety Algorithm goes here
int NPROC;
int NRES;

/**
 * Bankers Safety Algorithm runs here
 *
 */
bool safetyAlgo(int *resources, int **alloc, int **need)
{
    int *work = (int *)malloc(NRES * sizeof(int));
    work = cloneVector(resources);
    int *finished = (int *)malloc(NPROC * sizeof(int));
    for (int i = 0; i < NPROC; i++)
    {
        finished[i] = 0;
    }
    int *trackProcesses = (int *)malloc(NPROC * sizeof(int));
    int tracker = 0;
    int counter = indexUnfinished(finished, 0);
    while (!isFinished(finished))
    {
        if (compareNeedWork(need[counter], work) && isidxUnfinished(finished, counter))
        {
            work = createNewWork(work, alloc[counter]);
            finished[counter] = 1;
            trackProcesses[tracker] = counter;
            counter++;
            if (counter >= NPROC)
            {
                counter = 0;
                counter = indexUnfinished(finished, counter);
            }
            else
            {
                counter = indexUnfinished(finished, counter);
            }
            tracker++;
        }
        else
        {
            counter++;
            if (counter >= NPROC)
            {
                counter = 0;
                counter = indexUnfinished(finished, counter);
            }
            else
            {
                counter = indexUnfinished(finished, counter);
            }
        }
    }
    if (isFinished(finished))
    {
        printf("SAFE: ");
        for (int i = 0; i < NPROC; i++)
        {
            printf("T%d ", trackProcesses[i]);
        }
        printf("\n");
        return true;
    }
    printf("UNSAFE: ");
    for (int i = 0; i < NPROC; i++)
    {
        if (finished[i] == 0)
        {
            printf("T%d ", i);
        }
    }
    printf("\n");
    return false;
}

/**
 * Scan through finished array to find a 0
 *
 * @param finished the finished array
 *
 * @return true if finished array has all 1's, otherwise false
 */
bool isFinished(int *finished)
{
    for (int i = 0; i < NPROC; i++)
    {
        if (finished[i] == 0)
        {
            return false;
        }
    }
    return true;
}

/**
 * Return the int for the index of a 0
 *
 * @param finished the finished array
 * @param counter the counter to start the loop
 *
 * @return the int where you find a 0
 */
int indexUnfinished(int *finished, int counter)
{
    for (int i = counter; i < NPROC; i++)
    {
        if (finished[i] == 0)
        {
            return i;
        }
    }
    return 0;
}

/**
 * Return boolean for if the index at a specific spot is unfinished
 *
 * @param finished the finished array
 * @param counter the counter which specifies the index to be checked
 *
 * @return true if the given index is 0, otherwise false
 */
bool isidxUnfinished(int *finished, int counter)
{
    for (int i = 0; i < NPROC; i++)
    {
        if (finished[i] == 0 && i == counter)
        {
            return true;
        }
    }
    return false;
}
