#include "Ciphers.hpp"
#include <cstddef>
#include <cctype>
#include <cstdio>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <map>
#include <climits>

/*
 * Fill in an array with an alphabetic data that helps to deal with encrypting and decrypting.
 *
 * The array have a following data distribution:
 *     [  0]-[ 38]      '0'
 *     [ 39]-[ 64]      'A' - 'Z'
 *     [ 65]-[ 90]      'A' - 'Z'
 *     [ 91]-[116]      'A' - 'Z'
 *     [117]-[119]      '0'
 */
void ciphers::aux::FillAuxiliaryDigitsArray( char digits[] )
{
    int i;
    int j;

    for ( i = 0; i < DIGITS_ARRAY_SIZE; i++ ) {
        digits[i] = 0;
    }

    const int LETTER_A = static_cast<int>('A');
    const int LETTER_Z = static_cast<int>('Z');
    j = LETTER_A;

    for ( i = LETTER_A - ALPHABET_LENGTH; i <= LETTER_A - 1; i++ ) {
        digits[i] = j;
        j++;
    }

    for ( i = LETTER_A; i <= LETTER_Z; i++ ) {
        digits[i] = i;
    }

    j = LETTER_A;

    for ( i = LETTER_Z + 1; i <= LETTER_Z + ALPHABET_LENGTH; i++ ) {
        digits[i] = j;
        j++;
    }
}

/*
 * Encrypts or decrypts the message given on to the standard input (stdin).
 * Only letters from 'A' to 'Z' (also from 'a' to 'z') of the common languages base are subjected to processing.
 *
 * This function behaves as follows:
 *      offset  < 0         decryption
 *      offset == 0         no effect, asymptomatic in terms of encrypting/decrypting
 *      offset  > 0         encryption
 */
void ciphers::EncryptOrDecryptCesarLikeCipherFromStdIn( int offset )
{
    char character = ' ';
    int currentLetter;
    int newLetter;
    offset = offset % aux::ALPHABET_LENGTH;
    char * digits = new char[aux::DIGITS_ARRAY_SIZE];
    aux::FillAuxiliaryDigitsArray( digits );

    while ( (character = std::fgetc( stdin )) != EOF ) {
        if ( character < 0 || std::isalpha( character ) == false ) {
            std::fputc( character, stdout );
        }
        else {
            currentLetter = std::toupper( character );
            newLetter = digits[currentLetter + offset];
            std::fputc( newLetter, stdout );
        }
    }

    delete[] digits;
}

std::string ciphers::EncryptOrDecryptCesarLikeCipherFromFile( int offset, const char * path )
{
    char character = ' ';
    int currentLetter;
    int newLetter;
    char * digits = new char[aux::DIGITS_ARRAY_SIZE];
    std::string transformedMessage = "";
    std::ifstream fileReader;

    offset = offset % aux::ALPHABET_LENGTH;
    aux::FillAuxiliaryDigitsArray( digits );
    fileReader.open( path, std::ios::in );

    while ( fileReader ) {
        fileReader >> &std::noskipws >> character;

        if ( character < 0 || std::isalpha( character ) == false ) {
            transformedMessage += character;
        }
        else {
            currentLetter = std::toupper( character );
            newLetter = digits[currentLetter + offset];
            transformedMessage += newLetter;
        }
    }

    fileReader.close();
    delete[] digits;
    return transformedMessage;
}

/*
 * Reads the file character by character from 'path' and counts the amounts of letters to 'amounts'.
 * Only alphabetical characters are considered, that is 'A'-'Z' and 'a'-'z'.
 *
 * The 'amounts' array data distribution is as following:
 *     [0]         total amount of characters from 'A' to 'Z'
 *     [1]-[64]    not used
 *    [65]-[90]    amounts of characters from 'A' to 'Z'
 *    [90]+        not used
 */
void ciphers::aux::GainNumberOfCharactersFromFile( short amounts[], const char * path )
{
    std::ifstream fileReader;
    char character = ' ';
    int currentLetter;

    if ( amounts == nullptr ) {
        return;
    }

    fileReader.open( path, std::ios::in );

    while ( fileReader ) {
        fileReader >> &std::noskipws >> character;

        if ( character > 0 && std::isalpha( character ) ) {
            currentLetter = std::toupper( character );
            amounts[currentLetter]++;
            amounts[0]++;
        }
    }

    fileReader.close();
}

/*
 * Writes letters statistics to file given in 'path' using data from 'amounts'.
 * Letters means upper characters from 'A' to 'Z'.
 *
 * The file format is as following:
 *      A        321        12.34
 *      B        122        5.33234
 *      ...      ...        ...
 *      Z        11         0.7762311
 *      TOTAL    1667       100 %
 */
void ciphers::aux::WriteStatisticsAmountsToFile( short amounts[], const char * path )
{
    std::ofstream fileWriter;
    fileWriter.open( path, std::ios::out );

    if ( fileWriter.good() == false ) {
        return;
    }

    char currentLetter = ' ';
    double percent;
    const int LETTER_A = static_cast<int>('A');
    const int LETTER_Z = static_cast<int>('Z');

    for ( int i = LETTER_A; i <= LETTER_Z; i++ ) {
        if ( amounts[i] ) {
            currentLetter = static_cast<char>(i);
            percent = (static_cast<double>(amounts[i]) / static_cast<double>(amounts[0])) * 100.0;
            fileWriter << currentLetter << "\t" << amounts[i] << "\t" << percent << std::endl;
        }
    }

    fileWriter << "TOTAL\t" << amounts[0] << "\t100 %" << std::endl;
    fileWriter.close();
}

/*
 * Statistics should be performed on the pattern and cipher distinct texts respectively, but using the same language.
 */
int ciphers::aux::FindOffsetUsingStatistics( short amountsOfPattern[], short amountsOfCipher[] )
{
    const int LETTER_A = static_cast<int>('A');
    const int LETTER_Z = static_cast<int>('Z');
    int indexOfPattern = FindIndexOfMaximumValue( amountsOfPattern, LETTER_A, LETTER_Z );
    int indexOfCipher = FindIndexOfMaximumValue( amountsOfCipher, LETTER_A, LETTER_Z );
    return indexOfCipher - indexOfPattern;
}

int ciphers::aux::FindIndexOfMaximumValue( const short amounts[], const int leftLimit, const int rightLimit )
{
    int maximumValue = amounts[std::abs( leftLimit )];
    int maximumIndex = std::abs( leftLimit );

    for ( int i = std::abs( leftLimit ) + 1; i <= std::abs( rightLimit ); i++ ) {
        if ( amounts[i] > maximumValue ) {
            maximumValue = amounts[i];
            maximumIndex = i;
        }
    }

    return maximumIndex;
}

/*
 * Decrypts the message pointed at 'pathOfMessage' using 'offset' positive and negative value.
 * The result will be saved to the file pointed at 'pathOfResult'.
 *
 * The file format of 'pathOfResult' is as following (an example):
 * 3
 * ALEA IACTA EST.
 * =============================================
 * -3
 * GRKG OGIZG KYZ
 * =============================================
 *
 */
void ciphers::aux::TryToDecryptAndSaveMessageToFile( int offset, const char * pathOfMessage, const char * pathOfResult )
{
    std::string decryptedMessage1 = EncryptOrDecryptCesarLikeCipherFromFile( offset, pathOfMessage );
    std::string decryptedMessage2 = EncryptOrDecryptCesarLikeCipherFromFile( -offset, pathOfMessage );
    std::ofstream fileReader;
    fileReader.open( pathOfResult, std::ios::out );
    fileReader << offset << std::endl;
    fileReader << decryptedMessage1 << std::endl;
    fileReader << LINE_SEPARATOR << std::endl << std::endl;
    fileReader << -offset << std::endl;
    fileReader << decryptedMessage2 << std::endl;
    fileReader << LINE_SEPARATOR << std::endl << std::endl;
    fileReader.close();
}

/*
 * Performs statistical analysis using distinct texts of pattern and cipher respectively.
 * Tries to decrypt the message in the same language by finding a corresponding offset.
 * Saves files about performed statistics.
 */
int ciphers::PerformStatisticalAnalysisOfCesarLikeCipher( std::string catalogPath, const char * patternFilename, const char * cipherFilename )
{
    short int * amountsOfPattern = new short int[aux::AMOUNTS_ARRAY_SIZE];
    short int * amountsOfCipher = new short int[aux::AMOUNTS_ARRAY_SIZE];
    std::memset( amountsOfPattern, 0, aux::AMOUNTS_ARRAY_SIZE * sizeof( short int ) );
    std::memset( amountsOfCipher, 0, aux::AMOUNTS_ARRAY_SIZE * sizeof( short int ) );
    const std::string PATTERN_COMBINED_PATH = catalogPath + patternFilename;
    const std::string CIPHER_COMBINED_PATH = catalogPath + cipherFilename;
    ciphers::aux::GainNumberOfCharactersFromFile( amountsOfPattern, PATTERN_COMBINED_PATH.c_str() );
    ciphers::aux::GainNumberOfCharactersFromFile( amountsOfCipher, CIPHER_COMBINED_PATH.c_str() );
    const std::string STATISTICS_PATTERN_COMBINED_PATH = catalogPath + FILENAME_OF_PATTERN_STATISTICS;
    const std::string STATISTICS_CIPHER_COMBINED_PATH = catalogPath + FILENAME_OF_CIPHER_STATISTICS;
    ciphers::aux::WriteStatisticsAmountsToFile( amountsOfPattern, STATISTICS_PATTERN_COMBINED_PATH.c_str() );
    ciphers::aux::WriteStatisticsAmountsToFile( amountsOfCipher, STATISTICS_CIPHER_COMBINED_PATH.c_str() );
    int offset = ciphers::aux::FindOffsetUsingStatistics( amountsOfPattern, amountsOfCipher );
    delete[] amountsOfPattern;
    delete[] amountsOfCipher;
    return offset;
}

std::string ciphers::EncryptUsingExtendedVigenereCipher( const char * pathOfKey, const char * pathOfMessage )
{
    std::string keyLine = aux::ReadLineFromFile( pathOfKey );
    const std::string KEY = aux::RemoveNonAlphabeticalAndNonDigitCharacters( keyLine );
    const std::string ALPHABET = aux::GainExtendedVigenereAlphabet();
    const std::string MESSAGE = aux::ReadEntireFileMessage( pathOfMessage );
    std::string encryptedMessage = aux::EncryptMessageInVigenereWay( KEY, MESSAGE, ALPHABET );
    return encryptedMessage;
}

std::string ciphers::DecryptUsingExtendedVigenereCipher( const char * pathOfKey, const char * pathOfCipher )
{
    std::string keyLine = aux::ReadLineFromFile( pathOfKey );
    const std::string KEY = aux::RemoveNonAlphabeticalAndNonDigitCharacters( keyLine );
    const std::string ALPHABET = aux::GainExtendedVigenereAlphabet();
    const std::string CIPHER = aux::ReadEntireFileMessage( pathOfCipher );
    std::string decryptedMessage = aux::DecryptMessageInVigenereWay( KEY, CIPHER, ALPHABET );
    return decryptedMessage;
}

std::string ciphers::aux::ReadLineFromFile( const char * path )
{
    std::string line;
    std::ifstream fileReader;
    fileReader.open( path, std::ios::in );

    if ( fileReader.is_open() ) {
        std::getline( fileReader, line );
        fileReader.close();
    }

    return line;
}

std::string ciphers::aux::RemoveNonAlphabeticalAndNonDigitCharacters( const std::string string )
{
    std::string alphabet = GainExtendedVigenereAlphabet();
    std::string legitimateString;

    for ( std::size_t i = 0; i < string.size(); i++ ) {
        if ( IsCharacterInString( string.c_str()[i], alphabet ) ) {
            legitimateString += string.c_str()[i];
        }
    }

    return legitimateString;
}

std::string ciphers::aux::GainExtendedVigenereAlphabet()
{
    std::string alphabet( "" );
    char i;

    for ( i = 'A'; i <= 'Z'; i++ ) {
        alphabet += i;
    }

    for ( i = '0'; i <= '9'; i++ ) {
        alphabet += i;
    }

    return alphabet;
}

bool ciphers::aux::IsCharacterInString( char character, const std::string string )
{
    for ( std::size_t i = 0; i < string.size(); i++ ) {
        if ( string.c_str()[i] == character ) {
            return true;
        }
    }

    return false;
}

std::string ciphers::aux::ReadEntireFileMessage( const char * path )
{
    std::string content;
    std::ifstream fileReader;
    fileReader.open( path, std::ios::in );

    if ( fileReader.is_open() ) {
        fileReader.seekg( 0, std::ios_base::beg );
        content = std::string( (std::istreambuf_iterator<char>( fileReader )), std::istreambuf_iterator<char>() );
        fileReader.close();
    }

    return content;
}

std::string ciphers::aux::EncryptMessageInVigenereWay( const std::string key, const std::string message, const std::string alphabet )
{
    std::string processedMessage;
    std::size_t indexOfKey;
    std::size_t indexOfMessage;
    std::size_t indexOfNewLetter;

    for ( std::size_t i = 0; i < message.size(); i++ ) {
        if ( message[i] > 0 && std::isalnum( message[i] ) ) {
            indexOfKey = i % key.size();
            indexOfKey = GetIndexOfCharacterFirstOccurence( key[indexOfKey], alphabet );
            indexOfMessage = GetIndexOfCharacterFirstOccurence( std::toupper( message[i] ), alphabet );
            indexOfNewLetter = indexOfKey + indexOfMessage;
            indexOfNewLetter %= alphabet.size();
            processedMessage += alphabet[indexOfNewLetter];
        }
        else {
            processedMessage += message[i];
        }
    }

    return processedMessage;
}

std::string ciphers::aux::DecryptMessageInVigenereWay( const std::string key, const std::string cipher, const std::string alphabet )
{
    std::string processedMessage;
    std::size_t indexOfKey;
    std::size_t indexOfCipher;
    std::size_t indexOfTextLetter;

    for ( std::size_t i = 0; i < cipher.size(); i++ ) {
        if ( cipher[i] > 0 && std::isalnum( cipher[i] ) ) {
            indexOfKey = i % key.size();
            indexOfKey = GetIndexOfCharacterFirstOccurence( key[indexOfKey], alphabet );
            indexOfCipher = GetIndexOfCharacterFirstOccurence( std::toupper( cipher[i] ), alphabet );
            indexOfTextLetter = std::abs( static_cast<int>(indexOfKey - indexOfCipher) );

            if ( indexOfKey > indexOfCipher ) {
                indexOfTextLetter = alphabet.size() - indexOfTextLetter;
            }

            processedMessage += alphabet[indexOfTextLetter];
        }
        else {
            processedMessage += cipher[i];
        }
    }

    return processedMessage;
}

void ciphers::aux::SaveMessageToFile( const std::string message, const char * path )
{
    std::ofstream fileWriter;
    fileWriter.open( path, std::ios::out );

    if ( fileWriter.is_open() ) {
        fileWriter << message;
        fileWriter.close();
    }
}

std::size_t ciphers::aux::GetIndexOfCharacterFirstOccurence( char character, const std::string string )
{
    for ( std::size_t i = 0; i < string.size(); i++ ) {
        if ( string[i] == character ) {
            return i;
        }
    }

    return 0;
}

/*
 * Proceed with a Kasiski test for Vigenere ciphers that quesses the length of the key (a password).
 */
long ciphers::PerformKasiskiTestOfVigenereLikeCipher( const char * pathOfCipherText, short keyBlockLength, long * divisors, std::size_t divisorsLength )
{
    if ( keyBlockLength < ciphers::MINIMUM_BLOCK_LENGTH ) {
        return -1;
    }

    std::string ciphertext = aux::ReadEntireFileMessage( pathOfCipherText );
    std::size_t currentDistance;
    std::memset( divisors, 0, divisorsLength * sizeof( long ) );
    std::size_t lastLeftBlockBegin = 0;
    std::size_t lastLeftBlockEnd = keyBlockLength - 1;

    do {
        currentDistance = aux::FindDistanceBetweenTheFirstSameBlocksInText( ciphertext, lastLeftBlockBegin, lastLeftBlockEnd );
        aux::IncrementArrayCellsThatAreDivisorsOf( currentDistance, divisors, divisorsLength );
        lastLeftBlockBegin += currentDistance;
        lastLeftBlockEnd = lastLeftBlockBegin + keyBlockLength - 1;
    }
    while ( currentDistance != 0 );

    return aux::GetLastMaximumIndexOfValueFromArrayInBounds( divisors, 2, divisorsLength );
}

/*
 * Searches for the first occurence of a specified block of text in 'text'.
 * Computes the number of characters between the first characters of this two blocks.
 *
 * Example:
 *      For:
            indices = [012345678901234]
 *          text =    ".TEXT...TEXT..."
 *          blockInTextBegin = 1
 *          blockInTextEnd = 4
 *      It will be:
 *          blocktext = "TEXT"
 *          result = 7
 *
 * Returns:
 * 0, when the specified blocktext have no occurences in 'text',
 * positive value, otherwise.
 */
std::size_t ciphers::aux::FindDistanceBetweenTheFirstSameBlocksInText( const std::string text, const std::size_t blockInTextBegin, const std::size_t blockInTextEnd )
{
    std::string blocktext = text.substr( blockInTextBegin, blockInTextEnd - blockInTextBegin + 1 );
    std::string currentBlock;

    for ( std::size_t i = blockInTextEnd + 1; i < text.size() - blocktext.size(); i++ ) {
        currentBlock = text.substr( i, blocktext.size() );

        if ( currentBlock == blocktext ) {
            return (i - blockInTextBegin);
        }
    }

    return 0;
}

/*
 * Checks which of the indices from 1 to 'divisorsArrayLength' are divisors of a 'number'.
 * Increments the value of cells at index of divisors that have been classified as divisors of the 'number'.
 * At index 0 of 'divisorsArray' there will be stored the total amount of such increments.
 *
 * Example:
 *      divisorsArray = { 0, 0, 0 ... 0, 0 }
 *      number = 9
 *      divisors = { 1, 3, 9 }
 *      divisorsArray[1] = 1
 *      divisorsArray[3] = 1
 *      divisorsArray[9] = 1
 */
void ciphers::aux::IncrementArrayCellsThatAreDivisorsOf( std::size_t number, long * divisorsArray, std::size_t divisorsArrayLength )
{
    double currentDivision;
    long currentMultiplication;

    for ( std::size_t i = 1; i < divisorsArrayLength; i++ ) {
        currentDivision = static_cast<double>(number) / static_cast<double>(i);
        currentMultiplication = static_cast<long>(currentDivision) * i;

        if ( currentMultiplication == number ) {
            divisorsArray[i]++;
            divisorsArray[0]++;
        }

        if ( i >= number ) {
            break;
        }
    }
}

/*
 * Searches for the last index (in ascending order) of the maximum value from the 'array'.
 * The bounds are right exclusive, there are from an interval of <begin, end).
 *
 * Example:
 *      indices = [ 0  1  2  3  4  5  6  7 ]
 *      array =   { 1, 3, 2, 1, 3, 0, 3, 1 }
 *      begin = 0
 *      end = 6
 *      result = 4
 *
 * Returns:
 * -1, when 'begin' is greater than 'end',
 * a positive value, otherwise - searched in bounds of ['begin'; 'end').
 */
long ciphers::aux::GetLastMaximumIndexOfValueFromArrayInBounds( const long * array, std::size_t begin, std::size_t end )
{
    if ( begin > end ) {
        return -1;
    }

    long maximumValue = array[begin];
    long maximumIndex = begin;

    for ( std::size_t i = begin + 1; i < end; i++ ) {
        if ( array[i] >= maximumValue ) {
            maximumValue = array[i];
            maximumIndex = i;
        }
    }

    return maximumIndex;
}

bool ciphers::aux::SaveStatsFromKasiskiTestIntoFile( const char * filename, const long * const statsArray, const std::size_t statsArrayLength, long keyLength )
{
    std::ofstream fileWriter;
    fileWriter.open( filename, std::ios::out );

    if ( fileWriter.is_open() ) {
        const std::string TABULATOR = "\t";

        for ( std::size_t i = 0; i < statsArrayLength; i++ ) {
            fileWriter << &std::right << std::setw( 10 ) << i << TABULATOR << &std::right << std::setw( 10 ) << statsArray[i] << std::endl;
        }

        fileWriter << std::endl;
        fileWriter << "Expected key divisor (length):   " << &std::right << std::setw( 10 ) << keyLength << std::endl;
        fileWriter << "Expected key divisor occurences: " << &std::right << std::setw( 10 ) << statsArray[keyLength] << std::endl;
        fileWriter.close();
        return true;
    }

    return false;
}

bool ciphers::aux::IsPrime( unsigned long long number )
{
    if ( number < 2 ) {
        return false;
    }

    unsigned long long intervalOfNumber = GetRootedDecimalValueFromNumberOf( number ) + 1;

    for ( unsigned long long i = 2; i < intervalOfNumber; i++ ) {
        if ( number % i == 0 ) {
            return false;
        }
    }

    return true;
}

bool ciphers::aux::IsPrime2( unsigned long long number )
{
    if ( number < 2 ) {
        return false;
    }

    auto primes = GetPrimesLowerThenUsingEratostenesSieveApproach( number );

    for ( auto prime : primes ) {
        if ( number % prime == 0 ) {
            return false;
        }
    }

    return true;
}

unsigned long long ciphers::aux::GetRootedDecimalValueFromNumberOf( unsigned long long number )
{
    double squareRootOfNumber = std::sqrt( number );
    unsigned long long decimalPartOfNumber = static_cast<unsigned long long>(squareRootOfNumber);
    return decimalPartOfNumber;
}

std::set<unsigned long long> ciphers::aux::GetPrimesLowerThenUsingEratostenesSieveApproach( unsigned long long number )
{
    auto primes = std::set<unsigned long long>();

    if ( number < 2 ) {
        return primes;
    }

    for ( unsigned long long i = 2; i < number; i++ ) {
        primes.insert( i );
    }

    unsigned long long intervalOfNumber = GetRootedDecimalValueFromNumberOf( number ) + 1;
    bool isInSet;

    for ( unsigned long long i = 2; i < intervalOfNumber; i++ ) {
        for ( unsigned long long j = i + 1; j < number; j++ ) {
            isInSet = primes.find( j ) != primes.end();

            if ( IsNumberDivisibleBy( j, i ) && isInSet ) {
                primes.erase( j );
            }
        }
    }

    return primes;
}

bool ciphers::aux::IsNumberDivisibleBy( unsigned long long dividend, unsigned long long divider )
{
    double divisionResult = static_cast<double>(dividend) / static_cast<double>(divider);
    unsigned long long multiplicationResult = static_cast<unsigned long long>(divisionResult) * divider;

    if ( multiplicationResult == dividend ) {
        return true;
    }

    return false;
}

unsigned long long ciphers::aux::HowManyPrimesInInclusiveRangeOf( unsigned long long lowerLimit, unsigned long long upperLimit )
{
    if ( lowerLimit > upperLimit || upperLimit < 2 ) {
        return 0;
    }

    if ( lowerLimit == upperLimit ) {
        if ( IsPrime2( upperLimit ) ) {
            return 1;
        }
        else {
            return 0;
        }
    }

    unsigned long long numberOfPrimes = 0;
    auto primes = GetPrimesLowerThenUsingEratostenesSieveApproach( upperLimit + 1 );

    for ( unsigned long long i = 0; i < lowerLimit; i++ ) {
        primes.erase( i );
    }

    numberOfPrimes = static_cast<unsigned long long>(primes.size());
    return numberOfPrimes;
}

/*
 * Uses a prime counting function π(n).
 * The prime counting function π(n) is defined as the number of primes not greater or equal than n.
 *
 * The prime number theorem states that π(n) is approximately given by:
 *
 *                n
 *      π(n) = --------
 *               ln n
 *
 * Note:
 * 1. Using arguments of ('lowerLimit' <= 2) is improper.
 * 2. Using arguments of ('lowerLimit' == 'upperLimit') is improper.
 * 3. Using arguments of ('lowerLimit' > 'upperLimit') is improper.
 * 4. This is a naive approach. Study this problem in terms of the logarithms submissions.
 */
unsigned long long ciphers::aux::HowManyPrimesInInclusiveRangeOf2( unsigned long long lowerLimit, unsigned long long upperLimit )
{
    double minuend = (upperLimit + 1) / std::log( upperLimit + 1 );
    double subtrahend = (lowerLimit - 1) / std::log( lowerLimit - 1 );
    double substraction = minuend - subtrahend + 1;
    double squareRootFromDispersion = std::sqrt( upperLimit - lowerLimit );
    double result = substraction + squareRootFromDispersion;
    unsigned long long numberOfPrimes = static_cast<unsigned long long>(result + 1);
    return numberOfPrimes;
}

unsigned long long ciphers::aux::HowManyPrimesInInclusiveRangeOf3( unsigned long long lowerLimit, unsigned long long upperLimit )
{
    if ( lowerLimit > upperLimit || upperLimit < 2 ) {
        return 0;
    }

    if ( lowerLimit == upperLimit ) {
        if ( IsPrime2( upperLimit ) ) {
            return 1;
        }
        else {
            return 0;
        }
    }

    std::map<unsigned long long, bool> primes;
    unsigned long long squareRootUpperLimit = GetRootedDecimalValueFromNumberOf( upperLimit + 1 );
    unsigned long long tmp;

    for ( unsigned long long i = 2; i <= upperLimit; i++ ) {
        primes.insert( std::pair<unsigned long long, bool>( i, true ) );
    }

    for ( unsigned long long i = 2; i <= squareRootUpperLimit; i++ ) {
        if ( primes[i] == true ) {
            tmp = i + i;

            while ( tmp <= upperLimit ) {
                primes[tmp] = false;
                tmp += i;
            }
        }
    }

    unsigned long long numberOfPrimes = 0;
    std::map<unsigned long long, bool>::iterator iterator;

    for ( iterator = primes.begin(); iterator != primes.end(); ++iterator ) {
        if ( iterator->second == true && iterator->first >= lowerLimit ) {
            numberOfPrimes++;
        }
    }

    return numberOfPrimes;
}

void ciphers::PerformLucasLehmerTestForExponents( std::size_t lowerLimitExponent, std::size_t upperLimitExponent, const char * path = FILENAME_OF_LUCAS_LEHMER_TEST.c_str() )
{
    std::ofstream fileWriter;
    fileWriter.open( path, std::ios::out );

    if ( fileWriter.is_open() ) {
        const std::string TABULATOR = "\t";
        fileWriter << "Lucas-Lehmer test for checking if Mersenne numbers are primes." << std::endl;
        fileWriter << std::endl;

        for ( std::size_t i = lowerLimitExponent; i <= upperLimitExponent; i++ ) {
            uint64_t currentMarsenneNumber = aux::PowerForUInt64( 2, i ) - 1;
            bool isPrimeNumber = aux::IsPrime3( i );
            fileWriter << &std::right << std::setw( 10 ) << i << ")" << TABULATOR;
            fileWriter << &std::right << std::setw( 30 ) << currentMarsenneNumber << TABULATOR;
            fileWriter << &std::right << std::setw( 10 ) << &std::boolalpha << isPrimeNumber;
            fileWriter << std::endl;
        }

        fileWriter.close();
    }
}

/*
 * Performs Lucas-Lehmer test.
 * Mersenne number pattern: M = (2^P) - 1.
 * Should not be used for numbers that are greater than (2^32).
 */
bool ciphers::aux::IsPrime3( std::size_t marsenneNumberExponent )
{
    if ( marsenneNumberExponent == 2 ) {
        return true;
    }

    uint64_t range = PowerForUInt64( 2, marsenneNumberExponent ) - 1;
    uint64_t currentSum = 4;
    uint64_t partialResult;

    for ( std::size_t i = 0; i < marsenneNumberExponent - 2; i++ ) {
        partialResult = (currentSum * currentSum) - 2;
        currentSum = partialResult % range;
    }

    if ( currentSum != 0 ) {
        return false;
    }

    return true;
}

uint64_t ciphers::aux::PowerForUInt64( uint64_t base, uint64_t exponent )
{
    uint64_t result = 1;

    while ( exponent ) {
        if ( exponent & 1 ) {
            result *= base;
        }

        exponent >>= 1;
        base *= base;
    }

    return result;
}

unsigned long long ciphers::aux::PowerOfModuloByCongruents( unsigned long long base, unsigned long long exponent, unsigned long long modulo )
{
    unsigned long long result = 1;

    for ( unsigned long long i = 0; i < exponent; i++ ) {
        result *= base;
        result %= modulo;
    }

    return result;
}

unsigned long long ciphers::aux::PowerOfModuloByBinaryExpansion( unsigned long long base, unsigned long long exponent, unsigned long long modulo )
{
    if ( modulo == 1 || modulo > static_cast<unsigned long long>(sqrt( ULLONG_MAX - 1 )) ) {
        return 0;
    }

    unsigned long long result = 1;
    base %= modulo;

    while ( exponent > 0 ) {
        if ( exponent % 2 == 1 ) {
            result = (result * base) % modulo;
        }

        exponent = exponent >> 1;
        base = (base * base) % modulo;
    }

    return result;
}

/*
 * Resolves an equation of: ax + by = GCD(a,b).
 * GCD - Greatest Common Divider
 * EEA - Extended Euclidian Algorithm
 */
std::pair<long long, std::pair<long long, long long>> ciphers::aux::GetGCDUsingIterativeEEA( long long a, long long b )
{
    long long x = 1;
    long long y = 0;
    long long xLast = 0;
    long long yLast = 1;
    long long quotient;
    long long remainder;
    long long m;
    long long n;

    while ( a != 0 ) {
        quotient = b / a;
        remainder = b % a;
        m = xLast - quotient*x;
        n = yLast - quotient*y;
        xLast = x;
        yLast = y;
        x = m;
        y = n;
        b = a;
        a = remainder;
    }

    return std::make_pair( b, std::make_pair( xLast, yLast ) );
}

/*
 * Resolve of the equation: (ax) mod m ≡ 1. The result is x = a (mod m).
 * Time complexity: O( log (m^2) ).
 * EEA - Extended Euclidian Algorithm
 */
long long ciphers::aux::InverseModuloUsingIterativeEEA( long long a, long long m )
{
    return (GetGCDUsingIterativeEEA( a, m ).second.first + m) % m;
}

/*
* Resolves an equation of: ax + by = GCD(a,b).
* GCD - Greatest Common Divider
* EEA - Extended Euclidian Algorithm
*/
std::pair<long long, std::pair<long long, long long>> ciphers::aux::GetGCDUsingRecursiveEEA( long long a, long long b )
{
    if ( a == 0 ) {
        return std::make_pair( b, std::make_pair( 0, 1 ) );
    }

    std::pair<long long, std::pair<long long, long long>> pair;
    pair = GetGCDUsingRecursiveEEA( b % a, a );
    return std::make_pair( pair.first, std::make_pair( pair.second.second - pair.second.first * (b / a), pair.second.first ) );
}

/*
* Resolve of the equation: (ax) mod m ≡ 1. The result is x = a (mod m).
* Time complexity: O( log (m^2) ).
* EEA - Extended Euclidian Algorithm
*/
long long ciphers::aux::InverseModuloUsingRecursiveEEA( long long a, long long m )
{
    return (GetGCDUsingRecursiveEEA( a, m ).second.first + m) % m;
}

/*
 * Calculates (base^exponent) mod modulo.
 * Uses binary expansion. Designed to used for FLT (Fermat's Little Theorem) algorithms.
 */
long long ciphers::aux::PowerOfModuloByFLT( long long base, long long exponent, long long modulo )
{
    long long x = 1;
    long long y = base;

    while ( exponent > 0 ) {
        if ( exponent % 2 == 1 ) {
            x = x*y;

            if ( x > modulo ) {
                x %= modulo;
            }
        }

        y = y*y;

        if ( y > modulo ) {
            y %= modulo;
        }

        exponent /= 2;
    }

    return x;
}

/*
 * m - must be a prime
 * a - must be an integer co-prime
 * Resolve of the equation: (ax) mod m ≡ 1. The result is x = a (mod m).
 * If 'm' is not a prime and 'a' is not a co-prime, then the result will be: (a^(m-2)) mod m.
 * Time complexity: O( log (m) ).
 * FLT - Fermat's Little Theorem
 */
long long ciphers::aux::InverseModuloUsingFLT( long long a, long long m )
{
    return PowerOfModuloByFLT( a, m - 2, m );
}
