#ifndef ARRAY_2D_HPP
#define ARRAY_2D_HPP

#include <string>
#include <cstddef>

namespace pg
{
/*
 * 1-dimensional array that can be used as a 2-dimensional array.
 * The floating-point data of type 'double' are allocated on the heap.
 */

class Array2D 
    { 

    #pragma region Members
    private:
        std::size_t m_ArrayWidth;
        std::size_t m_ArrayHeight;
        double * m_Array;
    #pragma endregion

    #pragma region Constructors
    public: 
        Array2D( std::size_t width, std::size_t height );
        ~Array2D();
    
    private:
        Array2D();
        Array2D( const Array2D & rhs );
        Array2D & operator= ( const Array2D & rhs );
    #pragma endregion

    #pragma region Interface
    public:
        double get( std::size_t width, std::size_t height ) const;
        void set( double value, std::size_t width, std::size_t height );

    protected: 
        long recountIndices( std::size_t width, std::size_t height ) const;
    #pragma endregion
    
    };
}

#endif // !ARRAY_2D_HPP
