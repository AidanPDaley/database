#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "database.h"


// Create Table that will store data, head, tail
Table* create_table(void) {

    // Allocate memory and check malloc datatype
    Table* t = (Table*) malloc(sizeof(Table));

    // Check malloc return type
    if (t == NULL) {
        // Handle Error Later
        assert(0);
    }
    t->head = NULL;
    t->tail = NULL;

    return t;
}

// Create row struct
Row* create_row(char* cols[MAX_COLS]) {
    //printf("Creating row\n");    
    // Allocate memory for row
    Row* r = (Row*) malloc(sizeof(Row));
    if (r == NULL) {
        assert(0);
    }

    // Allocate Memory for cols because they may be temp pointers
    int i = 0;
    while (cols[i] != NULL && i <= MAX_COLS) {
        r->cols[i] = (char*) malloc(strlen(cols[i]) + 1);
        if (r->cols[i] == NULL) assert(0);
         
        strcpy(r->cols[i], cols[i]);
        i++;
    }

    
    // set data and pointers to next and prev rows
    r->prev_row = NULL;
    r->next_row = NULL;
    //printf("created row\n");
    return r;
}

// Insert Row into table
int insert_row(Table* t, Row* r) {
    // if Table Empty
    if (t->head == NULL) {
        //printf("INSERTING FIRST ROW\n");
        t->head = r;
        t->tail = r;
        return 1;
    }
    //printf("INSERTING SECOND\n");
    r->prev_row = t->tail;
    t->tail->next_row = r;
    t->tail = r;
    return 1;
}

void display_head(Table* t) {
    printf("HEAD: ");
    display_row(t->head);
}

void display_tail(Table* t) {
    printf("TAIL: ");
    display_row(t->tail);
}

// Displays row
void display_row(Row* r) {
    char col_str[MAX_COLS * MAX_COL_CHARS] = "";
    
    int i = 0;
    while (r->cols[i] != NULL && i <= MAX_COLS) {
        // strncat used to prevent buffer overflows
        strncat(col_str, r->cols[i], strlen(r->cols[i]));
        strncat(col_str, " ", 1);
        i++;
    }
    printf("%s\n", col_str);
}

// Displays table. Shows first n rows
void display_table(Table* t, int n) {
    // Iterate through database rows and display them
    if (n == 0) n = MAX_ITER;
    
    Row* r = t->head;
    int i = 0;
    while (r != NULL && i <= n && i <= MAX_ITER) {
        display_row(r);
        r = r->next_row;
        i++;
    }
}

int read_csv(char* path, Table* t) {
    FILE* file = fopen(path, "r");
    if (file == NULL)
        return 1;
    
    // Read CSV Line by Line
    char* line;
    char buffer[256];
    int i = 0;
    while((line = fgets(buffer, sizeof(buffer), file)) != NULL && i < MAX_ITER) {
        // Remove \n at the end of line
        line[strcspn(line, "\n")] = '\0'; 

        // Seperate the line into substrings based on the seperator ","
        char* cols[MAX_COLS] = {};
        int j = 0;
        char *token;
        while ((token = strsep(&line, ",")) != NULL) {
            cols[j] = token;
            j++;
        }

        // Create New Row and add to table
        Row* r = create_row(cols);
        insert_row(t, r);
    }
    fclose(file);
    return 0;
}