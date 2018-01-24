#include "Logger.hpp"
#include <iostream>

pg::Logger::Logger( const Logger & rhs )
{
    // This should be a utility class.
}

pg::Logger & pg::Logger::operator= ( const Logger & rhs )
{
    // This should be a utility class.
    return *this;
}

void pg::Logger::WriteToStdOut( std::string message )
{
    std::cout << message;
}

void pg::Logger::WriteToStdErr( std::string message )
{
    std::cerr << message;
}

void pg::Logger::WriteToStream( std::ostream & out, std::string msg )
{
    out << msg;
}

void pg::Logger::WriteLineToStdOut( std::string message )
{
    std::cout << message << std::endl;
}

void pg::Logger::WriteLineToStdErr( std::string message )
{
    std::cerr << message << std::endl;
}

void pg::Logger::WriteLineToStream( std::ostream & out, std::string msg )
{
    out << msg << std::endl;
}
