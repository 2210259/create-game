#pragma once

//******************************************************************************
//
//
//		SPRITE_DATA
//
//
//******************************************************************************

#include "../GameLib/texture.h"

#if 1
//******************************************************************************
// HACK:01 ����p�e�N�X�`���̃��x�����`����
//------------------------------------------------------------------------------
/*
�m�F�j
    ����p�e�N�X�`���̃��x�����`���Ă��܂��B
*/
//******************************************************************************
#endif
// ���x����`
enum TEXNO
{
    // �Q�[��
    PLAYER,
    MAP_BACK,
    MAP_TERRAIN,
    MAP_ITEM, 
    ENEMY0,
    ENEMY1,
    ENEMY5,
    //HACK_01
    WEAPON, 
};

extern GameLib::LoadTexture loadTexture[];

//------< �v���C���[ >----------------------------------------------------------
//�����
extern GameLib::SpriteData sprPlayer_Up0;
extern GameLib::SpriteData sprPlayer_Up1;
extern GameLib::SpriteData sprPlayer_Up2;

//�E����
extern GameLib::SpriteData sprPlayer_Right0;
extern GameLib::SpriteData sprPlayer_Right1;
extern GameLib::SpriteData sprPlayer_Right2;

//������
extern GameLib::SpriteData sprPlayer_Down0;
extern GameLib::SpriteData sprPlayer_Down1;
extern GameLib::SpriteData sprPlayer_Down2;

//������
extern GameLib::SpriteData sprPlayer_Left0;
extern GameLib::SpriteData sprPlayer_Left1;
extern GameLib::SpriteData sprPlayer_Left2;

//------< �A�C�e�� >-------------------------------------------------------------
extern GameLib::SpriteData sprItemSword;
extern GameLib::SpriteData sprItemKey;
extern GameLib::SpriteData sprItemOrb;

//------< �G >------------------------------------------------------------------

//================================
//      �G0
//================================

//�����
extern GameLib::SpriteData sprEnemy0_Up0;
extern GameLib::SpriteData sprEnemy0_Up1;
extern GameLib::SpriteData sprEnemy0_Up2;

//�E����
extern GameLib::SpriteData sprEnemy0_Right0;
extern GameLib::SpriteData sprEnemy0_Right1;
extern GameLib::SpriteData sprEnemy0_Right2;

//������
extern GameLib::SpriteData sprEnemy0_Down0;
extern GameLib::SpriteData sprEnemy0_Down1;
extern GameLib::SpriteData sprEnemy0_Down2;

//������
extern GameLib::SpriteData sprEnemy0_Left0;
extern GameLib::SpriteData sprEnemy0_Left1;
extern GameLib::SpriteData sprEnemy0_Left2;

//================================
//      �G1
//================================

//�����
extern GameLib::SpriteData sprEnemy1_Up0;
extern GameLib::SpriteData sprEnemy1_Up1;
extern GameLib::SpriteData sprEnemy1_Up2;

//�E����
extern GameLib::SpriteData sprEnemy1_Right0;
extern GameLib::SpriteData sprEnemy1_Right1;
extern GameLib::SpriteData sprEnemy1_Right2;

//������
extern GameLib::SpriteData sprEnemy1_Down0;
extern GameLib::SpriteData sprEnemy1_Down1;
extern GameLib::SpriteData sprEnemy1_Down2;

//������
extern GameLib::SpriteData sprEnemy1_Left0;
extern GameLib::SpriteData sprEnemy1_Left1;
extern GameLib::SpriteData sprEnemy1_Left2;

//================================
//      �G5
//================================

//�����
extern GameLib::SpriteData sprEnemy5_Up0;
extern GameLib::SpriteData sprEnemy5_Up1;
extern GameLib::SpriteData sprEnemy5_Up2;

//�E����
extern GameLib::SpriteData sprEnemy5_Right0;
extern GameLib::SpriteData sprEnemy5_Right1;
extern GameLib::SpriteData sprEnemy5_Right2;

//������
extern GameLib::SpriteData sprEnemy5_Down0;
extern GameLib::SpriteData sprEnemy5_Down1;
extern GameLib::SpriteData sprEnemy5_Down2;

//������
extern GameLib::SpriteData sprEnemy5_Left0;
extern GameLib::SpriteData sprEnemy5_Left1;
extern GameLib::SpriteData sprEnemy5_Left2;

//------< ���� >----------------------------------------------------------------

#if 4
//******************************************************************************
// HACK:04 ����p�X�v���C�g�f�[�^�̐錾
//------------------------------------------------------------------------------
/*
�m�F�j
    ���L�ŕ���̃X�v���C�g�f�[�^��extern�錾���s�Ȃ��Ă��܂��B
*/
//******************************************************************************
#endif
//HACK_04
extern GameLib::SpriteData sprWeapon_Sword;
extern GameLib::SpriteData sprWeapon_Katana;
extern GameLib::SpriteData sprWeapon_Axe;
extern GameLib::SpriteData sprWeapon_Spear;
extern GameLib::SpriteData sprWeapon_Shuriken;

//******************************************************************************

