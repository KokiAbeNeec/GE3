#pragma once
#include <Windows.h>


// WindosAPI
class WinApp
{
public:
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public:	// �����o�ϐ�
	// ������
	void Initialize();
	// �X�V
	void Update();
};