#include "Array2D.hpp"
#include <cstring>

pg::Array2D::Array2D( std::size_t width, std::size_t height )
    : m_ArrayWidth( width )
    , m_ArrayHeight( height )
    , m_Array( new double[width * height] )

{
    for ( unsigned long i = 0; i < m_ArrayHeight*m_ArrayWidth; i++ ) {
        m_Array[i] = 0.0;
    }
}

pg::Array2D::~Array2D()
{
    delete[] m_Array;
}

pg::Array2D::Array2D()
    : m_ArrayWidth( 100 )
    , m_ArrayHeight( 100 )
    , m_Array( new double[m_ArrayWidth * m_ArrayHeight] )

{
}

pg::Array2D::Array2D( const Array2D & rhs )
    : m_ArrayWidth( rhs.m_ArrayWidth )
    , m_ArrayHeight( rhs.m_ArrayHeight )
    , m_Array( new double[rhs.m_ArrayWidth * rhs.m_ArrayHeight] )

{
    std::memcpy( m_Array, rhs.m_Array, sizeof( double ) * rhs.m_ArrayHeight * rhs.m_ArrayWidth );
}

pg::Array2D & pg::Array2D::operator= ( const Array2D & rhs )
{
    if ( this != &rhs ) {
        m_ArrayWidth = rhs.m_ArrayWidth;
        m_ArrayHeight = rhs.m_ArrayHeight;
        std::memcpy( m_Array, rhs.m_Array, sizeof( double ) * rhs.m_ArrayHeight * rhs.m_ArrayWidth );
    }

    return *this;
}

double pg::Array2D::get( std::size_t width, std::size_t height ) const
{
    return m_Array[recountIndices( width, height )];
}

void pg::Array2D::set( double value, std::size_t width, std::size_t height )
{
    m_Array[recountIndices( width, height )] = value;
}

long pg::Array2D::recountIndices( std::size_t width, std::size_t height ) const
{
    return width + m_ArrayWidth * height;
}
