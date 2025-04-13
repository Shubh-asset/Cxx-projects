#include "screen.h"
#include <cstdlib>
#include <ctime>

int main(int argv, char **args)
{
    srand(time(0));
    Screen screen;
    for (int i = 0; i < 199; i++)
    {
        screen.pixel(rand() % 640, rand() % 480);
    }
    while (true)
    {
        screen.show();
        screen.input();
    }
    return 0;
}
