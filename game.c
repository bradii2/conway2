#include "game.h"
#include "list.h"
#include <SDL2/SDL.h>

Row *rows;

void initGame(void)
{
    rows = createRow(0);
}

void deinitGame(void)
{
    destroyRows(&rows);
}