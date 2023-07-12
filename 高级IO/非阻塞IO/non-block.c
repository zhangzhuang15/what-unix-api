// 非阻塞IO只需给IO操作设置非阻塞标志位
// 1）open中指定 O_NONBLOCK
// 2) fcntl中设置 O_NONBLOCK


#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = open("./test.txt", O_WRONLY | O_CREAT | O_NONBLOCK);
    if (fd < 0) {
        perror("无法打开文件");
        return -1;
    }

    int flag = fcntl(fd, F_GETFL);
    if (flag & O_NONBLOCK == 0) {
        int ok = fcntl(fd, F_SETFL, O_NONBLOCK);
        if (ok < 0) {
            perror("设置非阻塞失败");
            close(fd);
            return -1;
        }
    }
    close(fd);
    return 0;
}