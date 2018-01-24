////////////////////////////////////////////////////////////////////////////////////
/*

    Wavefront OBJ Model Viewer
    using OpenGL 1.1 and freeGLUT 3.0.0

    V 2016

    The program can parse, in the very basic manner, the .obj file of the
    Wavefront file format and visualize it using OpenGL 1.1.

*/
////////////////////////////////////////////////////////////////////////////////////

/*
------------------------------------------------------------------------------------

 ----- CONSTRAINTS -----
 (1) The program read the file "result.obj" from the catalogue of the project
     'Wavefront_OBJ_Creator' that is related with this solution.
 (2) The number of read lines is not limited, although there is no security at
     this point either. The sizes of the VLA arrays, where the parsed data is
     stored, are defined in 'WavefrontModelInterpretator.h' file as an
     enumerator constants, that are VERTICES_ROWS and FACES_ROWS. Also, it is
     important to note that the number of characters per each line in the
     entire file should be equal of greater than BUFFER_SIZE.
 (3) The program print some information during runtime to the standard input 
     device.
 (4) The WINDOW and obj::OBJ_data structures are declared in the global scope.
 (5) Currently only the 'f' (faces) group data are visualized (and interpreted
     as quadrangles).

------------------------------------------------------------------------------------
*/


#include <Windows.h>
#include <cstdlib>

// _________________________________________________________________________________

/*** OPENGL LIBRARIES ***/
#include <gl/GL.h>
#include <gl/GLU.h>

/*** GLUT LIBRARY ***/
#include "..\freeglut\include\GL\glut.h"

// _________________________________________________________________________________

/*** GLUT PROGRAM HEADERS ***/
#include "ProgramAuxiliaryStructure.h"
#include "MenuHandler.h"
#include "Resize.h"
#include "Display.h"
#include "MenuEntriesDefiner.h"
#include "KeyboardHandler.h"
#include "SpecialKeysHandler.h"
#include "MouseButtonsHandler.h"
#include "MouseMotionHandler.h"
#include "GLUTInitialization.h"

/*** SCENES DEFINITIONS ***/
#include "Square2D.h"
#include "CubeContour.h"
#include "GLUTObjects.h"
#include "Z-Buffer_Test.h"

/*** WAVEFRONT OBJ TASK HEADERS ***/
#include "WavefrontModelInterpretator.h"

// _________________________________________________________________________________

/*** SYSTEM RESOURCES ***/
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

// _________________________________________________________________________________

/*** ADDITIONAL DEPENDENCIES ***
$(SolutionDir)\freeglut\lib\freeglut.lib
*/

/*** DYNAMIC LINKING ***
$(SolutionDir)\freeglut\bin\freeglut.dll
*/

// _________________________________________________________________________________

int main( int argc, char * argv [] )
{
GLUT_Initialization( &argc, argv );

return ( 0 );
};

// _________________________________________________________________________________
