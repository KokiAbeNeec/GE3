#pragma once
#include <DirectXMath.h>
#include "SpriteCommon.h"


// スプライト
class Sprite
{
public: // 構造体
	// 頂点データ構造体
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;       // xyz座標
		DirectX::XMFLOAT2 uv;        // uv座標
	};
	// 定数バッファ用データ構造体（マテリアル）
	struct ConstBufferDataMaterial {
		DirectX::XMFLOAT4 color; // 色 (RGBA)
	};
	// 定数バッファ用データ構造体（３Ｄ変換行列）
	struct ConstBufferDataTransform {
		DirectX::XMMATRIX mat;   // ３Ｄ変換行列
	};
public: // メンバ関数
	// 初期化
	void Initialize(SpriteCommon* spriteCommon);
	// 更新
	void Update();
	// 描画
	void Draw();
private: // メンバ変数
	HRESULT result;
	// スプライト情報
	float rotationZ;
	DirectX::XMFLOAT3 position;
	// 頂点バッファの生成
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	// 頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffMaterial;
	// 定数バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform;
	DirectX::XMFLOAT4 color = { 1,0,0,0.5f };
	// 定数バッファのマッピング
	ConstBufferDataMaterial* constMapMaterial = nullptr;
	// 定数バッファ
	ConstBufferDataTransform* constMapTransform = nullptr;
	// SpriteCommon
	SpriteCommon* spriteCommon = nullptr;
};