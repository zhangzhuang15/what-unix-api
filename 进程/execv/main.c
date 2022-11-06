// #include <unistd.h>
// int execv(const char * pathname, char* const args[])
// 执行一个程序
//
// pathname - 可执行文件的路径
// args    -  命令行参数，末尾元素必须是 NULL 或者 （char*)0
//
// 失败返回 -1； 成功不返回。
//
// execv 的 v 表示命令行参数采取`向量` 格式，也就是 args[]
#include <unistd.h>
#include <stdio.h>

int main() {
    char* const args[] = {"/usr/bin/gcc", "-v", NULL};

    int r = execv("/usr/bin/gcc", args);

    if (r < 0) printf("execv gcc -v failed\n");

    return 0;
}