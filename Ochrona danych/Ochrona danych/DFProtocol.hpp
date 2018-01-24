#ifndef DF_PROTOCOL_HPP
#define DF_PROTOCOL_HPP

#include <random>

namespace df
{
    typedef unsigned long long int ullong;

    class DFProtocol
    {

    private:
        ullong prime;
        ullong generator;
        ullong sessionKey;
        static std::mt19937 engine;
        ullong myPrivateKey;
        ullong myPublicKey;
        ullong externalPublicKey;

    public:
        DFProtocol();
        ~DFProtocol() = default;

    private:
        DFProtocol( const DFProtocol & rhs ) = default;
        DFProtocol & operator=( const DFProtocol & rhs );

    public:
        static bool AgreeKeysExchangeChannelData( ullong prime, ullong generator, DFProtocol & alice, DFProtocol & bob );
        static void ExchangeSessionKey( DFProtocol & alice, DFProtocol & bob );
        static bool UseDiffieHellmanProtocol( ullong prime, ullong generator, DFProtocol & alice, DFProtocol & bob );

        void setPrime( ullong primeNumber );
        void setGenerator( ullong generatorNumber );
        void setExternalPublicKey( ullong publicKey );
        ullong getPrime();
        ullong getGenerator();
        ullong getSessionKey();
        ullong getMyPrivateKey();
        ullong getMyPublicKey();
        ullong getHandshakedExternalPublicKey();

        ullong countMyPublicKey();
        void sendMyPublicKeyTo( DFProtocol & target );
        ullong countSessionKey();
        ullong getRandomPrivateKey();

    };
}

#endif // !DF_PROTOCOL_HPP
