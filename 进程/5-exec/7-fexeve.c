// #include <unistd.h>
// int fexecve(int fd, char *const argv[], char *const envp[])
// 执行一个机器可执行程序
//
// fd - 程序文件的文件描述符
// argv - 可执行程序的参数向量
// envp - 可执行程序的环境变量
//
// 成功，不返回；失败，返回-1
//
// 注意：
//   macOS 似乎不支持，请在 linux 上执行；

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

extern char **environ;

int main() {
    int fd = open("/usr/bin/env", O_RDONLY);

    if (fd < 0) {
        printf("open failed\n");
        return -1;
    }

    const char *const argv[] = {"/usr/bin/env", NULL};
    int r = fexecve(fd, argv, environ);

    if(r < 0) {
        printf("fexecve failed\n");
        close(fd);
    }

    return 0;
}