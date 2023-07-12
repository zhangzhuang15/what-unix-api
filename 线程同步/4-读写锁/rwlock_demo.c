/** 读写锁 rwlock
 *  int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, pthread_rwlockattr_t* rwlockattr)
 *  int pthread_rwlock_rdlock(pthread_rwlock_t *restrict rwlock)
 *  int pthread_rwlock_wrlock(pthread_rwlock_t *restrict rwlock)
 *  int pthread_rwlock_tryrdlock(pthread_rwlock_t *restrict rwlock)
 *  int pthread_rwlock_trywrlock(pthread_rwlock_t *restrict rwlock)
 *  int pthread_rwlock_unlock(pthread_rwlock_t *restrict rwlock)
 *  int pthread_rwlock_destroy(pthread_rwlock_t *restrict rwlock)
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// 用于多线程间共享
int values[5] = {1, 1, 1, 1, 1};
pthread_rwlock_t rwlock;

void *operate_by_a(void *arg) {
    time_t start = time(NULL);
    if (pthread_rwlock_rdlock(&rwlock) == 0){
        printf("thread_a 拿到读锁了\t 读取values[0]: %d\n", values[0]);
        sleep(2);
        pthread_rwlock_unlock(&rwlock); // 必须释放读锁之后，再去拿写锁
        if (pthread_rwlock_wrlock(&rwlock) == 0) {
            values[0] += 10;
            printf("thread_a 拿到写锁了\t 把values[0]改为%d\n", values[0]);
            sleep(2);
            pthread_rwlock_unlock(&rwlock);
        }
        else {
            printf("thread_a 没有拿到写锁");
            pthread_rwlock_destroy(&rwlock);
        }
    }
    else {
        printf("thread_a 没有拿到读锁\n");
    }
    time_t end = time(NULL);
    printf("thread_a cost time：%lds\n", end - start);
    pthread_exit(NULL);
}

void *operate_by_b(void *arg) {
    time_t start = time(NULL);
    if (pthread_rwlock_rdlock(&rwlock) == 0){
        printf("thread_b 拿到读锁了\t 读取values[0]: %d\n", values[0]);
        sleep(2);
        pthread_rwlock_unlock(&rwlock);
        if (pthread_rwlock_wrlock(&rwlock) == 0) {
            values[0] += 20;
            printf("thread_b 拿到写锁了\t 把values[0]改为%d\n", values[0]);
            sleep(2);
            pthread_rwlock_unlock(&rwlock);
        }
        else {
            printf("thread_b 没有拿到写锁");
            pthread_rwlock_destroy(&rwlock);
        }
    }
    else {
        printf("thread_b 没有拿到读锁\n");
    }
    time_t end = time(NULL);
    printf("thread_b cost time: %lds\n", end - start); // 有时间结果可推知同一进程的两个线程跑在不同的CPU核心上
    pthread_exit(NULL);
}

int main() {
    time_t start = time(NULL);
    pthread_t thread_a, thread_b;
    pthread_rwlock_init(&rwlock, NULL);
    pthread_create(&thread_a, NULL, &operate_by_a, NULL);
    pthread_create(&thread_b, NULL, &operate_by_b, NULL);
    sleep(1);
    printf("主线程 values[0]: %d\n", values[0]); // 主线程可以访问数据
    sleep(1);
    printf("主线程 values[0]: %d\n", values[0]);
    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
    printf("主线程 values[0]: %d\n", values[0]);
    pthread_rwlock_destroy(&rwlock);
    time_t end = time(NULL);
    printf("主线程 cost time: %lds\n", end - start);
    return 0;
}