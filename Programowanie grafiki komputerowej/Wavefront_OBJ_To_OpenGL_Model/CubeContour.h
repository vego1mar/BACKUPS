#pragma once

// _________________________________________________________________________________

#include "..\freeglut\include\GL\freeglut.h"
#include "ProgramAuxiliaryStructure.h"

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION PROTOTYPES ***/

// A procedure for rendering the cube's contour.
void CubeContour( void );

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION DEFINITIONS ***/

void CubeContour()
{
glClearColor( 1.0, 1.0, 1.0, 1.0 );
glClear( GL_COLOR_BUFFER_BIT );
glMatrixMode( GL_MODELVIEW );
glLoadIdentity();
gluLookAt( WINDOW.eye_[0], WINDOW.eye_[1], WINDOW.eye_[2],
           WINDOW.center_[0], WINDOW.center_[1], WINDOW.center_[2],
           0.0, 1.0, 0.0
         );
glTranslatef( 0.0, 0.0, -3.0 );
glColor3f( 0.0, 0.0, 0.0 );

glBegin( GL_LINES );
glVertex3f(  1.0,  1.0,  1.0 );
glVertex3f(  1.0, -1.0,  1.0 );
glVertex3f(  1.0, -1.0,  1.0 );
glVertex3f(  1.0, -1.0, -1.0 );
glVertex3f(  1.0, -1.0, -1.0 );
glVertex3f(  1.0,  1.0, -1.0 );
glVertex3f(  1.0,  1.0, -1.0 );
glVertex3f(  1.0,  1.0,  1.0 );
glVertex3f( -1.0,  1.0,  1.0 );
glVertex3f( -1.0, -1.0,  1.0 );
glVertex3f( -1.0, -1.0,  1.0 );
glVertex3f( -1.0, -1.0, -1.0 );
glVertex3f( -1.0, -1.0, -1.0 );
glVertex3f( -1.0,  1.0, -1.0 );
glVertex3f( -1.0,  1.0, -1.0 );
glVertex3f( -1.0,  1.0,  1.0 );
glVertex3f(  1.0,  1.0,  1.0 );
glVertex3f( -1.0,  1.0,  1.0 );
glVertex3f(  1.0, -1.0,  1.0 );
glVertex3f( -1.0, -1.0,  1.0 );
glVertex3f(  1.0, -1.0, -1.0 );
glVertex3f( -1.0, -1.0, -1.0 ); 
glVertex3f(  1.0,  1.0, -1.0 );
glVertex3f( -1.0,  1.0, -1.0 );
glEnd();

glFlush();
glutSwapBuffers();
};

// _________________________________________________________________________________
