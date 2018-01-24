// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Data
// Used as a data type in the class List.
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// ------    -------------    -----------------------------------------------------------
// No.       Date             Description
// ------    -------------    -----------------------------------------------------------
// 001       27/03/2016       Start of the project.



#ifndef DATA_H
#define DATA_H

// **************************************************************************************

    class Data
        {

        // ___________________________________________________________________________

        /*** Poles ***/

        private:
            
            // An enumerator for storing constant values.
            enum constants { SIZE = 256 };

            // An array for the C-style string data.
            char T [SIZE];

        // ___________________________________________________________________________

        /*** Constructors and the destructor ***/

        public:

            // The parametric constructor #1.
            Data(const char *);

            // The parametric constructor #2.
            Data(char);

            // The destructor.
            ~Data();

            // The type conversion constructor.
            operator Data() const;

            // The default constructor.
            Data();
            
            // The copy constructor.
            Data(const Data &);

        // ___________________________________________________________________________

        /*** The overloaded operators ***/

        public:

            // The assignment operator.
            Data & operator= (const Data &);

        // ___________________________________________________________________________

        /*** Get functions ***/

        public:

            // Gives the C-style string data.
            const char * Get() const;

        // ___________________________________________________________________________

        /*** Set functions ***/

            // Set the C-style string data.
            void Set(const char *);

        // ___________________________________________________________________________

        };

// **************************************************************************************

#endif // DATA_H
