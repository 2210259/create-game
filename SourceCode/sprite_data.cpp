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
    { TEXNO::PLAYER,        L"./Data/Images/player.png",        1U },// プレイヤー
    { TEXNO::ENEMY0,        L"./Data/Images/no-tsu.png",         1U },// 敵
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
//      敵0
//================================
// 左向き
SpriteData sprEnemy0_Left0 = SPRITE_CENTER(TEXNO::ENEMY0, 128 * 0, 128 * 0, 128, 128);
SpriteData sprEnemy0_Left1 = SPRITE_CENTER(TEXNO::ENEMY0, 128 * 1, 128 * 0, 128, 128);

// 右向き
SpriteData sprEnemy0_Right0 = SPRITE_CENTER(TEXNO::ENEMY0, 128 * 0, 128 * 1, 128, 128);
SpriteData sprEnemy0_Right1 = SPRITE_CENTER(TEXNO::ENEMY0, 128 * 1, 128 * 1, 128, 128);

// 死亡時
SpriteData sprEnemy0_Dead0 = SPRITE_CENTER(TEXNO::ENEMY0, 128 * 0, 128 * 4, 128, 128);
SpriteData sprEnemy0_Dead1 = SPRITE_CENTER(TEXNO::ENEMY0, 128 * 1, 128 * 4, 128, 128);
SpriteData sprEnemy0_Dead2 = SPRITE_CENTER(TEXNO::ENEMY0, 128 * 2, 128 * 4, 128, 128);

//================================
//      敵1
//================================

//左歩き
SpriteData sprEnemy1_Left0 = SPRITE_CENTER(TEXNO::ENEMY1, 128 * 0, 128 * 0, 128, 128);
SpriteData sprEnemy1_Left1 = SPRITE_CENTER(TEXNO::ENEMY1, 128 * 1, 128 * 0, 128, 128);

//右歩き
SpriteData sprEnemy1_Right0 = SPRITE_CENTER(TEXNO::ENEMY1, 128 * 0, 128 * 1, 128, 128);
SpriteData sprEnemy1_Right1 = SPRITE_CENTER(TEXNO::ENEMY1, 128 * 1, 128 * 1, 128, 128);

// 死亡時
SpriteData sprEnemy1_Dead0 = SPRITE_CENTER(TEXNO::ENEMY1, 128 * 0, 128 * 4, 128, 128);
SpriteData sprEnemy1_Dead1 = SPRITE_CENTER(TEXNO::ENEMY1, 128 * 1, 128 * 4, 128, 128);
SpriteData sprEnemy1_Dead2 = SPRITE_CENTER(TEXNO::ENEMY1, 128 * 2, 128 * 4, 128, 128);

//================================
//      敵2
//================================

//左歩き
SpriteData sprEnemy2_Left0 = SPRITE_CENTER(TEXNO::ENEMY2, 250 * 0, 650 * 0, 250, 650);
SpriteData sprEnemy2_Left1 = SPRITE_CENTER(TEXNO::ENEMY2, 250 * 1, 650 * 0, 250, 650);

//右歩き
SpriteData sprEnemy2_Right0 = SPRITE_CENTER(TEXNO::ENEMY2, 250 * 0, 650 * 1, 250, 650);
SpriteData sprEnemy2_Right1 = SPRITE_CENTER(TEXNO::ENEMY2, 250 * 1, 650 * 1, 250, 650);

// 死亡時
SpriteData sprEnemy2_Dead0 = SPRITE_CENTER(TEXNO::ENEMY2, 250 * 0, 650 * 4, 250, 650);
SpriteData sprEnemy2_Dead1 = SPRITE_CENTER(TEXNO::ENEMY2, 250 * 1, 650 * 4, 250, 650);
SpriteData sprEnemy2_Dead2 = SPRITE_CENTER(TEXNO::ENEMY2, 250 * 2, 650 * 4, 250, 650);
SpriteData sprEnemy2_Dead3 = SPRITE_CENTER(TEXNO::ENEMY2, 250 * 3, 650 * 4, 250, 650);

//------------------------------------------------------------------------------
#undef SPRITE_CENTER
#undef SPRITE_BOTTOM

//******************************************************************************
