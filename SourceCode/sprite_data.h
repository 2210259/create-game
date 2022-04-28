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

// ƒ‰ƒxƒ‹’è‹`
enum TEXNO
{
    // ƒQ[ƒ€
    PLAYER,
    ENEMY0,       //“G1
    ENEMY1,       //“G2
    ENEMY2,       //“G3
    ENEMY3,       //“G4
    ENEMY4,       //“G5
    ENEMY5,       //“G6

    NUM
};

extern GameLib::LoadTexture loadTexture[];

//------< ƒvƒŒƒCƒ„[ >----------------------------------------------------------

// ‘Ò‹@
extern GameLib::SpriteData sprPlayer_Idle0;
extern GameLib::SpriteData sprPlayer_Idle1;
 
//ãŒü‚«
extern GameLib::SpriteData sprPlayer_Attack_U0;
extern GameLib::SpriteData sprPlayer_Attack_U1;
extern GameLib::SpriteData sprPlayer_Attack_U2;

//‰EŒü‚«
extern GameLib::SpriteData sprPlayer_Attack_R0;
extern GameLib::SpriteData sprPlayer_Attack_R1;
extern GameLib::SpriteData sprPlayer_Attack_R2;

//‰ºŒü‚«
extern GameLib::SpriteData sprPlayer_Down0;
extern GameLib::SpriteData sprPlayer_Down1;
extern GameLib::SpriteData sprPlayer_Down2;

//¶Œü‚«
extern GameLib::SpriteData sprPlayer_Attack_L0;
extern GameLib::SpriteData sprPlayer_Attack_L1;
extern GameLib::SpriteData sprPlayer_Attack_L2;

//================================
//      “G0
//================================
// UŒ‚
extern GameLib::SpriteData sprEnemy0_Idle0;

// €–S
extern GameLib::SpriteData sprEnemy0_Dead0;
extern GameLib::SpriteData sprEnemy0_Dead1;
extern GameLib::SpriteData sprEnemy0_Dead2;

//================================
//      “G1
//================================

// UŒ‚
extern GameLib::SpriteData sprEnemy1_Idle0;

// €–S
extern GameLib::SpriteData sprEnemy1_Dead0;
extern GameLib::SpriteData sprEnemy1_Dead1;
extern GameLib::SpriteData sprEnemy1_Dead2;

//================================
//      “G2
//================================

// UŒ‚
extern GameLib::SpriteData sprEnemy2_Idle0;

// €–S
extern GameLib::SpriteData sprEnemy2_Dead0;
extern GameLib::SpriteData sprEnemy2_Dead1;
extern GameLib::SpriteData sprEnemy2_Dead2;
extern GameLib::SpriteData sprEnemy2_Dead3;

//================================
//      “G3
//================================

// UŒ‚
extern GameLib::SpriteData sprEnemy3_Idle0;

// €–S
// extern GameLib::SpriteData sprEnemy3_Dead0;
// extern GameLib::SpriteData sprEnemy3_Dead1;
// extern GameLib::SpriteData sprEnemy3_Dead2;
// extern GameLib::SpriteData sprEnemy3_Dead3;

//================================
//      “G4
//================================

// UŒ‚
extern GameLib::SpriteData sprEnemy4_Idle0;
 
// €–S
// extern GameLib::SpriteData sprEnemy4_Dead0;
// extern GameLib::SpriteData sprEnemy4_Dead1;
// extern GameLib::SpriteData sprEnemy4_Dead2;
// extern GameLib::SpriteData sprEnemy4_Dead3;

//******************************************************************************
