%{
#include <stdio.h>
%}

%%

// Match numeric constants (integers and floating-point numbers)
[0-9]+(\.[0-9]+)?   { printf("Constant: %s\n", yytext); }

// Match defined constants (like #define PI 3.14)
"#define"[ \t]+[a-zA-Z_][a-zA-Z0-9_]*[ \t]+[0-9]+(\.[0-9]+)? {
    printf("Defined Constant: %s\n", yytext);
}

// Ignore comments and whitespace
[ \t\n]+            { /* ignore whitespace */ }
"//".*             { /* ignore single line comments */ }
"/\*".*"\*/"       { /* ignore multi-line comments */ }

.                  { /* ignore other characters */ }

%%

// Main function to call yylex
int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (file) {
            yyin = file;
            yylex();
            fclose(file);
        } else {
            fprintf(stderr, "Error opening file: %s\n", argv[1]);
            return 1;
        }
    } else {
        fprintf(stderr, "Usage: %s <source_file.c>\n", argv[0]);
        return 1;
    }
    return 0;
}
