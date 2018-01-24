// An implementation of the Prim's MST searching algorithm.
// Using Visual C (2010).

#include <stdio.h>
//#include <Windows.h>
//#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

// __________________________________________________________________________________________________

#define SIZE 16
#define MST_SIZE (SIZE - 1)

//#define ESC \
//		for ( ; ; ) if (GetAsyncKeyState(VK_ESCAPE)) break;

// __________________________________________________________________________________________________

typedef enum { false, true } bool;

// __________________________________________________________________________________________________

struct AuxiliaryEdge
    {
    unsigned short int vertex1;
    unsigned short int vertex2;
    short int value;
    };

struct Edge
    {
    char vertex1;
    char vertex2;
    short int value;
    };

// __________________________________________________________________________________________________

// Read the adjacency (neighborhoods) matrix from the standard input.
bool ReadAdjacencyMatrix(char *, short int (*)[SIZE]);

// Print the content of the markers array to the standard output.
void MarkersView(const char * const);

// Print the content of the adjacency matrix to the standard output.
void AdjacencyMatrixView(const short int (*)[SIZE], const char * const);

// The Prim algorithm of searching for the Minimal Spanning Tree.
void SearchForThePrimMST(const short int (*)[SIZE], struct Edge *, const char * const, short int, 
                         void (*)(struct AuxiliaryEdge *, const unsigned short int, const unsigned short int));

// The bubble sort algorithm working on an array of structures using starting and ending point.
void BubbleSort(struct AuxiliaryEdge *, const unsigned short int, const unsigned short int);

// Print the content of the struct Edge array to the standard output.
void MinimalSpanningTreeView(const struct Edge * const, const unsigned short int);

// **************************************************************************************************

int main(void)
{
// Declarations.
char (*Markers) = (char (*))calloc(SIZE,sizeof(char[SIZE]));
short int (*Matrix)[SIZE] = (short int (*)[SIZE])calloc(SIZE*SIZE,sizeof(short int[SIZE][SIZE]));
struct Edge (*MST) = (struct Edge (*))calloc(MST_SIZE,sizeof(struct Edge[MST_SIZE]));

// In order function calls.
ReadAdjacencyMatrix(Markers,Matrix);
MarkersView(Markers);
AdjacencyMatrixView(Matrix,Markers);
SearchForThePrimMST(Matrix,MST,Markers,13,BubbleSort);
MinimalSpanningTreeView(MST,MST_SIZE);

// Deallocating the data structures.
free(Markers);
free(Matrix);
free(MST);

// Resetting the pointers.
Markers = NULL;
Matrix = NULL;
MST = NULL;

//// Using a waiting macro.
//ESC;

// Exiting.
return (0);
};

// **************************************************************************************************

bool ReadAdjacencyMatrix(char * _markers, short int (*_Matrix)[SIZE])
// false   The read matrix size is non-positive or larger than SIZE.
// true    The matrix size was accepted and the data was adopted to the data structures.

{
// Declarations.
short int N;
short int * i = (short int *)malloc(sizeof(short int));
short int * j = (short int *)malloc(sizeof(short int));
bool op = true;
char ch;
short int sh;

// Reading the description number.
fscanf(stdin,"%hd",&N);

// The shadow read.
fscanf(stdin,"%*c");

// Checking for absorption.
if ((N > SIZE) || (N <= 0))
    {
    // Changing the returning value.
    op = false;
    }
else
    {
    // Absorbing the markers.
    for ((*i)=0; (*i)<N; (*i)=(*i)+1)
        {
        // Reading the marker.
        fscanf(stdin,"%c",&ch);

        // Absorbing the marker.
        _markers[(*i)] = ch;

        // The shadow read.
        fscanf(stdin,"%*c");
        };
    };

// Absorbing the adjacency matrix.
for ((*i)=0; (*i)<N; (*i)=(*i)+1)
    {
    // Handling with lines.
    for ((*j)=0; (*j)<N; (*j)=(*j)+1)
        {
        // Reading the value.
        fscanf(stdin,"%hd",&sh);

        // Absorbing the value.
        _Matrix[(*i)][(*j)] = sh;
        };

    // The shadow read.
    fscanf(stdin,"%*c");
    };

// Deallocating.
free(i);
free(j);

// Resetting the pointers.
i = NULL;
j = NULL;

// Exiting.
return (op);
};

// __________________________________________________________________________________________________

void MarkersView(const char * const _markers)
{
// Declarations.
short int i;

// Printing the starting lines.
for (i=0; i<(SIZE+2); i=i+1)
    {
    fprintf(stdout,"++++++");
    };

// Giving a newline character after the first starting line.
fputc('\n',stdout);

// Printing the trailing spaces.
for (i=0; i<((SIZE-1)/2); i=i+1)
    {
    fprintf(stdout,"      ");
    };

// Printing the description.
fprintf(stdout,"THE MARKERS ARRAY\n");

// Printing the second starting line.
for (i=0; i<(SIZE+2); i=i+1)
    {
    fprintf(stdout,"++++++");
    };

// Giving the newline characters after the third starting line.
fputc('\n',stdout);
fputc('\n',stdout);

// Printing the indexes.
for (i=0; i<SIZE; i=i+1)
    {
    // Dealing with the right spaces.
    fprintf(stdout,"%*.1hd",6,i);
    };

// Giving a newline character after the indexing line.
fputc('\n',stdout);
fputc('\n',stdout);

// Printing the markers.
for (i=0; i<SIZE; i=i+1)
    {
    // Dealing with the right spaces.
    fprintf(stdout,"%*.c",6,_markers[i]);
    };

// Giving the newline characters after the markers line.
fputc('\n',stdout);
fputc('\n',stdout);

// Printing the ending line.
for (i=0; i<(SIZE+2); i=i+1)
    {
    fprintf(stdout,"++++++");
    };

// Giving the newline characters after the ending line.
fputc('\n',stdout);
fputc('\n',stdout);
};

// __________________________________________________________________________________________________

void AdjacencyMatrixView(const short int (*_Matrix)[SIZE], const char * const _Markers)
{
// Declarations.
short int i;
short int j;

// Printing the first starting line.
for (i=0; i<(SIZE+2); i=i+1)
    {
    fprintf(stdout,"++++++");
    };

// Giving a newline character after the first line.
fputc('\n',stdout);

// Printing some spaces before putting a name.
for (i=0; i<((SIZE-1)/2); i=i+1)
    {
    fprintf(stdout,"      ");
    };

// Putting the name.
fprintf(stdout,"THE ADJACENCY MATRIX\n");

// Printing the third starting line.
for (i=0; i<(SIZE+2); i=i+1)
    {
    fprintf(stdout,"++++++");
    };

// Giving a newline character after the third line.
fputc('\n',stdout);
fputc('\n',stdout);

// Printing the trailing spaces.
fprintf(stdout,"         ");

// Printing the columns description.
for (i=0; i<SIZE; i=i+1)
    {
    fprintf(stdout,"%*.c",6,_Markers[i]);
    };

// Giving the trailing spaces.
fprintf(stdout,"\n         ");

// Printing the separator.
for (i=0; i<SIZE; i=i+1)
    {
    fprintf(stdout,"------");
    };

// Giving a newline character at the end of the separator line.
fputc('\n',stdout);

// Printing the values.
for (i=0; i<SIZE; i=i+1)
    {
    // Handling with a line.
    fprintf(stdout," %*.c | ",5,_Markers[i]);

    // Printing the values in the line.
    for (j=0; j<SIZE; j=j+1)
        {
        // Handling with the right spaces.
        fprintf(stdout,"%*.1hd",6,_Matrix[i][j]);
        };

    // Giving a newline character.
    fputc('\n',stdout);
    };

// Giving a newline character before the ending line.
fputc('\n',stdout);

// Printing the ending line.
for (i=0; i<(SIZE+2); i=i+1)
    {
    fprintf(stdout,"++++++");
    };

// Giving the newline characters after the ending line.
fputc('\n',stdout);
fputc('\n',stdout);
};

// __________________________________________________________________________________________________

void BubbleSort(struct AuxiliaryEdge * _aux, const unsigned short int _begin, const unsigned short int _end)
{
// Declarations.
unsigned short int * i = (unsigned short int *)malloc(sizeof(unsigned short int));
unsigned short int * j = (unsigned short int *)malloc(sizeof(unsigned short int));
short int * tmp = (short int *)malloc(sizeof(short int));
unsigned short int * tmp2 = (unsigned short int *)malloc(sizeof(unsigned short int));

// Sorting out the array of structures.
for ((*i)=_begin; (*i)<_end; (*i)=(*i)+1)
    {
    for ((*j)=_begin; (*j)<(_end-1); (*j)=(*j)+1)
        {
        if ((_aux[(*j)].value) > (_aux[(*j)+1].value))
            {
            // Swapping the 'value' pole.
            (*tmp) = _aux[(*j)+1].value;
            _aux[(*j)+1].value = _aux[(*j)].value;
            _aux[(*j)].value = (*tmp);
            
            // Swapping the 'vertex1' pole.
            (*tmp2) = _aux[(*j)+1].vertex1;
            _aux[(*j)+1].vertex1 = _aux[(*j)].vertex1;
            _aux[(*j)].vertex1 = (*tmp2);

            // Swapping the 'vertex2' pole.
            (*tmp2) = _aux[(*j)+1].vertex2;
            _aux[(*j)+1].vertex2 = _aux[(*j)].vertex2;
            _aux[(*j)].vertex2 = (*tmp2);
            };
        };
    };

// Deallocating the memory.
free(i);
free(j);
free(tmp);
free(tmp2);

// Resetting the pointers.
i = NULL;
j = NULL;
tmp = NULL;
tmp2 = NULL;
};

// __________________________________________________________________________________________________

void SearchForThePrimMST(const short int (*_Matrix)[SIZE], struct Edge * _MSTArray, const char * const _Markers, short int _edge,
                         void (*SortingProcedure)(struct AuxiliaryEdge *, const unsigned short int, const unsigned short int))
{
// Declarations.
const unsigned short int V_SIZE = 2*SIZE;
struct AuxiliaryEdge (*Vertices) = (struct AuxiliaryEdge (*))calloc(V_SIZE,V_SIZE*sizeof(struct AuxiliaryEdge));
unsigned short int i;
unsigned short int j = 0;
unsigned short int k;
unsigned short int l;
unsigned short int N_end;
unsigned short int N_begin;
unsigned short int counter;
unsigned short int v1;
unsigned short int v2;
bool flag;
bool occ [SIZE];

// I. Starting.
// Checking the starting edge bounds.
if ((_edge < 0) || (_edge >= SIZE))
    {
    // Redefining the parameter to the default behaviour.
    _edge = 0;
    };

// Absorbing the starting data to the auxiliary structure.
for (i=0; i<SIZE; i=i+1)
    {
    // Searching for the non-zero values.
    if (_Matrix[_edge][i])
        {
        // Filling the structure.
        Vertices[j].vertex1 = _edge;
        Vertices[j].vertex2 = i;
        Vertices[j].value = _Matrix[_edge][i];

        // Altering the array successor.
        j = j + 1;
        };
    };

// Sorting the auxiliary structure data.
N_end = j;
(*SortingProcedure)(Vertices,0,N_end);
N_begin = 1;

// Integrity check.
if (Vertices[0].value == 0)
    {
    fputs("There is no valid data or an internal failure occur.\n",stderr);
    abort();
    };

// Saving the first edge of the MST.
_MSTArray[0].value = Vertices[0].value;
_MSTArray[0].vertex1 = _Markers[Vertices[0].vertex1];
_MSTArray[0].vertex2 = _Markers[Vertices[0].vertex2];

// Changing the analyzed edge.
_edge = Vertices[0].vertex2;

// II. Starting the main processing loop.
for (counter=2; counter<MST_SIZE; counter=counter+1)
    {
    // Vertices[V_SIZE] = <MST> + <Aux>.
    // (1) Adding the next incidental vertices to the <Aux>.
    j = N_end;
    flag = false;

    for (i=0; i<SIZE; i=i+1)
        {
        // Checking for the data absorption to the Vertices[V_SIZE].
        if (_Matrix[_edge][i])
            {
            // Rejecting the vertices already being in the <MST> or <Aux>.
            for (k=0; k<N_end; k=k+1)
                {
                if (((_edge == Vertices[k].vertex1) && (i == Vertices[k].vertex2)) || 
                    ((_edge == Vertices[k].vertex2) && (i == Vertices[k].vertex1)))
                    {
                    flag = true;
                    break;
                    };
                };

            // Grabbing the rejection state from the previous instruction block.
            if (flag == true)
                {
                flag = false;
                continue;
                };

            // No rejection was recorded here, so fill in the structure.
            Vertices[j].vertex1 = _edge;
            Vertices[j].vertex2 = i;
            Vertices[j].value = _Matrix[_edge][i];

            // Altering the vertices successor.
            j = j + 1;
            };
        };

    // Changing the logic distribution of <Aux>.
    // <MST> bounds: from (0) to (N_begin).
    // <Aux> bounds: from (N_begin) to (N_end).
    N_end = j;

    // (2) Sorting out the <Aux> part.
    (*SortingProcedure)(Vertices,N_begin,N_end);

    // (3) Checking for vertices in the <Aux> that forming a cycle terms of the <MST>.
    // (a) The left-side transitivity check.
    for (i=N_begin; i<N_end; i=i+1)
        {
        v1 = Vertices[i].vertex1;
        v2 = Vertices[i].vertex2;

        for (j=0; j<N_begin; j=j+1)
            {
            if (Vertices[j].vertex2 == v1)
                {
                v1 = Vertices[j].vertex1;

                for (k=0; k<N_begin; k=k+1)
                    {
                    if (Vertices[k].vertex2 == v2)
                        {
                        v2 = Vertices[k].vertex1;

                        if (v1 == v2)
                            {
                            // Removing the cycle by shifting the vertices to save the continuity of the array.
                            for (l=i; l<(N_end-1); l=l+1)
                                {
                                Vertices[l].vertex1 = Vertices[l+1].vertex1;
                                Vertices[l].vertex2 = Vertices[l+1].vertex2;
                                Vertices[l].value = Vertices[l+1].value;
                                };

                            N_end = N_end - 1;
                            i = i - 1;
                            };
                        };
                    };
                };
            };
        };

    // (b) The right-side transitivity check.
    for (i=N_begin; i<N_end; i=i+1)
        {
        v1 = Vertices[i].vertex1;
        v2 = Vertices[i].vertex2;

        for (j=0; j<N_begin; j=j+1)
            {
            if (Vertices[j].vertex1 == v1)
                {
                v1 = Vertices[j].vertex2;

                for (k=0; k<N_begin; k=k+1)
                    {
                    if (Vertices[k].vertex1 == v2)
                        {
                        v2 = Vertices[k].vertex2;

                        if (v1 == v2)
                            {
                            // Removing the cycle by shifting the vertices to save the continuity of the array.
                            for (l=i; l<(N_end-1); l=l+1)
                                {
                                Vertices[l].vertex1 = Vertices[l+1].vertex1;
                                Vertices[l].vertex2 = Vertices[l+1].vertex2;
                                Vertices[l].value = Vertices[l+1].value;
                                };

                            N_end = N_end - 1;
                            i = i - 1;
                            };
                        };
                    };
                };
            };
        };

    // (c) The left-to-right crossed transitivity check.
    for (i=N_begin; i<N_end; i=i+1)
        {
        v1 = Vertices[i].vertex1;
        v2 = Vertices[i].vertex2;

        for (j=0; j<N_begin; j=j+1)
            {
            if (Vertices[j].vertex1 == v1)
                {
                v1 = Vertices[j].vertex2;

                for (k=0; k<N_begin; k=k+1)
                    {
                    if (Vertices[k].vertex2 == v2)
                        {
                        v2 = Vertices[k].vertex1;

                        if (v1 == v2)
                            {
                            // Removing the cycle by shifting the vertices to save the continuity of the array.
                            for (l=i; l<(N_end-1); l=l+1)
                                {
                                Vertices[l].vertex1 = Vertices[l+1].vertex1;
                                Vertices[l].vertex2 = Vertices[l+1].vertex2;
                                Vertices[l].value = Vertices[l+1].value;
                                };

                            N_end = N_end - 1;
                            i = i - 1;
                            };
                        };
                    };
                };
            };
        };

    // (d) The right-to-left crossed transitivity check.
    for (i=N_begin; i<N_end; i=i+1)
        {
        v1 = Vertices[i].vertex1;
        v2 = Vertices[i].vertex2;

        for (j=0; j<N_begin; j=j+1)
            {
            if (Vertices[j].vertex2 == v1)
                {
                v1 = Vertices[j].vertex1;

                for (k=0; k<N_begin; k=k+1)
                    {
                    if (Vertices[k].vertex1 == v2)
                        {
                        v2 = Vertices[k].vertex2;

                        if (v1 == v2)
                            {
                            // Removing the cycle by shifting the vertices to save the continuity of the array.
                            for (l=i; l<(N_end-1); l=l+1)
                                {
                                Vertices[l].vertex1 = Vertices[l+1].vertex1;
                                Vertices[l].vertex2 = Vertices[l+1].vertex2;
                                Vertices[l].value = Vertices[l+1].value;
                                };

                            N_end = N_end - 1;
                            i = i - 1;
                            };
                        };
                    };
                };
            };
        };

    // (e) The left-or-right occurrence check.
    for (i=N_begin; i<N_end; i=i+1)
        {
        v1 = Vertices[i].vertex1;
        v2 = Vertices[i].vertex2;
        occ[1] = false;
        occ[2] = false;
        flag = false;

        for (j=0; j<N_begin; j=j+1)
            {
            if ((Vertices[j].vertex1 == v1) || (Vertices[j].vertex2 == v1))
                {
                occ[1] = true;
                };

            if ((Vertices[j].vertex2 == v2) || (Vertices[j].vertex1 == v2))
                {
                occ[2] = true;
                };

            if ((occ[1] == true) && (occ[2] == true))
                {
                flag = true;
                break;
                };
            };

        if (flag == true)
            {
            // Removing the cycle by shifting the vertices to save the continuity of the array.
            for (l=i; l<(N_end-1); l=l+1)
                {
                Vertices[l].vertex1 = Vertices[l+1].vertex1;
                Vertices[l].vertex2 = Vertices[l+1].vertex2;
                Vertices[l].value = Vertices[l+1].value;
                };

            N_end = N_end - 1;
            i = i - 1;            
            };
        };

    // (4) Specifying the next vertex to be analyzed.
    _edge = Vertices[N_begin].vertex2;

    // (5) Redefining the logic of the <Aux> and <MST> partition.
    N_begin = N_begin + 1;
    };

// III. Updating the outside data structure with a reached result.
for (i=1; i<N_begin; i=i+1)
    {
    _MSTArray[i].vertex1 = _Markers[Vertices[i].vertex1];
    _MSTArray[i].vertex2 = _Markers[Vertices[i].vertex2];
    _MSTArray[i].value = Vertices[i].value;
    };

// IV. Defining the last edge of the MST.
memset(occ,false,SIZE*sizeof(bool));

// Searching for the marker number that has no occurrence until now.
for (i=0; i<N_begin; i=i+1)
    {
    for (j=0; j<SIZE; j=j+1)
        {
        if (Vertices[i].vertex1 == j)
            {
            occ[j] = true;
            break;
            };
        };

    for (j=0; j<SIZE; j=j+1)
        {
        if (Vertices[i].vertex2 == j)
            {
            occ[j] = true;
            break;
            };
        };
    };

// Saving the marker number.
for (i=0; i<SIZE; i=i+1)
    {
    if (occ[i] == false)
        {
        k = i;
        break;
        };
    };

// Searching for the first marker number occurrence in the <Aux>.
for (i=N_begin; i<N_end; i=i+1)
    {
    if ((Vertices[i].vertex1 == k) || (Vertices[i].vertex2 == k))
        {
        // Updating the MST array by the last edge.
        _MSTArray[MST_SIZE-1].vertex1 = _Markers[Vertices[i].vertex1];
        _MSTArray[MST_SIZE-1].vertex2 = _Markers[Vertices[i].vertex2];
        _MSTArray[MST_SIZE-1].value = Vertices[i].value;
        break;
        };
    };

// V. Deallocating.
free(Vertices);
Vertices = NULL;
};

// __________________________________________________________________________________________________

void MinimalSpanningTreeView(const struct Edge * const _Array, const unsigned short int _SIZE)
{
// Declarations.
unsigned short int i;

// Printing the starting lines.
fprintf(stdout,"++++++++++++++++++++++\n"
               "        MST\n"
               "++++++++++++++++++++++\n\n"
      );

// Printing the Minimal Spanning Tree data.
for (i=0; i<_SIZE; i=i+1)
    {
    // Giving the right separation.
    fprintf(stdout,"%*.c %*.c %*.1hd\n",4,_Array[i].vertex1,4,_Array[i].vertex2,10,_Array[i].value);
    };

// Printing the ending lines.
fprintf(stdout,"\n++++++++++++++++++++++\n\n");
};

// __________________________________________________________________________________________________
