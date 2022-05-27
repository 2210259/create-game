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
        { static_cast<int>(TEXNUM::SQUARE),  L"./Data/Images/stage2_icon.png",    1U },
        { static_cast<int>(TEXNUM::L_FUSUMA), L"./Data/Images/L_fusuma.png",      1U },
        { static_cast<int>(TEXNUM::R_FUSUMA), L"./Data/Images/R_fusuma.png",      1U },
        { static_cast<int>(TEXNUM::START), L"./Data/Images/start.png",            1U },
        { static_cast<int>(TEXNUM::TITLE_BACK), L"./Data/Images/title.png",       7U }, // �^�C�g���w�i
        { static_cast<int>(TEXNUM::T_AORENTER), L"./Data/Images/textAorEnter.png",1U }
    };

    // �e�N�X�`���̃��[�h
    texture::load(loadTextureTitle);
}

// �I������
void Title::deinit()
{    
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

        squarePos_ = { -window::getWidth() , -window::getHeight() };
        squareScale_ = { 8.0f, 0.02f };
        squareAngle_ = 29.0f;

        playerPos_ = { BG::WINDOW_W / 4, 1000 };
        playerScale_ = { 5.0f, 5.0f };
        playerColor_ = { 1, 1, 1, 1 };
        playerTexPos_ = { 0, 0 };
        titleColor_ = { 1, 1 ,1 ,1 };
        titleBackTexPos_ = {};

        //�V�[���؂�ւ��p�̉摜�ʒu�̏�����
        T_L_Fusuma_Pos_ = { -960 / 2, 540 };
        T_R_Fusuma_Pos_ = { (960 * 2) + (960 / 2) , 540 };

        Fusuma_timer_ = 0;

        //BGM���Đ�
        GameLib::music::play(6, false);

        GameLib::music::play(12, false);

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

        state_++;                                            // �����������̏I��

        /*fallthrough*/

    case 1:
        //////// �t�F�[�h�C���� ////////

        //�l�p�`�̈ړ�
        if (squarePos_.x < window::getWidth() / 2 && squarePos_.y < window::getHeight() / 2)
        {
            squarePos_.x += 100 * 3;
            squarePos_.y += 56.2f * 3;
        }
        //�l�p�`���w��̈ʒu�ɍs������Œ�
        else {
            squarePos_.x = window::getWidth() / 2;
            squarePos_.y = window::getHeight() / 2;
        }

        //�X�P�[����ω�������(�������)
        if (squarePos_.x >= window::getWidth() / 2 && squarePos_.y >= window::getHeight() / 2 &&
            squareScale_.y < 0.05f) {
            squareScale_.y += 0.001f;
        }
        //�X�P�[����ω�������(����)
        else if (squarePos_.x >= window::getWidth() / 2 && squarePos_.y >= window::getHeight() / 2 &&
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

        if (TRG(0) & PAD_START) {
            //���艹
            GameLib::music::play(8, false);

            // �v���C���[�̏�����
            timer_ = 0;
            state_++;
        }
        break;
    case 3:
        //////// �ʏ펞�̏��� ////////
        if (timer_ % 10 == 0 && titleColor_.w > 0) {
            titleColor_.w = 0;
        }
        else if (timer_ % 10 == 0 && titleColor_.w <= 0) {
            titleColor_.w = 1;
        }
        if (timer_ > 50)
        {
            //���J��
            GameLib::music::play(11, false);
            state_++;
            timer_ = 0;
        }
        break;
    case 4:
        //////// ���̏��� ////////
        if (T_L_Fusuma_Pos_.x <= 960 && T_R_Fusuma_Pos_.x >= (960 * 1.5f))
        {
            T_L_Fusuma_Pos_.x += 30;
            T_R_Fusuma_Pos_.x -= 30;
        }

        if (T_L_Fusuma_Pos_.x >= 480 && T_R_Fusuma_Pos_.x <= (960 * 1.5f))
        {
            T_L_Fusuma_Pos_.x = 480;
            T_R_Fusuma_Pos_.x = (960 * 1.5f);

            if (Fusuma_timer_ > 60) {
                music::stop(6);
                changeScene(Select::instance());
                break;
            }
            Fusuma_timer_++;
        }
        break;
    }
    // �v���C���[�̃A�j���[�V����
    if (state_ == 3 && timer_ > 35 && timer_ % 5 == 1 || state_ == 4 && timer_ % 5 == 1 && titleBackTexPos_.x < 11520) {
        titleBackTexPos_.x += BG::WINDOW_W;
    }

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
    sprTitleBack_.draw(
        { BG::WINDOW_W / 2, BG::WINDOW_H / 2 },
        VECTOR2(1,1),
        titleBackTexPos_.x, titleBackTexPos_.y, GameLib::window::getWidth(), GameLib::window::getHeight()
    );

    //"�J�n"�̕����̕`��
    sprStart_.draw(
        { GameLib::window::getWidth() - sprStart_.width / 2, GameLib::window::getHeight() - sprStart_.height / 2},
        VECTOR2(1,1), ToRadian(0), titleColor_
    );

    // text�̕`��
    if (timer_ >> 5 & 0x01 && state_ < 3) {
        sprAorEnter.draw(1450, 680);
    }

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

    // ���̕`��
    sprL_fusuma_.draw(T_L_Fusuma_Pos_);
    sprR_fusuma_.draw(T_R_Fusuma_Pos_);
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