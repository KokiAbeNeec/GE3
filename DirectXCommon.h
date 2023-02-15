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
	void PreDraw();
	void PostDraw();
private:
	void INitializeDevice();
	void INitializeCommand();
	void INitializeSwapchain();
	void INitializeRenderTargetView();
	void INitializeDepthBuffer();
	void INitializeFence();
public:
	// �f�o�C�X�擾
	ID3D12Device* GetDevice() const { return device.Get(); }
	// �R�}���h���X�g�擾
	ID3D12GraphicsCommandList* GetCommandList() const { return commandList.Get(); }
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
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	// �o�b�N�o�b�t�@
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
	// ���\�[�X
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;
	// �[�x�r���[�p�f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	// �t�F���X
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;
	// �t�F���X�l
	UINT64 fenceVal = 0;
	// ���\�[�X�o���A�̐ݒ�
	D3D12_RESOURCE_BARRIER barrierDesc{};

	// WindowsAPI
	WinApp* winApp = nullptr;
};