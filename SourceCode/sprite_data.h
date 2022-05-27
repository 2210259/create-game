#pragma once

//******************************************************************************
//
//
//		sprite_data.h
//
//
//******************************************************************************

#include "../GameLib/texture.h"
#include "../GameLib/obj2d_data.h"

// ���x����`
enum TEXNO
{
    // �Q�[��
    PLAYER,
    ENEMY0,       // �G1
    ENEMY1,       // �G2
    ENEMY2_1,     // �G3_1
    ENEMY2_2,     // �G3_2
    ENEMY2_DEAD,  // �G3 ���S��
    ENEMY3_1,     // �G4_1
    ENEMY3_2,     // �G4_2
    ENEMY3_DEAD,  // �G4 ���S��
    EFFECT,       // �G�t�F�N�g
    RESTART,      // "�Ē���"�̕���
    TOTITLE,      // "�����Ƃ��"�̕���
    CONTINUE,     // "�ĊJ"�̕���
    MAP_BACK,     // �w�i
    T_START,      // "�����I�I"
    T_END,        // "�����܂ŁI�I"
    T_FULLCOMBO,  // "�����ς�"
    L_FUSUMA,     // �Q�[���J�ڂ̉摜
    R_FUSUMA,     // �Q�[���J�ڂ̉摜
    HP_BAR,       // HP�o�[
    TUTORIAL0,    // �`���[�g���A���������
    TUTORIAL1,    // �`���[�g���A�����ʃm�[�c
    TUTORIAL2,    // �`���[�g���A���������m�[�c
    TUTORIAL3,    // �`���[�g���A���A�Ńm�[�c
    TUTORIAL4,    // �`���[�g���A���|�[�Y�m�[�c

    NUM
};

extern GameLib::LoadTexture loadTexture[];

//------< �v���C���[ >----------------------------------------------------------

// �ҋ@
extern GameLib::SpriteData sprPlayer_Idle0;
extern GameLib::SpriteData sprPlayer_Idle1;
 
//�����
extern GameLib::SpriteData sprPlayer_Attack_U0;
extern GameLib::SpriteData sprPlayer_Attack_U1;
extern GameLib::SpriteData sprPlayer_Attack_U2;

//�E����
extern GameLib::SpriteData sprPlayer_Attack_R0;
extern GameLib::SpriteData sprPlayer_Attack_R1;
extern GameLib::SpriteData sprPlayer_Attack_R2;

//������
extern GameLib::SpriteData sprPlayer_Down0;
extern GameLib::SpriteData sprPlayer_Down1;
extern GameLib::SpriteData sprPlayer_Down2;

//������
extern GameLib::SpriteData sprPlayer_Attack_L0;
extern GameLib::SpriteData sprPlayer_Attack_L1;
extern GameLib::SpriteData sprPlayer_Attack_L2;

//================================
//     �藠��
//================================
// �U��
extern GameLib::SpriteData sprEnemy0_Idle0;

// ���S��
extern GameLib::SpriteData sprEnemy0_Dead0;
extern GameLib::SpriteData sprEnemy0_Dead1;
extern GameLib::SpriteData sprEnemy0_Dead2;

//================================
//      �N�i�C
//================================

// �U��
extern GameLib::SpriteData sprEnemy1_Idle0;

// ���S��
extern GameLib::SpriteData sprEnemy1_Dead0;
extern GameLib::SpriteData sprEnemy1_Dead1;
extern GameLib::SpriteData sprEnemy1_Dead2;

//================================
//      �������m�[�c(��)
//================================

// �U��
extern GameLib::SpriteData sprEnemy2_1_Idle0;

//================================
//      �������m�[�c(��)
//================================

// �U��
extern GameLib::SpriteData sprEnemy2_2_Idle0;

// ���S��(�㉡����)
extern GameLib::SpriteData sprEnemy2_Dead0;
extern GameLib::SpriteData sprEnemy2_Dead1;

//================================
//      �A�Ńm�[�c(��)
//================================

// �U��
extern GameLib::SpriteData sprEnemy3_1_Idle0;
 
//================================
//      �A�Ńm�[�c(��)
//================================

// �U��
extern GameLib::SpriteData sprEnemy3_2_Idle0;

// ���S��(�㉡����)
extern GameLib::SpriteData sprEnemy3_Dead0;
extern GameLib::SpriteData sprEnemy3_Dead1;

//------< �G�t�F�N�g >------------------------------------------------------------------

//================================
//      Good�G�t�F�N�g
//================================

extern GameLib::SpriteData sprEffect0_Idle0;
extern GameLib::SpriteData sprEffect0_Idle1;
extern GameLib::SpriteData sprEffect0_Idle2;

//================================
//      Great�G�t�F�N�g
//================================

extern GameLib::SpriteData sprEffect1_Idle0;
extern GameLib::SpriteData sprEffect1_Idle1;
extern GameLib::SpriteData sprEffect1_Idle2;

//================================
//      Perfect�G�t�F�N�g
//================================

extern GameLib::SpriteData sprEffect2_Idle0;
extern GameLib::SpriteData sprEffect2_Idle1;
extern GameLib::SpriteData sprEffect2_Idle2;

//================================
//          ����
//================================

extern GameLib::SpriteData sprRestart;
extern GameLib::SpriteData sprTotitle;
extern GameLib::SpriteData sprTextStart;
extern GameLib::SpriteData sprTextEnd;

//******************************************************************************