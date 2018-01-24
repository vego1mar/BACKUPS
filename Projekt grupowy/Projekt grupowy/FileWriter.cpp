#include "FileWriter.hpp"
#include <iomanip>

#pragma region Constants
std::string pg::FileWriter::m_HoldingWriterInfo = "";
bool pg::FileWriter::m_IsWriterHolding = false;
std::ofstream * pg::FileWriter::m_HoldingWriterPointer = nullptr;
#pragma endregion

pg::FileWriter::FileWriter( const FileWriter & rhs )
{
    // This should be a utility class.
}

pg::FileWriter::FileWriter( const FileWriter && rhs )
{
    // This should be a utility class.
}

pg::FileWriter & pg::FileWriter::operator= ( const FileWriter & rhs )
{
    // This should be a utility class.
    return *this;
}

bool pg::FileWriter::Open( std::ofstream & writer, const char * path, std::ios_base::openmode mode )
{
    if ( m_IsWriterHolding ) {
        return false;
    }

    writer.open( path, mode );

    if ( writer.is_open() == false || writer.good() == false || writer.bad() == true || writer.fail() == true ) {
        return false;
    }

    return true;
}

bool pg::FileWriter::Close( std::ofstream & writer )
{
    if ( m_IsWriterHolding ) {
        return false;
    }

    if ( writer.is_open() ) {
        writer.close();
    }

    if ( writer.is_open() == false || writer.good() == false || writer.bad() == true || writer.fail() == true ) {
        return false;
    }

    return true;
}

bool pg::FileWriter::HoldWriter( std::ofstream & writer, std::string info = "" )
{
    if ( m_IsWriterHolding ) {
        return false;
    }

    if ( writer.is_open() ) {
        m_IsWriterHolding = true;
        m_HoldingWriterPointer = &(writer);
        m_HoldingWriterInfo = info;
        return true;
    }

    return false;
}

bool pg::FileWriter::IsWriterHolding()
{
    return m_IsWriterHolding;
}

std::string pg::FileWriter::GetHoldingWriterInfo()
{
    return m_HoldingWriterInfo;
}

bool pg::FileWriter::UnholdWriter()
{
    if ( m_IsWriterHolding ) {
        m_IsWriterHolding = false;
        m_HoldingWriterPointer = nullptr;
        m_HoldingWriterInfo = "";
        return true;
    }

    return false;
}

bool pg::FileWriter::Write( std::string content )
{
    if ( m_IsWriterHolding ) {
        *(m_HoldingWriterPointer) << content;
        return true;
    }

    return false;
}

bool pg::FileWriter::WriteFormattedDouble( std::streamsize width, m_PaddingStyles padding, bool fixed, std::streamsize setPrecision, double doubleNumber, bool endLine )
{
    if ( m_IsWriterHolding ) {
        m_HoldingWriterPointer->width( width );
        ApplyPaddingStyle( padding );

        if ( fixed == true ) {
            *(m_HoldingWriterPointer) << &std::fixed << std::setprecision( setPrecision ) << doubleNumber;
        }
        else {
            *(m_HoldingWriterPointer) << std::setprecision( setPrecision ) << doubleNumber;
        }

        if ( endLine == true ) {
            *(m_HoldingWriterPointer) << std::endl;
        }

        return true;
    }

    return false;
}

bool pg::FileWriter::WriteFormattedSizeT( m_PaddingStyles padding, std::streamsize setW, std::size_t sizeTNumber, bool endLine )
{
    if ( m_IsWriterHolding ) {
        ApplyPaddingStyle( padding );
        *(m_HoldingWriterPointer) << std::setw( setW ) << sizeTNumber;

        if ( endLine == true ) {
            *(m_HoldingWriterPointer) << std::endl;
        }

        return true;
    }

    return false;
}

bool pg::FileWriter::WriteLine( std::string content )
{
    if ( m_IsWriterHolding ) {
        *(m_HoldingWriterPointer) << content << std::endl;
        return true;
    }

    return false;
}

bool pg::FileWriter::WriteOnce( std::ofstream & writer, const char * path, std::ios_base::openmode mode, std::string content )
{
    if ( Open( writer, path, mode ) ) {
        writer << content << std::endl;

        if ( Close( writer ) ) {
            return true;
        }
    }

    return false;
}

void pg::FileWriter::ApplyPaddingStyle( m_PaddingStyles padding )
{
    switch ( padding ) {
    case INTERNAL:
        *(m_HoldingWriterPointer) << &std::internal;
        break;
    case LEFT:
        *(m_HoldingWriterPointer) << &std::left;
        break;
    case RIGHT:
        *(m_HoldingWriterPointer) << &std::right;
        break;
    default:
        *(m_HoldingWriterPointer) << &std::internal;
    }
}
