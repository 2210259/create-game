//******************************************************************************
//
//
//      �Z���N�g���
//
//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< �ϐ� >----------------------------------------------------------------
Select Select::instance_;

// �����ݒ�
void Select::init() {
    Scene::init();	    // ���N���X��init���Ă�

    // �ǂݍ��ރe�N�X�`��
    GameLib::LoadTexture loadTextureSelect[static_cast<size_t>(TEXNO::NUM)] = {
        { static_cast<int>(TEXNO::STAR),  L"./Data/Images/star.png", 1U },
        { static_cast<int>(TEXNO::BACK),  L"./Data/Images/stage_select.png", 1U },
        { static_cast<int>(TEXNO::TUTORIAL),  L"./Data/Images/tutorial_icon.png", 1U },
        { static_cast<int>(TEXNO::STAGE1),  L"./Data/Images/stage1_icon.png", 1U },
        { static_cast<int>(TEXNO::STAGE2),  L"./Data/Images/stage2_icon.png", 1U },
    };                    
                        
    // �e�N�X�`���̃��[�h
    GameLib::texture::load(loadTextureSelect);
}

// �I������
void Select::deinit() {
    // �e�N�X�`����S�ĉ��
    GameLib::texture::releaseAll();
}

// �X�V
void Select::update() {

    using namespace input;
    switch (state_) {
    case 0:
        //////// �����ݒ� ////////
        timer_ = 0;                         // �^�C�}�[��������
        fadeOutTimer_ = 0.0f;               // �t�F�[�h�A�E�g�p�ϐ��̏����ݒ�

        stageNum_ = 0;
        starScale_ = { 0.0f, 0.0f };
        starAngle_ = 0.0f;

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

        music::play(4, true);   //BGM�̍Đ�

        state_++;                                            // �����������̏I��

        /*fallthrough*/

    case 1:
        //////// �t�F�[�h�C���� ////////
        starAngle_ -= ToRadian(4);
        starScale_ += { 0.1f, 0.1f };

        if (starScale_.x > 8.0) {
            starScale_ = { 8.0f , 8.0f };
            ++state_;   // �ʏ�̏�����
        }
        break;

    case 2:
        //////// �ʏ펞�̏��� ////////

        //�X�e�[�W�I��p
        if (TRG(0) & PAD_LEFT)
        {
            if(stageNum_ > 0)
            stageNum_--;
        }

        if (TRG(0) & PAD_RIGHT)
        {
            if(stageNum_ < 2)
            stageNum_++;
        }

        //�I�����Ă���摜�̃��l�ƃX�P�[���̕ύX
        switch (stageNum_)
        {
        //�`���[�g���A���I��
        case 0:
            tutorialAlpha_ = 1.0f;            
            tutorialScale_ = { 0.6f , 0.6f };

            stage1Alpha_ = 0.2f;
            stage1Scale_ = { 0.5f , 0.5f };

            stage2Alpha_ = 0.2f;
            stage2Scale_ = { 0.5f , 0.5f };
            break;

        //�X�e�[�W�P�I��
        case 1:
            tutorialAlpha_ = 0.2f;
            tutorialScale_ = { 0.5f , 0.5f };

            stage1Alpha_ = 1.0f;
            stage1Scale_ = { 0.6f , 0.6f };

            stage2Alpha_ = 0.2f;
            stage2Scale_ = { 0.5f , 0.5f };
            break;

        //�X�e�[�W�Q�I��
        case 2:
            tutorialAlpha_ = 0.2f;
            tutorialScale_ = { 0.5f , 0.5f };

            stage1Alpha_ = 0.2f;
            stage1Scale_ = { 0.5f , 0.5f };

            stage2Alpha_ = 1.0f;
            stage2Scale_ = { 0.6f , 0.6f };
            break;
        }

        if (TRG(0) & PAD_START)
        {
            ++state_;
        }
        break;

    case 3:
        //////// �t�F�[�h�A�E�g�� ////////
        starAngle_ += ToRadian(4);
        starScale_ -= { 0.1f, 0.1f };

        if (starScale_.x < 0) {
            starScale_ = { 0.0f, 0.0f };
        }

        fadeOutTimer_ += 0.01167f;
        if (fadeOutTimer_ >= 1.0f) {
            changeScene(Game::instance());
            break;
        }

        break;
    }

    GameLib::debug::setString("state_:%d", state_);
    GameLib::debug::setString("timer_:%d", timer_);
    GameLib::debug::setString("stageNum_:%d", stageNum_);
    timer_++;
}

// �`��
void Select::draw() {
    // ��ʃN���A
    GameLib::clear(VECTOR4(0.0f, 0.0f, 1.0f, 1));

    // �X�e���V�����[�h�F�ʏ�
    DepthStencil::instance().set(DepthStencil::MODE::NONE);

    // �X�e���V�����[�h�F�}�X�N����
    DepthStencil::instance().set(DepthStencil::MODE::MASK);

    // ����`��
    sprStar_.draw(
        { GameLib::window::getWidth() / 2, GameLib::window::getHeight() / 2 },
        { starScale_.x , starScale_.y },
        starAngle_
    );

    // �X�e���V�����[�h�F�}�X�N�ɕ`��
    DepthStencil::instance().set(DepthStencil::MODE::APPLY_MASK);

    // �^�C�g���̕`��
    //GameLib::font::textOut(4, "StageSelect",
    //    { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 3) },
    //    VECTOR2(5.0f, 5.0f),
    //    { 1.0f, 1.0f, 1.0f, 1.0f },
    //    GameLib::TEXT_ALIGN::UPPER_MIDDLE
    //);

    //�w�i�̕`��
    sprBack_.draw(
        { 960,540 },
        { 1.0f,1.0f }
    );

    //�`���[�g���A���A�C�R���̕`��
    sprTutorial_.draw(
        { GameLib::window::getWidth() / 2 - (GameLib::window::getWidth() / 2) / 2 , GameLib::window::getHeight() / 2 },
        tutorialScale_,
        ToRadian(0),
        { 1.0f,1.0f,1.0f,tutorialAlpha_}
    );

    //�X�e�[�W�P�A�C�R���̕`��
    sprStage1_.draw(
        { GameLib::window::getWidth() / 2 , GameLib::window::getHeight() / 2 },
        stage1Scale_,
        ToRadian(0),
        { 1.0f,1.0f,1.0f,stage1Alpha_}
    );

    //�X�e�[�W�Q�A�C�R���̕`��
    sprStage2_.draw(
        { GameLib::window::getWidth() / 2 + (GameLib::window::getWidth() / 2) / 2 , GameLib::window::getHeight() / 2 },
        stage2Scale_,
        ToRadian(0),
        { 1.0f,1.0f,1.0f,stage2Alpha_}
    );


    // Push Enter Key �̕`��
    //if (timer_ >> 5 & 0x01) {
    //    GameLib::font::textOut(4, "Push Enter Key",
    //        { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 6) * 5 },
    //        VECTOR2(1.5f, 1.5f),
    //        { 1.0f, 1.0f, 1.0f, 1.0f },
    //        GameLib::TEXT_ALIGN::LOWER_MIDDLE
    //    );
    //}

    // �t�F�[�h�A�E�g
    // if (fadeOutTimer_ > 0.0f) {
    //     DepthStencil::instance().set(DepthStencil::MODE::APPLY_MASK);
    //     GameLib::primitive::rect({ 0, 0 }, 
    //         { GameLib::window::getWidth(), GameLib::window::getHeight() },
    //         { 0, 0 }, 0, { 0, 0, 0, fadeOutTimer_ });
    // }

    // �X�e���V�����[�h�F�}�X�N�ȊO�ɕ`��
    DepthStencil::instance().set(DepthStencil::MODE::EXCLUSIVE);

    // �l�p�`
    GameLib::primitive::rect({ 0, 0 },
        { GameLib::window::getWidth(), GameLib::window::getHeight() },
        { 0, 0 },
        ToRadian(0),
        { 0.0f, 0.0f, 0.0f, 1.0f }
    );
}
