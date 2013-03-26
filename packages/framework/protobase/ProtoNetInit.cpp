#include "ProtoNetInit.h"

void	ProtoNetInit::startNetMod()
{
	HMODULE hModule = LoadLibraryA("netmod.dll");
	if( !hModule || hModule == INVALID_HANDLE_VALUE )
		return;

	typedef int (CALLBACK*NETMODSTART)();
	NETMODSTART func = (NETMODSTART)GetProcAddress(hModule, "NetModStart");
	if( !func )
		return;

	func();
}

void	ProtoNetInit::stopNetMod()
{
	HMODULE hModule = LoadLibraryA("netmod.dll");
	if( !hModule || hModule == INVALID_HANDLE_VALUE )
		return;

	typedef void (CALLBACK*NETMODSTOP)();
	NETMODSTOP func = (NETMODSTOP)GetProcAddress(hModule, "NetModStop");
	if( !func )
		return;

	func();
}