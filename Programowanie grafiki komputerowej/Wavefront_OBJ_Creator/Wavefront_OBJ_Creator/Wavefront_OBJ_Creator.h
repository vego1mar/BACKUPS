//////////////////////////////////////////////////////////////////////////////////////////////////////
/*
   
   WavefrontOBJCreator
   CLI program

   IV 2016

   Create an .OBJ file of the Wavefront format from the data of the .PGM file.

*/
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdio>

// ---------------------------------------------------------------------------------------------------

class WavefrontOBJCreator
    {

    // _______________________________________________________________________________________________

    /*** THE POLES ***/

    private:

        // A file pointer to the input file (.pbm).
        FILE * in_;

        // A file pointer to the output file (.obj).
        FILE * out_;

        // An enumerator for storing constants.
        enum CONSTANTS_ { F = 63 };

        // An array for storing C-style string of the input file name.
        char input_filename_ [F];

        // An array for storing C-style string of the output file name.
        char output_filename_ [F];

        // An expected value searched in the input file (.pgm).
        short int expected_;

        // A value used as a height of the plane model.
        short int height_;


    // _______________________________________________________________________________________________

    /***  CONSTRUCTORS AND THE DESTRUCTOR ***/

    public:

        // The default constructor.
        WavefrontOBJCreator();

        // The destructor.
        ~WavefrontOBJCreator();

    private:

        // The copy constructor.
        WavefrontOBJCreator ( const WavefrontOBJCreator & );

    // _______________________________________________________________________________________________

    /***  THE OVERLOADED OPERATORS ***/

    private:

        // The overloaded assignment operator.
        WavefrontOBJCreator & operator= ( const WavefrontOBJCreator & );

    // _______________________________________________________________________________________________

    /*** THE GET-CLASS FUNCTIONS ***/

    public:

        // Retrieves a locked file pointer to the input file.
        const FILE * const GetInputFilePointer ( );

        // Retrieves a locked file pointer to the output file.
        const FILE * const GetOutputFilePointer ( );

        // Returns the value of an enumerator related to the filename size.
        int GetFilenameConstantValue ( );

        // Returns the C-style string having the input filename.
        const char * const GetInputFilename ( );

        // Returns the C-style string having the output filename.
        const char * const GetOutputFilename ( );

        // Returns the expected value searched in the input file (.pgm).
        short int GetExpectedValue ( );

        // Returns the height of the builded model.
        short int GetHeight ( );

    // _______________________________________________________________________________________________

    /*** THE SET-CLASS FUNCTIONS ***/

    public:

        // Set the new linkage in the input file pointer.
        void SetInputFilePointer ( FILE * & );

        // Set the new linkage in the output file pointer.
        void SetOutputFilePointer ( FILE * & );

        // Set the new filename of the input data.
        void SetInputFilename ( const char * );

        // Set the new filename of the output data.
        void SetOutputFilename ( const char * );

        // Set the new expected value to be searched in the input file (.pgm).
        void SetExpectedValue ( short int );

        // Set the new height of the builded model.
        void SetHeight ( short int ); 

    // _______________________________________________________________________________________________

    /*** THE CLASS INTERFACE ***/

    public:

        // Create the .obj file using data from the .pbm file implicitly named.
        unsigned long int CreateWavefrontFile( const char *, const char * );

        // Create the .obj file using data from the .pbm file.
        unsigned long int CreateWavefrontFile( );

    // _______________________________________________________________________________________________

    };

// ---------------------------------------------------------------------------------------------------
