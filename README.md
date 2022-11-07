# what-unix-api
example codes to introduce how to use native API of Unix system; more friendly to Chinese people.

## feature
- 非常简单的 Unix/Linux 系统API demo代码
- 基于《Unix环境高级编程》和《Linux-Unix系统编程手册》
- 对unix系统中的概念、模块提供友好、通俗的解释

## main language
C, some simple Rust or Go.

## why not C++
- 原汁原味的Unix/Linux 系统API都是C语言实现的，用C语言编写demo更合适；
  
- demo代码都很简单，用不上C++的高级特性，即便是用C++编写，那么风格注定也是偏C的，索性直接用C编写；
  
- C++的标准库存在对操作系统API的封装，并不能帮助我们彻底理解系统API；
  > 到酒馆喝酒，还是到酒厂观摩造酒，你自己挑。

- 本人喜欢简洁、易懂的代码，引入C++会把自己吓坏了；

## why Rust Or Go
别太担心哦，仅仅在做交叉编译介绍中会用到。