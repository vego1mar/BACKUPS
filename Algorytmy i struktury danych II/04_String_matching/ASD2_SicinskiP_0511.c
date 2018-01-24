// A simple implementation of the Karp-Rabin string matching algorithm.
// Microsoft Visual Studio 2010 Express (10.0.40219.1.SP1Rel).

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// ___________________________________________________________________________________________________________________

#define MAX_SIZE 346551
#define DIGIT_SIZE 256
#define BASE 71

// ___________________________________________________________________________________________________________________

typedef enum _Bool_ { FALSE = 0, TRUE = 1 } BOOLEAN;

// ___________________________________________________________________________________________________________________

// Read the string from the standard input and store it at a pointed data structure.
void ReadInputData( char (*) );

// Gives the power of the argument using '10' decimal number as a base.
unsigned long long int PowerBase10( unsigned short int );

// Gives the power of the argument using 'BASE' predefined number as a base.
unsigned long long int PowerBaseDefined( unsigned short int );

// Giving the definition of the digits of the pattern.
void DigitsDefinition( char (*), BOOLEAN );

// A procedure for giving the right interpretation of the unregular character of 852 code page.
void PrintHelper( const char * );

// Analyze the right bounds of the value of the defined character.
unsigned short int CharacterHandler( const char (*), char );

// Recommended function for counting the remainder of the specified fraction giving its elements.
unsigned long long int Remainder( const unsigned long long int, const unsigned long long int );

// Preprocessing procedure #1 for the Karp-Rabin string matching algorithm (used with FALSE argument).
void StringToDigitsConvertion( const char *, unsigned long long int *, const char (*), const size_t );

// Preprocessing procedure #2 for the Karp-Rabin string matching algorithm (used with TRUE argument).
void StringToDigitsConvertion2( const char *, unsigned long long int *, const char (*), const size_t );

// A procedure of the Karp-Rabin string matching algorithm.
void KarpRabinAlgorithm( const char *, const char (*), const char (*), BOOLEAN );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
// Declarations.
char (*Digit) = (char (*))calloc(DIGIT_SIZE,DIGIT_SIZE*sizeof(char));
char (*str) = (char (*))malloc(MAX_SIZE*sizeof(char));

// Clearing the data structure.
memset(str,0,MAX_SIZE*sizeof(char));

// Reading the string data.
ReadInputData( str );

if ( strnlen(str,MAX_SIZE) < 10100 )
    {
    DigitsDefinition( Digit, FALSE );
    KarpRabinAlgorithm("ACGTACGT",Digit,str,FALSE);
    }
else
    {
    DigitsDefinition( Digit, TRUE );
    KarpRabinAlgorithm("dziêcielin",Digit,str,TRUE);
    };

// Deallocating the memory.
free(Digit);
free(str);

// Cancelling the pointers.
Digit = NULL;
str = NULL;

// Exiting.
return ( 0 );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ReadInputData( char ( * _str ) )
{
// Validating the pointer.
if ( _str != NULL )
    {
    /* fscanf(stdin,"%s[^\n]",_str); */
    fgets(_str,MAX_SIZE,stdin);
    }
else
    {
    fputs("Error during data read.\n",stderr);
    abort();
    };
};

// ___________________________________________________________________________________________________________________

unsigned long long int PowerBase10( unsigned short int _exponent )
{
// Declarations.
unsigned short int i;
register unsigned long long int power = 1;

// Calculating.
for ( i=0; i<_exponent; i=i+1 )
    {
    power = power * 10;
    };

// Exiting.
return ( power );
};

// ___________________________________________________________________________________________________________________

unsigned long long int PowerBaseDefined( unsigned short int _exponent )
{
// Declarations.
unsigned short int i;
register unsigned long long int power = 1;
const unsigned short int base = (unsigned short int)(BASE);

// Calculating.
for ( i=0; i<_exponent; i=i+1 )
    {
    power = power * base;
    };

// Exiting.
return ( power );
};

// ___________________________________________________________________________________________________________________

void DigitsDefinition( char ( * _Digit ), BOOLEAN _set )
{
// Validating the pointer.
if ( _Digit != NULL )
    {
    if ( _set == FALSE )
        {
        // Defining the first set.
        _Digit['A'] = 1;
        _Digit['C'] = 2;
        _Digit['G'] = 3;
        _Digit['T'] = 4;
        }
    else
    if ( _set == TRUE )
        {
        // Defining the second set.
        _Digit['A'] = 'A';
        _Digit['#'] = '#'; // '¥'
        _Digit['a'] = 'a';
        _Digit['$'] = '$'; // '¹'
        _Digit['B'] = 'B';
        _Digit['b'] = 'b';
        _Digit['C'] = 'C';
        _Digit['%'] = '%'; // 'Æ'
        _Digit['c'] = 'c';
        _Digit['&'] = '&'; // 'æ'
        _Digit['D'] = 'D';
        _Digit['d'] = 'd';
        _Digit['E'] = 'E';
        _Digit['~'] = '~'; // 'Ê'
        _Digit['e'] = 'e';
        _Digit['('] = '('; // 'ê'
        _Digit['F'] = 'F';
        _Digit['f'] = 'f';
        _Digit['G'] = 'G';
        _Digit['g'] = 'g';
        _Digit['H'] = 'H';
        _Digit['h'] = 'h';
        _Digit['I'] = 'I';
        _Digit['i'] = 'i';
        _Digit['J'] = 'J';
        _Digit['j'] = 'j';
        _Digit['K'] = 'K';
        _Digit['k'] = 'k';
        _Digit['L'] = 'L';
        _Digit['l'] = 'l';
        _Digit[')'] = ')'; // '£'
        _Digit['*'] = '*'; // '³'
        _Digit['M'] = 'M';
        _Digit['m'] = 'm';
        _Digit['N'] = 'N';
        _Digit['{'] = '{'; // 'Ñ'
        _Digit['n'] = 'n';
        _Digit['}'] = '}'; // 'ñ'
        _Digit['O'] = 'O';
        _Digit['+'] = '+'; // 'Ó'
        _Digit['o'] = 'o';
        _Digit[','] = ','; // 'ó'
        _Digit['P'] = 'P';
        _Digit['p'] = 'p';
        _Digit['Q'] = 'Q';
        _Digit['q'] = 'q';
        _Digit['R'] = 'R';
        _Digit['r'] = 'r';
        _Digit['S'] = 'S';
        _Digit['-'] = '-'; // 'Œ'
        _Digit['s'] = 's';
        _Digit['.'] = '.'; // 'œ'
        _Digit['T'] = 'T';
        _Digit['t'] = 't';
        _Digit['U'] = 'U';
        _Digit['u'] = 'u';
        _Digit['V'] = 'V';
        _Digit['v'] = 'v';
        _Digit['W'] = 'W';
        _Digit['w'] = 'w';
        _Digit['X'] = 'X';
        _Digit['x'] = 'x';
        _Digit['Y'] = 'Y';
        _Digit['y'] = 'y';
        _Digit['Z'] = 'Z';
        _Digit['/'] = '/'; // '¯'
        _Digit[';'] = ';'; // ''
        _Digit['z'] = 'z';
        _Digit['`'] = '`'; // '¿'
        _Digit['|'] = '|'; // 'Ÿ'
        };
    }
else
    {
    fputs("Error during defining the digits.\n",stderr);
    abort();
    };
};

// ___________________________________________________________________________________________________________________

void PrintHelper( const char * _str )
{
// Declarations.
unsigned long long int (*i) = (unsigned long long int *)malloc(sizeof(unsigned long long int));
unsigned long long int (*size) = (unsigned long long int *)malloc(sizeof(unsigned long long int));

// Counting.
(*size) = 0;
(*size) = strnlen( _str, MAX_SIZE );

// Interpreting.
for ( (*i)=0; (*i)<(*size); (*i)=(*i)+1 )
    {
    if ( (((_str[(*i)]) >= 65) && ((_str[(*i)]) <= 90)) || (((_str[(*i)]) >= 97) && ((_str[(*i)]) <= 122)) )
        {
        // Handling the regular character ('A'-'Z' and 'a'-'z').
        fputc( _str[(*i)], stdout );
        }
    else
        {
        switch ( _str[(*i)] )
            {
            case '¥' : fprintf(stdout,"%c",0xA4); break;
            case '¹' : fprintf(stdout,"%c",0xA5); break;
            case 'Æ' : fprintf(stdout,"%c",0x8F); break;
            case 'æ' : fprintf(stdout,"%c",0x86); break;
            case 'Ê' : fprintf(stdout,"%c",0xA8); break;
            case 'ê' : fprintf(stdout,"%c",0xA9); break;
            case '£' : fprintf(stdout,"%c",0x9D); break;
            case '³' : fprintf(stdout,"%c",0x88); break;
            case 'Ñ' : fprintf(stdout,"%c",0xE3); break;
            case 'ñ' : fprintf(stdout,"%c",0xE4); break;
            case 'Ó' : fprintf(stdout,"%c",0xE0); break;
            case 'ó' : fprintf(stdout,"%c",0xA2); break;
            case 'Œ' : fprintf(stdout,"%c",0x97); break;
            case 'œ' : fprintf(stdout,"%c",0x98); break;
            case '¯' : fprintf(stdout,"%c",0xBD); break;
            case '¿' : fprintf(stdout,"%c",0xBE); break;
            case '' : fprintf(stdout,"%c",0x8D); break;
            case 'Ÿ' : fprintf(stdout,"%c",0xAB); break;
            };
        };
    };

// Deallocating the memory.
free(i);
free(size);

// Resetting the pointer.
i = NULL;
size = NULL;
};

// ___________________________________________________________________________________________________________________

unsigned short int CharacterHandler( const char ( * _Digit ), char _ch )
{
unsigned short int value = 0;

if ( (((_ch) >= 65) && ((_ch) <= 90)) || (((_ch) >= 97) && ((_ch) <= 122)) )
    {
    // Handling the regular character ('A'-'Z' and 'a'-'z').
    value = _Digit[ _ch ];
    }
else
    {
    // Handling the unregular character (extended, but non-wide and non-Unicode).
    switch ( _ch )
        {
        case '¥' : value = (unsigned short int)(_Digit['#']); break;
        case '¹' : value = (unsigned short int)(_Digit['$']); break;
        case 'Æ' : value = (unsigned short int)(_Digit['%']); break;
        case 'æ' : value = (unsigned short int)(_Digit['&']); break;
        case 'Ê' : value = (unsigned short int)(_Digit['~']); break;
        case 'ê' : value = (unsigned short int)(_Digit['(']); break;
        case '£' : value = (unsigned short int)(_Digit[')']); break;
        case '³' : value = (unsigned short int)(_Digit['*']); break;
        case 'Ñ' : value = (unsigned short int)(_Digit['{']); break;
        case 'ñ' : value = (unsigned short int)(_Digit['}']); break;
        case 'Ó' : value = (unsigned short int)(_Digit['+']); break;
        case 'ó' : value = (unsigned short int)(_Digit[',']); break;
        case 'Œ' : value = (unsigned short int)(_Digit['-']); break;
        case 'œ' : value = (unsigned short int)(_Digit['.']); break;
        case '¯' : value = (unsigned short int)(_Digit['/']); break;
        case '¿' : value = (unsigned short int)(_Digit['`']); break;
        case '' : value = (unsigned short int)(_Digit[';']); break;
        case 'Ÿ' : value = (unsigned short int)(_Digit['|']); break;
        };
    };

return ( value );
};

// ___________________________________________________________________________________________________________________

unsigned long long int Remainder( const unsigned long long int _a, const unsigned long long int _b )
{
register unsigned long long int mod;

if ( _a < _b )
    {
    mod = _a;
    }
else
if ( _a == _b )
    {
    mod = 0;
    }
else
    {
    mod = _a - ( _b * ( _a/_b ) );
    };

return ( mod );
};

// ___________________________________________________________________________________________________________________

void StringToDigitsConvertion( const char * _str, unsigned long long int * _number, const char ( * _Digit ), const size_t _P_SIZE )
{
// Declarations.
unsigned short int (*i) = (unsigned short int *)malloc(sizeof(unsigned short int));
unsigned long long int (*no) = (unsigned long long int *)calloc(1,sizeof(unsigned long long int));
unsigned long int (*digit) = (unsigned long int *)malloc(sizeof(unsigned long int));

// Counting the number.
for ( (*i)=0; (*i)<(_P_SIZE-1); (*i)=(*i)+1 )
    {
    (*digit) = (unsigned long int)(_Digit[ _str[(*i)] ]);
    (*no) = (*no) + (*digit);
    (*no) = (*no) * 10;
    };

(*digit) = (unsigned long int)(_Digit[ _str[(*i)] ]);
(*no) = (*no) + (*digit);

// Writing the result to the outside data structure.
(*_number) = (*no);

// Deallocating the memory.
free(no);
free(i);
free(digit);

// Cancelling the pointer.
no = NULL;
i = NULL;
digit = NULL;
};

// ___________________________________________________________________________________________________________________

void StringToDigitsConvertion2( const char * _str, unsigned long long int * _number, const char ( * _Digit ), const size_t _P_SIZE )
{
// Declarations.
unsigned short int (*i) = (unsigned short int *)malloc(sizeof(unsigned short int));
unsigned long long int (*no) = (unsigned long long int *)malloc(sizeof(unsigned long long int));
unsigned long long int (*digit) = (unsigned long long int *)malloc(sizeof(unsigned long long int));
unsigned long long int (*power) = (unsigned long long int *)malloc(sizeof(unsigned long long int));
unsigned short int (*exp) = (unsigned short int *)malloc(sizeof(unsigned short int));
char (*ch) = (char *)malloc(sizeof(char));

// Presetting.
(*exp) = _P_SIZE - 1;
(*no) = 0;
(*ch) = 0;

// Counting the number.
for ( (*i)=0; (*i)<_P_SIZE; (*i)=(*i)+1 )
    {
    (*ch) = _str[(*i)];
    (*digit) = CharacterHandler( _Digit, (*ch) );
    (*power) = PowerBaseDefined( (*exp) );
    (*exp) = (*exp) - 1;
    (*no) = (*no) + ( (*power) * (*digit) );
    };

// Writing the result to the outside data structure.
(*_number) = (*no);

// Deallocating the memory.
free(no);
free(i);
free(digit);
free(power);
free(exp);
free(ch);

// Cancelling the pointer.
no = NULL;
i = NULL;
digit = NULL;
power = NULL;
exp = NULL;
ch = NULL;
};

// ___________________________________________________________________________________________________________________

void KarpRabinAlgorithm( const char * _pattern, const char ( * _Digit ), const char ( * _string ), BOOLEAN _mode )
//  _mode:=FALSE   The pattern will be treated by the recursion model only. 
//  _mode:=TRUE    The pattern will be treated by the recursion model with congruential operations. 
                
{
// Declarations.
unsigned long long int pattern = 0;
unsigned long long int number = 0;
const size_t PATTERN_SIZE = strlen(_pattern);
char (*fstr) = (char (*))malloc(PATTERN_SIZE*sizeof(char));
unsigned long long int (*offset) = (unsigned long long int (*))malloc(sizeof(unsigned long long int));
unsigned long long int (*i) = (unsigned long long int (*))malloc(sizeof(unsigned long long int));
unsigned long long int (*condition) = (unsigned long long int (*))malloc(sizeof(unsigned long long int));
unsigned long int (*no1) = (unsigned long int (*))malloc(sizeof(unsigned long int));
unsigned long int (*no2) = (unsigned long int (*))malloc(sizeof(unsigned long int));
unsigned long long int (*power) = (unsigned long long int (*))malloc(sizeof(unsigned long long int));
char flag = 'F';
unsigned long long int (*tmp1) = (unsigned long long int *)malloc(sizeof(unsigned long long int));
unsigned long long int (*tmp2) = (unsigned long long int *)malloc(sizeof(unsigned long long int));
const unsigned long long int Q_NUMBER = 18446744073709551615;

// Copying the first bytes.
memset(fstr,0,PATTERN_SIZE*sizeof(char));
memcpy(fstr,_string,PATTERN_SIZE*sizeof(char));

// Common issues resolving.
(*offset) = 0;
(*condition) = strnlen(_string,MAX_SIZE) - PATTERN_SIZE;

// Switching the route.
switch ( _mode )
    {

    // ------------------------------------------------------------------------------------------

    case ( FALSE ) :
        {
        // Preprocessing: convertion.
        StringToDigitsConvertion( _pattern, &pattern, _Digit, PATTERN_SIZE );
        StringToDigitsConvertion( fstr, &number, _Digit, PATTERN_SIZE );

        // Precalculating.
        (*power) = PowerBase10( PATTERN_SIZE-1 );

        // Shifting and searching for the first occurence of the pattern.
        for ( (*i)=0; (*i)<(*condition); (*i)=(*i)+1 )
            {
            (*no1) = (unsigned long int)(_Digit[_string[(*offset)]]);
            (*no2) = (unsigned long int)(_Digit[_string[(*offset)+PATTERN_SIZE]]);
            number = ( ( number - ( (*no1) * (*power) ) ) * 10 ) + (*no2);
            (*offset) = (*offset) + 1;

            if ( number == pattern )
                {
                // Printing the searching result.
                fprintf(stdout,"The first occurence of the pattern:\n%s\nhas been found at:"
                               "\n%llu\nposition.\n",_pattern,(*offset));
                flag = 'T';
                break;
                };
            };

        if ( flag == 'F' )
            {
            fprintf(stdout,"The pattern:\n%s\nhas not been found in the linked data.\n",_pattern);
            };
        }
        break;

    // ------------------------------------------------------------------------------------------

    case ( TRUE ) :
        {
        // Preprocessing: convertion.
        StringToDigitsConvertion2( _pattern, &pattern, _Digit, PATTERN_SIZE );
        StringToDigitsConvertion2( fstr, &number, _Digit, PATTERN_SIZE );

        // Precalculating.
        (*power) = PowerBaseDefined( PATTERN_SIZE - 1 );
        (*no1) = 0;

        // Shifting and searching for the first occurence of the pattern footprint.
        for ( (*i)=0; (*i)<(*condition); (*i)=(*i)+1 )
            {
            (*tmp1) = (unsigned long long int)(CharacterHandler( _Digit, _string[(*offset)] ));
            (*tmp2) = (*tmp1) * (*power);
            (*tmp1) = Remainder( (*tmp2), Q_NUMBER );
            (*tmp2) = number - (*tmp1);
            (*tmp1) = (*tmp2) * (unsigned long int)(BASE);
            (*tmp2) = Remainder( (*tmp1), Q_NUMBER );
            (*tmp1) = (*tmp2) + (unsigned long long int)(CharacterHandler( _Digit, _string[(*offset)+PATTERN_SIZE] ));
            (*offset) = (*offset) + 1;
            number = (*tmp1);

            if ( number == pattern )
                {
                (*no1) = (*no1) + 1;

                // Comparing the strings.
                memset(fstr,0,PATTERN_SIZE*sizeof(char));
                memcpy(fstr,_string+(*i)+1,PATTERN_SIZE*sizeof(char));
                (*no2) = strncmp( _pattern, fstr, PATTERN_SIZE );

                if ( (*no2) == 0 )
                    {
                    // Printing the searching results.
                    if ((*no1) == 1) 
                        {
                        fputs("Pattern: ",stdout);
                        PrintHelper( _pattern );
                        fputc( '\n', stdout );
                        fprintf(stdout,"%10lu) %20llu position\n",(*no1),(*offset));
                        }
                    else
                        {
                        fprintf(stdout,"%10lu) %20llu position\n",(*no1),(*offset));
                        };
                    };
                };
            };

        if ( (*no1) == 0 )
            {
            fputs("The pattern:\n",stdout);
            PrintHelper( _pattern );
            fprintf(stdout,"\nhas not been found in the linked data; after:\n%lu\nchecks.\n",(*no1));
            }
        else
            {
            fprintf(stdout,"\nFinished after %lu checks.\n",(*no1));
            };
        }
        break;

    // ------------------------------------------------------------------------------------------

    };

// Deallocating the memory.
free(fstr);
free(offset);
free(i);
free(condition);
free(no1);
free(no2);
free(power);
free(tmp1);
free(tmp2);

// Cancelling the pointer.
fstr = NULL;
offset = NULL;
i = NULL;
condition = NULL;
no1 = NULL;
no2 = NULL;
power = NULL;
tmp1 = NULL;
tmp2 = NULL;
};

// ___________________________________________________________________________________________________________________
