#pragma once
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
	// 頂点シェーダオブジェクト
	ID3DBlob* vsBlob = nullptr;
	// ピクセルシェーダオブジェクト
 	ID3DBlob* psBlob = nullptr;
	// エラーオブジェクト
	ID3DBlob* errorBlob = nullptr;
	// DirectX
	DirectXCommon* dxCommon = nullptr;
};