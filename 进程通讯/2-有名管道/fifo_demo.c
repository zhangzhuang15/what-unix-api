// #include <sys/stat.h>
// int mkfifo(const char* path, mode_t mode)
// 创建 fifo 文件
//
// path - 文件路径，和创建普通文件时一样
// mode - 文件权限， 和 open 函数一样
//           用户可读         S_IRUSR 
//           用户可写         S_IWUSR
//           用户可执行       S_IXUSR
//           用户组可读       S_IRGRP
//           用户组可写       S_IWGRP
//           用户组可执行      S_IXGRP
//           其他可读         S_IROTH
//           其他可写         S_IWOTH
//           其他可执行       S_IXOTH
//
// 成功返回0，失败返回-1
//
// 注意：
// 1. 没有指定non-block, 以只读方式 open 一个fifo，如果没有其他进程以写方式打开这个fifo，当前进程会被阻塞；
// 2. 没有指定non-block, 以只写方式 open 一个fifo，如果没有其他进程以读方式打开这个fifo，当前进程会被阻塞；
// 3. 如果读取一个 fifo， 而且这个 fifo 被另外一个进程关闭了，则当读进程将 fifo 中的数据全部读取完毕后，read
//    函数会返回0，表示文件结束；
// 4. 如果写入一个 fifo，而且这个 fifo 被另外一个进程关闭，当前进程会接受到 SIGPIPE 信号，write函数返回 -1，
//    errno 会被设置为 EPIPE。
// 5. 没有指定non-block，以读方式 open 一个 fifo，如果写进程没有关闭fifo，也没有写数据到fifo中去，读进程
//    就会在 read 的时候一直阻塞；
// 6. 没有指定non-block，以写方式 open 一个 fifo，如果 fifo 中的数据满了，则写进程会一直阻塞；

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