%{
#include <stdio.h>

int char_count = 0; 
int line_count = 0; 
int word_count = 0;

void count_word() {
    word_count++;
}
%}

%%

"//".*                ; 
"/*"([^*]|\*+[^*/])*\*+"/" ; 

[ \t]+               ;
\n                   { line_count++; }
[a-zA-Z_][a-zA-Z0-9_]* { count_word(); }
\"([^\\"]|\\.)*\"     { count_word(); }
[0-9]+                { count_word(); } 
.                     { char_count++; } 

%%

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source_file.c>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    yyin = file; 
    yylex(); 
    printf("Characters: %d\n", char_count);
    printf("Lines: %d\n", line_count);
    printf("Words: %d\n", word_count);

    fclose(file);
    return 0;
}
