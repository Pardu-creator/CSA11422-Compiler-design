#include <stdio.h>
#include <ctype.h>  

void lexical_analyzer(const char *input) {
    int whitespace_count = 0;
    int newline_count = 0;
    
    for (int i = 0; input[i] != '\0'; i++) {
        if (isspace(input[i])) {  
            whitespace_count++;
        }
        if (input[i] == '\n') {    
            newline_count++;
        }
    }

    printf("Whitespace characters: %d\n", whitespace_count);
    printf("Newline characters: %d\n", newline_count);
}

int main() {
    char input_string[] = "Hello world! \nThis is a test string.\nAnother line here.\n";
    
    printf("Input:\n%s\n", input_string);
    
    lexical_analyzer(input_string);
    
    return 0;
}

