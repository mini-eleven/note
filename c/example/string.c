#include <string.h>
#include <stdio.h>

void main()
{
    char dest[20];
    char* ps = strcpy(dest, "abcde");
    printf("%s\n", dest);
    printf("%s", ps);
}