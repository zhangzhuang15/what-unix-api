// 使用 <stdarg.h> 获取函数的不定长参数！

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
typedef struct {
    char* msg;
    u_int32_t len;
} Message;

/* 展示c语言中， 函数中的可变参数用法 */
int sum(int,unsigned char,...);

int main(){
    Message m = {
        "Come on!",
        strlen("Comon on!"),
    };

    sum(3, 'A', "Jack", (double)98.23, &m);
}

int sum(int id,unsigned char rank, ...){
    va_list list; /* 声明一个可变参数列表 */
    va_start(list, rank);/* 告诉list，可变参数从 rank 后边的参数算起 */

    printf("hello , welcome to this world " "\n"
           "some information:" "\n");

    printf("ID: %d\n", id);
    printf("Rank: %c\n", rank);

    const char* name = va_arg(list, char*);
    printf("Name: %s\n", name);

    const double score = va_arg(list, double);
    printf("Score: %f\n", score);

    const Message* m = va_arg(list, Message*);
    printf("Message: %s\n", m->msg);

    va_end(list);
    return 0;
}

/**
 * func(int arg1, char arg2, int arg3, char* arg4)
 * 按照c函数入参顺序，有
 * 
 * arg1           高地址
 * arg2
 * arg3
 * arg4           低地址
 * 
 * va_start(list, arg2) ， 会出现
 * arg1
 * arg2    <- list
 * arg3
 * arg4
 * 
 * va_arg(list, int), list 会向下移动4个字节，读取arg3
 * arg1
 * arg2
 * arg3   <- list
 * arg4
 * 
 * 
 * 举个读取数据的例子，内存排列如下：
 * 地址          数据
 *  6           0x01
 *  5           0x04
 *  4           0x02
 *  3           0x05
 *  2           0x07
 *  1           0x10           <- list
 * 
 *  如果 list 是 char 类型， list 读取一个字节，就是 0x10
 *  如果 list 是 int 类型， list 读取4个字节， 就是 0x02050710
 *  如果 list 是 int* 类型（假设指针类型是4个字节），list读取4个字节， 就是 0x02050710, 只不过这个数据代表地址！
 */