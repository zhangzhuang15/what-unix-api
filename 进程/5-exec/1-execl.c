// #include <unistd.h>
// int execl(const char* pathname, const char* arg0, ..., const char* argN)
// 执行一个机器可执行程序
//
// pathname - 可执行文件的路径
// arg0, ..., argN  - 命令行参数
//       argN -   NULL 或者 (char*)0
//
// 成功，不返回；失败，返回-1
//
// execl 的   l 表示 命令行参数采取`列表`的形式
#include <unistd.h>
#include <stdio.h>

int main() {
    int r = execl("/usr/bin/gcc", "/usr/bin/gcc", "-v", NULL);
    if (r < 0) printf("invoke gcc -v failed\n");
    return 0;
}