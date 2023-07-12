#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// int pthread_create(pthread_t *restrict t, 
//                    const pthread_attr_t *restrict attr,
//                    void* (*work)(void *), 
//                    void *restrict arg)
//  work 是线程函数；
//  arg 是传入 work 中的实参；
//  attr 是对线程的定制化设置，一般设置为 NULL  即可；
// 
//  创建失败返回非0， 成功时返回0

/**
 * 创建线程
 */

void* work(void* arg) {
    // 休息2s， 这会发生线程调度， 用来证明 main 中的 pthread_join 会阻塞代码
    sleep(2);

    printf("child thread is running %lu\n", *(unsigned long*)(arg));

    long result = 100;
    
    // 将值发送给主线程
    pthread_exit((void*)result);
}

int main() {
    pthread_t thread;

    // void* 代表指向通用数据类型的指针
    // 在 arm64 macOS 占据 8 字节。
    void* result;
    unsigned long arg = 100;
    // 创建线程
    pthread_create(&thread, NULL, work, &arg);

    // 阻塞主线程，直到子线程运行结束，
    // 如果子线程有值返回给主线程，主线程通过 &result 接收；
    pthread_join(thread, &result);

    printf("worker thread is end\n");

    printf("result: %ld\n", (long)result);

    return 0; 
}