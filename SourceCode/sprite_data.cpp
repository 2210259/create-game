//******************************************************************************
//
//
//		SPRITE_DATA
//
//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< �f�[�^ >---------------------------------------------------------------

#if 2
//******************************************************************************
// HACK:02 ����p�e�N�X�`���̓ǂݍ���
//------------------------------------------------------------------------------
/*
�m�F�j
    ����p�̃e�N�X�`����ǂݍ��ސݒ�����Ă��܂��B
*/
//******************************************************************************
#endif
// 2D�摜���[�h�f�[�^
LoadTexture loadTexture[] = {
    { TEXNO::PLAYER,        L"./Data/Images/player.png",        1U },// �v���C���[
    { TEXNO::MAP_BACK,      L"./Data/Maps/back_chip.png",       static_cast<UINT>(BG::LOOP_X * BG::LOOP_Y) }, // �}�b�v�w�i
    { TEXNO::MAP_TERRAIN,   L"./Data/Maps/terrain_chip.png",    static_cast<UINT>(BG::LOOP_X * BG::LOOP_Y) }, // �}�b�v�n�`
    { TEXNO::MAP_ITEM,      L"./Data/Maps/item_chip.png",       1U }, 
    { TEXNO::ENEMY0,        L"./Data/Images/enemy00.png",       1U },
    { TEXNO::ENEMY1,        L"./Data/Images/enemy01.png",       1U },
    { TEXNO::ENEMY5,        L"./Data/Images/enemy05.png",       1U },
    //HACK_02
    { TEXNO::WEAPON,        L"./Data/Images/weapon.png",        1U }, 
    { -1, nullptr }	// �I���t���O
};

//------< �}�N�� >--------------------------------------------------------------
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // �摜�̐^�񒆂����S
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // �摜�̑��������S

//------< �v���C���[ >----------------------------------------------------------
//�����
SpriteData sprPlayer_Up0 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 0, 128 * 0, 96, 128);
SpriteData sprPlayer_Up1 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 1, 128 * 0, 96, 128);
SpriteData sprPlayer_Up2 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 2, 128 * 0, 96, 128);

//�E����
SpriteData sprPlayer_Right0 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 0, 128 * 1, 96, 128);
SpriteData sprPlayer_Right1 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 1, 128 * 1, 96, 128);
SpriteData sprPlayer_Right2 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 2, 128 * 1, 96, 128);

//������
SpriteData sprPlayer_Down0 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 0, 128 * 2, 96, 128);
SpriteData sprPlayer_Down1 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 1, 128 * 2, 96, 128);
SpriteData sprPlayer_Down2 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 2, 128 * 2, 96, 128);

//������
SpriteData sprPlayer_Left0 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 0, 128 * 3, 96, 128);
SpriteData sprPlayer_Left1 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 1, 128 * 3, 96, 128);
SpriteData sprPlayer_Left2 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 2, 128 * 3, 96, 128);

//------< �A�C�e�� >-------------------------------------------------------------
SpriteData sprItemSword = SPRITE_CENTER(TEXNO::MAP_ITEM, 64 * 0, 64 * 0, 64, 64);
SpriteData sprItemKey   = SPRITE_CENTER(TEXNO::MAP_ITEM, 64 * 2, 64 * 0, 64, 64);
SpriteData sprItemOrb   = SPRITE_CENTER(TEXNO::MAP_ITEM, 64 * 4, 64 * 0, 64, 64);

//------< �G >------------------------------------------------------------------

//================================
//      �G0
//================================

//�����
SpriteData sprEnemy0_Up0 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 0, 128 * 0, 96, 128);
SpriteData sprEnemy0_Up1 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 1, 128 * 0, 96, 128);
SpriteData sprEnemy0_Up2 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 2, 128 * 0, 96, 128);

//�E����
SpriteData sprEnemy0_Right0 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 0, 128 * 1, 96, 128);
SpriteData sprEnemy0_Right1 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 1, 128 * 1, 96, 128);
SpriteData sprEnemy0_Right2 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 2, 128 * 1, 96, 128);

//������
SpriteData sprEnemy0_Down0 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 0, 128 * 2, 96, 128);
SpriteData sprEnemy0_Down1 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 1, 128 * 2, 96, 128);
SpriteData sprEnemy0_Down2 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 2, 128 * 2, 96, 128);

//������
SpriteData sprEnemy0_Left0 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 0, 128 * 3, 96, 128);
SpriteData sprEnemy0_Left1 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 1, 128 * 3, 96, 128);
SpriteData sprEnemy0_Left2 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 2, 128 * 3, 96, 128);

//================================
//      �G1
//================================

//�����
SpriteData sprEnemy1_Up0 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 0, 128 * 0, 96, 128);
SpriteData sprEnemy1_Up1 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 1, 128 * 0, 96, 128);
SpriteData sprEnemy1_Up2 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 2, 128 * 0, 96, 128);

//�E����
SpriteData sprEnemy1_Right0 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 0, 128 * 1, 96, 128);
SpriteData sprEnemy1_Right1 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 1, 128 * 1, 96, 128);
SpriteData sprEnemy1_Right2 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 2, 128 * 1, 96, 128);

//������
SpriteData sprEnemy1_Down0 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 0, 128 * 2, 96, 128);
SpriteData sprEnemy1_Down1 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 1, 128 * 2, 96, 128);
SpriteData sprEnemy1_Down2 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 2, 128 * 2, 96, 128);

//������
SpriteData sprEnemy1_Left0 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 0, 128 * 3, 96, 128);
SpriteData sprEnemy1_Left1 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 1, 128 * 3, 96, 128);
SpriteData sprEnemy1_Left2 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 2, 128 * 3, 96, 128);

//================================
//      �G5
//================================

//�����
SpriteData sprEnemy5_Up0 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 0, 128 * 0, 96, 128);
SpriteData sprEnemy5_Up1 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 1, 128 * 0, 96, 128);
SpriteData sprEnemy5_Up2 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 2, 128 * 0, 96, 128);

//�E����
SpriteData sprEnemy5_Right0 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 0, 128 * 1, 96, 128);
SpriteData sprEnemy5_Right1 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 1, 128 * 1, 96, 128);
SpriteData sprEnemy5_Right2 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 2, 128 * 1, 96, 128);

//������
SpriteData sprEnemy5_Down0 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 0, 128 * 2, 96, 128);
SpriteData sprEnemy5_Down1 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 1, 128 * 2, 96, 128);
SpriteData sprEnemy5_Down2 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 2, 128 * 2, 96, 128);

//������
SpriteData sprEnemy5_Left0 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 0, 128 * 3, 96, 128);
SpriteData sprEnemy5_Left1 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 1, 128 * 3, 96, 128);
SpriteData sprEnemy5_Left2 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 2, 128 * 3, 96, 128);

//------< ���� >----------------------------------------------------------------

#if 3
//******************************************************************************
// HACK:03 ����p�X�v���C�g�f�[�^�̒�`
//------------------------------------------------------------------------------
/*
�m�F�j
    ���L�ŕ���̃X�v���C�g�f�[�^�̒�`�����Ă��܂��B
*/
//******************************************************************************
#endif
//HACK_03
SpriteData sprWeapon_Sword = SPRITE_BOTTOM(TEXNO::WEAPON, 128 * 0, 0, 128, 128);
SpriteData sprWeapon_Katana = SPRITE_BOTTOM(TEXNO::WEAPON, 128 * 1, 0, 128, 128);
SpriteData sprWeapon_Axe = SPRITE_BOTTOM(TEXNO::WEAPON, 128 * 2, 0, 128, 128);
SpriteData sprWeapon_Spear = SPRITE_BOTTOM(TEXNO::WEAPON, 128 * 3, 0, 128, 128);
SpriteData sprWeapon_Shuriken = SPRITE_CENTER(TEXNO::WEAPON, 128 * 4, 0, 128, 128);

//------------------------------------------------------------------------------
#undef SPRITE_CENTER
#undef SPRITE_BOTTOM

//******************************************************************************
