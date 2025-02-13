#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_IDENTIFIER_LENGTH 100

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>' || c == '!' || c == '&' || c == '|');
}

void tokenize(const char *source) {
    int i = 0;
    char currentChar;

    while ((currentChar = source[i]) != '\0') {
        if (isspace(currentChar)) {
            i++;
            continue;
        }

        if (currentChar == '/' && source[i + 1] == '/') {
            printf("Single-line comment: ");
            i += 2; 
            while (source[i] != '\n' && source[i] != '\0') {
                putchar(source[i]);
                i++;
            }
            putchar('\n');
            continue;
        }

        if (currentChar == '/' && source[i + 1] == '*') {
            printf("Multi-line comment: ");
            i += 2; 
            while (!(source[i] == '*' && source[i + 1] == '/') && source[i] != '\0') {
                putchar(source[i]);
                i++;
            }
            if (source[i] == '*' && source[i + 1] == '/') {
                i += 2;
            }
            putchar('\n');
            continue;
        }

        if (isalpha(currentChar) || currentChar == '_') {
            char identifier[MAX_IDENTIFIER_LENGTH];
            int identifierIndex = 0;
            while (isalnum(source[i]) || source[i] == '_') {
                if (identifierIndex < MAX_IDENTIFIER_LENGTH - 1) {
                    identifier[identifierIndex++] = source[i];
                }
                i++;
            }
            identifier[identifierIndex] = '\0';
            printf("Identifier: %s\n", identifier);
            continue;
        }

        if (isdigit(currentChar)) {
            char constant[20];
            int constantIndex = 0;
            while (isdigit(source[i])) {
                if (constantIndex < 19) {
                    constant[constantIndex++] = source[i];
                }
                i++;
            }
            constant[constantIndex] = '\0';
            printf("Constant: %s\n", constant);
            continue;
        }

        if (isOperator(currentChar)) {
            printf("Operator: %c\n", currentChar);
            i++;
            continue;
        }

        printf("Unknown character: %c\n", currentChar);
        i++;
    }
}

int main() {
    const char *sourceCode = "int main() {\n"
                             "    // This is a single-line comment\n"
                             "    int a = 5; /* This is a multi-line comment */\n"
                             "    int b = a + 10;\n"
                             "    return 0;\n"
                             "}\n";

    tokenize(sourceCode);
    return 0;
}
