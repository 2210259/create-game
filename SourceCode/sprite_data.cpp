//******************************************************************************
//
//
//		sprite_data.cpp
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< データ >---------------------------------------------------------------
// 2D画像ロードデータ
LoadTexture loadTexture[] = {
    { TEXNO::PLAYER,        L"./Data/Images/player.png",        1U }, // プレイヤー
    { TEXNO::ENEMY0,        L"./Data/Images/no-tsu01.png",      1U }, // 手裏剣
    { TEXNO::ENEMY1,        L"./Data/Images/no-tsu02.png",      1U }, // クナイ
    { TEXNO::ENEMY2_1,      L"./Data/Images/no-tsu03_1.png",    1U }, // 長押しノーツ
    { TEXNO::ENEMY2_2,      L"./Data/Images/no-tsu03_2.png",    1U }, // 長押しノーツ
    { TEXNO::ENEMY2_DEAD,   L"./Data/Images/no-tsu03_dead.png", 1U }, // 長押しノーツ(死亡時)
    { TEXNO::ENEMY3_1,      L"./Data/Images/no-tsu04_1.png",    1U }, // 連打ノーツ
    { TEXNO::ENEMY3_2,      L"./Data/Images/no-tsu04_2.png",    1U }, // 連打ノーツ
    { TEXNO::ENEMY3_DEAD,   L"./Data/Images/no-tsu04_dead.png", 1U }, // 連打ノーツ(死亡時)
    { TEXNO::EFFECT,        L"./Data/Images/effect.png",        1U }, // エフェクト
    { TEXNO::RESTART,       L"./Data/Images/restart.png",       1U }, // "再挑戦"文字
    { TEXNO::TOTITLE,       L"./Data/Images/to title.png",      1U }, // "たいとるへ"文字
    { TEXNO::MAP_BACK,      L"./Data/Images/background.png",    1U }, // 背景
    { TEXNO::T_START,       L"./Data/Images/textStart.png",     1U }, // "開幕！！"
    { TEXNO::T_END,         L"./Data/Images/textEnd.png",       1U }, // "閉幕！！"
    { TEXNO::T_FULLCOMBO,   L"./Data/Images/textFullCombo.png", 1U }, // "フルコンボ"
    { TEXNO::L_FUSUMA,      L"./Data/Images/L_fusuma.png",      1U }, // 左襖
    { TEXNO::R_FUSUMA,      L"./Data/Images/R_fusuma.png",      1U }, // 右襖
    { TEXNO::HP_BAR,        L"./Data/Images/HP_Bar.png",        1U }, // HPバー
    { TEXNO::TUTORIAL0,     L"./Data/Images/tutorial_operate.png",      1U },  // チュートリアル操作説明
    { TEXNO::TUTORIAL1,     L"./Data/Images/tutorial_normalnotes.png",      1U },  // チュートリアル普通ノーツ
    { TEXNO::TUTORIAL2,     L"./Data/Images/tutorial_hold_notes.png",      1U },  // チュートリアル長押しノーツ
    { TEXNO::TUTORIAL3,     L"./Data/Images/tutorial_barragenotes.png",      1U }, // チュートリアル連打ノーツ
    { TEXNO::TUTORIAL4,     L"./Data/Images/tutorial_puose.png",      1U }, // チュートリアルポーズノーツ

    { -1, nullptr }	// 終了フラグ
};

//------< マクロ >--------------------------------------------------------------
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // 画像の真ん中が中心
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // 画像の足元が中心

//------< プレイヤー >---------------------------------------------------------

// 待機
SpriteData sprPlayer_Idle0 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 0, 150 * 0, 150, 150);
SpriteData sprPlayer_Idle1 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 1, 150 * 0, 150, 150);

// 左攻撃
SpriteData sprPlayer_Attack_L0 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 0, 150 * 1, 150, 150);
SpriteData sprPlayer_Attack_L1 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 1, 150 * 1, 150, 150);
SpriteData sprPlayer_Attack_L2 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 2, 150 * 1, 150, 150);

// 右攻撃
SpriteData sprPlayer_Attack_R0 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 0, 150 * 2, 150, 150);
SpriteData sprPlayer_Attack_R1 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 1, 150 * 2, 150, 150);
SpriteData sprPlayer_Attack_R2 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 2, 150 * 2, 150, 150);

// 上攻撃
SpriteData sprPlayer_Attack_U0 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 0, 150 * 3, 150, 150);
SpriteData sprPlayer_Attack_U1 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 1, 150 * 3, 150, 150);
SpriteData sprPlayer_Attack_U2 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 2, 150 * 3, 150, 150);

// 下攻撃
// SpriteData sprPlayer_Down0 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 0, 150 * 2, 150, 150);
// SpriteData sprPlayer_Down1 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 1, 150 * 2, 150, 150);
// SpriteData sprPlayer_Down2 = SPRITE_BOTTOM(TEXNO::PLAYER, 150 * 2, 150 * 2, 150, 150);

//------< 敵 >------------------------------------------------------------------

//================================
//      手裏剣
//================================
// 攻撃
SpriteData sprEnemy0_Idle0 = SPRITE_CENTER(TEXNO::ENEMY0, 150 * 0, 150 * 0, 150, 150);

// 死亡時
SpriteData sprEnemy0_Dead0 = SPRITE_CENTER(TEXNO::ENEMY0, 150 * 1, 150 * 0, 150, 150);
SpriteData sprEnemy0_Dead1 = SPRITE_CENTER(TEXNO::ENEMY0, 150 * 2, 150 * 0, 150, 150);
SpriteData sprEnemy0_Dead2 = SPRITE_CENTER(TEXNO::ENEMY0, 150 * 3, 150 * 0, 150, 150);

//================================
//      クナイ
//================================

// 攻撃
SpriteData sprEnemy1_Idle0 = SPRITE_CENTER(TEXNO::ENEMY1, 150 * 0, 150 * 0, 150, 150);

// 死亡時
SpriteData sprEnemy1_Dead0 = SPRITE_CENTER(TEXNO::ENEMY1, 150 * 1, 150 * 0, 150, 150);
SpriteData sprEnemy1_Dead1 = SPRITE_CENTER(TEXNO::ENEMY1, 150 * 2, 150 * 0, 150, 150);
SpriteData sprEnemy1_Dead2 = SPRITE_CENTER(TEXNO::ENEMY1, 150 * 3, 150 * 0, 150, 150);

//================================
//      長押しノーツ(上)
//================================

// 攻撃
SpriteData sprEnemy2_1_Idle0 = SPRITE_CENTER(TEXNO::ENEMY2_1, 128 * 0, 512 * 0, 128, 512);

//================================
//      長押しノーツ(横)
//================================

// 攻撃
SpriteData sprEnemy2_2_Idle0 = SPRITE_CENTER(TEXNO::ENEMY2_2, 128 * 0, 128 * 0, 512, 128);

// 死亡時
SpriteData sprEnemy2_Dead0 = SPRITE_CENTER(TEXNO::ENEMY2_DEAD, 150 * 0, 150 * 0, 150, 150);
SpriteData sprEnemy2_Dead1 = SPRITE_CENTER(TEXNO::ENEMY2_DEAD, 150 * 1, 150 * 0, 150, 150);

//================================
//      連打ノーツ(上)
//================================

// 攻撃
SpriteData sprEnemy3_1_Idle0 = SPRITE_CENTER(TEXNO::ENEMY3_1, 128 * 0, 128 * 0, 128, 512);

//================================
//      連打ノーツ(横)
//================================

// 攻撃
SpriteData sprEnemy3_2_Idle0 = SPRITE_CENTER(TEXNO::ENEMY3_2, 128 * 0, 128 * 0, 512, 128);

// 死亡時
SpriteData sprEnemy3_Dead0 = SPRITE_CENTER(TEXNO::ENEMY3_DEAD, 150 * 0, 150 * 0, 150, 150);
SpriteData sprEnemy3_Dead1 = SPRITE_CENTER(TEXNO::ENEMY3_DEAD, 150 * 1, 150 * 0, 150, 150);

//------< エフェクト >------------------------------------------------------------------

//================================
//      Goodエフェクト
//================================

SpriteData sprEffect0_Idle0 = SPRITE_CENTER(TEXNO::EFFECT, 150 * 0, 150 * 0, 150, 150);
SpriteData sprEffect0_Idle1 = SPRITE_CENTER(TEXNO::EFFECT, 150 * 1, 150 * 0, 150, 150);
SpriteData sprEffect0_Idle2 = SPRITE_CENTER(TEXNO::EFFECT, 150 * 2, 150 * 0, 150, 150);

//================================
//      Greatエフェクト
//================================

SpriteData sprEffect1_Idle0 = SPRITE_CENTER(TEXNO::EFFECT, 150 * 0, 150 * 1, 150, 150);
SpriteData sprEffect1_Idle1 = SPRITE_CENTER(TEXNO::EFFECT, 150 * 1, 150 * 1, 150, 150);
SpriteData sprEffect1_Idle2 = SPRITE_CENTER(TEXNO::EFFECT, 150 * 2, 150 * 1, 150, 150);

//================================
//      Perfectエフェクト
//================================

SpriteData sprEffect2_Idle0 = SPRITE_CENTER(TEXNO::EFFECT, 150 * 0, 150 * 2, 150, 150);
SpriteData sprEffect2_Idle1 = SPRITE_CENTER(TEXNO::EFFECT, 150 * 1, 150 * 2, 150, 150);
SpriteData sprEffect2_Idle2 = SPRITE_CENTER(TEXNO::EFFECT, 150 * 2, 150 * 2, 150, 150);

//================================
//           文字
//================================

SpriteData sprRestart = SPRITE_CENTER(TEXNO::RESTART, 0, 0, 600, 300);
SpriteData sprTotitle = SPRITE_CENTER(TEXNO::TOTITLE, 0, 0, 600, 300);
SpriteData sprT_Start = SPRITE_CENTER(TEXNO::T_START, 0, 0, 600, 200);
SpriteData sprT_End   = SPRITE_CENTER(TEXNO::T_END,   0, 0, 600, 200);
SpriteData sprT_FullCombo = SPRITE_CENTER(TEXNO::T_FULLCOMBO, 0, 0, 600, 200);

//================================
//           UI
//================================

SpriteData sprHP_Bar = SPRITE_CENTER(TEXNO::RESTART, 0, 0, 600, 150);

//------------------------------------------------------------------------------
#undef SPRITE_CENTER
#undef SPRITE_BOTTOM

//******************************************************************************
