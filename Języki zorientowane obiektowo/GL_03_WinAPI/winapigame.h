// ------------------------------------------------------------------------------------------------------
// AN OVERVIEW
// ------------------------------------------------------------------------------------------------------
// 
// WinAPIGame
// 
// Specialization of the Game class with an aim to dealing with WinAPI output.
// 



// ------------------------------------------------------------------------------------------------------
// HISTORY OF CHANGES
// ------------------------------------------------------------------------------------------------------
//
// -----------------	----------------	-------------------------------------------------------------
// Ordinal no.			Date				Description
// -----------------	----------------	-------------------------------------------------------------
// 001					04/03/2016			Start of the project
//



#ifndef WINAPI_GAME_H
#define WINAPI_GAME_H

	#include "..\GL_00_Libraries\game.h"

	class WinAPIGame : public Game
		{

		// _______________________________________________________________________________________

		public:

			// The default constructor
			WinAPIGame();

			// The destructor.
			~WinAPIGame();

		// _______________________________________________________________________________________

		private:

			// The copy constructor.
			WinAPIGame(const WinAPIGame &);

			// The overloaded assignment operator.
			WinAPIGame & operator= (const WinAPIGame &);

		// _______________________________________________________________________________________

		public:

			// Derived pure virtual function from the Game class.
			// Gives logic using Analyze() procedure from the Engine class.
			void Play();

			// Derived pure virtual function from the Game class.
			// Gives graphics using their specialized way.
			// Specialization in the ConsoleGame class is to handle with WinAPI output.
			void Draw();

		// _______________________________________________________________________________________

		};

#endif // WINAPI_GAME_H