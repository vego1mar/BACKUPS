#pragma once

// _________________________________________________________________________________

#include "..\freeglut\include\GL\freeglut.h"
#include "ProgramAuxiliaryStructure.h"
#include "Display.h"
#include "Resize.h"
#include "KeyboardHandler.h"
#include "SpecialKeysHandler.h"
#include "MouseButtonsHandler.h"
#include "MouseMotionHandler.h"
#include "MenuEntriesDefiner.h"

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION PROTOTYPES ***/

// Intializing chain for the GLUT graphical handlers.
void GLUT_Initialization( int * _argc, char ** _agrv );

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION DEFINITIONS ***/

void GLUT_Initialization( int * _argc, char ** _argv )
{
FulfillAuxiliaryStructure();
glutInit( _argc, _argv );
glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
glutInitWindowSize( 600, 600 );
glutCreateWindow( "OpenGL Viewer" );
glutDisplayFunc( Display );
glutReshapeFunc( Resize );
glutKeyboardFunc( KeyboardHandler );
glutSpecialFunc( SpecialKeysHandler );
glutMouseFunc( MouseButtonsHandler );
glutMotionFunc( MouseMotionHandler );
MenuEntriesDefiner();
glutAttachMenu ( GLUT_RIGHT_BUTTON );
glutMainLoop();
};

// _________________________________________________________________________________
