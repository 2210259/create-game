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
    LoadTexture loadTextureTitle[static_cast<size_t>(TEXNOM::NUM)] = {
        { static_cast<int>(TEXNOM::STAR),  L"./Data/Images/star.png", 1U },
        { static_cast<int>(TEXNOM::START),  L"./Data/Images/start.png", 1U },
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

        starScale_ = { 0.0f, 0.0f };
        starAngle_ = 0.0f;

        playerPos_      = { 320, 600 };
        playerScale_    = { 1.0f, 1.0f };
        playerTexPos_   = { 0, 0 };
        playerTexSize_  = { 150, 150 };

        //BGM���Đ�
        GameLib::music::play(5, false);

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // �ʏ�̃A���t�@����
                 
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

        if (TRG(0) & PAD_START) {

            //���艹
            GameLib::music::play(7, false);

            ++state_;   // �t�F�[�h�A�E�g��
        }

        break;

    case 3:
        //////// �t�F�[�h�A�E�g�� ////////
        starAngle_ += ToRadian(4);
        starScale_ -= { 0.1f , 0.1f };

        if (starScale_.x < 0) {
            starScale_ = { 0.0f, 0.0f };
        }

        fadeOutTimer_ += 0.01167f;
        if (fadeOutTimer_ >= 1.0f) {
            //BGM���~�߂�
            GameLib::music::stop(5);
            changeScene(Game::instance());
            break;
        }
        break;
    }

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
    // texture::begin(TEXNO::PLAYER);
    // texture::draw(TEXNO::PLAYER, playerPos_, playerScale_,
    //     playerTexPos_, playerTexSize_);
    // texture::end(TEXNO::PLAYER);

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