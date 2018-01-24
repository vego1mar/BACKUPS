// ------------------------------------------------------------------------------------------------------
// AN OVERVIEW
// ------------------------------------------------------------------------------------------------------
// 
// ConsoleGame
// 
// Specialization of the Game class with an aim to dealing with console output.
// 



// ------------------------------------------------------------------------------------------------------
// HISTORY OF CHANGES
// ------------------------------------------------------------------------------------------------------
//
// -----------------	----------------	-------------------------------------------------------------
// Ordinal no.			Date				Description
// -----------------	----------------	-------------------------------------------------------------
// 001					04/03/2016			Start of the project
// 002                  15/04/2016          Play() and Draw() procedures has been finished.
// 003                  22/05/2016          Set/Get functions and the console context was added.



#ifndef CONSOLE_GAME_H
#define CONSOLE_GAME_H

	#include "..\GL_00_Libraries\game.h"
    #include <Windows.h>

	class ConsoleGame : public Game
		{

        // _______________________________________________________________________________________

        private :

            // A handler to the console output context.
            HANDLE hc_;

            // An auxiliary structure to set the cursor position in the console context.
            COORD c_;

            // The number of iteration to the game logic in the Play() procedure.
            unsigned short int loop_;

            // The number of miliseconds to sleep before executing the next step of the game logic.
            DWORD ms_;

            // A flag informing whether sleeping before the next step should be used or not.
            bool sl_;

            // A flag informing whether Play() procedure should go step by step after a keystroke or not.
            bool wait_;

		// _______________________________________________________________________________________

		public:

			// The default constructor
			ConsoleGame();

			// The destructor.
			~ConsoleGame();

		// _______________________________________________________________________________________

		private:

			// The copy constructor.
			ConsoleGame(const ConsoleGame &);

			// The overloaded assignment operator.
			ConsoleGame & operator= (const ConsoleGame &);

		// _______________________________________________________________________________________

		public:

			// Derived pure virtual function from the Game class.
			// Gives logic using Analyze() procedure from the Engine class.
			void Play();

			// Derived pure virtual function from the Game class.
			// Gives graphics using their specialized way.
			// Specialization in the ConsoleGame class is to handle with console output.
			void Draw();

		// _______________________________________________________________________________________

        public :

            // Set the number of iteration for the Play() procedure.
            void PlayFor( unsigned short int );

            // Set the number of miliseconds to be sleeped before the next step and the on-off flag.
            void SleepFor( bool, DWORD );

            // Set a flag to whether wait for a key before the next step or not.
            void WaitKey( bool );

        // _______________________________________________________________________________________

        public :

            // Retrieves the number of iteration for the Play() procedure.
            unsigned short int GetPlayForValue();

            // Retrieves the number of miliseconds to be sleeped in the Play() procedure.
            DWORD GetSleepForValue1();

            // Retrieves the state of the on-off sleeping flag for the Play() procedure.
            bool GetSleepForValue2();

            // Retrieves the state of the on-off keywaiting-flag used in the Play() procedure.
            bool GetWaitKeyValue();

        // _______________________________________________________________________________________

		};

#endif // CONSOLE_GAME_H
