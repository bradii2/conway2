#include "render.h"
#include "game.h"
#include <SDL2/SDL.h>

SDL_Window  *window;
SDL_Surface *windowSurface;
SDL_Surface *greySurface;
SDL_Surface *whiteSurface;
SDL_Surface *blackSurface;

int WINDOW_W, WINDOW_H, CELL_W, CELL_H;
/* The offsets are for rendering */
int offsetX, offsetY;

void initRender(int *going)
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL_Init error: %s\n", SDL_GetError());
        *going = 0;
        return;
    }
    
    /* Create the main window and its surface */
    window = SDL_CreateWindow("Conway's Game of Life", 
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              500,
                              500,
                              SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
    windowSurface = SDL_GetWindowSurface(window);
    
    /* Create the single-color surfaces */
    whiteSurface = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
    blackSurface = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
    greySurface  = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
    SDL_FillRect(whiteSurface, NULL, SDL_MapRGB(whiteSurface->format, 255, 255, 255));
    SDL_FillRect(blackSurface, NULL, SDL_MapRGB(blackSurface->format, 0  , 0  , 0  ));
    SDL_FillRect(greySurface , NULL, SDL_MapRGB(greySurface->format , 127, 127, 127));
}
void deinitRender(void)
{
    SDL_FreeSurface(windowSurface);
    SDL_FreeSurface(greySurface);
    SDL_FreeSurface(whiteSurface);
    SDL_Freesurface(blackSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/* TODO: get this up and running */
void draw(void)
{
    
    SDL_UpdateWindowSurface(window);
}