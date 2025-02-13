%{
#include <stdio.h>

int macro_count = 0;  // Counter for macros
int include_count = 0; // Counter for header files

void count_macro() {
    macro_count++;
}

void count_include() {
    include_count++;
}
%}

%%

// Match macro definitions
"#define"              { count_macro(); }

// Match include directives
"#include"            { count_include(); }

// Ignore comments and whitespace
[ \t\n]+              ; // Ignore whitespace
"//".*                ; // Ignore single-line comments
"/*".* "*/"          ; // Ignore multi-line comments

.                     { /* Ignore any other character */ }

%%

// Main function
int main() {
    const char *source_code = 
        "#define PI 3.14\n"
        "#include<stdio.h>\n"
        "#include<conio.h>\n"
        "void main()\n"
        "{\n"
        "    int a,b,c = 30;\n"
        "    printf(\"hello\");\n"
        "}\n";

    // Simulate reading from a file by using a string
    YY_BUFFER_STATE buffer = yy_scan_string(source_code);
    yylex();
    yy_delete_buffer(buffer);

    // Print the counts
    printf("Number of macros defined: %d\n", macro_count);
    printf("Number of header files included: %d\n", include_count);

    return 0;
}
