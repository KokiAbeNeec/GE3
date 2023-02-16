#pragma once
#include "SpriteCommon.h"


// �X�v���C�g
class Sprite
{
public: // �����o�֐�
	// ������
	void Initialize(SpriteCommon* spriteCommon);
	// �`��
	void Draw();
private: // �����o�ϐ�
	HRESULT result;
	// ���_�o�b�t�@�̐���
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// SpriteCommon
	SpriteCommon* spriteCommon = nullptr;
};