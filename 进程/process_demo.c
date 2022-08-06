/** 展示进程方面的system call 使用方法
 *  fork
 *  vfork
 *  exec
 *  wait
 *  getpid
*/
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void test_fork() {
    printf("父进程-> 进程ID : %d\n", getpid());
    int m = 5;
    pid_t t;
    printf("before fork m: %d\n\n", m);
    
    t = fork();
    if (t < 0) {
        printf("子进程创建失败");
    }
    else if( t == 0) {
        printf("子进程->进程ID： %d\t父进程ID: %d\n", getpid(), getppid());
        m = 4;
        printf("子进程-> m: %d\n", m);
        printf("子进程退出\n");
        exit(0);
    }
    else {
        int status = 0;
        /* 阻塞等待子进程结束，回收其进程控制符
           如果父进程先于子进程结束，子进程成为孤儿进程，交由进程号1的进程控制
           如果子进程先于父进程结束，子进程成为僵尸进程，进程控制符无法释放，造成进程资源泄漏（进程控制符数量有限制，白白占用了一个进程控制符）
        */
        waitpid(t, &status, WUNTRACED | WCONTINUED);
        printf("父进程-> 子进程ID：%d\n m: %d\n status: %d\n", t, m, status);
        printf("父进程退出\n");
    }

}

int main() {
    test_fork();
}