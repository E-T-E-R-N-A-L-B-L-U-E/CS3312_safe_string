//
// created by linxi on 02/24/2023
//

#include "safe_string.h"

#include "assert.h"

/**
 * input variables:
 * @dest: the target where we copy the memory
 * @mdstlen: the maximum length of dest
 * @src: where we copy the memory from
 * @count: copy ${count} byte from src to dest
 */
void *safe_memncpy(void *dest, const size_t mdstlen, const void *src, size_t count)
{
    // check is mdstlen and count is valid
    assert(mdstlen != 0 && count != 0);

    // check if dest is capable
    assert(mdstlen >= count);        // the last byte of dest must be '\0'
    
    // check overlapping
    assert(!((dest <= src && dest + mdstlen > src) || (src <= dest && src + count > dest)));

    memcpy(dest, src, count);
}


/**
 * input variables:
 * @dest: the target where we copy the memory
 * @mdstlen: the maximum length of dest
 * @src: where we copy the memory from
 * @count: copy ${count} byte from src to dest
 */
void safe_memnmove(void *dest, const size_t mdstlen, const void *src, size_t count)
{
    // check is mdstlen and count is valid
    assert(mdstlen != 0 && count != 0);

    // check if dest is capable
    assert(mdstlen >= count);        // the last byte of dest must be '\0'
    
    memmove(dest, src, count);
}


/**
 * input variables:
 * @cs: one area of memory
 * @mcslen: the maximum length of cs
 * @cd: another area of memory
 * @mcdlen: the maximum length of cd
 * @count: the bytes to compare
 */
int safe_memncmp(const void *cs, const size_t mcslen, const void *cd, const size_t mcdlen, size_t count)
{
    if (mcslen == 0 && mcdlen == 0)
        return 0;
    
    if (mcslen == 0)
        return -1;
    else if (mcdlen == 0)
        return 1;
    
    assert((mcslen >= count) && (mcdlen >= count));

    return memcmp(cs, cd, count);
}


/**
 * input variables:
 * @dest: the target where we copy the memory
 * @mdstlen: the maximum length of dest
 * @src: where we copy the memory from
 * @msrclen: the maximum length of src
 */
char *safe_strcpy(char *dest, const size_t mdstlen, const char *src, size_t msrclen)
{
    char *tmp_dest = dest;
    const char *tmp_src = src;
    size_t count = 0;

    // check is mdstlen and msrclen is valid
    assert(mdstlen != 0 && msrclen != 0);

    count = safe_strnlen(src, msrclen);
    
    safe_strncpy(dest, mdstlen, src, count);

    return tmp_dest;
}


/**
 * input variables:
 * @dest: the target where we copy the memory
 * @mdstlen: the maximum length of dest
 * @src: where we copy the memory from
 * @count: the count of char to copy
 */
char *safe_strncpy(char *dest, const size_t mdstlen, const char *src, size_t count)
{
    // check is mdstlen and msrclen is valid
    assert(mdstlen != 0 && count != 0);

    // check if dest is capable
    assert(mdstlen > count);        // the last byte of dest must be '\0'
    
    // check overlapping
    assert(!((dest <= src && dest + mdstlen > src) || (src <= dest && src + count >= dest)));

    strncpy(dest, src, count);
    *(dest + count) = '\0';
    
    return dest;
}


/**
 * input variables:
 * @dest: the target where we concat the string
 * @mdstlen: the maximum length of dest
 * @src: where we copy the string from
 * @msrclen: the maximum length of src
 */
char *safe_strcat(char * dest, const size_t mdstlen, const char *src, const size_t msrclen)
{
    size_t count;

    // check is mdstlen and msrclen is valid
    assert(mdstlen != 0 && msrclen != 0);

    count = safe_strnlen(src, msrclen);

    safe_strncat(dest, mdstlen, src, count);
}


/**
 * input variables:
 * @dest: the target where we concat the string
 * @mdstlen: the maximum length of dest
 * @src: where we copy the string from
 * @msrclen: the concat size
 */
char *safe_strncat(char * dest, const size_t mdstlen, const char *src, const size_t count)
{
    size_t dest_base_len, src_base_len;

    // check if mdstlen and count is valid
    assert(mdstlen != 0 && count != 0);

    dest_base_len = safe_strnlen(dest, mdstlen);

    // check if dest is capable
    assert(dest_base_len + count < mdstlen);

    strncat(dest, src, count);
}


/**
 * input variables:
 * @s1: the string to be searched
 * @mlens1: the maximum length of s1
 * @s2: the string to search for
 * @mlens2: the maximum length of s2
 */
char *safe_strstr_(const char *s1, const size_t mlens1, const char *s2, const size_t mlens2)
{
	size_t l1, l2;
	l2 = safe_strnlen(s2, mlens2);
	if (!l2)
		return (char *)s1;
	l1 = safe_strnlen(s1, mlens1);
	while (l1 >= l2) {
		l1--;
		if (!safe_memncmp(s1, mlens1, s2, mlens2, l2))
			return (char *)s1;
		s1++;
	}
	return NULL;
}


/**
 * input variables: 
 * @s: the string which we need to calculate the length
 * @mlen: the maximum length of s
 * 
 * result:
 * size_t: the length of s
 */
size_t safe_strlen(const char *s, const size_t mlen)
{
    size_t len = 0;
    const char *sc;

    // check if mlen is valid
    assert(mlen > 0);

    for (sc = s; *sc != '\0' && len < mlen; ++sc, ++len);
        // do nothing
    assert(len < mlen);     // the last char of string s must be '\0'
    return len;
}



/**
 * input variables: 
 * @s: the string which we need to calculate the length
 * @n: if the length of s if greater than n, function will return n
 * 
 * result:
 * size_t: the length of s
 */
size_t safe_strnlen(const char *s, const size_t n)
{
    size_t len = 0;
    const char *sc;

    // check if n is valid
    assert(n > 0);

    for (sc = s; *sc != '\0' && len < n; ++sc, ++len);
        // do nothing

    if (len >= n)
        len = len - 1;
    return len;
}