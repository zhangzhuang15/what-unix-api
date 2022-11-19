// #include <unistd.h>
// int execle(const char *pathname, const char *arg0, ..., NULL, char *const envp[])
// 执行一个机器可执行程序
//
// pathname - 机器可执行文件的路径；
// arg0,..., NULL - 程序输入的参数；
// envp - 程序运行的环境变量，会覆盖掉系统环境变量
//        如果设置为 NULL, 环境变量为空
//        如果不传，报错
//
// 成功，不返回；失败，返回-1

#include <unistd.h>
#include <stdio.h>

int main() {
    char *const envp[] = {"zhangzhuang=true", "perter=false", NULL };
    int r = execle("/usr/bin/env", "/usr/bin/env", NULL, envp);

    if (r < 0) {
        printf("execle failed\n");
    }

    return 0;
}