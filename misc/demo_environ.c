#include <stdio.h>

extern char** environ;

int main(int argc, char** argv) {
    printf("argc: %d\n", argc);

    for(int i = 0; *argv != NULL; i++, argv++) {
        printf("argv[%d]: %s\n", i, *argv);
    }

    for (int i = 0; *environ != NULL; i++, environ++) {
        printf("env[%d]: %s\n", i, *environ);
    }

    return 0;
}