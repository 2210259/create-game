//******************************************************************************
//
//
//      �^�C�g�����
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
    LoadTexture loadTextureTitle[static_cast<size_t>(TEXNO::NUM)] = {
        { static_cast<int>(TEXNO::STAR),  L"./Data/Images/star.png", 1U },
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
            changeScene(Select::instance());
            break;
        }
        break;
    }

    debug::setString("timer_:%d", timer_);
    debug::setString("state_:%d", state_);
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
    GameLib::font::textOut(4, "Title",
        { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 3) },
        VECTOR2(5.0f, 5.0f),
        { 1.0f, 1.0f, 1.0f, 1.0f },
        GameLib::TEXT_ALIGN::UPPER_MIDDLE
    );

    // Push Enter Key �̕`��
    if (timer_ >> 5 & 0x01) {
        GameLib::font::textOut(4, "Push Enter Key",
            { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 6) * 5 },
            VECTOR2(1.5f, 1.5f),
            { 1.0f, 1.0f, 1.0f, 1.0f },
            GameLib::TEXT_ALIGN::LOWER_MIDDLE
        );
    }

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