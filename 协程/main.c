#include<stdio.h>

int gen(int left, int right) {
    // NOTE: 设置 static int 类型数据也是一个关键，
    // 这种变量具备 “记忆”，可以记录上一次调用时的状态，
    // 这就为状态机的形成做好了铺垫。
    static int state = 0, i = 0;
    
    switch(state) {
        case 0:
          for(i = left; i < right; i++) {
            state = 1;
            return i;
            case 1:;     // 我去，case 还可以放在另一个case的代码块里边！ NOTE: 这就是无栈协程实现上的一个关键原理
          }
    }
    return -1;
}


int main() {
    int num = gen(0, 3);
    printf("num: %d\n", num);

    num = gen(0, 3);
    printf("num: %d\n", num);

    num = gen(0, 3);
    printf("num: %d\n", num);

    num = gen(0, 3);
    printf("num: %d\n", num);

    return 0;
}