/** 屏蔽 barrier
 *  int pthread
 * 
 *  MacOS不支持 屏蔽，该用Linux测试本代码
*/

#include <stdio.h>
#include <pthread.h>

pthread_barrier_t barrier;

void *thread_a_action(void *arg) {
    for (int i = 1 ; i < 12; i += 3){
        printf("thread_a print: %d\n", i);
        pthread_barrier_wait(&barrier);
    }
    printf("thread_a 结束\n");
    pthread_exit(NULL);
}

void *thread_b_action(void *arg) {
    for (int i = 2 ; i < 12; i += 3){
        printf("thread_b print: %d\n", i);
        pthread_barrier_wait(&barrier);
    }
    printf("thread_b 结束\n");
    pthread_exit(NULL);
}

void *thread_c_action(void *arg) {
    for (int i = 3 ; i < 12; i += 3){
        printf("thread_c print: %d\n", i);
        pthread_barrier_wait(&barrier);
    }
    printf("thread_c 结束\n");
    pthread_exit(NULL);
}

int main(){
    pthread_barrier_init(&barrier, NULL, 3);
    pthread_t thread_a, thread_b, thread_c;
    pthread_create(&thread_a, NULL, &thread_a_action, NULL);
    pthread_create(&thread_b, NULL, &thread_b_action, NULL);
    pthread_create(&thread_c, NULL, &thread_c_action, NULL);
    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
    pthread_join(thread_c, NULL);
    pthread_barrier_destroy(&barrier);
    printf("主线程结束\n");
    return 0;
}