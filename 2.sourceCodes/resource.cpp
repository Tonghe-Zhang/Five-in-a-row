#include <Windows.h>
#include "resource.h"
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#define WIN32_LEAN_AND_MEAN


int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow)
{

	WNDCLASSEX winclass;
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC | CS_DBLCLKS;
	//winclass.lpfnWndProc = WndProc; //WndProc还没有定义。
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hinstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = (LPCWSTR)"WINCLASS1";
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	winclass.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(DarkAlbertCorpIcon));	//create an icon.
	winclass.hIconSm = LoadIcon(hinstance, MAKEINTRESOURCE(DarkAlbertCorpIcon)); //this is the icon you can see on the window of this programme.
	return 0;
}

WNDCLASSEX winclass;


#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#pragma comment(lib, "Winmm.lib")    // 引用 Windows Multimedia API
#include "resource.h"     // 注：如果资源 ID 为宏定义，请保留这行


//////////////////////////////////////////////////////////////////
// 提取指定模块中的资源文件
// 参数：
//     strDstFile:     目标文件名。提取的资源将保存在这里；
//     strResType:     资源类型；
//     strResName:     资源名称；
// 返回值：
//     true: 执行成功；
//     false: 执行失败。
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)
{
	// 创建文件
	HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	// 查找资源文件中、加载资源到内存、得到资源大小
	HRSRC    hRes = ::FindResource(NULL, strResName, strResType);
	HGLOBAL    hMem = ::LoadResource(NULL, hRes);
	DWORD    dwSize = ::SizeofResource(NULL, hRes);

	// 写入文件
	DWORD dwWrite = 0; // 返回写入字节
	::WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
	::CloseHandle(hFile);

	return true;
}
