#pragma once

// _________________________________________________________________________________

#include "..\freeglut\include\GL\freeglut.h"
#include "ProgramAuxiliaryStructure.h"
#include "MenuHandler.h"

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION PROTOTYPES ***/

// A procedure for defining the entries on the menu list.
void MenuEntriesDefiner( void );

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION DEFINITIONS ***/

void MenuEntriesDefiner()
{
// Declarations.
int RenderingScope;
int OrthogonalProjections;
int PerspectiveProjections;
int GLUTBasicModels;
int ZBufferTest;
int ScenesSwitcher;
int Keys;
int WavefrontScene;

// 'RenderingScope' submenu
RenderingScope = glutCreateMenu( MenuHandler );
glutAddMenuEntry( "Rendering scope: entire window", WINDOW.RENDERING_MODE_FULL_WINDOW );
glutAddMenuEntry( "Rendering scope: 1:1 aspect ratio", WINDOW.RENDERING_MODE_1_TO_1_ASPECT_RATIO );

// 'OrthogonalProjections' submenu
OrthogonalProjections = glutCreateMenu( MenuHandler );
glutAddMenuEntry( "Entire window", WINDOW.ORTHOGONAL_VIEW_FULL_WINDOW );
glutAddMenuEntry( "1:1 aspect ratio", WINDOW.ORTHOGONAL_VIEW_1_TO_1_ASPECT_RATIO );

// 'PerspectiveProjections' submenu
PerspectiveProjections = glutCreateMenu( MenuHandler );
glutAddMenuEntry( "Entire window", WINDOW.PERSPECTIVE_VIEW_FULL_WINDOW );
glutAddMenuEntry( "1:1 aspect ratio", WINDOW.PERSPECTIVE_VIEW_1_TO_1_ASPECT_RATIO );
glutAddMenuEntry( "Field of view", WINDOW.PERSPECTIVE_VIEW_FIELD_OF_VIEW );
glutAddMenuEntry( "Standard", WINDOW.PERSPECTIVE_VIEW_MODELS );

// 'GLUTBasicModels' submenu
GLUTBasicModels = glutCreateMenu( MenuHandler );
glutAddMenuEntry( "Cone (wired)", WINDOW.OBJECT_WIRE_CONE );
glutAddMenuEntry( "Cube (wired)", WINDOW.OBJECT_WIRE_CUBE );
glutAddMenuEntry( "Torus (wired)", WINDOW.OBJECT_WIRE_TORUS );
glutAddMenuEntry( "Dodecahedron (wired)", WINDOW.OBJECT_WIRE_DODECAHEDRON );
glutAddMenuEntry( "Teapot (wired)", WINDOW.OBJECT_WIRE_TEAPOT );
glutAddMenuEntry( "Octahedron (wired)", WINDOW.OBJECT_WIRE_OCTAHEDRON );
glutAddMenuEntry( "Tetrahedron (wired)", WINDOW.OBJECT_WIRE_TETRAHEDRON );
glutAddMenuEntry( "Icosahedron (wired)", WINDOW.OBJECT_WIRE_ICOSAHEDRON );

// 'ZBufferTest' submenu
ZBufferTest = glutCreateMenu( MenuHandler );
glutAddMenuEntry( "GL_NEVER", GL_NEVER );
glutAddMenuEntry( "GL_LESS", GL_LESS );
glutAddMenuEntry( "GL_EQUAL", GL_EQUAL );
glutAddMenuEntry( "GL_LEQUAL", GL_LEQUAL );
glutAddMenuEntry( "GL_GREATER", GL_GREATER );
glutAddMenuEntry( "GL_NOTEQUAL", GL_NOTEQUAL );
glutAddMenuEntry( "GL_GEQUAL", GL_GEQUAL );
glutAddMenuEntry( "GL_ALWAYS", GL_ALWAYS );

// 'ScenesSwitcher' submenu
ScenesSwitcher = glutCreateMenu( MenuHandler );
glutAddMenuEntry( "SCENE_1_SQUARE", WINDOW.SCENE_1_SQUARE );
glutAddMenuEntry( "SCENE_2_CUBE_CONTOUR", WINDOW.SCENE_2_CUBE_CONTOUR );
glutAddMenuEntry( "SCENE_3_GLUT_OBJECTS", WINDOW.SCENE_3_GLUT_OBJECTS );
glutAddMenuEntry( "SCENE_4_Z_BUFFER_TEST", WINDOW.SCENE_4_Z_BUFFER_TEST );
glutAddMenuEntry( "SCENE_5_WAVEFRONT_MODEL", WINDOW.SCENE_5_WAVEFRONT_MODEL );

// 'WavefrontScene' submenu
WavefrontScene = glutCreateMenu( MenuHandler );
glutAddMenuEntry( "PREDEFINED_PILLAR_WITH_CONTOUR", obj::OBJ_data.PREDEFINED_PILLAR_WITH_CONTOUR );
glutAddMenuEntry( "WAVEFRONT_MODEL_FROM_A_FILE", obj::OBJ_data.WAVEFRONT_MODEL_FROM_A_FILE );
glutAddMenuEntry( "WAVEFRONT_MODEL_WITH_Z_BUFFER", obj::OBJ_data.WAVEFRONT_MODEL_WITH_Z_BUFFER );

// 'Keys' submenu
Keys = glutCreateMenu( MenuHandler );
glutAddMenuEntry( "F     |  Field of view + 1", -1 );
glutAddMenuEntry( "f     |  Field of view - 1", -1 );
glutAddMenuEntry( "E     |  OX observer position + 0.1", -1 );
glutAddMenuEntry( "e     |  OX observer position - 0.1", -1 );
glutAddMenuEntry( "R     |  OY observer position + 0.1", -1 );
glutAddMenuEntry( "r     |  OY observer position - 0.1", -1 );
glutAddMenuEntry( "T     |  OZ observer position + 0.1", -1 );
glutAddMenuEntry( "T     |  OZ observer position - 0.1", -1 );
glutAddMenuEntry( "+     |  Scale + 0.1", -1 );
glutAddMenuEntry( "-     |  Scale - 0.1", -1 );
glutAddMenuEntry( "LEFT  |  OY rotation - 1.0", -1 );
glutAddMenuEntry( "UP    |  OX rotation - 1.0", -1 );
glutAddMenuEntry( "RIGHT |  OY rotation + 1.0", -1 );
glutAddMenuEntry( "DOWN  |  OX rotation + 1.0", -1 );

// The main menu
glutCreateMenu( MenuHandler );
glutAddMenuEntry( "Close the program", WINDOW.PROGRAM_EXIT );
glutAddSubMenu( "Rendering scope", RenderingScope );
glutAddSubMenu( "Orthogonal projections", OrthogonalProjections );
glutAddSubMenu( "Perspective projections", PerspectiveProjections );
glutAddSubMenu( "GLUT Basic Models", GLUTBasicModels );
glutAddSubMenu( "Z-Buffer tests", ZBufferTest );
glutAddSubMenu( "Scene", ScenesSwitcher );
glutAddSubMenu( "Keymap", Keys );
glutAddSubMenu( "Wavefront scene", WavefrontScene );
};

// _________________________________________________________________________________
