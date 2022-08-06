#include <stdio.h>
#include <stdarg.h>
/* 展示c语言中， 函数中的可变参数用法 */
int sum(int,int,...);
int main(){
   printf("1+10+100 = %d", sum(3, 2, 1, 10, 100));
}

int sum(int length, int offset, ...){
    va_list list; /* 声明一个可变参数列表 */
    va_start(list, length);/* 从函数参数列表中...的位置依次获取 length个参数放入列表中 */
    int val = 0;
    int temp = 0;
    for(int i = 0; i < length; i++){
        temp = va_arg(list, int); /* 取出可变参数列表中的一个参数*/
        printf("temp is %d\n", temp);
        val += temp;
    }
    va_end(list);
    return val;
}