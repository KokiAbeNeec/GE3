#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "WinApp.h"


// DirectX基盤
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
	// DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	// DXGIファクトリ
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
	// コマンドアロケータ
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	// コマンドリスト
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	// コマンドキュー
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	// スワップチェーン
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	// // スワップチェーンの設定
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	// デスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;
	// バックバッファ
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
	// リソース生成
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;
	// フェンスの生成
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;

	// WindowsAPI
	WinApp* winApp = nullptr;
};