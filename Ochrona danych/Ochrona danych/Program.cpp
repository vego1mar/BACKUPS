#include "Program.hpp"
#include "Ciphers.hpp"
#include "DFProtocol.hpp"
#include "RSA.hpp"
#include <fstream>
#include <iomanip>
#include <chrono>
#include <random>

void program::RunWithArguments( int argc, char * argv[] )
{
    if ( argc > 1 ) {
        ciphers::EncryptOrDecryptCesarLikeCipherFromStdIn( std::atoi( argv[argc - 1] ) );
    }
}

void program::RunForCesarCipherAnalysisDecryption()
{
    const std::string CATALOG_RELATIVE_PATH = "test\\AnalysisOfCesarCipher\\";
    const std::string PATTERN_FILENAME = "Kafka_pattern.txt";
    const std::string CIPHER_FILENAME = "Pangram_cipher.txt";
    const std::string CIPHER_PATH = CATALOG_RELATIVE_PATH + CIPHER_FILENAME;
    const std::string RESULT_PATH = CATALOG_RELATIVE_PATH + ciphers::FILENAME_OF_RESULT_STATISTICS;
    int offset = ciphers::PerformStatisticalAnalysisOfCesarLikeCipher( CATALOG_RELATIVE_PATH, PATTERN_FILENAME.c_str(), CIPHER_FILENAME.c_str() );
    ciphers::aux::TryToDecryptAndSaveMessageToFile( offset, CIPHER_PATH.c_str(), RESULT_PATH.c_str() );
}

void program::RunExtendedVigenereEncryptionAndDecryption()
{
    const std::string CATALOG_RELATIVE_PATH = "test\\ExtendedVigenereCipher\\";
    const std::string KEY_FILENAME = CATALOG_RELATIVE_PATH + "vigenere_key.txt";
    const std::string MESSAGE_FILENAME = CATALOG_RELATIVE_PATH + "vigenere_message.txt";
    const std::string CIPHER_FILENAME = CATALOG_RELATIVE_PATH + ciphers::FILENAME_OF_EXTENDED_VIGENERE_CIPHER_TEXT;
    const std::string PLAINTEXT_FILENAME = CATALOG_RELATIVE_PATH + ciphers::FILENAME_OF_EXTENDED_VIGENERE_PLAIN_TEXT;
    std::string encryptedMessage = ciphers::EncryptUsingExtendedVigenereCipher( KEY_FILENAME.c_str(), MESSAGE_FILENAME.c_str() );
    ciphers::aux::SaveMessageToFile( encryptedMessage, CIPHER_FILENAME.c_str() );
    std::string decryptedMessage = ciphers::DecryptUsingExtendedVigenereCipher( KEY_FILENAME.c_str(), CIPHER_FILENAME.c_str() );
    ciphers::aux::SaveMessageToFile( decryptedMessage, PLAINTEXT_FILENAME.c_str() );
}

void program::RunKasiskiTestOfGuessingLengthOfVigenereLikeCipher()
{
    const std::string CATALOG_RELATIVE_PATH = "test\\KasiskiTestOfVigenereCipher\\";
    const std::string CIPHERTEXT_FILENAME = CATALOG_RELATIVE_PATH + "ciphertext.txt";
    const std::string RESULT_STATS = CATALOG_RELATIVE_PATH + ciphers::FILENAME_OF_STATS_FROM_KASISKI_TEST;
    const short KEY_BLOCK_LENGTH = ciphers::MINIMUM_BLOCK_LENGTH;
    const std::size_t STATS_OF_DIVISORS_LENGTH = ciphers::aux::DIVISORS_ARRAY_MINIMUM_SIZE;
    long * statsOfDivisors = new long[STATS_OF_DIVISORS_LENGTH];
    long keyLength = ciphers::PerformKasiskiTestOfVigenereLikeCipher( CIPHERTEXT_FILENAME.c_str(), KEY_BLOCK_LENGTH, statsOfDivisors, STATS_OF_DIVISORS_LENGTH );
    ciphers::aux::SaveStatsFromKasiskiTestIntoFile( RESULT_STATS.c_str(), statsOfDivisors, STATS_OF_DIVISORS_LENGTH, keyLength );
    delete[] statsOfDivisors;
}

void program::RunTestForNumberOfPrimesBetweenSpecifiedRange( unsigned long long lowerLimit, unsigned long long upperLimit )
{
    auto timeOfStart = std::chrono::high_resolution_clock::now();
    auto result = ciphers::aux::HowManyPrimesInInclusiveRangeOf3( lowerLimit, upperLimit );
    auto timeOfEnd = std::chrono::high_resolution_clock::now();
    auto timeResultNanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(timeOfEnd - timeOfStart).count();
    auto timeResultSeconds = std::chrono::duration_cast<std::chrono::seconds>(timeOfEnd - timeOfStart).count();

    std::ofstream fileWriter;
    const std::streamsize WIDTH = 25;
    fileWriter.open( "test\\PrimesInRange\\primes_result.txt", std::ios::out );

    if ( fileWriter.is_open() ) {
        fileWriter << "Lower limit:     " << &std::right << std::setw( WIDTH ) << lowerLimit << std::endl;
        fileWriter << "Upper limit:     " << &std::right << std::setw( WIDTH ) << upperLimit << std::endl;
        fileWriter << "Primes in range: " << &std::right << std::setw( WIDTH ) << result << std::endl;
        fileWriter << std::endl;
        fileWriter << "Program finished after " << timeResultNanoseconds << " nanoseconds." << std::endl;
        fileWriter << "Program finished after " << timeResultSeconds << " seconds." << std::endl;
        fileWriter.close();
    }
}

void program::RunLucasLehmerTest()
{
    const std::string CATALOG_RELATIVE_PATH = "test\\LucasLehmerTest\\";
    const std::string LUCAS_LEHMER_TEST_FILENAME = CATALOG_RELATIVE_PATH + ciphers::FILENAME_OF_LUCAS_LEHMER_TEST;
    ciphers::PerformLucasLehmerTestForExponents( 2, 32, LUCAS_LEHMER_TEST_FILENAME.c_str() );
}

void program::RunPowerOfModuloCountingTest()
{
    const unsigned long NUMBER_OF_DIGITS = 10;
    const unsigned long long LOWER_LIMIT = 1000000;
    const unsigned long long UPPER_LIMIT = 1000000000;
    std::mt19937 generator;
    generator.seed( std::random_device()() );
    std::uniform_int_distribution<std::mt19937::result_type> distribution( LOWER_LIMIT, UPPER_LIMIT );
    unsigned long long resultOfCongruentialExponentiation;
    unsigned long long resultOfBinaryExpansion;
    std::chrono::time_point<std::chrono::steady_clock> timeOfStart;
    std::chrono::time_point<std::chrono::steady_clock> timeOfEnd;
    long long timeOfCongruentialExponentiation;
    long long timeOfBinaryExpansion;
    std::ofstream fileWriter;
    fileWriter.open( "test\\PowerOfModulo\\powmod_test.txt", std::ios::out );
    const std::string TABULATOR = "\t";
    const short WIDTH = 11;

    if ( fileWriter.is_open() ) {
        short headerWidth = 4;
        resultOfBinaryExpansion = ciphers::aux::PowerOfModuloByBinaryExpansion( 123, 456, 789 );
        fileWriter << " 123 ^  456 mod  789 =  699; returned: " << &std::right << std::setw( headerWidth ) << resultOfBinaryExpansion << std::endl;
        resultOfBinaryExpansion = ciphers::aux::PowerOfModuloByBinaryExpansion( 23, 1, 19 );
        fileWriter << "  23 ^    1 mod   19 =    4; returned: " << &std::right << std::setw( headerWidth ) << resultOfBinaryExpansion << std::endl;
        resultOfBinaryExpansion = ciphers::aux::PowerOfModuloByBinaryExpansion( 256, 40, 100 );
        fileWriter << " 256 ^   40 mod  100 =   76; returned: " << &std::right << std::setw( headerWidth ) << resultOfBinaryExpansion << std::endl;
        resultOfBinaryExpansion = ciphers::aux::PowerOfModuloByBinaryExpansion( 4321, 5678, 9876 );
        fileWriter << "4321 ^ 5678 mod 9876 = 8941; returned: " << &std::right << std::setw( headerWidth ) << resultOfBinaryExpansion << std::endl;
        fileWriter << std::endl;
        fileWriter.flush();

        for ( unsigned long i = 0; i < NUMBER_OF_DIGITS; i++ ) {
            unsigned long long randomBase = distribution( generator );
            unsigned long long randomExponent = distribution( generator );
            unsigned long long randomModulo = distribution( generator );
            fileWriter << &std::right << std::setw( WIDTH ) << randomBase << " ^ ";
            fileWriter << &std::right << std::setw( WIDTH ) << randomExponent << " mod ";
            fileWriter << &std::right << std::setw( WIDTH ) << randomModulo << " = ";
            fileWriter.flush();
            timeOfStart = std::chrono::high_resolution_clock::now();
            resultOfCongruentialExponentiation = ciphers::aux::PowerOfModuloByCongruents( randomBase, randomExponent, randomModulo );
            timeOfEnd = std::chrono::high_resolution_clock::now();
            timeOfCongruentialExponentiation = std::chrono::duration_cast<std::chrono::nanoseconds>(timeOfEnd - timeOfStart).count();
            timeOfStart = std::chrono::high_resolution_clock::now();
            resultOfBinaryExpansion = ciphers::aux::PowerOfModuloByBinaryExpansion( randomBase, randomExponent, randomModulo );
            timeOfEnd = std::chrono::high_resolution_clock::now();
            timeOfBinaryExpansion = std::chrono::duration_cast<std::chrono::nanoseconds>(timeOfEnd - timeOfStart).count();
            fileWriter << &std::right << std::setw( WIDTH ) << resultOfCongruentialExponentiation << ",";
            fileWriter << &std::right << std::setw( WIDTH ) << resultOfBinaryExpansion;
            fileWriter << TABULATOR << "(" << &std::right << std::setw( WIDTH ) << timeOfCongruentialExponentiation << " ns,";
            fileWriter << &std::right << std::setw( WIDTH ) << timeOfBinaryExpansion << " ns)" << std::endl;
            fileWriter.flush();
        }

        fileWriter.close();
    }
}

void program::RunTestOfDiffieHellmanProtocolKeysExchange()
{
    const df::ullong PRIME_FOR_ALICE_AND_EVE = 16699;
    const df::ullong GENERATOR_FOR_ALICE_AND_EVE = 21232123;
    const df::ullong PRIME_FOR_BOB_AND_EVE = 16603;
    const df::ullong GENERATOR_FOR_BOB_AND_EVE = 32123212;
    df::DFProtocol alice;
    df::DFProtocol bob;
    df::DFProtocol eveToAlice;
    df::DFProtocol eveToBob;
    df::DFProtocol::UseDiffieHellmanProtocol( PRIME_FOR_ALICE_AND_EVE, GENERATOR_FOR_ALICE_AND_EVE, alice, eveToAlice );
    df::DFProtocol::UseDiffieHellmanProtocol( PRIME_FOR_BOB_AND_EVE, GENERATOR_FOR_BOB_AND_EVE, bob, eveToBob );
    std::ofstream fileWriter;
    fileWriter.open( "test\\DiffieHellmanMITM\\df_mitm.txt", std::ios::out );

    if ( fileWriter.is_open() ) {
        const int WIDTH = 20;
        const std::string TABULATOR = "\t";
        fileWriter << &std::left << std::setw( WIDTH ) << "Alice" << TABULATOR << "Eve" << &std::left << std::setw( WIDTH ) << std::endl;
        std::string v1 = "p=" + std::to_string( alice.getPrime() );
        std::string v2 = "p=" + std::to_string( eveToAlice.getPrime() );
        fileWriter << &std::left << std::setw( WIDTH ) << v1 << TABULATOR << &std::left << std::setw( WIDTH ) << v2 << std::endl;
        v1 = "g=" + std::to_string( alice.getGenerator() );
        v2 = "g=" + std::to_string( eveToAlice.getGenerator() );
        fileWriter << &std::left << std::setw( WIDTH ) << v1 << TABULATOR << &std::left << std::setw( WIDTH ) << v2 << std::endl;
        v1 = "k=" + std::to_string( alice.getSessionKey() );
        v2 = "k=" + std::to_string( eveToAlice.getSessionKey() );
        fileWriter << &std::left << std::setw( WIDTH ) << v1 << TABULATOR << &std::left << std::setw( WIDTH ) << v2 << std::endl;
        v1 = "a=" + std::to_string( alice.getMyPrivateKey() );
        v2 = "e=" + std::to_string( eveToAlice.getMyPrivateKey() );
        fileWriter << &std::left << std::setw( WIDTH ) << v1 << TABULATOR << &std::left << std::setw( WIDTH ) << v2 << std::endl;
        v1 = "A=" + std::to_string( alice.getMyPublicKey() );
        v2 = "E=" + std::to_string( eveToAlice.getMyPublicKey() );
        fileWriter << &std::left << std::setw( WIDTH ) << v1 << TABULATOR << &std::left << std::setw( WIDTH ) << v2 << std::endl;
        v1 = "E=" + std::to_string( alice.getHandshakedExternalPublicKey() );
        v2 = "A=" + std::to_string( eveToAlice.getHandshakedExternalPublicKey() );
        fileWriter << &std::left << std::setw( WIDTH ) << v1 << TABULATOR << &std::left << std::setw( WIDTH ) << v2 << std::endl;
        fileWriter << std::endl << std::endl;
        fileWriter << &std::left << std::setw( WIDTH ) << "Eve" << TABULATOR << "Bob" << &std::left << std::setw( WIDTH ) << std::endl;
        v1 = "p=" + std::to_string( eveToBob.getPrime() );
        v2 = "p=" + std::to_string( bob.getPrime() );
        fileWriter << &std::left << std::setw( WIDTH ) << v1 << TABULATOR << &std::left << std::setw( WIDTH ) << v2 << std::endl;
        v1 = "g=" + std::to_string( eveToBob.getGenerator() );
        v2 = "g=" + std::to_string( bob.getGenerator() );
        fileWriter << &std::left << std::setw( WIDTH ) << v1 << TABULATOR << &std::left << std::setw( WIDTH ) << v2 << std::endl;
        v1 = "k=" + std::to_string( eveToBob.getSessionKey() );
        v2 = "k=" + std::to_string( bob.getSessionKey() );
        fileWriter << &std::left << std::setw( WIDTH ) << v1 << TABULATOR << &std::left << std::setw( WIDTH ) << v2 << std::endl;
        v1 = "e=" + std::to_string( eveToBob.getMyPrivateKey() );
        v2 = "b=" + std::to_string( bob.getMyPrivateKey() );
        fileWriter << &std::left << std::setw( WIDTH ) << v1 << TABULATOR << &std::left << std::setw( WIDTH ) << v2 << std::endl;
        v1 = "E=" + std::to_string( eveToBob.getMyPublicKey() );
        v2 = "B=" + std::to_string( bob.getMyPublicKey() );
        fileWriter << &std::left << std::setw( WIDTH ) << v1 << TABULATOR << &std::left << std::setw( WIDTH ) << v2 << std::endl;
        v1 = "B=" + std::to_string( eveToBob.getHandshakedExternalPublicKey() );
        v2 = "E=" + std::to_string( bob.getHandshakedExternalPublicKey() );
        fileWriter << &std::left << std::setw( WIDTH ) << v1 << TABULATOR << &std::left << std::setw( WIDTH ) << v2 << std::endl;
        fileWriter.close();
    }
}

void program::RunRSAAlgorithm()
{
    std::ofstream fileWriter;
    fileWriter.open( "test\\RSA\\rsa_test.txt", std::ios::out );

    if ( fileWriter.is_open() ) {
        rsa::RSA crypter;
        crypter.setPrimeP( 1033 );
        crypter.setPrimeQ( 2069 );
        crypter.setMessage( "The quick, brown fox jumps over a lazy dog." );
        crypter.countKeyPairs();
        crypter.encrypt();
        const std::streamsize WIDTH = 23;
        fileWriter << " p = " << &std::right << std::setw( WIDTH ) << crypter.getPrimeP() << std::endl;
        fileWriter << " q = " << &std::right << std::setw( WIDTH ) << crypter.getPrimeQ() << std::endl;
        fileWriter << " n = " << &std::right << std::setw( WIDTH ) << crypter.getPublicKey().primesTotient << std::endl;
        rsa::ullong fi = (crypter.getPrimeP() - 1) * (crypter.getPrimeQ() - 1);
        fileWriter << " t = " << &std::right << std::setw( WIDTH ) << fi << std::endl;
        fileWriter << " e = " << &std::right << std::setw( WIDTH ) << crypter.getPublicKey().key << std::endl;
        fileWriter << " d = " << &std::right << std::setw( WIDTH ) << crypter.getPrivateKey().key << std::endl;
        fileWriter << std::endl;
        fileWriter << "m = " << crypter.getMessage() << std::endl;
        fileWriter << "c = " << crypter.getCipherString() << std::endl;
        fileWriter << "M = " << crypter.decrypt() << std::endl;
        fileWriter << std::endl;
        fileWriter.close();
    }
}
