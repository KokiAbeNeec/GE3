#pragma once
#include <DirectXMath.h>
#include <array>
#include <string>
#include "DirectXCommon.h"


// �X�v���C�g���ʕ�
class SpriteCommon
{
public: // �����o�֐�
	// ������
	void Initialize(DirectXCommon* directXCommon);
	/// <summary>
	/// �`��O����
	/// </summary>
	void PreDraw();
	/// <summary>
	/// �`��㏈��
	/// </summary>
	void PostDraw();
	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <param name="index">�e�N�X�`���ԍ�</param>
	void LoadTexture(uint32_t index, const std::string& fileName);
	/// <summary>
	/// �`��e�N�X�`���R�}���h�̔��s
	/// </summary>
	/// <param name="index">�e�N�X�`���ԍ�</param>
	void SetTextureCommands(uint32_t index);
	// getter
	DirectXCommon* GetDirectXCommon() const { return dxCommon; }
	ID3D12Resource* GetTextureBuffer(uint32_t index)const { return texBuff[index].Get(); }
private: // �ÓI�����o�ϐ�
	// SRV�̍ő��
	static const size_t kMaxSRVCount = 2056;
	// �f�t�H���g�e�N�X�`���i�[�f�B���N�g��
	static std::string kDefaultTextureDirectoryPath;
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
	// �e�N�X�`���o�b�t�@
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, kMaxSRVCount> texBuff;
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