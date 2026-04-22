#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
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
Row* create_row(char* name, int age, char* career) {
    
    // Allocate memory and check malloc datatype
    Row* r = malloc(sizeof(Row));
    if (r == NULL) {
        assert(0);
    }

    // set data and pointers to next and prev rows
    strcpy(r->name, name);
    strcpy(r->career, career);
    r->age = age;
    r->prev_row = NULL;
    r->next_row = NULL;

    return r;
}

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

void display_row(Row* r) {
    printf("| Name: %s | Age: %d | Career: %s |\n", r->name, r->age, r->career);
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