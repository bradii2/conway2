typedef struct Cell_
{
    int x;
    struct Cell_ *next;
} Cell;

typedef struct Row_
{
    int y;
    Cell *cells;
    struct Row_ *next;
} Row;

Cell* createCell(int x);
void addCell(Cell **head, Cell *c);
void freeCell(Cell **c);
void destroyCells(Cell **head);
void removeCell(Cell **head, int x);

Row* createRow(int y);
void addRow(Row **head, Row *r);
void freeRow(Row **head);
void destroyRows(Row **head);
void removeRow(Row **head, int y);


















