#pragma once
#include "SpriteCommon.h"


// スプライト
class Sprite
{
public: // メンバ関数
	// 初期化
	void Initialize(SpriteCommon* spriteCommon);
	// 描画
	void Draw();
private: // メンバ変数
	HRESULT result;
	// 頂点バッファの生成
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	// 頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// SpriteCommon
	SpriteCommon* spriteCommon = nullptr;
};