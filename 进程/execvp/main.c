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