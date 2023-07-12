// #include <fcntl.h>
// int open(const char* pathname, int flags, /* mode_t mode */)
// 创建/打开 一个文件描述符
//
//  pathname-文件路径名
//  flags-文件的访问模式。
//           只读            O_RDONLY  
//           只写            O_WRONLY
//           可读可写         O_RDWR
//           不存在时创建      O_CREAT
//           在文件末尾追加    O_APPEND
//           文件存在时报错    O_EXCL      要配合 O_CREAT使用
//           非阻塞方式打开    O_NONBLOCK
//           同步IO方式打开    O_SYNC
//           不是文件夹时报错   O_DIRECTORY
//           打开符号链接报错   O_NOFOLLOW
//
//  mode  - 可选参数，文件的访问权限。
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
//  成功时，返回文件描述符
//  失败时，返回-1， 具体错误记录在 errno 中
//
// 注意在没有设置 O_NONBLOCK 下打开一个文件，发生的阻塞场景：
// 1. 以只读模式打开一个 FIFO，如果没有写进程打开这个FIFO，当前读进程会阻塞；
// 2. 以只写模式打开一个 FIFO，如果没有读进程打开这个FIFO，当前写进程会阻塞；


#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>


int main() {
    
    int fd = open("./test.txt", O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    if(fd == -1) {
        printf("打开文件时发生错误\n");
        // #include <errno.h>
        switch(errno){
            case ENOENT:
                printf("原因是文件不存在\n");
                break;
            default:
                printf("原因不明\n");
        }
    }

    fd = open("./test.txt", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if(fd > 0) {
        printf("文件test.txt创建成功\n");
        // #include <unistd.h>
        close(fd);
    }
}


// 执行代码，
// 输出：
//  打开文件时发生错误
//  原因是文件不存在
//  文件test.txt创建成功
//
// test.txt文件生成