#include "RSA.hpp"
#include "Ciphers.hpp"

rsa::RSA::RSA()
    : primeP( 2027 )
    , primeQ( 6661 )
    , message( std::string() )
    , cipher( std::vector<ullong>() )
    , generator()
    , publicKey()
    , privateKey()
{
    generator.seed( std::random_device()() );
    countKeyPairs();
}

rsa::RSA & rsa::RSA::operator= ( const RSA & rhs )
{
    if ( &rhs != this ) {
        primeP = rhs.primeP;
        primeQ = rhs.primeQ;
        message = rhs.message;
        cipher = rhs.cipher;
        generator = rhs.generator;
        publicKey = rhs.publicKey;
        privateKey = rhs.privateKey;
    }

    return *this;
}

rsa::ullong rsa::RSA::getPrimeP()
{
    return primeP;
}

rsa::ullong rsa::RSA::getPrimeQ()
{
    return primeQ;
}

std::string rsa::RSA::getMessage()
{
    return message;
}

std::vector<rsa::ullong> rsa::RSA::getCipher()
{
    return cipher;
}

std::string rsa::RSA::getCipherString()
{
    std::string cipherString;

    for ( std::size_t i = 0; i < cipher.size(); i++ ) {
        cipherString += std::to_string( cipher[i] );
        cipherString += ',';
    }

    cipherString.pop_back();
    return cipherString;
}

rsa::RSAKey rsa::RSA::getPublicKey()
{
    return publicKey;
}

rsa::RSAKey rsa::RSA::getPrivateKey()
{
    return privateKey;
}

bool rsa::RSA::setPrimeP( ullong prime )
{
    if ( ciphers::aux::IsPrime2( prime ) ) {
        primeP = prime;
        return true;
    }

    return false;
}

bool rsa::RSA::setPrimeQ( ullong prime )
{
    if ( ciphers::aux::IsPrime2( prime ) ) {
        primeQ = prime;
        return true;
    }

    return false;
}

void rsa::RSA::setMessage( std::string newMessage )
{
    message = newMessage;
}

void rsa::RSA::countKeyPairs()
{
    ullong n = primeP * primeQ;
    ullong fi = (primeP - 1) * (primeQ - 1);
    uint e = 0;
    std::pair<llong, std::pair<llong, llong>> gcd;
    gcd.first = 0;

    while ( gcd.first != 1 ) {
        e = getRandomNumber( 2, static_cast<rsa::uint>(fi - 1) );
        gcd = ciphers::aux::GetGCDUsingRecursiveEEA( e, fi );
    }

    publicKey.primesTotient = n;
    publicKey.key = e;
    llong d = ciphers::aux::InverseModuloUsingRecursiveEEA( e, fi );
    privateKey.primesTotient = n;
    privateKey.key = d;
}

void rsa::RSA::encrypt()
{
    cipher.clear();
    cipher.reserve( message.size() );

    for ( std::size_t i = 0; i < message.size(); i++ ) {
        ullong characterCipher = ciphers::aux::PowerOfModuloByBinaryExpansion( std::abs( message[i] ), publicKey.key, publicKey.primesTotient );
        cipher.push_back( characterCipher );
    }
}

std::string rsa::RSA::decrypt()
{
    std::string decryptedMessage;
    decryptedMessage.reserve( message.size() );

    for ( std::size_t i = 0; i < cipher.size(); i++ ) {
        ullong characterPlainText = ciphers::aux::PowerOfModuloByBinaryExpansion( cipher[i], privateKey.key, privateKey.primesTotient );
        char characterConversion = static_cast<char>(characterPlainText);
        std::string textToAppend;
        textToAppend = characterConversion;
        decryptedMessage.append( textToAppend );
    }

    return decryptedMessage;
}

rsa::uint rsa::RSA::getRandomNumber( uint leftLimit, uint rightLimit )
{
    std::uniform_int_distribution<std::mt19937::result_type> distribution( leftLimit, rightLimit );
    return distribution( generator );
}
