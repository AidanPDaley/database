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
        assert(0);
    }
    t->head = NULL;
    t->tail = NULL;

    return t;
}

// Create row struct
Row* create_row(char* cols[MAX_COLS]) { 
    // Allocate memory for row
    Row* r = (Row*) malloc(sizeof(Row));

    // Allocate Memory for cols
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

// Free the memory stored in cols (char*[]) in the row struct
void delete_cols(char* cols[]) {
    for (int i = 0; cols[i] != NULL && i < MAX_COLS ; i++) {
        if (cols[i] != NULL) {
            free(cols[i]);
            cols[i] = NULL;
        }
    }
}

// free the row
void delete_row(Row* r) {
    delete_cols(r->cols);
    free(r);
}

// Free table. Includes freeing the rows and the data cols in the rows
void delete_table(Table* t) {
    printf("Deleting Table...\n");
    // Null table or empty table
    if (t == NULL)
        assert(0);
    else if (t->head == NULL) {
        free(t);
        return;
    }
    // Table with rows
    Row* temp = t->head;
    int i = 0;
    while (temp != NULL && i <= MAX_ITER) {
        Row* next = temp->next_row;
        delete_row(temp);
        temp = next;
        i++;
    }
    free(t);
    printf("Table Deleted\n");
}


// Displays row
void display_row(Row* r) {
    char col_str[MAX_COLS * MAX_COL_CHARS] = "";
    
    int i = 0;
    while (r->cols[i] != NULL && i <= MAX_COLS) {
        strncat(col_str, r->cols[i], strlen(r->cols[i]));
        strncat(col_str, " ", 1);
        i++;
    }
    printf("%s\n", col_str);
}

// Display the head / first row in table
void display_head(Table* t) {
    printf("HEAD: ");
    display_row(t->head);
}

// Display the tail / last row in the table
void display_tail(Table* t) {
    printf("TAIL: ");
    display_row(t->tail);
}

// Displays table. Shows first n rows. If n == 0, show all rows
void display_table(Table* t, int n) {
    if (t == NULL) {
        printf("Table does not exist\n");
        return;
    }
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

// Read the source csv file that is pased with the executable through stdin
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