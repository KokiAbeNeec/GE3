#pragma once
#include <Windows.h>


// WindosAPI
class WinApp
{
public:
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public:	// メンバ変数
	// 初期化
	void Initialize();
	// 更新
	void Update();
};