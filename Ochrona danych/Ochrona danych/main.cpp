#include "Program.hpp"

/*
 * Default command arguments:
 * $(TargetPath) 0< test/Arguments/input.txt 1> test/Arguments/output.txt
 */

int main( int argc, char * argv[] )
{
    //program::RunWithArguments( argc, argv );
    //program::RunForCesarCipherAnalysisDecryption();
    //program::RunExtendedVigenereEncryptionAndDecryption();
    //program::RunKasiskiTestOfGuessingLengthOfVigenereLikeCipher();
    //program::RunTestForNumberOfPrimesBetweenSpecifiedRange( 10000000, 11000000 );
    //program::RunLucasLehmerTest();
    //program::RunPowerOfModuloCountingTest();
    //program::RunTestOfDiffieHellmanProtocolKeysExchange();
    program::RunRSAAlgorithm();
    return 0;
}
