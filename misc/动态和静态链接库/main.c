#include "util.h"
#include <stdio.h>


int main() {
    hello();
    int index = find("Jack", 'c');
    if (index != -1) {
        printf("index: %d\n", index);
    }
}