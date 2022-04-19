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

    { -1, nullptr }	// 終了フラグ
};

//------< マクロ >--------------------------------------------------------------
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // 画像の真ん中が中心
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // 画像の足元が中心

//------< プレイヤー >----------------------------------------------------------
//上歩き
SpriteData sprPlayer_Up0 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 0, 128 * 0, 96, 128);
SpriteData sprPlayer_Up1 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 1, 128 * 0, 96, 128);
SpriteData sprPlayer_Up2 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 2, 128 * 0, 96, 128);

//右歩き
SpriteData sprPlayer_Right0 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 0, 128 * 1, 96, 128);
SpriteData sprPlayer_Right1 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 1, 128 * 1, 96, 128);
SpriteData sprPlayer_Right2 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 2, 128 * 1, 96, 128);

//下歩き
SpriteData sprPlayer_Down0 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 0, 128 * 2, 96, 128);
SpriteData sprPlayer_Down1 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 1, 128 * 2, 96, 128);
SpriteData sprPlayer_Down2 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 2, 128 * 2, 96, 128);

//左歩き
SpriteData sprPlayer_Left0 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 0, 128 * 3, 96, 128);
SpriteData sprPlayer_Left1 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 1, 128 * 3, 96, 128);
SpriteData sprPlayer_Left2 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 2, 128 * 3, 96, 128);

//------< 敵 >------------------------------------------------------------------

//================================
//      敵0
//================================
// 左向き
SpriteData sprEnemy0_Left0 = SPRITE_CENTER(TEXNO::ENEMY0, 600 * 0, 600 * 0, 600, 600);
SpriteData sprEnemy0_Left1 = SPRITE_CENTER(TEXNO::ENEMY0, 600 * 1, 600 * 0, 600, 600);

// 右向き
SpriteData sprEnemy0_Right0 = SPRITE_CENTER(TEXNO::ENEMY0, 600 * 0, 600 * 1, 600, 600);
SpriteData sprEnemy0_Right1 = SPRITE_CENTER(TEXNO::ENEMY0, 600 * 1, 600 * 1, 600, 600);

// 死亡時
SpriteData sprEnemy0_Dead0 = SPRITE_CENTER(TEXNO::ENEMY0, 600 * 0, 600 * 4, 600, 600);
SpriteData sprEnemy0_Dead1 = SPRITE_CENTER(TEXNO::ENEMY0, 600 * 1, 600 * 4, 600, 600);
SpriteData sprEnemy0_Dead2 = SPRITE_CENTER(TEXNO::ENEMY0, 600 * 2, 600 * 4, 600, 600);

//================================
//      敵1
//================================

//左歩き
SpriteData sprEnemy1_Left0 = SPRITE_CENTER(TEXNO::ENEMY1, 740 * 0, 380 * 0, 740, 380);
SpriteData sprEnemy1_Left1 = SPRITE_CENTER(TEXNO::ENEMY1, 740 * 1, 380 * 0, 740, 380);

//右歩き
SpriteData sprEnemy1_Right0 = SPRITE_CENTER(TEXNO::ENEMY1, 740 * 0, 380 * 1, 740, 380);
SpriteData sprEnemy1_Right1 = SPRITE_CENTER(TEXNO::ENEMY1, 740 * 1, 380 * 1, 740, 380);

// 死亡時
SpriteData sprEnemy1_Dead0 = SPRITE_CENTER(TEXNO::ENEMY1, 740 * 0, 380 * 4, 740, 380);
SpriteData sprEnemy1_Dead1 = SPRITE_CENTER(TEXNO::ENEMY1, 740 * 1, 380 * 4, 740, 380);
SpriteData sprEnemy1_Dead2 = SPRITE_CENTER(TEXNO::ENEMY1, 740 * 2, 380 * 4, 740, 380);

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
