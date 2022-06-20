# Union 结构

> C 语言提供了 Union 结构，用来自定义可以灵活变更的数据结构。它内部可以包含各种属性，但同一时间只能有一个属性，因为所有属性都保存在同一个内存地址，后面写入的属性会覆盖前面的属性。这样做的最大好处是节省空间。

```cpp
union quantity {
  short count;
  float weight;
  float volume;
};

// 写法一
union quantity q;
q.count = 4;

// 写法二
union quantity q = {.count=4};

// 写法三
union quantity q = {4};

// 执行完上面的代码以后，q.count可以取到值，另外两个属性取不到值。
printf("count is %i\n", q.count); // count is 4
printf("weight is %f\n", q.weight); // 未定义行为

// 如果要让q.weight属性可以取到值，就要先为它赋值。 除了这一点，Union 结构的其他用法与 Struct 结构，基本上是一致的。
q.weight = 0.5;
printf("weight is %f\n", q.weight); // weight is 0.5
```
