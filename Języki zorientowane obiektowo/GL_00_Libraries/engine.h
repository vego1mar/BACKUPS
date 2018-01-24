// ------------------------------------------------------------------------------------------------------
// AN OVERVIEW
// ------------------------------------------------------------------------------------------------------
// 
// Engine
// 
// Class giving logic and the aggregated operations based on it.
// 



// ------------------------------------------------------------------------------------------------------
// HISTORY OF CHANGES
// ------------------------------------------------------------------------------------------------------
//
// -----------------    ----------------    -------------------------------------------------------------
// Ordinal no.          Date                Description
// -----------------    ----------------    -------------------------------------------------------------
// 001                  04/03/2016          Start of the project.
// 002                  06/03/2016          Set/Get functions was added.
// 003                  15/04/2016          Set/Get functions related to basic arrays was added.



#ifndef ENGINE_H
#define ENGINE_H

	class Engine
		{

		// _______________________________________________________________________________________

		protected:

			// An enumerator used for storing constant values.
			enum { X = 80, Y = 25, P = 9 };

		// _______________________________________________________________________________________

		private:

			// An array containing cells logic representation.
			bool T_ [X][Y];

			// An auxiliary array used for analyzing purposes.
			bool A_ [X][Y];

			// An array storing the information about survival of the cell.
			bool live_ [P];

			// An array storing the information about death of the cell.
			bool die_ [P];

		// _______________________________________________________________________________________

		public:

			// The default constructor.
			Engine();

			// The destructor.
			~Engine();

		// _______________________________________________________________________________________
		
		private:

			// The copy constructor.
			Engine(const Engine &);

			// The overloaded assignment operator.
			Engine & operator= (const Engine &);

		// _______________________________________________________________________________________

		protected:

			// A procedure giving the next step of a solution.
			void Analyze();

		// _______________________________________________________________________________________

		protected:

			// Set function related to the T_ array.
			// Parameters are value and the first & second index number.
			// The cell is set only when index bounds are correct.
			void SetCell(bool, short int, short int);

			// Get function related to the T_ array.
			// Parameters are first & second index number.
			// If the index bounds are incorrect, false is returned.
			bool GetCell(short int, short int) const;

			// Set function related to the Y_ array.
			// Parameters are value and the first & second index number.
			// The cell is set only when index bounds are correct.
			void SetAux(bool, short int, short int);

			// Get function related to the Y_ array.
			// Parameters are first & second index number.
			// If the index bounds are incorrect, false is returned.
			bool GetAux(short int, short int) const;

            // Get function related to the live_ array.
            bool GetLive ( short int ) const;

            // Set function related to the live_ array.
            void SetLive ( bool, short int );

            // Get function related to the die_ array.
            bool GetDie ( short int ) const;

            // Set function related to the die_ array.
            void SetDie ( bool, short int );

		// _______________________________________________________________________________________

		};

#endif // ENGINE_H
