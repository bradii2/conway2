#include "game.h"
#include "list.h"
#include <SDL2/SDL.h>

Row *currRows, *prevRows;

void initGame(void)
{
    currRows = createRow(0);
    prevRows = createRow(0);
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
    
    temp = prevRows;
    prevRows = currRows;
    currRows = temp;
    /* Now, use prevRows list to check each cell for neighbors. */
    /* Iterate through every row, and then every cell, and count neighbors for each cell. */
    for (r = prevRows; r->next != NULL; r = r->next)
    {
        for (c = r->cells; c->next != NULL; c = c->next)
        {  
            startFor:
            /* Now do the logic for adding and removing cells based on neighbor count */
            count = countNeighbors(c->x, r->y);
            
            /* If the cell is live, follow these rules */
            switch (count)
            {
            /* 2 or fewer, kills the cell */
            case 0: case 1:
                removeCell(&currRows, c->x);
                goto startFor;
                break;
            /* If 2 or 3 neighbors, the cell lives on */
            case 2: case 3:
                break;
             /* 4 or more neighbors kills the cell */
            case 4: case 5: case 6: case 7: case 8:
                removeCell(&currRows, c->x);
                goto startFor;
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
                        if ((temp = getRow(y)) != NULL)
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
    for (currCell = currRow->cells; (currCell != NULL) && (currCell->next != NULL); currCell = currCell->next)
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












