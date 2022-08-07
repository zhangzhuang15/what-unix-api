// #include <unistd.h>
// int symlink(const char *actualpath, const char *sympath)
// 创建软链接（符号链接）
//
// actualpath-被链接的文件路径，该文件可以不存在
// sympath-软链接文件路径
//
// 成功返回0
// 失败返回-1

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

    int r = symlink("./test.txt", "./t-symlink");
    if (r < 0) {
        printf("创建失败");
        return -1;
    }

    return 0;
}