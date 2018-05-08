#include "inputs.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>

SDL_Event e;

Mouse *mouse;

int currKeys[KEYS_LENGTH];
int prevKeys[KEYS_LENGTH];

/* Make an array of funciton pointers */
typedef void (*func_ptr)(void);
func_ptr keyFuncs[KEYS_LENGTH];

/* Variable to tell if the program should be stopped */
int stop = 0;
int winW = 0;
int winH = 0;

void initInputs(void)
{
    int i;
    for (i = 0; i < KEYS_LENGTH; ++i)
    {
        currKeys[i] = prevKeys[i] = 0;
        keyFuncs[i] = NULL;
    }
    mouse = (Mouse*) malloc(sizeof(Mouse));
}
void deinitInputs(void)
{
    free(mouse);
}
void updateInputs(void)
{
    int i;
    for (i = 0; i < KEYS_LENGTH; ++i)
        prevKeys[i] = currKeys[i];
    while (SDL_PollEvent(&e))
    {
        switch(e.type)
        {
        case SDL_QUIT:
            stop = 1;
            break;
        /* Keyboard Event */
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            switch (e.key.keysym.sym)
            {
            case SDLK_SPACE:
                i = SPACE;
                break;
            case SDLK_s:
                i = S_KEY;
                break;
            case SDLK_LCTRL:
            case SDLK_RCTRL:
                i = CTRL;
                break;
            case SDLK_RETURN:
            case SDLK_RETURN2:
                i = ENTER;
                break;
            case SDLK_UP:
                i = UP_ARROW;
                break;
            case SDLK_DOWN:
                i = DOWN_ARROW;
                break;
            /* = is on the same button as +, so that's used for zooming in */
            case SDLK_EQUALS:
                i = EQUAL;
                break;
            case SDLK_MINUS:
                i = MINUS;
                break;
            default:
                i = EMPTY;
                break;
            }
            currKeys[i] = e.key.state == SDL_PRESSED;
            break;
        /* Mosue Press */
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            switch(e.button.button)
            {
            case SDL_BUTTON_LEFT:
                i = L_CLICK;
                break;
            case SDL_BUTTON_RIGHT:
                i = R_CLICK;
                break;
            default:
                i = EMPTY;
                break;
            }
            currKeys[i] = e.button.state == SDL_PRESSED;
            break;
        /* Mouse Movement */
        case SDL_MOUSEMOTION:
            mouse->x = e.motion.x;
            mouse->y = e.motion.y;
            break;
        /* Window Event */
        case SDL_WINDOWEVENT:
            /* We only care about window resizes here */
            if (e.window.event != SDL_WINDOWEVENT_RESIZED)
                break;
            winW = e.window.data1;
            winH = e.window.data2;
            i = RESIZED;
            /* TODO: */
            /* We have to set this to 0 if SDL_WINDOWEVENT_RESIZED is not called in a frame! */
            /* Do this in render.c after checking for this key? But then other files 
             * would have direct access to currKeys[]...
             * Or, we could just check the size every frame... it's unnecessary, but won't slow the program down noticeably
             */
            currKeys[i] = 1;
            break;
        default:
            break;
        }
    }
    
}

int getInput(int num)
{
    if (num < 0 || num > KEYS_LENGTH)
        return 0;
    return currKeys[num];
}
int getFirstInput(int num)
{
    if (num < 0 || num > KEYS_LENGTH)
        return 0;
    return currKeys[num] && !prevKeys[num];
}

/* TODO: finish this */
void handleInputs(int *paused, int *going)
{
    int i;
    /* Tell the program to stop if you are trying to close the window */
    if (stop)
    {
        *going = 0;
        return;
    }
    /* Set PAUSED when spacebar is pressed */
    if (getFirstInput(SPACE))
        *paused = !(*paused);
    
    /* Now, for the real stuff */
    /* Because most buttons do something that should happen in different parts of the program, 
     * we pass a funciton to call and store it in an array from setKeyFunc() function
     */
    for (i = 0; i < KEYS_LENGTH; ++i)
    {
        if (keyFuncs[i] == NULL)
            continue;
        /* If the funciton doensn't need to be called... */
        if (!getInput(i))
            continue;
        /* If the funciton exists, call it */
        keyFuncs[i]();
    }
}

/* Arguments: f = a void-returning function with no arguments 
 *            key = the key that will call the function when pressed
 */
void setKeyFunc(int key, void (*f)(void))
{
    if (key < 0 || key >= KEYS_LENGTH)
        return;
    printf("Setting key function: %d\n", key);
    keyFuncs[key] = f;
}

int getWindowW(void)
{
    return winW;
}
int getWindowH(void)
{
    return winH;
}

Mouse* getMouse(void)
{
    return mouse;
}







































