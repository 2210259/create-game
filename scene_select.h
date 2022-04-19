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
        NUM,
    };

    // �g�p����X�v���C�g�f�[�^
    GameLib::SpriteData sprStar_ = SPRITE_CENTER(static_cast<INT>(TEXNO::STAR), 0, 0, 500, 500);

private:
    // �t�F�[�h�A�E�g�p�^�C�}�[
    float fadeOutTimer_ = 0.0f;

    // �����o�ϐ�
    VECTOR2 starScale_ = { 0.0f, 0.0f };
    float   starAngle_ = 0.0f;
    int stageNum_ = 0;
};