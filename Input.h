#pragma once
#include <windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION     0x0800
#include <dinput.h>


class Input
{
public:
	// namespace�ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:	// �����o�֐�
	// ������
	void Initialize(HINSTANCE hInstance, HWND hwnd);

	// �X�V
	void Update();
private: // �����o�ϐ�
	ComPtr<IDirectInputDevice8> keyboard;
};