#include <stdio.h>
#include <stdlib.h>

void traverse(int m[], int length){
    /* 一个数组名作为函数参数，会将其转换为指针类型，
       在调用sizeof的时候， 返回的是指针变量占据的内存大小，不是数组 
       int m[]生命 等效于 int *m  
    */
    printf("sizeof m in traverse function : %lu\n", sizeof(m));
    for (int i = 0; i < length; i++) {
        printf("traverse : %d\n", *(m+i));
    }
}

void traverse2(int *m, int length) {
    printf("sizeof m in traverse2 function : %lu\n", sizeof(m));
    for (int i = 0; i < length; i++) {
        printf("traverse2 : %d\n", m[i]);
    }
}


int main() {
    int m[] = { 1, 2, 3, 4, 5};
    /* 数组名作为sizeof的参数时，返回整个数组占据的内存大小，单位字节 */
    printf("sizeof m array : %lu\n", sizeof(m));
    printf("sizeof m[0] : %lu\n", sizeof(m[0]));
    printf("sizeof int ; %lu\n", sizeof(int));
    traverse(m, 5);
    traverse2(m, 5);
    int *n = (int*)malloc(sizeof(int)*5);
    /* 指向数组的指针作为sizeof的参数时，返回的是该指针占据内存的大小，单位字节 */
    printf("sizeof n array made in malloc way : %lu\n", sizeof(n));
    n[4] = 25;
    /* 数组从最多容纳5个元素升级为容纳6个元素*/
    n = (int*)realloc(n, sizeof(int)*6);
    /* 扩展内存大小后，n[4]的值没有受到影响 */
    printf("after realloc operation n[4] : %d\n", n[4]);
    /* 打印各个元素的逻辑地址，看看0～5地址是不是越来越大, 
       确实是这样，地址越来越大 */
    for (int i = 0 ; i < 6 ; i++ ){ 
        printf("array[%d] logical address: %#x\n", i, (unsigned int)(n+i));
    }
    free(n);
    /* 统一都是8字节 */
    printf("sizeof char* : %lu\n", sizeof(char*));
    printf("sizeof float* : %lu\n", sizeof(float*));
    printf("sizeof double* : %lu\n", sizeof(double*));
    printf("sizeof long* : %lu\n", sizeof(long*));

    const int length = 5;
    /*const int 类型可以， int类型不可以*/
    int p[length];
    for (int i = 0 ; i < length; i++) {
        p[i] = i;
    }
    traverse(p, length);
}