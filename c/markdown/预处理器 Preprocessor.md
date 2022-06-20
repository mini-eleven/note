# 预处理器

## 简介

C 语言编译器在编译程序之前，会先使用预处理器（preprocessor）处理代码。

预处理器首先会清理代码，进行删除注释、多行语句合成一个逻辑行等工作。然后，执行#开头的预处理指令。本章介绍 C 语言的预处理指令。

所有预处理指令都是一行的，除非在行尾使用反斜杠，将其折行。指令结尾处不需要分号。

## #define

> #define 是最常见的预处理指令，用来将指定的词替换成另一个词。它的参数分成两个部分，第一个参数就是要被替换的部分，其余参数是替换后的内容。每条替换规则，称为一个宏（macro）。

> 同名的宏可以重复定义，只要定义是相同的，就没有问题。如果定义不同，就会报错。

## 单参数的宏

> 什么时候使用带参数的宏, 什么时候使用函数呢? 一般来说，应该首先使用函数，它的功能更强、更容易理解。宏有时候会产生意想不到的替换结果，而且往往只能写成一行，除非对换行符进行转义，但是可读性就变得很差。

### 基本用法

- #define SQUARE(X) X\*X
- #define getchar() getc(stdin)
- #define MAX(x, y) ((x)>(y)?(x):(y)) #define IS_EVEN(n) ((n)%2==0)

### #运算符, ##运算符

- 由于宏不涉及数据类型，所以替换以后可能为各种类型的值。如果希望替换后的值为字符串，可以在替换文本的参数前面加上#。

```cpp
#define STR(x) #x

// 等同于 printf("%s\n", "3.14159");
printf("%s\n", STR(3.14159));

#define XNAME(n) "x"#n

// 输出 x4
printf("%s\n", XNAME(4));
```

- 如果替换后的文本里面，参数需要跟其他标识符连在一起，组成一个新的标识符，可以使用##运算符。它起到粘合作用，将参数“嵌入”一个标识符之中。

```cpp
#define MK_ID(n) i##n

int MK_ID(1), MK_ID(2), MK_ID(3);
// 替换成
int i1, i2, i3;
```

### 不定参数的宏

> 宏的参数还可以是不定数量的（即不确定有多少个参数），...表示剩余的参数。

```cpp
#define X(a, b, ...) (10*(a) + 20*(b)), __VA_ARGS__

X(5, 4, 3.14, "Hi!", 12)
// 替换成
(10*(5) + 20*(4)), 3.14, "Hi!", 12

// __VA_ARGS__前面加上一个#号，可以让输出变成一个字符串。
#define X(...) #__VA_ARGS__

printf("%s\n", X(1,2,3));  // Prints "1, 2, 3"
```

## undef

> #undef 指令用来取消已经#define 定义的宏

> gcc 的 -U 选项可以在命令行取消宏定义

```cpp
#define LIMIT 400
#undef LIMIT
```

## include

```cpp
// 形式一
#include <foo.h> // 加载系统提供的文件

// 形式二
#include "foo.h" // 加载用户提供的文件
```

## #if...#endif

> GCC 的-D 参数可以在编译时指定宏的值, 因此可以方便的打开调试开关 gcc -DDEBUG=1 foo.c

```cpp
#define FOO 1
#if FOO
  printf("defined\n");
#else
  printf("not defined\n");
#endif

#if HAPPY_FACTOR == 0
  printf("I'm not happy!\n");
#elif HAPPY_FACTOR == 1
  printf("I'm just regular\n");
#else
  printf("I'm extra happy!\n");
#endif
```

## ifdef...#endif

> 有时源码文件可能会重复加载某个库，为了避免这种情况，可以在库文件里使用#define 定义一个空的宏。通过这个宏，判断库文件是否被加载了。

```cpp
#ifdef MAVIS
  #include "foo.h"
  #define STABLES 1
#else
  #include "bar.h"
  #define STABLES 2
#endif
```

## defined 运算符

> #if defined 等同于 上面#ifdef

```cpp
#if defined IBMPC
  #include "ibmpc.h"
#elif defined MAC
  #include "mac.h"
#else
  #include "general.h"
#endif
```

## #ifndef...#endif

> #ifndef...#endif 指令跟#ifdef...#endif 正好相反

```cpp
#ifndef FOO
// 等同于
#if !defined FOO
```

## 预定义宏

- \_\_DATE\_\_：编译日期，格式为“Mmm dd yyyy”的字符串（比如 Nov 23 2021）。
- \_\_TIME\_\_：编译时间，格式为“hh:mm:ss”。
- \_\_FILE\_\_：当前文件名。
- \_\_LINE\_\_：当前行号。
- \_\_func\_\_：当前正在执行的函数名。该预定义宏必须在函数作用域使用。
- \_\_STDC\_\_：如果被设为 1，表示当前编译器遵循 C 标准。
- \_\_STDC_HOSTED\_\_：如果被设为 1，表示当前编译器可以提供完整的标准库；否则被设为 0（嵌入式系统的标准库常常是不完整的）。
- \_\_STDC_VERSION\_\_：编译所使用的 C 语言版本，是一个格式为 yyyymmL 的长整数，C99 版本为“199901L”，C11 版本为“201112L”，C17 版本为“201710L”。

```cpp
#include <stdio.h>

int main(void) {
  printf("This function: %s\n", __func__);
  printf("This file: %s\n", __FILE__);
  printf("This line: %d\n", __LINE__);
  printf("Compiled on: %s %s\n", __DATE__, __TIME__);
  printf("C Version: %ld\n", __STDC_VERSION__);
}

/* 输出如下

This function: main
This file: test.c
This line: 7
Compiled on: Mar 29 2021 19:19:37
C Version: 201710

*/
```

## #line

> #line指令用于覆盖预定义宏__LINE__，将其改为自定义的行号。后面的行将从__LINE__的新值开始计数。

```cpp
// 将下一行的行号重置为 300
#line 300
```

## #error

> #error指令用于让预处理器抛出一个错误，终止编译。

```cpp
#if defined WIN32
  // ...
#elif defined MAC_OS
  // ...
#elif defined LINUX
  // ...
#else
  #error NOT support the operating system
#endif
```

## #pragma

> #pragma指令用来修改编译器属性。

```cpp
// 使用 C99 标准
#pragma c9x on
```