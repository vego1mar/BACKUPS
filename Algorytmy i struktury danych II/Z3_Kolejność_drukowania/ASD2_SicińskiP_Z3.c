// Zadanie 3. Kolejnoœæ drukowania.
// Microsoft Visual Studio 2010.

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// ______________________________________________________________________________

#define QUEUE_SIZE 100

// ______________________________________________________________________________

int main( void )
{
// Declarations.
unsigned short int N = 0;
unsigned short int n = 0;
unsigned short int m = 0;
short int i = 0;
short int (*Queue) = (short int (*))calloc(QUEUE_SIZE,QUEUE_SIZE*sizeof(short int));
unsigned short int t = 0;
short int j = 0;

// Reading the number of test cases.
fscanf( stdin, "%hu%[^\n]", &N );

// Entering the main processing cycle.
while ( N )
    {
    // Reading the number of tasks in the queue.
    fscanf( stdin, "%hu", &n );

    // Reading the position of the task to do analysis.
    fscanf( stdin, "%hu%*c", &m );

    // Grabbing the task's priorities in the queue.
    for ( i=0; i<n; i=i+1 )
        {
        fscanf( stdin, "%hd", &Queue[i] );
        };

    // Calculating the output data.
    for ( i=(n-1); i>=m; i=i-1 )
        {
        // Check if it should be concidered.
        if ( Queue[i] != (-1) )
            {
            // Searching for the higher priority in the queue.
            for ( j=i; j>=0; j=j-1 )
                {
                if ( Queue[j] > Queue[i] )
                    {
                    Queue[j] = -1;
                    break;
                    };
                };

            // Defining the next step.
            n = n - 1;
            t = t + 1;
            };
        };

    // Printing the output data.
    fprintf( stdout, "%hu\n", t );

    // The shadow read for the next test case.
    fscanf( stdin, "%[^\n]" );

    // Clearing before the next use.
    t = 0;

    // Changing the successor.
    N = N - 1;
    };

// Clearing the memory before exit.
N = 0;
n = 0;
m = 0;
i = 0;
memset( Queue, 0, QUEUE_SIZE*sizeof(unsigned short int) );
t = 0;
j = 0;

// Deallocating the memory.
free( Queue );

// Resetting the pointer.
Queue = NULL;

// Exiting.
return ( 0 );
};

// ______________________________________________________________________________
