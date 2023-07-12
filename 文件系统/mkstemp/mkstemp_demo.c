// mkstemp 所必需
#include <stdlib.h>

#include <stdio.h>

// 创建一个文件
// int mkstemp(char *template)
// 成功时，返回文件描述符；
// 出错时，返回 -1

int main() {
    mkstemp("demo.txt");
}