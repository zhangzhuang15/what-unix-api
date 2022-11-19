// #include <stdio.h>
// FILE* popen(const char* cmd, const char* type)
//  fork一个子进程，用exec执行 cmd 命令，返回一个 FILE，读取子进程
// 标准输出，或者写入子进程的标准输入
//
// cmd - 命令字符串， 比如 “gcc -v”
// type - 
//        "r" FILE 用于读取子进程标准输出
//        "w" FILE 用于写入子进程标准输入
//
// 成功返回 FILE* 类型数据，失败返回NULL
//
// 别忘记用 pclose 函数关闭 FILE, 该函数会等待子进程结束，返回子进程终止码

#include <stdio.h>
#include <sys/wait.h>

int main() {
    FILE* f = popen("gcc -v>&1", "r");

    if (f == NULL) {
        perror("popen调用失败");
        return -1;
    } 

    char buff[512];
    size_t n = fread(buff, sizeof(char), 512, f);
    if (n < 0) {
        perror("fread调用错误");
        return -2;
    }

    
    printf("result: %s\n", buff);

    // 子进程终止码
    int stopCode = pclose(f);
    printf("exit code: %d\n", WEXITSTATUS(stopCode));

    return 0;
}