// #include <unistd.h>
// int readlink(const char *restrict pathname, char *restrict buf, size_t bufsize)
// 读取链接文件所链接的文件的名字
// 
// pathname-软链接文件名
// buf-缓存区地址，存储所链接文件的名字
// bufsize-缓存区大小.
//
// 成功，返回读取的字节数
// 失败，返回-1

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // 准备文件
    int fd = open("./test.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        return -1;
    }
    close(fd);

    // 准备软链接文件
    int r = symlink("./test.txt", "./t-symlink");
    if (r < 0) {
        printf("创建失败");
        return -1;
    }

    // 读取, 故意把缓存区取小
    char buffer[5];
    // 最多就读取 5个字节，如果文件名过长，只会截断，不会读溢出
    int num = readlink("./t-symlink", buffer, 5);
    if (num < 0) {
        perror("读取失败");
        return -1;
    }

    buffer[num] = '\0';
    printf("文件名：%s\n", buffer);
    return 0;
}