#pragma once
#include <Windows.h>


// WindosAPI
class WinApp
{
public:
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public:	// �����o�֐�
	// ������
	void Initialize();
	// �X�V
	void Update();
	// �I��
	void Finalize();
	// getter
	HWND GetHwnd() const { return hwnd; }
	HINSTANCE GetHInstance() const { return w.hInstance; }
public: // �萔
	// �E�C���h�E����
	static const int window_width = 1280;
	// �E�C���h�E�c��
	static const int window_height = 720;
private: //	�����o�ϐ�
	// �E�C���h�E�n���h��
	HWND hwnd = nullptr;
	// �E�B���h�E�N���X�̐ݒ�
	WNDCLASSEX w{};
};