extern struct Cell;
extern struct Row;

void initGame(void);
void deinitGame(void);

int countNeighbors(int x, int y);

int cellExists(int x, int y);
Cell* getCell(int x, int y);
Row* getRow(int y);

void step(void);