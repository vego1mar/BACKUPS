#include <cstdio>
#include "consolegame.h"

// _______________________________________________________________________________________

int main(void)
{
printf("Starting at console!\n\n");

ConsoleGame X;

X.Init("input.in","3/0156789");
X.Draw();
printf("\nPress any key to play.\n");
getchar();
X.Play();

getchar();
printf("Console end.\n");

return (0);
};

// _______________________________________________________________________________________
