#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include "Sprite.h"


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#pragma region 基盤システムの初期化
    // ポインタ
    Input* input = nullptr;
    WinApp* winApp = nullptr;
    DirectXCommon* dxCommon = nullptr;
    SpriteCommon* spriteCommon = nullptr;

    // WinAppの初期化
    winApp = new WinApp();
    winApp->Initialize();
    // DirectXの初期化
    dxCommon = new DirectXCommon();
    dxCommon->Initialize(winApp);
    // 入力の初期化
    input = new Input();
    input->Initialize(winApp);
    // SpriteCommonの初期化
    spriteCommon = new SpriteCommon;
    spriteCommon->Initialize(dxCommon);
    spriteCommon->LoadTexture(0, "texture.png");
    spriteCommon->LoadTexture(1, "reimu.png");
#pragma endregion 基盤システムの初期化

#pragma region WindowsAPI初期化処理
    // メッセージ
    MSG msg{};
#pragma endregion WindowsAPI初期化処理

#pragma region 最初のシーンの初期化
    // Sprite初期化
    Sprite* sprite = new Sprite();
    sprite->Initialize(spriteCommon);
    sprite->SetColor({ 1,1,1,1 });
    sprite->SetTextureIndex(1);
#pragma endregion 最初のシーンの初期化

    // ゲームループ
#pragma region 基盤システムの更新
    while (true) {
        // Windowsのメッセージ処理
        if (winApp->ProcessMessage()) {
            // ゲームループを抜ける
            break;
        }

        // 入力の更新
        input->Update();
#pragma endregion 基盤システムの更新

#pragma region 最初のシーンの更新
        DirectX::XMFLOAT2 pos = sprite->GetPosition();
        //pos.x += 0.1f;
        sprite->SetPosition(pos);
        float rotZ = sprite->GetRotation();
        //rotZ += 0.1f;
        sprite->SetRotation(rotZ);
        DirectX::XMFLOAT2 siz = sprite->GetSize();
        //siz.y += 1.0f;
        sprite->SetSize(siz);
        sprite->Update();
#pragma endregion 最初のシーンの更新

        // DirectX描画前処理
        dxCommon->PreDraw();

#pragma region 最初のシーンの描画
        // SpriteCommon描画前処理
        spriteCommon->PreDraw();
        // Sprite描画
        sprite->Draw();
        // SpriteCommon描画後処理
        spriteCommon->PostDraw();
#pragma endregion 最初のシーンの描画

        // 描画後処理
        dxCommon->PostDraw();
    }

#pragma region 最初のシーンの終了
    // Sprite解放
    delete sprite;
#pragma endregion 最初のシーンの終了

#pragma region 基盤システムの終了
    // 入力解放
    delete input;
    // DirectX解放
    delete dxCommon;
    // WindowsAPIの終了処理
    winApp->Finalize();
    // WindowsAPI解放
    delete winApp;
    // SpriteCommon解放
    delete spriteCommon;
#pragma endregion 基盤システムの終了

    return 0;
}
