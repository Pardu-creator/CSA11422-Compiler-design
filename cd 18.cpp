%{
#include <stdio.h>

int macro_count = 0;  
int include_count = 0; 

void count_macro() {
    macro_count++;
}

void count_include() {
    include_count++;
}
%}

%%

"#define"              { count_macro(); }

"#include"            { count_include(); }

[ \t\n]+              ;
"//".*                ; 
"/*".* "*/"          ; 

.                     { /* Ignore any other character */ }

%%

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

    YY_BUFFER_STATE buffer = yy_scan_string(source_code);
    yylex();
    yy_delete_buffer(buffer);

    printf("Number of macros defined: %d\n", macro_count);
    printf("Number of header files included: %d\n", include_count);

    return 0;
}
