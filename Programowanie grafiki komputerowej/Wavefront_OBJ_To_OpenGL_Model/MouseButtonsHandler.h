#pragma once

// _________________________________________________________________________________

#include "..\freeglut\include\GL\freeglut.h"
#include "ProgramAuxiliaryStructure.h"

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION PROTOTYPES ***/

// A procedure for the handling with the mouse buttons.
void MouseButtonsHandler( int, int, int, int );

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION DEFINITIONS ***/

void MouseButtonsHandler( int _button, int _state, int _x, int _y )
{
switch ( _button )
    {

    // -------------------------------------

    case GLUT_LEFT_BUTTON :
        {
        /*** Storing the cursor state and position ***/
        WINDOW.bstate_ = _state;

        if ( _state == GLUT_DOWN )
            {
            WINDOW.cursor_[0] = _x;
            WINDOW.cursor_[1] = _y;
            };
        }
        break;

    // -------------------------------------

    };
};

// _________________________________________________________________________________
