#include <stdlib.h>
#include <stdio.h>


void exit_handler(){
    printf("program is finished!");
}

int main(){
    atexit(exit_handler);
    double m = atof("4.28");
    int n = atoi("28");
    long p = atol("2000");
    printf("m is %.3f \n n is %d \n p is %ld \n", m, n, p);

    char* env = getenv("Name=Zhangzhuang");
    printf("Env is %s\n", env);

    printf("begin to use system function:\n");
    system("echo hello");


    return 0;
}