#include "inputs.h"
#include <SDL2/SDL.h>

SDL_Event e;

int currKeys[KEYS_LENGTH];
int prevKeys[KEYS_LENGTH];

/* Variable to tell if the program should be stopped */
int stop = 0;
int winW = 0;
int winH = 0;

struct
{
    int x, y;
} Mouse;

void initInptus(void)
{
    int i;
    for (i = 0; i < KEYS_LENGTH; ++i)
    {
        currKeys[i] = 0;
        prevKeys[i] = 0;
    }
}

int updateInputs(void)
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
            Mouse.x = e.motion.x;
            Mouse.y = e.motion.y;
            break;
        /* Window Event */
        case SDL_WINDOWEVENT:
            /* We only care about window resizes here */
            if (e.event != SDL_WINDOWEVENT_RESIZED)
                break;
            winW = e.window.data1;
            winH = e.window.data2;
            i = RESIZED;
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
    if (stop)
    {
        *going = 0;
        break;
    }
    if (getFirstInput(SPACE))
        *paused = !(*paused);
}

int getWindowW(void)
{
    return winW;
}
int getWindowH(void)
{
    return winH;
}









































