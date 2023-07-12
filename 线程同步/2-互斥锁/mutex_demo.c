/** 互斥量mutex
 *  int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *restrict attr)
 *  int pthread_mutext_destroy(pthread_mutex_t *mutex)
 *  int pthread_mutex_lock(pthread_mutex_t *mutex)
 *  int pthread_mutex_trylock(pthread_mutex_t *mutex)
 *  int pthread_mutex_unlock(pthread_mutex_t *mutex)
 *  
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;

void* worker_task_A(int count){
    /*上锁*/
    pthread_mutex_lock(&mutex);
    for ( int i = 0; i < count; i++ ) {
        printf("child_A thread: %d\n", i);
        sleep(2);
    }
    /*解锁*/
    pthread_mutex_unlock(&mutex);
}

void* worker_task_B(int count) {
    if (pthread_mutex_trylock(&mutex) == 0){
        printf("child_B thread尝试拿锁成功\n");
    }
    else {
        printf("child_B thread要重新阻塞式拿锁\n");
        pthread_mutex_lock(&mutex);
    }
    for ( int i = 0; i < count; i++ ) {
        printf("child_B thread: %d\n", i);
        sleep(2);
    }
    pthread_mutex_unlock(&mutex);
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_t pchild_A, pchild_B;
    if (pthread_create(&pchild_A, NULL, worker_task_A, 5) != 0) {
        printf("child A create failed\n");
    }
    if (pthread_create(&pchild_B, NULL, worker_task_B, 5) != 0) {
        printf("child B create failed\n");
    }
    pthread_join(pchild_A, NULL);
    pthread_join(pchild_B, NULL);
    pthread_mutex_destroy(&mutex); 
}