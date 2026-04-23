#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "database.h"


int main(int argc, char *argv[]) {
    
    printf("Reading from file: %s\n", argv[1]);
    // REPL
    while(1) {
        if (argc != 2)
            assert(0);
        char* path = argv[1];

        // Table
        Table* t = create_table();
        int fd = read_csv(path, t);
        if (fd == 1)
            assert(0);
        /*
        insert_row(t, create_row("Aidan", 26, "Unemployed"));
        insert_row(t, create_row("Ailie", 23, "Nurse"));
        insert_row(t, create_row("Annin", 22, "Unemployed"));
        insert_row(t, create_row("Abby", 20, "Unemployed"));
        insert_row(t, create_row("Dani", 21, "Vet Tech"));
        */

        // User Input Query
        char query[256]; // query can be up to 255 characters / bytes long
        printf("?> ");
        fgets(query, sizeof(query), stdin);
        query[strcspn(query, "\n")] = 0; // rm \n
        
        // Parser Goes here
        // printf("Query Given: %s", query);

        // Basic Control flow
        if (strcmp(query, "q") == 0 || strcmp(query, "quit") == 0) break;
        else if (strcmp(query, "print") == 0) display_table(t, 0);
    }
    
    return 0;
}