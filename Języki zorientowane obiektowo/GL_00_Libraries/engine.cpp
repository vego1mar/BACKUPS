#include "engine.h"
#include <cstring>

// _______________________________________________________________________________________

Engine::Engine()
	: T_()
	, A_()
	, live_ ()
	, die_ ()

{
memset(Engine::T_,false,sizeof(Engine::T_));
memset(Engine::A_,false,sizeof(Engine::A_));
memset(live_,false,Engine::P*sizeof(bool));
memset(die_,false,Engine::P*sizeof(bool));
};

// _______________________________________________________________________________________

Engine::~Engine()
{
};

// _______________________________________________________________________________________

Engine::Engine(const Engine & _rvalue)
	: T_ ()
	, A_ ()
    , live_ ()
    , die_ ()
{
memcpy(T_,_rvalue.T_,sizeof(_rvalue.T_));
memcpy(A_,_rvalue.A_,sizeof(_rvalue.A_));
memcpy(Engine::live_,_rvalue.live_,sizeof(Engine::live_));
memcpy(Engine::die_,_rvalue.die_,sizeof(Engine::die_));
};

// _______________________________________________________________________________________

Engine & Engine::operator= (const Engine & _rvalue)
{
//*this = _rvalue;
return (*this);
};

// _______________________________________________________________________________________

void Engine::Analyze()
{
// Declarations.
short int i;
short int j;
short int counter;

// I. Analyzing the first line.
for ( i=0; i<Engine::X; i++ )
	{
    // Reseting the counter for the next use.
    counter = 0;

    // Handling the first cell.
    if ( i == 0 )
        {
        if ( T_[i+1][0] ) counter++;
        if ( T_[i][1] ) counter++;
        if ( T_[i+1][1] ) counter++;
        }
    else
    // Handling the last cell.
    if ( i == (Engine::X - 1) )
        {
        if ( T_[Engine::X - 2][0] ) counter++;
        if ( T_[Engine::X - 2][1] ) counter++;
        if ( T_[Engine::X - 1][1] ) counter++;
        }
    else
    // Handling the other cells.
        {
        if ( T_[i-1][0] ) counter++;
        if ( T_[i+1][0] ) counter++;
        if ( T_[i-1][1] ) counter++;
        if ( T_[i][1] ) counter++;
        if ( T_[i+1][1] ) counter++;
        };

    // Analyzing the counter state.
    if ( Engine::T_[i][0] == true )
        {
        // Check if should it be dead.
        switch (counter)
            {
            case 0 : if ( GetDie(0) == true ) SetAux(false,i,0); else SetAux(GetCell(i,0),i,0); break;
            case 1 : if ( GetDie(1) == true ) SetAux(false,i,0); else SetAux(GetCell(i,0),i,0); break;
            case 2 : if ( GetDie(2) == true ) SetAux(false,i,0); else SetAux(GetCell(i,0),i,0); break;
            case 3 : if ( GetDie(3) == true ) SetAux(false,i,0); else SetAux(GetCell(i,0),i,0); break;
            case 4 : if ( GetDie(4) == true ) SetAux(false,i,0); else SetAux(GetCell(i,0),i,0); break;
            case 5 : if ( GetDie(5) == true ) SetAux(false,i,0); else SetAux(GetCell(i,0),i,0); break;
            };
        }
    else
        {
        // Check if should it be alive.
        switch (counter)
            {
            case 0 : if ( GetLive(0) == true ) SetAux(true,i,0); else SetAux(GetCell(i,0),i,0); break;
            case 1 : if ( GetLive(1) == true ) SetAux(true,i,0); else SetAux(GetCell(i,0),i,0); break;
            case 2 : if ( GetLive(2) == true ) SetAux(true,i,0); else SetAux(GetCell(i,0),i,0); break;
            case 3 : if ( GetLive(3) == true ) SetAux(true,i,0); else SetAux(GetCell(i,0),i,0); break;
            case 4 : if ( GetLive(4) == true ) SetAux(true,i,0); else SetAux(GetCell(i,0),i,0); break;
            case 5 : if ( GetLive(5) == true ) SetAux(true,i,0); else SetAux(GetCell(i,0),i,0); break;
            };
        };
	};

// II. Analyzing the lines between the first and the last one.
for ( j=1; j<( Engine::Y - 1 ); j++ )
    {
    for ( i=0; i<Engine::X; i++ )
        {
        // Reseting the counter for the next use.
        counter = 0;

        // Handling the first cell.
        if ( i == 0 )
            {
            if ( T_[i][j-1] ) counter++;
            if ( T_[i+1][j-1] ) counter++;
            if ( T_[i+1][j] ) counter++;
            if ( T_[i][j+1] ) counter++;
            if ( T_[i+1][j+1] ) counter++;
            }
        else
        // Handling the last cell.
        if ( i == (Engine::X - 1) )
            {
            if ( T_[Engine::X - 2][j-1] ) counter++;
            if ( T_[Engine::X - 2][j] ) counter++;
            if ( T_[Engine::X - 2][j+1] ) counter++;
            if ( T_[Engine::X - 1][j-1] ) counter++;
            if ( T_[Engine::X - 1][j+1] ) counter++;
            }
        else
        // Handling the other cells.
            {
            if ( T_[i-1][j-1] ) counter++;
            if ( T_[i-1][j] ) counter++;
            if ( T_[i-1][j+1] ) counter++;
            if ( T_[i][j-1] ) counter++;
            if ( T_[i][j+1] ) counter++;
            if ( T_[i+1][j-1] ) counter++;
            if ( T_[i+1][j] ) counter++;
            if ( T_[i+1][j+1] ) counter++;
            };

        // Analyzing the counter state.
        if ( Engine::T_[i][j] == true )
            {
            // Check if should it be dead.
            switch (counter)
                {
                case 0 : if ( GetDie(0) == true ) SetAux(false,i,j); else SetAux(GetCell(i,j),i,j); break;
                case 1 : if ( GetDie(1) == true ) SetAux(false,i,j); else SetAux(GetCell(i,j),i,j); break;
                case 2 : if ( GetDie(2) == true ) SetAux(false,i,j); else SetAux(GetCell(i,j),i,j); break;
                case 3 : if ( GetDie(3) == true ) SetAux(false,i,j); else SetAux(GetCell(i,j),i,j); break;
                case 4 : if ( GetDie(4) == true ) SetAux(false,i,j); else SetAux(GetCell(i,j),i,j); break;
                case 5 : if ( GetDie(5) == true ) SetAux(false,i,j); else SetAux(GetCell(i,j),i,j); break;
                case 6 : if ( GetDie(6) == true ) SetAux(false,i,j); else SetAux(GetCell(i,j),i,j); break;
                case 7 : if ( GetDie(7) == true ) SetAux(false,i,j); else SetAux(GetCell(i,j),i,j); break;
                case 8 : if ( GetDie(8) == true ) SetAux(false,i,j); else SetAux(GetCell(i,j),i,j); break;
                };
            }
        else
            {
            // Check if should it be alive.
            switch (counter)
                {
                case 0 : if ( GetLive(0) == true ) SetAux(true,i,j); else SetAux(GetCell(i,j),i,j); break;
                case 1 : if ( GetLive(1) == true ) SetAux(true,i,j); else SetAux(GetCell(i,j),i,j); break;
                case 2 : if ( GetLive(2) == true ) SetAux(true,i,j); else SetAux(GetCell(i,j),i,j); break;
                case 3 : if ( GetLive(3) == true ) SetAux(true,i,j); else SetAux(GetCell(i,j),i,j); break;
                case 4 : if ( GetLive(4) == true ) SetAux(true,i,j); else SetAux(GetCell(i,j),i,j); break;
                case 5 : if ( GetLive(5) == true ) SetAux(true,i,j); else SetAux(GetCell(i,j),i,j); break;
                case 6 : if ( GetLive(6) == true ) SetAux(true,i,j); else SetAux(GetCell(i,j),i,j); break;
                case 7 : if ( GetLive(7) == true ) SetAux(true,i,j); else SetAux(GetCell(i,j),i,j); break;
                case 8 : if ( GetLive(8) == true ) SetAux(true,i,j); else SetAux(GetCell(i,j),i,j); break;
                };
            };
        };
    };

// III. Analyzing the last line.
for ( i=0; i<Engine::X; i++ )
	{
    // Reseting the counter for the next use.
    counter = 0;

    // Handling the first cell.
    if ( i == 0 )
        {
        if ( T_[0][Engine::Y - 2] ) counter++;
        if ( T_[1][Engine::Y - 2] ) counter++;
        if ( T_[1][Engine::Y - 1] ) counter++;
        }
    else
    // Handling the last cell.
    if ( i == (Engine::X - 1) )
        {
        if ( T_[Engine::X - 2][Engine::Y - 2] ) counter++;
        if ( T_[Engine::X - 2][Engine::Y - 1] ) counter++;
        if ( T_[Engine::X - 1][Engine::Y - 2] ) counter++;
        }
    else
    // Handling the other cells.
        {
        if ( T_[i-1][Engine::Y - 2] ) counter++;
        if ( T_[i-1][Engine::Y - 1] ) counter++;
        if ( T_[i][Engine::Y - 2] ) counter++;
        if ( T_[i+1][Engine::Y - 2] ) counter++;
        if ( T_[i+1][Engine::Y - 1] ) counter++;
        };

    // Analyzing the counter state.
    if ( Engine::T_[i][Engine::Y - 1] == true )
        {
        // Check if should it be dead.
        switch (counter)
            {
            case 0 : if ( GetDie(0) == true ) SetAux(false,i,0); else SetAux(GetCell(i,0),i,0); break;
            case 1 : if ( GetDie(1) == true ) SetAux(false,i,0); else SetAux(GetCell(i,0),i,0); break;
            case 2 : if ( GetDie(2) == true ) SetAux(false,i,0); else SetAux(GetCell(i,0),i,0); break;
            case 3 : if ( GetDie(3) == true ) SetAux(false,i,0); else SetAux(GetCell(i,0),i,0); break;
            case 4 : if ( GetDie(4) == true ) SetAux(false,i,0); else SetAux(GetCell(i,0),i,0); break;
            case 5 : if ( GetDie(5) == true ) SetAux(false,i,0); else SetAux(GetCell(i,0),i,0); break;
            };
        }
    else
        {
        // Check if should it be alive.
        switch (counter)
            {
            case 0 : if ( GetLive(0) == true ) SetAux(true,i,0); else SetAux(GetCell(i,0),i,0); break;
            case 1 : if ( GetLive(1) == true ) SetAux(true,i,0); else SetAux(GetCell(i,0),i,0); break;
            case 2 : if ( GetLive(2) == true ) SetAux(true,i,0); else SetAux(GetCell(i,0),i,0); break;
            case 3 : if ( GetLive(3) == true ) SetAux(true,i,0); else SetAux(GetCell(i,0),i,0); break;
            case 4 : if ( GetLive(4) == true ) SetAux(true,i,0); else SetAux(GetCell(i,0),i,0); break;
            case 5 : if ( GetLive(5) == true ) SetAux(true,i,0); else SetAux(GetCell(i,0),i,0); break;
            };
        };
	};

// IV. Copying the analyzed data to the main data structure.
for ( i=0; i<Engine::X; i++ )
    {
    for ( j=0; j<Engine::Y; j++ )
        {
        SetCell(GetAux(i,j),i,j);
        };
    };
};

// _______________________________________________________________________________________

void Engine::SetCell(bool _value, short int _X, short int _Y)
{
if ((_X >= 0) && (_X < Engine::X) && (_Y >= 0) && (_Y < Engine::Y))
	{
	T_[_X][_Y] = _value;
	};
};

// _______________________________________________________________________________________

bool Engine::GetCell(short int _X, short int _Y) const
{
bool value = false;

if ((_X >= 0) && (_X < Engine::X) && (_Y >= 0) && (_Y < Engine::Y))
	{
	value = T_[_X][_Y];
	};

return (value);
};

// _______________________________________________________________________________________

void Engine::SetAux(bool _value, short int _X, short int _Y)
{
if ((_X >= 0) && (_X < Engine::X) && (_Y >= 0) && (_Y < Engine::Y))
	{
	A_[_X][_Y] = _value;
	};
};

// _______________________________________________________________________________________

bool Engine::GetAux(short int _X, short int _Y) const
{
bool value = false;

if ((_X >= 0) && (_X < Engine::X) && (_Y >= 0) && (_Y < Engine::Y))
	{
	value = A_[_X][_Y];
	};

return (value);
};

// _______________________________________________________________________________________

bool Engine::GetLive ( short int _P ) const
{
bool value = false;

if ( ( _P >= 0 ) && ( _P < Engine::P ) )
    {
    value = live_[_P];
    };

return (value);
};

// _______________________________________________________________________________________

void Engine::SetLive ( bool _value, short int _P )
{
if ( ( _P >= 0 ) && ( _P < Engine::P ) )
    {
    live_[_P] = _value;
    };
};

// _______________________________________________________________________________________

bool Engine::GetDie ( short int _P ) const
{
bool value = false;

if ( ( _P >= 0 ) && ( _P < Engine::P ) )
    {
    value = die_[_P];
    };

return (value);
};

// _______________________________________________________________________________________

void Engine::SetDie ( bool _value, short int _P )
{
if ( ( _P >= 0 ) && ( _P < Engine::P ) )
    {
    die_[_P] = _value;
    };
};

// _______________________________________________________________________________________
