#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "database.h"


int main(int argc, char *argv[]) {
    
    printf("\nReading from file: %s\n", argv[1]);
    printf("Type help for more info\n");
    // REPL
    while(1) {
        // Check correct number of arguments
        if (argc != 2)
            assert(0);
        char* path = argv[1];

        // Table
        Table* t = create_table();
        
        // Read csv file
        int fd = read_csv(path, t);
        if (fd == 1)
            assert(0);

        // User Input Query
        char query[256]; // query can be up to 255 characters / bytes long
        printf("?> ");
        fgets(query, sizeof(query), stdin);
        query[strcspn(query, "\n")] = 0; // rm \n

        // Basic Control flow, parser needed
        if (strcmp(query, "q") == 0 || strcmp(query, "quit") == 0) break;
        else if (strcmp(query, "print") == 0) display_table(t, 0);
        else if (strcmp(query, "help") == 0) printf("Commands Currently Available: help, print\n");
    }
    
    return 0;
}