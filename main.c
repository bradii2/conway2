#include "list.h"
#include "render.h"
#include "inputs.h"
#include "game.h"
#include <SDL2/SDL.h>

int going  = 1;
int paused = 1;

void init(void);
void deinit(void);


int main(int argc, char *argv[])
{
    init();
    
    while (going)
    {
        /* Make handleInputs come AFTER updateInputs! */
        /* Handle actually does the changes to the program - 
         * update just updates the arrays for which keys are pressed
         */
        updateInputs(&paused, &going);
        handleInputs();
        
        step();
        draw();
    }
    
    deinit();
}

void init(void)
{
    initRender(&going);
    initInputs();
    initGame();
}
void deinit(void)
{
    deinitRender();
    deinitInputs();
    deinitGame();
}