//
// created by linxi on 02/24/2023
//

#include "safe_string.h"

#include "stdio.h"

void safe_memncpy_check()
{
    char dest[12] = "***********";
    char src[12] = "hello world";
    safe_memncpy(dest, 12, src, 10);
    printf("result of memcpy: %s\n", dest);
}

void safe_memnmove_check()
{
    char src[12] = "hello world";
    safe_memnmove(src, 10, src + 1, 10);
    printf("result of memmove: %s\n", src);
}

void safe_memncmp_check()
{
    char cs[12] = "hello world";
    char cd[12] = "hell oworld";
    printf("result of memcmp: %d\n", safe_memncmp(cs, 12, cd, 12, 12));
}

void safe_strcpy_check()
{
    char dest[12] = "***********";
    char src[12] = "hello world";
    safe_strcpy(dest, 12, src, 12);
    printf("result of strcpy: %s\n", dest);
}

void safe_strncpy_check()
{
    char dest[12] = "***********";
    char src[12] = "hello world";
    safe_strncpy(dest, 12, src, 11);
    printf("result of strcpy: %s\n", dest);
}

void safe_strcat_check()
{
    char dest[12] = "**";
    char src[12] = "hello";
    safe_strcat(dest, 12, src, 5);
    printf("result of strcat: %s\n", dest);
}

void safe_strncat_check()
{
    char dest[12] = "**";
    char src[12] = "hello";
    safe_strncat(dest, 8, src, 5);
    printf("result of strcat: %s\n", dest);
}

void safe_strstr_check()
{
    char s1[12] = "hello world";
    char s2[3] = "ll";
    char *result = NULL;
    result = safe_strstr_(s1, 12, s2, 3);
    if (result)
    {
        printf("result of strstr: find target at pos: %d\n", result - s1);
    } else
    {
        printf("result of strstr: failed to find target\n");
    }
}

void safe_strlen_check()
{
    char str[12] = "hello world";
    printf("strlen: %d\n", safe_strlen(str, 12));
}


int main(int argc, char** argv)
{
    safe_memncpy_check();
    safe_memnmove_check();
    safe_memncmp_check();
    safe_strcpy_check();
    safe_strncpy_check();
    safe_strcat_check();
    safe_strncat_check();
    safe_strstr_check();
    safe_strlen_check();
    return 0;
}