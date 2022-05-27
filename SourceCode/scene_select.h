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

    float calcIconFlashing(float colorW, int timer);
    float calcIconFade(float colorW);

    void shurikenAct();

    //�Q�b�^�[�̐ݒ�
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
    // �g�p����e�N�X�`���̃��x��
    enum class TEXNOM {
        BACK,
        TUTORIAL,
        STAGE1,
        L_FUSUMA,
        R_FUSUMA,
        TOTITLE,
        DECORATION,
        SHURIKEN,
        NUM,
    };

    // �g�p����X�v���C�g�f�[�^
    GameLib::SpriteData sprBack_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::BACK), 0, 0, 1920, 1080);
    GameLib::SpriteData sprTutorial_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::TUTORIAL), 0, 0, 438, 1050);
    GameLib::SpriteData sprStage1_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::STAGE1), 0, 0, 438, 1050);
    GameLib::SpriteData sprL_fusuma_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::L_FUSUMA), 0, 0, 960, 1080);
    GameLib::SpriteData sprR_fusuma_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::R_FUSUMA), 0, 0, 960, 1080);
    GameLib::SpriteData sprTotitle_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::TOTITLE), 0, 0, 438, 1050);
    GameLib::SpriteData sprShuriken_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::SHURIKEN), 0, 0, 150, 150);
    GameLib::SpriteData sprDecration_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::DECORATION), 0, 0, 438, 1050);

private:
    struct Param {
        VECTOR2 pos;
        VECTOR2 scale;
        VECTOR2 texPos;
        VECTOR2 texSize;
        float angle;
        VECTOR4 color;
    } param_ = {};

    // �����o�ϐ�
    int stageNum_ = 0;
    bool push_flg = false;

    float tutorial_icon_Alpha_ = 1.0f;// �`���[�g���A���̃A�C�R����
    float stage1_icon_Alpha_ = 1.0f;  // �X�e�[�W�P�̃A�C�R����
    VECTOR2 tutorial_icon_Scale_ = { 0.5f , 0.5f }; // �`���[�g���A���̃A�C�R���X�P�[��
    VECTOR2 stage1_icon_Scale_ = { 0.5f , 0.5f };   // �X�e�[�W�P�̃A�C�R���X�P�[��
    VECTOR2 tutorial_icon_Pos_ = { GameLib::window::getWidth() / 2 - (GameLib::window::getWidth() / 2) / 2 , GameLib::window::getHeight() / 2 };    //�`���[�g���A���̃A�C�R���ʒu
    VECTOR2 stage1_icon_Pos_ = { GameLib::window::getWidth() / 2 , GameLib::window::getHeight() / 2 };  //�X�e�[�W�P�̃A�C�R���ʒu
    VECTOR2 S_L_Fusuma_Pos_ = { 0,0 };  // �����̈ʒu
    VECTOR2 S_R_Fusuma_Pos_ = { 0,0 };  // �E���̈ʒu
    float Fusuma_timer_ = 0.0f;         // �����J���n�߂�܂ł̎���
    VECTOR2 shuriken_Pos_[10] = {};      //�藠���ʒu�̏�����
    float shuriken_Angle_ = 0;          //�藠���̊p�x�̏�����
    VECTOR2 title_icon_Scale_ = { 0.5f , 0.5f };   // �^�C�g���̃A�C�R���X�P�[��
    VECTOR2 title_icon_Pos_ = { GameLib::window::getWidth() / 2 - (GameLib::window::getWidth() / 2) / 2 , GameLib::window::getHeight() / 2 };    //�^�C�g���ւ̃A�C�R���ʒu
    float title_icon_Alpha_ = 1.0f;  // �^�C�g���̃A�C�R����
    bool title_push_flg_ = false;

    Param stagingShuriken_[1] = {};
};