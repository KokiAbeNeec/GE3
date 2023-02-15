#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <chrono>
#include "WinApp.h"


// DirectX基盤
class DirectXCommon
{
public:
	void Initialize(WinApp* winApp);
	void PreDraw();
	void PostDraw();
private:
	// デバイスの生成
	void INitializeDevice();
	// コマンド関連の初期化
	void INitializeCommand();
	// スワップチェーンの初期化
	void INitializeSwapchain();
	// レンダーターゲットビューの初期化
	void INitializeRenderTargetView();
	// 深度バッファの初期化
	void INitializeDepthBuffer();
	// フェンスの初期化
	void INitializeFence();
	// FPS固定初期化
	void INitializeFixFPS();
	// FPS固定更新
	void UpdateFixFPS();
public:
	// デバイス取得
	ID3D12Device* GetDevice() const { return device.Get(); }
	// コマンドリスト取得
	ID3D12GraphicsCommandList* GetCommandList() const { return commandList.Get(); }
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
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	// バックバッファ
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
	// リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;
	// 深度ビュー用デスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	// フェンス
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;
	// フェンス値
	UINT64 fenceVal = 0;
	// リソースバリアの設定
	D3D12_RESOURCE_BARRIER barrierDesc{};
	// 記録時間(FPS固定用)
	std::chrono::steady_clock::time_point reference_;

	// WindowsAPI
	WinApp* winApp = nullptr;
};