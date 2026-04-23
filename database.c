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
Row* create_row(char* name, char* age, char* career) {
    
    // Allocate memory and check malloc datatype
    Row* r = malloc(sizeof(Row));
    if (r == NULL) {
        assert(0);
    }

    // set data and pointers to next and prev rows
    strcpy(r->name, name);
    strcpy(r->career, career);
    strcpy(r->age, age);
    r->prev_row = NULL;
    r->next_row = NULL;

    return r;
}

// Insert Row into table
int insert_row(Table* t, Row* r) {
    // if Table Empty
    if (t->head == NULL) {
        t->head = r;
        t->tail = r;
        return 1;
    }
    // if table not empty, connect row to last row
    t->tail->next_row = r;
    r->prev_row = t->tail;
    t->tail= r;
    return 1;
}

// Displays a row
void display_row(Row* r) {
    printf("%s, %s, %s", r->name, r->age, r->career);
}

// Displays table through stdout. Shows first n rows
void display_table(Table* t, int n) {
    // Iterate through database rows and display them
    if (n == 0) n = MAX_ITER;
    
    Row* r = t->head;
    int i = 0;
    while (r != NULL && i < n && i <= MAX_ITER) {
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
        
        // Seperate the line into substrings with a seperator of ","
        char cols[MAX_COLS][MAX_COL_CHARS]; // Maximum 20 cols, 64 characters per column
        char* token;
        int j = 0;
        while ((token = strsep(&line,",")) != NULL && j <= MAX_COLS) { 
            //printf("%s\n", token);
            strcpy(cols[j],token);
            j++;
        }
        //printf("%s %s %s",cols[0],cols[1], cols[2]);
        insert_row(t, create_row(cols[0], cols[1], cols[2]));
        
        i++; // MAX ITERS
    }
    fclose(file);
    return 0;
}