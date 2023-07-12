// 使用全局变量 char** environ,
// 在 C 程序中获取系统自带和用户自定义的环境变量！
#include <stdio.h>

extern char** environ;

int main(int argc, char** argv) {
    printf("argc: %d\n", argc);

    for(int i = 0; *argv != NULL; i++, argv++) {
        printf("argv[%d]: %s\n", i, *argv);
    }

    for (int i = 0; *environ != NULL; i++, environ++) {
        printf("env[%d]: %s\n", i, *environ);
    }

    return 0;
}