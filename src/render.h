typedef struct Row_ Row;

int WINDOW_W, WINDOW_H;
int offsetX, offsetY;

int initRender(int *going);
void deinitRender(void);
void draw(Row *head);