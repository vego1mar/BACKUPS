#include "FileReader.hpp"
#include <cstddef>
#include <iostream>

pg::FileReader::FileReader( const FileReader & rhs )
{
// This should be a utility class.
}

pg::FileReader & pg::FileReader::operator= ( const FileReader & rhs )
{
// This should be a utility class.
return *this;
}

bool pg::FileReader::Open( std::ifstream & stream, const char * filename, std::ios_base::openmode mode )
{
if ( stream.is_open() == false ) {
    stream.open( filename, mode );
    }

if ( stream.rdstate() == std::ios_base::failbit ) {
    return false;
    }

return true;
}

bool pg::FileReader::Close( std::ifstream & stream )
{
if ( stream.is_open() ) {
    stream.close();
    }

if ( stream.rdstate() == std::ios_base::failbit ) {
    return false;
    }

return true;
}

std::string pg::FileReader::GetNextLine( std::ifstream & stream )
{
if ( stream.is_open() ) {
    std::string line;
    std::getline( stream, line );
    return line;
    }

return std::string( "" );
}

bool pg::FileReader::HasNextLine( std::ifstream & stream )
{
if ( stream.peek() != EOF ) {
    return true;
    }

return false;
}

void pg::FileReader::SetFileCursorFlagAtStart( std::ifstream & stream )
{
if ( HasNextLine(stream) == false ) {
    stream.clear();
    }

stream.seekg( 0, std::ios::beg );
}
