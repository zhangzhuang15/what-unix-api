#include <stdio.h>
#include <limits.h>

int main(){
    printf("The minimum value of int: %d\n", INT_MIN);
    printf("The maximum value of int: %d\n\n", INT_MAX);
    printf("The minimum value of long: %ld\n", LONG_MIN);
    printf("The maximum value of long: %ld\n\n", LONG_MAX);
    printf("The minimum value of char: %d\n", CHAR_MIN);
    printf("The maximum value of char: %d\n\n", CHAR_MAX);
    printf("The number of bits in a byte: %d\n", CHAR_BIT);
    return 0;
}