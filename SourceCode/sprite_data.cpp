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
    { TEXNO::RESTART,       L"./Data/Images/restart.png",       1U },// "�Ē���"����
    { TEXNO::TOTITLE,       L"./Data/Images/to title.png",      1U },// "�����Ƃ��"����

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
SpriteData sprEnemy0_Idle0 = SPRITE_CENTER(TEXNO::ENEMY0, 128 * 0, 128 * 0, 128, 128);
// SpriteData sprEnemy0_Idle1 = SPRITE_CENTER(TEXNO::ENEMY0, 128 * 1, 128 * 0, 128, 128);

// ���S��
// SpriteData sprEnemy0_Dead0 = SPRITE_CENTER(TEXNO::ENEMY0, 128 * 0, 128 * 4, 128, 128);
// SpriteData sprEnemy0_Dead1 = SPRITE_CENTER(TEXNO::ENEMY0, 128 * 1, 128 * 4, 128, 128);
// SpriteData sprEnemy0_Dead2 = SPRITE_CENTER(TEXNO::ENEMY0, 128 * 2, 128 * 4, 128, 128);

//================================
//      �N�i�C
//================================

// �U��
SpriteData sprEnemy1_Idle0 = SPRITE_CENTER(TEXNO::ENEMY1, 128 * 0, 128 * 0, 128, 128);
// SpriteData sprEnemy1_Idle1 = SPRITE_CENTER(TEXNO::ENEMY0, 128 * 1, 128 * 0, 128, 128);

// ���S��
//SpriteData sprEnemy1_Dead0 = SPRITE_CENTER(TEXNO::ENEMY1, 128 * 0, 128 * 4, 128, 128);
//SpriteData sprEnemy1_Dead1 = SPRITE_CENTER(TEXNO::ENEMY1, 128 * 1, 128 * 4, 128, 128);
//SpriteData sprEnemy1_Dead2 = SPRITE_CENTER(TEXNO::ENEMY1, 128 * 2, 128 * 4, 128, 128);

//================================
//      �������m�[�c(��)
//================================

// �U��
SpriteData sprEnemy2_Idle0 = SPRITE_CENTER(TEXNO::ENEMY2, 128 * 0, 512 * 0, 128, 512);
// SpriteData sprEnemy2_Idle1 = SPRITE_CENTER(TEXNO::ENEMY0, 128 * 1, 128 * 0, 128, 128);

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
// SpriteData sprEnemy3_Idle1 = SPRITE_CENTER(TEXNO::ENEMY3, 128 * 1, 128 * 0, 128, 128);

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
// SpriteData sprEnemy4_Idle1 = SPRITE_CENTER(TEXNO::ENEMY0, 128 * 1, 128 * 0, 128, 128);

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

//================================
//           ����
//================================

SpriteData sprRestart = SPRITE_CENTER(TEXNO::RESTART, 0, 0, 600, 300);
SpriteData sprTotitle = SPRITE_CENTER(TEXNO::TOTITLE, 0, 0, 600, 300);

//------------------------------------------------------------------------------
#undef SPRITE_CENTER
#undef SPRITE_BOTTOM

//******************************************************************************
