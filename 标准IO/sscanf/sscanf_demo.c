// sscanf 所需
#include <stdio.h>

// int sscanf(const char *restrict buf, const char *restrict format, ...)
// 成功时，返回输入的项数
// 失败时，返回EOF

int main() {
    char buff[10];
    sscanf("My name is 张剑客", "My name is %9s", buff);
    printf("your name is %s", buff);
}