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
    ENEMY0,       //�G1
    ENEMY1,       //�G2
    ENEMY2,       //�G3

    NUM
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


//================================
//      �G0
//================================

// ���ړ�
extern GameLib::SpriteData sprEnemy0_Left0;
extern GameLib::SpriteData sprEnemy0_Left1;

// �E�ړ�
extern GameLib::SpriteData sprEnemy0_Right0;
extern GameLib::SpriteData sprEnemy0_Right1;

// ���S��
extern GameLib::SpriteData sprEnemy0_Dead0;
extern GameLib::SpriteData sprEnemy0_Dead1;
extern GameLib::SpriteData sprEnemy0_Dead2;

//================================
//      �G1
//================================

// ���ړ�
extern GameLib::SpriteData sprEnemy1_Left0;
extern GameLib::SpriteData sprEnemy1_Left1;

// �E�ړ�
extern GameLib::SpriteData sprEnemy1_Right0;
extern GameLib::SpriteData sprEnemy1_Right1;

// ���S��
extern GameLib::SpriteData sprEnemy1_Dead0;
extern GameLib::SpriteData sprEnemy1_Dead1;
extern GameLib::SpriteData sprEnemy1_Dead2;

//================================
//      �G2
//================================

// ���ړ�
extern GameLib::SpriteData sprEnemy2_Left0;
extern GameLib::SpriteData sprEnemy2_Left1;

// �E�ړ�
extern GameLib::SpriteData sprEnemy2_Right0;
extern GameLib::SpriteData sprEnemy2_Right1;

// ���S��
extern GameLib::SpriteData sprEnemy2_Dead0;
extern GameLib::SpriteData sprEnemy2_Dead1;
extern GameLib::SpriteData sprEnemy2_Dead2;
extern GameLib::SpriteData sprEnemy2_Dead3;

//******************************************************************************
