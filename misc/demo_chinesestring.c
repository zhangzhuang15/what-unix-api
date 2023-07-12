#include <stdio.h>

int main() {
    char *p = "你好hello";
    /*中文字符占据三个字节*/
    char m[4] = { p[0], p[1], p[2], '\0'};
    printf("%s\n", p);
    printf("%s\n", m);
}