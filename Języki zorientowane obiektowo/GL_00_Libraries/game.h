// ------------------------------------------------------------------------------------------------------
// AN OVERVIEW
// ------------------------------------------------------------------------------------------------------
// 
// Game
// 
// A class that operates on Engine class methods.
// It gives also the prerequisites.
// 



// ------------------------------------------------------------------------------------------------------
// HISTORY OF CHANGES
// ------------------------------------------------------------------------------------------------------
//
// -----------------	----------------	-------------------------------------------------------------
// Ordinal no.			Date				Description
// -----------------	----------------	-------------------------------------------------------------
// 001					04/03/2016			Start of the project
// 002                  15/04/2016          Init() procedure has been fixed.



// ------------------------------------------------------------------------------------------------------
// FILE FORMAT DESCRIPTION
// ------------------------------------------------------------------------------------------------------
// 
// Behaviour:
// Game::Init()   -->>   Engine::T_ [T1][T2]
//
// There are T2 rows and T1 columns.
// Each row is breaked by a newline character after T1 values.
// Each value is separated by a white space character.
// Only 0 and 1 values are acceptable.
// 
// The following example shows correct filled file array when T1 = T2 = 10.
// 
//   0   0   0   0   0   0   0   0   0   0
//   0   0   0   0   0   0   0   0   0   0
//   0   0   0   0   0   0   0   0   0   0
//   0   0   0   0   0   1   0   0   0   0
//   0   0   0   0   0   1   0   0   0   0
//   0   0   0   1   1   1   1   1   0   0
//   0   0   0   0   0   1   0   0   0   0
//   0   0   0   0   0   1   0   0   0   0
//   0   0   0   0   0   0   0   0   0   0
//   0   0   0   0   0   0   0   0   0   0
//



#ifndef GAME_H
#define GAME_H

	#include "engine.h"

	class Game : public Engine
		{

		// _______________________________________________________________________________________

		protected:

			// An enumerator used for storing constant values.
			enum { F = 32, C = 12 };

			// A character array for storing the filename.
			char filename_ [F];

			// A character array for storing the condition.
			char condition_ [C];

		// _______________________________________________________________________________________

		public:

			// The default constructor.
			Game();

		// _______________________________________________________________________________________

		private:

			// The copy constructor.
			Game(const Game &);

			// The overloaded assignment operator.
			Game & operator= (const Game &);

		// _______________________________________________________________________________________

		protected:

			// The destructor.
			// When protected, then dynamic upcast or downcast is illegal.
			~Game();

		// _______________________________________________________________________________________

		public:

			// Gives logic using Analyze() procedure from the Engine class.
			virtual void Play() = 0;

			// Gives graphics using their specialized way.
			virtual void Draw() = 0;

		// _______________________________________________________________________________________

		public:

			// A general procedure used for first initialization.
			// Gives the prerequisites for the Game-like class that is a filename and a condition.
			void Init(const char *, const char *);

		// _______________________________________________________________________________________

		};

#endif // GAME_H
