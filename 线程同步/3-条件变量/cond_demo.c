/** condition 条件变量 
 *  int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict addr)
 *  int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex)
 *  int pthread_cond_signal(pthread_cond_t *restrict cond)
 *  int pthread_cond_broadcast(pthread_cond_t *restrict cond)
 *  int pthread_cond_destroy(pthread_cond_t *restrict cond)
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

void *thread_a_action(void *arg) {
    pthread_mutex_lock(&mutex);
    for (int i = 0 ; i < 10 ; i++) {
        if (i == 5) {
            struct timespec spc;
            clock_gettime(CLOCK_REALTIME, &spc); // 获取当前时刻，存储为timespc格式
            spc.tv_sec += 3; // 再等三秒
            pthread_cond_timedwait(&cond, &mutex, &spc);
            //pthread_cond_wait(&cond, &mutex);
        }
        printf("thread_a speak: %d\n", i);
    }
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond);
    pthread_exit(NULL);
}

void *thread_b_action(void *arg) {
    pthread_mutex_lock(&mutex);
    for (int i = 11; i < 20 ; i++) {
        if (i == 15) {
            pthread_cond_signal(&cond);
            pthread_cond_wait(&cond, &mutex);
        }
        printf("thread_b speak: %d\n", i);
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main() {
    printf("主线程开始\n");
    pthread_t thread_a, thread_b;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_create(&thread_a, NULL, &thread_a_action, NULL);
    pthread_create(&thread_b, NULL, &thread_b_action, NULL);
    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
    printf("主线程结束\n");
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
    return 0;
}