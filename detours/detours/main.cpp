// detours.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Detours/src/detours.h"
static int (__cdecl * oldsystem)(_In_opt_z_ char const*_Command)=system;
static int (__stdcall *oldMessageBoxW)(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCWSTR lpText,
	_In_opt_ LPCWSTR lpCaption,
	_In_ UINT uType) = MessageBoxW;
int WINAPI MyMessageBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
{
	/*DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&g_pOldMessageBoxW, MyMessageBoxW);
	LONG ret = DetourTransactionCommit();*/
	//((PfuncMessageBoxW)g_pOldMessageBoxW)(hWnd, L"W Hook This!", L"W My hook", uType);
	printf("hook\n"); 
	return oldMessageBoxW(hWnd, lpText, lpCaption, uType);
}
int newsystemA(char * _Command)
{
	char *p = strstr(_Command,"tasklist");
	if (p == NULL)
	{
		oldsystem(_Command);
	}
	else
	{
		printf("%s", _Command); //�ҵ��ˣ���ִֹ�� 
		return 0;
	}
	return 0;
}
void Hook()
{

	DetourRestoreAfterWith();//�ָ�ԭ��״̬,
	DetourTransactionBegin();//���ؿ�ʼ
	DetourUpdateThread(GetCurrentThread());//ˢ�µ�ǰ�߳�
										   //�������������ε���DetourAttach������HOOK�������

	DetourAttach((void **)&oldsystem, newsystemA);//ʵ�ֺ�������
	DetourAttach((void **)&oldMessageBoxW, MyMessageBoxW);//ʵ�ֺ�������

	DetourTransactionCommit();//������Ч

}
void main()
{
 
	Hook();
	system("calc");
	MessageBox(NULL, L"2222!", L"2222", NULL);
	system("tasklist");
	//UnHook(); 
	getchar();
}
//typedef int (WINAPI *PfuncMessageBoxA)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
//typedef int (WINAPI *PfuncMessageBoxW)(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType);
//PVOID g_pOldMessageBoxW = NULL;
//PVOID g_pOldMessageBoxA = NULL;
//////////////
//int WINAPI MyMessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
//{
//	 ((PfuncMessageBoxA)g_pOldMessageBoxA)(hWnd, "Hook This!", "My hook", uType);
//	return MessageBoxA(hWnd, lpText, lpCaption, uType);
//}
//
//////////////
//int WINAPI MyMessageBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
//{
//	/*DetourTransactionBegin();
//	DetourUpdateThread(GetCurrentThread());
//	DetourDetach(&g_pOldMessageBoxW, MyMessageBoxW);
//	LONG ret = DetourTransactionCommit();*/
//	  //((PfuncMessageBoxW)g_pOldMessageBoxW)(hWnd, L"W Hook This!", L"W My hook", uType);
//	  printf("hook\n");
//	  return MessageBoxW(hWnd, lpText, lpCaption, uType);
//}
//BOOL APIENTRY InstallHook();
//int main()
//{
//	InstallHook();
//	MessageBox(NULL, L"2222!", L"2222", NULL);
//	getchar();
//    return 0;
//}
//////////////
//BOOL APIENTRY InstallHook()
//{
//	DetourTransactionBegin();
//	DetourUpdateThread(GetCurrentThread());
//	g_pOldMessageBoxA = DetourFindFunction("User32.dll", "MessageBoxA");
//	g_pOldMessageBoxW = DetourFindFunction("User32.dll", "MessageBoxW");
//	DetourAttach(&g_pOldMessageBoxA, MyMessageBoxA);
//	DetourAttach(&g_pOldMessageBoxW, MyMessageBoxW);
//	LONG ret = DetourTransactionCommit();
//	return ret == NO_ERROR;
//}
//
//////////////
//BOOL APIENTRY UnInstallHook()
//{
//	DetourTransactionBegin();
//	DetourUpdateThread(GetCurrentThread());
//	DetourDetach(&g_pOldMessageBoxA, MyMessageBoxA);
//	DetourDetach(&g_pOldMessageBoxW, MyMessageBoxW);
//	LONG ret = DetourTransactionCommit();
//	return ret == NO_ERROR;
//}
//
