#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void testArrayAndPointer() {
    char str[2] = {"a"};
    char *s = "abc";
    char *s2 = "defg";
    printf("%p-%p-%p\n", str, s, s2);
    printf("%s\n", s);
}

void arrayParam(int a[]) {
    printf("%p\n", a + 1);
    printf("sizeof a is %lu\n", sizeof(a));
}

void testArray() {
    int a[10];
    int (*p)[10] = &a;
    printf("Array a begin addr=%p\n"
            "The content of Pointer p which points to a=%p\n"
            "p content after +1=%p\n", a, p, p + 1);
    printf("type of a is %lu.\n", sizeof(a));
    arrayParam(a);
}

int main (int argc, char *argv[])
{
    testArray();
}


