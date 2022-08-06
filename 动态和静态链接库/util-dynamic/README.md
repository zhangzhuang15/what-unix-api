`gcc -fPIC -shared -o libutil.dylib util.c`
> 生成动态链接库；
> 动态链接库名格式为 lib{库名}.{后缀};
> linux的后缀是 so;
> Mac的后缀是 dylib;
> Windows的后缀是 dll;
> -fPIC 中 PIC的含义是`Position Independent Code`;

将 libutil.dylib 存入 /usr/local/lib中
> 连接器运行时，会到 `/usr/lib` `/usr/local/lib`中寻找动态链接库，但是前者无权编辑;

`gcc -I "util-dynamic" -L "util-dynamic" -lutil -o main main.c && ./main && rm main`
> 动态链接库和静态链接库重名时，优先选择动态链接库。