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

    // �ǂݍ��ރe�N�X�`��
    LoadTexture loadTextureTitle[static_cast<size_t>(TEXNUM::NUM)] = {
        { static_cast<int>(TEXNUM::STAR),  L"./Data/Images/star.png", 1U },
        { static_cast<int>(TEXNUM::START), L"./Data/Images/start.png", 1U },
        { static_cast<int>(TEXNUM::PLAYER), L"./Data/Images/player.png", 1U },
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
        fadeOutTimer_ = 0.0f;               // �t�F�[�h�A�E�g�p�ϐ��̏����ݒ�
        switchNum = 0;
        starScale_ = { 0.0f, 0.0f };
        starAngle_ = 0.0f;

        playerPos_      = { BG::WINDOW_W / 4, 1000 };
        playerScale_    = { 5.0f, 5.0f };
        playerColor_    = { 1, 1, 1, 1 };
        playerTexPos_   = { 0, 0 };
        
        //BGM���Đ�
        GameLib::music::play(5, false);

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // �ʏ�̃A���t�@����
                 
        state_++;                                            // �����������̏I��

        /*fallthrough*/

    case 1:
        //////// �t�F�[�h�C���� ////////
        starAngle_ -= ToRadian(4);
        starScale_ += { 0.2f, 0.2f };

        if (starScale_.x > 15.0) {
            starScale_ = { 15.0f , 15.0f };
            ++state_;   // �ʏ�̏�����
        }
        break;

    case 2:
        //////// �ʏ펞�̏��� ////////

        if (TRG(0) & PAD_START) {

            //���艹
            GameLib::music::play(7, false);

            ++state_;   // �t�F�[�h�A�E�g��
        }

        break;

    case 3:
        //////// �t�F�[�h�A�E�g�� ////////
        starAngle_ += ToRadian(4);
        starScale_ -= { 0.2f , 0.2f };

        if (starScale_.x < 0) {
            starScale_ = { 0.0f, 0.0f };
            //BGM���~�߂�
            GameLib::music::stop(5);
            changeScene(Select::instance());
            break;
        }
        break;
    }
    // �v���C���[�̃A�j���[�V����
    // playerAnime();

    debug::setString("timer_:%d", timer_);
    debug::setString("state_:%d", state_);
    debug::setString("playerPos_.x:%f", playerPos_.x);
    debug::setString("playerPos_.y:%f", playerPos_.y);
    debug::setString("playerScale_.x:%f", playerScale_.x);
    debug::setString("playerScale_.y:%f", playerScale_.y);

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

    // ����`��
    sprStar_.draw(
        { GameLib::window::getWidth() / 2, GameLib::window::getHeight() / 2 },
        { starScale_.x , starScale_.y },
        starAngle_
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