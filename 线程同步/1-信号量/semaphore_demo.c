#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
sem_t s;

void* worker_task_A(int count){
    /*信号量P操作*/
    sem_wait(&s);
    for ( int i = 0; i < count; i++ ) {
        printf("child_A thread: %d\n", i);
        sleep(2);
    }
    /*信号量V操作*/
    sem_post(&s);
}

void* worker_task_B(int count) {
    sem_wait(&s);
    for ( int i = 0; i < count; i++ ) {
        printf("child_B thread: %d\n", i);
        sleep(2);
    }
    sem_post(&s);
}
int main() {
    /* 
      first param: sem_t* 
      second param: int   0:线程间信号量  1:进程间信号量
      third param: unsigned int 信号量初始值
    */
    sem_init(&s, 0, 1);
    pthread_t pchild_A, pchild_B;
    if (pthread_create(&pchild_A, NULL, worker_task_A, 5) != 0) {
        printf("child A create failed\n");
    }
    if (pthread_create(&pchild_B, NULL, worker_task_B, 5) != 0) {
        printf("child B create failed\n");
    }
    pthread_join(pchild_A, NULL);
    pthread_join(pchild_B, NULL);
}