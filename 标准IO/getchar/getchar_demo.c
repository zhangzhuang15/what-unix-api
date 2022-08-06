// getchar所必需
#include <stdio.h>

// 从标准输入读取一个字符
// int getchar(void)
// 成功时，返回字符；
// 失败，返回 EOF

int main() {
    printf("输入一个字符吧\n");
    int letter = getchar();
    printf("输入的时 %c\n", letter);
}