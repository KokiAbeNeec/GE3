#pragma once
#include <DirectXMath.h>
#include "DirectXCommon.h"


// �X�v���C�g���ʕ�
class SpriteCommon
{
public: // �����o�֐�
	// ������
	void Initialize(DirectXCommon* directXCommon);
	// �`��O����
	void PreDraw();
	// getter
	DirectXCommon* GetDirectXCommon() const { return dxCommon; }
private: // �����o�ϐ�
	HRESULT result;
	// �O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
	// ���[�g�V�O�l�`��
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	// �p�C�v�����X�e�[�g
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	// �摜�C���[�W�f�[�^�z��
	DirectX::XMFLOAT4* imageData;
	// �e�N�X�`���o�b�t�@�̐���
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;
	// �ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;
	// ���_�V�F�[�_�I�u�W�F�N�g
	ID3DBlob* vsBlob = nullptr;
	// �s�N�Z���V�F�[�_�I�u�W�F�N�g
 	ID3DBlob* psBlob = nullptr;
	// �G���[�I�u�W�F�N�g
	ID3DBlob* errorBlob = nullptr;
	// DirectX
	DirectXCommon* dxCommon = nullptr;
};