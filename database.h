#ifndef DATABASE_H
#define DATABASE_H
#define MAX_ITER 10000
#define MAX_COLS 20
#define MAX_COL_CHARS 64


// prototype table with set column types
// Double Linked List
typedef struct Row {
    char* cols[MAX_COLS];
    struct Row* prev_row;
    struct Row* next_row;
} Row;

typedef struct {
    Row* head;
    Row* tail;
} Table;

Table* create_table(void);
Row* create_row(char* cols[MAX_COLS]);
int insert_row(Table* t, Row* r);
void display_row(Row* r);
void display_table(Table* t, int n);

int read_csv(char* path, Table* t);
void display_head(Table* t);
void display_tail(Table* t);


#endif