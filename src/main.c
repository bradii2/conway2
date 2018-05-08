/**
 *  Conway's Game of Life
 *  Rules:
 *  1. Any live cell with fewer than 2 neighbors dies
 *  2. Any live cell with two or three neighbors lives on to the next generation
 *  3. Any live cell with more than three neighbors dies
 *  4. Any dead cell with exactly three live neighbors becomes a live cell
 *  
 *  This implementation of life has an infinitely sized grid that the user can scroll through.
 *  The window is also resizeable, and you can zoom in and out to make cells bigger or smaller.
 */


#include "list.h"
#include "render.h"
#include "inputs.h"
#include "game.h"
#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"

int going  = 1;
int paused = 1;

int init(void);
void deinit(void);


int main(int argc, char *argv[])
{
    if(init())
        return 1;
    
    while (going)
    {
        /* Make handleInputs come AFTER updateInputs! */
        /* Handle actually does the changes to the program - 
         * update just updates the arrays for which keys are pressed
         */
        updateInputs();
        handleInputs(&paused, &going);
        if (!going)
            break;

        gameLoop(paused);
        
        gameDraw();
    }
    
    deinit();
}

int init(void)
{
    /* Call initInputs() before any other inits that use setKeyFunc()! */
    initInputs();
    if (initRender(&going) != 0)
        return 1;
    initGame();
    return 0;
}
void deinit(void)
{
    deinitRender();
    deinitGame();
    deinitInputs();
}