#ifndef RSA_HPP
#define RSA_HPP

#include <cstddef>
#include <string>
#include <random>
#include <vector>

namespace rsa
{
    typedef unsigned long long int ullong;
    typedef long long int llong;
    typedef unsigned int uint;

    struct RSAKey
    {
        ullong primesTotient;
        llong key;
    };

    class RSA
    {

    private:
        ullong primeP;
        ullong primeQ;
        std::string message;
        std::vector<ullong> cipher;
        std::mt19937 generator;
        RSAKey publicKey;
        RSAKey privateKey;

    public:
        RSA();
        ~RSA() = default;

        ullong getPrimeP();
        ullong getPrimeQ();
        std::string getMessage();
        std::vector<ullong> getCipher();
        std::string getCipherString();
        RSAKey getPublicKey();
        RSAKey getPrivateKey();
        bool setPrimeP( ullong prime );
        bool setPrimeQ( ullong prime );
        void setMessage( std::string newMessage );

        void countKeyPairs();
        void encrypt();
        std::string decrypt();

    private:
        RSA( const RSA & rhs ) = default;
        RSA & operator= ( const RSA & rhs );

        uint getRandomNumber( uint leftLimit, uint rightLimit );

    };
}

#endif // !RSA_HPP
