#include <DirectXMath.h>
#include "Sprite.h"

using namespace DirectX;
using namespace Microsoft::WRL;


void Sprite::Initialize(SpriteCommon* spriteCommon, uint32_t textureIndex)
{
	this->spriteCommon = spriteCommon;

    // �e�N�X�`���T�C�Y���C���[�W�ɍ��킹��
    if (textureIndex != UINT32_MAX) {
        textureIndex_ = textureIndex;
        AdjustTextureSize();
        // �e�N�X�`���T�C�Y���X�v���C�g�̃T�C�Y�ɓK�p
        size_ = textureSize_;
    }

    ID3D12Resource* textBuffer = spriteCommon->GetTextureBuffer(textureIndex_);

    if (textBuffer) {
        // �e�N�X�`�����擾
        D3D12_RESOURCE_DESC resDesc = textBuffer->GetDesc();

        // �A���J�[�|�C���g
        float tex_left = textureLeftTop_.x / resDesc.Width;
        float tex_right = (textureLeftTop_.x + textureSize_.x) / resDesc.Width;
        float tex_top = textureLeftTop_.y / resDesc.Height;
        float tex_bottom = (textureLeftTop_.y + textureSize_.y) / resDesc.Height;
        // ���_�f�[�^uv
        vertices_[LB].uv = { tex_left,tex_bottom }; // ����
        vertices_[LT].uv = { tex_left,tex_top }; // ����
        vertices_[RB].uv = { tex_right,tex_bottom }; // �E��
        vertices_[RT].uv = { tex_right,tex_top }; // �E��
    }

    // �A���J�[�|�C���g
    float left = (0.0f - anchorPoint_.x) * size_.x;
    float right = (1.0f - anchorPoint_.x) * size_.x;
    float top = (0.0f - anchorPoint_.y) * size_.y;
    float bottom = (1.0f - anchorPoint_.y) * size_.y;
    // ���E���]
    if (isFlipX_) {
        left = -left;
        right = -right;
    }
    // �㉺���]
    if (isFlipY_) {
        top = -top;
        bottom = -bottom;
    }
    // ���_�f�[�^
    vertices_[LB] = { { left,  bottom, 0.0f },{0.0f,1.0f} }; // ����
    vertices_[LT] = { { left, top,     0.0f },{0.0f,0.0f} }; // ����
    vertices_[RB] = { { right, bottom, 0.0f },{1.0f,1.0f} }; // �E��
    vertices_[RT] = { { right, top,    0.0f },{1.0f,0.0f} }; // �E��

	// ���_�f�[�^�S�̂̃T�C�Y = ���_�f�[�^����̃T�C�Y * ���_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(vertices_[0]) * _countof(vertices_));

    // ���_�o�b�t�@�̐ݒ�
    D3D12_HEAP_PROPERTIES heapProp{};   // �q�[�v�ݒ�
    heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPU�ւ̓]���p
    // ���\�[�X�ݒ�
    D3D12_RESOURCE_DESC resDesc{};
    resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    resDesc.Width = sizeVB; // ���_�f�[�^�S�̂̃T�C�Y
    resDesc.Height = 1;
    resDesc.DepthOrArraySize = 1;
    resDesc.MipLevels = 1;
    resDesc.SampleDesc.Count = 1;
    resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

    // ���_�o�b�t�@�̐���
    result = spriteCommon->GetDirectXCommon()->GetDevice()->CreateCommittedResource(
        &heapProp, // �q�[�v�ݒ�
        D3D12_HEAP_FLAG_NONE,
        &resDesc, // ���\�[�X�ݒ�
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&vertBuff));
    assert(SUCCEEDED(result));

    // GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
    Vertex* vertMap = nullptr;
    result = vertBuff->Map(0, nullptr, (void**)&vertMap);
    assert(SUCCEEDED(result));
    // �S���_�ɑ΂���
    for (int i = 0; i < _countof(vertices_); i++) {
        vertMap[i] = vertices_[i];   // ���W���R�s�[
    }
    // �q���������
    vertBuff->Unmap(0, nullptr);

    // GPU���z�A�h���X
    vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
    // ���_�o�b�t�@�̃T�C�Y
    vbView.SizeInBytes = sizeVB;
    // ���_�P���̃f�[�^�T�C�Y
    vbView.StrideInBytes = sizeof(vertices_[0]);

    // �}�e���A��
    {
        // �q�[�v�ݒ�
        D3D12_HEAP_PROPERTIES cbHeapProp{};
        cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;                   // GPU�ւ̓]���p
        // ���\�[�X�ݒ�
        D3D12_RESOURCE_DESC cbResourceDesc{};
        cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        cbResourceDesc.Width = (sizeof(ConstBufferDataMaterial) + 0xff) & ~0xff;   // 256�o�C�g�A���C�������g
        cbResourceDesc.Height = 1;
        cbResourceDesc.DepthOrArraySize = 1;
        cbResourceDesc.MipLevels = 1;
        cbResourceDesc.SampleDesc.Count = 1;
        cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        // �萔�o�b�t�@�̐���
        result = spriteCommon->GetDirectXCommon()->GetDevice()->CreateCommittedResource(
            &cbHeapProp, // �q�[�v�ݒ�
            D3D12_HEAP_FLAG_NONE,
            &cbResourceDesc, // ���\�[�X�ݒ�
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&constBuffMaterial));
        assert(SUCCEEDED(result));
        // �萔�o�b�t�@�̃}�b�s���O
        result = constBuffMaterial->Map(0, nullptr, (void**)&constMapMaterial); // �}�b�s���O
        assert(SUCCEEDED(result));
        // �l���������ނƎ����I�ɓ]�������
        constMapMaterial->color = color;
    }

    // �s��
    {
        // �q�[�v�ݒ�
        D3D12_HEAP_PROPERTIES cbHeapProp{};
        cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;                   // GPU�ւ̓]���p
        // ���\�[�X�ݒ�
        D3D12_RESOURCE_DESC cbResourceDesc{};
        cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        cbResourceDesc.Width = (sizeof(ConstBufferDataTransform) + 0xff) & ~0xff;   // 256�o�C�g�A���C�������g
        cbResourceDesc.Height = 1;
        cbResourceDesc.DepthOrArraySize = 1;
        cbResourceDesc.MipLevels = 1;
        cbResourceDesc.SampleDesc.Count = 1;
        cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        // �萔�o�b�t�@�̐���
        result = spriteCommon->GetDirectXCommon()->GetDevice()->CreateCommittedResource(
            &cbHeapProp, // �q�[�v�ݒ�
            D3D12_HEAP_FLAG_NONE,
            &cbResourceDesc, // ���\�[�X�ݒ�
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&constBuffTransform));
        assert(SUCCEEDED(result));
        // �萔�o�b�t�@�̃}�b�s���O
        result = constBuffTransform->Map(0, nullptr, (void**)&constMapTransform); // �}�b�s���O
        assert(SUCCEEDED(result));

        // ���[���h�ϊ��s��
        XMMATRIX matWorld;
        matWorld = XMMatrixIdentity();

        rotationZ_ = 0.0f;
        position_ = { 0.0f,0.0f };

        // ��]
        XMMATRIX matRot;
        matRot = XMMatrixIdentity();
        matRot = XMMatrixRotationZ(XMConvertToRadians(rotationZ_));
        matWorld *= matRot;

        // ���s
        XMMATRIX matTrans;
        matTrans = XMMatrixTranslation(position_.x, position_.y, 0.0f);
        matWorld *= matTrans;

        // �ˉe�ϊ�
        XMMATRIX matProjection = XMMatrixOrthographicOffCenterLH(
            0.0f, WinApp::window_width,
            WinApp::window_height, 0.0f,
            0.0f, 1.0f
        );

        constMapTransform->mat = matWorld * matProjection;
    }
}

void Sprite::Update()
{
    ID3D12Resource* textBuffer = spriteCommon->GetTextureBuffer(textureIndex_);

    if (textBuffer) {
        // �e�N�X�`�����擾
        D3D12_RESOURCE_DESC resDesc = textBuffer->GetDesc();

        // �A���J�[�|�C���g
        float tex_left = textureLeftTop_.x / resDesc.Width;
        float tex_right = (textureLeftTop_.x + textureSize_.x) / resDesc.Width;
        float tex_top = textureLeftTop_.y / resDesc.Height;
        float tex_bottom = (textureLeftTop_.y + textureSize_.y) / resDesc.Height;
        // ���_�f�[�^uv
        vertices_[LB].uv = { tex_left,tex_bottom }; // ����
        vertices_[LT].uv = { tex_left,tex_top }; // ����
        vertices_[RB].uv = { tex_right,tex_bottom }; // �E��
        vertices_[RT].uv = { tex_right,tex_top }; // �E��
    }

    // �A���J�[�|�C���g
    float left = (0.0f - anchorPoint_.x) * size_.x;
    float right = (1.0f - anchorPoint_.x) * size_.x;
    float top = (0.0f - anchorPoint_.y) * size_.y;
    float bottom = (1.0f - anchorPoint_.y) * size_.y;
    // ���E���]
    if (isFlipX_) {
        left = -left;
        right = -right;
    }
    // �㉺���]
    if (isFlipY_) {
        top = -top;
        bottom = -bottom;
    }
    // ���_�f�[�^���W
    vertices_[LB].pos = { left,  bottom, 0.0f }; // ����
    vertices_[LT].pos = { left, top,     0.0f }; // ����
    vertices_[RB].pos = { right, bottom, 0.0f }; // �E��
    vertices_[RT].pos = { right, top,    0.0f }; // �E��

    // ���_�f�[�^�]��
    Vertex* vertMap = nullptr;
    result = vertBuff->Map(0, nullptr, (void**)&vertMap);
    assert(SUCCEEDED(result));
    // �S���_�ɑ΂���
    for (int i = 0; i < _countof(vertices_); i++) {
        vertMap[i] = vertices_[i];   // ���W���R�s�[
    }
    // �q���������
    vertBuff->Unmap(0, nullptr);

    constMapMaterial->color = color_;

    // ���[���h�ϊ��s��
    XMMATRIX matWorld;
    matWorld = XMMatrixIdentity();

    // ��]
    XMMATRIX matRot;
    matRot = XMMatrixIdentity();
    matRot = XMMatrixRotationZ(XMConvertToRadians(rotationZ_));
    matWorld *= matRot;

    // ���s
    XMMATRIX matTrans;
    matTrans = XMMatrixTranslation(position_.x, position_.y, 0.0f);
    matWorld *= matTrans;

    // �ˉe�ϊ�
    XMMATRIX matProjection = XMMatrixOrthographicOffCenterLH(
        0.0f, WinApp::window_width,
        WinApp::window_height, 0.0f,
        0.0f, 1.0f
    );

    constMapTransform->mat = matWorld * matProjection;
}

void Sprite::Draw()
{
    // ��\��
    if (isInvisible_) {
        return;
    }

    // �e�N�X�`���R�}���h
    spriteCommon->SetTextureCommands(textureIndex_);

    // ���_�o�b�t�@�r���[�̐ݒ�R�}���h
    spriteCommon->GetDirectXCommon()->GetCommandList()->IASetVertexBuffers(0, 1, &vbView);
    // �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
    spriteCommon->GetDirectXCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffMaterial->GetGPUVirtualAddress());
    spriteCommon->GetDirectXCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(2, constBuffTransform->GetGPUVirtualAddress());
    // �`��R�}���h
    spriteCommon->GetDirectXCommon()->GetCommandList()->DrawInstanced(4, 1, 0, 0);
}

void Sprite::AdjustTextureSize()
{
    ID3D12Resource* textBuffer = spriteCommon->GetTextureBuffer(textureIndex_);
    assert(textBuffer);

    // �e�N�X�`�����擾
    D3D12_RESOURCE_DESC resDesc = textBuffer->GetDesc();

    textureSize_.x = static_cast<float>(resDesc.Width);
    textureSize_.y = static_cast<float>(resDesc.Height);
}