%{
#include <stdio.h>
%}

%%

<[^/!][^>]*>          { printf("Opening tag: %s\n", yytext); }

</[^>]+>              { printf("Closing tag: %s\n", yytext); }

<[^/!][^>]*\/>        { printf("Self-closing tag: %s\n", yytext); }

[ \t\n]+              ; // Ignore whitespace
"<!--".* "-->"        ; // Ignore HTML comments

.                     { /* Ignore any other character */ }

%%

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (file) {
            yyin = file;
            yylex();
            fclose(file);
        } else {
            fprintf(stderr, "Could not open file: %s\n", argv[1]);
            return 1;
        }
    } else {
        fprintf(stderr, "Usage: %s <html_file.html>\n", argv[0]);
        return 1;
    }
    return 0;
}
