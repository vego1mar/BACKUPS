// Saint John Festival
// Using Graham algorithm of searching for convex hull
// MSVC 2010

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// ____________________________________________________________________________________________________________

#define LARGE_LANTERNS 10000
#define SMALL_LANTERNS 50000
#define CONVEX_HULL (LARGE_LANTERNS)
#define OFFSET 1073741826

// ____________________________________________________________________________________________________________

typedef enum _TBool_ { NONE = -1, FALSE = 0, TRUE = 1 } bool_tri;

// ____________________________________________________________________________________________________________

struct LargePoint
    {
    long int x;
    long int y;
    double angle;
    };

struct SmallPoint
    {
    long int x;
    long int y;
    };

// ____________________________________________________________________________________________________________

// A procedure for clearing the memory occupied by the data allocated on the heap.
void AllocationClear( struct LargePoint (* const), struct SmallPoint (* const),
                      unsigned short int * const, unsigned short int * const,
                      struct SmallPoint (* const), unsigned short int * const,
                      unsigned short int * const, unsigned short int * const );

// A procedure for the proper allocation check of the most used data structures.
void AllocationCheck( const struct LargePoint (* const), const struct SmallPoint (* const), 
                      const unsigned short int * const, const unsigned short int * const,
                      const struct SmallPoint (* const), unsigned short int * const,
                      unsigned short int * const, unsigned short int * const );

// A procedure for dealing with deallocation of the data.
void Deallocation( struct LargePoint (*), struct SmallPoint (*),
                   unsigned short int *, unsigned short int *,
                   struct SmallPoint (*),
                   unsigned short int *, unsigned short int *, unsigned short int * );

// Read the input data from the standard input.
void DataRead( struct LargePoint (* const), struct SmallPoint (* const), 
               unsigned short int * const, unsigned short int * const );

// Preprocessing procedure that finds the starting point for building the convex hull.
void FirstPointSearch( const struct LargePoint (* const), const unsigned short int * const,
                       unsigned short int * const );

// Procedure of defining the angles based on the radius vector.
void DispatchRadiusVectorAngle( struct LargePoint (* const), const unsigned short int * const );

// The sorting (by angle) procedure for large lanterns data structure.
void Sorter( struct LargePoint (* const), const unsigned short int * const );

// Preprocessing procedure that evaluates the convex hull data structure by the first three proper points.
void FirstDataAbsorption( struct SmallPoint (* const), struct LargePoint (* const),
                          unsigned short int * const, const unsigned short int * const );

// The Graham algorithm of convex hull defining.
void ConvexHullBuilder( struct SmallPoint (* const),
                        const struct LargePoint (* const), const unsigned short int * const,
                        unsigned short int * const );

// Function of three-level matrix determinant counting.
long long int Determinant( const struct SmallPoint (* const),
                           const struct SmallPoint (* const),
                           const struct LargePoint (* const) );

// Altering the original coordinates by translating them as precedings of StartPoint to begin.
void CoordinatesTranslation( struct LargePoint (* const), struct SmallPoint (* const),
                             const unsigned short int * const, const unsigned short int * const,
                             const unsigned short int * const );

// Counts the number of intersections of the sections given by the convex hull with the small lanterns.
void IntersectionsCounter( const struct SmallPoint (* const), const unsigned short int * const,
                           const struct SmallPoint (* const), const unsigned short int * const,
                           unsigned short int * const );

// Function determining if given last point are on the section defining by the first two points.
bool_tri IsOnSection( const struct SmallPoint (* const), const struct SmallPoint (* const),
                      const struct LargePoint (* const) );

// Function determining which argument has the lowest value.
long int Minimum( const long int * const, const long int * const );

// Function determining which argument has the highest value.
long int Maximum( const long int * const, const long int * const );

// Print the solution of the case read from the input data to the standard output.
void PrintOutput( const unsigned short int * const );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
// Declarations.
struct LargePoint (*Large) = (struct LargePoint (*))malloc(LARGE_LANTERNS*sizeof(struct LargePoint));
struct SmallPoint (*Small) = (struct SmallPoint (*))malloc(SMALL_LANTERNS*sizeof(struct SmallPoint));
unsigned short int (*L) = (unsigned short int (*))malloc(sizeof(unsigned short int));
unsigned short int (*S) = (unsigned short int (*))malloc(sizeof(unsigned short int));
struct SmallPoint (*ConvexHull) = (struct SmallPoint (*))malloc(CONVEX_HULL*sizeof(struct SmallPoint));
unsigned short int (*StartPoint) = (unsigned short int (*))malloc(sizeof(unsigned short int));
unsigned short int (*CH) = (unsigned short int (*))malloc(sizeof(unsigned short int));
unsigned short int (*I) = (unsigned short int (*))malloc(sizeof(unsigned short int));

// Executing the Graham algorithm procedure.
AllocationCheck(Large,Small,L,S,ConvexHull,StartPoint,CH,I);
AllocationClear(Large,Small,L,S,ConvexHull,StartPoint,CH,I);

DataRead(Large,Small,L,S);
FirstPointSearch(Large,L,StartPoint);
CoordinatesTranslation(Large,Small,L,S,StartPoint);
DispatchRadiusVectorAngle(Large,L);
FirstDataAbsorption(ConvexHull,Large,L,StartPoint);
ConvexHullBuilder(ConvexHull,Large,L,CH);
IntersectionsCounter(ConvexHull,CH,Small,S,I);
PrintOutput(I);

Deallocation(Large,Small,L,S,ConvexHull,StartPoint,CH,I);

// Exiting.
return (0);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ____________________________________________________________________________________________________________

void AllocationClear( struct LargePoint ( * const _Large ), struct SmallPoint ( * const _Small ),
                      unsigned short int * const _L, unsigned short int * const _S,
                      struct SmallPoint ( * const _ConvexHull ),
                      unsigned short int * const _StartPoint,
                      unsigned short int * const _CH, unsigned short int * const _I )
{
memset(_Large,0,LARGE_LANTERNS*sizeof(struct LargePoint));
memset(_Small,0,SMALL_LANTERNS*sizeof(struct SmallPoint));
memset(_L,0,sizeof(unsigned short int));
memset(_S,0,sizeof(unsigned short int));
memset(_ConvexHull,0,CONVEX_HULL*sizeof(struct SmallPoint));
memset(_StartPoint,0,sizeof(unsigned short int));
memset(_CH,0,sizeof(unsigned short int));
memset(_I,0,sizeof(unsigned short int));
};

// ____________________________________________________________________________________________________________

void AllocationCheck( const struct LargePoint ( * const _Large ), const struct SmallPoint ( * const _Small ),
                      const unsigned short int * const _L, const unsigned short int * const _S,
                      const struct SmallPoint ( * const _ConvexHull ),
                      unsigned short int * const _StartPoint, unsigned short int * const _CH,
                      unsigned short int * const _I )
{
if ( _Large == NULL )
    {
    fputs("AllocationCheck(): '_Large' argument is an invalid pointer.",stderr);
    abort();
    };

if ( _Small == NULL )
    {
    fputs("AllocationCheck(): '_Small' argument is an invalid pointer.",stderr);
    abort();
    };

if ( _L == NULL )
    {
    fputs("AllocationCheck(): '_L' argument is an invalid pointer.",stderr);
    abort();
    };

if ( _S == NULL )
    {
    fputs("AllocationCheck(): '_S' argument is an invalid pointer.",stderr);
    abort();
    };

if ( _ConvexHull == NULL )
    {
    fputs("AllocationCheck(): '_ConvexHull' argument is an invalid pointer.",stderr);
    abort();
    };

if ( _StartPoint == NULL )
    {
    fputs("AllocationCheck(): '_StartPoint' argument is an invalid pointer.",stderr);
    abort();
    };

if ( _CH == NULL )
    {
    fputs("AllocationCheck(): '_CH' argument is an invalid pointer.",stderr);
    abort();
    };

if ( _I == NULL )
    {
    fputs("AllocationCheck(): '_I' argument is an invalid pointer.",stderr);
    abort();
    };
};

// ____________________________________________________________________________________________________________

void Deallocation( struct LargePoint ( * _Large ), struct SmallPoint ( * _Small ),
                   unsigned short int * _L, unsigned short int * _S,
                   struct SmallPoint ( * _ConvexHull ),
                   unsigned short int * _StartPoint, unsigned short int * _CH,
                   unsigned short int * _I )
{
// Clearing the memory.
AllocationClear(_Large,_Small,_L,_S,_ConvexHull,_StartPoint,_CH,_I);

// Deallocating the memory.
free(_Large);
free(_Small);
free(_L);
free(_S);
free(_ConvexHull);
free(_StartPoint);
free(_CH);
free(_I);

// Reseting the pointer.
_Large = NULL;
_Small = NULL;
_L = NULL;
_S = NULL;
_ConvexHull = NULL;
_StartPoint = NULL;
_CH = NULL;
_I = NULL;
};

// ____________________________________________________________________________________________________________

void DataRead( struct LargePoint (* const _Large ), struct SmallPoint (* const _Small ) ,
               unsigned short int * const _L, unsigned short int * const _S )
{
// Declarations.
unsigned short int (*i) = (unsigned short int (*))malloc(sizeof(unsigned short int));

// Internal allocation check section.
if ( i == NULL )
    {
    fputs("DataRead(): 'i' variable is an invalid pointer.",stderr);
    abort();
    };

// I. Reading the number of _L lines.
fscanf(stdin,"%hu%*c",_L);

// II. Reading _L lines of the data points.
for ( (*i)=0; (*i)<(*_L); (*i)=(*i)+1 )
    {
    fscanf(stdin,"%ld%ld%*c",&_Large[(*i)].x,&_Large[(*i)].y);
    };

// III. Reading the number of _S lines.
fscanf(stdin,"%hu%*c",_S);

// IV. Reading _S lines of the data points.
for ( (*i)=0; (*i)<(*_S); (*i)=(*i)+1 )
    {
    fscanf(stdin,"%ld%ld%*c",&_Small[(*i)].x,&_Small[(*i)].y);
    };

// Deallocating the memory.
free(i);

// Reseting the pointer.
i = NULL;
};

// ____________________________________________________________________________________________________________

void FirstPointSearch( const struct LargePoint ( * const _Large ), const unsigned short int * const _L,
                       unsigned short int * const _StartPoint )
{
// Declarations.
unsigned short int (*i) = (unsigned short int (*))malloc(sizeof(unsigned short int));
long int (*min_val) = (long int (*))malloc(sizeof(long int));
unsigned short int (*min_idx) = (unsigned short int (*))malloc(sizeof(unsigned short int));

// Internal allocation check section.
if ( i == NULL )
    {
    fputs("FirstPointSearch(): 'i' variable is an invalid pointer.",stderr);
    abort();
    };

if ( min_val == NULL )
    {
    fputs("FirstPointSearch(): 'min' variable is an invalid pointer.",stderr);
    abort();
    };

if ( min_idx == NULL )
    {
    fputs("FirstPointSearch(): 'min' variable is an invalid pointer.",stderr);
    abort();
    };

// I. Searching for the minimal value of 'y' coordinate of the point.
(*min_idx) = 0;
(*min_val) = _Large[(*min_idx)].y;

for ( (*i)=1; (*i)<(*_L); (*i)=(*i)+1 )
    {
    if ( _Large[(*i)].y < (*min_val) )
        {
        (*min_val) = _Large[(*i)].y;
        (*min_idx) = (*i);
        };
    };

// II. Searching for points of the same 'y' coordinate value.
for ( (*i)=0; (*i)<(*_L); (*i)=(*i)+1 )
    {
    if ( _Large[(*i)].y == (*min_val) )
        {
        if ( _Large[(*i)].x > _Large[(*min_idx)].x )
            {
            // Lowest 'y', highest 'x' coordinates
            (*min_idx) = (*i);
            };
        };
    };

// III. Writing result to the outside data structure.
*(_StartPoint) = (*min_idx);

// Deallocating the memory.
free(i);
free(min_val);
free(min_idx);

// Reseting the pointer.
i = NULL;
min_val = NULL;
min_idx = NULL;
};

// ____________________________________________________________________________________________________________

void DispatchRadiusVectorAngle( struct LargePoint ( * const _Large ), const unsigned short int * const _L )
{
// Declarations.
unsigned short int (*i) = (unsigned short int *)malloc(sizeof(unsigned short int));
unsigned long int (*d) = (unsigned long int *)malloc(sizeof(unsigned long int));

// Internal allocation check section.
if ( i == NULL )
    {
    fputs("DispatchRadiusVectorAngle(): 'i' variable is an invalid pointer.",stderr);
    abort();
    };

if ( d == NULL )
    {
    fputs("DispatchRadiusVectorAngle(): 'd' variable is an invalid pointer.",stderr);
    abort();
    };

for ( (*i)=0; (*i)<(*_L); (*i)=(*i)+1 )
    {
    (*d) = abs(_Large[(*i)].x) + abs(_Large[(*i)].y);

    if ( (*d) != 0 )
        {
        if ( (_Large[(*i)].x >= 0) && (_Large[(*i)].y >= 0) )
            {
            _Large[(*i)].angle = (double)(_Large[(*i)].y) / (*d);
            }
        else
        if ( (_Large[(*i)].x < 0) && (_Large[(*i)].y > 0) )
            {
            _Large[(*i)].angle = 2 - ((double)(_Large[(*i)].y) / (*d));
            }
        else
        if ( (_Large[(*i)].x < 0) && (_Large[(*i)].y < 0) )
            {
            _Large[(*i)].angle = 2 + ((double)(abs(_Large[(*i)].y)) / (*d));
            }
        else
        if ( (_Large[(*i)].x >= 0) && (_Large[(*i)].y < 0) )
            {
            _Large[(*i)].angle = 4 - ((double)(abs(_Large[(*i)].y)) / (*d));
            };
        }
    else
        {
        _Large[(*i)].angle = 0.0;
        };
    };

// Deallocating the memory.
free(i);
free(d);

// Reseting the pointer.
i = NULL;
d = NULL;
};

// ____________________________________________________________________________________________________________

void Sorter( struct LargePoint ( * const _Large ), const unsigned short int * const _L )
{
// Declarations.
unsigned short int (*i) = (unsigned short int (*))malloc(sizeof(unsigned short int));
unsigned short int (*j) = (unsigned short int (*))malloc(sizeof(unsigned short int));
double (*tmp) = (double (*))malloc(sizeof(double));
long int (*tmp2) = (long int (*))malloc(sizeof(long int));

// Internal allocation check section.
if ( i == NULL )
    {
    fputs("Sorter(): 'i' variable is an invalid pointer.",stderr);
    abort();
    };

if ( j == NULL )
    {
    fputs("Sorter(): 'j' variable is an invalid pointer.",stderr);
    abort();
    };

if ( tmp == NULL )
    {
    fputs("Sorter(): 'tmp' variable is an invalid pointer.",stderr);
    abort();
    };

if ( tmp2 == NULL )
    {
    fputs("Sorter(): 'tmp2' variable is an invalid pointer.",stderr);
    abort();
    };

// Bubble sort.
for ( (*i)=0; (*i)<(*_L); (*i)=(*i)+1 )
    {
    for ( (*j)=0; (*j)<((*_L)-1); (*j)=(*j)+1 )
        {
        if ( _Large[(*j)].angle > _Large[(*j)+1].angle )
            {
            // Swapping the 'angle' pole.
            (*tmp) = _Large[(*j)].angle;
            _Large[(*j)].angle = _Large[(*j)+1].angle;
            _Large[(*j)+1].angle = (*tmp);

            // Swapping the 'y' pole.
            (*tmp2) = _Large[(*j)].y;
            _Large[(*j)].y = _Large[(*j)+1].y;
            _Large[(*j)+1].y = (*tmp2);

            // Swapping the 'x' pole.
            (*tmp2) = _Large[(*j)].x;
            _Large[(*j)].x = _Large[(*j)+1].x;
            _Large[(*j)+1].x = (*tmp2);
            };
        };
    };

// Deallocating the memory.
free(i);
free(j);
free(tmp);
free(tmp2);

// Reseting the pointer.
i = NULL;
j = NULL;
tmp = NULL;
tmp2 = NULL;
};

// ____________________________________________________________________________________________________________

void FirstDataAbsorption( struct SmallPoint ( * const _ConvexHull ), struct LargePoint ( * const _Large ),
                          unsigned short int * const _L, const unsigned short int * const _StartPoint )
{
// Declarations.
unsigned short int (*i) = (unsigned short int (*))malloc(sizeof(unsigned short int));
short int (*ctr) = (short int (*))malloc(sizeof(short int));
long int (*cp_x) = (long int (*))malloc(sizeof(long int));
long int (*cp_y) = (long int (*))malloc(sizeof(long int));

// Internal allocation check section.
if ( i == NULL )
    {
    fputs("FirstDataAbsorption(): 'i' variable is an invalid pointer.",stderr);
    abort();
    };

if ( ctr == NULL )
    {
    fputs("FirstDataAbsorption(): 'ctr' variable is an invalid pointer.",stderr);
    abort();
    };

if ( cp_x == NULL )
    {
    fputs("FirstDataAbsorption(): 'cp_x' variable is an invalid pointer.",stderr);
    abort();
    };

if ( cp_y == NULL )
    {
    fputs("FirstDataAbsorption(): 'cp_y' variable is an invalid pointer.",stderr);
    abort();
    };

// I. Evaluating the starting point to the convex hull outside data structure.
(*ctr) = 0;
_ConvexHull[(*ctr)].x = _Large[*(_StartPoint)].x;
_ConvexHull[(*ctr)].y = _Large[*(_StartPoint)].y;
(*cp_x) = _Large[*(_StartPoint)].x;
(*cp_y) = _Large[*(_StartPoint)].y;
(*ctr) = (*ctr) + 1;

// II. Executing the sorting procedure.
Sorter(_Large,_L);

// III. Evaluating the first two points on the sorted list to the convex hull structure.
for ( (*i)=0; (*i)<(*_L); (*i)=(*i)+1 )
    {
    if ( (*ctr) >= 3 )
        {
        break;
        }
    else
        {
        if ( (_Large[(*i)].x != (*cp_x)) || (_Large[(*i)].y != (*cp_y)) )
            {
            _ConvexHull[(*ctr)].x = _Large[(*i)].x;
            _ConvexHull[(*ctr)].y = _Large[(*i)].y;
            (*ctr) = (*ctr) + 1;
            }
        else
        if ( (_Large[(*i)].x == (*cp_x)) || (_Large[(*i)].y == (*cp_y)) )
            {
            _Large[(*i)].x = -1;
            _Large[(*i)].y = -1;
            };
        };
    };

// IV. Removing added points from the original data structure.
for ( (*i)=0; (*i)<(*_L); (*i)=(*i)+1 )
    {
    if ( (_Large[(*i)].x == (-1)) && (_Large[(*i)].y == (-1)) )
        {
        for ( (*cp_x)=(*i); (*cp_x)<((*_L)-1); (*cp_x)=(*cp_x)+1 )
            {
            _Large[(*cp_x)] = _Large[(*cp_x)+1];
            };

        break;
        };
    };

*(_L) = *(_L) - 1;

for ( (*i)=2; (*i)<(*_L); (*i)=(*i)+1 )
    {
    _Large[(*i)-2] = _Large[(*i)];
    };

*(_L) = *(_L) - 2;

// Deallocating the memory.
free(i);
free(ctr);
free(cp_x);
free(cp_y);

// Reseting the pointer.
i = NULL;
ctr = NULL;
cp_x = NULL;
cp_y = NULL;
};

// ____________________________________________________________________________________________________________

void ConvexHullBuilder( struct SmallPoint ( * const _ConvexHull ),
                        const struct LargePoint ( * const _Large ), const unsigned short int * const _L,
                        unsigned short int * const _CH )
{
// Declarations.
unsigned short int (*i) = (unsigned short int (*))malloc(sizeof(unsigned short int));
long long int (*det) = (long long int (*))malloc(sizeof(long long int));
unsigned short int (*succ) = (unsigned short int (*))malloc(sizeof(unsigned short int));

// Internal allocation check section.
if ( i == NULL )
    {
    fputs("ConvexHullBuilder(): 'i' variable is an invalid pointer.",stderr);
    abort();
    };

if ( det == NULL )
    {
    fputs("ConvexHullBuilder(): 'det' variable is an invalid pointer.",stderr);
    abort();
    };

if ( succ == NULL )
    {
    fputs("ConvexHullBuilder(): 'succ' variable is an invalid pointer.",stderr);
    abort();
    };

// Main processing.
(*succ) = 3;

for ( (*i)=0; (*i)<(*_L); (*i)=(*i)+1 )
    {
    (*det) = Determinant( &(_ConvexHull[(*succ)-2]), &(_ConvexHull[(*succ)-1]), &(_Large[(*i)]) );

    if ( (*det) <= 0 )
        {
        // The next point is on the left or is collinear.
        _ConvexHull[(*succ)].x = _Large[(*i)].x;
        _ConvexHull[(*succ)].y = _Large[(*i)].y;
        (*succ) = (*succ) + 1;
        }
    else
        {
        // The next point is on the right.
        _ConvexHull[(*succ)-1].x = _Large[(*i)].x;
        _ConvexHull[(*succ)-1].y = _Large[(*i)].y;
        };
    };

*(_CH) = (*succ);

// Deallocating the memory.
free(i);
free(det);
free(succ);

// Reseting the pointer.
i = NULL;
det = NULL;
succ = NULL;
};

// ____________________________________________________________________________________________________________

long long int Determinant( const struct SmallPoint ( * const _Point1 ),
                           const struct SmallPoint ( * const _Point2 ),
                           const struct LargePoint ( * const _Point3 ) )

// VAR < 0  :=  _Point3 is on the left side of [_Point1 -> _Point2] section
// VAR = 0  :=  _Point3 is collinear with [_Point1 -> _Point2] section
// VAR > 0  :=  _Point3 is on the right side of [_Point1 -> _Point2] section

{
// Declarations.
long long int result = 0;
long long int (*tmp1) = (long long int (*))malloc(sizeof(long long int));
long long int (*tmp2) = (long long int (*))malloc(sizeof(long long int));

// Internal allocation check section.
if ( tmp1 == NULL )
    {
    fputs("Determinant(): 'tmp1' variable is an invalid pointer.",stderr);
    abort();
    };

if ( tmp2 == NULL )
    {
    fputs("Determinant(): 'tmp2' variable is an invalid pointer.",stderr);
    abort();
    };

// Counting.
(*tmp1) = _Point1->x;
(*tmp2) = _Point2->y;
(*tmp1) = (*tmp1) * (*tmp2);
result = result + (*tmp1);

(*tmp1) = _Point2->x;
(*tmp2) = _Point3->y;
(*tmp1) = (*tmp1) * (*tmp2);
result = result + (*tmp1);

(*tmp1) = _Point3->x;
(*tmp2) = _Point1->y;
(*tmp1) = (*tmp1) * (*tmp2);
result = result + (*tmp1);

(*tmp1) = _Point3->x;
(*tmp2) = _Point2->y;
(*tmp1) = (*tmp1) * (*tmp2);
result = result - (*tmp1);

(*tmp1) = _Point1->x;
(*tmp2) = _Point3->y;
(*tmp1) = (*tmp1) * (*tmp2);
result = result - (*tmp1);

(*tmp1) = _Point2->x;
(*tmp2) = _Point1->y;
(*tmp1) = (*tmp1) * (*tmp2);
result = result - (*tmp1);

result = -(result);

// Deallocating the memory.
free(tmp1);
free(tmp2);

// Reseting the pointer.
tmp1 = NULL;
tmp2 = NULL;

// Exiting.
return ( result );
};

// ____________________________________________________________________________________________________________

void CoordinatesTranslation( struct LargePoint ( * const _Large ), struct SmallPoint ( * const _Small ),
                             const unsigned short int * const _L, const unsigned short int * const _S,
                             const unsigned short int * const _StartPoint )
{
// Declarations.
unsigned short int (*i) = (unsigned short int (*))malloc(sizeof(unsigned short int));

// Internal allocation check section.
if ( i == NULL )
    {
    fputs("CoordinatesTranslation(): 'i' variable is an invalid pointer.",stderr);
    abort();
    };

// Translation for the large lanterns data.
for ( (*i)=0; (*i)<(*_L); (*i)=(*i)+1 )
    {
    if ( (*i) != *(_StartPoint) )
        {
        _Large[(*i)].x = _Large[(*i)].x - _Large[*(_StartPoint)].x;
        _Large[(*i)].y = _Large[(*i)].y - _Large[*(_StartPoint)].y;
        };
    };

// Translation for the small lanterns data.
for ( (*i)=0; (*i)<(*_S); (*i)=(*i)+1 )
    {
    _Small[(*i)].x = _Small[(*i)].x - _Large[*(_StartPoint)].x;
    _Small[(*i)].y = _Small[(*i)].y - _Large[*(_StartPoint)].y;
    };

// Translation of the pattern point.
_Large[*(_StartPoint)].x = 0;
_Large[*(_StartPoint)].y = 0;
_Large[*(_StartPoint)].angle = 0.0;

// Deallocating the memory.
free(i);

// Reseting the pointer.
i = NULL;
};

// ____________________________________________________________________________________________________________

void IntersectionsCounter( const struct SmallPoint ( * const _ConvexHull ), const unsigned short int * const _CH,
                           const struct SmallPoint ( * const _Small ), const unsigned short int * const _S,
                           unsigned short int * const _I )
{
// Declarations.
unsigned short int (*i) = (unsigned short int (*))malloc(sizeof(unsigned short int));
struct LargePoint (*AuxPoint1) = (struct LargePoint (*))malloc(sizeof(struct LargePoint));
unsigned short int (*j) = (unsigned short int (*))malloc(sizeof(unsigned short int));
long long int (*det1) = (long long int (*))malloc(sizeof(long long int));
long long int (*det2) = (long long int (*))malloc(sizeof(long long int));
long long int (*det3) = (long long int (*))malloc(sizeof(long long int));
long long int (*det4) = (long long int (*))malloc(sizeof(long long int));
struct SmallPoint (*AuxPoint2) = (struct SmallPoint (*))malloc(sizeof(struct SmallPoint));
long long int (*tmp) = (long long int (*))malloc(sizeof(long long int));
bool_tri (*result) = (bool_tri (*))malloc(sizeof(bool_tri));
unsigned short int (*ctr) = (unsigned short int (*))malloc(sizeof(unsigned short int));
unsigned short int (*output) = (unsigned short int (*))malloc(sizeof(unsigned short int));
bool_tri (*common) = (bool_tri (*))malloc(sizeof(bool_tri));
bool_tri (*occ) = (bool_tri (*))malloc(sizeof(bool_tri));

// Internal allocation check section.
if ( i == NULL )
    {
    fputs("IntersectionsCounter(): 'i' variable is an invalid pointer.",stderr);
    abort();
    };

if ( AuxPoint1 == NULL )
    {
    fputs("IntersectionsCounter(): 'AuxPoint1' variable is an invalid pointer.",stderr);
    abort();
    };

if ( j == NULL )
    {
    fputs("IntersectionsCounter(): 'j' variable is an invalid pointer.",stderr);
    abort();
    };

if ( det1 == NULL )
    {
    fputs("IntersectionsCounter(): 'det1' variable is an invalid pointer.",stderr);
    abort();
    };

if ( det2 == NULL )
    {
    fputs("IntersectionsCounter(): 'det2' variable is an invalid pointer.",stderr);
    abort();
    };

if ( det3 == NULL )
    {
    fputs("IntersectionsCounter(): 'det3' variable is an invalid pointer.",stderr);
    abort();
    };

if ( det4 == NULL )
    {
    fputs("IntersectionsCounter(): 'det4' variable is an invalid pointer.",stderr);
    abort();
    };

if ( AuxPoint2 == NULL )
    {
    fputs("IntersectionsCounter(): 'AuxPoint2' variable is an invalid pointer.",stderr);
    abort();
    };

if ( tmp == NULL )
    {
    fputs("IntersectionsCounter(): 'tmp' variable is an invalid pointer.",stderr);
    abort();
    };

if ( result == NULL )
    {
    fputs("IntersectionsCounter(): 'result' variable is an invalid pointer.",stderr);
    abort();
    };

if ( ctr == NULL )
    {
    fputs("IntersectionsCounter(): 'ctr' variable is an invalid pointer.",stderr);
    abort();
    };

if ( output == NULL )
    {
    fputs("IntersectionsCounter(): 'output' variable is an invalid pointer.",stderr);
    abort();
    };

if ( common == NULL )
    {
    fputs("IntersectionsCounter(): 'common' variable is an invalid pointer.",stderr);
    abort();
    };

if ( occ == NULL )
    {
    fputs("IntersectionsCounter(): 'occ' variable is an invalid pointer.",stderr);
    abort();
    };

// Preparing.
(*AuxPoint1).x = OFFSET;
(*AuxPoint1).y = 0;
(*AuxPoint1).angle = 0.0;
(*AuxPoint2).x = OFFSET;
(*AuxPoint2).y = 0;
(*result) = NONE;
(*ctr) = 0;
(*output) = 0;
(*common) = NONE;
(*occ) = NONE;

// For each small lantern...
for ( (*i)=0; (*i)<(*_S); (*i)=(*i)+1 )
    {
    // ... check the intersections with the sections defined by the convex hull points.
    for ( (*j)=0; (*j)<(*_CH); (*j)=(*j)+1 )
        {
        // Passing the arguments for determinants counting.
        (*AuxPoint2).x = OFFSET;
        (*AuxPoint2).y = _Small[(*i)].y;
        (*AuxPoint1).y = _ConvexHull[(*j)].y;
        (*AuxPoint1).x = _ConvexHull[(*j)].x;
        (*det1) = Determinant( AuxPoint2, &(_Small[(*i)]), AuxPoint1 );

        if ( ((*j) + 1) != (*_CH) )
            {
            (*AuxPoint1).x = _ConvexHull[(*j)+1].x;
            (*AuxPoint1).y = _ConvexHull[(*j)+1].y;
            }
        else
            {
            (*AuxPoint1).x = _ConvexHull[0].x;
            (*AuxPoint1).y = _ConvexHull[0].y;
            };

        (*det2) = Determinant( AuxPoint2, &(_Small[(*i)]), AuxPoint1 );
        (*AuxPoint1).x = _Small[(*i)].x;
        (*AuxPoint1).y = _Small[(*i)].y;

        if ( ((*j) + 1) != (*_CH) )
            {
            (*det3) = Determinant( &(_ConvexHull[(*j)]), &(_ConvexHull[(*j)+1]), AuxPoint1 );
            }
        else
            {
            (*det3) = Determinant( &(_ConvexHull[(*j)]), &(_ConvexHull[0]), AuxPoint1 );
            };

        (*AuxPoint1).x = OFFSET;
        (*AuxPoint1).y = _Small[(*i)].y;

        if ( ((*j) + 1) != (*_CH) )
            {
            (*det4) = Determinant( &(_ConvexHull[(*j)]), &(_ConvexHull[(*j)+1]), AuxPoint1 );
            }
        else
            {
            (*det4) = Determinant( &(_ConvexHull[(*j)]), &(_ConvexHull[0]), AuxPoint1 );
            };

        // Checking the condition of sections intersection.
        if ( (((*det1) < 0) && ((*det2) < 0)) || (((*det1) > 0) && ((*det2) > 0)) )
            {
            (*tmp) = 1;
            }
        else
        if ( ((*det1) == 0) || ((*det2) == 0) )
            {
            (*tmp) = 0;
            }
        else
            {
            (*tmp) = -1;
            };

        //(*tmp) = (*det1) * (*det2);

        if ( (*tmp) < 0 )
            {
            if ( (((*det3) < 0) && ((*det4) < 0)) || (((*det3) > 0) && ((*det4) > 0)) )
                {
                (*tmp) = 1;
                }
            else
            if ( ((*det3) == 0) || ((*det4) == 0) )
                {
                (*tmp) = 0;
                }
            else
                {
                (*tmp) = -1;
                };

            //(*tmp) = (*det3) * (*det4);

            if ( (*tmp) < 0 )
                {
                (*ctr) = (*ctr) + 1;
                continue;
                };
            };

        // Checking for the common intersected points.
        if ( (*det1) == 0 )
            {
            (*AuxPoint2).x = OFFSET;
            (*AuxPoint2).y = _Small[(*i)].y;
            (*AuxPoint1).x = _ConvexHull[(*j)].x;
            (*AuxPoint1).y = _ConvexHull[(*j)].y;
            (*result) = IsOnSection( AuxPoint2, &(_Small[(*i)]), AuxPoint1 );
            
            if ( _Small[(*i)].y == _ConvexHull[(*j)].y )
                {
                (*common) = TRUE;
                };

            if ( (*result) == TRUE )
                {
                (*occ) = TRUE;
                };

            if ( ((*result)  == TRUE) && ((*common) != TRUE) )
                {
                (*ctr) = (*ctr) + 1;
                continue;
                };

            (*common) = FALSE;
            }
        else
        if ( (*det2) == 0 )
            {
            if ( ((*j) + 1) != (*_CH) )
                {
                (*AuxPoint1).x = _ConvexHull[(*j)+1].x;
                (*AuxPoint1).y = _ConvexHull[(*j)+1].y;

                if ( _Small[(*i)].y == _ConvexHull[(*j)+1].y )
                    {
                    (*common) = TRUE;
                    (*ctr) = (*ctr) - 1;
                    };
                }
            else
                {
                (*AuxPoint1).x = _ConvexHull[0].x;
                (*AuxPoint1).y = _ConvexHull[0].y;

                if ( _Small[(*i)].y == _ConvexHull[0].y )
                    {
                    (*common) = TRUE;
                    (*ctr) = (*ctr) - 1;
                    };
                };

            (*result) = IsOnSection( AuxPoint2, &(_Small[(*i)]), AuxPoint1 );

            if ( (*result) == TRUE )
                {
                (*occ) = TRUE;
                };

            if ( ((*result) == TRUE) && ((*common) != TRUE) )
                {
                (*ctr) = (*ctr) + 1;
                continue;
                };

            (*common) = FALSE;
            }
        else
        if ( (*det3) == 0 )
            {
            (*AuxPoint1).x = _Small[(*i)].x;
            (*AuxPoint1).y = _Small[(*i)].y;

            if ( ((*j) + 1) != (*_CH) )
                {
                (*result) = IsOnSection( &(_ConvexHull[(*j)]), &(_ConvexHull[(*j)+1]), AuxPoint1 );

                if ( _Small[(*i)].y == _ConvexHull[(*j)].y )
                    {
                    (*common) = TRUE;
                    };
                }
            else
                {
                (*result) = IsOnSection( &(_ConvexHull[(*j)]), &(_ConvexHull[0]), AuxPoint1 );

                if ( _Small[(*i)].y == _ConvexHull[0].y )
                    {
                    (*common) = TRUE;
                    };
                };

            if ( (*result) == TRUE )
                {
                (*occ) = TRUE;
                };

            if ( ((*result) == TRUE) && ((*common) != TRUE) )
                {
                (*ctr) = (*ctr) + 1;
                continue;
                };

            (*common) = FALSE;
            }
        else
        if ( (*det4) == 0 )
            {
            (*AuxPoint1).x = OFFSET;
            (*AuxPoint1).y = _Small[(*i)].y;

            if ( ((*j) + 1) != (*_CH) )
                {
                (*result) = IsOnSection( &(_ConvexHull[(*j)]), &(_ConvexHull[(*j)+1]), AuxPoint1 );

                if ( _Small[(*i)].y == _ConvexHull[(*j)+1].y )
                    {
                    (*common) = TRUE;
                    (*ctr) = (*ctr) - 1;
                    };
                }
            else
                {
                (*result) = IsOnSection( &(_ConvexHull[(*j)]), &(_ConvexHull[0]), AuxPoint1 );

                if ( _Small[(*i)].y == _ConvexHull[0].y )
                    {
                    (*common) = TRUE;
                    (*ctr) = (*ctr) - 1;
                    };
                };

            if ( (*result) == TRUE )
                {
                (*occ) = TRUE;
                };

            if ( ((*result) == TRUE) && ((*common) != TRUE) )
                {
                (*ctr) = (*ctr) + 1;
                continue;
                };

            (*common) = FALSE;
            };

        if ( ((*occ) == TRUE) && ((*ctr) > 1) )
            {
            (*ctr) = (*ctr) - 1;
            (*occ) = FALSE;
            };
        };

    // If the number of intersections is an odd number...
    if ( ((*ctr) % 2) != 0 )
        {
        // ... increment the number of total intersections.
        (*output) = (*output) + 1;
        };

    (*ctr) = 0;
    };

// Returning the number of intersections.
*(_I) = (*output);

// Deallocating the memory.
free(i);
free(AuxPoint1);
free(j);
free(det1);
free(det2);
free(det3);
free(det4);
free(AuxPoint2);
free(tmp);
free(result);
free(ctr);
free(output);
free(common);
free(occ);

// Reseting the pointer.
i = NULL;
AuxPoint1 = NULL;
j = NULL;
det1 = NULL;
det2 = NULL;
det3 = NULL;
det4 = NULL;
AuxPoint2 = NULL;
tmp = NULL;
result = NULL;
ctr = NULL;
output = NULL;
common = NULL;
occ = NULL;
};

// ____________________________________________________________________________________________________________

bool_tri IsOnSection( const struct SmallPoint ( * const _Point1 ), const struct SmallPoint ( * const _Point2 ),
                      const struct LargePoint ( * const _Point3 ) )
{
return ( (((_Point3->x >= Minimum(&(_Point1->x),&(_Point2->x))) && (_Point3->x <= Maximum(&(_Point1->x),&(_Point2->x)))) 
         && (((_Point3->y >= Minimum(&(_Point1->y),&(_Point2->y))) && (_Point3->y <= Maximum(&(_Point1->y),&(_Point2->y))))))
         ? TRUE : FALSE );
};

// ____________________________________________________________________________________________________________

long int Minimum( const long int * const _left, const long int * const _right )
{
return ( (*(_left) < *(_right)) ? *(_left) : *(_right) );
};

// ____________________________________________________________________________________________________________

long int Maximum( const long int * const _left, const long int * const _right )
{
return ( (*(_left) > *(_right)) ? *(_left) : *(_right) );
};

// ____________________________________________________________________________________________________________

void PrintOutput( const unsigned short int * const _I )
{
fprintf(stdout,"%hu\n",*(_I));
};

// ____________________________________________________________________________________________________________
