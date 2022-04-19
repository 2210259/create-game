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
//上歩き
extern GameLib::SpriteData sprPlayer_Up0;
extern GameLib::SpriteData sprPlayer_Up1;
extern GameLib::SpriteData sprPlayer_Up2;

//右歩き
extern GameLib::SpriteData sprPlayer_Right0;
extern GameLib::SpriteData sprPlayer_Right1;
extern GameLib::SpriteData sprPlayer_Right2;

//下歩き
extern GameLib::SpriteData sprPlayer_Down0;
extern GameLib::SpriteData sprPlayer_Down1;
extern GameLib::SpriteData sprPlayer_Down2;

//左歩き
extern GameLib::SpriteData sprPlayer_Left0;
extern GameLib::SpriteData sprPlayer_Left1;
extern GameLib::SpriteData sprPlayer_Left2;


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
