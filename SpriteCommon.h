#pragma once
#include <DirectXMath.h>
#include <array>
#include <string>
#include "DirectXCommon.h"


// スプライト共通部
class SpriteCommon
{
public: // メンバ関数
	// 初期化
	void Initialize(DirectXCommon* directXCommon);
	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();
	/// <summary>
	/// 描画後処理
	/// </summary>
	void PostDraw();
	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <param name="index">テクスチャ番号</param>
	void LoadTexture(uint32_t index, const std::string& fileName);
	/// <summary>
	/// 描画テクスチャコマンドの発行
	/// </summary>
	/// <param name="index">テクスチャ番号</param>
	void SetTextureCommands(uint32_t index);
	// getter
	DirectXCommon* GetDirectXCommon() const { return dxCommon; }
	ID3D12Resource* GetTextureBuffer(uint32_t index)const { return texBuff[index].Get(); }
private: // 静的メンバ変数
	// SRVの最大個数
	static const size_t kMaxSRVCount = 2056;
	// デフォルトテクスチャ格納ディレクトリ
	static std::string kDefaultTextureDirectoryPath;
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
	// テクスチャバッファ
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, kMaxSRVCount> texBuff;
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