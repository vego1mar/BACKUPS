#include "Data.h"

#include <cstring>
#include <cstdio>

// ______________________________________________________________________________________

Data::Data(const char * _T)
    : T()

{
// Clearing the data array.
memset(T,0,SIZE*sizeof(char));

// :: Checking for absorption.
if (_T != nullptr)
    {
    // Checking the string size.
    size_t size = strlen(_T);

    if ((size > 0) && (size < SIZE))
        {
        // Copying the data.
        memcpy(T,_T,size*sizeof(char));
        };
    };
};

// ______________________________________________________________________________________

Data::Data(char _ch)
    : T()
{
// Fullfilling the array with a given character.
memset(T,_ch,SIZE*sizeof(char));

// Explicit trimming at the last element of the array.
T[SIZE-1] = '\0';
};

// ______________________________________________________________________________________

Data::~Data()
{
// Clearing the memory.
memset(T,0,SIZE*sizeof(char));
};

// ______________________________________________________________________________________

Data::operator Data() const
{
return (Data());
};

// ______________________________________________________________________________________

Data::Data()
    : T()

{
// Clearing the data array.
memset(T,0,SIZE*sizeof(char));
};

// ______________________________________________________________________________________

Data::Data(const Data & _rvalue)
    : T()

{
// Copying the data.
memcpy(T,_rvalue.T,SIZE*sizeof(char));
};

// ______________________________________________________________________________________

Data & Data::operator= (const Data & _rvalue)
{
// Copying the data.
memcpy(T,_rvalue.T,SIZE*sizeof(char));

return (*this);
};

// ______________________________________________________________________________________

const char * Data::Get() const
{
// Declaration of a static C-style string.
static char tmp[SIZE] = {0};

// Clearing the static C-style string.
memset(tmp,0,SIZE*sizeof(char));

// Copying the data from a pole.
sprintf(tmp,"%s",T);

return (tmp);
};

// ______________________________________________________________________________________

void Data::Set(const char * _string)
{
// :: Checking the pointer.
if (_string != nullptr)
    {
    // Checking the string size.
    size_t size = strlen(_string);

    // :: Checking for the absorption.
    if ((size > 0) && (size < SIZE))
        {
        // Clearing the data array.
        memset(T,0,SIZE*sizeof(char));

        // Copying the data.
        memcpy(T,_string,size*sizeof(char));
        };
    };
};

// ______________________________________________________________________________________
