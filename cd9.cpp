#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const char *input;
int pos = 0;
int isDigit(char c) {
    return c >= '0' && c <= '9';
}
int parseNumber() {
    int value = 0;
    while (isDigit(input[pos])) {
        value = value * 10 + (input[pos] - '0');
        pos++;
    }
    return value;
}
int parseFactor() {
    if (input[pos] == '(') {
        pos++; 
        int result = parseExpression();
        if (input[pos] == ')') {
            pos++; // Skip ')'
            return result;
        } else {
            printf("Error: Expected ')'\n");
            exit(1);
        }
    } else if (isDigit(input[pos])) {
        return parseNumber();
    } else {
        printf("Error: Expected a number or '('\n");
        exit(1);
    }
}
int parseTerm() {
    int result = parseFactor();
    while (input[pos] == '*' || input[pos] == '/') {
        char op = input[pos++];
        int nextFactor = parseFactor();
        if (op == '*') {
            result *= nextFactor;
        } else {
            result /= nextFactor;
        }
    }
    return result;
}
int parseExpression() {
    int result = parseTerm();
    while (input[pos] == '+' || input[pos] == '-') {
        char op = input[pos++];
        int nextTerm = parseTerm();
        if (op == '+') {
            result += nextTerm;
        } else {
            result -= nextTerm;
        }
    }
    return result;
}
void checkEnd() {
    if (input[pos] != '\0') {
        printf("Error: Unexpected character '%c' at position %d\n", input[pos], pos);
        exit(1);
    }
}

int main() {
    input = "3 + 5 * (2 - 8)";
    char *cleanedInput = malloc(strlen(input) + 1);
    char *ptr = cleanedInput;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] != ' ') {
            *ptr++ = input[i];
        }
    }
    *ptr = '\0';
    input = cleanedInput;

    printf("Input: %s\n", input);
    int result = parseExpression();
    checkEnd(); 
    printf("The expression is valid. Result: %d\n", result);

    free(cleanedInput);
    return 0;
}
