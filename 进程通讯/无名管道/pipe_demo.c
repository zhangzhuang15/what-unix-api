#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main() {
    /* p[0] ---> read end
       p[1] ---> write end
    */
    int p[2];
    pid_t child;
    /*定义在这里是为了创建子进程的时候，让子进程也复制一份 */
    char buf[30];
    if (pipe(p) !=0) {
        printf("pipe create failed\n");
    }
    if ((child = fork()) < 0) {
        printf("child process create failed\n");
    }
    else if (child == 0) {
        /* 子进程 */
        strcpy(buf, "hello main process");
        write(p[1], buf, 19);
        printf("child process has written well\n");
        return 0;
    }
    else {
        /*主进程*/
        printf("main process wait for child process writing to the pipe write end\n");
        sleep(3);
        read(p[0], buf, 30);
        printf("get message from child : %s\n", buf);
        return 0;
    }
}
