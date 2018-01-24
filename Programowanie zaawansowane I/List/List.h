// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// List
// The one-directional list data structure based on a queue.
//
// At the start the list is empty.
// Adding a node means updating the array of class Node's allocated on the heap.
// The number of nodes that can be added is a specific number defined as SIZE.
// Addition of the node is starting from an index equal 0.
// Removing the node means clearing the links of class Node object.
// The number of nodes that can be removed is the same as SIZE.
// Deletion of the node is starting from an index equal 0 (like in FIFO queue).
//
// The copy construction is not allowed.
// Set functions are currently available only for completeness.
// Calling the destructor means clearing the memory with 0's or spaces.
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// ------    -------------    -----------------------------------------------------------
// No.       Date             Description
// ------    -------------    -----------------------------------------------------------
// 001       27/03/2016       Start of the project.
// 002       28/03/2016       Development of the functionalities was ended.



#ifndef LIST_H
#define LIST_H

// **************************************************************************************

    #include "Node.h"
    #include "Data.h"

// **************************************************************************************

    class List
        {

        // ___________________________________________________________________________

        /*** Poles ***/

        private:

            // A pointer to the first element on the queue list.
            class Node * first_;

            // A pointer to the last element on the queue list.
            class Node * last_;

            // A pointer to the last used element on the queue list.
            class Node * current_;

            // The number of elements on the list.
            unsigned short int number_;

            // A dynamically allocated array for the queue of the list.
            class Node * queue_;

            // An enumerator for storing constant values.
            enum constants_ { SIZE = 0xFFFF };

            // The number of removed nodes in the queue list.
            unsigned short int deleted_;

        // ___________________________________________________________________________

        /*** Constructors and the destructor ***/

        public:

            // The default constructor.
            List();

            // The destructor.
            ~List();

        private:

            // The copy constructor.
            List(const List &);

        // ___________________________________________________________________________

        /*** The overloaded operators ***/

        private:

            // The assignment operator.
            List & operator= (const List &);

        public:

            // The array subscript operator.
            // Use to get the data of a given class Node object on the queue chain list.
            const char * operator[] (unsigned short int);

            // The array subscript operator.
            // Use to get the data of a given class Node object on the queue chain list.
            const char * const operator[] (unsigned short int) const;

        // ___________________________________________________________________________

        /*** Set functions ***/

        protected:

            // Set a pointer to the first element on the list.
            void SetFirstElement(class Node * const);

            // Set a pointer to the last element on the list.
            void SetLastElement(class Node * const);

            // Set a pointer to the last used element on the list.
            void SetCurrentElement(class Node * const);

            // Set the number of elements on the list.
            void SetNumberOfElements(unsigned short int);

            // Set the class Node on the queue chain list.
            void SetNodeOnTheQueue(unsigned short int, const char *, Node * const, Node * const);

            // Set the number of removed elements on the queue list.
            void SetNumberOfDeletedNodes(unsigned short int); 
             
        // ___________________________________________________________________________

        /*** Get functions ***/

        public:
            
            // Gives a pointer to the first element on the list.
            const class Node * const GetFirstElement() const;

            // Gives a pointer to the last element on the list.
            const class Node * const GetLastElement() const;

            // Gives a pointer to the last used element on the list.
            const class Node * const GetCurrentElement() const;

            // Gives the number of elements on the list.
            unsigned short int GetNumberOfElements() const; 

            // Gives the number of class Node elements being allocated on the heap.
            unsigned short int GetListSize() const;

            // Gives the number of removed nodes on the queue list.
            unsigned short int GetNumberOfDeletedNodes() const;

        protected:

            // Gives a pointer to the class Node on the queue chain list.
            const class Node * const GetNodeOnTheQueue(unsigned short int) const;

        // ___________________________________________________________________________

        /*** The class interface ***/

        public:

            // Add the element with its data to the list.
            void AddNode(const class Data & _data);

            // Remove the first element from the list (like in FIFO queue).
            bool RemoveNode();

            // Retrieves the element data at given index position on the queue list.
            // It is not the same behaviour as it is in the array subscript operator.
            class Node & GetElementDataAt(unsigned short int);

            // Retrieves a pointer to the previous element on the list.
            class Node * const GetPreviousElement();

            // Retrieves a pointer to the next element on the list.
            class Node * const GetNextElement();

            // Rewind the list by setting the current pointer to the first element on the list.
            void Rewind(); 

        // ___________________________________________________________________________

        /*** The internal functions ***/

        private:

            // Aggregates some routines to be used at destructor time.
            void ClearTheQueue();

        // ___________________________________________________________________________

        };

// **************************************************************************************

#endif // LIST_H
