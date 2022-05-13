#pragma once
//******************************************************************************
//
//      scene_select.h
//
//******************************************************************************

#include "scene.h"
#include "../GameLib/obj2d_data.h"

class Select : public Scene
{
private:
    static Select instance_;

public:
    // �C���X�^���X�̎擾
    static Select* instance() { return &instance_; }

    void init() override;
    void deinit() override;
    void update() override;
    void draw() override;

    //TODO:�Q�b�^�[�̐ݒ�
    //�Q�b�^�[
    int stageNum() { return stageNum_; }

private:
    Select() {}
    ~Select() {}

    Select(const Select&) = delete;                 // �R�s�[�R���X�g���N�^�[
    Select& operator=(const Select&) = delete;      // �R�s�[������Z�q
    Select(Select&&) noexcept = delete;             // ���[�u�R���X�g���N�^�[
    Select& operator=(Select&&) noexcept = delete;  // ���[�u������Z�q

public:
    //TODO:�ύX
    // �g�p����e�N�X�`���̃��x��
    enum class TEXNO {
        BACK,
        TUTORIAL,
        STAGE1,
        STAGE2,
        L_FUSUMA,
        R_FUSUMA,
        NUM,
    };

    //TODO:�ύX
    // �g�p����X�v���C�g�f�[�^
    GameLib::SpriteData sprBack_ = SPRITE_CENTER(static_cast<INT>(TEXNO::BACK), 0, 0, 1920, 1080);
    GameLib::SpriteData sprTutorial_ = SPRITE_CENTER(static_cast<INT>(TEXNO::TUTORIAL), 0, 0, 700, 700);
    GameLib::SpriteData sprStage1_ = SPRITE_CENTER(static_cast<INT>(TEXNO::STAGE1), 0, 0, 700, 700);
    GameLib::SpriteData sprStage2_ = SPRITE_CENTER(static_cast<INT>(TEXNO::STAGE2), 0, 0, 700, 700);
    GameLib::SpriteData sprL_fusuma_ = SPRITE_CENTER(static_cast<INT>(TEXNO::L_FUSUMA), 0, 0, 960, 1080);
    GameLib::SpriteData sprR_fusuma_ = SPRITE_CENTER(static_cast<INT>(TEXNO::R_FUSUMA), 0, 0, 960, 1080);


private:

    // �����o�ϐ�
    int stageNum_ = 0;
    bool push_flg = false;

    //TODO:�ϐ��̒ǉ����ύX
    float tutorial_icon_Alpha_ = 1.0f;
    float stage1_icon_Alpha_ = 1.0f;
    float stage2_icon_Alpha_ = 1.0f;
    VECTOR2 tutorial_icon_Scale_ = { 0.5f , 0.5f };
    VECTOR2 stage1_icon_Scale_ = { 0.5f , 0.5f };
    VECTOR2 stage2_icon_Scale_ = { 0.5f , 0.5f };
    VECTOR2 tutorial_icon_Pos_ = { GameLib::window::getWidth() / 2 - (GameLib::window::getWidth() / 2) / 2 , GameLib::window::getHeight() / 2 };
    VECTOR2 stage1_icon_Pos_ = { GameLib::window::getWidth() / 2 , GameLib::window::getHeight() / 2 };
    VECTOR2 stage2_icon_Pos_ = { GameLib::window::getWidth() / 2 + (GameLib::window::getWidth() / 2) / 2 , GameLib::window::getHeight() / 2 };
    VECTOR2 S_L_Fusuma_Pos_ = { 0,0 };
    VECTOR2 S_R_Fusuma_Pos_ = { 0,0 };
    float Fusuma_timer_ = 0.0f;
};