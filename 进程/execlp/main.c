// #include <unistd.h>
// int execlp(const char *filename, const char *arg0, ..., (char*) 0)
// 执行一个程序
//
// filename-可执行文件名或者路径
//        如果是文件名，则会到PATH中寻找
// arg0,...-可执行文件的若干执行参数
// (char*)0-可变参数结尾
//         因为使用 va_list解析变长参数，所以要有个标志参数结尾;
//         把 （char *）0 改成 NULL 也是可以的
//
// 成功，不返回值
// 失败，返回-1

#include <unistd.h>
#include <stdio.h>

int main() {
    int r = execlp("echo", "echo", "hello world", (char *)0);
    if (r < 0) {
        printf("执行失败");
    }
    return 0;
}