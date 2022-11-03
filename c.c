#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
    char str[2] = {"a"};
    char *s = "abc";
    char *s2 = "defg";
    printf("%p-%p-%p\n", str, s, s2);
    printf("%s\n", s);
    return 0;
}
