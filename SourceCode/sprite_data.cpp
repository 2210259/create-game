//******************************************************************************
//
//
//		sprite_data.cpp
//
//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< �f�[�^ >---------------------------------------------------------------
// 2D�摜���[�h�f�[�^
LoadTexture loadTexture[] = {
    { TEXNO::PLAYER,        L"./Data/Images/player.png",        1U },// �v���C���[
    { TEXNO::ENEMY0,        L"./Data/Images/no-tsu01.png",      1U },// �m�[�c
    { TEXNO::ENEMY1,        L"./Data/Images/no-tsu02.png",      1U },// �m�[�c
    { TEXNO::ENEMY2,        L"./Data/Images/no-tsu03.png",      1U },// �m�[�c
    { TEXNO::ENEMY3,        L"./Data/Images/no-tsu04.png",      1U },// �m�[�c
    { TEXNO::ENEMY4,        L"./Data/Images/no-tsu05.png",      1U },// �m�[�c
    { TEXNO::ENEMY5,        L"./Data/Images/no-tsu06.png",      1U },// �m�[�c
    { TEXNO::EFFECT,        L"./Data/Images/effect.png",        1U },// �G�t�F�N�g
    { TEXNO::RESTART,       L"./Data/Images/restart.png",       1U },// "�Ē���"����
    { TEXNO::TOTITLE,       L"./Data/Images/to title.png",      1U },// "�����Ƃ��"����
    { TEXNO::MAP_BACK,      L"./Data/Images/background.png",    1U },// �w�i
    { TEXNO::T_END,         L"./Data/Images/textEnd.png",       1U },// "���I�I"
    { TEXNO::T_FULLCOMBO,   L"./Data/Images/textFullCombo.png", 1U },// "�t���R���{"
    { TEXNO::L_FUSUMA,      L"./Data/Images/L_fusuma.png",      1U },// ����
    { TEXNO::R_FUSUMA,      L"./Data/Images/R_fusuma.png",      1U },// �E��

    { -1, nullptr }	// �I���t���O
};

//------< �}�N�� >--------------------------------------------------------------
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // �摜�̐^�񒆂����S
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // �摜�̑��������S

//------< �v���C���[ >---------------------------------------------------------

// �ҋ@
SpriteData sprPlayer_Idle0 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 0, 150 * 0, 150, 150);
SpriteData sprPlayer_Idle1 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 1, 150 * 0, 150, 150);

// ���U��
SpriteData sprPlayer_Attack_L0 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 0, 150 * 1, 150, 150);
SpriteData sprPlayer_Attack_L1 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 1, 150 * 1, 150, 150);
SpriteData sprPlayer_Attack_L2 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 2, 150 * 1, 150, 150);

// �E�U��
SpriteData sprPlayer_Attack_R0 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 0, 150 * 2, 150, 150);
SpriteData sprPlayer_Attack_R1 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 1, 150 * 2, 150, 150);
SpriteData sprPlayer_Attack_R2 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 2, 150 * 2, 150, 150);

// ��U��
SpriteData sprPlayer_Attack_U0 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 0, 150 * 3, 150, 150);
SpriteData sprPlayer_Attack_U1 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 1, 150 * 3, 150, 150);
SpriteData sprPlayer_Attack_U2 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 2, 150 * 3, 150, 150);

// ���U��
// SpriteData sprPlayer_Down0 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 0, 150 * 2, 150, 150);
// SpriteData sprPlayer_Down1 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 1, 150 * 2, 150, 150);
// SpriteData sprPlayer_Down2 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 2, 150 * 2, 150, 150);

//------< �G >------------------------------------------------------------------

//================================
//      �藠��
//================================
// �U��
SpriteData sprEnemy0_Idle0 = SPRITE_CENTER(TEXNO::ENEMY0, 150 * 0, 150 * 0, 150, 150);

// ���S��
SpriteData sprEnemy0_Dead0 = SPRITE_CENTER(TEXNO::ENEMY0, 150 * 1, 150 * 0, 150, 150);
SpriteData sprEnemy0_Dead1 = SPRITE_CENTER(TEXNO::ENEMY0, 150 * 2, 150 * 0, 150, 150);
SpriteData sprEnemy0_Dead2 = SPRITE_CENTER(TEXNO::ENEMY0, 150 * 3, 150 * 0, 150, 150);

//================================
//      �N�i�C
//================================

// �U��
SpriteData sprEnemy1_Idle0 = SPRITE_CENTER(TEXNO::ENEMY1, 150 * 0, 150 * 0, 150, 150);

// ���S��
SpriteData sprEnemy1_Dead0 = SPRITE_CENTER(TEXNO::ENEMY1, 150 * 1, 150 * 0, 150, 150);
SpriteData sprEnemy1_Dead1 = SPRITE_CENTER(TEXNO::ENEMY1, 150 * 2, 150 * 0, 150, 150);
SpriteData sprEnemy1_Dead2 = SPRITE_CENTER(TEXNO::ENEMY1, 150 * 3, 150 * 0, 150, 150);

//================================
//      �������m�[�c(��)
//================================

// �U��
SpriteData sprEnemy2_Idle0 = SPRITE_CENTER(TEXNO::ENEMY2, 128 * 0, 512 * 0, 128, 512);

// ���S��
//SpriteData sprEnemy2_Dead0 = SPRITE_CENTER(TEXNO::ENEMY2, 250 * 0, 650 * 4, 250, 650);
//SpriteData sprEnemy2_Dead1 = SPRITE_CENTER(TEXNO::ENEMY2, 250 * 1, 650 * 4, 250, 650);
//SpriteData sprEnemy2_Dead2 = SPRITE_CENTER(TEXNO::ENEMY2, 250 * 2, 650 * 4, 250, 650);
//SpriteData sprEnemy2_Dead3 = SPRITE_CENTER(TEXNO::ENEMY2, 250 * 3, 650 * 4, 250, 650);

//================================
//      �������m�[�c(��)
//================================

// �U��
SpriteData sprEnemy3_Idle0 = SPRITE_CENTER(TEXNO::ENEMY3, 128 * 0, 128 * 0, 512, 128);

// ���S��
//SpriteData sprEnemy3_Dead0 = SPRITE_CENTER(TEXNO::ENEMY3, 250 * 0, 650 * 4, 250, 650);
//SpriteData sprEnemy3_Dead1 = SPRITE_CENTER(TEXNO::ENEMY3, 250 * 1, 650 * 4, 250, 650);
//SpriteData sprEnemy3_Dead2 = SPRITE_CENTER(TEXNO::ENEMY3, 250 * 2, 650 * 4, 250, 650);
//SpriteData sprEnemy3_Dead3 = SPRITE_CENTER(TEXNO::ENEMY3, 250 * 3, 650 * 4, 250, 650);

//================================
//      �A�Ńm�[�c(��)
//================================

// �U��
SpriteData sprEnemy4_Idle0 = SPRITE_CENTER(TEXNO::ENEMY4, 128 * 0, 128 * 0, 128, 512);

// ���S��
//SpriteData sprEnemy4_Dead0 = SPRITE_CENTER(TEXNO::ENEMY4, 250 * 0, 650 * 4, 250, 650);
//SpriteData sprEnemy4_Dead1 = SPRITE_CENTER(TEXNO::ENEMY4, 250 * 1, 650 * 4, 250, 650);
//SpriteData sprEnemy4_Dead2 = SPRITE_CENTER(TEXNO::ENEMY4, 250 * 2, 650 * 4, 250, 650);
//SpriteData sprEnemy4_Dead3 = SPRITE_CENTER(TEXNO::ENEMY4, 250 * 3, 650 * 4, 250, 650);

//================================
//      �A�Ńm�[�c(��)
//================================

// �U��
SpriteData sprEnemy5_Idle0 = SPRITE_CENTER(TEXNO::ENEMY5, 128 * 0, 128 * 0, 512, 128);
// SpriteData sprEnemy4_Idle1 = SPRITE_CENTER(TEXNO::ENEMY0, 128 * 1, 128 * 0, 128, 128);

// ���S��
//SpriteData sprEnemy4_Dead0 = SPRITE_CENTER(TEXNO::ENEMY4, 250 * 0, 650 * 4, 250, 650);
//SpriteData sprEnemy4_Dead1 = SPRITE_CENTER(TEXNO::ENEMY4, 250 * 1, 650 * 4, 250, 650);
//SpriteData sprEnemy4_Dead2 = SPRITE_CENTER(TEXNO::ENEMY4, 250 * 2, 650 * 4, 250, 650);
//SpriteData sprEnemy4_Dead3 = SPRITE_CENTER(TEXNO::ENEMY4, 250 * 3, 650 * 4, 250, 650);

//------< �G�t�F�N�g >------------------------------------------------------------------

//================================
//      Good�G�t�F�N�g
//================================

SpriteData sprEffect0_Idle0 = SPRITE_CENTER(TEXNO::EFFECT, 150 * 0, 150 * 0, 150, 150);
SpriteData sprEffect0_Idle1 = SPRITE_CENTER(TEXNO::EFFECT, 150 * 1, 150 * 0, 150, 150);
SpriteData sprEffect0_Idle2 = SPRITE_CENTER(TEXNO::EFFECT, 150 * 2, 150 * 0, 150, 150);

//================================
//      Great�G�t�F�N�g
//================================

SpriteData sprEffect1_Idle0 = SPRITE_CENTER(TEXNO::EFFECT, 150 * 0, 150 * 1, 150, 150);
SpriteData sprEffect1_Idle1 = SPRITE_CENTER(TEXNO::EFFECT, 150 * 1, 150 * 1, 150, 150);
SpriteData sprEffect1_Idle2 = SPRITE_CENTER(TEXNO::EFFECT, 150 * 2, 150 * 1, 150, 150);

//================================
//      Perfect�G�t�F�N�g
//================================

SpriteData sprEffect2_Idle0 = SPRITE_CENTER(TEXNO::EFFECT, 150 * 0, 150 * 2, 150, 150);
SpriteData sprEffect2_Idle1 = SPRITE_CENTER(TEXNO::EFFECT, 150 * 1, 150 * 2, 150, 150);
SpriteData sprEffect2_Idle2 = SPRITE_CENTER(TEXNO::EFFECT, 150 * 2, 150 * 2, 150, 150);

//================================
//           ����
//================================

SpriteData sprRestart = SPRITE_CENTER(TEXNO::RESTART, 0, 0, 600, 300);
SpriteData sprTotitle = SPRITE_CENTER(TEXNO::TOTITLE, 0, 0, 600, 300);
SpriteData sprT_End   = SPRITE_CENTER(TEXNO::T_END, 0, 0, 350,  94);
SpriteData sprT_FullCombo = SPRITE_CENTER(TEXNO::T_FULLCOMBO, 0, 0, 782, 94);

//------------------------------------------------------------------------------
#undef SPRITE_CENTER
#undef SPRITE_BOTTOM

//******************************************************************************
