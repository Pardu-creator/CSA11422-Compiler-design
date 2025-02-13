#include <stdio.h>
#include <ctype.h>

int main() {
    int characterCount = 0; // To count characters
    int wordCount = 0;      
    int lineCount = 0;      
    int inWord = 0;         
    char ch;

    printf("Enter text (Press Ctrl+D to end input on Unix/Linux or Ctrl+Z on Windows):\n");

    while ((ch = getchar()) != EOF) {
        characterCount++; 

        if (ch == '\n') {
            lineCount++;
        }

        if (isspace(ch)) {
            if (inWord) {
                inWord = 0; 
            }
        } else {
            if (!inWord) {
                inWord = 1; 
                wordCount++;
            }
        }
    }

    if (characterCount > 0 && ch != '\n') {
        lineCount++;
    }

    printf("\nResults:\n");
    printf("Total Characters: %d\n", characterCount);
    printf("Total Words: %d\n", wordCount);
    printf("Total Lines: %d\n", lineCount);

    return 0;
}
