# typedef

## 简介

> typedef 用来为某个类型起别名 typedef type name;

```cpp
typedef unsigned char BYTE;
BYTE c = 'z';

typedef int antelope, bagel, mushroom;

typedef int five_ints[5];
five_ints x = {11, 22, 33, 44, 55};

// 为函数起别名
// 代表函数 signed char (*)(void);
typedef signed char (*fp)(void);
```

## 优势

- 更好的可读性
- 为 struct/union/enum 等复杂数据结构创建别名, 方便引用

```cpp
typedef struct animal {
  char* name;
  int leg_count, speed;
} animal;

// 这种情况下, 可以省略struct后面的类型名

typedef struct {
    char* name;
    int leg_count, speed;
} animal;
```

- 方便以后为变量改类型

```cpp
typedef float app_float;

app_float f1, f2, f3;
// 直接修改typedef, 方便修改f1 f2 f3的类型
```

- 可移植性 某一个值在不同计算机上的类型，可能是不一样的。 比如 int 这时使用类型别名 int32_t, 则无论 32 位还是 16 位计算机都没问题
- 简化类型声明

以下示例要再研究一下..

- x 是一个函数，返回一个指向 Arr 类型的指针。
- Arr 是一个数组，有 5 个成员，每个成员是 Func 类型。
- Func 是一个函数指针，指向一个无参数、返回字符值的函数

```cpp
char (*(*x(void))[5])(void);

//
typedef char (*Func)(void);
Func (*x(void))[5];

//
typedef char (*Func)(void);
typedef Func Arr[5];
Arr* x(void);
```
