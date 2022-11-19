// #include <unistd.h>
// int execve(const char *pathname, char *const argv[], char *const envp[])
// 执行一个机器可执行程序
//
// pathname - 可执行程序文件的完整路径
// argv     - 可执行程序的参数向量
//            argv[0] == pathname
//            argv最后一个值是 NULL
// envp     - 环境变量向量
//            envp最后一个值是 NULL
//
// 成功，不返回；失败，返回-1

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;
int main() {
    
    // 往 environ 添加环境变量数据
    putenv("jason=false");
    putenv("zhangzhuang=yes");

    char *pathname = "/usr/bin/env";
    char *const argv[] = {pathname, NULL};

    int r = execve((const char*)pathname, argv, environ);

    if (r < 0) {
        printf("execve failed\n");
    }

    return 0;
}