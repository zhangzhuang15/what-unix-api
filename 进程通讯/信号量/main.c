


#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    // 信号量集合中只有 1 个信号量
    int semId = semget(IPC_PRIVATE, 1, 0666);
    
    if (semId < 0) {
        printf("semget failed\n");
        return -1;
    }

    // 给集合中唯一的信号量设置资源数为 1
    semctl(semId, 0, SETVAL, 1);


    pid_t child = fork();

    if (child < 0) {
        printf("fork failed\n");
        return -1;
    }

    if (child == 0) {
        // 子进程

        // 从信号量集合中唯一的信号量上，获取 1 个资源
        struct sembuf buf[] = {
            {
                .sem_num = 0,
                .sem_op = -1,
            }
        };

        semop(semId, buf, 1);

        printf("child\n");

        // 释放1个资源
        buf[0].sem_op = 1;

        semop(semId, buf, 1);
    } else {
        struct sembuf buf[] = {
            {
                .sem_num = 0,
                .sem_op = -1,
            }
        };

        semop(semId, buf, 1);

        printf("master");

        buf[0].sem_op = 1;

        semop(semId, buf, 1);

        waitpid(child, NULL, 0);

        semctl(semId, 0, IPC_RMID);
    }

    return 0;
}