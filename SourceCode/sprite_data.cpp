//******************************************************************************
//
//
//		SPRITE_DATA
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< データ >---------------------------------------------------------------

#if 2
//******************************************************************************
// HACK:02 武器用テクスチャの読み込み
//------------------------------------------------------------------------------
/*
確認）
    武器用のテクスチャを読み込む設定をしています。
*/
//******************************************************************************
#endif
// 2D画像ロードデータ
LoadTexture loadTexture[] = {
    { TEXNO::PLAYER,        L"./Data/Images/player.png",        1U },// プレイヤー
    { TEXNO::MAP_BACK,      L"./Data/Maps/back_chip.png",       static_cast<UINT>(BG::LOOP_X * BG::LOOP_Y) }, // マップ背景
    { TEXNO::MAP_TERRAIN,   L"./Data/Maps/terrain_chip.png",    static_cast<UINT>(BG::LOOP_X * BG::LOOP_Y) }, // マップ地形
    { TEXNO::MAP_ITEM,      L"./Data/Maps/item_chip.png",       1U }, 
    { TEXNO::ENEMY0,        L"./Data/Images/enemy00.png",       1U },
    { TEXNO::ENEMY1,        L"./Data/Images/enemy01.png",       1U },
    { TEXNO::ENEMY5,        L"./Data/Images/enemy05.png",       1U },
    //HACK_02
    { TEXNO::WEAPON,        L"./Data/Images/weapon.png",        1U }, 
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

//------< アイテム >-------------------------------------------------------------
SpriteData sprItemSword = SPRITE_CENTER(TEXNO::MAP_ITEM, 64 * 0, 64 * 0, 64, 64);
SpriteData sprItemKey   = SPRITE_CENTER(TEXNO::MAP_ITEM, 64 * 2, 64 * 0, 64, 64);
SpriteData sprItemOrb   = SPRITE_CENTER(TEXNO::MAP_ITEM, 64 * 4, 64 * 0, 64, 64);

//------< 敵 >------------------------------------------------------------------

//================================
//      敵0
//================================

//上歩き
SpriteData sprEnemy0_Up0 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 0, 128 * 0, 96, 128);
SpriteData sprEnemy0_Up1 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 1, 128 * 0, 96, 128);
SpriteData sprEnemy0_Up2 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 2, 128 * 0, 96, 128);

//右歩き
SpriteData sprEnemy0_Right0 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 0, 128 * 1, 96, 128);
SpriteData sprEnemy0_Right1 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 1, 128 * 1, 96, 128);
SpriteData sprEnemy0_Right2 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 2, 128 * 1, 96, 128);

//下歩き
SpriteData sprEnemy0_Down0 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 0, 128 * 2, 96, 128);
SpriteData sprEnemy0_Down1 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 1, 128 * 2, 96, 128);
SpriteData sprEnemy0_Down2 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 2, 128 * 2, 96, 128);

//左歩き
SpriteData sprEnemy0_Left0 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 0, 128 * 3, 96, 128);
SpriteData sprEnemy0_Left1 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 1, 128 * 3, 96, 128);
SpriteData sprEnemy0_Left2 = SPRITE_BOTTOM(TEXNO::ENEMY0, 96 * 2, 128 * 3, 96, 128);

//================================
//      敵1
//================================

//上歩き
SpriteData sprEnemy1_Up0 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 0, 128 * 0, 96, 128);
SpriteData sprEnemy1_Up1 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 1, 128 * 0, 96, 128);
SpriteData sprEnemy1_Up2 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 2, 128 * 0, 96, 128);

//右歩き
SpriteData sprEnemy1_Right0 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 0, 128 * 1, 96, 128);
SpriteData sprEnemy1_Right1 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 1, 128 * 1, 96, 128);
SpriteData sprEnemy1_Right2 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 2, 128 * 1, 96, 128);

//下歩き
SpriteData sprEnemy1_Down0 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 0, 128 * 2, 96, 128);
SpriteData sprEnemy1_Down1 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 1, 128 * 2, 96, 128);
SpriteData sprEnemy1_Down2 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 2, 128 * 2, 96, 128);

//左歩き
SpriteData sprEnemy1_Left0 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 0, 128 * 3, 96, 128);
SpriteData sprEnemy1_Left1 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 1, 128 * 3, 96, 128);
SpriteData sprEnemy1_Left2 = SPRITE_BOTTOM(TEXNO::ENEMY1, 96 * 2, 128 * 3, 96, 128);

//================================
//      敵5
//================================

//上歩き
SpriteData sprEnemy5_Up0 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 0, 128 * 0, 96, 128);
SpriteData sprEnemy5_Up1 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 1, 128 * 0, 96, 128);
SpriteData sprEnemy5_Up2 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 2, 128 * 0, 96, 128);

//右歩き
SpriteData sprEnemy5_Right0 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 0, 128 * 1, 96, 128);
SpriteData sprEnemy5_Right1 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 1, 128 * 1, 96, 128);
SpriteData sprEnemy5_Right2 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 2, 128 * 1, 96, 128);

//下歩き
SpriteData sprEnemy5_Down0 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 0, 128 * 2, 96, 128);
SpriteData sprEnemy5_Down1 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 1, 128 * 2, 96, 128);
SpriteData sprEnemy5_Down2 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 2, 128 * 2, 96, 128);

//左歩き
SpriteData sprEnemy5_Left0 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 0, 128 * 3, 96, 128);
SpriteData sprEnemy5_Left1 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 1, 128 * 3, 96, 128);
SpriteData sprEnemy5_Left2 = SPRITE_BOTTOM(TEXNO::ENEMY5, 96 * 2, 128 * 3, 96, 128);

//------< 武器 >----------------------------------------------------------------

#if 3
//******************************************************************************
// HACK:03 武器用スプライトデータの定義
//------------------------------------------------------------------------------
/*
確認）
    下記で武器のスプライトデータの定義をしています。
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
