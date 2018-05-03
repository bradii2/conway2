#include "game.h"
#include "list.h"
#include "inputs.h"
#include "render.h"
#include <stdio.h>
#include <SDL2/SDL.h>

Row *currRows, *prevRows;

int updateDelay = 300;

void step(void);
/* Define the functions for key presses here */
void clearBoard(void);
void onClick(void);
void changeSpeed(void);
void stepAndDraw(void);

/* Left click makes cells, right click destroys them */
Mouse *mouse;

void initGame(void)
{
    currRows = createRow(0);
    prevRows = createRow(0);
    
    setKeyFunc(Q_KEY, stepAndDraw); /* Step */
    setKeyFunc(ENTER, clearBoard); /* Kill all cells */
    setKeyFunc(L_CLICK, onClick); /* Create cell */
    setKeyFunc(R_CLICK, onClick); /* Kill cell */
    setKeyFunc(DOWN_ARROW, changeSpeed); /* Make slower */
    setKeyFunc(UP_ARROW, changeSpeed); /* Make faster */
    
    mouse = getMouse();
}
void deinitGame(void)
{
    destroyRows(&currRows);
    destroyRows(&prevRows);
}

void step(void)
{
    /* Step 1: swap the current rows and previous rows */
    Row *temp;
    Row *r;
    Cell *c;
    
    int count;
    int x, y;
    
    /* Swap prevRows and currRows in the fastest way possible, no copying of the entire array */
    temp = prevRows;
    prevRows = currRows;
    currRows = temp;
    
    /* Now, use prevRows list to check each cell for neighbors. */
    /* Iterate through every row, and then every cell, and count neighbors for each cell. */
    for (r = prevRows; r->next != NULL; r = r->next)
    {
        for (c = r->cells; c->next != NULL; c = c->next)
        {  
            /* Now do the logic for adding and removing cells based on neighbor count */
            count = countNeighbors(c->x, r->y);
            
            /* If the cell is live, follow these rules */
            switch (count)
            {
            /* 2 or fewer, kills the cell */
            case 0: case 1:
                removeCell(&(r->cells), c->x);
                break;
            /* If 2 or 3 neighbors, the cell lives on */
            case 2: case 3:
                break;
             /* 4 or more neighbors kills the cell */
            case 4: case 5: case 6: case 7: case 8:
                removeCell(&(r->cells), c->x);
                break;
            default:
                printf("You should not have this message appear!\n");
                printf("Cell x: %2d\ty: %2d\n", c->x, r->y);
                printf("Neighbors: %d\n", count);
                break;
            }
            /* Now, iterate through every neighbor of every cell to check if we  
             * need to make a live cell (3 live surrounding a dead -> live cell)
             */
             
            for (x = c->x - 1; x <= c->x + 1; ++x)
            {
                for (y = r->y; y <= r->y + 1; ++y)
                {
                    count = countNeighbors(x, y);
                    /* If there are exactly 3 neighbors, add the cell */
                    if (count == 3)
                    {
                        /* If the row doesn't exist, add it */
                        if ((temp = getRow(y)) == NULL)
                        {
                            addRow(&currRows, createRow(y));
                        }
                        /* Now, add the cell */
                        else
                            temp = getRow(y);
                        addCell(&(temp->cells), createCell(x));
                    } /* End makeLive */
                } /* End y for */
            } /* End x for */
        }
    }
}

/* TODO: add argument Row *head, and make curr = head, and in onClick pass currRows. else prev */
Row* getRow(int y)
{
    Row *curr;
    for (curr = prevRows; curr != NULL && curr->next != NULL; curr = curr->next)
    {
        if (curr->y == y)
            return curr;
    }
    return NULL;
}
int rowExists(int y)
{
    return (getRow(y) != NULL);
}

/* This function will need to find neighbors of dead rows/cells too! */
int countNeighbors(int x, int y)
{
    int currX, currY; /* x and y offsets */
    int count;
    
    count = 0;
    for (currX = x - 1; currX <= x + 1; ++currX)
    {
        for (currY = y - 1; currY <= y + 1; ++currY)
        {
            if (cellExists(currX, currY))
                ++count;
        }
    }
    /* If the current cell exists (isn't a dead cell), remove it from the count */
    if (cellExists(x, y))
        --count;
    return count;
}

int cellExists(int x, int y)
{
    if (getCell(x, y) == NULL)
        return 0;
    return 1;
}

Cell *getCell(int x, int y)
{
    Row *currRow;
    Cell *currCell;
    
    for (currRow = prevRows; currRow->next != NULL; currRow = currRow->next)
    {
        if (currRow->y == y)
            break;
    }
    /* If there is nothing in the row */
    if (currRow->next == NULL && currRow->y != y)
        return NULL;
    for (currCell = currRow->cells; (currCell != NULL) && (currCell->next != NULL); 
         currCell = currCell->next)
    {
        if (currCell->x == x)
            break;
    }
    /* If there is no cell matching the given x value */
    /* You must check for if the cell itself is null first 
     * so that no errors occur when looking for NULL->next
     */
    if (currCell == NULL || (currCell->next == NULL && currCell->x != x))
        return NULL;
    /* If the cell is found */
    return currCell;
}


void clearBoard(void)
{
    /* Remove the entire tree, then make a tree with a NULL cell list at y = 0 */
    destroyRows(&currRows);
    destroyRows(&prevRows);
    
    currRows = createRow(0);
    prevRows = createRow(0);
}
/* TODO: stop this from crashing the program */
void onClick(void)
{
    int x, y; /* The x, y of THE CELL the mouse is over */
    Row *r;
    
    x = mouse->x;
    y = mouse->y;
    
    /* Left click */
    if (getInput(L_CLICK))
    {
        printf("Left click\n");
        /* See if we can find the cell */
        if (cellExists(x, y))
            return;
        
        /* Cell does not exist, so let's make it */
        /* Make sure the row exists too */
        /* If not, make one now */
        if ((r = getRow(y)) == NULL)
            addRow(&currRows, r = createRow(y));
        printf("Adding the cell\n");
        /* Now, add the cell to the row */
        /* TODO: IMPORTANT: fix addCell()! */
        addCell(&(r->cells), createCell(x));
        printf("Done!\n");
    }
    /* Right click */
    else if (getInput(R_CLICK))
    {
        printf("Right click\n");
        /* Check if a cell exists. if so, get it, and delete it */
        /* If there is no cell where you right click, then don't do anything */
        if (!cellExists(x, y))
            return;
        
        /* At this point, the cell exists, so delete it */
        removeCell(&((getRow(y))->cells), x);
    }
    else
        printf("onClick() called without mouse click!\n");
}
void changeSpeed(void)
{
    /* Every frame where MINUS is held, make the game slower */
    if (getInput(DOWN_ARROW))
    {
        /* Maximum delay of 1000 */
        updateDelay = (updateDelay + 10 > 1000) ? 1000 : updateDelay + 10;
    }
    /* If plus is held, then make it faster */
    else if (getInput(UP_ARROW))
    {
        /* Minumum dealy of 10 */
        updateDelay = (updateDelay - 10 < 10) ? 10 : updateDelay - 10;
    }
    else
    {
        printf("changeSpeed called without - or + being pressed!\n");
    }
}

/* If the time passed is >= updateDelay, then step and decrement lag */
void gameLoop(int paused)
{
    /* These variables only get initialized once, and the same values transfer across calls */
    static int currTime = 0;
    static int prevTime = 0;
    if (currTime == 0)
        prevTime = currTime = SDL_GetTicks();
    
    if (paused)
        /* prevTime + (non-0) is always > currTime, and after game unpaused, it doesn't
         * rush to "catch back up" with the lost time this way.
         */
        currTime = prevTime = SDL_GetTicks();
    
    for (currTime = SDL_GetTicks(); prevTime + updateDelay <= currTime; prevTime += updateDelay)
        step();
}
void stepAndDraw(void)
{
    /* Only run on the first key input */
    if (getFirstInput(Q_KEY))
    {
        step();
        draw(currRows);
    }
}
void gameDraw(void)
{
    draw(currRows);
}


















