#include "render.h"
#include "game.h"
#include "list.h"
#include "inputs.h"
#include <stdio.h>
#include "SDL2/SDL.h"

#define CELL_DEFAULT 50.0

SDL_Window  *window;
SDL_Surface *windowSurface;
SDL_Surface *greySurface;
SDL_Surface *whiteSurface;
SDL_Surface *blackSurface;

/* CELL_W and CELL_H are changed when the zoom is changed, and
 * WINDOW_W and WINDOW_H are changed when the window is resized
 */ 
int CELL_W, CELL_H;
int zoom = 100;

/* Keypress functions */
void windowResized(void);
void zoomChange(void);
void moveWindow(void); /* moveWindow is for when the inner window moves, not the whole program */

int initRender(int *going)
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL_Init error: %s\n", SDL_GetError());
        *going = 0;
        return 1;
    }
    
    /* These are all the default starting values */
    WINDOW_W = 500;
    WINDOW_H = 500;
    CELL_W = 10;
    CELL_H = 10;
    offsetX = 0;
    offsetY = 0;
    
    
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
    
    /* Here, init the functions for inputs */
    setKeyFunc(RESIZED, windowResized);
    setKeyFunc(W_KEY, moveWindow);
    setKeyFunc(A_KEY, moveWindow);
    setKeyFunc(S_KEY, moveWindow);
    setKeyFunc(D_KEY, moveWindow);
    setKeyFunc(EQUAL, zoomChange);
    setKeyFunc(MINUS, zoomChange);
    return 0;
}
void deinitRender(void)
{
    SDL_FreeSurface(windowSurface);
    SDL_FreeSurface(greySurface);
    SDL_FreeSurface(whiteSurface);
    SDL_FreeSurface(blackSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/* TODO: get this up and running */
/* This is called after every game update and every event that could cause visual changes */
void draw(Row *head)
{
    Cell *currC;
    Row *currR;
    SDL_Rect cell;
    
    cell.w = CELL_W;
    cell.h = CELL_H;
    /* First, for testing, just render an area from (0, 0) to (60, 60) */
    /* Use CELL and WINDOW measurements to find out how many cells per row/column */
    
    
    /* Draw background (grey), then cells */
    SDL_BlitScaled(blackSurface, NULL, windowSurface, NULL);
    
    /* Iterate through the list of cells, and if it's within the bounds, draw it */
    /* I hope this works lol */
    for (currR = head; currR != NULL; currR = currR->next)
    {
        for (currC = currR->cells; currC != NULL /*&& currC->next != NULL*/; currC = currC->next)
        {
            cell.x = currC->x * CELL_W + offsetX;
            cell.y = currR->y * CELL_H + offsetY;
            if (cell.x > 0 && cell.x + cell.w < WINDOW_W && 
                cell.y > 0 && cell.y + cell.h < WINDOW_H)
                {
                    printf("Blitting white surface\n");
                    SDL_BlitScaled(whiteSurface, NULL, windowSurface, &cell);
                }
        }
    }
    
    /* Actually draw the frame */
    SDL_UpdateWindowSurface(window);
}

/* Some inputs are handled by render - like window resizing and zooming */
void windowResized(void)
{
    WINDOW_W = getWindowW();
    WINDOW_H = getWindowH();
    
}
void zoomChange(void)
{
    if (getFirstInput(EQUAL))
        zoom += 1;
    if (getFirstInput(MINUS))
        zoom -= 1;
    
    if (zoom < 10)
        zoom = 10;
    else if (zoom > 200)
        zoom = 200;
    
    CELL_W = CELL_H = (int) ((zoom / 100.0) * CELL_DEFAULT);
}
void moveWindow(void)
{
    offsetX += getInput(D_KEY);
    offsetX -= getInput(A_KEY);
    offsetY += getInput(S_KEY);
    offsetY -= getInput(W_KEY);
}










