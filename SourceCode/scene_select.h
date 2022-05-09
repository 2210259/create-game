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

private:
    Select() {}
    ~Select() {}

    Select(const Select&) = delete;                 // �R�s�[�R���X�g���N�^�[
    Select& operator=(const Select&) = delete;      // �R�s�[������Z�q
    Select(Select&&) noexcept = delete;             // ���[�u�R���X�g���N�^�[
    Select& operator=(Select&&) noexcept = delete;  // ���[�u������Z�q

public:
    // �g�p����e�N�X�`���̃��x��
    enum class TEXNO {
        STAR,
        BACK,
        TUTORIAL,
        STAGE1,
        STAGE2,
        NUM,
    };

    // �g�p����X�v���C�g�f�[�^
    GameLib::SpriteData sprStar_ = SPRITE_CENTER(static_cast<INT>(TEXNO::STAR), 0, 0, 500, 500);
    GameLib::SpriteData sprBack_ = SPRITE_CENTER(static_cast<INT>(TEXNO::BACK), 0, 0, 1920, 1080);
    GameLib::SpriteData sprTutorial_ = SPRITE_CENTER(static_cast<INT>(TEXNO::TUTORIAL), 0, 0, 700, 700);
    GameLib::SpriteData sprStage1_ = SPRITE_CENTER(static_cast<INT>(TEXNO::STAGE1), 0, 0, 700, 700);
    GameLib::SpriteData sprStage2_ = SPRITE_CENTER(static_cast<INT>(TEXNO::STAGE2), 0, 0, 700, 700);


private:
    // �t�F�[�h�A�E�g�p�^�C�}�[
    float fadeOutTimer_ = 0.0f;

    // �����o�ϐ�
    VECTOR2 starScale_ = { 0.0f, 0.0f };
    float   starAngle_ = 0.0f;
    int stageNum_ = 0;
    float tutorialAlpha_ = 1.0f;
    float stage1Alpha_ = 1.0f;
    float stage2Alpha_ = 1.0f;
    VECTOR2 tutorialScale_ = { 0.5f , 0.5f };
    VECTOR2 stage1Scale_ = { 0.5f , 0.5f };
    VECTOR2 stage2Scale_ = { 0.5f , 0.5f };

};