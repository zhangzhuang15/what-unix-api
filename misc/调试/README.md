### 调试C程序

#### 使用vscode
1. 安装`gcc` 或 `clang`;
2. 安装vscode官方 **C/C++** 插件；
3. 选中vscode左侧的调试面板，点击debug, 依照提示选中准确的`lldb`调试器；(linux上是 `gdb`)
4. 修改调试器对应的launch.json文件配置。
```json{.line-numbers}
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(lldb) 启动",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/调试/main", 
            "args": ["--size", "4", "--C"],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "lldb"
        }
    ]
}
 ```
 > launch.json文件的注释中会告诉你，可以到哪个网站获取如何配置的资料。
 > 所以不用太担心啦🤭

 5. 源码位置打好断点，点击左上方的绿色箭头，即可调试。



#### GDB/LLDB工具
1. 安装 gdb/lldb 工具；
   > linux和macOS一般系统自带；
   > 如果没有，可以使用 `apt-get` 或者 `brew` 安装；

2. 编译源代码： `gcc main.c -g -o main`
   > 必须要`-g`，这样编译出来的结果中，包含了调试器所需要的信息；

3. 调试器启动程序： `lldb ./main` 
如果想让程序启动时接收命令行参数，
可`lldb -- ./main -C 4 --ok`.
`-C 4 --ok` 就是命令行参数，
在main函数第二个参数可以访问到；
    > gdb 同理

4. 在lldb或者gdb的调试界面中，开始调试。
   > 具体调试指令，使用 `help` 查看，调试器解释得很详细哦😎