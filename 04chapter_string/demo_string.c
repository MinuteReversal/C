#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char *s1 = "hello world!";
    char s2[10];
    char s3[] = "how are you";
    memcpy(&s2, s1, 3);
    printf("%s\n", s2);
    return 0;
}