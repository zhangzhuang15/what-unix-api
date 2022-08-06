// scanf 所必需
#include <stdio.h>

//
// int scanf(const char *restrict format, ...)
// 成功时，返回输入项数；
// 失败时，返回EOF

int main() {
    char buff[10];
    printf("输入你的名字\n");
    scanf("%9s", buff);

    printf("你的名字是%s", buff);
}