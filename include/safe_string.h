//
// created by linxi on 02/24/2023
//

#ifndef SAFE_STRING_H
#define SAFE_STRING_H

#include "string.h"

/**
  * Here list the 22 functions included in string.h
  *
  * 1. void memcpy (void * dst, void * src, size_t n);
  *
  * 2. void memmove (void * dst, void * src, size_t n);
  * 
  * 3. void memset (void * s, int c, size_t n);
  *
  * 4. int memcmp (const void * s1, const void * s2, size_t n);
  * 
  * 5. void memchr (void * s, int c, size_t n);
  *
  * 6. char * strcpy (char * dst, const char * src);
  *
  * 7. char * strncpy (char * dst, const char * src, size_t n);
  * 
  * 8. char * strcat (char * dst, const char *src );
  *
  * 9. char * strncat (char * dst, const char * src, size_t n);
  * 
  * 10. int strcmp (const char * str1, const char * str2);
  *
  * 11. int strncmp (const char * s1, const char * s2, size_t n);
  *
  * 12. int strcoll (const char * s1, const char * s2);
  * 
  * 13. size_t strxfrm (char * dst, const char * src, size_t n);
  *
  * 14. char * strchr (char * s, int c);
  *
  * 15. char * strrchr (char * s, int c);
  *
  * 16. size_t strcspn (const char * s, const char * rej);
  *
  * 17. size_t strspn (const char * s, const char * acc);
  *
  * 18. char * strpbrk (char * s, const char * acc);
  *
  * 19. char * strstr (char * haystack, const char * needle);
  *
  * 20. char * strtok (char * s, const char * delim);
  *
  * 21. size_t strlen (const char * s);
  *
  * 22. char * strerror (int errnum);
  * 
**/

/**
 * UNSAFE: the size of dest is not guaranteed
 * 		   overlapping of dest and src is not checked	
 * 
 * 1. memcpy - Copy one area of memory to another
 * @dest: Where to copy to
 * @src: Where to copy from
 * @count: The size of the area.
 *
 * You should not use this function to access IO space, use memcpy_toio()
 * or memcpy_fromio() instead.
 * 
 * here is the memcpy source code
 *
void *memcpy(void *dest, const void *src, size_t count)
{
	char *tmp = dest;
	const char *s = src;
	while (count--)
		*tmp++ = *s++;
	return dest;
}
 */
void *safe_memncpy(void *dest, const size_t mdstlen, const void *src, size_t count);


/**
 * UNSAFE: the size of dest is not guaranteed
 *
 * 2. memmove - Copy one area of memory to another
 * @dest: Where to copy to
 * @src: Where to copy from
 * @count: The size of the area.
 *
 * Unlike memcpy(), memmove() copes with overlapping areas.
 * 
 * here is the memmove source code
 *
void *memmove(void *dest, const void *src, size_t count)
{
	char *tmp;
	const char *s;
	if (dest <= src) {
		tmp = dest;
		s = src;
		while (count--)
			*tmp++ = *s++;
	} else {
		tmp = dest;
		tmp += count;
		s = src;
		s += count;
		while (count--)
			*--tmp = *--s;
	}
	return dest;
}
 */
void safe_memnmove(void *dest, const size_t mdstlen, const void *src, size_t count);


/**
 * SAFE: count should guarantee the size of s
 * 3. memset - Fill a region of memory with the given value
 * @s: Pointer to the start of the area.
 * @c: The byte to fill the area with
 * @count: The size of the area.
 *
 * Do not use memset() to access IO space, use memset_io() instead.
 *
 * here is the memset source code
 *
void *memset(void *s, int c, size_t count)
{
	char *xs = s;
	while (count--)
		*xs++ = c;
	return s;
}
 */


/**
 * UNSAFE: the size of cs and ct is not checked
 *
 * 4. memcmp - Compare two areas of memory
 * @cs: One area of memory
 * @ct: Another area of memory
 * @count: The size of the area.
 *
 * here is the memcmp source code
 *
#undef memcmp
__visible int memcmp(const void *cs, const void *ct, size_t count)
{
	const unsigned char *su1, *su2;
	int res = 0;
#ifdef CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	if (count >= sizeof(unsigned long)) {
		const unsigned long *u1 = cs;
		const unsigned long *u2 = ct;
		do {
			if (get_unaligned(u1) != get_unaligned(u2))
				break;
			u1++;
			u2++;
			count -= sizeof(unsigned long);
		} while (count >= sizeof(unsigned long));
		cs = u1;
		ct = u2;
	}
#endif
	for (su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
		if ((res = *su1 - *su2) != 0)
			break;
	return res;
}
 */
int safe_memncmp(const void *cs, const size_t mcslen, const void *cd, const size_t mcdlen, size_t count);


/**
 * SAFE: the size of s is guaranteed by n
 *
 * 5. memchr - Find a character in an area of memory.
 * @s: The memory area
 * @c: The byte to search for
 * @n: The size of the area.
 *
 * returns the address of the first occurrence of @c, or %NULL
 * if @c is not found
 *
 * here is the memchr source code
 *
void *memchr(const void *s, int c, size_t n)
{
	const unsigned char *p = s;
	while (n-- != 0) {
        	if ((unsigned char)c == *p++) {
			return (void *)(p - 1);
		}
	}
	return NULL;
}
 */


/**
 * UNSAFE: the size of dest is not guaranteed
 * 
 * 6. strcpy - Copy a %NUL terminated string
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 *
 * here is the strcpy source code
 *
char *strcpy(char *dest, const char *src)
{
	char *tmp = dest;
	while ((*dest++ = *src++) != '\0')
		;
	return tmp;
}
 */

char *safe_strcpy(char *dest, const size_t mdstlen, const char *src, size_t msrclen);


/**
 * UNSAFE: the size of dest is not guaranteed
 *
 * 7. strncpy - Copy a length-limited, C-string
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 * @count: The maximum number of bytes to copy
 *
 * The result is not %NUL-terminated if the source exceeds
 * @count bytes.
 *
 * In the case where the length of @src is less than  that  of
 * count, the remainder of @dest will be padded with %NUL.
 *
 * here is the strncpy source code
 *
char *strncpy(char *dest, const char *src, size_t count)
{
	char *tmp = dest;
	while (count) {
		if ((*tmp = *src) != 0)
			src++;
		tmp++;
		count--;
	}
	return dest;
}
 */
char *safe_strncpy(char *dest, const size_t mdstlen, const char *src, size_t count);

/**
 * UNSAFE: the size of dest is not guaranteed
 *
 * 8. strcat - Append one %NUL-terminated string to another
 * @dest: The string to be appended to
 * @src: The string to append to it
 *
 * here is the strcat source code
 *
char *strcat(char *dest, const char *src)
{
	char *tmp = dest;
	while (*dest)
		dest++;
	while ((*dest++ = *src++) != '\0')
		;
	return tmp;
}
 */
char *safe_strcat(char * dest, const size_t mdstlen, const char *src, const size_t msrclen);




/**
 * UNSAFE: the size of dest is not guaranteed
 *
 * 9. strncat - Append a length-limited, C-string to another
 * @dest: The string to be appended to
 * @src: The string to append to it
 * @count: The maximum numbers of bytes to copy
 *
 * Note that in contrast to strncpy(), strncat() ensures the result is
 * terminated.
 *
 * here is the strnct source code
 *
char *strncat(char *dest, const char *src, size_t count)
{
	char *tmp = dest;
	if (count) {
		while (*dest)
			dest++;
		while ((*dest++ = *src++) != 0) {
			if (--count == 0) {
				*dest = '\0';
				break;
			}
		}
	}
	return tmp;
}
 */
char *safe_strncat(char * dest, const size_t mdstlen, const char *src, const size_t count);


/**
 * SAFE
 * 10. strcmp - Compare two strings
 * @cs: One string
 * @ct: Another string
 *
 * here is the strcmp source code
 *
int strcmp(const char *cs, const char *ct)
{
	unsigned char c1, c2;
	while (1) {
		c1 = *cs++;
		c2 = *ct++;
		if (c1 != c2)
			return c1 < c2 ? -1 : 1;
		if (!c1)
			break;
	}
	return 0;
}
 */


/**
 * SAFE
 * 11. strncmp - Compare two length-limited strings
 * @cs: One string
 * @ct: Another string
 * @count: The maximum number of bytes to compare
 *
 * here is the strncmp source code
 * 
int strncmp(const char *cs, const char *ct, size_t count)
{
	unsigned char c1, c2;
	while (count) {
		c1 = *cs++;
		c2 = *ct++;
		if (c1 != c2)
			return c1 < c2 ? -1 : 1;
		if (!c1)
			break;
		count--;
	}
	return 0;
}
 */

/**
 * SAFE
 * 12. strcoll - Compare two strings
 * according to the manpage, this is equiv in the POSIX/C locale.
 *
 * here is the strcoll source code
 *
int strcoll(const char *s1, const char *s2) {
  return strcmp(s1,s2);
}
 */


/**
 * 13. strxfrm - Transforms the first n characters of the string src into current locale and places them in the string dest.
 *
size_t
strxfrm (STRING_TYPE *dest, const STRING_TYPE *src, size_t n, locale_t l)
{
  locale_data_t l_data;
  struct __locale_data *current = l->__locales[LC_COLLATE];
  l_data.nrules = current->values[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].word;
    //  Handle byte comparison case.  
  if (l_data.nrules == 0)
    {
      size_t srclen = STRLEN (src);
      if (n != 0)
	STPNCPY (dest, src, MIN (srclen + 1, n));
      return srclen;
    }
    //  Handle an empty string, code hereafter relies on strlen (src) > 0.  
  if (*src == L('\0'))
    {
      if (n != 0)
	*dest = L('\0');
      return 0;
    }
    //  Get the locale data.  
  l_data.rulesets = (unsigned char *)
    current->values[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  l_data.table = (int32_t *)
    current->values[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_TABLE,SUFFIX))].string;
  l_data.weights = (USTRING_TYPE *)
    current->values[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_WEIGHT,SUFFIX))].string;
  l_data.extra = (USTRING_TYPE *)
    current->values[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  l_data.indirect = (int32_t *)
    current->values[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_INDIRECT,SUFFIX))].string;
  assert (((uintptr_t) l_data.table) % __alignof__ (l_data.table[0]) == 0);
  assert (((uintptr_t) l_data.weights) % __alignof__ (l_data.weights[0]) == 0);
  assert (((uintptr_t) l_data.extra) % __alignof__ (l_data.extra[0]) == 0);
  assert (((uintptr_t) l_data.indirect) % __alignof__ (l_data.indirect[0]) == 0);
    //  We need the elements of the string as unsigned values since they
    //  are used as indices.  
  const USTRING_TYPE *usrc = (const USTRING_TYPE *) src;
    //  Allocate cache for small strings on the stack and fill it with weight and
    //  rule indices.  If the cache size is not sufficient, continue with the
    //  uncached xfrm version.  
  size_t idxmax = 0;
  const USTRING_TYPE *cur = usrc;
  int32_t *idxarr = alloca (SMALL_STR_SIZE * sizeof (int32_t));
  unsigned char *rulearr = alloca (SMALL_STR_SIZE + 1);
  do
    {
      int32_t tmp = findidx (l_data.table, l_data.indirect, l_data.extra, &cur,
			     -1);
      rulearr[idxmax] = tmp >> 24;
      idxarr[idxmax] = tmp & 0xffffff;
      ++idxmax;
    }
  while (*cur != L('\0') && idxmax < SMALL_STR_SIZE);
    //  This element is only read, the value never used but to determine
    //  another value which then is ignored.
  rulearr[idxmax] = '\0';
//    Do the transformation.
  if (*cur == L('\0'))
    return do_xfrm_cached (dest, n, &l_data, idxmax, idxarr, rulearr);
  else
    return do_xfrm (usrc, dest, n, &l_data);
}
 */


/**
 * SAFE
 * 14. strchr - Find the first occurrence of a character in a string
 * @s: The string to be searched
 * @c: The character to search for
 *
 * Note that the %NUL-terminator is considered part of the string, and can
 * be searched for.
 *
 * here is the source code of strchr
 *
char *strchr(const char *s, int c)
{
	for (; *s != (char)c; ++s)
		if (*s == '\0')
			return NULL;
	return (char *)s;
}
 */


/**
 * SAFE
 * 15. strrchr - Find the last occurrence of a character in a string
 * @s: The string to be searched
 * @c: The character to search for
 *
 * here is the source code of strrchr
 *
char *strrchr(const char *s, int c)
{
	const char *last = NULL;
	do {
		if (*s == (char)c)
			last = s;
	} while (*s++);
	return (char *)last;
}
 */

/**
 * SAFE
 * 16. strcspn - Calculate the length of the initial substring of @s which does not contain letters in @reject
 * @s: The string to be searched
 * @reject: The string to avoid
 *
 * here is the source code of the strcspn
 *
size_t strcspn(const char *s, const char *reject)
{
	const char *p;
	for (p = s; *p != '\0'; ++p) {
		if (strchr(reject, *p))
			break;
	}
	return p - s;
}
 */


/**
 * SAFE
 * 17. strspn - Calculate the length of the initial substring of @s which only contain letters in @accept
 * @s: The string to be searched
 * @accept: The string to search for
 *
 * here is the source code of strspn
 *
size_t strspn(const char *s, const char *accept)
{
	const char *p;
	for (p = s; *p != '\0'; ++p) {
		if (!strchr(accept, *p))
			break;
	}
	return p - s;
}
 */


/**
 * SAFE
 * 18. strpbrk - Find the first occurrence of a set of characters
 * @cs: The string to be searched
 * @ct: The characters to search for
 *
 * here is the source code of strpbrk
 *
char *strpbrk(const char *cs, const char *ct)
{
	const char *sc1, *sc2;
	for (sc1 = cs; *sc1 != '\0'; ++sc1) {
		for (sc2 = ct; *sc2 != '\0'; ++sc2) {
			if (*sc1 == *sc2)
				return (char *)sc1;
		}
	}
	return NULL;
}
 */

/**
 * UNSAFE: use unsafe function memcmp
 *
 * 19. strstr - Find the first substring in a %NUL terminated string
 * @s1: The string to be searched
 * @s2: The string to search for
 *
 * here is the source code of strstr
 *
char *strstr(const char *s1, const char *s2)
{
	size_t l1, l2;
	l2 = strlen(s2);
	if (!l2)
		return (char *)s1;
	l1 = strlen(s1);
	while (l1 >= l2) {
		l1--;
		if (!memcmp(s1, s2, l2))
			return (char *)s1;
		s1++;
	}
	return NULL;
}
 */
char *safe_strstr_(const char *s1, const size_t mlens1, const char *s2, const size_t mlens2);


/**
 * 20. strtok - Finds the first occurrence of the entire string needle (not including the terminating null character) which appears in the string haystack.
 *
 * here is the source code of strtok
 *
char* __strtok_r(char* s, const char* delim, char** last)
{
	char *spanp, *tok;
	int c, sc;

	if(s == NULL && (s = *last) == NULL)
		return (NULL);


//    Skip (span) leading delimiters (s += strspn(s, delim), sort of).

cont:
	c = *s++;
	for(spanp = (char*)delim; (sc = *spanp++) != 0;)
	{
		if(c == sc)
			goto cont;
	}

	if(c == 0)
	{ // no non-delimiter characters 
		*last = NULL;
		return (NULL);
	}
	tok = s - 1;

	// 
	//  Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
	//  Note that delim must have one NUL; we stop if we see that, too.
	// 
	for(;;)
	{
		c = *s++;
		spanp = (char*)delim;
		do
		{
			if((sc = *spanp++) == c)
			{
				if(c == 0)
					s = NULL;
				else
					s[-1] = '\0';
				*last = s;
				return (tok);
			}
		} while(sc != 0);
	}
}

char* strtok(char* s, const char* delim)
{
	static char* last;

	return (__strtok_r(s, delim, &last));
}
 */

/**
 * UNSAFE: the size of s is not guaranteed
 * 
 * 21. strlen - Find the length of a string
 * @s: The string to be sized
 *
 * here is the source code of strlen
 *
size_t strlen(const char *s)
{
	const char *sc;
	for (sc = s; *sc != '\0'; ++sc)

	return sc - s;
}
 */

size_t safe_strlen(const char *s, const size_t mlen);
size_t safe_strnlen(const char *s, const size_t n);


/**
 * 22. strerror - Searches an internal array for the error number errnum and returns a pointer to an error message string.
 *
char *
strerror (int errnoval)
{
  const char *msg;
  static char buf[32];

#ifndef HAVE_SYS_ERRLIST

  if (error_names == NULL)
    {
      init_error_tables ();
    }

#endif

  if ((errnoval < 0) || (errnoval >= sys_nerr))
    {
#ifdef EVMSERR
      if (errnoval == evmserr.value)
	msg = evmserr.msg;
      else
#endif
      // Out of range, just return NULL
      msg = NULL;
    }
  else if ((sys_errlist == NULL) || (sys_errlist[errnoval] == NULL))
    {
      // In range, but no sys_errlist or no entry at this index. 
      sprintf (buf, "Error %d", errnoval);
      msg = buf;
    }
  else
    {
      // In range, and a valid message.  Just return the message. 
      msg = (char *) sys_errlist[errnoval];
    }
  
  return (msg);
}
 */




#endif