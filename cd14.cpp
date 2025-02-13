#include <stdio.h>

int main() {
    int a = 5, b = 10, c = 15;
    int common_subexpr = a * b; 
    int result1, result2, result3;

    result1 = common_subexpr + c; 
    result2 = common_subexpr - c; 
    result3 = common_subexpr * c;

    printf("Result 1: %d\n", result1);
    printf("Result 2: %d\n", result2);
    printf("Result 3: %d\n", result3);

    return 0;
}
