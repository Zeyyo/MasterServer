#pragma once
#include <string.h>

#ifdef SERVERLIBRARY_EXPORTS
#define SERVERLIBRARY_API __declspec(dllexport)
#else
#define SERVERLIBRARY_API __declspec(dllimport)
#endif


extern char rot19c(char c);
extern void rot19(char* buf, const char* in);