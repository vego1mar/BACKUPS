#ifndef CIPHERS_HPP
#define CIPHERS_HPP

#include <string>
#include <cstdbool>
#include <cstddef>
#include <set>
#include <cstring>

namespace ciphers
{
    #pragma region Constants
    const int OFFSET_OF_CESAR_CIPHER = 3;
    const short MINIMUM_BLOCK_LENGTH = 3;
    const std::string FILENAME_OF_PATTERN_STATISTICS = "stats_pattern.txt";
    const std::string FILENAME_OF_CIPHER_STATISTICS = "stats_cipher.txt";
    const std::string FILENAME_OF_RESULT_STATISTICS = "stats_result.txt";
    const std::string FILENAME_OF_EXTENDED_VIGENERE_CIPHER_TEXT = "vigenere_ciphertext.txt";
    const std::string FILENAME_OF_EXTENDED_VIGENERE_PLAIN_TEXT = "vigenere_plaintext.txt";
    const std::string FILENAME_OF_STATS_FROM_KASISKI_TEST = "stats_kasiski_test.txt";
    const std::string FILENAME_OF_LUCAS_LEHMER_TEST = "lucas_lehmer_test.txt";
    #pragma endregion

    #pragma region Main interface
    void EncryptOrDecryptCesarLikeCipherFromStdIn( int offset );
    std::string EncryptOrDecryptCesarLikeCipherFromFile( int offset, const char * path );
    int PerformStatisticalAnalysisOfCesarLikeCipher( std::string catalogPath, const char * patternFilename, const char * cipherFilename );
    std::string EncryptUsingExtendedVigenereCipher( const char * pathOfKey, const char * pathOfMessage );
    std::string DecryptUsingExtendedVigenereCipher( const char * pathOfKey, const char * pathOfCipher );
    long PerformKasiskiTestOfVigenereLikeCipher( const char * pathOfCipherText, short keyBlockLength, long * divisors, std::size_t divisorsLength );
    void PerformLucasLehmerTestForExponents( std::size_t lowerLimitExponent, std::size_t upperLimitExponent, const char * path );
    #pragma endregion    

    namespace aux
    {
        #pragma region Constants    
        const int DIGITS_ARRAY_SIZE = 120;
        const int ALPHABET_LENGTH = 26;
        const short int AMOUNTS_ARRAY_SIZE = 128;
        const std::string LINE_SEPARATOR = "=============================================";
        const std::size_t DIVISORS_ARRAY_MINIMUM_SIZE = 20;
        #pragma endregion

        #pragma region Auxiliary interface
        void FillAuxiliaryDigitsArray( char digits[] );
        void GainNumberOfCharactersFromFile( short amounts[], const char * path );
        void WriteStatisticsAmountsToFile( short amounts[], const char * path );
        int FindOffsetUsingStatistics( short amountsOfPattern[], short amountsOfCipher[] );
        int FindIndexOfMaximumValue( const short amounts[], const int leftLimit, const int rightLimit );
        void TryToDecryptAndSaveMessageToFile( int offset, const char * pathOfMessage, const char * pathOfResult );
        std::string ReadLineFromFile( const char * path );
        std::string RemoveNonAlphabeticalAndNonDigitCharacters( const std::string string );
        std::string GainExtendedVigenereAlphabet();
        bool IsCharacterInString( char character, const std::string string );
        std::string ReadEntireFileMessage( const char * path );
        std::string EncryptMessageInVigenereWay( const std::string key, const std::string message, const std::string alphabet );
        std::string DecryptMessageInVigenereWay( const std::string key, const std::string cipher, const std::string alphabet );
        void SaveMessageToFile( const std::string message, const char * path );
        std::size_t GetIndexOfCharacterFirstOccurence( char character, const std::string string );
        std::size_t FindDistanceBetweenTheFirstSameBlocksInText( const std::string text, const std::size_t blockInTextBegin, const std::size_t blockInTextEnd );
        void IncrementArrayCellsThatAreDivisorsOf( std::size_t number, long * divisorsArray, std::size_t divisorsArrayLength );
        long GetLastMaximumIndexOfValueFromArrayInBounds( const long * array, std::size_t begin, std::size_t end );
        bool SaveStatsFromKasiskiTestIntoFile( const char * filename, const long * const statsArray, const std::size_t statsArrayLength, long keyLength );
        bool IsPrime( unsigned long long number );
        bool IsPrime2( unsigned long long number );
        unsigned long long GetRootedDecimalValueFromNumberOf( unsigned long long number );
        std::set<unsigned long long> GetPrimesLowerThenUsingEratostenesSieveApproach( unsigned long long number );
        bool IsNumberDivisibleBy( unsigned long long dividend, unsigned long long divider );
        unsigned long long HowManyPrimesInInclusiveRangeOf( unsigned long long lowerLimit, unsigned long long upperLimit );
        unsigned long long HowManyPrimesInInclusiveRangeOf2( unsigned long long lowerLimit, unsigned long long upperLimit );
        unsigned long long HowManyPrimesInInclusiveRangeOf3( unsigned long long lowerLimit, unsigned long long upperLimit );
        bool IsPrime3( std::size_t marsenneNumberExponent );
        uint64_t PowerForUInt64( uint64_t base, uint64_t exponent );
        unsigned long long PowerOfModuloByCongruents( unsigned long long base, unsigned long long exponent, unsigned long long modulo );
        unsigned long long PowerOfModuloByBinaryExpansion( unsigned long long base, unsigned long long exponent, unsigned long long modulo );
        std::pair<long long, std::pair<long long, long long>> GetGCDUsingIterativeEEA( long long a, long long b );
        std::pair<long long, std::pair<long long, long long>> GetGCDUsingRecursiveEEA( long long a, long long b );
        long long InverseModuloUsingIterativeEEA( long long a, long long m );
        long long InverseModuloUsingRecursiveEEA( long long a, long long m );
        long long PowerOfModuloByFLT( long long base, long long exponent, long long modulo );
        long long InverseModuloUsingFLT( long long a, long long m );
        #pragma endregion
    }

}

#endif // !CIPHERS_HPP
