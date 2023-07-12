/** pthread多线程 
 *  int pthread_create(pthread_t *restrict t, const pthread_attr_t *restrict attr,
 *                 void *(*start_func)(void *), void *restrict arg)
 *  int pthread_join(pthread_t t, void **result)
 *  int pthread_exit(void *result)
 *  pthread_t pthread_self()
 *  int pthread_equal(pthread_t t1, pthread_t t2)
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

void* worker_task(void *arg) {
  int count = *((int *)arg);

  // 获取当前线程ID
  pthread_t t = pthread_self();

  // 获取当前进程号
  pid_t process = getpid();

  printf("process %d ,child thread %lu is running\n", process, (unsigned long)t);
  
  for (int i = 0; i < count; i++) {
      printf("child thread : %d \n", i);
      sleep(2);
  }
  printf("child 执行完毕\n");
  pthread_exit("child finish: 200\n");
}

int main() {
    long cores = sysconf(_SC_NPROCESSORS_ONLN);
    printf("可用的CPU内核数量: %ld\n", cores);
    
    pthread_t t, main_thread;
    void* result;
    pid_t process = getpid();
    int arg = 5;
    if (pthread_create(&t, NULL, worker_task, (void *)&arg) !=0 ) {
        printf("create thread failed\n");
    }
    main_thread = pthread_self();
    if (pthread_equal(t, main_thread) != 0) { 
        printf("主线程和子线程的TID是一样的\n");
    }
    else{
        printf("主线程和子线程的TID是不一样的\n");
    }
    printf("process %d , main thread %lu is running\n", process, (unsigned long) main_thread);
   
    for (int i = 0; i < 10; i++) {
        printf("main thread : %d\n", i);
        sleep(3);
    }
    pthread_kill(t, SIGINT);
    //pthread_join(t, &result);
    printf("get result from child thread: %s\n", result);
    printf("main thread is finished\n");
}