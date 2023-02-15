#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#pragma region 基盤システムの初期化
    // ポインタ
    Input* input = nullptr;
    WinApp* winApp = nullptr;
    DirectXCommon* dxCommon = nullptr;

    // WinAppの初期化
    winApp = new WinApp();
    winApp->Initialize();
    // DirectXの初期化
    dxCommon = new DirectXCommon();
    dxCommon->Initialize(winApp);
    // 入力の初期化
    input = new Input();
    input->Initialize(winApp);
#pragma endregion 基盤システムの初期化

#pragma region WindowsAPI初期化処理
    MSG msg{};  // メッセージ
#pragma endregion WindowsAPI初期化処理

#pragma region 最初のシーンの初期化

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

#pragma endregion 最初のシーンの更新

        // 描画処理
        dxCommon->PreDraw();

#pragma region 最初のシーンの描画

#pragma endregion 最初のシーンの描画

        // 描画後処理
        dxCommon->PostDraw();
    }

#pragma region 最初のシーンの終了

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
#pragma endregion 基盤システムの終了

    return 0;
}
