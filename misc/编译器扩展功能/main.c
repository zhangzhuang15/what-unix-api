#include <stdio.h>

struct data {
    int age;
    char* name;
};

int main() {
    struct data mine = { age: 4, name: "" };
    printf("%s", mine.name);
    return 0;
}