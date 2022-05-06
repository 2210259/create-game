#pragma once
//******************************************************************************
//
//      bg.h
//
//******************************************************************************

//==============================================================================
//
//      BG�N���X
//
//==============================================================================

class BG
{
public:
    //------< �萔 >------------------------------------------------------------
    // TOOD:�t���X�N���[���̕\���ɕς���
    static const int WINDOW_W = 1280;                   // �E�C���h�E�̕�
    static const int WINDOW_H = 720;                    // �E�C���h�E�̍���
    static const int CLIENT_W = 1280;                   // �N���C�A���g�̈�̕�
    static const int CLIENT_H = 720;                    // �N���C�A���g�̈�̍���

    // static constexpr float CHIP_SIZE_F = static_cast<float>(CHIP_SIZE);
    static constexpr float WIDTH  = WINDOW_W;  // �}�b�v�̕�
    static constexpr float HEIGHT = WINDOW_H; // �}�b�v�̍���
    static constexpr float SCROLL_MERGIN_X = 240.f;     // ���̐��l����ʒ[�ɋ߂Â�����X�N���[������i���j
    static constexpr float SCROLL_MERGIN_Y = 160.f;     // ���̐��l����ʒ[�ɋ߂Â�����X�N���[������i�c�j
    // static constexpr float ADJUST_Y = 0.25f;            // �����蔻��ł̈ʒu�����p�i�c�j
    // static constexpr float ADJUST_X = 0.025f;           // �����蔻��ł̈ʒu�����p�i���j

private:

    //------< �ϐ� >------------------------------------------------------------
    VECTOR2 scroll;                                         // ���ݕ\������Ă��鍶��̒n�_�̍��W
    OBJ2D* player_;

public:
    BG();
    ~BG();

    // ������
    void init(OBJ2D* player);

    // �X�V
    void update();

    // �`��
    void drawBack(); //�w�i�`��

    // void drawObject();                                      // �I�u�W�F�N�g�`��
    // void drawTerrain();                                     // �n�`�`��
    
    // �X�N���[���ʒu�擾
    float getScrollX() { return scroll.x; }
    float getScrollY() { return scroll.y; }
    const VECTOR2& getScrollPos() { return scroll; }

private:
    // �N���A
    void clear();

    // �}�b�v�X�N���[���p
    void scrollMap();
};

//******************************************************************************
