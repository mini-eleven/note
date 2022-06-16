#include <stdio.h>
#include <stdarg.h>

int sum(int a, int b)
{
    return a + b;
}

int (*sum_ptr)(int, int) = &sum;

double average(int i, ...)
{
    double total = 0;
    va_list ap;
    va_start(ap, i);
    for (int j = 1; j <= i; ++j)
    {
        total += va_arg(ap, double);
    }
    va_end(ap);
    return total / i;
}

void main()
{
    int result = average(1, 5);
    printf("result: %d", result);
}