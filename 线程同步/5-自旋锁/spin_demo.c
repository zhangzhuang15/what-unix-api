/** spin 自旋锁
 *  int pthread_spin_init(pthread_spinlock_t *restrict spinlock, int pshared )
 *  int pthread_spin_destroy(pthread_spinlock_t *restrict spinlock)
 *  int pthread_spin_lock(pthread_spinlock_t *restrict spinlock)
 *  int pthread_spin_trylock(pthread_spinlock_t *restrict spinlock)
 *  int pthread_spin_unlock(pthread_spinlock_t *restrict spinlock)
 *  自旋锁在MacOS上不支持，本代码只能在Linux上运行
*/

#include <stdio.h>
#include <pthread.h>

pthread_spinlock_t lock;

void *thread_a_action(void *arg) {
    if (pthread_spin_trylock(&lock) == 0){
        printf("thread_a 拿到自旋锁了\n");
    }
    else {
        printf("thread_a 没能一下子拿到自旋锁，需要重新拿\n");
        pthread_spin_lock(&lock); // thread_a 在这里进行空转拿锁，CPU在工作中
    }
    for (int i = 0 ; i < 10 ; i++) printf("thread_a print: %d\n", i);
    pthread_spin_unlock(&lock);
}

int main(){
    pthread_t thread_a;
    pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE);
    pthread_create(&thread_a, NULL, &thread_a_action, NULL);
    pthread_spin_lock(&lock);
    for (int i = 10 ; i < 20; i++) printf("主线程 print: %d\n", i);
    pthread_spin_unlock(&lock);
    pthread_join(thread_a, NULL);
    pthread_spin_destroy(&lock);
    printf("主线程结束\n");
}

