#include "game.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

// _______________________________________________________________________________________

Game::Game()
	: filename_ ()
	, condition_ ()

{
// Clearing the poles.
memset(filename_,0,Game::F*sizeof(char));
memset(condition_,0,Game::C*sizeof(char));
};

// _______________________________________________________________________________________

Game::Game(const Game & _rvalue)
{
};

// _______________________________________________________________________________________

Game & Game::operator= (const Game & _rvalue)
{
return (*this);
};

// _______________________________________________________________________________________

Game::~Game()
{
};

// _______________________________________________________________________________________

// pure virtual
void Game::Play()
{
};

// _______________________________________________________________________________________

// pure virtual
void Game::Draw()
{
};

// _______________________________________________________________________________________

void Game::Init(const char * _filename, const char * _condition)
{
// Storing the parameters.
size_t size;
size = strlen(_filename);

if (size <= 0)
	{
	fputs("The filename is empty or invalid.\n",stderr);
	abort();
	}
else if (size >= F)
	{
	fputs("The filename is too long.\n",stderr);
	abort();
	}
else
	{
	strcpy(filename_,_filename);
	};

size = strlen(_condition);

if (size <= 0)
	{
	fputs("There is no condition at all.\n",stderr);
	abort();
	}
else if (size >= C)
	{
	fputs("The condition string is too long.\n",stderr);
	abort();
	}
else
	{
	strcpy(condition_,_condition);
	};

// Opening the file.
FILE *fp;
fp = fopen(_filename,"rt");

// Checking the file.
if (fp == nullptr)
	{
	fputs("Input file not found.\n",stderr);
	abort();
	};

// Reading data from the file.
short int i;
short int j;
int read = 0;
bool value = false;

for (i=0; i<Engine::Y; i++)
	{
	for (j=0; j<Engine::X; j++)
		{
		fscanf(fp,"%d",&read);
		value = (read != 0);
		SetCell(value,j,i);
		value = false;
		};
	};

// Parsing the condition string.
char c = 0;
size_t k;

for (k=0; k<size; k++)
	{
	c = _condition[k];

	if (c == '/')
		{
		break;
		};

	switch (c)
		{
		case '0' : SetLive(true,0); break;
		case '1' : SetLive(true,1); break;
		case '2' : SetLive(true,2); break;
		case '3' : SetLive(true,3); break;
		case '4' : SetLive(true,4); break;
		case '5' : SetLive(true,5); break;
		case '6' : SetLive(true,6); break;
		case '7' : SetLive(true,7); break;
		case '8' : SetLive(true,8); break;
		};
	};

k = k + 1;

for (k=k; k<size; k++)
	{
	c = _condition[k];

	switch (c)
		{
		case '0' : SetDie(true,0); break;
		case '1' : SetDie(true,1); break;
		case '2' : SetDie(true,2); break;
		case '3' : SetDie(true,3); break;
		case '4' : SetDie(true,4); break;
		case '5' : SetDie(true,5); break;
		case '6' : SetDie(true,6); break;
		case '7' : SetDie(true,7); break;
		case '8' : SetDie(true,8); break;
		};
	};

// Closing the file.
fclose(fp);
};

// _______________________________________________________________________________________
