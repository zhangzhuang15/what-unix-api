## exec 系列函数

### 功能
用磁盘上的一个新程序替换当前程序，将进程的`程序段`、`数据段`、`堆栈`覆盖；

新程序从调用进程中继承：
1. 进程ID，父进程ID，进程组ID；
2. 实际用户ID，组ID，附属组ID；
3. 会话ID；
4. 控制终端；
5. 闹钟剩余时间；
6. 当前工作目录；
7. 根目录；
8. 文件模式创建屏蔽字；
9. 文件锁；
10. 进程信号屏蔽；
11. 未处理的信号；
12. 进程资源限制；
13. nice值；
14. tms_utime、tms_stime、tms_cutime、 tms_cstime

根据程序文件的 `set-user-id` 位 和 `set-group-id` 位，进程的`有效用户ID`和`有效组ID`可能会改变；

根据旧程序打开的文件描述符是否设置了`FD_CLOEXEC`，新程序会关闭一些文件描述符，所以可能不会完成继承所有打开的文件描述符；

### 形式
exec 系列函数包括：
```c
int execl(const char *pathname, 
          const char *arg0, 
          ..., 
          NULL);

int execle(const char *pathname, 
           const char *arg0,
           ..., 
           NULL, 
           char *const envp[]);

int execlp(const char *filename, 
           const char *arg0, 
           ..., 
           NULL);

int execv(const char *pathname, 
          char *const argv[]);

int execve(const char *pathname,
           char *const argv[],
           char *const envp[]);

int execvp(const char *filename,
           char *const argv[],
           char *const envp[]);

int fexecve(int fd,
            char *const argv[],
            char *const envp[]);
```
#### 字符含义
`l`: 表示command line 参数形式是 list（列表形式）;
`v`: 表示command line 参数形式是 vector(向量形式)
```c 
// list 形式
int func1(int a, int b, int c);
func1(1, 2, 3);



// vector 形式
int func1(int a, int v[]);
int v[] = {2, 3};
func1(1, v);
``` 

`p`: 表示会在 `PATH` 环境变量中查找程序文件的路径（所以是 `filename` 而不是 `pathname`），如果不是`机器可执行程序`，则当作一个shell脚本，由 `/bin/sh`（或者其他`系统默认的shell解释程序`）执行；

`e`: 表示可以给程序制定环境变量，这会覆盖掉`系统默认环境变量`，而不是取二者的并集, 因此函数入参有个 `envp`；

`f`: 表示程序文件由文件描述符确定；


### 各形式间的调用关系

```shell

execlp          execl             execle
  ⬇              ⬇                 ⬇
execvp  ---->   execv   ---->     execve (system call)
        PATH           environ      ⬆
                                  fexecve
```