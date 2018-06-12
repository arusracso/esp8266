#include "str.h"

unsigned strlen(const char *s) {
	unsigned i;
	for (i = 0; s[i] != '\0'; i++) ;
	return i;
}

int compare(const char *p, const char *q) {
	while (*p && *q) {
		if (*p != *q) return 0;
		
		p++;
		q++;
	}
	return *q == '\0';
}

const char *strstrr(const char *p, const char *q) {
	while (*p != '\0') {
		if ((*p == *q) && compare(p, q))
			return p;
		p++;
	}
	return 0;
}

int strncmp(const char *s1, const char *s2, unsigned n) {
	if (n == 0) return 0;
	
	do {
		if (*s1 != *s2++) {
			return (*(unsigned char *)s1 - *(unsigned char *)--s2);
		}
		if (*s1++ == 0) {
			break;
		}
	} while (--n != 0);
	return 0;
}

char *strstr(const char *s, const char *find) {
	char c, sc;
	unsigned len;
	if ((c = *find++) != 0) {
		len = strlen(find);
		do {
			do {
				if ((sc = *s++) == 0)
					return 0;
			} while (sc != c);		
		} while (strncmp(s, find, len) != 0);
		s--;
	}
	return ((char *)s);
}
