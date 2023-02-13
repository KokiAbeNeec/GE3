#pragma once
#include <Windows.h>


// WindosAPI
class WinApp
{
public:
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public:	// メンバ関数
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 終了
	void Finalize();
	// getter
	HWND GetHwnd() const { return hwnd; }
	HINSTANCE GetHInstance() const { return w.hInstance; }
public: // 定数
	// ウインドウ横幅
	static const int window_width = 1280;
	// ウインドウ縦幅
	static const int window_height = 720;
private: //	メンバ変数
	// ウインドウハンドル
	HWND hwnd = nullptr;
	// ウィンドウクラスの設定
	WNDCLASSEX w{};
};