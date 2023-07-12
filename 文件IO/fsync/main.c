// #include <unistd.h>
// int fsync(int fd)
// 将文件中修改的数据落盘，并更新文件属性
//
// fd-文件描述符
//
// 成功，返回0
// 失败，返回 -1
//
// 常用于数据库

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MB 1024*1024
int main() {
    int fd = open("./test.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        return -1;
    }
    
    char* buffer = (char*)malloc(10*MB);
    memset(buffer, 'k', 10*MB);
    write(fd, buffer, 10*MB);
    fsync(fd);
    close(fd);
    free(buffer);
    return 0;
}

