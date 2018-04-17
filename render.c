#include "render.h"
#include "game.h"
#include "list.h"
#include "inputs.h"
#include <SDL2/SDL.h>

SDL_Window  *window;
SDL_Surface *windowSurface;
SDL_Surface *greySurface;
SDL_Surface *whiteSurface;
SDL_Surface *blackSurface;

/* CELL_W and CELL_H are changed when the zoom is changed, and
 * WINDOW_W and WINDOW_H are changed when the window is resized
 */ 
int WINDOW_W, WINDOW_H, CELL_W, CELL_H;

/* The offsets are for rendering */
/* Measured by # of pixels */
int offsetX, offsetY;

void initRender(int *going)
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL_Init error: %s\n", SDL_GetError());
        *going = 0;
        return;
    }
    
    /* These are all the default starting values */
    WINDOW_W = 500;
    WINDOW_H = 500;
    CELL_W = 10;
    CELL_H = 10;
    
    /* Create the main window and its surface */
    window = SDL_CreateWindow("Conway's Game of Life", 
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WINDOW_W,
                              WINDOW_H,
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
/* This is called after every game update and every event that could cause visual changes */
void draw(void)
{
    /* First, for testing, just render an area from (0, 0) to (60, 60) */
    /* Use CELL and WINDOW measurements to find out how many cells per row/column */
    
    /* If the window has changed size, get that size */
    if (getFirstInput(RESIZED))
    {
        WINDOW_W = getWindowW();
        WINDOW_H = getWindowH();
    }
    
    
    
    /* Actually draw the frame */
    SDL_UpdateWindowSurface(window);
}
















