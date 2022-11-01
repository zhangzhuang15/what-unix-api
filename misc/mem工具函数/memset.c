#include <string.h>
#include <stdio.h>


// memset(char* src, char value, size_t n)
// 将 src 指向的 n 个字节都替换成 value


int main() {
    char src[] = "hello world";
    char* ptr = src + 6;
    printf("before memset: %s\n", src);
    memset(ptr, 'w', 5);
    printf("after memset: %s\n", src);
}