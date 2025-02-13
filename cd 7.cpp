#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>  // Include this header for strcpy and strcspn

#define MAX_INPUT_SIZE 100

char input[MAX_INPUT_SIZE];
int pos = 0;
char current_char;

void next_char() {
    current_char = input[pos++];
}

int match(char expected) {
    if (current_char == expected) {
        next_char();
        return 1;
    }
    return 0;
}

void Factor() {
    if (current_char == '(') {
        match('(');
        Expression();
        match(')');
    } else if (isdigit(current_char)) {
        while (isdigit(current_char)) {
            next_char();
        }
    } else {
        printf("Syntax error: Expected number or '('\n");
        exit(1);
    }
}

void TermPrime() {
    if (current_char == '*') {
        match('*');
        Factor();
        TermPrime();
    }
}

void Term() {
    Factor();
    TermPrime();
}

void ExpressionPrime() {
    if (current_char == '+') {
        match('+');
        Term();
        ExpressionPrime();
    }
}

void Expression() {
    Term();
    ExpressionPrime();
}

void parse(char* input_str) {
    strcpy(input, input_str);
    pos = 0;
    next_char();

    Expression();

    if (current_char == '\0') {
        printf("Parsing successful: The input is valid.\n");
    } else {
        printf("Syntax error: Unexpected character '%c'.\n", current_char);
    }
}

int main() {
    char input_str[MAX_INPUT_SIZE];

    printf("Enter an arithmetic expression: ");
    fgets(input_str, MAX_INPUT_SIZE, stdin);

    input_str[strcspn(input_str, "\n")] = 0;

    parse(input_str);

    return 0;
}

