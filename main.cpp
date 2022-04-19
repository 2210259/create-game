//******************************************************************************
//
//
//      main
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include "all.h"

int APIENTRY WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

    // SceneManagerを定義
    SceneManager sceneManager;

    // タイトルシーン開始
    sceneManager.execute(Title::instance());

    return 0;
}
