#include <DirectXMath.h>
#include "Sprite.h"

using namespace DirectX;
using namespace Microsoft::WRL;


void Sprite::Initialize(SpriteCommon* spriteCommon)
{
	this->spriteCommon = spriteCommon;

    // 頂点データ
    Vertex vertices[] = {
        { {   0.0f, 100.0f, 0.0f},{0.0f, 1.0f}}, // 左下
        { {   0.0f,   0.0f, 0.0f},{0.0f, 0.0f}}, // 左上
        { { 100.0f, 100.0f, 0.0f},{1.0f, 1.0f}}, // 右下
        { { 100.0f,   0.0f, 0.0f},{1.0f, 0.0f}}, // 右上
    };

	// 頂点データ全体のサイズ = 頂点データ一つ分のサイズ * 頂点データの要素数
	UINT sizeVB = static_cast<UINT>(sizeof(vertices[0]) * _countof(vertices));

    // 頂点バッファの設定
    D3D12_HEAP_PROPERTIES heapProp{};   // ヒープ設定
    heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPUへの転送用
    // リソース設定
    D3D12_RESOURCE_DESC resDesc{};
    resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    resDesc.Width = sizeVB; // 頂点データ全体のサイズ
    resDesc.Height = 1;
    resDesc.DepthOrArraySize = 1;
    resDesc.MipLevels = 1;
    resDesc.SampleDesc.Count = 1;
    resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

    // 頂点バッファの生成
    result = spriteCommon->GetDirectXCommon()->GetDevice()->CreateCommittedResource(
        &heapProp, // ヒープ設定
        D3D12_HEAP_FLAG_NONE,
        &resDesc, // リソース設定
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&vertBuff));
    assert(SUCCEEDED(result));

    // GPU上のバッファに対応した仮想メモリ(メインメモリ上)を取得
    Vertex* vertMap = nullptr;
    result = vertBuff->Map(0, nullptr, (void**)&vertMap);
    assert(SUCCEEDED(result));
    // 全頂点に対して
    for (int i = 0; i < _countof(vertices); i++) {
        vertMap[i] = vertices[i];   // 座標をコピー
    }
    // 繋がりを解除
    vertBuff->Unmap(0, nullptr);

    // GPU仮想アドレス
    vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
    // 頂点バッファのサイズ
    vbView.SizeInBytes = sizeVB;
    // 頂点１つ分のデータサイズ
    vbView.StrideInBytes = sizeof(vertices[0]);

    // マテリアル
    {
        // ヒープ設定
        D3D12_HEAP_PROPERTIES cbHeapProp{};
        cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;                   // GPUへの転送用
        // リソース設定
        D3D12_RESOURCE_DESC cbResourceDesc{};
        cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        cbResourceDesc.Width = (sizeof(ConstBufferDataMaterial) + 0xff) & ~0xff;   // 256バイトアラインメント
        cbResourceDesc.Height = 1;
        cbResourceDesc.DepthOrArraySize = 1;
        cbResourceDesc.MipLevels = 1;
        cbResourceDesc.SampleDesc.Count = 1;
        cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        // 定数バッファの生成
        result = spriteCommon->GetDirectXCommon()->GetDevice()->CreateCommittedResource(
            &cbHeapProp, // ヒープ設定
            D3D12_HEAP_FLAG_NONE,
            &cbResourceDesc, // リソース設定
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&constBuffMaterial));
        assert(SUCCEEDED(result));
        // 定数バッファのマッピング
        result = constBuffMaterial->Map(0, nullptr, (void**)&constMapMaterial); // マッピング
        assert(SUCCEEDED(result));
        // 値を書き込むと自動的に転送される
        constMapMaterial->color = color;
    }

    // 行列
    {
        // ヒープ設定
        D3D12_HEAP_PROPERTIES cbHeapProp{};
        cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;                   // GPUへの転送用
        // リソース設定
        D3D12_RESOURCE_DESC cbResourceDesc{};
        cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        cbResourceDesc.Width = (sizeof(ConstBufferDataTransform) + 0xff) & ~0xff;   // 256バイトアラインメント
        cbResourceDesc.Height = 1;
        cbResourceDesc.DepthOrArraySize = 1;
        cbResourceDesc.MipLevels = 1;
        cbResourceDesc.SampleDesc.Count = 1;
        cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        // 定数バッファの生成
        result = spriteCommon->GetDirectXCommon()->GetDevice()->CreateCommittedResource(
            &cbHeapProp, // ヒープ設定
            D3D12_HEAP_FLAG_NONE,
            &cbResourceDesc, // リソース設定
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&constBuffTransform));
        assert(SUCCEEDED(result));
        // 定数バッファのマッピング
        result = constBuffTransform->Map(0, nullptr, (void**)&constMapTransform); // マッピング
        assert(SUCCEEDED(result));

        // ワールド変換行列
        XMMATRIX matWorld;
        matWorld = XMMatrixIdentity();

        rotationZ = 0.f;
        position = { 0.f,0.f,0.f };

        // 回転
        XMMATRIX matRot;
        matRot = XMMatrixIdentity();
        matRot = XMMatrixRotationZ(XMConvertToRadians(rotationZ));
        matWorld *= matRot;

        // 平行
        XMMATRIX matTrans;
        matTrans = XMMatrixTranslation(position.x, position.y, position.z);
        matWorld *= matTrans;

        // 射影変換
        XMMATRIX matProjection = XMMatrixOrthographicOffCenterLH(
            0.f, WinApp::window_width,
            WinApp::window_height, 0.f,
            0.0f, 1.0f
        );

        constMapTransform->mat = matWorld * matProjection;
    }
}

void Sprite::Update()
{
    constMapMaterial->color = color;

    // ワールド変換行列
    XMMATRIX matWorld;
    matWorld = XMMatrixIdentity();

    // 回転
    XMMATRIX matRot;
    matRot = XMMatrixIdentity();
    matRot = XMMatrixRotationZ(XMConvertToRadians(rotationZ));
    matWorld *= matRot;

    // 平行
    XMMATRIX matTrans;
    matTrans = XMMatrixTranslation(position.x, position.y, position.z);
    matWorld *= matTrans;

    // 射影変換
    XMMATRIX matProjection = XMMatrixOrthographicOffCenterLH(
        0.f, WinApp::window_width,
        WinApp::window_height, 0.f,
        0.0f, 1.0f
    );

    constMapTransform->mat = matWorld * matProjection;
}

void Sprite::Draw()
{
    // 頂点バッファビューの設定コマンド
    spriteCommon->GetDirectXCommon()->GetCommandList()->IASetVertexBuffers(0, 1, &vbView);
    // 定数バッファビュー(CBV)の設定コマンド
    spriteCommon->GetDirectXCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffMaterial->GetGPUVirtualAddress());
    spriteCommon->GetDirectXCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(2, constBuffTransform->GetGPUVirtualAddress());
    // 描画コマンド
    spriteCommon->GetDirectXCommon()->GetCommandList()->DrawInstanced(4, 1, 0, 0);
}
