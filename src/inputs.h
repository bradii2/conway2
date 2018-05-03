enum keys { SPACE, Q_KEY, W_KEY, A_KEY, S_KEY, D_KEY, ENTER, L_CLICK, R_CLICK, UP_ARROW, DOWN_ARROW,
            CTRL, EQUAL, MINUS, RESIZED, EMPTY, KEYS_LENGTH };

/*  Space: pause/play
 *  Q_KEY: step
 *  ?_KEY: move the inner window
 *  ENTER: clear the board
 *  L_CLICK: create a cell
 *  R_CLICK: delete a cell
 *  ?_ARROW: either run faster or slower
 *  EQUAL: Zoom in
 *  MINUS: Zoom out 
 *  RESIZED: called when the window is resized
 */

typedef struct Mouse_t
{
    int x, y;
} Mouse;

void initInputs(void);
void deinitInputs(void);

/* Can modify the game's pause and going states */
/* Must be called at the beginning of each loop */
void updateInputs(void);
void handleInputs(int *paused, int *going);

/* Returns 1 if an inputs is pressed, 0 if not */
int getInput(int key);
/* Same as before, but only returns 1 if this is the first frame of 
 * the button being pressed
 */
int getFirstInput(int key);

void setKeyFunc(int key, void (*f)(void));

int getWindowW(void);
int getWindowH(void);


Mouse* getMouse(void);























