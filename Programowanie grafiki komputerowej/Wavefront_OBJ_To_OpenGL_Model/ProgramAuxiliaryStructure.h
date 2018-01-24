#pragma once

// _________________________________________________________________________________

#include <gl\GL.h>
#include "..\freeglut\include\GL\freeglut.h"

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION PROTOTYPES ***/

// A procedure for filling the auxiliary structure at start.
void FulfillAuxiliaryStructure( void );

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** DATATYPES DEFINITIONS ***/

struct WindowAuxiliaryData
    {
    
    // An enumerator for constant values used further.
    enum constants1_
        {
        PROGRAM_EXIT = 0,
        RENDERING_MODE_FULL_WINDOW = 1,
        RENDERING_MODE_1_TO_1_ASPECT_RATIO = 2,
        ORTHOGONAL_VIEW_FULL_WINDOW = 3,
        ORTHOGONAL_VIEW_1_TO_1_ASPECT_RATIO = 4,
        PERSPECTIVE_VIEW_FULL_WINDOW = 5,
        PERSPECTIVE_VIEW_1_TO_1_ASPECT_RATIO = 6,
        PERSPECTIVE_VIEW_FIELD_OF_VIEW = 7,
        OBJECT_WIRE_SPHERE = 8,
        OBJECT_WIRE_CONE = 9,
        OBJECT_WIRE_CUBE = 10,
        OBJECT_WIRE_TORUS = 11,
        OBJECT_WIRE_DODECAHEDRON = 12,
        OBJECT_WIRE_TEAPOT = 13,
        OBJECT_WIRE_OCTAHEDRON = 14,
        OBJECT_WIRE_TETRAHEDRON = 15,
        OBJECT_WIRE_ICOSAHEDRON = 16,
        PERSPECTIVE_VIEW_MODELS = 17,
        Z_BUFFER_FULL_WINDOW = GL_ALWAYS + 100,
        JUST_DISPLAY = 18
        };

    // An enumerator for the data structures boundaries.
    enum constants2_
        {
        EYE = (unsigned short int)(3),
        CENTER = (unsigned short int)(3),
        CURSOR = (unsigned short int)(2),
        ROTATE = (unsigned short int)(2),
        TRANSLATE = (unsigned short int)(2)
        };

    // An enumerator for scenes distinction purposes.
    enum constants3_
        {
        SCENE_1_SQUARE = (unsigned short int)(1001),
        SCENE_2_CUBE_CONTOUR = (unsigned short int)(1002),
        SCENE_3_GLUT_OBJECTS = (unsigned short int)(1003),
        SCENE_4_Z_BUFFER_TEST = (unsigned short int)(1004),
        SCENE_5_WAVEFRONT_MODEL = (unsigned short int)(1005)
        };

    // The enumerator value of the aspect ratio constant.
    short int aspect_ ;

    // The angle of the field of the view.
    GLdouble fovy_ ;

    // The coordinates <x,y,z> of the observer's position.
    GLdouble eye_ [ EYE ];

    // The coordinates <x,y,z> of the point that the observer is looking at.
    GLdouble center_ [ CENTER ];

    // The actual mouse button state.
    int bstate_;

    // The mouse cursor coordinates of <x,y>.
    int cursor_ [ CURSOR ];

    // The number of the predefined object.
    short int object_ ;

    // The parameters of the projection block.
    GLdouble left_ ;
    GLdouble right_ ;
    GLdouble bottom_ ;
    GLdouble top_ ;
    GLdouble near_ ;
    GLdouble far_ ;

    // The scaling factor.
    GLfloat scale_ ;

    // The rotation angles of <alfa,beta>.
    GLfloat rotate_ [ ROTATE ];

    // The translation coordinates of <x,y>.
    GLfloat translate_ [ TRANSLATE ];

    // The type of the Z-buffer test mode.
    GLenum depth_;

    // An identificator of the scene.
    unsigned short int scene_;

    } 
    
    /*** STRUCTURE DECLARATIONS ***/
    WINDOW;

// _________________________________________________________________________________
// _________________________________________________________________________________

/*** FUNCTION DEFINITIONS ***/

void FulfillAuxiliaryStructure()
{
WINDOW.aspect_ = WINDOW.RENDERING_MODE_FULL_WINDOW;
WINDOW.fovy_ = 90.0;
WINDOW.eye_[0] = 0.0;
WINDOW.eye_[1] = 0.0;
WINDOW.eye_[2] = 3.0;
WINDOW.center_[0] = 0.0;
WINDOW.center_[1] = 0.0;
WINDOW.center_[2] = -100.0;
WINDOW.bstate_ = GLUT_DOWN;
WINDOW.cursor_[0] = 0;
WINDOW.cursor_[1] = 0;
WINDOW.cursor_[2] = 0;
WINDOW.object_ = 1;
WINDOW.left_ = -10.0;
WINDOW.right_ = 10.0;
WINDOW.bottom_ = -10.0;
WINDOW.top_ = 10.0;
WINDOW.near_ = 50.0;
WINDOW.far_ = 70.0;
WINDOW.scale_ = 1.0;
WINDOW.rotate_[0] = 0.0;
WINDOW.rotate_[1] = 0.0;
WINDOW.translate_[0] = 0.0;
WINDOW.translate_[1] = 0.0;
WINDOW.depth_ = GL_LESS;
WINDOW.scene_ = WINDOW.SCENE_1_SQUARE;
};

// _________________________________________________________________________________
