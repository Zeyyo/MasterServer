#include "pch.h"

template<class sin_addr>
char* GetIP(sin_addr&& addr)
{
	char host[NI_MAXHOST];
	ZeroMemory(host, NI_MAXHOST);
	inet_ntop(AF_INET, &addr, host, NI_MAXHOST);

	return host;
}