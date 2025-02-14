#include "Menu.h"
#include "ScoreMenu.h"
#include <ctime>
int main()
{
    srand(std::time(0));
Menu menu;
menu.ShowMenu();
}