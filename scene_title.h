#pragma once
//******************************************************************************
//
//      scene_title.h
//
//******************************************************************************

#include "scene.h"
#include "../GameLib/obj2d_data.h"

class Title : public Scene
{
private:
    static Title instance_;

public:
    // �C���X�^���X�̎擾
    static Title* instance() { return &instance_; }

    void init() override;
    void deinit() override;
    void update() override;
    void draw() override;

private:
    Title() {}
    ~Title() {}

    Title(const Title&) = delete;                 // �R�s�[�R���X�g���N�^�[
    Title& operator=(const Title&) = delete;      // �R�s�[������Z�q
    Title(Title&&) noexcept = delete;             // ���[�u�R���X�g���N�^�[
    Title& operator=(Title&&) noexcept = delete;  // ���[�u������Z�q

public:
    // �g�p����e�N�X�`���̃��x��
    enum class TEXNO {
        STAR,
        NUM,
    };

    // �g�p����X�v���C�g�f�[�^
    GameLib::SpriteData sprStar_ = SPRITE_CENTER(static_cast<INT>(TEXNO::STAR), 0, 0, 500, 500);

    // �t�F�[�h�A�E�g�p�^�C�}�[
    float fadeOutTimer_ = 0.0f;

    // �ϐ�
    VECTOR2 starScale_ = { 0.0f, 0.0f };
    float starAngle_ = 0.0f;
};
