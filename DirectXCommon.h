#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "WinApp.h"


// DirectX���
class DirectXCommon
{
public:
	void Initialize(WinApp* winApp);
private:
	void INitializeDevice();
	void INitializeCommand();
	void INitializeSwapchain();
	void INitializeRenderTargetView();
	void INitializeDepthBuffer();
	void INitializeFence();
private:
	// DirectX12�f�o�C�X
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	// DXGI�t�@�N�g��
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
	// �R�}���h�A���P�[�^
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	// �R�}���h���X�g
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	// �R�}���h�L���[
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	// �X���b�v�`�F�[��
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	// // �X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	// �f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;
	// �o�b�N�o�b�t�@
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
	// ���\�[�X����
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;
	// �t�F���X�̐���
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;

	// WindowsAPI
	WinApp* winApp = nullptr;
};