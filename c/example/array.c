#include <stdio.h>
#include <string.h>

int main()
{
    int a[5] = {11, 22, 33, 44, 55};
    int b[5];

    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", *(a + i));
    }

    memcpy(b, a, sizeof(a));
    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", *(b + i));
    }

    return 0;
}