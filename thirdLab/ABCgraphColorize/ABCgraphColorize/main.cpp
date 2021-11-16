#include "ConsoleMenu.h"
#include <random>
#include <time.h>

int main()
{
	srand(time(NULL));
	ConsoleMenu menu(200, 20, 1, 30, 2, 20, 1000);
	menu.startMenu();
}