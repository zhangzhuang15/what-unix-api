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

        if ( msgsnd(msgId, &m, sizeof(m), IPC_NOWAIT) < 0 ) {
            printf("child send message failed\n");
            _exit(20);
        };

        printf("child send message\n");

    } else {
        Message *msg = (Message*)malloc(sizeof(Message));
        printf("master attemp to read from queue\n");
        ssize_t rcved =  msgrcv(msgId, msg, sizeof(Message), 0, 0);
        if (rcved < 0) {
            printf("msgrcv failed\n");
        } else {
            printf("received %ld bytes\n", rcved);
            printf("msg: %s\n", msg->data);
        }

        waitpid(child, NULL, 0);

        msgctl(IPC_RMID, msgId, NULL);

        free(msg);
    }
    
    return 0;
}