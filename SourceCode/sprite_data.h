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
// HACK:01 武器用テクスチャのラベルを定義する
//------------------------------------------------------------------------------
/*
確認）
    武器用テクスチャのラベルを定義しています。
*/
//******************************************************************************
#endif
// ラベル定義
enum TEXNO
{
    // ゲーム
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

//------< アイテム >-------------------------------------------------------------
extern GameLib::SpriteData sprItemSword;
extern GameLib::SpriteData sprItemKey;
extern GameLib::SpriteData sprItemOrb;

//------< 敵 >------------------------------------------------------------------

//================================
//      敵0
//================================

//上歩き
extern GameLib::SpriteData sprEnemy0_Up0;
extern GameLib::SpriteData sprEnemy0_Up1;
extern GameLib::SpriteData sprEnemy0_Up2;

//右歩き
extern GameLib::SpriteData sprEnemy0_Right0;
extern GameLib::SpriteData sprEnemy0_Right1;
extern GameLib::SpriteData sprEnemy0_Right2;

//下歩き
extern GameLib::SpriteData sprEnemy0_Down0;
extern GameLib::SpriteData sprEnemy0_Down1;
extern GameLib::SpriteData sprEnemy0_Down2;

//左歩き
extern GameLib::SpriteData sprEnemy0_Left0;
extern GameLib::SpriteData sprEnemy0_Left1;
extern GameLib::SpriteData sprEnemy0_Left2;

//================================
//      敵1
//================================

//上歩き
extern GameLib::SpriteData sprEnemy1_Up0;
extern GameLib::SpriteData sprEnemy1_Up1;
extern GameLib::SpriteData sprEnemy1_Up2;

//右歩き
extern GameLib::SpriteData sprEnemy1_Right0;
extern GameLib::SpriteData sprEnemy1_Right1;
extern GameLib::SpriteData sprEnemy1_Right2;

//下歩き
extern GameLib::SpriteData sprEnemy1_Down0;
extern GameLib::SpriteData sprEnemy1_Down1;
extern GameLib::SpriteData sprEnemy1_Down2;

//左歩き
extern GameLib::SpriteData sprEnemy1_Left0;
extern GameLib::SpriteData sprEnemy1_Left1;
extern GameLib::SpriteData sprEnemy1_Left2;

//================================
//      敵5
//================================

//上歩き
extern GameLib::SpriteData sprEnemy5_Up0;
extern GameLib::SpriteData sprEnemy5_Up1;
extern GameLib::SpriteData sprEnemy5_Up2;

//右歩き
extern GameLib::SpriteData sprEnemy5_Right0;
extern GameLib::SpriteData sprEnemy5_Right1;
extern GameLib::SpriteData sprEnemy5_Right2;

//下歩き
extern GameLib::SpriteData sprEnemy5_Down0;
extern GameLib::SpriteData sprEnemy5_Down1;
extern GameLib::SpriteData sprEnemy5_Down2;

//左歩き
extern GameLib::SpriteData sprEnemy5_Left0;
extern GameLib::SpriteData sprEnemy5_Left1;
extern GameLib::SpriteData sprEnemy5_Left2;

//------< 武器 >----------------------------------------------------------------

#if 4
//******************************************************************************
// HACK:04 武器用スプライトデータの宣言
//------------------------------------------------------------------------------
/*
確認）
    下記で武器のスプライトデータのextern宣言を行なっています。
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

