enum keys { SPACE, S_KEY, ENTER, L_CLICK, R_CLICK, UP_ARROW, DOWN_ARROW,
            CTRL, EQUAL, MINUS, RESIZED, EMPTY, KEYS_LENGTH };

void initInputs(void);

/* Can modify the game's pause and going states */
/* Must be called at the beginning of each loop */
int updateInputs(void);
int handleInputs(int *paused, int *going);

/* Returns 1 if an inputs is pressed, 0 if not */
int getInput(int key);
/* Same as before, but only returns 1 if this is the first frame of 
 * the button being pressed
 */
int getFirstInput(int key);

int getWindowW(void);
int getWindowH(void);


























