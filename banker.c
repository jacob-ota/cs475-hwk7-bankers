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
 * @param resources the available array
 * @param alloc the allocation matrix
 * @param need the need matrix
 * 
 * @return true if the algorithm is safe, false otherwise
 */
bool safetyAlgo(int *resources, int **alloc, int **need)
{
    //clone the resource available array
    int *work = (int *)malloc(NRES * sizeof(int));
    work = cloneVector(resources, work);
    //initialize finished array to all 0's
    int *finished = (int *)malloc(NPROC * sizeof(int));
    for (int i = 0; i < NPROC; i++)
    {
        finished[i] = 0;
    }
    int *trackProcesses = (int *)malloc(NPROC * sizeof(int));
    //tracker: tracks order of processes when completed stores into trackprocesses
    int tracker = 0;
    int counter = indexUnfinished(finished, 0);
    //make a counter for if the process goes to long and is deemed unsafe
    int unsafe = 0;
    while (!isFinished(finished))
    {
        if (compareNeedWork(need[counter], work) && isidxUnfinished(finished, counter))
        {
            //work += alloc[i]
            work = createNewWork(work, alloc[counter]);
            //update counter
            finished[counter] = 1;
            //store thread in order to print out later
            trackProcesses[tracker] = counter;
            counter++;
            //update the counter so that it can get the next index unfinished
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
            //update counter so it can get the next index unfinished
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
            unsafe++;
        }
        if(unsafe == 100) {
            break;
        }
    }
    if (isFinished(finished))
    {
        //if all threads finish then print out the safe solution
        printf("SAFE: ");
        for (int i = 0; i < NPROC; i++)
        {
            printf("T%d ", trackProcesses[i]);
        }
        printf("\n");
        //free up work, finish and track processes
        free(work);
        free(finished);
        free(trackProcesses);
        return true;
    }
    //print out the unsafe and what did not finish
    printf("UNSAFE: ");
    for (int i = 0; i < NPROC; i++)
    {
        if (finished[i] == 0)
        {
            printf("T%d ", i);
        }
    }
    printf("\n");
    free(work);
    free(finished);
    free(trackProcesses);
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
    //check if any spots in finished are equal to 0
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
    //return the index of an unfinished spot
    for (int i = counter; i < NPROC; i++)
    {
        if (finished[i] == 0)
        {
            return i;
        }
    }
    return -1;
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
    //check if a certain spot in the finished array is unfinished
    for (int i = 0; i < NPROC; i++)
    {
        if (finished[i] == 0 && i == counter)
        {
            return true;
        }
    }
    return false;
}
