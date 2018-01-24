// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Node
// Used as an abstract input in the class List.
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// ------    -------------    -----------------------------------------------------------
// No.       Date             Description
// ------    -------------    -----------------------------------------------------------
// 001       27/03/2016       Start of the project.



#ifndef NODE_H
#define NODE_H

// **************************************************************************************

    #include "Data.h"

// **************************************************************************************

    class Node
        {

        // ___________________________________________________________________________

        /*** Poles ***/

        private:

            // An object used as a datatype.
            class Data data_;

            // A pointer to the previous element (on the list).
            Node * previous_;

            // A pointer to the next element (on the list).
            Node * next_;

        // ___________________________________________________________________________

        /*** Constructors and the destructor ***/

        public:

            // The destructor.
            ~Node();

            // The default constructor.
            Node();

            // The parametric constructor #1.
            Node(const Data &);

            // The copy constructor.
            Node(const Node &);

        // ___________________________________________________________________________

        /*** The overloaded operators ***/

        public:

            // The assignment operator.
            Node & operator= (const Node &);

        // ___________________________________________________________________________

        /*** Set functions ***/

        public:

           // Set the data in the given Node.
           void SetData(const char *);

           // Alters the pointer to the previous Node element at nodes chain.
           void SetPrevious(Node * const);

           // Set a nullptr value as a previous Node element at nodes chain.
           void SetANullPointerToPrevious();

           // Alters the pointer to the next Node element at nodes chain.
           void SetNext(Node * const);

           // Set a nullptr value as a next Node element at nodes chain.
           void SetANullPointerToNext();

        // ___________________________________________________________________________

        /*** Get functions ***/

        public:

            // Giving the data from a composed object of class Data.
            const char * GetData() const;

            // Gives the pointer to the previous Node element at nodes chain.
            const Node * const GetPrevious() const;

            // Gives the pointer to the next Node element at nodes chain.
            const Node * const GetNext() const;

        // ___________________________________________________________________________

        };

// **************************************************************************************

#endif // NODE_H
