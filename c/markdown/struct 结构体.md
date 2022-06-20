# struct

## 简介

> 定义一个 struct

```cpp
struct car {
    char* name;
    int speed;
    float price;
};

struct car model3 = {"telsa", 230, 270000};
// 或者将struct的声明和变量的声明合起来
struct book {
    char* title;
    float value;
} b1;
```

> 用 typedef 给 struct 指定一个别名, 这样更简介

```cpp
typedef struct cell_phone {
    int cell_no;
    float price;
} phone;

phone p = {.cell_no = 123333};
```

> 指针变量也可以指向 struct

```cpp
struct book {
  char title[500];
  char author[100];
  float value;
}* b1;

// 或者写成两个语句
struct book {
  char title[500];
  char author[100];
  float value;
};
struct book* b1;
```

上面示例中，变量 b1 是一个指针，指向的数据是 struct book 类型的实例。

> struct 结构也可以作为数组成员

```cpp
// 声明了一个有200个car类型的cars数组
struct car cars[200];
```

> struct 结构占用的存储空间, 不是各个属性存储空间的总和, 而是最大内存占用属性的存储空间的倍数, 其他属性会添加空位与之对齐, 这样可以提高效率

```cpp
struct foo {
  int a;
  char* b;
  char c;
};
printf("%d\n", sizeof(struct foo)); // 24
```

上面示例中，struct foo 有三个属性，在 64 位计算机上占用的存储空间分别是：int a 占 4 个字节，指针 char* b 占 8 个字节，char c 占 1 个字节。它们加起来，一共是 13 个字节（4 + 8 + 1）。但是实际上，struct foo 会占用 24 个字节，原因是它最大的内存占用属性是 char* b 的 8 个字节，导致其他属性的存储空间也是 8 个字节，这样才可以对齐，导致整个 struct foo 就是 24 个字节（8 \* 3）。

多出来的存储空间，都采用空位填充，所以上面的 struct foo 真实的结构其实是下面这样。

```cpp
struct foo {
  int a;        // 4
  char pad1[4]; // 填充4字节
  char *b;      // 8
  char c;       // 1
  char pad2[7]; // 填充7字节
};
printf("%d\n", sizeof(struct foo)); // 24
```

为什么浪费这么多空间进行内存对齐呢？这是为了加快读写速度，把内存占用划分成等长的区块，就可以快速在 Struct 结构体中定位到每个属性的起始地址。

## struct 的复制

> struct 变量可以使用赋值运算符（=），复制给另一个变量，这时会生成一个全新的副本。系统会分配一块新的内存空间，大小与原来的变量相同，把每个属性都复制过去，即原样生成了一份数据

> 总结一下，赋值运算符（=）可以将 struct 结构每个属性的值，一模一样复制一份，拷贝给另一个 struct 变量。这一点跟数组完全不同，使用赋值运算符复制数组，不会复制数据，只会共享地址。

> 另外，C 语言没有提供比较两个自定义数据结构是否相等的方法，无法用比较运算符（比如==和!=）比较两个数据结构是否相等或不等。

## struct 指针

> 如果将 struct 变量传入函数，函数内部得到的是一个原始值的副本。 这时候就需要 struct 指针

```cpp
#include <stdio.h>

struct turtle {
  char* name;
  char* species;
  int age;
};

void happy(struct turtle t) {
  t.age = t.age + 1;
}

int main() {
  struct turtle myTurtle = {"MyTurtle", "sea turtle", 99};
  happy(myTurtle);
  printf("Age is %i\n", myTurtle.age); // 输出 99
  return 0;
}

// struct 指针
void happy(struct turtle* t) {
    (*t).age = (*t).age + 1;
}

happy(&myTurtle);

// (*t).age这样的写法很麻烦。C 语言就引入了一个新的箭头运算符（->），可以从 struct 指针上直接获取属性，大大增强了代码的可读性。

void happy(struct turtle* t) {
  t->age = t->age + 1;
}
```

> 总结一下，对于 struct 变量名，使用点运算符（.）获取属性；对于 struct 变量指针，使用箭头运算符（->）获取属性。以变量 myStruct 为例，假设 ptr 是它的指针，那么下面三种写法是同一回事。

```cpp
// ptr == &myStruct
myStruct.prop == (*ptr).prop == ptr->prop
```

## struct 嵌套

```cpp
struct node {
  int data;
  struct node* next;
};

struct node* head;

// 生成一个三个节点的列表 (11)->(22)->(33)
head = malloc(sizeof(struct node));

head->data = 11;
head->next = malloc(sizeof(struct node));

head->next->data = 22;
head->next->next = malloc(sizeof(struct node));

head->next->next->data = 33;
head->next->next->next = NULL;

// 遍历这个列表
for (struct node *cur = head; cur != NULL; cur = cur->next) {
  printf("%d\n", cur->data);
}
```

## 位字段

> struct 还可以用来定义二进制位组成的数据结构，称为“位字段”（bit field），这对于操作底层的二进制数据非常有用。

```cpp
struct {
  unsigned int ab:1;
  unsigned int cd:1;
  unsigned int ef:1;
  unsigned int gh:1;
} synth;

synth.ab = 0;
synth.cd = 1;
```

## 弹性数组成员

> 很多时候，不能事先确定数组到底有多少个成员。如果声明数组的时候，事先给出一个很大的成员数，就会很浪费空间。C 语言提供了一个解决方法，叫做弹性数组成员（flexible array member）。

```cpp
struct vstring {
  int len;
  char chars[];
};

struct vstring* str = malloc(sizeof(struct vstring) + n * sizeof(char));
str->len = n;
```
