// #include <unistd.h>
// int dup2(int fd, int fd2)
// 复制文件表
//
// fd-文件描述符
// fd2-指定新描述符的值
//
// 成功时，返回新的文件描述符, 也即是fd2
//        1）fd == fd2 ， 直接返回 fd
//        2）fd != fd2, 且fd2已经打开，先将其关闭，复制fd后，恢复成打开状态
// 失败时， 返回 -1
//
// @example:
//  fd_1    --->   file
//
//  int fd_2 = dup2(fd_1, 3)
//
//  fd_1    --->   file  <---  fd_2

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
    // 复制标准输出， 此时有两个文件描述符指向终端
    int fd = dup2(STDOUT_FILENO, 3);
    // 关闭默认的标准输出描述符
    close(STDOUT_FILENO);
    
    sleep(1);

    char buffer[] = "hello world, boy";
    ssize_t num = write(fd, buffer, sizeof(buffer));
    if (num < 0) {
        perror("写入数据失败");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}