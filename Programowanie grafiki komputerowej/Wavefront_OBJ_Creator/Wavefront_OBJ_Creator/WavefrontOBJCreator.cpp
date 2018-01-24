#include "Wavefront_OBJ_Creator.h"
#include <cstring>
#include <cstdlib>

// _______________________________________________________________________________________________

WavefrontOBJCreator::WavefrontOBJCreator()
    : in_ ( nullptr )
    , out_ ( nullptr )
    , input_filename_ ( )
    , output_filename_ ( )
    , expected_ ( 255 )
    , height_ ( 5 )

{
// Clearing the arrays.
memset(input_filename_,0,F*sizeof(char));
memset(output_filename_,0,F*sizeof(char));
};

// _______________________________________________________________________________________________

WavefrontOBJCreator::~WavefrontOBJCreator()
{
// Clearing the memory.
in_ = nullptr;
out_ = nullptr;
memset(input_filename_,0,F*sizeof(char));
memset(output_filename_,0,F*sizeof(char));
expected_ = 0;
height_ = 0;
};

// _______________________________________________________________________________________________

WavefrontOBJCreator::WavefrontOBJCreator ( const WavefrontOBJCreator & _rvalue )
    : in_ ( _rvalue.in_ )
    , out_ ( _rvalue.out_ )
    , input_filename_ ( )
    , output_filename_ ( )
    , expected_ ( _rvalue.expected_ )
    , height_ ( _rvalue.height_ )

{
// Clearing and copying.
memset(input_filename_,0,F*sizeof(char));
memset(output_filename_,0,F*sizeof(char));
memcpy(input_filename_,_rvalue.input_filename_,F*sizeof(char));
memcpy(output_filename_,_rvalue.output_filename_,F*sizeof(char));
};

// _______________________________________________________________________________________________

WavefrontOBJCreator & WavefrontOBJCreator::operator= ( const WavefrontOBJCreator & _rvalue )
{
//*this = _rvalue; // ?
return (*this);
};

// _______________________________________________________________________________________________

const FILE * const WavefrontOBJCreator::GetInputFilePointer ( )
{
return ( in_ );
};

// _______________________________________________________________________________________________

const FILE * const WavefrontOBJCreator::GetOutputFilePointer ( )
{
return ( out_ );
};

// _______________________________________________________________________________________________

int WavefrontOBJCreator::GetFilenameConstantValue ( )
{
return ( F );
};

// _______________________________________________________________________________________________

const char * const WavefrontOBJCreator::GetInputFilename ( )
{
return ( input_filename_ );
};

// _______________________________________________________________________________________________

const char * const WavefrontOBJCreator::GetOutputFilename ( )
{
return ( output_filename_ );
};

// _______________________________________________________________________________________________

short int WavefrontOBJCreator::GetExpectedValue (  )
{
return ( expected_ );
};

// _______________________________________________________________________________________________

short int WavefrontOBJCreator::GetHeight ( )
{
return ( height_ );
};

// _______________________________________________________________________________________________

void WavefrontOBJCreator::SetInputFilePointer ( FILE * & _fp )
{
if ( _fp != nullptr )
    {
    in_ = _fp;
    };
};

// _______________________________________________________________________________________________

void WavefrontOBJCreator::SetOutputFilePointer ( FILE * & _fp )
{
if ( _fp != nullptr )
    {
    out_ = _fp;
    };
};

// _______________________________________________________________________________________________

void WavefrontOBJCreator::SetInputFilename ( const char * _string )
{
if ( _string != nullptr )
    {
    memset(input_filename_,0,F*sizeof(char));
    memcpy(input_filename_,_string,strlen(_string));
    };
};

// _______________________________________________________________________________________________

void WavefrontOBJCreator::SetOutputFilename ( const char * _string )
{
if ( _string != nullptr )
    {
    memset(output_filename_,0,F*sizeof(char));
    memcpy(output_filename_,_string,strlen(_string));
    };
};

// _______________________________________________________________________________________________

void WavefrontOBJCreator::SetExpectedValue ( short int _value )
{
expected_ = _value;
};

// _______________________________________________________________________________________________

void WavefrontOBJCreator::SetHeight ( short int _value )
{
height_ = _value;
};

// _______________________________________________________________________________________________

unsigned long int WavefrontOBJCreator::CreateWavefrontFile( const char * _pgm, const char * _obj )
// 1        Not a valid filename found for the .pgm file.
// 2        Not a valid filename found for the .obj file.
// 3        The input file (.pgm) has not been opened corretly.
// 4        The input file (.obj) has not been opened corretly.
// VAR      The number of expected values read from the input file (.pgm).

{
// Declarations.
const short int offset = 8;                 // An offset related to the matrix of faces.

int done = 0;                               // The code returned by a function as a result of the executed call.
unsigned long int succ = 1;                 // The successor of the model (Plane) number.
unsigned long int rows;                     // Number of rows read from the input file (.pgm).
unsigned long int columns;                  // Number of columns read from the input file (.pgm).
unsigned long int i;                        // A successor for columns.
unsigned long int j;                        // A successor for rows.
short int tmp;                              // An auxiliary, temporal variable.
long long int x1;                           // A vertex coordinate number. Used for optimization purposes.
long long int z1;                           // A vertex coordinate number. Used for optimization purposes.
long long int z2;                           // A vertex coordinate number. Used for optimization purposes.

// The matrix of faces. Related with an offset.
const short int M = 6;
const short int N = 4;
unsigned long int faces[M][N] = { { 1,2,3,4 },{ 5,6,7,8 },{ 7,6,2,3 },{ 8,7,3,4 },{ 8,5,1,4 },{ 5,6,2,1 } };

// Checking the filename of the .pgm file.
if ( _pgm == nullptr )
    {
    done = 1;
    };

if ( !done )
    {
    // Checking the filename of the .obj file.
    if ( _obj == nullptr )
        {
        done = 2;
        };

    if ( !done )
        {
        // Opening the files.
        in_ = fopen(_pgm,"rt");
        out_ = fopen(_obj,"wt");

        // Checking the input file pointer.
        if ( in_ == nullptr )
            {
            done = 3;
            };

        if ( !done )
            {
            // Checking the output file pointer.
            if ( in_ == nullptr )
                {
                done = 4;
                };

            if ( !done )
                {
                // Printing the main comment line.
                fprintf(out_,"# WavefrontOBJCreator\n");

                // Reading the data about number of rows and columns.
                fscanf(in_,"%*s");
                fscanf(in_,"%lu%lu",&columns,&rows);
                fscanf(in_,"%*s%[\n]");
                
                // Starting the file reading loop.
                for ( j=0; j<rows; j++ )
                    {
                    for ( i=0; i<columns; i++ )
                        {
                        // Reading the next value from the file.
                        fscanf(in_,"%hd",&tmp);

                        // Checking if it is an expected value.
                        if ( tmp == expected_ )
                            {
                            // Counting the vertices set.
                            x1 = i + 1;
                            z1 = -(long long int)(j);
                            z2 = z1 - 1;

                            // Printing the information about the wall.
                            fprintf(out_,"# Wall [ %lu COLUMN ] [ %lu ROW ]\n",i,j);
                            fprintf(out_,"o Plane.%lu\n",succ);

                            // Successoring.
                            done++;
                            succ++;

                            // Printing the vertices set to the file.
                            fprintf(out_,
                                    "v %lld.000000 0.000000 %lld.000000\n"
                                    "v %lu.000000 0.000000 %lld.000000\n"
                                    "v %lu.000000 0.000000 %lld.000000\n"
                                    "v %lld.000000 0.000000 %lld.000000\n"
                                    "v %lld.000000 %hd.000000 %lld.000000\n"
                                    "v %lu.000000 %hd.000000 %lld.000000\n"
                                    "v %lu.000000 %hd.000000 %lld.000000\n"
                                    "v %lld.000000 %hd.000000 %lld.000000\n"
                                    ,x1,z1,i,z1,i,z2,x1,z2
                                    ,x1,height_,z1,i,height_,z1,i,height_,z2,x1,height_,z2);

                            // Printing the faces data.
                            fprintf(out_,
                                    "f %lu %lu %lu %lu\n"
                                    "f %lu %lu %lu %lu\n"
                                    "f %lu %lu %lu %lu\n"
                                    "f %lu %lu %lu %lu\n"
                                    "f %lu %lu %lu %lu\n"
                                    "f %lu %lu %lu %lu\n"
                                    ,faces[0][0],faces[0][1],faces[0][2],faces[0][3]
                                    ,faces[1][0],faces[1][1],faces[1][2],faces[1][3]
                                    ,faces[2][0],faces[2][1],faces[2][2],faces[2][3]
                                    ,faces[3][0],faces[3][1],faces[3][2],faces[3][3]
                                    ,faces[4][0],faces[4][1],faces[4][2],faces[4][3]
                                    ,faces[5][0],faces[5][1],faces[5][2],faces[5][3]
                                    );

                            // Offseting the matrix of faces.
                            for ( z1=0; z1<M; z1++ )
                                {
                                for ( z2=0; z2<N; z2++ )
                                    {
                                    faces[z1][z2] = faces[z1][z2] + offset;
                                    };
                                };

                            // Clearing the counted data for the safety of the next step.
                            x1 = 0;
                            z1 = 0;
                            z2 = 0;
                            };
                        };

                    // The shadow read for a newline character.
                    fscanf(in_,"%[\n]");
                    };
                };
            };
        };
    };
    
//

// Closing the files.
fclose(in_);
fclose(out_);

// Exiting.
return (done);
};

// _______________________________________________________________________________________________

unsigned long int WavefrontOBJCreator::CreateWavefrontFile( )
{
unsigned long int done = CreateWavefrontFile(input_filename_,output_filename_);
return (done);
};

// _______________________________________________________________________________________________
