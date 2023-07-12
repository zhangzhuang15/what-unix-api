// #include <unistd.h>
// off_t lseek(int fd, off_t offset, int whence)
// 设置当前文件操作的位置
//
// fd-文件描述符
// offset-文件偏移量
// whence-文件偏移量计算方式
//        SEEK_SET 文件开始处
//        SEEK_END 文件结尾处
//        SEEK_CUR 文件当前位置处
//
// 成功，返回新的文件偏移量
// 失败，返回-1

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    // #include <fcntl.h>
    int fd = open("./test.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        perror("文件无法打开");
        return -1;
    }

    lseek(fd, 0, SEEK_END);

    char buffer[] = "hello world";
                                // #include <string.h>
    int num = write(fd, buffer, strlen(buffer));

    if (num < 0) {
        perror("写入数据失败");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}