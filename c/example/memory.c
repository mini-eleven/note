#include <stdio.h>

void *my_memcpy(void *dest, void *source, size_t n)
{
    char *s = source;
    char *d = dest;

    while (n--)
    {
        *d++ = *s++;
    }

    return dest;
}

void main()
{
    char s[] = "Nice to meet you!";
    char t[100];
    my_memcpy(t, s, sizeof(char) * 18);
    printf("%s", t);
}