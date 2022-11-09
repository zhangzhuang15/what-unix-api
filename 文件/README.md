## 文件权限管理
有些文件你可以打开，有些文件你无法打开，原因在于文件有一套权限管理机制。  

最直观感受文件权限管理的方式是执行 `ls -lh`
![ls结果图](./ls%E7%BB%93%E6%9E%9C.png)

`-rw-r--r--`描述的就是文件权限  

开头的`-`表示文件类型是**普通文件**，如果开头是`d`表示文件类型是**文件夹**。

`rw-r--r--`三位一组，分成三组，从左到右依次代表：
user - 文件拥有者的权限；
group - 文件所属组的权限；
other - 其他情况下文件的权限；

`rw-` 表示：
`r` - 文件拥有者有读权限；
`w` - 文件拥有者有写权限；
`-` - 文件拥有者没有执行该文件的权限；

请留意第三位：
如果是`x`，则拥有者具有执行该文件的权限；
如果是`s`，表示在执行该文件的时候，可以将进程的有效用户ID设置为文件拥有者ID，允许实际用户执行该文件；
> `rwx` 在 chmod 函数中，等于 4 + 2 + 1 = 7;
> `r` 对应 `<fcntl.h>` 中的S_IRUSR 宏，这个宏等于0400,这是一个8进制数据，低2位的0，对应group other 权限，如果单看user位置的权限，`r` 就是 4；
> `s` 对应 S_ISUID 宏，这个宏等于 0x04000;

更多的字母含义See: `man ls`


为了加深印象，让我们再看几个问题

#### 为什么我们可以在shell中执行`ls -lh` ?
你执行一下`ls -lh /bin` 就可以发现，ls 这个可执行文件的拥有者是 `root`
![](./ls_bin_%E7%BB%93%E6%9E%9C.png)

尽管 ls 属于root， root具备超管权限，但并不意味着我们必须要有超管权限才能执行它。  

请看 ls 文件的权限:
  user:  `rwx` 
  group: `r-x`
  other: `r-x`

我们不是root，也和root不在同一个组wheel中，所以 other 表示的才是我们有什么权限，显然我们有读权限和执行权限，我们当然可以执行 ls 的。  


#### ps 权限中的 s 干啥用的？
![](./ls_ps.png)

ps 文件的权限：
user: `rws`
group: `r-x`
other: `r-x`

根据上一个问题，我们知道，我们可以执行 ps 。

那么， `rws` 中的 `s` 是什么意思呢？

ps 命令用于检索进程，而进程是一个系统概念，如果想获取系统级的信息，那我们必然应该具备非常高的权限，比如 root 权限。

先说一个知识点：对于一个进程来说，它有个 user id 的概念，用来表示这个进程是由谁创建的，又具备怎样的权限。

user id 具体分为
- 实际用户id（real-user-id，ruid）
- 有效用户id（effective-user-id，euid）
- 设置用户id（set-user-id，suid）

实际用户id表示这个进程是谁启动的。

有效用户id表示这个进程在访问文件系统时，是作为谁来访问的。

设置用户id 就和 文件权限中的 `s` 直接相关，没办法用一句话解释清楚，看个例子吧：

假设我们编写了一个c程序：
```c
#include <unistd.h>

int main() {
    char* const args[] = {"/bin/ps", "-a", NULL};
    execv("/bin/ps", args);

    return 0;
}
```
execv 函数会找到 ps 文件，发现 ps 文件权限设置了`s` , 于是 execv 函数会将 root 的 id 赋值给当前进程的 set-user-id, 之后通过 setuid 函数，将进程的 effective-user-id 赋值为 set-user-id，**这就是 set-user-id 的意义**。这个时候，进程的real-user-id 还是我们，但 euid 和 suid 变成了 root 的 id 了。

euid 已经是 root 的 id， 那么当前进程就会以 root 的身份去访问 文件系统。

但是，我们直接在 zsh 中执行的 ps，并不是在 c 程序中执行的，那么我们是怎样获取到root的文件权限？

事实上，zsh进程在启动后，会调整用户id，设置为我们，当执行 ps 时，实际上zsh进程会先 `fork` 一个子进程，在子进程中使用 `execve` 函数执行 ps，之后发生的事情和 c 程序调用 execv 执行 ps 时一样。
> 1. `execv` 函数底层调用的就是 `execve` 函数；
> 2. zsh启动后调整用户id，可以从github上的 zsh 源码得到验证，位于源码中的 options.c 文件中，你可以在源码中全局搜索 `setuid` 快速找到这个文件。

#### 为什么 nginx 启动时，要加上 sudo ?
nginx 作为守护进程，需要充分访问文件系统，因此nginx进程必须要拥有root权限。

遗憾的是，nginx 程序本身无法使用 setuid 函数将 euid（有效用户id）设置为 root的 id。所以，在启动的时候需要用 sudo 。

执行 `ls -lh /bin | grep sudo`, 你会发现 sudo 文件权限设置了 `s`，这样在执行的时候，sudo 进程就可以将 suid(set-user-id) 设置为 root 的 id，进而将euid 设置为 root 的 id，于是就拿到了 root 权限，执行 nginx 的时候，nginx 也就获得了 root 权限。
> 非root权限的进程，在执行 setuid 函数时，只能将 ruid 或者 suid 赋值给 euid。  


你可以用一个简单的 c 程序感受一下：
```c
#include <stdio.h>
#include <unistd.h>

int main() {
    uid_t ruid = getuid();
    uid_t euid = geteuid();

    printf("ruid: %d, euid: %d\n", ruid, euid);

    return 0;
}
```
编译后，直接执行一次，再加上 sudo 执行一次，你就发现第一次打印的是你的 id 值，第二次打印的是 0，也就是 root 的 id 值。

> 对于 macOS 而言，加上 sudo 获取的并不是最高超管权限，因为 macOS 拥有一个叫做 SPI 的机制，会阻止你编写的程序获取更高的权限，不信的话，你可以执行一下 `dtruss ls`, 再执行一下 `sudo dtrucc ls`, 你会发现二者都不管用。
#### 文件拥有者的ID等于进程实际用户ID，还是有效用户ID？
文件是通过进程执行相应的API创建的，因此文件拥有者的ID等于创建该文件的进程的有效用户ID。  
进程实际用户ID，表示的是启动该进程的是谁；
进程的有效用户ID，表示的是在进程中，访问文件系统资源的权限是怎样的；

#### 文件组ID就是进程的有效组ID吗？
一般来讲是这样的，但还有一种情况是文件组ID是文件所在目录的组ID。

当对文件权限的 group 设置 `s` 时，文件的 set-group-id 位就被设置了，此时文件的group id 值，等于 文件所在目录的 group id 值。


## API 快览
校验文件访问权限 - access
改变当前工作目录 - chdir
改变文件的权限   - chmod
改变文件拥有者   - chown
删除文件        - remove
重命名文件      - rename
遍历目录        - readdir
获取文件描述信息（权限，拥有者ID，组ID等）  - stat
设置文件权限屏蔽码 - umask
删除空目录        - rmdir
创建硬链接       - link
创建软连接       - symlink