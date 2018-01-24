#pragma once

// _________________________________________________________________________________

#include "..\freeglut\include\GL\freeglut.h"
#include "ProgramAuxiliaryStructure.h"
#include "Resize.h"

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION PROTOTYPES ***/

// A procedure for the handling of the keyboard function keys and mouse keys.
void SpecialKeysHandler( int, int, int );

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION DEFINITIONS ***/

void SpecialKeysHandler( int _key, int _x, int _y )
{
switch ( _key )
    {

    // -------------------------------------

    case GLUT_KEY_LEFT :
        {
        WINDOW.rotate_[1] = WINDOW.rotate_[1] - (GLfloat)1.0;
        }
        break;

    // -------------------------------------

    case GLUT_KEY_UP :
        {
        WINDOW.rotate_[0] = WINDOW.rotate_[0] - (GLfloat)1.0;
        }
        break;

    // -------------------------------------

    case GLUT_KEY_RIGHT :
        {
        WINDOW.rotate_[1] = WINDOW.rotate_[1] + (GLfloat)1.0;
        }
        break;

    // -------------------------------------

    case GLUT_KEY_DOWN :
        {
        WINDOW.rotate_[0] = WINDOW.rotate_[0] + (GLfloat)1.0;
        }
        break;

    // -------------------------------------

    };

Resize( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
};

// _________________________________________________________________________________
