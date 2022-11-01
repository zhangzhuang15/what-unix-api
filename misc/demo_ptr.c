#include <stdio.h>

int sum(int a, int b) {
    return a + b;
}

int main() {
    int m = 24;
    int *p = &m;
    int n = (int)p;
    void* q = n-10;
    int c = &sum;
    printf("p: %p\n"
           "n: %d\n"
           "q: %p\n"
           "c: %d\n"
           "sum: %p\n"
           "ENTER: %p\n"
           "p-1: %p\n"
           "p-1: %ld\n", p, n, q, c, &sum, &&_ENTER, p-1, p-1);
    printf("p size: %lu\n", sizeof(p));
    _ENTER:
      printf("This is another line in this code file");
    return 1;
}