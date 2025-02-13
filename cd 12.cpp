#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_VAR_LENGTH 10
#define MAX_CODE_LENGTH 100

typedef struct {
    char code[MAX_CODE_LENGTH][50];
    int index;
} TAC;

// Function to create a new temporary variable
char* newTemp() {
    static int tempCount = 0;
    static char tempVar[MAX_VAR_LENGTH];
    sprintf(tempVar, "t%d", tempCount++);
    return tempVar;
}

// Function to generate three-address code for an expression
void generateTAC(char* expression, TAC* tac) {
    char* token = strtok(expression, " ");
    char* stack[MAX_CODE_LENGTH];
    int top = -1;

    while (token != NULL) {
        if (isalnum(token[0])) {
            stack[++top] = token;
        } else {
            char* op2 = stack[top--];
            char* op1 = stack[top--];
            char* tempVar = newTemp();
            sprintf(tac->code[tac->index++], "%s = %s %s %s", tempVar, op1, token, op2);
            stack[++top] = tempVar;
        }
        token = strtok(NULL, " ");
    }
}

int main() {
    char expression[100];
    TAC tac;
    tac.index = 0;

    printf("Enter an expression (e.g., a b c + d * e -): ");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = 0;

    generateTAC(expression, &tac);
    printf("\nThree-Address Code:\n");
    for (int i = 0; i < tac.index; i++) {
        printf("%s\n", tac.code[i]);
    }

    return 0;
}
