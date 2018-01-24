// Zadanie 17. Iloczyny cyfr.
// Microsoft Visual Studio 2010.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define SIZE 100

// _________________________________________________________________________________

int main( void )
{
// I. Declarations.
unsigned short int divisor;
unsigned short int modulo;
unsigned short int (*outcome) = (unsigned short int *)calloc(SIZE,SIZE*sizeof(unsigned short int));
unsigned short int limit;
unsigned long int cases;
unsigned long int number;

// II. Preparing for the first use.
divisor = 9;
modulo = 0;
limit = 0;
cases = 0;
number = 0;

// III. Reading the number of test cases to be processed.
fscanf(stdin,"%lu%[^\n]",&cases);

// IV. Entering the main processing cycle.
while ( cases )
    {
    // (1) Reading the next case number.
    fscanf(stdin,"%lu%[^\n]",&number);

    // (2) Checking if the number has one digit.
    if ( number < 10 )
        {
        if ( !number )
            {
            fprintf(stdout,"0\n");
            }
        else
            {
            fprintf(stdout,"%lu\n",number);
            };
        }
    else
    // (3) Searching for the minimal number.
        {
        while ( ( divisor > 1 ) && ( number > 1 ) )
            {
            while ( ( modulo = ( number % divisor ) ) == 0 )
                {
                outcome[limit] = divisor;
                limit = limit + 1;
                number = number / divisor;
                };

            divisor = divisor - 1;
            };

        // (4) Interpreting the counted data.
        if ( number > 1 )
            {
            fprintf(stdout,"NIE\n");
            }
        else
            {
            for ( number=limit; number>0; number=number-1 )
                {
                fprintf(stdout,"%hu",outcome[number-1]);
                outcome[number-1] = 0;
                };

            fputc('\n',stdout);
            };

        // (5) Cleaning the data for the next use.
        divisor = 9;
        modulo = 0;
        limit = 0;
        number = 0;
        };

    // (6) Changing the successor.
    cases = cases - 1;
    };

// V. Clearing the memory.
divisor = 0;
modulo = 0;
memset(outcome,0,SIZE*sizeof(unsigned short int));
limit = 0;
cases = 0;
number = 0;

// VI. Deallocating the memory.
free( outcome );

// VII. Resetting the pointer.
outcome = NULL;

// VIII. Exiting.
return ( 0 );
};

// _________________________________________________________________________________
