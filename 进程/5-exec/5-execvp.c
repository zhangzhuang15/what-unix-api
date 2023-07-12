// #include <unistd.h>
// int execvp(const char* filename, char* const argv[])
// 执行一个可执行程序
//
// filename - 可执行文件名，比如 `node`
// argv - 命令行参数数组， 注意数组最后一个元素是 NULL 或者 (char*)0
//
// 成功，不返回；失败，返回-1
//
// execvp 的  v  -  vector， 对应 argv[]
//            p  -  表示会用环境变量PATH，检索文件名，确定文件路径
#include <unistd.h>
#include <stdio.h>

int main() {
    // 把 (char*)0 换成 NULL 也是可以的
    char *arg[] = {"echo", "hello world", (char*)0};
    int r = execvp("echo", arg);
    if (r < 0) {
        printf("执行失败");
    }
    return 0;
}