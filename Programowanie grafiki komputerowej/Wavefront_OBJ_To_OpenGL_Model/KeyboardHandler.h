#pragma once

// _________________________________________________________________________________

#include "..\freeglut\include\GL\freeglut.h"
#include "ProgramAuxiliaryStructure.h"
#include "Resize.h"

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION PROTOTYPES ***/

// A procedure for the keyboard handling.
void KeyboardHandler( unsigned char, int, int );

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION DEFINITIONS ***/

void KeyboardHandler( unsigned char _key, int _x, int _y )
{
switch ( _key )
    {

    // -------------------------------------

    case 'F' :
        {
        if ( WINDOW.fovy_ < 180.0 ) 
            {
            WINDOW.fovy_ = WINDOW.fovy_ + 1;
            };
        }
        break;

    // -------------------------------------

    case 'f' :
        {
        if ( WINDOW.fovy_ > 0.0 ) 
            {
            WINDOW.fovy_ = WINDOW.fovy_ - 1;
            };
        }
        break;

    // -------------------------------------

    case '+' :
        {
        WINDOW.scale_ = WINDOW.scale_ + (GLfloat)0.1;
        }
        break;

    // -------------------------------------

    case '-' :
        {
        if ( WINDOW.scale_ > 0.1 )
            {
            WINDOW.scale_ = WINDOW.scale_ - (GLfloat)0.1;
            };
        }
        break;

    // -------------------------------------

    case 'E' :
        {
        WINDOW.eye_[0] = WINDOW.eye_[0] + 0.1;
        }
        break;

    // -------------------------------------

    case 'r' :
        {
        WINDOW.eye_[1] = WINDOW.eye_[1] - 0.1;
        }
        break;

    // -------------------------------------

    case 'e' :
        {
        WINDOW.eye_[0] = WINDOW.eye_[0] - 0.1;
        }
        break;

    // -------------------------------------

    case 'R' :
        {
        WINDOW.eye_[1] = WINDOW.eye_[1] + 0.1;
        }
        break;

    // -------------------------------------

    case 't' :
        {
        WINDOW.eye_[2] = WINDOW.eye_[2] - 0.1;
        }
        break;

    // -------------------------------------

    case 'T' :
        {
        WINDOW.eye_[2] = WINDOW.eye_[2] + 0.1;
        }
        break;

    // -------------------------------------

    };

Resize( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
};

// _________________________________________________________________________________
