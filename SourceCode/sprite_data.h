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
    ENEMY2_1,     // 敵3_1
    ENEMY2_2,     // 敵3_2
    ENEMY2_DEAD,  // 敵3 死亡時
    ENEMY3_1,     // 敵4_1
    ENEMY3_2,     // 敵4_2
    ENEMY3_DEAD,  // 敵4 死亡時
    EFFECT,       // エフェクト
    RESTART,      // "再挑戦"の文字
    TOTITLE,      // "たいとるへ"の文字
    CONTINUE,     // "再開"の文字
    MAP_BACK,     // 背景
    T_START,      // "いざ！！"
    T_END,        // "そこまで！！"
    T_FULLCOMBO,  // "あっぱれ"
    L_FUSUMA,     // ゲーム遷移の画像
    R_FUSUMA,     // ゲーム遷移の画像
    HP_BAR,       // HPバー
    TUTORIAL0,    // チュートリアル操作説明
    TUTORIAL1,    // チュートリアル普通ノーツ
    TUTORIAL2,    // チュートリアル長押しノーツ
    TUTORIAL3,    // チュートリアル連打ノーツ
    TUTORIAL4,    // チュートリアルポーズノーツ

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
extern GameLib::SpriteData sprEnemy2_1_Idle0;

//================================
//      長押しノーツ(横)
//================================

// 攻撃
extern GameLib::SpriteData sprEnemy2_2_Idle0;

// 死亡時(上横共通)
extern GameLib::SpriteData sprEnemy2_Dead0;
extern GameLib::SpriteData sprEnemy2_Dead1;

//================================
//      連打ノーツ(上)
//================================

// 攻撃
extern GameLib::SpriteData sprEnemy3_1_Idle0;
 
//================================
//      連打ノーツ(横)
//================================

// 攻撃
extern GameLib::SpriteData sprEnemy3_2_Idle0;

// 死亡時(上横共通)
extern GameLib::SpriteData sprEnemy3_Dead0;
extern GameLib::SpriteData sprEnemy3_Dead1;

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
extern GameLib::SpriteData sprTextStart;
extern GameLib::SpriteData sprTextEnd;

//******************************************************************************