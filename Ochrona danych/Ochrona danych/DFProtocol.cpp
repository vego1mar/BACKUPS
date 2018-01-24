#include "DFProtocol.hpp"
#include "Ciphers.hpp"
#include <climits>

std::mt19937 df::DFProtocol::engine;

df::DFProtocol::DFProtocol()
    : prime( 8191 )
    , generator( 1111 )
    , sessionKey( 0 )
    , myPrivateKey( 0 )
    , myPublicKey( 0 )
    , externalPublicKey( 0 )
{
    engine.seed( std::random_device()() );
    getRandomPrivateKey();
    countMyPublicKey();
}

df::DFProtocol & df::DFProtocol::operator=( const DFProtocol & rhs )
{
    if ( &rhs != this ) {
        prime = rhs.prime;
        generator = rhs.generator;
        sessionKey = rhs.sessionKey;
        myPrivateKey = rhs.myPrivateKey;
        myPublicKey = rhs.myPublicKey;
        externalPublicKey = rhs.externalPublicKey;
    }

    return *this;
}

bool df::DFProtocol::AgreeKeysExchangeChannelData( ullong prime, ullong generator, DFProtocol & alice, DFProtocol & bob )
{
    if ( !ciphers::aux::IsPrime2( prime ) ) {
        return false;
    }

    alice.setPrime( prime );
    alice.setGenerator( generator );
    bob.setPrime( prime );
    bob.setGenerator( generator );
    return true;
}

void df::DFProtocol::ExchangeSessionKey( DFProtocol & alice, DFProtocol & bob )
{
    alice.getRandomPrivateKey();
    alice.countMyPublicKey();
    bob.getRandomPrivateKey();
    bob.countMyPublicKey();
    alice.sendMyPublicKeyTo( bob );
    bob.sendMyPublicKeyTo( alice );
    alice.countSessionKey();
    bob.countSessionKey();
}

bool df::DFProtocol::UseDiffieHellmanProtocol( ullong prime, ullong generator, DFProtocol & alice, DFProtocol & bob )
{
    if ( AgreeKeysExchangeChannelData( prime, generator, alice, bob ) ) {
        ExchangeSessionKey( alice, bob );
        return true;
    }

    return false;
}

void df::DFProtocol::setPrime( ullong primeNumber )
{
    prime = primeNumber;
}

void df::DFProtocol::setGenerator( ullong generatorNumber )
{
    generator = generatorNumber;
}

void df::DFProtocol::setExternalPublicKey( ullong publicKey )
{
    externalPublicKey = publicKey;
}

df::ullong df::DFProtocol::getPrime()
{
    return prime;
}

df::ullong df::DFProtocol::getGenerator()
{
    return generator;
}

df::ullong df::DFProtocol::getSessionKey()
{
    return sessionKey;
}

df::ullong df::DFProtocol::getMyPrivateKey()
{
    return myPrivateKey;
}

df::ullong df::DFProtocol::getMyPublicKey()
{
    return myPublicKey;
}

df::ullong df::DFProtocol::getHandshakedExternalPublicKey()
{
    return externalPublicKey;
}

df::ullong df::DFProtocol::countMyPublicKey()
{
    myPublicKey = ciphers::aux::PowerOfModuloByBinaryExpansion( generator, myPrivateKey, prime );
    return myPublicKey;
}

void df::DFProtocol::sendMyPublicKeyTo( DFProtocol & target )
{
    target.setExternalPublicKey( myPublicKey );
}

df::ullong df::DFProtocol::countSessionKey()
{
    sessionKey = ciphers::aux::PowerOfModuloByBinaryExpansion( externalPublicKey, myPrivateKey, prime );
    return sessionKey;
}

df::ullong df::DFProtocol::getRandomPrivateKey()
{
    std::uniform_int_distribution<std::mt19937::result_type> distribution( 1, UINT32_MAX );
    myPrivateKey = distribution( engine );
    return myPrivateKey;
}
