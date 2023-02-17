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
	// ���_�ԍ�
	enum VertexNumber {
		LB,	// ����
		LT,	// ����
		RB,	// �E��
		RT,	// �E��
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
	// setter
	void SetPosition(const DirectX::XMFLOAT2& position) { position_ = position; }
	void SetRotation(float& rotationZ) { rotationZ_ = rotationZ; }
	void SetColor(const DirectX::XMFLOAT4& color) { color_ = color; }
	void SetSize(const DirectX::XMFLOAT2& size) { size_ = size; }
	void SetAnchorPoint(const DirectX::XMFLOAT2& anchorPoint) { anchorPoint_ = anchorPoint; }
	void SetIsFlipX(const bool& isFlipX) { isFlipX_ = isFlipX; }
	void SetIsFlipY(const bool& isFlipY) { isFlipY_ = isFlipY; }
	void SetIsInvisible_(const bool& isInvisible) { isInvisible_ = isInvisible; }
	// getter
	const DirectX::XMFLOAT2& GetPosition()const { return position_; }
	const float& GetRotation()const { return rotationZ_; }
	const DirectX::XMFLOAT4& GetColor()const { return color_; }
	const DirectX::XMFLOAT2& GetSize()const { return size_; }
	const DirectX::XMFLOAT2& GetAnchorPoint()const { return anchorPoint_; }
	const bool& GetIsFlipX()const { return isFlipX_; }
	const bool& GetIsFlipY()const { return isFlipY_; }
	const bool& GetIsInvisible_()const { return isInvisible_; }
private: // �����o�ϐ�
	HRESULT result;
	// �X�v���C�g���
	float rotationZ_;
	// ���W
	DirectX::XMFLOAT2 position_{ 0.0f,100.0f };
	// �F
	DirectX::XMFLOAT4 color_ = { 1,1,1,1 };
	// �T�C�Y
	DirectX::XMFLOAT2 size_ = { 100.0f,100.0f };
	// �A���J�[�|�C���g
	DirectX::XMFLOAT2 anchorPoint_ = { 0.0f,0.0f };
	// ���E�t���b�v
	bool isFlipX_ = false;
	// �㉺�t���b�v
	bool isFlipY_ = false;
	// ��\���t���O
	bool isInvisible_ = false;
	DirectX::XMFLOAT4 color = { 1,0,0,0.5f };

	// ���_�f�[�^
	Vertex vertices_[4];
	// ���_�o�b�t�@�̐���
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// ���\�[�X
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffMaterial;
	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform;
	// �萔�o�b�t�@�̃}�b�s���O
	ConstBufferDataMaterial* constMapMaterial = nullptr;
	// �萔�o�b�t�@
	ConstBufferDataTransform* constMapTransform = nullptr;
	// SpriteCommon
	SpriteCommon* spriteCommon = nullptr;
};