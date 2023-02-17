#pragma once
#include <DirectXMath.h>
#include "DirectXCommon.h"


// スプライト共通部
class SpriteCommon
{
public: // メンバ関数
	// 初期化
	void Initialize(DirectXCommon* directXCommon);
	// 描画前処理
	void PreDraw();
	// getter
	DirectXCommon* GetDirectXCommon() const { return dxCommon; }
private: // メンバ変数
	HRESULT result;
	// グラフィックスパイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
	// ルートシグネチャ
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	// パイプランステート
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	// 画像イメージデータ配列
	DirectX::XMFLOAT4* imageData;
	// テクスチャバッファの生成
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;
	// 設定を元にSRV用デスクリプタヒープを生成
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;
	// 頂点シェーダオブジェクト
	ID3DBlob* vsBlob = nullptr;
	// ピクセルシェーダオブジェクト
 	ID3DBlob* psBlob = nullptr;
	// エラーオブジェクト
	ID3DBlob* errorBlob = nullptr;
	// DirectX
	DirectXCommon* dxCommon = nullptr;
};