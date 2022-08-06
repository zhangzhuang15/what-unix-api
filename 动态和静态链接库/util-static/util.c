#ifndef __My_Util
#define __My_Util
#include "./util.h"
#include "stdio.h"

void hello() {
    printf("hello friends\n");
}

int find(const char* source, char dest) {
    for ( int i = 0; source[i] != '\0'; i++) {
        if (source[i] == dest) return i;
    }
    return -1;
}
#endif