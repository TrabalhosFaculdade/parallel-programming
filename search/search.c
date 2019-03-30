#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <stdbool.h>

#define NUM_VALUES 32

void inituniquearray (int values[]) 
{
	int i;
	for (i = 0; i < NUM_VALUES; i++)
		values[i] = i;
}

bool findvalue (int values[], int wantedvalue)
{
	int numthreads = omp_get_max_threads();
	int valuesperthread = NUM_VALUES / numthreads;	

	bool found = false;
	
	#pragma omp parallel
	{
		int initialvalue = omp_get_thread_num() * valuesperthread;
		int lastvalue = initialvalue + valuesperthread;
			
		int i;
		for (i = initialvalue; i < lastvalue && !found; i++)
			if (values[i] == wantedvalue)
				found = true;
	}
	
	return found;
}

int main () {
	
	int i;
	int lastvalue;
	int values[NUM_VALUES];
	inituniquearray(values);

	//you wont find the last 10 values
	for (i = 0; i < NUM_VALUES + 10; i++)
	{
		printf("Value: %d, Found? %d\n", i, findvalue(values, i));
	}	

	return 0;
	
}