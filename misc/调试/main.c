#include <stdio.h>


int main(int args, const char* arg[]) {
    printf("welcome to use C program\n");
    printf("length of arguments you put is %d\n", args);
    printf("let's take a look at these arguments\n");
    
    for (int i = 0; i < args; i++) {
        printf("The %dth argument: %s\n", i+1, arg[i]);
    }
}