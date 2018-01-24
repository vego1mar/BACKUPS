#pragma once

// _________________________________________________________________________________

#include "..\freeglut\include\GL\freeglut.h"
#include "ProgramAuxiliaryStructure.h"
#include "Resize.h"
#include "Display.h"
#include "WavefrontModelInterpretator.h"

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION PROTOTYPES ***/

// A procedure for the pop-up menu for the GLUT chain.
void MenuHandler( int );

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION DEFINITIONS ***/

void MenuHandler ( int _code )
{
switch ( _code )
    {

    // -------------------------------------

    case ( WINDOW.PROGRAM_EXIT ) :
        {
        fputs("The heap is cleaning now...\n",stdout);
        obj::OBJ_data.Clean();
        fputs("Done.\n",stdout);
        exit( 0 );
        }
        break;

    // -------------------------------------

    case ( WINDOW.RENDERING_MODE_FULL_WINDOW ) :
        {
        WINDOW.aspect_ = WINDOW.RENDERING_MODE_FULL_WINDOW;
        Resize( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
        }
        break;

    // -------------------------------------

    case ( WINDOW.RENDERING_MODE_1_TO_1_ASPECT_RATIO ) :
        {
        WINDOW.aspect_ = WINDOW.RENDERING_MODE_1_TO_1_ASPECT_RATIO;
        Resize( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
        }
        break;

    // -------------------------------------

    case ( WINDOW.ORTHOGONAL_VIEW_FULL_WINDOW ) :
        {
        WINDOW.aspect_ = WINDOW.ORTHOGONAL_VIEW_FULL_WINDOW;
        Resize( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
        }
        break;

    // -------------------------------------

    case ( WINDOW.ORTHOGONAL_VIEW_1_TO_1_ASPECT_RATIO ) :
        {
        WINDOW.aspect_ = WINDOW.ORTHOGONAL_VIEW_1_TO_1_ASPECT_RATIO;
        Resize( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
        }
        break;

    // -------------------------------------

    case ( WINDOW.PERSPECTIVE_VIEW_FULL_WINDOW ) :
        {
        WINDOW.aspect_ = WINDOW.PERSPECTIVE_VIEW_FULL_WINDOW;
        Resize( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
        }
        break;

    // -------------------------------------

    case ( WINDOW.PERSPECTIVE_VIEW_1_TO_1_ASPECT_RATIO ) :
        {
        WINDOW.aspect_ = WINDOW.PERSPECTIVE_VIEW_1_TO_1_ASPECT_RATIO;
        Resize( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
        }
        break;

    // -------------------------------------

    case ( WINDOW.PERSPECTIVE_VIEW_FIELD_OF_VIEW ) :
        {
        WINDOW.aspect_ = WINDOW.PERSPECTIVE_VIEW_FIELD_OF_VIEW;
        Resize( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
        }
        break;

    // -------------------------------------

    case ( WINDOW.PERSPECTIVE_VIEW_MODELS ) :
        {
        WINDOW.aspect_ = WINDOW.PERSPECTIVE_VIEW_MODELS;
        Resize( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
        }
        break;

    // -------------------------------------

    case ( WINDOW.OBJECT_WIRE_SPHERE ) :
        {
        WINDOW.object_ = WINDOW.OBJECT_WIRE_SPHERE;
        Display();
        }
        break;

    // -------------------------------------

    case ( WINDOW.OBJECT_WIRE_CONE ) :
        {
        WINDOW.object_ = WINDOW.OBJECT_WIRE_CONE;
        Display();
        }
        break;

    // -------------------------------------

    case ( WINDOW.OBJECT_WIRE_CUBE ) :
        {
        WINDOW.object_ = WINDOW.OBJECT_WIRE_CUBE;
        Display();
        }
        break;

    // -------------------------------------

    case ( WINDOW.OBJECT_WIRE_TORUS ) :
        {
        WINDOW.object_ = WINDOW.OBJECT_WIRE_TORUS;
        Display();
        }
        break;

    // -------------------------------------

    case ( WINDOW.OBJECT_WIRE_DODECAHEDRON ) :
        {
        WINDOW.object_ = WINDOW.OBJECT_WIRE_DODECAHEDRON;
        Display();
        }
        break;

    // -------------------------------------

    case ( WINDOW.OBJECT_WIRE_TEAPOT ) :
        {
        WINDOW.object_ = WINDOW.OBJECT_WIRE_TEAPOT;
        Display();
        }
        break;

    // -------------------------------------

    case ( WINDOW.OBJECT_WIRE_OCTAHEDRON ) :
        {
        WINDOW.object_ = WINDOW.OBJECT_WIRE_OCTAHEDRON;
        Display();
        }
        break;

    // -------------------------------------

    case ( WINDOW.OBJECT_WIRE_TETRAHEDRON ) :
        {
        WINDOW.object_ = WINDOW.OBJECT_WIRE_TETRAHEDRON;
        Display();
        }
        break;

    // -------------------------------------

    case ( WINDOW.OBJECT_WIRE_ICOSAHEDRON ) :
        {
        WINDOW.object_ = WINDOW.OBJECT_WIRE_ICOSAHEDRON;
        Display();
        }
        break;

    // -------------------------------------

    case ( WINDOW.Z_BUFFER_FULL_WINDOW ) :
        {
        WINDOW.aspect_ = WINDOW.Z_BUFFER_FULL_WINDOW;
        Resize( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
        }
        break;

    // -------------------------------------

    case GL_NEVER :
        {
        WINDOW.depth_ = GL_NEVER;
        Display();
        }
        break;

    // -------------------------------------

    case GL_LESS :
        {
        WINDOW.depth_ = GL_LESS;
        Display();
        }
        break;

    // -------------------------------------

    case GL_EQUAL :
        {
        WINDOW.depth_ = GL_EQUAL;
        Display();
        }
        break;

    // -------------------------------------

    case GL_LEQUAL :
        {
        WINDOW.depth_ = GL_LEQUAL;
        Display();
        }
        break;

    // -------------------------------------

    case GL_GREATER :
        {
        WINDOW.depth_ = GL_GREATER;
        Display();
        }
        break;

    // -------------------------------------

    case GL_NOTEQUAL :
        {
        WINDOW.depth_ = GL_NOTEQUAL;
        Display();
        }
        break;

    // -------------------------------------

    case GL_GEQUAL :
        {
        WINDOW.depth_ = GL_GEQUAL;
        Display();
        }
        break;

    // -------------------------------------

    case GL_ALWAYS :
        {
        WINDOW.depth_ = GL_ALWAYS;
        Display();
        }
        break;

    // -------------------------------------

    case ( WINDOW.SCENE_1_SQUARE ) :
        {
        WINDOW.scene_ = WINDOW.SCENE_1_SQUARE;
        WINDOW.aspect_ = WINDOW.PERSPECTIVE_VIEW_FIELD_OF_VIEW;
        Resize( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
        }
        break;

    // -------------------------------------

    case ( WINDOW.SCENE_2_CUBE_CONTOUR ) :
        {
        WINDOW.scene_ = WINDOW.SCENE_2_CUBE_CONTOUR;
        WINDOW.aspect_ = WINDOW.PERSPECTIVE_VIEW_FIELD_OF_VIEW;
        Resize( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
        }
        break;

    // -------------------------------------

    case ( WINDOW.SCENE_3_GLUT_OBJECTS ) :
        {
        WINDOW.scene_ = WINDOW.SCENE_3_GLUT_OBJECTS;
        WINDOW.aspect_ = WINDOW.PERSPECTIVE_VIEW_MODELS;
        Resize( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
        }
        break;

    // -------------------------------------

    case ( WINDOW.SCENE_4_Z_BUFFER_TEST ) :
        {
        WINDOW.scene_ = WINDOW.SCENE_4_Z_BUFFER_TEST;
        WINDOW.aspect_ = WINDOW.PERSPECTIVE_VIEW_MODELS;
        Resize( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
        }
        break;

    // -------------------------------------

    case ( WINDOW.SCENE_5_WAVEFRONT_MODEL ) :
        {
        WINDOW.scene_ = WINDOW.SCENE_5_WAVEFRONT_MODEL;
        WINDOW.aspect_ = WINDOW.PERSPECTIVE_VIEW_MODELS;
        Resize( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
        }
        break;

    // -------------------------------------

    case ( obj::WavefrontOBJData::PREDEFINED_PILLAR_WITH_CONTOUR ) :
        {
        obj::OBJ_data.model_ = obj::WavefrontOBJData::PREDEFINED_PILLAR_WITH_CONTOUR;
        Display();
        }
        break;

    // -------------------------------------

    case ( obj::WavefrontOBJData::WAVEFRONT_MODEL_FROM_A_FILE ) :
        {
        obj::OBJ_data.model_ = obj::WavefrontOBJData::WAVEFRONT_MODEL_FROM_A_FILE;
        Display();
        }
        break;

    // -------------------------------------

    case ( obj::WavefrontOBJData::WAVEFRONT_MODEL_WITH_Z_BUFFER ) :
        {
        obj::OBJ_data.model_ = obj::WavefrontOBJData::WAVEFRONT_MODEL_WITH_Z_BUFFER;
        Display();
        }
        break;

    // -------------------------------------

    };
};

// _________________________________________________________________________________
