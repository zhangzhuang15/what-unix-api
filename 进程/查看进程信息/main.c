#include <libproc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysctl.h>
#include <string.h>

#define err -1

int main(int argc, char* argv[]) {
     
     /**
      * to get the information of a process on macOS, you can use proc_pidinfo API
      * which is declared in libproc.h by Apple;
      * 
      * the same case on Linux or other Unix-like system which support /proc/{processID}
      * file, you can read the file /proc/{processID};
      */
     struct proc_bsdinfo info;

     pid_t currentProc = getpid();
     int success = proc_pidinfo(currentProc, PROC_PIDTBSDINFO, 0, &info, sizeof(info));
     if (success <= 0) {
        perror("proc_pidinfo");
        return err;
     }

     printf("process program name: %s\n", info.pbi_name);
     printf("process program name 2: %s\n", info.pbi_comm);
     printf("process PID: %u\n", info.pbi_pid);
     printf("process PPID: %u\n", info.pbi_ppid);
     printf("process user ID: %u\n", info.pbi_uid);
     printf("process real user ID: %u\n", info.pbi_ruid);
     printf("process svuid: %u\n", info.pbi_svuid);
     printf("tty process group ID: %u\n", info.e_tpgid);
     printf("process group leader ID: %u\n", info.pbi_pgid);
     printf("controlling tty dev: %u\n", info.e_tdev);
     printf("process nice value: %d\n", info.pbi_nice);
     printf("session ID: %d\n", getsid(currentProc));

     if (info.pbi_flags & PROC_FLAG_SYSTEM) {
        printf("is system process\n");
     } else {
        printf("is not system process\n");
     }

     if (info.pbi_flags & PROC_FLAG_TRACED) {
        printf("this process is traced by gdb\n");
     } else {
        printf("this process is not traced by gdb\n");
     }

     if (info.pbi_flags & PROC_FLAG_SLEADER) {
        printf("this process is session leader\n");
     } else {
        printf("this process is not session leader\n");
     }

     if (info.pbi_flags & PROC_FLAG_CTTY) {
        printf("this process has a control tty\n");
     } else {
        printf("this process doesn't have a control tty\n");
     }

     if (info.pbi_flags & PROC_FLAG_CONTROLT) {
        printf("this process has a control terminal\n");
     } else {
        printf("this process doesn't have a control terminal\n");
     }

    /**
     * info.pbi_name and info.pbi_comm are not enough for me, they
     * only tell me the executable file name, other arguments of a
     * command are ignored.
     * 
     * e.g. you call "./main --help hello", a process will run. 
     * info.pbi_name only tell you "./main", so how to get the
     * part of "--help hello" ?
     * 
     * on Linux or other Unix-like system which support /proc/{processID}
     * file, you can read /proc/{processID}/cmdline;
     * 
     * on macOS, you can use sysctl API which is declared in sys/sysctl.h,
     * the following code is a demo.
     */

    /**
     * in c, we should use a buffer to load command line whose data type is string, 
     * so, what size of buffer we should alloc ? don't worry, we just use the largest
     * size which macOS supports.
     * 
     * we invoke sysctl to get the largest size, and load it in variable `argmax`;
     * mib will tell sysctl to do what, you can use  `man 3 sysctl` to know more.
     */
    int argmax;
    int mib[3];
    size_t size = sizeof(argmax);

    mib[0] = CTL_KERN;
    mib[1] = KERN_ARGMAX;

   
    if (sysctl(mib, 2, &argmax, &size, NULL, 0) < 0) {
        perror("sysctl failed call argmax");
        return err;
    }
   
   /**
    * we use `argmax` to alloc a buffer `procArgs`, and the command line we expect
    * will be load in `procArgs`.
    * 
    * to get the command line, we should make changes in `mib`, telling sysctl to
    * get the command line of a process whose ID is `currentProc`.
    * 
    * remember that we cannot assign `&argmax` to the 4-th argument of `sysctl`,
    * the reason is simple:
    * 1. 4-th argument of `sysctl` is a *size_t type;
    * 2. if we assign a *int type data to it, c compiler will auto-transfer it to
    * *size_t type, bringing unexpected action, maybe cause `sysctl` fail to invoke;
    */

    mib[1] = KERN_PROCARGS2;
    mib[2] =  currentProc;
    char* procArgs = (char*)malloc(argmax * sizeof(char));
    size = argmax;

    if(sysctl(mib, 3, procArgs, &size, NULL, 0) == -1) {
        perror("sysctl failed call procArgs");
        return err;
     };

     /**
      * now, the command line we expect is located in `procArgs`;
      * 
      * before we access the command line, talk something about the
      * data structure of `procArgs`:
      * 
      * 1. the sizeof(int) bytes starting from `procArgs` will record the
      *    length of command line.
      *    e.g. if the command line is "./main --help hello", the length of
      *    command line is 3 because of { "./main", "--help", "hello" };
      *    we save this value in `args`.
      * 
      * 2. after the 4 bytes, there are executable file name and command line.
      *    first, we declare a pinter to point the string of executable file name
      *    by `arg`, then we don't need executable file name, so we adapt 
      *    `arg += strlen(arg) + 1` to jump over the executable file name,
      *    i.e. *(arg) is executable file name.
      * 
      * 3. we have known that there are `args` command line args, we could use
      *    a loop which is limited by `args` to access command line args.
      *    e.g. if command line is "./main --help hello", the first loop we will
      *    get "./main" by *(arg), the second loop we will get "--help", the final
      *    loop we will get "hello"(`args` is 3 in this case).
      * 
      */
     int args = *(int*)procArgs;

     printf("args: %d\n", args);

     int count = 0;

     char* arg = procArgs + sizeof(int);
     arg += strlen(arg) + 1;
     while(count < args) {
        if (*arg == '\0') arg += 1;
        else {
            printf("%s\n", arg);
            arg += strlen(arg) + 1;
            count++;
        }
     }

     free(procArgs);
     return 0;

}