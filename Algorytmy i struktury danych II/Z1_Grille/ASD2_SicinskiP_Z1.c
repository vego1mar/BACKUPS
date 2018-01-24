// Zadanie 1. Grille.
// Using Visual C (2010).

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// __________________________________________________________________________________

#define T 1000

// __________________________________________________________________________________

int main(void)
{
// Declarations.
short int N;
short int i;
short int j;

// Declarations of VLAs (variable length arrays).
size_t SIZE = sizeof(char[T][T]);
char (*M)[T] = (char (*)[T])malloc(SIZE);
char (*A)[T] = (char (*)[T])malloc(SIZE);
char (*B)[T] = (char (*)[T])malloc(SIZE);

// :: Processing loop.
while (1)
    {
    // Reading for the first value.
    fscanf(stdin,"%hd",&N);

    // Checking for exit.
    if (!N) break;

    // Cleaning for the next step.
    fscanf(stdin,"%*c");

    // Absorbing the matrix.
    for (i=0; i<N; i=i+1)
        {
        for (j=0; j<N; j=j+1)
            {
            fscanf(stdin,"%c",&A[i][j]);
            };

        fscanf(stdin,"%*c");
        };
    
    // Absorbing the message.
    for (i=0; i<N; i=i+1)
        {
        for (j=0; j<N; j=j+1)
            {
            fscanf(stdin,"%c",&M[i][j]);
            };

        fscanf(stdin,"%*c");
        };

    // The first reading for encoding.
    for (i=0; i<N; i=i+1)
        {
        for (j=0; j<N; j=j+1)
            {
            if (A[i][j] == '0')
                {
                fprintf(stdout,"%c",M[i][j]);
                };
            };
        };

    // The first rotation of the matrix.
    for (i=(N-1); i>=0; i=i-1)
        {
        for (j=0; j<N; j=j+1)
            {
            B[j][i] = A[(N-1)-i][j];
            };
        };

    // The second reading for encoding.
    for (i=0; i<N; i=i+1)
        {
        for (j=0; j<N; j=j+1)
            {
            if (B[i][j] == '0')
                {
                fprintf(stdout,"%c",M[i][j]);
                };
            };
        };

    // The second rotation of the matrix.
    for (i=(N-1); i>=0; i=i-1)
        {
        for (j=0; j<N; j=j+1)
            {
            A[j][i] = B[(N-1)-i][j];
            };
        };

    // The third reading for encoding.
    for (i=0; i<N; i=i+1)
        {
        for (j=0; j<N; j=j+1)
            {
            if (A[i][j] == '0')
                {
                fprintf(stdout,"%c",M[i][j]);
                };
            };
        };

    // The third rotation of the matrix.
    for (i=(N-1); i>=0; i=i-1)
        {
        for (j=0; j<N; j=j+1)
            {
            B[j][i] = A[(N-1)-i][j];
            };
        };

    // The fourth reading for encoding.
    for (i=0; i<N; i=i+1)
        {
        for (j=0; j<N; j=j+1)
            {
            if (B[i][j] == '0')
                {
                fprintf(stdout,"%c",M[i][j]);
                };
            };
        };

    // Giving a newline character at end of the encrypted message.
    fputc('\n',stdout);

    // Changing the successor.
    N = N - 1;
    };

// Deallocating.
free(M);
free(A);
free(B);
M = NULL;
A = NULL;
B = NULL;

// Exiting.
return (0);
};

// __________________________________________________________________________________
