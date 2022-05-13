//******************************************************************************
//
//
//      scene_title.cpp
//
//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;
using namespace input;

//------< �ϐ� >----------------------------------------------------------------
Title Title::instance_;

// �����ݒ�
void Title::init() {
    Scene::init();	    // ���N���X��init���Ă�

    //�f�[�^�ATEXNUM�̕ύX
    // �ǂݍ��ރe�N�X�`��
    LoadTexture loadTextureTitle[static_cast<size_t>(TEXNUM::NUM)] = {
        { static_cast<int>(TEXNUM::SQUARE),  L"./Data/Images/tutorial_icon.png", 1U },
        { static_cast<int>(TEXNUM::START), L"./Data/Images/start.png", 1U },
        { static_cast<int>(TEXNUM::PLAYER), L"./Data/Images/player.png", 1U },
        { static_cast<int>(TEXNUM::L_FUSUMA), L"./Data/Images/L_fusuma.png", 1U },
        { static_cast<int>(TEXNUM::R_FUSUMA), L"./Data/Images/R_fusuma.png", 1U },
    };

    // �e�N�X�`���̃��[�h
    texture::load(loadTextureTitle);
}

// �I������
void Title::deinit() {
    
    // �e�N�X�`����S�ĉ��
    texture::releaseAll();
}

// �X�V
void Title::update() {
    
    switch (state_) {
    case 0:
        //////// �����ݒ� ////////
        timer_ = 0;                         // �^�C�}�[��������
        switchNum = 0;

        squarePos_ = { -window::getWidth() , -window::getHeight()};
        squareScale_ = { 8.0f, 0.02f };
        squareAngle_ = 29.0f;

        playerPos_      = { BG::WINDOW_W / 4, 1000 };
        playerScale_    = { 5.0f, 5.0f };
        playerColor_    = { 1, 1, 1, 1 };
        playerTexPos_   = { 0, 0 };
        
        push_flg_ = false;

        //�V�[���؂�ւ��p�̉摜�ʒu�̏�����
        T_L_Fusuma_Pos_ = { -960 / 2,540 };
        T_R_Fusuma_Pos_ = { (960 * 2) + (960 / 2) , 540 };

        Fusuma_timer_ = 0;

        //TODO:���ԕύX�ɔ����ύX
        //BGM���Đ�
        GameLib::music::play(6, false);

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // �ʏ�̃A���t�@����
                 
        state_++;                                            // �����������̏I��

        /*fallthrough*/

    case 1:
        //////// �t�F�[�h�C���� ////////

        //TODO:��ʑJ�ڂ̏���
        //�l�p�`�̈ړ�
        if (squarePos_.x < window::getWidth() / 2 && squarePos_.y < window::getHeight() / 2)
        {
            squarePos_.x += 100 * 3;
            squarePos_.y += 56.2f * 3;
        }
        //�l�p�`���w��̈ʒu�ɍs������Œ�
        else
        {
            squarePos_.x = window::getWidth() / 2;
            squarePos_.y = window::getHeight() / 2;
        }

        //�X�P�[����ω�������(�������)
        if (squarePos_.x >= window::getWidth() / 2 && squarePos_.y >= window::getHeight() / 2 && 
            squareScale_.y < 0.05f)
        {
            squareScale_.y += 0.001f;
        }
        //�X�P�[����ω�������(����)
        else if(squarePos_.x >= window::getWidth() / 2 && squarePos_.y >= window::getHeight() / 2 &&
            squareScale_.y >= 0.05f)
        {
            squareScale_.y += 0.1f;
            //�X�P�[���̒l���Œ�
            if (squareScale_.y >= 5.5f)
            {
                squareScale_.y = 5.5f;
                state_++;
                break;
            }
        }

        break;

    case 2:
        //////// �ʏ펞�̏��� ////////

        if (TRG(0) & PAD_START) 
        {
            //���艹
            GameLib::music::play(7, false);

            //TODO:�t���O��true��
            push_flg_ = true;
        }

        //TODO:���̏���
        if (push_flg_)
        {
            if (T_L_Fusuma_Pos_.x <= 960 && T_R_Fusuma_Pos_.x >= (960 * 1.5f))
            {
                T_L_Fusuma_Pos_.x += 30;
                T_R_Fusuma_Pos_.x -= 30;
            }

            if (T_L_Fusuma_Pos_.x >= 480 && T_R_Fusuma_Pos_.x <= (960 * 1.5f))
            {
                T_L_Fusuma_Pos_.x = 480;
                T_R_Fusuma_Pos_.x = (960 * 1.5f);

                if (Fusuma_timer_ > 60)
                    changeScene(Select::instance());

                Fusuma_timer_++;
            }
        }

        break;
    }
    // �v���C���[�̃A�j���[�V����
    // playerAnime();

    debug::setString("timer_:%d", timer_);
    debug::setString("state_:%d", state_);
    //debug::setString("playerPos_.x:%f", playerPos_.x);
    //debug::setString("playerPos_.y:%f", playerPos_.y);
    //debug::setString("playerScale_.x:%f", playerScale_.x);
    //debug::setString("playerScale_.y:%f", playerScale_.y);
    debug::setString("squareScale_.x%f", squareScale_.x);
    debug::setString("squareScale_.y%f", squareScale_.y);

    timer_++;
}

// �`��
void Title::draw() {
    // ��ʃN���A
    GameLib::clear(VECTOR4(0.5f, 0.5f, 0.5f, 1.0f));

    // �X�e���V�����[�h�F�ʏ�
    DepthStencil::instance().set(DepthStencil::MODE::NONE);

    // �X�e���V�����[�h�F�}�X�N����
    DepthStencil::instance().set(DepthStencil::MODE::MASK);

    // �l�p��`��
    sprSquare_.draw(
        squarePos_,
        squareScale_,
        squareAngle_ * PI / 180 
    );

    // �X�e���V�����[�h�F�}�X�N�ɕ`��
    DepthStencil::instance().set(DepthStencil::MODE::APPLY_MASK);

    // �^�C�g���̕`��
    GameLib::font::textOut(4, "NoName",
        { GameLib::window::getWidth() / 4 * 3, (GameLib::window::getHeight() / 4) },
        VECTOR2(2.0f, 2.0f),
        { 1.0f, 1.0f, 1.0f, 1.0f },
        GameLib::TEXT_ALIGN::UPPER_RIGHT
    );

    //"�J�n"�̕����̕`��
    sprStart_.draw(
        { GameLib::window::getWidth() - sprStart_.width / 2, GameLib::window::getHeight() - sprStart_.height / 2 }
    );

    // �v���C���[�̕`��

    // sprPlayer_.draw(
    //     { playerPos_.x, playerPos_.y }, 
    //     { playerScale_.x, playerScale_.y },
    //     0,
    //     playerColor_
    // );

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

    // �X�e���V�����[�h�F�ʏ�
    DepthStencil::instance().set(DepthStencil::MODE::NONE);

    sprL_fusuma_.draw(
        T_L_Fusuma_Pos_
    );

    sprR_fusuma_.draw(
        T_R_Fusuma_Pos_
    );

}

void Title::playerAnime() {
    switch (switchNum)
    {
    case 0:
        playerTexPos_ = { 0, 0 };
        if (timer_ % 10 == 0)
            switchNum++;
        break;
    case 1:
        playerTexPos_ = { 150, 0 };
        if (timer_ % 10 == 0)
            switchNum--;
        break;
    }
    debug::setString("playerTexPos_:%f", playerTexPos_.x);
    debug::setString("switchNum:%d", switchNum);
}