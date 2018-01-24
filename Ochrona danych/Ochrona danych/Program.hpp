#ifndef PROGRAM_HPP
#define PROGRAM_HPP

namespace program
{
    #pragma region Interface
    void RunWithArguments( int argc, char * argv[] );
    void RunForCesarCipherAnalysisDecryption();
    void RunExtendedVigenereEncryptionAndDecryption();
    void RunKasiskiTestOfGuessingLengthOfVigenereLikeCipher();
    void RunTestForNumberOfPrimesBetweenSpecifiedRange( unsigned long long lowerLimit, unsigned long long upperLimit );
    void RunLucasLehmerTest();
    void RunPowerOfModuloCountingTest();
    void RunTestOfDiffieHellmanProtocolKeysExchange();
    void RunRSAAlgorithm();
    #pragma endregion
}

#endif // !PROGRAM_HPP
