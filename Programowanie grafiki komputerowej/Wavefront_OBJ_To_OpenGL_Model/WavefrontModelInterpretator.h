#pragma once

// _________________________________________________________________________________

#include "..\freeglut\include\GL\freeglut.h"
#include "Colors.h"
#include "ProgramAuxiliaryStructure.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <stddef.h>
#include <errno.h>

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION PROTOTYPES ***/

// A procedure for displaying the Wavefront .obj file 3D model.
void WavefrontModelInterpretator( void );

// A procedure of building predefined pillar with a contour.
void PredefinedPillar( void );

// A procedure of building model from the parsed data.
void ModelFromFile( void );

// A procedure of building model from the parsed data using Z-Buffer.
void ModelFromFileWithZBuffer( void );

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** DATATYPES DEFINITIONS ***/

namespace obj
    {

    struct WavefrontOBJData
        {

        // An enumerator for the datatypes boundaries.
        enum constants1_
            {
            VERTICES_ROWS = (unsigned short int)(100),
            VERTICES_COLUMNS = (unsigned short int)(3),
            FACES_ROWS = (unsigned short int)(VERTICES_ROWS),
            FACES_COLUMNS = (unsigned short int)(4),
            BUFFER_SIZE = (unsigned short int)(50)
            };

        // An enumerator for scene models differentiate.
        enum constants2_
            {
            PREDEFINED_PILLAR_WITH_CONTOUR = 2001,
            WAVEFRONT_MODEL_FROM_A_FILE = 2002,
            WAVEFRONT_MODEL_WITH_Z_BUFFER = 2003
            };

        // A VLA array for the vertices of the given vector data.
        double (*Vertices_)[ VERTICES_ROWS ];

        // A VLA array for the faces data based on the written vertices.
        short int (*Faces_)[ FACES_ROWS ];

        // A flag indicating the information about parsering.
        bool parsed_;

        // A file pointer to the input data file.
        FILE * input_;

        // An enumerator for differentiate between displaying scene.
        enum constants2_ model_;

        // The number of counted vertices during the parsering.
        unsigned short int vertices_;

        // The number of counted faces during the parsering.
        unsigned short int faces_;

        // ----------------------------

        // A set-class-like function specifying the prerequisites.
        int SetStructure( void );

        // A method-like procedure for do the proper cleaning.
        void Clean( void );

        // A procedure for parsering the Wavefront .obj file to the structure.
        int FileToStructureParser( void );

        // A procedure for defining the OpenGL interpretation of the Wavefront .obj parsed data.
        void Build3DModel( void );

        }
        
        /*** STRUCTURE DECLARATIONS ***/
        OBJ_data;
        ;

    };

// _________________________________________________________________________________

int obj::WavefrontOBJData::SetStructure()
//  0       The structure allocate the arrays properly.
//  1       The VLA for the vertices data has not been allocated.
//  2       The VLA for the faces order information has not been allocated.
//  3       Both, the vertices and faces arrays has not been allocated.
//  4       The allocation has been skipped.

    {
    // Declaration.
    static int done = -1;

    if ( ( done != 4 ) && ( done != 0 ) )
        {
        // Resetting at start.
        Vertices_ = nullptr;
        Faces_ = nullptr;

        // This may not be defined at compile time.
        // Allocating the memory for the vertices data.
        Vertices_ = (double (*)[VERTICES_ROWS])malloc(sizeof *Vertices_ * VERTICES_COLUMNS);
        memset(Vertices_, 0, VERTICES_ROWS * VERTICES_COLUMNS * sizeof(double));

        // Allocating the data for the faces order information.
        Faces_ = (short int (*)[FACES_ROWS])malloc(sizeof *Faces_ * FACES_COLUMNS);
        memset(Faces_, 0, FACES_ROWS * FACES_COLUMNS * sizeof(short int));

        // Setting the poles.
        parsed_ = false;
        input_ = nullptr;
        model_ = obj::WavefrontOBJData::PREDEFINED_PILLAR_WITH_CONTOUR;
        vertices_ = 0;
        faces_ = 0;

        // Allocation check.
        if ( ( Vertices_ == nullptr ) && ( Faces_ == nullptr ) ) done = 3;
        else if ( Vertices_ == nullptr ) done = 1;
        else if ( Faces_ == nullptr ) done = 2;
        else done = 0;
        }
    else done = 4;

    // Exiting.
    return ( done );
    };

// _________________________________________________________________________________

void obj::WavefrontOBJData::Clean()
    {
    // Clearing the memory.
    memset(Vertices_, 0, VERTICES_ROWS * VERTICES_COLUMNS * sizeof(double));
    memset(Faces_, 0, FACES_ROWS * FACES_COLUMNS * sizeof(short int));

    // Deallocating the memory.
    free( Vertices_ );
    free( Faces_ );

    // Resetting the pointers.
    Vertices_ = NULL;
    Faces_ = NULL;
    };

// _________________________________________________________________________________

int obj::WavefrontOBJData::FileToStructureParser()
//  0       The file has been parsed.
//  1       The file has not been opened.
//  2       The file has already been parsed.

{
// Declarations.
int done = 0;

// Process further if the file has not been parsered yet.
if ( parsed_ == false )
    {
    // Opening the file.
    errno_t err;
    err = fopen_s(&input_,"..\\Wavefront_OBJ_Creator\\Wavefront_OBJ_Creator\\result.obj","rt");

    if ( ( err ) || ( input_ == nullptr ) )
        {
        const unsigned short int ERR_BUFF = 80;
        const char * tokenstring = "The file has not been opened: obj::WavefrontOBJData::FileToStructureParser().";
        char err_buff [ ERR_BUFF ];
        memset( err_buff, 0, ERR_BUFF*sizeof(char) );
        strncpy_s( err_buff, tokenstring, strlen( tokenstring ) );
        fprintf(stderr,"%s\n%s : %s\n",tokenstring,err_buff,strerror_s( err_buff, ERR_BUFF , err ));
        perror("perror has been dispatched.\n");
        done = 1;
        };

    // Process further if the file was opened.
    if ( !done )
        {
        // Declaring auxiliary datatypes.
        char buffer [ BUFFER_SIZE ];
        char tmp [ BUFFER_SIZE ];
        memset(buffer, 0, BUFFER_SIZE * sizeof(char));
        memset(tmp, 0, BUFFER_SIZE * sizeof(char));
        unsigned short int Vrows = 0;
        unsigned short int Frows = 0;
        unsigned short int i;
        unsigned short int j;
        double tmp2;
        short int tmp3;
        unsigned short int which;
        short int number;

        // Entering the processing cycle.
        while ( !feof( input_ ) )
            {
            // Reading the entire line.
            //fscanf( input_, "%[^\n]\n", buffer );
            fgets( buffer, BUFFER_SIZE, input_ );

            // Interpreting.
            switch ( buffer[0] )
                {

                // --------------------------------------------------------------------------------------------------
                /*** A valid set of vertices has been found. ***/
                
                case 'v' :
                    {
                    tmp2 = 0.0;
                    memset(tmp, 0, BUFFER_SIZE * sizeof(char));
                    which = 0;
                    number = 0;

                    for ( i=0, j=0;  i<BUFFER_SIZE, j<(VERTICES_COLUMNS+1);  i++, j++ )
                        {
                        memset(tmp, 0, BUFFER_SIZE * sizeof(char));
                        which = 0;

                        while ( buffer[i] != ' ')
                            {
                            if ( buffer[i] == '\n' ) break;
                            tmp[which] = buffer[i];
                            which++;
                            i++;
                            };

                        number++;

                        if ( number > 1 )
                            {
                            sscanf_s( tmp, "%lf", &tmp2 );
                            Vertices_ [j-1][Vrows] = tmp2;
                            tmp2 = 0.0;
                            };

                        tmp[which] = buffer[i];
                        which++;
                        };

                    Vrows = Vrows + 1;
                    vertices_ = vertices_ + 1;
                    }
                    break;

                // --------------------------------------------------------------------------------------------------
                /*** A valid information about faces has been found. ***/

                case 'f' :
                    {
                    tmp3 = 0;
                    memset(tmp, 0, BUFFER_SIZE * sizeof(char));
                    which = 0;
                    number = 0;

                    for ( i=0, j=0;  i<BUFFER_SIZE, j<(FACES_COLUMNS+1);  i++, j++ )
                        {
                        memset(tmp, 0, BUFFER_SIZE * sizeof(char));
                        which = 0;

                        while ( buffer[i] != ' ')
                            {
                            if ( buffer[i] == '\n' ) break;
                            tmp[which] = buffer[i];
                            which++;
                            i++;
                            };

                        number++;

                        if ( number > 1 )
                            {
                            sscanf_s( tmp, "%hd", &tmp3 );
                            Faces_ [j-1][Frows] = tmp3;
                            tmp3 = 0;
                            };

                        tmp[which] = buffer[i];
                        which++;
                        };

                    Frows = Frows + 1;
                    faces_ = faces_ + 1;
                    }
                    break;

                // --------------------------------------------------------------------------------------------------

                };

            // Cleaning the buffer.
            memset( buffer, 0, BUFFER_SIZE * sizeof(char) );
            };

        // Exiting.
        fclose( input_ );
        input_ = nullptr;
        parsed_ = true;
        };
    }
else done = 2;

// Exiting.
return ( done );
};

// _________________________________________________________________________________

void obj::WavefrontOBJData::Build3DModel()
{
// Defining the perspective block.
WINDOW.left_ = -10.0;
WINDOW.right_ = 10.0;
WINDOW.bottom_ = -10.0;
WINDOW.top_ = 10.0;
WINDOW.near_ = 100.0;
WINDOW.far_ = 1.0;

// The coordinates system to the object center.
glTranslatef( 0, 0, (GLfloat)(-( WINDOW.near_ + WINDOW.far_ ) / 2.0) );

// Rotatation of the object when using keyboard.
glRotatef( WINDOW.rotate_[0], 1.0, 0.0, 0.0 );
glRotatef( WINDOW.rotate_[1], 0.0, 1.0, 0.0 );

// Impacting the scale.
glScalef( WINDOW.scale_, WINDOW.scale_, WINDOW.scale_ );

// Preprocessing.
glClearColor( 0.0, 0.0, 0.0, 1.0 );
glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
glMatrixMode( GL_MODELVIEW );
glLoadIdentity();

// Determining which model procedure to choose.
switch ( model_ )
    {

    // -----------------------------------

    case ( obj::WavefrontOBJData::PREDEFINED_PILLAR_WITH_CONTOUR ) :
        PredefinedPillar();
        break;

    // -----------------------------------

    case (obj::WavefrontOBJData::WAVEFRONT_MODEL_FROM_A_FILE ) :
        ModelFromFile();
        break;

    // -----------------------------------

    case (obj::WavefrontOBJData::WAVEFRONT_MODEL_WITH_Z_BUFFER ) :
        ModelFromFileWithZBuffer();
        break;

    // -----------------------------------

    };
};

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION DEFINITIONS ***/

void WavefrontModelInterpretator()
{
// Declarations.
int code = 0;

// I. Preparing the data structure.
fputs("Giving the prerequisites...\n",stdout);
code = obj::OBJ_data.SetStructure();

// Printing the information about operation.
switch ( code )
    {
    case 0 : fputs("The structure allocate the arrays properly.\n",stdout); break;
    case 1 : fputs("The VLA for the vertices data has not been allocated.\n",stdout); break;
    case 2 : fputs("The VLA for the faces order information has not been allocated.\n",stdout); break;
    case 3 : fputs("Both, the vertices and faces arrays has not been allocated.\n",stdout); break;
    case 4 : fputs("The allocation has been skipped.\n",stdout); break;
    };

fputs("Done.\n",stdout);

// II. Reading the data.
fputs("Parsing the Wavefront .obj file...\n",stdout);
code = obj::OBJ_data.FileToStructureParser();

// Printing the information about operation.
switch ( code )
    {
    case 0 : fputs("The file has been parsed.\n",stdout); break;
    case 1 : fputs("The file has not been opened.\n",stdout); break;
    case 2 : fputs("The file has already been parsed.\n",stdout); break;
    };

fputs("Done.\n",stdout);

if ( code == 1 )
    {
    fputs("Rendering task will be skiped.\n",stderr);
    return;
    };

// III. Building the model.
fputs("Rendering: WavefrontModelInterpretator()...\n",stdout);
obj::OBJ_data.Build3DModel();
fputs("Done.\n",stdout);

};

// _________________________________________________________________________________

void PredefinedPillar()
{
// Defining the vectors.
const GLfloat VECTOR_1 [3] = {  1.0,  0.0, -1.0 };
const GLfloat VECTOR_2 [3] = {  0.0,  0.0, -1.0 };
const GLfloat VECTOR_3 [3] = {  0.0,  0.0, -2.0 };
const GLfloat VECTOR_4 [3] = {  1.0,  0.0, -2.0 };
const GLfloat VECTOR_5 [3] = {  1.0,  5.0, -1.0 };
const GLfloat VECTOR_6 [3] = {  0.0,  5.0, -1.0 };
const GLfloat VECTOR_7 [3] = {  0.0,  5.0, -2.0 };
const GLfloat VECTOR_8 [3] = {  1.0,  5.0, -2.0 };

// Defining the model from the data.
glColor3fv( WHEAT );

// Bottom base
glBegin( GL_POLYGON );
glVertex3fv( VECTOR_1 );
glVertex3fv( VECTOR_2 );
glVertex3fv( VECTOR_3 );
glVertex3fv( VECTOR_4 );
glEnd();

// Near face
glBegin( GL_POLYGON );
glVertex3fv( VECTOR_8 );
glVertex3fv( VECTOR_7 );
glVertex3fv( VECTOR_3 );
glVertex3fv( VECTOR_4 );
glEnd();

// Left face
glBegin( GL_POLYGON );
glVertex3fv( VECTOR_7 );
glVertex3fv( VECTOR_6 );
glVertex3fv( VECTOR_2 );
glVertex3fv( VECTOR_3 );
glEnd();

// Right face
glBegin( GL_POLYGON );
glVertex3fv( VECTOR_8 );
glVertex3fv( VECTOR_5 );
glVertex3fv( VECTOR_1 );
glVertex3fv( VECTOR_4 );
glEnd();

// Far face
glBegin( GL_POLYGON );
glVertex3fv( VECTOR_5 );
glVertex3fv( VECTOR_6 );
glVertex3fv( VECTOR_2 );
glVertex3fv( VECTOR_1 );
glEnd();

// Top base
glBegin( GL_POLYGON );
glVertex3fv( VECTOR_5 );
glVertex3fv( VECTOR_6 );
glVertex3fv( VECTOR_7 );
glVertex3fv( VECTOR_8 );
glEnd();

// Lines
glColor3fv( BLACK );

glBegin( GL_LINES );
glVertex3fv( VECTOR_1 );
glVertex3fv( VECTOR_2 );
glEnd();

glBegin( GL_LINES );
glVertex3fv( VECTOR_2 );
glVertex3fv( VECTOR_3 );
glEnd();

glBegin( GL_LINES );
glVertex3fv( VECTOR_3 );
glVertex3fv( VECTOR_4 );
glEnd();

glBegin( GL_LINES );
glVertex3fv( VECTOR_4 );
glVertex3fv( VECTOR_1 );
glEnd();

glBegin( GL_LINES );
glVertex3fv( VECTOR_3 );
glVertex3fv( VECTOR_7 );
glEnd();

glBegin( GL_LINES );
glVertex3fv( VECTOR_7 );
glVertex3fv( VECTOR_8 );
glEnd();

glBegin( GL_LINES );
glVertex3fv( VECTOR_8 );
glVertex3fv( VECTOR_4 );
glEnd();

glBegin( GL_LINES );
glVertex3fv( VECTOR_8 );
glVertex3fv( VECTOR_5 );
glEnd();

glBegin( GL_LINES );
glVertex3fv( VECTOR_5 );
glVertex3fv( VECTOR_1 );
glEnd();

glBegin( GL_LINES );
glVertex3fv( VECTOR_5 );
glVertex3fv( VECTOR_6 );
glEnd();

glBegin( GL_LINES );
glVertex3fv( VECTOR_6 );
glVertex3fv( VECTOR_2 );
glEnd();

glBegin( GL_LINES );
glVertex3fv( VECTOR_6 );
glVertex3fv( VECTOR_7 );
glEnd();

// Exiting.
glFlush();
glutSwapBuffers();
};

// _________________________________________________________________________________

void ModelFromFile()
{
// Declarations.
unsigned short int i;

// Interpretating the faces order information.
for ( i=0; i<obj::OBJ_data.faces_; i++ )
    {
    // Preprocessing.
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( WINDOW.depth_ );

    // Bulding the face.
    glColor3fv( BLANCHED_ALMOND );
    glBegin( GL_POLYGON );
    glVertex3f( 
               (GLfloat)obj::OBJ_data.Vertices_[0][obj::OBJ_data.Faces_[0][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[1][obj::OBJ_data.Faces_[0][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[2][obj::OBJ_data.Faces_[0][i] - 1]
               );
    glVertex3f(
               (GLfloat)obj::OBJ_data.Vertices_[0][obj::OBJ_data.Faces_[1][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[1][obj::OBJ_data.Faces_[1][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[2][obj::OBJ_data.Faces_[1][i] - 1]
               );
    glVertex3f(
               (GLfloat)obj::OBJ_data.Vertices_[0][obj::OBJ_data.Faces_[2][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[1][obj::OBJ_data.Faces_[2][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[2][obj::OBJ_data.Faces_[2][i] - 1]
               );
    glVertex3f(
               (GLfloat)obj::OBJ_data.Vertices_[0][obj::OBJ_data.Faces_[3][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[1][obj::OBJ_data.Faces_[3][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[2][obj::OBJ_data.Faces_[3][i] - 1]
                );
    glEnd();

    // Exiting.
    glDisable( GL_DEPTH_TEST );

    // Building the countour using lines.
    glColor3fv( BLACK );

    glBegin( GL_LINES );
    glVertex3f( 
               (GLfloat)obj::OBJ_data.Vertices_[0][obj::OBJ_data.Faces_[0][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[1][obj::OBJ_data.Faces_[0][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[2][obj::OBJ_data.Faces_[0][i] - 1]
               );
    glVertex3f(
               (GLfloat)obj::OBJ_data.Vertices_[0][obj::OBJ_data.Faces_[1][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[1][obj::OBJ_data.Faces_[1][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[2][obj::OBJ_data.Faces_[1][i] - 1]
               );
    glEnd();

    glBegin( GL_LINES );
    glVertex3f(
               (GLfloat)obj::OBJ_data.Vertices_[0][obj::OBJ_data.Faces_[1][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[1][obj::OBJ_data.Faces_[1][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[2][obj::OBJ_data.Faces_[1][i] - 1]
               );
    glVertex3f(
               (GLfloat)obj::OBJ_data.Vertices_[0][obj::OBJ_data.Faces_[2][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[1][obj::OBJ_data.Faces_[2][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[2][obj::OBJ_data.Faces_[2][i] - 1]
               );
    glEnd();

    glBegin( GL_LINES );
    glVertex3f(
               (GLfloat)obj::OBJ_data.Vertices_[0][obj::OBJ_data.Faces_[2][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[1][obj::OBJ_data.Faces_[2][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[2][obj::OBJ_data.Faces_[2][i] - 1]
               );
    glVertex3f(
               (GLfloat)obj::OBJ_data.Vertices_[0][obj::OBJ_data.Faces_[3][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[1][obj::OBJ_data.Faces_[3][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[2][obj::OBJ_data.Faces_[3][i] - 1]
                );
    glEnd();

    glBegin( GL_LINES );
    glVertex3f(
               (GLfloat)obj::OBJ_data.Vertices_[0][obj::OBJ_data.Faces_[3][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[1][obj::OBJ_data.Faces_[3][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[2][obj::OBJ_data.Faces_[3][i] - 1]
                );
    glVertex3f( 
               (GLfloat)obj::OBJ_data.Vertices_[0][obj::OBJ_data.Faces_[0][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[1][obj::OBJ_data.Faces_[0][i] - 1],
               (GLfloat)obj::OBJ_data.Vertices_[2][obj::OBJ_data.Faces_[0][i] - 1]
               );
    glEnd();
    };

// Exiting.
glFlush();
glutSwapBuffers();
};

// _________________________________________________________________________________

void ModelFromFileWithZBuffer()
{
// Declarations.
unsigned short int i;

// Interpretating the faces order information.
for ( i=0; i<obj::OBJ_data.faces_; i++ )
    {
    // Preprocessing.
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( WINDOW.depth_ );

    // Bulding the face using triangulation.
    glBegin( GL_TRIANGLES );

    // (1) The first triangle.
    glColor3fv( LAWN_GREEN );
    glVertex3f( 
              (GLfloat)obj::OBJ_data.Vertices_[0][obj::OBJ_data.Faces_[0][i] - 1],
              (GLfloat)obj::OBJ_data.Vertices_[1][obj::OBJ_data.Faces_[0][i] - 1],
              (GLfloat)obj::OBJ_data.Vertices_[2][obj::OBJ_data.Faces_[0][i] - 1] 
              );
    glColor3fv( LAWN_GREEN );
    glVertex3f( 
              (GLfloat)obj::OBJ_data.Vertices_[0][obj::OBJ_data.Faces_[1][i] - 1],
              (GLfloat)obj::OBJ_data.Vertices_[1][obj::OBJ_data.Faces_[1][i] - 1],
              (GLfloat)obj::OBJ_data.Vertices_[2][obj::OBJ_data.Faces_[1][i] - 1] 
              );
    glColor3fv( GREEN );
    glVertex3f( 
              (GLfloat)obj::OBJ_data.Vertices_[0][obj::OBJ_data.Faces_[2][i] - 1],
              (GLfloat)obj::OBJ_data.Vertices_[1][obj::OBJ_data.Faces_[2][i] - 1],
              (GLfloat)obj::OBJ_data.Vertices_[2][obj::OBJ_data.Faces_[2][i] - 1] 
              );

    // (2) The second triangle.
    glColor3fv( GREEN );
    glVertex3f( 
              (GLfloat)obj::OBJ_data.Vertices_[0][obj::OBJ_data.Faces_[2][i] - 1],
              (GLfloat)obj::OBJ_data.Vertices_[1][obj::OBJ_data.Faces_[2][i] - 1],
              (GLfloat)obj::OBJ_data.Vertices_[2][obj::OBJ_data.Faces_[2][i] - 1] 
              );
    glColor3fv( LAWN_GREEN );
    glVertex3f( 
              (GLfloat)obj::OBJ_data.Vertices_[0][obj::OBJ_data.Faces_[3][i] - 1],
              (GLfloat)obj::OBJ_data.Vertices_[1][obj::OBJ_data.Faces_[3][i] - 1],
              (GLfloat)obj::OBJ_data.Vertices_[2][obj::OBJ_data.Faces_[3][i] - 1]
              );
    glColor3fv( LAWN_GREEN );
    glVertex3f( 
              (GLfloat)obj::OBJ_data.Vertices_[0][obj::OBJ_data.Faces_[0][i] - 1],
              (GLfloat)obj::OBJ_data.Vertices_[1][obj::OBJ_data.Faces_[0][i] - 1],
              (GLfloat)obj::OBJ_data.Vertices_[2][obj::OBJ_data.Faces_[0][i] - 1] 
              );

    glEnd();

    // Exiting.
    glDisable( GL_DEPTH_TEST );
    };

// Exiting.
glFlush();
glutSwapBuffers();
};

// _________________________________________________________________________________
