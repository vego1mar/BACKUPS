#pragma once

// _________________________________________________________________________________

#include "..\freeglut\include\GL\freeglut.h"
#include "Colors.h"

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION PROTOTYPES ***/

// A procedure drawing a cube with hidden edges with color shading.
void Z_Buffer_Test( void );

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION DEFINITIONS ***/

void Z_Buffer_Test()
{
// Defining the perspective block.
WINDOW.left_ = -2.0;
WINDOW.right_ = 2.0;
WINDOW.bottom_ = -2.0;
WINDOW.top_ = 2.0;
WINDOW.near_ = 3.0;
WINDOW.far_ = 7.0;

// Preprocessing.
glClearColor( 1.0, 1.0, 1.0, 1.0 );
glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
glMatrixMode( GL_MODELVIEW );
glLoadIdentity();
glTranslatef( 0.0, 0.0, (GLfloat)(-( WINDOW.near_ + WINDOW.far_ ) / 2.0) );
glRotatef( WINDOW.rotate_[0], 1.0, 0.0, 0.0 );
glRotatef( WINDOW.rotate_[1], 0.0, 1.0, 0.0 );
glScalef( (GLfloat)1.15, (GLfloat)1.15, (GLfloat)1.15 );
glEnable( GL_DEPTH_TEST );
glDepthFunc( WINDOW.depth_ );

// Cube definition.
glBegin( GL_TRIANGLES );
glColor3fv( RED );
glVertex3f( -1.0, -1.0,  1.0 );
glColor3fv( YELLOW );
glVertex3f(  1.0, -1.0,  1.0 );
glColor3fv( WHITE );
glVertex3f(  1.0,  1.0,  1.0 );
glColor3fv( RED );
glVertex3f( -1.0, -1.0,  1.0 );
glColor3fv( WHITE );
glVertex3f(  1.0,  1.0,  1.0 );
glColor3fv( MAGENTA );
glVertex3f( -1.0,  1.0,  1.0 );
glColor3fv( MAGENTA );
glVertex3f( -1.0,  1.0,  1.0 );
glColor3fv( WHITE );
glVertex3f(  1.0,  1.0,  1.0 );
glColor3fv( BLUE );
glVertex3f( -1.0,  1.0, -1.0 );
glColor3fv( BLUE );
glVertex3f( -1.0,  1.0, -1.0 );
glColor3fv( WHITE );
glVertex3f(  1.0,  1.0,  1.0 );
glColor3fv( CYAN );
glVertex3f(  1.0,  1.0, -1.0 );
glColor3fv( CYAN );
glVertex3f(  1.0,  1.0, -1.0 );
glColor3fv( WHITE );
glVertex3f(  1.0,  1.0,  1.0 );
glColor3fv( YELLOW );
glVertex3f(  1.0, -1.0,  1.0 );
glColor3fv( CYAN );
glVertex3f(  1.0,  1.0, -1.0 );
glColor3fv( YELLOW );
glVertex3f(  1.0, -1.0,  1.0 );
glColor3fv( LIME );
glVertex3f(  1.0, -1.0, -1.0 );
glColor3fv( LIME );
glVertex3f(  1.0, -1.0, -1.0 );
glColor3fv( YELLOW );
glVertex3f(  1.0, -1.0,  1.0 );
glColor3fv( BLACK );
glVertex3f( -1.0, -1.0, -1.0 );
glColor3fv( BLACK );
glVertex3f( -1.0, -1.0, -1.0 );
glColor3fv( YELLOW );
glVertex3f(  1.0, -1.0,  1.0 );
glColor3fv( RED );
glVertex3f( -1.0, -1.0,  1.0 );
glColor3fv( BLACK );
glVertex3f( -1.0, -1.0, -1.0 );
glColor3fv( RED );
glVertex3f( -1.0, -1.0,  1.0 );
glColor3fv( BLUE );
glVertex3f( -1.0,  1.0, -1.0 );
glColor3fv( BLUE );
glVertex3f( -1.0,  1.0, -1.0 );
glColor3fv( RED );
glVertex3f( -1.0, -1.0,  1.0 );
glColor3fv( MAGENTA );
glVertex3f( -1.0,  1.0,  1.0 );
glColor3fv( BLACK );
glVertex3f( -1.0, -1.0, -1.0 );
glColor3fv( BLUE );
glVertex3f( -1.0,  1.0, -1.0 );
glColor3fv( CYAN );
glVertex3f(  1.0,  1.0, -1.0 );
glColor3fv( LIME );
glVertex3f(  1.0, -1.0, -1.0 );
glColor3fv( BLACK );
glVertex3f( -1.0, -1.0, -1.0 );
glColor3fv( CYAN );
glVertex3f(  1.0,  1.0, -1.0 );
glEnd();

// Exiting.
glFlush();
glutSwapBuffers();
glDisable ( GL_DEPTH_TEST );
};

// _________________________________________________________________________________
