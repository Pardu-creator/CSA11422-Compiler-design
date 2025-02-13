#include <stdio.h>
#include <ctype.h>
#include <string.h>

char input[100];  
int pos = 0;      
char currentChar() {
    return input[pos];
}

void consume() {
    if (input[pos] != '\0') {
        pos++;
    }
}

void matchId() {
    if (isalpha(currentChar())) {
        printf("Matched id: %c\n", currentChar());
        consume();
    } else {
        printf("Syntax Error: Expected id\n");
        exit();
    }
}

void factor() {
    if (currentChar() == '(') {
        consume(); 
        printf("Matched '('\n");
        E();  
        if (currentChar() == ')') {
            consume();  
            printf("Matched ')'\n");
        } else {
            printf("Syntax Error: Expected ')'\n");
            exit(1);
        }
    } else if (isalpha(currentChar())) {
        matchId(); 
    } else {
        printf("Syntax Error: Expected factor\n");
        exit(1);
    }
}

void TPrime() {
    if (currentChar() == '*') {
        consume(); 
        printf("Matched '*'\n");
        factor();  
        TPrime();   
    }
}

void T() {
    factor();  
    TPrime();  
}

void EPrime() {
    if (currentChar() == '+') {
        consume(); 
        printf("Matched '+'\n");
        T(); 
        EPrime(); 
    }
}

void E() {
    T(); 
    EPrime(); 
}

int main() {
    printf("Enter an arithmetic expression: ");
    scanf("%s", input);  
    E();  
    if (currentChar() == '\0') {
        printf("Parsing successful!\n");
    } else {
        printf("Syntax Error: Unexpected character '%c'\n", currentChar());
    }
    return 0;
}

