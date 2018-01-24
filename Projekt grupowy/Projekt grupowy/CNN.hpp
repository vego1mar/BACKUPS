#ifndef CNN_HPP
#define CNN_HPP

#include "Array2D.hpp"
#include <string>
#include <cstddef>

namespace pg
{
    /*
     * Created for gaining a Condensed Nearest Neighbour set.
     * Utility class.
     */
    class CNN
    {

    #pragma region Members
    private:
        static std::size_t m_LastNumberOfClasses;
        static std::size_t m_LastNumberOfParameters;
        static std::size_t m_LastNumberOfRecords;
    #pragma endregion

    #pragma region Constants
    public:
        static const std::string RELATIVE_PATH_OF_CNN_SET_1ST_PASS;
        static const std::string RELATIVE_PATH_OF_CNN_SET_2ND_PASS;
        static const std::string RELATIVE_PATH_OF_OBJECT_OF_CENTER;
        static const std::string RELATIVE_PATH_OF_SORTED_DISTANCES_DATA;
        static const std::string RELATIVE_PATH_OF_SORTED_SOURCE_DATA_1ST_PASS;
        static const std::string RELATIVE_PATH_OF_SORTED_SOURCE_DATA_2ND_PASS;
        static const std::string RELATIVE_PATH_OF_CNN_SET_1ST_PASS_CYCLES_INFO;
        static const std::string RELATIVE_PATH_OF_CNN_SET_2ND_PASS_CYCLES_INFO;
    #pragma endregion

    #pragma region Constructors
    private:
        CNN() = default;
        CNN( const CNN & rhs );
        CNN( const CNN && rhs );
        CNN & operator= ( const CNN & rhs );
        ~CNN() = default;
    #pragma endregion

    #pragma region Interface
    public:
        // TODO: missing return
        static void GetCNNSet( std::string filename );

    private:
        static void ParseFileHeader( std::ifstream & reader );
        static void ReadFileData( std::ifstream & reader, Array2D & data );
        static void GainObjectOfCenter( Array2D & center, const Array2D & DATA );
        static void WriteObjectOfCenterIntoFile( const Array2D & CENTER, const char * path );
        static void GainDistancesAuxiliaryData( const Array2D & DATA, const Array2D & CENTER, Array2D & distances );
        static void BubbleSortDistancesData( Array2D & distances );
        static void WriteSortedDistancesDataIntoFile( const Array2D & DISTANCES, const char * path );
        static void GainSortedFileData( Array2D & sorted, const Array2D & DATA, const Array2D & DISTANCES );
        static void WriteSortedSourceDataIntoFile( const Array2D & SORTED, const char * path );
        static std::size_t ProcessUsingHartAlgorithm( const Array2D & SORTED, Array2D & cnnSet, Array2D & recordsOriginIndices, Array2D & cyclesInfo );
        static void CopyRecord( const Array2D & SOURCE, std::size_t sourceRecordIndex, std::size_t parametersNumber, Array2D & target, std::size_t targetRecordIndex );
        static std::size_t ClassifyRecordWithCNNSet( const Array2D & CNN_SET, std::size_t cnnSetSize, const Array2D & SORTED, std::size_t recordIndex );
        static double CountDistanceBetweenRecords( const Array2D & SORTED, std::size_t recordIndex, const Array2D & CNN_SET, std::size_t cnnIndex );
        static std::size_t GetIndexOfMinimalValue( const Array2D & DISTANCES, std::size_t cnnSetSize );
        static void WriteCyclesInfoDataIntoFile( const Array2D & CNN_SET_CYCLES_INFO, const char * path );
        static bool WriteCNNSetToFile( const char * filename, const Array2D & CNN_SET, std::size_t cnnSetSize, const Array2D & ORIGIN_RECORDS_INDICES );
        static std::size_t GetMaximumClassNumberFromRecords( const Array2D & CNN_SET, std::size_t cnnSetSize );
        static void WriteHeaderToStream( std::size_t numberOfClasses, std::size_t numberOfParameters, std::size_t numberOfRecords );
        static void WriteSetOfDataToStream( const Array2D & SET, std::size_t setSize, const Array2D & ORIGIN_RECORDS_INDICES );
        static void SortDataByModifyingTheOrder( Array2D & sorted, Array2D & originRecordsIndices, std::size_t cnnSetSize, const Array2D & DATA );
        static std::size_t GetOriginalIndexHavingRelativeIndexOf( std::size_t index, const Array2D & ORIGIN_RECORDS_INDICES );
        static void GainNewOrderForHartAlgorithm( Array2D & order, std::size_t cnnSetSize, Array2D & originRecordsIndices );
        static void SortUsingNewOrderForHartAlgorithm( Array2D & sorted, const Array2D & ORDER, const Array2D & DATA );
    #pragma endregion

    };

}

#endif // !CNN_HPP

