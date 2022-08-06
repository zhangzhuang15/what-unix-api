#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// pthread_t 就是 thread ID
pthread_t maint, t;

void* work(void* arg) {
    // 获取 子线程的 pthread_t
    t = pthread_self();
    return 0;
}

int main() {
    pthread_t tt;

    pthread_create(&tt, NULL, work, NULL);

    // 获取主线程的 pthread_t
    maint = pthread_self();

    pthread_join(tt, NULL);

    // 主线程和子线程的 pthead_t 是否一致（内容上一致）
    if (!pthread_equal(maint, tt)) {
        printf("main thread not child thread\n");
    }

    if (pthread_equal(tt, t)) {
        printf("child thread tt is child thread t");
    }
    return 0;
}