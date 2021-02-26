

#include <graphics.h>
#include "resource.h"
#include <Windows.h>
int main()
{
	HDC
	HMODULE hExe = GetModuleHandle(0);
	HRSRC hRes = FindResource(hExe, MAKEINTRESOURCE(101), TEXT("PNG"));
	HGLOBAL hgRes = LoadResource(hExe, hRes);
	//然后拿bai到指向资源数du据zhi的指针和资源数据的大小
		DWORD nResSize = SizeofResource(hExe, hRes);
	LPVOID pRes = LockResource(hgRes);

	
}