#pragma once
#include <io.h>
#include <stdio.h>
#include <tchar.h>
#include <metahost.h>
#include <windows.h>
#pragma comment(lib, "MSCorEE.lib")
#import "mscorlib.tlb" raw_interfaces_only				\
    high_property_prefixes("_get","_put","_putref")		\
    rename("ReportEvent", "InteropServices_ReportEvent")
//#define DEBUGTRACE 1
#ifdef DEBUGTRACE
#define dprintf(...) real_dprintf(__VA_ARGS__)
#else
#define dprintf(...) do{}while(0);
#endif

using namespace mscorlib;

VOID Execute(LPVOID lpPayload);
BOOL FindVersion(void * assembly, int length);
BOOL BypassAmsi();
VOID PatchAmsi();


static _inline void real_dprintf(char* format, ...)
{
	va_list args;
	char buffer[1024];
	size_t len;
	_snprintf_s(buffer, sizeof(buffer), sizeof(buffer) - 1, "[%x] ", GetCurrentThreadId());
	len = strlen(buffer);
	va_start(args, format);
	vsnprintf_s(buffer + len, sizeof(buffer) - len, sizeof(buffer) - len - 3, format, args);
	strcat_s(buffer, sizeof(buffer), "\r\n");
	OutputDebugStringA(buffer);
	va_end(args);
}