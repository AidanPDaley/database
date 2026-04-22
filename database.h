#ifndef DATABASE_H
#define DATABASE_H
#define MAX_ITER 10000


// prototype table with set column types
// Double Linked List
typedef struct Row {
    char name[64];
    int  age;
    char career[64];
    struct Row* prev_row;
    struct Row* next_row;
} Row;

typedef struct {
    Row* head;
    Row* tail;
} Table;

// Done
Table* create_table(void);
Row* create_row(char* name, int age, char* career);
int insert_row(Table* t, Row* r);
void display_row(Row* r);
void display_table(Table* t, int n);

#endif