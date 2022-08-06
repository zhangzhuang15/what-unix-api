#include <stdio.h>
#include <pthread.h>

__thread char *base, *cur;

__attribute__((noinline)) void set_cur(void *ptr) { cur = ptr; }

__attribute__((noinline)) char *get_cur()         { return cur; }


void stackoverflow(int n) {
    set_cur(&n);
    if (n % 1024 == 0) {
        int sz = base - get_cur();
        printf("Stack size of T >= %d KB\n", sz / 1024);
    }
    stackoverflow(n + 1);
}

void* work(void* arg) {
    base = (void*)&arg;
    stackoverflow(0);
}

int main() {
    setbuf(stdout, NULL);

    pthread_t t;
    unsigned long arg = 10;
    pthread_create(&t, NULL, work, &arg);

    pthread_join(t, NULL);

    return 0;
}