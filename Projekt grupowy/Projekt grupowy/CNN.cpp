#include "CNN.hpp"
#include "Logger.hpp"
#include "FileReader.hpp"
#include "FileWriter.hpp"
#include "GNUCompilersPatches.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <set>

#pragma region Members
std::size_t pg::CNN::m_LastNumberOfClasses = 0;
std::size_t pg::CNN::m_LastNumberOfParameters = 0;
std::size_t pg::CNN::m_LastNumberOfRecords = 0;
#pragma endregion

#pragma region Constants
const std::string pg::CNN::RELATIVE_PATH_OF_CNN_SET_1ST_PASS = "Outputs\\Reduced_1stPass.txt";
const std::string pg::CNN::RELATIVE_PATH_OF_CNN_SET_2ND_PASS = "Outputs\\Reduced_2ndPass.txt";
const std::string pg::CNN::RELATIVE_PATH_OF_OBJECT_OF_CENTER = "Outputs\\ObjectOfCenter.txt";
const std::string pg::CNN::RELATIVE_PATH_OF_SORTED_DISTANCES_DATA = "Outputs\\SortedDistancesData.txt";
const std::string pg::CNN::RELATIVE_PATH_OF_SORTED_SOURCE_DATA_1ST_PASS = "Outputs\\SortedSourceData_1stPass.txt";
const std::string pg::CNN::RELATIVE_PATH_OF_SORTED_SOURCE_DATA_2ND_PASS = "Outputs\\SortedSourceData_2ndPass.txt";
const std::string pg::CNN::RELATIVE_PATH_OF_CNN_SET_1ST_PASS_CYCLES_INFO = "Outputs\\CyclesInfo_1stPass.txt";
const std::string pg::CNN::RELATIVE_PATH_OF_CNN_SET_2ND_PASS_CYCLES_INFO = "Outputs\\CyclesInfo_2ndPass.txt";
#pragma endregion

pg::CNN::CNN( const CNN & rhs )
{
    // This should be a utility class.
}

pg::CNN::CNN( const CNN && rhs )
{
    *this = std::move( rhs );
}

pg::CNN & pg::CNN::operator= ( const CNN & rhs )
{
    // This should be a utility class.
    return *this;
}

void pg::CNN::GetCNNSet( std::string filename )
{
    std::ifstream reader;

    if ( FileReader::Open( reader, filename.c_str(), std::ios::in ) == false ) {
        Logger::WriteLineToStdErr( "Reading the content of a file '" + filename + "' fails at opening." );
        return;
    }

    m_LastNumberOfClasses = 0;
    m_LastNumberOfParameters = 0;
    m_LastNumberOfRecords = 0;
    ParseFileHeader( reader );

    Array2D recordsData( m_LastNumberOfRecords, m_LastNumberOfParameters + 1 );
    ReadFileData( reader, recordsData );

    if ( FileReader::Close( reader ) == false ) {
        Logger::WriteLineToStdErr( "Stream closing related with file '" + filename + "' has not been handled properly." );
    }

    Array2D objectOfCenter( 1, m_LastNumberOfParameters + 1 );
    GainObjectOfCenter( objectOfCenter, recordsData );
    WriteObjectOfCenterIntoFile( objectOfCenter, RELATIVE_PATH_OF_OBJECT_OF_CENTER.c_str() );

    Array2D distancesKeys( m_LastNumberOfRecords, 2 );
    GainDistancesAuxiliaryData( recordsData, objectOfCenter, distancesKeys );
    BubbleSortDistancesData( distancesKeys );
    WriteSortedDistancesDataIntoFile( distancesKeys, RELATIVE_PATH_OF_SORTED_DISTANCES_DATA.c_str() );

    Array2D recordsDataSorted( m_LastNumberOfRecords, m_LastNumberOfParameters + 1 );
    GainSortedFileData( recordsDataSorted, recordsData, distancesKeys );
    WriteSortedSourceDataIntoFile( recordsDataSorted, RELATIVE_PATH_OF_SORTED_SOURCE_DATA_1ST_PASS.c_str() );

    Array2D cnnSet( m_LastNumberOfRecords, m_LastNumberOfParameters + 1 );
    Array2D cnnSetCyclesInfo( m_LastNumberOfRecords, 1 );
    std::size_t cnnSetOf1stPassSize = ProcessUsingHartAlgorithm( recordsDataSorted, cnnSet, distancesKeys, cnnSetCyclesInfo );
    WriteCyclesInfoDataIntoFile( cnnSetCyclesInfo, RELATIVE_PATH_OF_CNN_SET_1ST_PASS_CYCLES_INFO.c_str() );

    if ( WriteCNNSetToFile( RELATIVE_PATH_OF_CNN_SET_1ST_PASS.c_str(), cnnSet, cnnSetOf1stPassSize, distancesKeys ) == false ) {
        std::string cnnSetOf1stPassPath( RELATIVE_PATH_OF_CNN_SET_1ST_PASS );
        Logger::WriteLineToStdErr( "WriteCNNSetToFile() returned 'false' for a relative path='" + cnnSetOf1stPassPath + "'." );
    }

    SortDataByModifyingTheOrder( recordsDataSorted, distancesKeys, cnnSetOf1stPassSize, recordsData );
    WriteSortedSourceDataIntoFile( recordsDataSorted, RELATIVE_PATH_OF_SORTED_SOURCE_DATA_2ND_PASS.c_str() );
    std::size_t cnnSetOf2ndPassSize = ProcessUsingHartAlgorithm( recordsDataSorted, cnnSet, distancesKeys, cnnSetCyclesInfo );
    WriteCyclesInfoDataIntoFile( cnnSetCyclesInfo, RELATIVE_PATH_OF_CNN_SET_2ND_PASS_CYCLES_INFO.c_str() );

    if ( WriteCNNSetToFile( RELATIVE_PATH_OF_CNN_SET_2ND_PASS.c_str(), cnnSet, cnnSetOf2ndPassSize, distancesKeys ) == false ) {
        std::string cnnSetOf2ndPassPath( RELATIVE_PATH_OF_CNN_SET_2ND_PASS );
        Logger::WriteLineToStdErr( "WriteCNNSetToFile() returned 'false' for a relative path='" + cnnSetOf2ndPassPath + "'." );
    }
}

/*
 * Please note, that the 'reader' should already been opened.
 */
void pg::CNN::ParseFileHeader( std::ifstream & reader )
{
    std::string header = FileReader::GetNextLine( reader );
    std::stringstream parser( header );
    parser >> m_LastNumberOfClasses;
    parser >> m_LastNumberOfParameters;
    parser >> m_LastNumberOfRecords;
}

/*
 * Please note, that the 'reader' should already been opened.
 */
void pg::CNN::ReadFileData( std::ifstream & reader, Array2D & data )
{
    double parsedNumber = 0.0;

    for ( std::size_t i = 0; i < m_LastNumberOfRecords; i++ ) {
        std::string line = FileReader::GetNextLine( reader );
        std::stringstream parser( line );

        for ( std::size_t j = 0; j < m_LastNumberOfParameters + 1; j++ ) {
            parser >> parsedNumber;
            data.set( parsedNumber, i, j );
        }
    }
}

/*
 * This is a mean value for each of the columns, namely parameters.
 * Please note, that the first parameter - at index 0 - will be ignored.
 */
void pg::CNN::GainObjectOfCenter( Array2D & center, const Array2D & DATA )
{
    for ( std::size_t i = 0; i < m_LastNumberOfParameters + 1; i++ ) {
        center.set( 0.0, 0, i );
    }

    for ( std::size_t i = 0; i < m_LastNumberOfRecords; i++ ) {
        for ( std::size_t j = 1; j < m_LastNumberOfParameters + 1; j++ ) {
            center.set( center.get( 0, j ) + DATA.get( i, j ), 0, j );
        }
    }

    for ( std::size_t i = 1; i < m_LastNumberOfParameters + 1; i++ ) {
        center.set( center.get( 0, i ) / m_LastNumberOfRecords, 0, i );
    }
}

/*
 * Example:
 * 0)	4.510000	4.510000	4.510000	4.510000	4.510000
 */
void pg::CNN::WriteObjectOfCenterIntoFile( const Array2D & CENTER, const char * path )
{
    std::ofstream fileWriter;
    const std::string TABULATOR = "\t";
    std::string fileContent = "0)" + TABULATOR;

    for ( std::size_t i = 1; i < m_LastNumberOfParameters + 1; i++ ) {
        fileContent += gnu::to_string( CENTER.get( 0, i ) );
        fileContent += TABULATOR;
    }

    FileWriter::WriteOnce( fileWriter, path, std::ios::out, fileContent );
}

/*
 * Data distribution of 'distances' is as following:
 *             [0]               [1]
 *    [0]      distance_0        key_0
 *    [1]      distance_1        key_1
 *    ...      ...               ...
 *
 * The stored key is an index value and may be safe casted to the decimal data type.
 * Also note, that the first parameter (namely column) from 'DATA' and 'CENTER' will be ignored, so as in 'distances'.
 */
void pg::CNN::GainDistancesAuxiliaryData( const Array2D & DATA, const Array2D & CENTER, Array2D & distances )
{
    double substractionSquare;
    double distance;

    for ( std::size_t i = 0; i < m_LastNumberOfRecords; i++ ) {
        distance = 0.0;

        for ( std::size_t j = 1; j < m_LastNumberOfParameters + 1; j++ ) {
            substractionSquare = DATA.get( i, j ) - CENTER.get( 0, j );
            substractionSquare *= substractionSquare;
            distance += substractionSquare;
        }

        distances.set( distance, i, 0 );
        distances.set( i, i, 1 );
    }
}

/*
 * Sorts (distance, key) pairs using distance value as a determinant (sorter).
 */
void pg::CNN::BubbleSortDistancesData( Array2D & distances )
{
    double swapDistance;
    double swapKey;

    for ( std::size_t i = 0; i < m_LastNumberOfRecords; i++ ) {
        for ( std::size_t j = 0; j < m_LastNumberOfRecords - 1; j++ ) {
            if ( distances.get( j, 0 ) > distances.get( j + 1, 0 ) ) {
                swapDistance = distances.get( j, 0 );
                swapKey = distances.get( j, 1 );
                distances.set( distances.get( j + 1, 0 ), j, 0 );
                distances.set( distances.get( j + 1, 1 ), j, 1 );
                distances.set( swapDistance, j + 1, 0 );
                distances.set( swapKey, j + 1, 1 );
            }
        }
    }
}

/*
 * [A] - an index of the 'DISTANCES' table
 * [B] - a distance from `object` (`record`) referenced in this same line of [C] to the object of center
 * [C] - an index of an `object` prior to the input data (from file)
 *
 * Example:
 *        [A]            [B]             [C]
           0)	    0.464538	         588
           1)	    0.645045	         295
           2)	    0.712347	         490
           3)	    0.724625	         792
 */
void pg::CNN::WriteSortedDistancesDataIntoFile( const Array2D & DISTANCES, const char * path )
{
    std::ofstream fileWriter;
    const std::string TABULATOR = "\t";
    const std::streamsize WIDTH = 12;
    const std::streamsize PRECISION = 6;

    if ( FileWriter::Open( fileWriter, path, std::ios::out ) ) {
        FileWriter::HoldWriter( fileWriter, path );

        for ( std::size_t i = 0; i < m_LastNumberOfRecords; i++ ) {
            FileWriter::WriteFormattedSizeT( FileWriter::RIGHT, WIDTH, i, false );
            FileWriter::Write( ")" + TABULATOR );
            FileWriter::WriteFormattedDouble( WIDTH, FileWriter::RIGHT, true, PRECISION, DISTANCES.get( i, 0 ), false );
            FileWriter::Write( TABULATOR );
            FileWriter::WriteFormattedDouble( WIDTH, FileWriter::RIGHT, true, 0, DISTANCES.get( i, 1 ), true );
        }

        FileWriter::UnholdWriter();
        FileWriter::Close( fileWriter );
    }
}

void pg::CNN::GainSortedFileData( Array2D & sorted, const Array2D & DATA, const Array2D & DISTANCES )
{
    std::size_t currentReplacementIndex;

    for ( std::size_t i = 0; i < m_LastNumberOfRecords; i++ ) {
        currentReplacementIndex = static_cast<std::size_t>(DISTANCES.get( i, 1 ));

        for ( std::size_t j = 0; j < m_LastNumberOfParameters + 1; j++ ) {
            sorted.set( DATA.get( currentReplacementIndex, j ), i, j );
        }
    }
}

void pg::CNN::WriteSortedSourceDataIntoFile( const Array2D & SORTED, const char * path )
{
    std::ofstream fileWriter;
    const std::string TABULATOR = "\t";
    const std::streamsize WIDTH = 10;
    const std::streamsize PRECISION = 6;

    if ( FileWriter::Open( fileWriter, path, std::ios::out ) ) {
        FileWriter::HoldWriter( fileWriter, path );

        for ( std::size_t i = 0; i < m_LastNumberOfRecords; i++ ) {
            FileWriter::WriteFormattedSizeT( FileWriter::RIGHT, WIDTH, i, false );
            FileWriter::Write( ")" + TABULATOR );
            FileWriter::WriteFormattedSizeT( FileWriter::RIGHT, WIDTH, static_cast<std::size_t>(SORTED.get( i, 0 )), false );
            FileWriter::Write( TABULATOR );

            for ( std::size_t j = 1; j < m_LastNumberOfParameters + 1; j++ ) {
                FileWriter::WriteFormattedDouble( WIDTH, FileWriter::RIGHT, true, PRECISION, SORTED.get( i, j ), false );
            }

            FileWriter::WriteLine( "" );
        }

        FileWriter::UnholdWriter();
        FileWriter::Close( fileWriter );
    }
}

/*
 * An implementation of the Hart's CNN algorithm (of a NN-classification rule).
 * Builds the reduced set and stores it in 'cnnSet' parameter.
 * Returns the number of records in 'cnnSet', that has been reached from index 0 (a workflow size).
 */
std::size_t pg::CNN::ProcessUsingHartAlgorithm( const Array2D & SORTED, Array2D & cnnSet, Array2D & recordsOriginIndices, Array2D & cyclesInfo )
{
    CopyRecord( SORTED, 0, m_LastNumberOfParameters + 1, cnnSet, 0 );
    recordsOriginIndices.set( 0, 0, 0 );

    std::size_t cnnSetWorkflowSize = 1;
    bool isAdditionDone = true;
    std::size_t currentClassFromCNN;
    std::size_t currentClassFromSortedSet;
    unsigned long numberOfCycle = 0;

    do {
        isAdditionDone = false;

        for ( std::size_t i = 1; i < m_LastNumberOfRecords; i++ ) {
            currentClassFromCNN = ClassifyRecordWithCNNSet( cnnSet, cnnSetWorkflowSize, SORTED, i );
            currentClassFromSortedSet = static_cast<std::size_t>(SORTED.get( i, 0 ));

            if ( currentClassFromSortedSet != currentClassFromCNN ) {
                recordsOriginIndices.set( i, cnnSetWorkflowSize, 0 );
                CopyRecord( SORTED, i, m_LastNumberOfParameters + 1, cnnSet, cnnSetWorkflowSize );
                cnnSetWorkflowSize++;
                isAdditionDone = true;
            }
        }

        numberOfCycle++;
        cyclesInfo.set( cnnSetWorkflowSize, numberOfCycle, 0 );
    }
    while ( isAdditionDone );

    cyclesInfo.set( numberOfCycle, 0, 0 );
    return cnnSetWorkflowSize;
}

/*
 * Copy 'parametersNumber' of cells from the 'source' at 'sourceRecordIndex' to the 'target' at 'targetRecordIndex'.
 * Designed for intepreting an 'Array2D' type, assuming that initialization was as follows: array( records, parameters ).
 */
void pg::CNN::CopyRecord( const Array2D & SOURCE, std::size_t sourceRecordIndex, std::size_t parametersNumber, Array2D & target, std::size_t targetRecordIndex )
{
    for ( std::size_t i = 0; i < parametersNumber; i++ ) {
        target.set( SOURCE.get( sourceRecordIndex, i ), targetRecordIndex, i );
    }
}

/*
 * Searches for the nearest record in 'CNN_SET' in terms of a record pointed by 'recordIndex' in 'SORTED'.
 * Returns a `class` parameter of the nearest founded record in 'CNN_SET', that is the first parameter.
 */
std::size_t pg::CNN::ClassifyRecordWithCNNSet( const Array2D & CNN_SET, std::size_t cnnSetSize, const Array2D & SORTED, std::size_t recordIndex )
{
    Array2D distances( cnnSetSize, 1 );
    double currentDistance;

    for ( std::size_t i = 0; i < cnnSetSize; i++ ) {
        currentDistance = CountDistanceBetweenRecords( SORTED, recordIndex, CNN_SET, i );
        distances.set( currentDistance, i, 0 );
    }

    std::size_t searchedRecordIndex = GetIndexOfMinimalValue( distances, cnnSetSize );
    std::size_t classParameter = static_cast<std::size_t>(CNN_SET.get( searchedRecordIndex, 0 ));
    return classParameter;
}

/*
 * Counts the distance from 'SORTED' at 'recordIndex' to 'CNN_SET' at 'cnnIndex'.
 */
double pg::CNN::CountDistanceBetweenRecords( const Array2D & SORTED, std::size_t recordIndex, const Array2D & CNN_SET, std::size_t cnnIndex )
{
    double distance = 0.0;
    double partialResult;

    for ( std::size_t i = 0; i < m_LastNumberOfParameters + 1; i++ ) {
        partialResult = SORTED.get( recordIndex, i ) - CNN_SET.get( cnnIndex, i );
        partialResult *= partialResult;
        distance += partialResult;
    }

    return distance;
}

/*
 * Please note, that only the first parameters will be checked.
 */
std::size_t pg::CNN::GetIndexOfMinimalValue( const Array2D & DISTANCES, std::size_t cnnSetSize )
{
    std::size_t minimumIndex = 0;
    double minimumValue = DISTANCES.get( minimumIndex, 0 );

    for ( std::size_t i = 1; i < cnnSetSize; i++ ) {
        if ( DISTANCES.get( i, 0 ) < minimumValue ) {
            minimumValue = DISTANCES.get( i, 0 );
            minimumIndex = i;
        }
    }

    return minimumIndex;
}

/*
 * [A] - number of the cycle
 * [B] - size of the CNN set
 *
 * Example:
 *       [A]           [B]
 *        1)	        59
 *        2)	        70
 *        3)	        74
 *        4)	        74
 */
void pg::CNN::WriteCyclesInfoDataIntoFile( const Array2D & CNN_SET_CYCLES_INFO, const char * path )
{
    std::ofstream fileWriter;

    if ( FileWriter::Open( fileWriter, path, std::ios::out ) ) {
        FileWriter::HoldWriter( fileWriter, path );
        const unsigned long NUMBER_OF_CYCLES_PERFORMED = static_cast<unsigned long>(CNN_SET_CYCLES_INFO.get( 0, 0 ));
        const std::streamsize WIDTH = 10;
        const std::string TABULATOR = "\t";
        std::size_t currentCastedValue;

        for ( unsigned long i = 1; i <= NUMBER_OF_CYCLES_PERFORMED; i++ ) {
            currentCastedValue = static_cast<std::size_t>(CNN_SET_CYCLES_INFO.get( i, 0 ));
            FileWriter::WriteFormattedSizeT( FileWriter::RIGHT, WIDTH, i, false );
            FileWriter::Write( ")" + TABULATOR );
            FileWriter::WriteFormattedSizeT( FileWriter::RIGHT, WIDTH, currentCastedValue, true );
        }

        FileWriter::UnholdWriter();
        FileWriter::Close( fileWriter );
    }
}

/*
 * Example:
 * 2 5 3
 * 2    2.000000    2.000000    2.000000    2.000000    2.000000    -->    2
 * 2    0.100000    0.100000    0.100000    0.100000    0.100000    -->    0
 * 1    1.000000    1.000000    1.000000    1.000000    1.000000    -->    1
 */
bool pg::CNN::WriteCNNSetToFile( const char * filename, const Array2D & CNN_SET, std::size_t cnnSetSize, const Array2D & ORIGIN_RECORDS_INDICES )
{
    std::ofstream fileWriter;

    if ( FileWriter::Open( fileWriter, filename, std::ios::out ) == false ) {
        std::string fileName( filename );
        Logger::WriteLineToStdErr( "Internal stream of WriteCNNSetToFile() fails at opening '" + fileName + "'." );
        return false;
    }

    FileWriter::HoldWriter( fileWriter, filename );
    std::size_t classesVariety = GetMaximumClassNumberFromRecords( CNN_SET, cnnSetSize );
    WriteHeaderToStream( classesVariety, m_LastNumberOfParameters, cnnSetSize );
    WriteSetOfDataToStream( CNN_SET, cnnSetSize, ORIGIN_RECORDS_INDICES );
    FileWriter::UnholdWriter();
    FileWriter::Close( fileWriter );
    return true;
}

std::size_t pg::CNN::GetMaximumClassNumberFromRecords( const Array2D & CNN_SET, std::size_t cnnSetSize )
{
    std::size_t maximum = 0;
    std::size_t currentClass;

    for ( std::size_t i = 0; i < cnnSetSize; i++ ) {
        currentClass = static_cast<std::size_t>(CNN_SET.get( i, 0 ));

        if ( currentClass > maximum ) {
            maximum = currentClass;
        }
    }

    return maximum;
}

/*
 * An example of a file header:
 * 3 10 960
 */
void pg::CNN::WriteHeaderToStream( std::size_t numberOfClasses, std::size_t numberOfParameters, std::size_t numberOfRecords )
{
    const std::string SPACE = " ";
    std::string header = gnu::to_string( numberOfClasses );
    header += SPACE;
    header += gnu::to_string( numberOfParameters );
    header += SPACE;
    header += gnu::to_string( numberOfRecords );
    FileWriter::WriteLine( header );
}

/*
 * Writes the data from 'SET' using writer holding under 'FileWriter' utility class.
 *
 * An example of this data format output ('numberOfParameters' = 3, 'setSize' = 2):
 * 1    12.45553    23.45455     2.345229
 * 3    21.35554     3.54216    10.124500
 */
void pg::CNN::WriteSetOfDataToStream( const Array2D & SET, std::size_t setSize, const Array2D & ORIGIN_RECORDS_INDICES )
{
    const std::string SPACE = " ";
    const std::string TABULATOR = "\t";
    std::size_t currentClass;
    double currentParameter;
    std::size_t currentOriginIndex;

    for ( std::size_t i = 0; i < setSize; i++ ) {
        currentClass = static_cast<std::size_t>(SET.get( i, 0 ));
        FileWriter::WriteFormattedSizeT( FileWriter::LEFT, 2, currentClass, false );
        FileWriter::Write( SPACE );

        for ( std::size_t j = 1; j < m_LastNumberOfParameters + 1; j++ ) {
            currentParameter = SET.get( i, j );
            FileWriter::WriteFormattedDouble( 10, FileWriter::RIGHT, true, 6, currentParameter, false );
            FileWriter::Write( TABULATOR );
        }

        currentOriginIndex = GetOriginalIndexHavingRelativeIndexOf( i, ORIGIN_RECORDS_INDICES );
        FileWriter::Write( TABULATOR + "-->" );
        FileWriter::WriteFormattedSizeT( FileWriter::RIGHT, 12, currentOriginIndex, true );
    }
}

void pg::CNN::SortDataByModifyingTheOrder( Array2D & sorted, Array2D & originRecordsIndices, std::size_t cnnSetSize, const Array2D & DATA )
{
    Array2D newOrder( m_LastNumberOfRecords, 1 );
    GainNewOrderForHartAlgorithm( newOrder, cnnSetSize, originRecordsIndices );
    SortUsingNewOrderForHartAlgorithm( sorted, newOrder, DATA );
}

std::size_t pg::CNN::GetOriginalIndexHavingRelativeIndexOf( std::size_t index, const Array2D & ORIGIN_RECORDS_INDICES )
{
    std::size_t relativeIndex = static_cast<std::size_t>(ORIGIN_RECORDS_INDICES.get( index, 0 ));
    std::size_t originIndex = static_cast<std::size_t>(ORIGIN_RECORDS_INDICES.get( relativeIndex, 1 ));
    return originIndex;
}

/*
 * Example:
 *      Objects = 10
 *      CNN     = { 5, 4, 6, 7, 1, 0, 2 }
 *      Ordered = { 2, 0, 1, 7, 6, 4, 5, 3, 8, 9 }
 */
void pg::CNN::GainNewOrderForHartAlgorithm( Array2D & order, std::size_t cnnSetSize, Array2D & originRecordsIndices )
{
    std::size_t newOrderSize = 0;
    std::size_t currentOriginIndex;
    std::set<std::size_t> cnnSetOriginIndices;
    bool isInSet;

    for ( std::size_t i = cnnSetSize - 1; i > 0; i-- ) {
        currentOriginIndex = GetOriginalIndexHavingRelativeIndexOf( i, originRecordsIndices );
        order.set( currentOriginIndex, cnnSetSize - i - 1, 0 );
        cnnSetOriginIndices.insert( currentOriginIndex );
        newOrderSize++;
    }

    currentOriginIndex = GetOriginalIndexHavingRelativeIndexOf( 0, originRecordsIndices );
    order.set( currentOriginIndex, cnnSetSize - 1, 0 );
    cnnSetOriginIndices.insert( currentOriginIndex );
    newOrderSize++;

    for ( std::size_t i = 0; i < m_LastNumberOfRecords; i++ ) {
        isInSet = cnnSetOriginIndices.find( i ) != cnnSetOriginIndices.end();

        if ( isInSet == false ) {
            order.set( i, newOrderSize, 0 );
            newOrderSize++;
        }
    }

    for ( std::size_t i = 0; i < m_LastNumberOfRecords; i++ ) {
        originRecordsIndices.set( order.get( i, 0 ), i, 1 );
    }
}

void pg::CNN::SortUsingNewOrderForHartAlgorithm( Array2D & sorted, const Array2D & ORDER, const Array2D & DATA )
{
    std::size_t currentReplacementIndex;

    for ( std::size_t i = 0; i < m_LastNumberOfRecords; i++ ) {
        currentReplacementIndex = static_cast<std::size_t>(ORDER.get( i, 0 ));

        for ( std::size_t j = 0; j < m_LastNumberOfParameters + 1; j++ ) {
            sorted.set( DATA.get( currentReplacementIndex, j ), i, j );
        }
    }
}
