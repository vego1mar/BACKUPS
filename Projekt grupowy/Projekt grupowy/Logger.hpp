#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

namespace pg
{
    /*
     * Created for logging purposes. Uses standard output and standard error output.
     * Utility class.
     */
    class Logger
    {

    #pragma region Constructors
    private:
        Logger() = default;
        Logger( const Logger & rhs );
        Logger & operator= ( const Logger & rhs );
        ~Logger() = default;
    #pragma endregion

    #pragma region Interface
    public:
        static void WriteToStdOut( std::string message );
        static void WriteToStdErr( std::string message );
        static void WriteToStream( std::ostream & out, std::string msg );
        static void WriteLineToStdOut( std::string message );
        static void WriteLineToStdErr( std::string message );
        static void WriteLineToStream( std::ostream & out, std::string msg );
    #pragma endregion

    };
}

#endif // !LOGGER_H
