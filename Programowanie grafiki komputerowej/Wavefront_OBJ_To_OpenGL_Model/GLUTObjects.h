#pragma once

// _________________________________________________________________________________

#include "..\freeglut\include\GL\freeglut.h"
#include "ProgramAuxiliaryStructure.h"

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION PROTOTYPES ***/

// A procedure for rendering the basics GLUT library object in a wire mode.
void GLUTObjects( void );

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION DEFINITIONS ***/

void GLUTObjects()
{
glClearColor( 1.0, 1.0, 1.0, 1.0 );
glClear( GL_COLOR_BUFFER_BIT );
glMatrixMode( GL_MODELVIEW );
glLoadIdentity();

// The coordinates system to the object center.
glTranslatef( 0, 0, (GLfloat)(-( WINDOW.near_ + WINDOW.far_ ) / 2.0) );

// Moving the object when moving the mouse.
glTranslatef( WINDOW.translate_[0], WINDOW.translate_[1], 0.0 );

// Impacting the scale.
glScalef( WINDOW.scale_, WINDOW.scale_, WINDOW.scale_ );

// Rotatation of the object when using keyboard.
glRotatef( WINDOW.rotate_[0], 1.0, 0.0, 0.0 );
glRotatef( WINDOW.rotate_[1], 0.0, 1.0, 0.0 );

// The edges color of the object.
glColor3f( 0.0, 0.0, 1.0 );

switch ( WINDOW.object_ )
    {

    // -------------------------------------

    case ( WINDOW.OBJECT_WIRE_SPHERE ) :
        {
        glutWireSphere( 1.0, 20, 10 );
        }
        break;

    // -------------------------------------

    case ( WINDOW.OBJECT_WIRE_CONE ) :
        {
        glutWireCone( 1.0, 2.0, 20, 10 );
        }
        break;

    // -------------------------------------

    case ( WINDOW.OBJECT_WIRE_CUBE ) :
        {
        glutWireCube( 1.0 );
        }
        break;

    // -------------------------------------

    case ( WINDOW.OBJECT_WIRE_TORUS ) :
        {
        glutWireTorus( 0.2, 1.0, 10, 20 );
        }
        break;

    // -------------------------------------

    case ( WINDOW.OBJECT_WIRE_DODECAHEDRON ) :
        {
        glutWireDodecahedron();
        }
        break;

    // -------------------------------------

    case ( WINDOW.OBJECT_WIRE_TEAPOT ) :
        {
        glutWireTeapot( 1.0 );
        }
        break;

    // -------------------------------------

    case ( WINDOW.OBJECT_WIRE_OCTAHEDRON ) :
        {
        glutWireOctahedron();
        }
        break;

    // -------------------------------------

    case ( WINDOW.OBJECT_WIRE_TETRAHEDRON ) :
        {
        glutWireTetrahedron();
        }
        break;

    // -------------------------------------

    case ( WINDOW.OBJECT_WIRE_ICOSAHEDRON ) :
        {
        glutWireIcosahedron();
        }
        break;

    // -------------------------------------

    };

glFlush();
glutSwapBuffers();
};

// _________________________________________________________________________________
