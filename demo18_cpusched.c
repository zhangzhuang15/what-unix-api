#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <cpuid.h>

// refer: https://stackoverflow.com/questions/2215063/how-can-you-find-the-processor-number-a-thread-is-running-on/18866681#18866681
int main() {
    // int cpus = 0;
    // cpu_set_t mask;
    // cpus = sysconf(_SC_NPROCESSORS_ONLN);
    // printf("cpus: %d\n", cpus);
    // CPU_ZERO(&mask);
    // CPU_SET(2, &mask);
    // if (sched_se)

    printf("%d\n", );
}