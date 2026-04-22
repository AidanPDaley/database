#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "database.h"


int main(void) {
    
    // REPL
    while(1) {
        char query[256]; // query can be up to 255 characters / bytes long
        Table* t = create_table();
        insert_row(t, create_row("Aidan", 26, "Unemployed"));
        insert_row(t, create_row("Ailie", 23, "Nurse"));
        insert_row(t, create_row("Annin", 22, "Unemployed"));
        insert_row(t, create_row("Abby", 20, "Unemployed"));
        insert_row(t, create_row("Dani", 21, "Vet Tech"));

        // User Input Query
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