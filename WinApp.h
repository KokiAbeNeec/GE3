#pragma once
#include <Windows.h>


// WindosAPI
class WinApp
{
public:
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public:	// ƒƒ“ƒo•Ï”
	// ‰Šú‰»
	void Initialize();
	// XV
	void Update();
};