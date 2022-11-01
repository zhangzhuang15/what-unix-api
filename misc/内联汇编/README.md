内联汇编由编译器支持，编译器会提供一些关键字或者宏，让编程者可以在C语言中直接嵌入汇编代码，但这并不是C语言规范的一部分，只是编译器提供的一种功能。

### GCC内联汇编方案
#### asm
基本内联汇编：
```c 
asm(
    "汇编指令1" "\n\t"
    "汇编指令2" "\n\t"
    ...
);

asm(
    "汇编指令1; "
    "汇编指令2; "
    ...
);
```



扩展式内联汇编：
```c
asm(
    "汇编指令1" "\n\t"
    "汇编指令2" "\n\t"
    ...
    : "=r"(name), "=r"(age)
    : "=r"(message)
    : "memory"
);
```
详见：https://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html