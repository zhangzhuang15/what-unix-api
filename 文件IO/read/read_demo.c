#include <stdio.h>

// memset函数所必需
#include <string.h>

// read close 函数所必需
#include <unistd.h>

// open函数所必需
#include <fcntl.h>

// 从 fd 中读取数据，存入到 buff 中
// ssize_t read(int fd, void *buff, size_t count)
// 成功时，返回 读取到的字节数；
// 文件全部读取完毕时， 返回 0； 读取大数据时，要一小块一小块读取，啥时候大数据都读完了呢，返回 0 的时候。
// 失败时，返回 -1；
//
// count   buff的字节大小。 buff是一个指针，可指针所指的内存有多大并不知道，需要用count变量指明。


int main() {
    int fd = open("./demo.txt", O_RDONLY);
    char buff[1024];
    memset(buff, 0, 1024);
    ssize_t bytes = read(fd, buff, 1024);
    switch (bytes)
    {
    case 0:
        printf("数据都读干净了\n");
        break;
    case -1:
        printf("读取数据发生了错误\n");
        break;
    default:
        printf("读取数据%zd bytes\n", bytes);
    }
    printf("读取到数据: %s\n", buff);

    close(fd);
}