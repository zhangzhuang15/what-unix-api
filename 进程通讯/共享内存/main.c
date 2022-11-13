// #include <sys/ipc.h>
// #include <sys/shm.h>
// int shmget(key_t key, size_t size, int shmflag)
// 创建一个共享内存空间，返回共享内存描述符
//
// key  - 可以理解为创建文件时需要的 path 路径，作为锁定一个共享内存空间的标志
// size - 共享内存空间大小，单位字节，最好是 2 的整数倍；
//        假设你设置为 4.5KB, 那么会占据2页内存，而且第二页剩下的 4KB - 0.5KB = 3.5KB 的空间将不可用;
//        如果是 使用一个已经存在的共享内存区，传入 0；
// shmflag - 共享存储区域对应的 ipc_perm 权限设置
//           用户可读         S_IRUSR 
//           用户可写         S_IWUSR
//           用户组可读       S_IRGRP
//           用户组可写       S_IWGRP
//           其他可读         S_IROTH
//           其他可写         S_IWOTH
//
//           如果只设置了 S_IRUSR, 共享存储区域创建者或者超管用户，
//           可以使用 shmctl 做写操作，删除操作，其他用户无法通过
//           shmctl做任何操作
//
// 失败返回 -1； 成功返回 共享内存 描述符。

// #include <sys/ipc.h>
// #include <sys/shm.h>
// int shmctl(int shmid, int cmd, struct shmid_ds *buf)
// 对共享内存区域执行操作
//
// shmid - 共享内存id
// cmd   - 操作指令
//         IPC_STAT  - 获取共享内存区的元信息，存储到 buf 中
//         IPC_SET   - 将 buf 存储的元信息设置给 共享内存区
//         IPC_RMID  - 从系统中删除共享存储区，将无法再使用
//
// 成功返回 0， 失败返回 -1

// #include <sys/ipc.h>
// #include <sys/shm.h>
// void* shmat(int shmid, const void *addr, int flag)
// 将共享内存区映射到当前进程虚拟内存地址中使用
//
// shmid - 共享内存区id
// addr  - 共享内存区域连接到当前进程的虚拟内存地址
//         0    -     地址由内核选择
//         非0 且 flag 指定了 SHM_RND   - 链接到 addr 上
//         非0 且 flag 没有指定 SHM_RND  - 链接到 (addr - (addr mod SHMLBA)), 相当于让 addr 按照 SHMLBA 对齐
// 
// flag  - 如何操作共享内存区
//         SHM_RDONLY  - 只读
//
// 成功时，返回映射到当前进程的虚拟内存地址； 失败返回-1

// #include <sys/ipc.h>
// #include <sys/shm.h>
// int shmdt(const void *addr)
// 删除当前进程虚拟内存地址 addr 到 共享内存区的映射关系；
//
// 成功返回0； 失败返回 -1；

#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int shmId;
    char data[128] = "hello world";

    shmId = shmget(IPC_PRIVATE, sizeof(data), S_IREAD | S_IWUSR);

    if (shmId < 0) {
        printf("create shm failed\n");
        return -1;
    }

    pid_t child = fork();

    if (child < 0) {
        printf("fork failed\n");
        return -1;
    }

    if (child == 0) {
        // 子进程
        char *p = (char*)shmat(shmId, 0, SHM_W);
        
        // 直接对 p 写入操作，实际就会写入到 共享存储区
        memcpy(p, data, strlen(data) + 1);

        shmdt(p);

    } else {
        // 主进程

        // 共享内存区映射到 p
        // 注意第二个参数是 0
        char* p = (char*)shmat(shmId, 0, SHM_RDONLY);
        waitpid(child, NULL, 0);

        // 通过 p 读取共享内存内容
        printf("result: %s\n", p);

        // 删除映射关系
        shmdt(p);

        // 删除共享内存区
        shmctl(shmId, IPC_RMID, NULL);
    }

    return 0;
}