#pragma once

// _________________________________________________________________________________

#include "WavefrontModelInterpretator.h"
#include "Square2D.h"
#include "CubeContour.h"
#include "GLUTObjects.h"
#include "Z-Buffer_Test.h"

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION PROTOTYPES ***/

// A procedure for displaying the graphic in the GLUT context.
void Display( void );

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION DEFINITIONS ***/

void Display()
{
switch ( WINDOW.scene_ )
    {

    // -------------------------------------

    case ( WINDOW.SCENE_1_SQUARE ) :
        Square2D();
        break;

    // -------------------------------------

    case ( WINDOW.SCENE_2_CUBE_CONTOUR ) :
        CubeContour();
        break;

    // -------------------------------------

    case ( WINDOW.SCENE_3_GLUT_OBJECTS ) :
        GLUTObjects();
        break;

    // -------------------------------------

    case ( WINDOW.SCENE_4_Z_BUFFER_TEST ) :
        Z_Buffer_Test();
        break;

    // -------------------------------------

    case ( WINDOW.SCENE_5_WAVEFRONT_MODEL ) :
        WavefrontModelInterpretator();
        break;

    // -------------------------------------

    };
};

// _________________________________________________________________________________
