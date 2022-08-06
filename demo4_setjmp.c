#include <stdio.h>
#include <setjmp.h>

int main(){
    jmp_buf buff;
    int num = 0;
    int result = setjmp(buff);
    for(int i = 1; i < 10 && result < 3; i++){
        printf("epoch %d : %d\n", num, i);
    }
    if(result < 3){
        longjmp(buff, ++num);
    }
    
}