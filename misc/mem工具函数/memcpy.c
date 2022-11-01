#include <string.h>
#include <stdio.h>

// memcpy(void* dest, const void* src, size_t n)
// 将 src 指向的 n 个 byte 复制到 dest指向的位置


int main() {
    char dest[] = "hello world";
    char src[] = "hello Peter";
    printf("before dest: %s\n", src);
    memcpy(dest + 6, src + 6, 5);
    printf("after dest: %s\n", src);
}