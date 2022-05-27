//******************************************************************************
//
//
//      �V�[���Ǘ�
//
//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
#include "all.h"

//==============================================================================
//
//      Scene�N���X
//
//==============================================================================

//--------------------------------------------------------------
//  ���s
//--------------------------------------------------------------
Scene* Scene::execute()
{
    using namespace GameLib;

    // ����������
    init();

    // �Q�[�����[�v
    while (GameLib::gameLoop(false))    // false��true�ɂ���ƃ^�C�g���o�[�Ƀt���[�����[�g�\��
    {
        // ���͏���
        input::update();

        // �X�V����
        update();

        // �X�e���V�����[�h�F�ʏ�
        DepthStencil::instance().set(DepthStencil::MODE::NONE);

        // �`�揈��
        draw();

        // �X�e���V�����[�h�F�ʏ�
        DepthStencil::instance().set(DepthStencil::MODE::NONE);

        // �f�o�b�O������̕`��
        debug::display(0, 0, 0, 1.5f, 1.5f);
        
        // debug::display(1, 0.6f, 0, 1.5f, 1.5f);
        // debug::setString("GP2_10 SAMPLE");

        // ��ʃt���b�v
        GameLib::present(1, 0);

        // �I���`�F�b�N
        if (nextScene_) break;
    }

    // �I������
    deinit();

    return nextScene_;	// ���̃V�[����Ԃ�
}

//******************************************************************************
//
//      SceneManager�N���X
//
//******************************************************************************

//--------------------------------------------------------------
//  ���s
//--------------------------------------------------------------
void SceneManager::execute(Scene* scene)
{
    using namespace GameLib;

    bool isFullScreen = true;	// �t���X�N���[���ɂ���Ȃ�true�ɕς���
                                //�iRelease���[�h�̂݁j

    // �Q�[�����C�u�����̏���������
    GameLib::init(L"�E�Ҋy", BG::WINDOW_W, BG::WINDOW_H, isFullScreen);

#ifndef _DEBUG
    ShowCursor(!isFullScreen);	// �t���X�N���[�����̓J�[�\��������
#endif
    //�e�N�X�`���̓ǂݍ���
    texture::load(loadTexture);

    //���y�ǂݍ���
    audio.init();

    // ���C�����[�v
    while (scene)
    {
        scene = scene->execute();
    }

    //�e�N�X�`���̉��
    texture::releaseAll();

    //���y�N���A
    audio.deinit();

    // �Q�[�����C�u�����̏I������
    GameLib::uninit();
}

//******************************************************************************
