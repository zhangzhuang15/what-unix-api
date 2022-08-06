#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid1 = fork();
    pid_t pid2 = fork();
    pid_t pid3 = fork();

    printf("(pid1, pid2, pid3) => (%d, %d, %d)\n", pid1, pid2, pid3);
}