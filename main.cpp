//******************************************************************************
//
//
//      main
//
//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
#include "all.h"

int APIENTRY WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

    // SceneManager���`
    SceneManager sceneManager;

    // �^�C�g���V�[���J�n
    sceneManager.execute(Title::instance());

    return 0;
}