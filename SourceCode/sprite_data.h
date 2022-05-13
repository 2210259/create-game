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
    ENEMY0,       // 敵1
    ENEMY1,       // 敵2
    ENEMY2,       // 敵3
    ENEMY3,       // 敵4
    ENEMY4,       // 敵5
    ENEMY5,       // 敵6
    EFFECT,       // エフェクト
    RESTART,      // "再挑戦"の文字
    TOTITLE,      // "たいとるへ"の文字
    MAP_BACK,     // 背景
    T_END,        // "閉幕！！"
    T_FULLCOMBO,  // "フルコンボ"
    L_FUSUMA,     // ゲーム遷移の画像
    R_FUSUMA,     // ゲーム遷移の画像

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
//     手裏剣
//================================
// 攻撃
extern GameLib::SpriteData sprEnemy0_Idle0;

// 死亡時
extern GameLib::SpriteData sprEnemy0_Dead0;
extern GameLib::SpriteData sprEnemy0_Dead1;
extern GameLib::SpriteData sprEnemy0_Dead2;

//================================
//      クナイ
//================================

// 攻撃
extern GameLib::SpriteData sprEnemy1_Idle0;

// 死亡時
extern GameLib::SpriteData sprEnemy1_Dead0;
extern GameLib::SpriteData sprEnemy1_Dead1;
extern GameLib::SpriteData sprEnemy1_Dead2;

//================================
//      長押しノーツ(上)
//================================

// 攻撃
extern GameLib::SpriteData sprEnemy2_Idle0;

// 死亡時
extern GameLib::SpriteData sprEnemy2_Dead0;
extern GameLib::SpriteData sprEnemy2_Dead1;
extern GameLib::SpriteData sprEnemy2_Dead2;
extern GameLib::SpriteData sprEnemy2_Dead3;

//================================
//      長押しノーツ(横)
//================================

// 攻撃
extern GameLib::SpriteData sprEnemy3_Idle0;

// 死亡時
// extern GameLib::SpriteData sprEnemy3_Dead0;
// extern GameLib::SpriteData sprEnemy3_Dead1;
// extern GameLib::SpriteData sprEnemy3_Dead2;
// extern GameLib::SpriteData sprEnemy3_Dead3;

//================================
//      連打ノーツ(上)
//================================

// 攻撃
extern GameLib::SpriteData sprEnemy4_Idle0;
 
// 死亡時
// extern GameLib::SpriteData sprEnemy4_Dead0;
// extern GameLib::SpriteData sprEnemy4_Dead1;
// extern GameLib::SpriteData sprEnemy4_Dead2;
// extern GameLib::SpriteData sprEnemy4_Dead3;

//================================
//      連打ノーツ(横)
//================================

// 攻撃
extern GameLib::SpriteData sprEnemy5_Idle0;

// 死亡時
// extern GameLib::SpriteData sprEnemy4_Dead0;
// extern GameLib::SpriteData sprEnemy4_Dead1;
// extern GameLib::SpriteData sprEnemy4_Dead2;
// extern GameLib::SpriteData sprEnemy4_Dead3;

//------< エフェクト >------------------------------------------------------------------

//================================
//      Goodエフェクト
//================================

extern GameLib::SpriteData sprEffect0_Idle0;
extern GameLib::SpriteData sprEffect0_Idle1;
extern GameLib::SpriteData sprEffect0_Idle2;

//================================
//      Greatエフェクト
//================================

extern GameLib::SpriteData sprEffect1_Idle0;
extern GameLib::SpriteData sprEffect1_Idle1;
extern GameLib::SpriteData sprEffect1_Idle2;

//================================
//      Perfectエフェクト
//================================

extern GameLib::SpriteData sprEffect2_Idle0;
extern GameLib::SpriteData sprEffect2_Idle1;
extern GameLib::SpriteData sprEffect2_Idle2;

//================================
//          文字
//================================

extern GameLib::SpriteData sprRestart;
extern GameLib::SpriteData sprTotitle;
extern GameLib::SpriteData sprTextEnd;

//******************************************************************************
