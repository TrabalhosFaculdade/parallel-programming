
/**
 * Daniel Dias de Lima
 * 31687679
 * 
 * Average time execution:
 * 
 * When multithreading: 1200~
 * Not multithreading : 2400~
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>

#define NUM_VALUES 20000
#define UNDEFINED_VALUE 0
#define MULTITHREADING

unsigned long long fibValues[NUM_VALUES] = {UNDEFINED_VALUE};

void *runFromTheBottomUp(void *nothing)
{
    printf("Started bottom up search\n");

    bool finished = false;

    //defining the initial values, just for the sake of the algorithm
    fibValues[0] = fibValues[1] = 1;
    for (long i = 2; i < NUM_VALUES && !finished; i++)
    {
        if (fibValues[i] == UNDEFINED_VALUE)
            fibValues[i] = fibValues[i - 1] + fibValues[i - 2];
        else
            ///found where both ends met
            finished = true;
    }

    pthread_exit(NULL);
}

unsigned long long fibonacci(long n)
{
    if (n == 0 || n == 1)
        return 1;

    if (fibValues[n] != UNDEFINED_VALUE)
    {
        int resultFound = fibValues[n];
        return fibValues[n];
    }

    int partialResult = fibonacci(n - 1) + fibonacci(n - 2);
    fibValues[n] = partialResult;

    return partialResult;
}

int main()
{
    long start = clock();

#ifdef MULTITHREADING 
    pthread_t bottomUpThread;
    if (pthread_create(&bottomUpThread, NULL, runFromTheBottomUp, (void *)NULL))
    {
        printf("Error while creating new thread");
        return 2;
    }
#endif
    unsigned long long result = fibonacci(NUM_VALUES);

    long finish = clock();
    long totalTime = (finish - start);

    printf("Total time: %ld\n", totalTime);
    pthread_exit(NULL);
}