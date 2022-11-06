#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

/* 展示IPC中有名管道的使用方式**/

int main() {
    /* first param: const char * 
       second param: mode_t    描述fifo的访问权限*/
    char buf[30];
    if(mkfifo("fifo", 0666) != 0) {
        printf("create fifo failed\n");
    }
    pid_t child_A, child_B;
    if ((child_A = fork()) < 0 ) {
        printf("child A process create failed\n");
    }
    else if (child_A == 0) {
        int fd = open("fifo", O_WRONLY);
        strcpy(buf, "hello child B", 14);
        write(fd, buf, sizeof(buf) );
        printf("child A write finish\n");
        close(fd);
    }
    else {
        if ( (child_B = fork()) < 0) {
            printf("create child B failed\n");
        }
        else if (child_B == 0){
            int fd = open("fifo", O_RDONLY);
            read(fd, buf, 30);
            printf("child B read from child A : %s\n", buf);
            close(fd);
        }
        
    }
}