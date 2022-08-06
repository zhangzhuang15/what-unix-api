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
    printf("p: %p\nn: %d\nq: %p\nc: %d\nsum: %p\nENTER: %p\n", p, n, q, c, &sum, &&_ENTER);
    printf("p size: %lu\n", sizeof(p));
    _ENTER:
      printf("This is another line in this code file");
    return 1;
}