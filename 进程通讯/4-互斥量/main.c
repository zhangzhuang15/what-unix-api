// #include <pthread.h>
// int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int pshared)
// 设置互斥量共享属性
//
// attr - 互斥量属性
// pshared - 互相量共享属性值
//           PTHREAD_PROCESS_SHARED - 互斥量支持进程共享
//           PTHREAD_PROCESS_PRIVATE - 互斥量只能在一个进程内使用，默认值
// 
// 成功返回0，失败返回-1
//
// 注意：
// 除了设置 PTHREAD_PROCESS_SHARED, 互斥量本身必须处于共享内存中，否则互斥量
// 仍然无法跨进程共享使用，当一个进程上锁的时候，另一个进程将不会受到阻塞。
//
// 互斥量并非只能用于线程，还可以用于进程之间。

#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
    int shmId = shmget(IPC_PRIVATE, sizeof(pthread_mutex_t), 0666);

    if (shmId < 0) {
        printf("shmget failed\n");
        return -1;
    }

    pthread_mutex_t *mutex = (pthread_mutex_t*)shmat(shmId, 0, 0600);

    pthread_mutexattr_t attr;
    // 初始化互斥量属性
    pthread_mutexattr_init(&attr);
    // 设置进程间共享互斥量
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);

    pthread_mutex_init(mutex, &attr);

    const pid_t child = fork();

    if (child < 0) {
        printf("fork failed\n");
        return -1;
    }

    if (child == 0) {
        pthread_mutex_t *lock = (pthread_mutex_t*)shmat(shmId, 0, 0600);
        printf("child want to get lock....");
        pthread_mutex_lock(lock);
        printf("child get lock\n");
        pthread_mutex_unlock(lock);
        printf("child release lock\n");

        shmdt((void*)lock);
        _exit(10);

    } else {
        printf("master want to get lock...\n");
        pthread_mutex_lock(mutex);
        printf("master get lock\n");
        sleep(3);
        pthread_mutex_unlock(mutex);
        printf("child release lock\n");
        
        int status;
        waitpid(child, &status, 0);

        // 打印的是 进程 终止码 和 退出码
        printf("child terminate code: %d\n"
               "child exit code: %d\n",
               status,
               WEXITSTATUS(status)
        );

        shmdt((void*)mutex);

        shmctl(shmId, IPC_RMID, NULL);
    }

    return 0;
}