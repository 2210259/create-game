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

// ラベル定義
enum TEXNO
{
    // ゲーム
    PLAYER,
    ENEMY0,       //敵1
    ENEMY1,       //敵2
    ENEMY2,       //敵3

    NUM
};

extern GameLib::LoadTexture loadTexture[];

//------< プレイヤー >----------------------------------------------------------

// 待機
extern GameLib::SpriteData sprPlayer_Idle0;
extern GameLib::SpriteData sprPlayer_Idle1;
 
//上向き
extern GameLib::SpriteData sprPlayer_Attack_U0;
extern GameLib::SpriteData sprPlayer_Attack_U1;
extern GameLib::SpriteData sprPlayer_Attack_U2;

//右向き
extern GameLib::SpriteData sprPlayer_Attack_R0;
extern GameLib::SpriteData sprPlayer_Attack_R1;
extern GameLib::SpriteData sprPlayer_Attack_R2;

//下向き
extern GameLib::SpriteData sprPlayer_Down0;
extern GameLib::SpriteData sprPlayer_Down1;
extern GameLib::SpriteData sprPlayer_Down2;

//左向き
extern GameLib::SpriteData sprPlayer_Attack_L0;
extern GameLib::SpriteData sprPlayer_Attack_L1;
extern GameLib::SpriteData sprPlayer_Attack_L2;

//================================
//      敵0
//================================

// 左移動
extern GameLib::SpriteData sprEnemy0_Left0;
extern GameLib::SpriteData sprEnemy0_Left1;

// 右移動
extern GameLib::SpriteData sprEnemy0_Right0;
extern GameLib::SpriteData sprEnemy0_Right1;

// 死亡時
extern GameLib::SpriteData sprEnemy0_Dead0;
extern GameLib::SpriteData sprEnemy0_Dead1;
extern GameLib::SpriteData sprEnemy0_Dead2;

//================================
//      敵1
//================================

// 左移動
extern GameLib::SpriteData sprEnemy1_Left0;
extern GameLib::SpriteData sprEnemy1_Left1;

// 右移動
extern GameLib::SpriteData sprEnemy1_Right0;
extern GameLib::SpriteData sprEnemy1_Right1;

// 死亡時
extern GameLib::SpriteData sprEnemy1_Dead0;
extern GameLib::SpriteData sprEnemy1_Dead1;
extern GameLib::SpriteData sprEnemy1_Dead2;

//================================
//      敵2
//================================

// 左移動
extern GameLib::SpriteData sprEnemy2_Left0;
extern GameLib::SpriteData sprEnemy2_Left1;

// 右移動
extern GameLib::SpriteData sprEnemy2_Right0;
extern GameLib::SpriteData sprEnemy2_Right1;

// 死亡時
extern GameLib::SpriteData sprEnemy2_Dead0;
extern GameLib::SpriteData sprEnemy2_Dead1;
extern GameLib::SpriteData sprEnemy2_Dead2;
extern GameLib::SpriteData sprEnemy2_Dead3;

//******************************************************************************
