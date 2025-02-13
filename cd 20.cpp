%{
#include <stdio.h>
int line_number = 1; 
%}

%%

.|\n {
    printf("%d: %s", line_number++, yytext);
}

[ \t]+    ;
"/*".* "*/"  ; 
"//".* "\n"  ; 

%%

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
