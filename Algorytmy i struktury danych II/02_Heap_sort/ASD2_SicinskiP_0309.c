// A simple implementation of the heap sort algorithm.
// Using Visual C (2010).

// PRECAUTIONS:
// Numeration is defined as an ordinal starting from 1.
// Seed of the randomness is currently set to a fixed value.
// TreeView() function gives correct output only if the array size is lower or equal than 16.


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <stddef.h>

// __________________________________________________________________________________

#define N           0x0000000C
#define RAND_MAX_2  0x7FFFFFFF

// __________________________________________________________________________________

// Fullfil an array by the random real numbers.
void SetRandomValues(double *, const short int);

// Shows the actual status of a pointed array.
void ArrayView(const double *, const short int);

// Aggregate stages needed for sorting the heap tree.
void HeapSort(double *, const short int);

// Formes the heap tree.
void FormHeapTree(double *, const short int);

// Remove the last element from the heap tree.
void HeapTreeRemoval(double *, const short int);

// Shows the heap tree array as a quasi-graphic tree.
void TreeView(const double *, const short int);

// __________________________________________________________________________________
// __________________________________________________________________________________

int main(void)
{
double T [N] = {0};

SetRandomValues(T,N);
ArrayView(T,N);
putchar('\n');
//TreeView(T,N);
HeapSort(T,N);
//putchar('\n');
ArrayView(T,N);
//putchar('\n');
//TreeView(T,N);

getchar();
return (0);
};

// __________________________________________________________________________________
// __________________________________________________________________________________

void SetRandomValues(double * _T, const short int _N)
{
short int i;
time_t t = 23;

srand((unsigned int)time(&t));

for (i=1; i<_N; i=i+1)
    {
    _T[i] = ((double)(0x5477ACFF) * rand()) / (RAND_MAX_2);
    };
};

// __________________________________________________________________________________

void ArrayView(const double * _T, const short int _N)
{
short int i;

printf(
      "-----------------------------------------------------\n"
      "|       index    |              value               |\n"
      "-----------------------------------------------------\n"
      );

for (i=1; i<_N; i=i+1)
    {
    printf("|   %8hd     |%30.17lf    |\n",i,_T[i]);
    };

printf("-----------------------------------------------------\n");
};

// __________________________________________________________________________________

void HeapSort(double * _T, const short int _N)
{
FormHeapTree(_T,_N);
HeapTreeRemoval(_T,_N);
};

// __________________________________________________________________________________

void FormHeapTree(double * _T, const short int _N)
{
// Declarations.
short int i;
unsigned short int x;

for (i=1; i<_N; i=i+1)
    {
    // Pointing at the left descendant.
    x = 2*i;

    // Checking the heap tree condition and watching of the array bounds.
    if (x < _N)
        {
        if (_T[x] < _T[i])
            {
            _T[0] = _T[x];
            _T[x] = _T[i];
            _T[i] = _T[0];
            i = 0;
            continue;
            };
        };

    // Pointing at the right descendant.
    x = x + 1;

    // Checking the heap tree condition and watching of the array bounds.
    if (x < _N)
        {
        if (_T[x] < _T[i])
            {
            _T[0] = _T[x];
            _T[x] = _T[i];
            _T[i] = _T[0];
            i = 0;
            continue;
            };
        };
    };
};

// __________________________________________________________________________________

void HeapTreeRemoval(double * _T, const short int _N)
{
// Declarations.
short int i;
short int ig = _N-1;

for (i=1; i<ig; i=i+1)
    {
    // Removal of the last element from the heap tree.
    _T[0] = _T[1];
    _T[1] = _T[ig];
    _T[ig] = _T[0];

    // Reformating the heap tree.
    FormHeapTree(_T,ig);

    // Ignoring of removed elements.
    ig = ig - 1;
    i = 0;
    };
};

// __________________________________________________________________________________

void TreeView(const double * _T, const short int _N)
{
// Declarations.
unsigned short int p = 1;
unsigned short int s = 0;
short int n = 10;
unsigned long int l;
unsigned long int f;
unsigned short int q = 1;
short int idx = 1;
short int i;
short int j;
unsigned long int k;

// Counting the number of elements in the last and the most widen row.
for ( ; ; )
    {
    if (p >= _N) break;
    p = p*2;
    s = s + 1;
    };

p = p/2;

// Counting the number of characters per line needed.
// Counting the first offset.
l = (p*n)+(3*p);
f = (l/2)-6;

// Building the quasi-graphic tree.
for (i=0; i<s; i=i+1)
    {
    // Giving the trailing spaces.
    if (f > 0)
        {
        for (k=0; k<f; k=k+1)
            {
            putchar(' ');
            };
        };

    // Counting the next offset.
    f = f - (6*(i+2)) + 5;
    if (i == (s-2)) f = 0;

    // Printing the numbers of the tree.
    if (q < _N)
        {
        for (j=0; j<q; j=j+1)
            {
            if (idx < _N) 
                {
                // 10 characters, but ending zeros is not considered.
                printf("%.9g   ",_T[idx]);
                idx = idx + 1;
                };
            };
        };

    // Ending the row.
    putchar('\n');
    putchar('\n');
    q = q*2;
    };
};

// __________________________________________________________________________________
