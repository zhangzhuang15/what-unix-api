// #include <sys/ipc.h>
// #include <sys/shm.h>
// int shmget(key_t key, size_t size, int shmflag)
//
// 失败返回 -1； 成功返回 IPC 描述符。
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main() {
    int shmId;

    shmId = shmget(IPC_PRIVATE, );
    return 0;
}