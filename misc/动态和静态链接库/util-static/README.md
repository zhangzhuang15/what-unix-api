`gcc -c util.c`
> 只编译代码为 .o 文件，不链接，也不作为可执行文件

`ar r libutil.a util.o`
> 生成静态库文件 libutil.a
> 在 unix 上静态文件 .a 后缀，在Windows是.lib后缀
> 文件名是 lib{静态库名}

`gcc -o main -I "util-static" -L "util-static" -lutil main.c && ./main && rm main`
> -I 指定 include的时候，到哪个文件夹去找
> -L 指定 寻找静态库的时候，到哪个文件夹去找
> -l 指定静态库文件名，此时lib和.a后缀可省略
> 这一步也可以替换为 `gcc -o main -I "util-static" main.c ./util-static/libutil.a && ./main && rm main`