#ifndef FILE_READER_HPP
#define FILE_READER_HPP

#include <fstream>
#include <string>
#include <cstdbool>

namespace pg
{
    /*
     * Created for dealing with file's reading and a quick access for the most common operation related with it.
     * Utility class.
     */
    class FileReader
    {

    #pragma region Constructors
    private:
        FileReader() = default;
        FileReader( const FileReader & rhs );
        FileReader & operator= ( const FileReader & rhs );
        ~FileReader() = default;
    #pragma endregion

    #pragma region Interface
    public:
        static bool Open( std::ifstream & stream, const char * filename, std::ios_base::openmode mode );
        static bool Close( std::ifstream & stream );
        static std::string GetNextLine( std::ifstream & stream );
        static bool HasNextLine( std::ifstream & stream );
        static void SetFileCursorFlagAtStart( std::ifstream & stream );
    #pragma endregion

    };
}

#endif // !FILE_READER_HPP
