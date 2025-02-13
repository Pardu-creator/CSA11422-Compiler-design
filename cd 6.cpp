#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void eliminateLeftRecursion(char *nonTerminal, char productions[][100], int numProductions) {
    char newNonTerminal[2] = {nonTerminal[0], '\''};  
    char newProductions[10][100];  
    int newProductionCount = 0;
    
    printf("Eliminating left recursion for %s:\n", nonTerminal);

    printf("Original productions:\n");
    int nonRecursiveCount = 0;
    for (int i = 0; i < numProductions; i++) {
        printf("%s -> %s\n", nonTerminal, productions[i]);
        
        if (productions[i][0] == nonTerminal[0]) {
            char newProduction[100];
            sprintf(newProduction, "%s%s", nonTerminal, newNonTerminal);  // A -> ßA'
            strcpy(newProductions[newProductionCount], newProduction);
            newProductionCount++;
        } else {
            char newProduction[100];
            sprintf(newProduction, "%s%s", productions[i], newNonTerminal);  // A' -> aA'
            strcpy(newProductions[newProductionCount], newProduction);
            newProductionCount++;
        }
    }

    printf("New productions after eliminating left recursion:\n");

    for (int i = 0; i < nonRecursiveCount; i++) {
        printf("%s -> %s\n", nonTerminal, productions[i]);
    }

    for (int i = 0; i < newProductionCount; i++) {
        printf("%s -> %s\n", newNonTerminal, newProductions[i]);
    }
}

int main() {
    char nonTerminal[100], productions[10][100];
    int numProductions;

    printf("Enter the non-terminal for the grammar: ");
    scanf("%s", nonTerminal);
    
    printf("Enter the number of production rules: ");
    scanf("%d", &numProductions);

    printf("Enter the production rules for %s (one per line):\n", nonTerminal);
    for (int i = 0; i < numProductions; i++) {
        printf("Rule %d: ", i + 1);
        scanf("%s", productions[i]);
    }
    eliminateLeftRecursion(nonTerminal, productions, numProductions);
    
    return 0;
}

