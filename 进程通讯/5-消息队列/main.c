// #include <sys/ipc.h>
// #include <sys/msg.h>
// int msgget(key_t key, int flag)
// 创建消息队列
//
// key - 消息队列的键值
//          可以指定为 IPC_PRIVATE, 也可以使用<sys/ipc.h>中 ftok 函数生成
// flag - 权限符，用于设置 ipc_perm 中的 mode
//        权限包括读、写，没有可执行的概念；
//        该属性会影响到 semctl
//
// 成功返回消息队列ID， 失败返回 -1


// #include <sys/ipc.h>
// #include <sys/msg.h>
// int msgctl(int msgId, int cmd, struct msgid_ids *buf)
// 操作消息队列
//
// msgId - 消息队列ID；
// cmd   - 操作
//         IPC_STAT - 获取消息队列信息，存储于 buf;
//         IPC_SET  - 设置消息队列信息，信息的值来自 buf;
//         IPC_RMID - 删除消息队列
// buf   - 获取或者设置值
//
// 成功返回 0，失败返回 -1


// #include <sys/ipc.h>
// #include <sys/msg.h>
// int msgsnd(int msgId, const void *ptr, size_t nbytes, int flag)
// 发送数据到消息队列
//
// msgId - 消息队列ID；
// ptr   - 被发送数据起始地址；
// nbytes - 被发送数据大小，单位字节；
// flag  - 修饰符
//         IPC_NOWAIT - 发送不会阻塞进程，出错会设置 errno 为 EAGAIN
//
// 成功返回 0， 失败返回 -1
//
// 注意：
//   被发送的数据具有固定的格式：
//     struct {
//        long type; // 消息类型，用于消息队列内部排序
//        char data[256]; // 消息数据，大小可调整，可以不取 256
//     }


// #include <sys/ipc.h>
// #include <sys/msg.h>
// ssize_t msgrcv(int msgId, void *ptr, size_t nbytes, long type, int flag)
// 获取消息队列的一条数据
//
// msgId - 消息队列ID；
// ptr   - 存储数据的起始地址；
// nbytes - 存储数据的空间大小，单位字节；
// type  - 消息类型
//         0 - 获取消息队列中的第一个消息
//         正数n - 获取消息队列中第一个 type == n 的消息
//         负数n - 获取消息队列中 type ≤ |n| 且 type 最小的 消息
// 
// flag  - 修饰符
//         IPC_NOWAIT - 操作不会阻塞进程，如果没有消息返回，函数返回 -1，errno 设置为 ENOMSG
//
// 成功时，返回接收到的字节数； 失败，返回 -1

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    long type;
    char data[128];
} Message;

int main() {
    // 创建消息队列
    int msgId = msgget(IPC_PRIVATE, 0666);

    if (msgId < 0) {
        printf("msgget failed\n");
        return -1;
    }

    const pid_t child = fork();

    if (child < 0) {
        printf("fork failed\n");
        msgctl(IPC_RMID, msgId, NULL);
        return -1;
    }

    if (child == 0) {
        Message m = {
            .type = 1,
            .data = "hello world",
        };

        // 发送消息
        if ( msgsnd(msgId, &m, sizeof(m), IPC_NOWAIT) < 0 ) {
            printf("child send message failed\n");
            _exit(20);
        };

        printf("child send message\n");

    } else {
        Message *msg = (Message*)malloc(sizeof(Message));
        printf("master attemp to read from queue\n");

        // 接收数据
        ssize_t rcved =  msgrcv(msgId, msg, sizeof(Message), 1, 0);
        if (rcved < 0) {
            printf("msgrcv failed\n");
        } else {
            printf("received %ld bytes\n", rcved);
            printf("msg: %s\n", msg->data);
        }

        waitpid(child, NULL, 0);

        // 删除消息队列
        msgctl(IPC_RMID, msgId, NULL);

        free(msg);
    }
    
    return 0;
}