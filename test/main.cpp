

#include <graphics.h>
#include "resource.h"
#include <Windows.h>
int main()
{
	HDC
	HMODULE hExe = GetModuleHandle(0);
	HRSRC hRes = FindResource(hExe, MAKEINTRESOURCE(101), TEXT("PNG"));
	HGLOBAL hgRes = LoadResource(hExe, hRes);
	//Ȼ����bai��ָ����Դ��du��zhi��ָ�����Դ���ݵĴ�С
		DWORD nResSize = SizeofResource(hExe, hRes);
	LPVOID pRes = LockResource(hgRes);

	
}