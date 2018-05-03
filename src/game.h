typedef struct Cell_ Cell;
typedef struct Row_ Row;

void initGame(void);
void deinitGame(void);

int countNeighbors(int x, int y);

int cellExists(int x, int y);
Cell* getCell(int x, int y);
Row* getRow(int y);

void gameClick(int x, int y);

void step(void);
void gameLoop(int paused);
void gameDraw(void);