#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPR_LENGTH 100

void generateAssembly(const char *expression) {
    char *token;
    char *exprCopy = strdup(expression);
    char *delim = " ";
    printf("; Assembly code generated from expression: %s\n", expression);
    printf("section .data\n");
    printf("    result db 0\n");
    printf("section .text\n");
    printf("global _start\n");
    printf("_start:\n");
    token = strtok(exprCopy, delim);
    int tempVarCount = 0;

    while (token != NULL) {
        if (strcmp(token, "+") == 0) {
            printf("    ; Addition operation\n");
            printf("    mov al, [var1]\n");
            printf("    add al, [var2]\n");
            printf("    mov [result], al\n");
        } else if (strcmp(token, "*") == 0) {
            printf("    ; Multiplication operation\n");
            printf("    mov al, [var2]\n");
            printf("    mul [var3]\n");
            printf("    mov [result], al\n");
        } else {
            printf("    mov [%s], al\n", token);
        }
        token = strtok(NULL, delim);
    }

    printf("    ; Exit the program\n");
    printf("    mov eax, 1\n");
    printf("    int 0x80\n");

    free(exprCopy); 
}

int main() {
    char expression[MAX_EXPR_LENGTH];

    printf("Enter a simple arithmetic expression (e.g., a + b * c): ");
    fgets(expression, MAX_EXPR_LENGTH, stdin);
    expression[strcspn(expression, "\n")] = 0;
    generateAssembly(expression);

    return 0;
}
