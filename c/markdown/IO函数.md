# I/O 函数

> C 语言的输入输出函数，凡是涉及读写文件，都是属于字节流操作。输入函数从文件获取数据，操作的是输入流；输出函数向文件写入数据，操作的是输出流。

## printf()

## scanf()

> 读取用户的键盘操作, 注意 scanf 传递的不是值, 而是地址, 即将变量的地址指向用户输入的值

> scanf("%d", &i);

### 占位符

- %c：字符。
- %d：整数。
- %f：float 类型浮点数。
- %lf：double 类型浮点数。
- %Lf：long double 类型浮点数。
- %s：字符串。
- %[]：在方括号中指定一组匹配的字符（比如%[0-9]），遇到不在集合之中的字符，匹配将会停止。

### 赋值忽略符

```cpp
scanf("%d%*c%d%*c%d", &year, &month, &day);
```

## sscanf() // stdio.h

> int sscanf(const char* s, const char* format, ...);

> sscanf()函数与 scanf()很类似，不同之处是 sscanf()从字符串里面，而不是从用户输入获取数据

> sscanf()的一个好处是，它的数据来源不是流数据，所以可以反复使用，不像 scanf()的数据来源是流数据，只能读取一次。

> sscanf()的返回值是成功赋值的变量的数量，如果提取失败，返回常量 EOF。

## getchar(), putchar() // stdio.h

### getchar()

> getchar()函数返回用户从键盘输入的一个字符，使用时不带有任何参数。程序运行到这个命令就会暂停，等待用户从键盘输入，等同于使用 scanf()方法读取一个字符

```cpp
// 计算某一行的长度
int len = 0;
while(getchar() != '\n')
  len++;
```

### putchar()

> putchar()函数将它的参数字符输出到屏幕，等同于使用 printf()输出一个字符

```cpp
putchar(ch);
// 等同于
printf("%c", ch);
```

## puts() // stdio.h

> puts()函数用于将参数字符串显示在屏幕（stdout）上，并且自动在字符串末尾添加换行符。

```cpp
puts("Here are some messages:");
puts("Hello World");
```

## gets() // stdio.h

> gets()函数以前用于从stdin读取整行输入，现在已经被废除了