// #include <sys/ipc.h>
// #include <sys/sem.h>
// int semget(key_t key, int nsems, int flag)
// 创建一个进程共享的信号量集合，返回信号量集合ID
//
// key - 信号量集合的键值
//       可以指定为 IPC_PRIVATE, 也可以使用<sys/ipc.h>中 ftok 函数生成
//
// sems - 信号量集合中的信号量个数
// flag - 权限符，用于设置 ipc_perm 中的 mode
//        权限包括读、写，没有可执行的概念；
//        该属性会影响到 semctl
//
// 成功返回ID，失败返回 -1


// #include <sys/ipc.h>
// #include <sys/sem.h>
// int semctl(int semId, int semnum, int cmd, .../* union semun arg */)
// 操作信号量集合
//
// semId - 信号量集合ID
// semnum - 被操作的信号量在 信号量集合中的索引（索引号从 0 开始计算）
// cmd - 操作
//       IPC_STAT - 获取信号量集合信息 semid_ds
//       IPC_SET  - 设置信号量集合信息，设置的值存储于 arg 中
//       IPC_RMID - 删除信号量集合
//       GETVAL - 获取semnum信号量的值
//       SETVAL - 设置semnum信号量的值
//       GETPID - 获取上一次操作semnum信号量的进程id
//       GETNCNT - 获取有多少个进程在等待 semnum信号量的值变大
//       GETZCNT - 获取有多少个进程在等待 semnum信号量的值为0
//       GETALL - 获取信号量集合中所有信号量的值
//       GETALL - 设置信号量集合中所有信号量的值
//
// arg - 可选参数，配合 cmd 使用，用于传入值或者接收值
//
// GETALL以外的GET cmd 调用成功时，返回相应的值；
// 除此之外，成功时返回0，失败时返回-1，设置errno


// #include <sys/ipc.h>
// #include <sys/sem.h>
// int semop(int semId, struct sembuf semoparray[], size_t nops)
// 对信号量集合中的信号量进行操作；
// 是原子操作；
//
// semId - 信号量集合id
// semoparray - 信号量操作的集合
//         sembuf
//            .sem_num - 被操作的信号量在信号量集合中的索引
//            .sem_op  - 操作的资源数
//                       正数n，表示释放 n 个资源
//                       负数n，表示占据 |n| 个资源
//                       0，表示进程希望信号量的资源数为0
//            .sem_flag - 操作修饰符
//                      IPC_NOWAIT - 操作不会阻塞进程
//                      SEM_UNDO  - 当占用信号量资源的进程退出，且没有释放
//                                  资源数，内核去释放
//                                 
// nops - 信号量操作的集合中，操作的个数
//
// 成功返回 0， 失败返回 -1
//
// 注意：
//   如果sem_op < 0, 信号量的资源数不够，
//   指定 IPC_NOWAIT: 返回 -1，errno 设置为 EAGAIN;
//   没有指定 IPC_NOWAIT: 该信号量的 semncnt 增1， 进程进入阻塞。
//       发生如下事情时，进程结束阻塞：
//       1. 信号量集合semId被删除，返回 -1，errno 设置为 EIDRM;
//       2. 进程捕捉到一个信号，从信号处理函数返回后，信号量的 semncnt 减1，
//          结束阻塞，返回 -1， errno 设置为 EINTR；
//       3. 信号量的资源数又够了，信号量的 semncnt 减1，返回 0；
//
//   如果sem_op == 0, 信号量的资源数 ≠ 0
//   指定 IPC_NOWAIT: 返回 -1， errno 设置为 EAGAIN;
//   没有指定 IPC_NOWAIT: 该信号量的 semzcnt 增1， 进程进入阻塞。
//       发生如下事情时，进程结束阻塞：
//       1. 信号量集合semId被删除，返回 -1，errno 设置为 EIDRM;
//       2. 进程捕捉到一个信号，从信号处理函数返回后，信号量的 semzcnt 减1，
//          结束阻塞，返回 -1， errno 设置为 EINTR；
//       3. 信号量的资源数 == 0，信号量的 semzcnt 减1，返回 0；


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
                // 获取资源
                .sem_op = -1,
            }
        };

        // 获取
        semop(semId, buf, 1);

        printf("child\n");

        sleep(3);

        // 释放1个资源
        buf[0].sem_op = 1;

        // 释放
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