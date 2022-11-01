#include <stdio.h>
#include <setjmp.h>

int main(){
    // 锚点
    jmp_buf buff;
    int num = 0;
    // 设置锚点，返回锚点初始值 0
    int result = setjmp(buff);
    for(int i = 1; i < 10 && result < 3; i++){
        printf("epoch %d : %d\n", num, i);
    }
    if(result < 3){
        // 跳转到锚点所在代码，也就是第9行代码，
        // 设置锚点值为 ++num
        longjmp(buff, ++num);
    }
    
}