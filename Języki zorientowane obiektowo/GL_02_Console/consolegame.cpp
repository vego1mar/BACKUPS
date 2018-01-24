#include "consolegame.h"
#include <cstdio>
#include <cstdlib>
#include <Windows.h>
#include <stddef.h>
#include <string>

// _______________________________________________________________________________________

ConsoleGame::ConsoleGame()
    : hc_ ( nullptr )
    , c_ ( )
    , loop_ ( 256 )
    , ms_ ( 250 )
    , sl_ ( false )
    , wait_ ( false )

{
hc_ = GetStdHandle( STD_OUTPUT_HANDLE );

if ( hc_ == INVALID_HANDLE_VALUE )
    {
    fputs("The console output context has not been set.",stderr);
    abort();
    };

SetConsoleTextAttribute( hc_, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
c_.X = 0;
c_.Y = 0;
};

// _______________________________________________________________________________________

ConsoleGame::~ConsoleGame()
{
BOOL code;
DWORD error;
LPSTR msg_buff = nullptr;
size_t size;

code = FreeConsole();

if ( code == 0 )
    {
    fputs("The console context connot been released.",stderr);
    error = ::GetLastError();
    size = FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                           NULL, error, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
                           reinterpret_cast<LPSTR>(&msg_buff), 0, NULL );
    std::string msg( msg_buff, size );
    LocalFree( msg_buff );
    fprintf(stderr,"--> System Error: %s\n",msg.c_str());
    };
};

// _______________________________________________________________________________________

ConsoleGame::ConsoleGame(const ConsoleGame & _rvalue)
{
};

// _______________________________________________________________________________________

ConsoleGame & ConsoleGame::operator= (const ConsoleGame & _rvalue)
{
return (*this);
};

// _______________________________________________________________________________________

// virtual
void ConsoleGame::Play()
{
for ( int i=0 ; i<ConsoleGame::loop_ ; i++ )
    {
    Draw();
    Analyze();
    if ( ConsoleGame::sl_ == true ) { Sleep( ConsoleGame::ms_ ); };
    if ( ConsoleGame::wait_ == true ) { getchar(); };
    };
};

// _______________________________________________________________________________________

// virtual
void ConsoleGame::Draw()
{
short int i;
short int j;

for (i=0; i<Engine::Y; i++)
	{
	for (j=0; j<Engine::X; j++)
		{
        //   32   space
        //  219   block
        c_.X = j;
        c_.Y = i;
        SetConsoleCursorPosition( hc_, c_ );
        putchar(GetCell(j,i) ? char(219) : char(32));
		};

	putchar('\n');
	};
};

// _______________________________________________________________________________________

void ConsoleGame::PlayFor( unsigned short int _arg )
{
loop_ = _arg;
};

// _______________________________________________________________________________________

void ConsoleGame::SleepFor( bool _arg1, DWORD _arg2 )
{
sl_ = _arg1;
ms_ = _arg2;
};

// _______________________________________________________________________________________

void ConsoleGame::WaitKey( bool _arg )
{
wait_ = _arg;
};

// _______________________________________________________________________________________

unsigned short int ConsoleGame::GetPlayForValue()
{
return ( loop_ );
};

// _______________________________________________________________________________________

DWORD ConsoleGame::GetSleepForValue1()
{
return ( ms_ );
};

// _______________________________________________________________________________________

bool ConsoleGame::GetSleepForValue2()
{
return ( sl_ );
};

// _______________________________________________________________________________________

bool ConsoleGame::GetWaitKeyValue()
{
return ( wait_ );
};

// _______________________________________________________________________________________
