#pragma once

// _________________________________________________________________________________

#include "..\freeglut\include\GL\freeglut.h"
#include "ProgramAuxiliaryStructure.h"
#include "Display.h"

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION PROTOTYPES ***/

// A procedure defining the behaviour for the window resizing.
void Resize( int, int );

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION DEFINITIONS ***/

void Resize( int _width, int _height )
{
glViewport( 0, 0, _width, _height );
glMatrixMode( GL_PROJECTION );
glLoadIdentity();

switch ( WINDOW.aspect_ )
    {

    // -------------------------------------

    case ( WINDOW.JUST_DISPLAY ) :
        break;

    // -------------------------------------

    case ( WINDOW.RENDERING_MODE_FULL_WINDOW ) :
        {
        glViewport( 0, 0, _width, _height );
        }
        break;

    // -------------------------------------

    case ( WINDOW.RENDERING_MODE_1_TO_1_ASPECT_RATIO ) :
        {
        if ( _width > _height )
            {
            glViewport( ( _width - _height) / 2, 0, _height, _width );
            }
        else
        if ( _width < _height )
            {
            glViewport( 0, ( _height - _width ) / 2, _width, _height );
            }
        else
            {
            glViewport( 0, 0, _width, _height );
            };
        }
        break;

    // -------------------------------------

    case ( WINDOW.ORTHOGONAL_VIEW_FULL_WINDOW ) :
        {
        glOrtho( -2.0,  2.0, -2.0,  2.0, -2.0,  2.0 );
        }
        break;

    // -------------------------------------

    case ( WINDOW.ORTHOGONAL_VIEW_1_TO_1_ASPECT_RATIO ) :
        {
        if ( ( _width < _height ) && ( _width > 0 ) )
            {
            glOrtho( -2.0,  2.0, -2.0 * _height / _width,  2.0 * _height / _width, -2.0,  2.0 );
            }
        else
        if ( ( _width >= _height ) && ( _height > 0 ) )
            {
            glOrtho( -2.0 * _width / _height,  2.0 * _width / _height, -2.0,  2.0, -2.0,  2.0 );
            }
        else
            {
            glOrtho( -2.0,  2.0, -2.0,  2.0, -2.0,  2.0 );
            };
        }
        break;

    // -------------------------------------

    case ( WINDOW.PERSPECTIVE_VIEW_FULL_WINDOW ) :
        {
        glFrustum( -2.0,  2.0, -2.0,  2.0, -2.0,  2.0 );
        }
        break;

    // -------------------------------------

    case ( WINDOW.PERSPECTIVE_VIEW_1_TO_1_ASPECT_RATIO ) :
        {
        if ( ( _width < _height ) && ( _width > 0 ) )
            {
            glFrustum( -2.0,  2.0, -2.0 * _height / _width,  2.0 * _height / _width,  1.0,  5.0 );
            }
        else
        if ( ( _width >= _height ) && ( _height > 0 ) )
            {
            glFrustum( -2.0 * _width / _height,  2.0 * _width / _height, -2.0,  2.0,  1.0,  5.0 );
            }
        else
            {
            glFrustum( -2.0,  2.0, -2.0,  2.0,  1.0,  5.0 );
            };
        }
        break;

    // -------------------------------------

    case ( WINDOW.PERSPECTIVE_VIEW_FIELD_OF_VIEW ) :
        {
        if ( _height > 0 ) 
            {
            gluPerspective( WINDOW.fovy_, _width / (GLdouble)_height,  1.0,  5.0 );
            }
        else
            {
            gluPerspective( WINDOW.fovy_,  1.0,  1.0,  5.0 );
            };
        }
        break;

    // -------------------------------------

    case ( WINDOW.PERSPECTIVE_VIEW_MODELS ) :
        {
        if ( ( _width < _height ) && ( _width > 0 ) )
            {
            glFrustum( WINDOW.left_, WINDOW.right_, 
                       WINDOW.bottom_ * _height / _width, WINDOW.top_ * _height / _width,
                       WINDOW.near_, WINDOW.far_ );
            }
        else
        if ( ( _width >= _height ) && ( _height > 0 ) )
            {
            glFrustum( WINDOW.left_ * _width / _height, WINDOW.right_ * _width / _height,
                       WINDOW.bottom_, WINDOW.top_,
                       WINDOW.near_, WINDOW.far_ );
            }
        else
            {
            glFrustum( WINDOW.left_, WINDOW.right_,
                       WINDOW.bottom_, WINDOW.top_,
                       WINDOW.near_, WINDOW.far_ );
            };
        }
        break;

    // -------------------------------------

    case ( WINDOW.Z_BUFFER_FULL_WINDOW ) :
        {
        if ( ( _width < _height ) && ( _width > 0 ) )
            {
            glFrustum( WINDOW.left_, WINDOW.right_, 
                       WINDOW.bottom_ * _height / _width, WINDOW.top_ * _height / _width,
                       WINDOW.near_, WINDOW.far_ );
            }
        else
        if ( ( _width >= _height ) && ( _height > 0 ) )
            {
            glFrustum( WINDOW.left_ * _width / _height, WINDOW.right_ * _width / _height,
                       WINDOW.bottom_, WINDOW.top_,
                       WINDOW.near_, WINDOW.far_ );
            }
        else
            {
            glFrustum( WINDOW.left_, WINDOW.right_,
                       WINDOW.bottom_, WINDOW.top_,
                       WINDOW.near_, WINDOW.far_ );
            };
        }
        break;

    // -------------------------------------

    default :
        {
        glViewport( 0, 0, _width, _height );
        }
        break;

    // -------------------------------------

    };

Display();
};

// _________________________________________________________________________________
