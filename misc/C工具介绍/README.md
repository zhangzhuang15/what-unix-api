### GNU工具链组成
* binutils: 二进制工具包，包含 `assembler` `linker` `readelf`
* gcc: 编译器 
* C库：基于POSIX的标准化API

工具链是在具体一个平台上使用的，所以按照不同平台，工具链有不同实现。
CPU架构 + 供应商 + 操作系统内核 确定了一个平台。
在使用 binutils 的时候，必须下载正确平台的binutils实现。

### C库种类
glibc: 标准的GNU C库，非常大，最完整的POSIX API实现；
musl libc： 轻小的C库实现；
uClibc-ng: 微控器的C库；
eglibc： glibc的分支，用于嵌入式应用。

### C库的组成
libc：最常用的POSIX函数，如printf，open，close，read，write等
libm：数学函数，如cos，exp，log
libpthread: POSIX线程函数；
librt: POSIX的real-time扩展，包括shared memory和asynchronous I/O

### C库的使用
当用gcc编译的时候，可以不用指明libc，这个应该是gcc会自动去引入的，
其他的需要用-l指明，比如引入 libm, 就要指定 -lm.

### Glibc
C语言的函数库，封装系统调用，提供了很多工具函数。
Posix API 就包含在内。


### gcc
光有上边的函数库还不行，还要有编译器。
编译器里边也包括连接器。
有 gnu 版本 和 musl 版本。
> gnu版本对c的支持非常全，musl版本更加轻量，而且采用静态编译。

编译器的实现和CPU架构、操作系统相关。
在交叉编译的时候，要用到指定CPU架构操作系统下的连接器。

### binutils
二进制文件的工具包。

因为我们用gcc将代码编译成二进制文件后，仍需要一些工具帮助我们
阅读、分析二进制文件的信息。这个工具包内就提供了这些工具。

通常这是一系列二进制工具小程序的集合。

包括 `readelf` `nm` `hexdump` `strip` 等工具。