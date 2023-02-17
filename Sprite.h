#pragma once
#include <DirectXMath.h>
#include "SpriteCommon.h"


// �X�v���C�g
class Sprite
{
public: // �\����
	// ���_�f�[�^�\����
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;       // xyz���W
		DirectX::XMFLOAT2 uv;        // uv���W
	};
	// �萔�o�b�t�@�p�f�[�^�\���́i�}�e���A���j
	struct ConstBufferDataMaterial {
		DirectX::XMFLOAT4 color; // �F (RGBA)
	};
	// �萔�o�b�t�@�p�f�[�^�\���́i�R�c�ϊ��s��j
	struct ConstBufferDataTransform {
		DirectX::XMMATRIX mat;   // �R�c�ϊ��s��
	};
public: // �����o�֐�
	// ������
	void Initialize(SpriteCommon* spriteCommon);
	// �X�V
	void Update();
	// �`��
	void Draw();
private: // �����o�ϐ�
	HRESULT result;
	// �X�v���C�g���
	float rotationZ;
	DirectX::XMFLOAT3 position;
	// ���_�o�b�t�@�̐���
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// ���\�[�X
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffMaterial;
	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform;
	DirectX::XMFLOAT4 color = { 1,0,0,0.5f };
	// �萔�o�b�t�@�̃}�b�s���O
	ConstBufferDataMaterial* constMapMaterial = nullptr;
	// �萔�o�b�t�@
	ConstBufferDataTransform* constMapTransform = nullptr;
	// SpriteCommon
	SpriteCommon* spriteCommon = nullptr;
};