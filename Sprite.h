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
	// 頂点番号
	enum VertexNumber {
		LB,	// 左下
		LT,	// 左上
		RB,	// 右下
		RT,	// 右上
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
	// setter
	void SetPosition(const DirectX::XMFLOAT2& position) { position_ = position; }
	void SetRotation(float& rotationZ) { rotationZ_ = rotationZ; }
	void SetColor(const DirectX::XMFLOAT4& color) { color_ = color; }
	void SetSize(const DirectX::XMFLOAT2& size) { size_ = size; }
	void SetAnchorPoint(const DirectX::XMFLOAT2& anchorPoint) { anchorPoint_ = anchorPoint; }
	void SetIsFlipX(const bool& isFlipX) { isFlipX_ = isFlipX; }
	void SetIsFlipY(const bool& isFlipY) { isFlipY_ = isFlipY; }
	void SetIsInvisible_(const bool& isInvisible) { isInvisible_ = isInvisible; }
	// getter
	const DirectX::XMFLOAT2& GetPosition()const { return position_; }
	const float& GetRotation()const { return rotationZ_; }
	const DirectX::XMFLOAT4& GetColor()const { return color_; }
	const DirectX::XMFLOAT2& GetSize()const { return size_; }
	const DirectX::XMFLOAT2& GetAnchorPoint()const { return anchorPoint_; }
	const bool& GetIsFlipX()const { return isFlipX_; }
	const bool& GetIsFlipY()const { return isFlipY_; }
	const bool& GetIsInvisible_()const { return isInvisible_; }
private: // メンバ変数
	HRESULT result;
	// スプライト情報
	float rotationZ_;
	// 座標
	DirectX::XMFLOAT2 position_{ 0.0f,100.0f };
	// 色
	DirectX::XMFLOAT4 color_ = { 1,1,1,1 };
	// サイズ
	DirectX::XMFLOAT2 size_ = { 100.0f,100.0f };
	// アンカーポイント
	DirectX::XMFLOAT2 anchorPoint_ = { 0.0f,0.0f };
	// 左右フリップ
	bool isFlipX_ = false;
	// 上下フリップ
	bool isFlipY_ = false;
	// 非表示フラグ
	bool isInvisible_ = false;
	DirectX::XMFLOAT4 color = { 1,0,0,0.5f };

	// 頂点データ
	Vertex vertices_[4];
	// 頂点バッファの生成
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	// 頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffMaterial;
	// 定数バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform;
	// 定数バッファのマッピング
	ConstBufferDataMaterial* constMapMaterial = nullptr;
	// 定数バッファ
	ConstBufferDataTransform* constMapTransform = nullptr;
	// SpriteCommon
	SpriteCommon* spriteCommon = nullptr;
};