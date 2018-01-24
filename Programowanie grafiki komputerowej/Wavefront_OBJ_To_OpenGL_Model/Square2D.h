#pragma once

// _________________________________________________________________________________

#include "..\freeglut\include\GL\freeglut.h"

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION PROTOTYPES ***/

// A procedure for rendering the square.
void Square2D( void );

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION DEFINITIONS ***/

void Square2D()
{
// Defining the perspective block.
WINDOW.left_ = -10.0;
WINDOW.right_ = 10.0;
WINDOW.bottom_ = -10.0;
WINDOW.top_ = 10.0;
WINDOW.near_ = 50.0;
WINDOW.far_ = 70.0;

// Preprocessing.
glClearColor( 1.0, 1.0, 1.0, 1.0 );
glClear( GL_COLOR_BUFFER_BIT );
glColor3f( 0.0, 1.0, 0.0 );

// Square definition.
glBegin( GL_POLYGON );
glVertex3f(  0.0,  0.0,  0.0 );
glVertex3f(  0.0,  1.0,  0.0 );
glVertex3f( -1.0,  1.0,  0.0 );
glVertex3f( -1.0,  0.0,  0.0 );
glEnd();

// Exiting.
glFlush();
glutSwapBuffers();
};

// _________________________________________________________________________________
