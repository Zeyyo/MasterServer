#include "NEtw_pch.h"
#include "rot19.h"

char rot19c(char c)
{
	char u[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char l[] = "abcdefghijklmnopqrstuvwxyz";
	char* p;

	if ((p = strchr(u, c)) != NULL)
		return u[((p - u) + 19) % 26];
	else if ((p = strchr(l, c)) != NULL)
		return l[((p - l) + 19) % 26];
	else
		return c;
}


void rot19(char* buf, const char* in)
{
	while (*in)
		*buf++ = rot19c(*in++);
	*buf = 0;
}