#pragma once

// _________________________________________________________________________________

#include "..\freeglut\include\GL\freeglut.h"
#include "ProgramAuxiliaryStructure.h"

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION PROTOTYPES ***/

// A procedure for the handling with the mouse motion.
void MouseMotionHandler( int, int );

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION DEFINITIONS ***/

void MouseMotionHandler( int _x, int _y )
{
switch ( WINDOW.bstate_ )
    {

    // -------------------------------------

    case GLUT_DOWN :
        {
        WINDOW.translate_[0] = WINDOW.translate_[0] + (GLfloat)( 1.1 * ( WINDOW.right_ - WINDOW.left_ ) 
                                 / glutGet( GLUT_WINDOW_WIDTH ) * ( _x - WINDOW.cursor_[0]) );
        WINDOW.translate_[1] = WINDOW.translate_[1] + (GLfloat)( 1.1 * ( WINDOW.top_ - WINDOW.bottom_ ) 
                                 / glutGet( GLUT_WINDOW_HEIGHT ) * ( WINDOW.cursor_[1] - _y ) );
        glutPostRedisplay();
        }
        break;

    // -------------------------------------

    };
};

// _________________________________________________________________________________
