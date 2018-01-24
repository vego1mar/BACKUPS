#ifndef FILE_WRITER_HPP
#define FILE_WRITER_HPP

#include <string>
#include <fstream>
#include <cstdbool>

namespace pg
{
    /*
     * Designed for dealing with file's writing and writing controlling.
     * Utility class.
     */
    class FileWriter
    {

    #pragma region Members
    public:
        static const enum m_PaddingStyles { INTERNAL, LEFT, RIGHT } PADDING;

    private:
        static std::string m_HoldingWriterInfo;
        static bool m_IsWriterHolding;
        static std::ofstream * m_HoldingWriterPointer;
    #pragma endregion

    #pragma region Constructors
    private:
        FileWriter() = default;
        FileWriter( const FileWriter & rhs );
        FileWriter( const FileWriter && rhs );
        FileWriter & operator= ( const FileWriter & rhs );
        ~FileWriter() = default;
    #pragma endregion

    #pragma region Interface
    public:
        static bool Open( std::ofstream & writer, const char * path, std::ios_base::openmode mode );
        static bool Close( std::ofstream & writer );
        static bool HoldWriter( std::ofstream & writer, std::string info );
        static bool IsWriterHolding();
        static std::string GetHoldingWriterInfo();
        static bool UnholdWriter();
        static bool Write( std::string content );
        static bool WriteFormattedDouble( std::streamsize width, m_PaddingStyles padding, bool fixed, std::streamsize setPrecision, double doubleNumber, bool endLine );
        static bool WriteFormattedSizeT( m_PaddingStyles padding, std::streamsize setW, std::size_t sizeTNumber, bool endLine );
        static bool WriteLine( std::string content );
        static bool WriteOnce( std::ofstream & writer, const char * path, std::ios_base::openmode mode, std::string content );

    private:
        static void ApplyPaddingStyle( m_PaddingStyles padding );
    #pragma endregion

    };
}

#endif // !FILE_WRITER_HPP
