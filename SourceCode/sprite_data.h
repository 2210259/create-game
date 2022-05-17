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

// xè`
enum TEXNO
{
    // Q[
    PLAYER,
    ENEMY0,       // G1
    ENEMY1,       // G2
    ENEMY2_1,     // G3_1
    ENEMY2_2,     // G3_2
    ENEMY2_DEAD,  // G3 S
    ENEMY3_1,     // G4_1
    ENEMY3_2,     // G4_2
    ENEMY3_DEAD,  // G4 S
    EFFECT,       // GtFNg
    RESTART,      // "Ä§í"Ì¶
    TOTITLE,      // "½¢ÆéÖ"Ì¶
    MAP_BACK,     // wi
    T_START,      // "JII"
    T_END,        // "ÂII"
    T_FULLCOMBO,  // "tR{"
    L_FUSUMA,     // Q[JÚÌæ
    R_FUSUMA,     // Q[JÚÌæ
    HP_BAR,       // HPo[
    TUTORIAL0,    // `[gAìà¾
    TUTORIAL1,    // `[gAÊm[c
    TUTORIAL2,    // `[gA·µm[c
    TUTORIAL3,    // `[gAAÅm[c
    TUTORIAL4,    // `[gA|[Ym[c

    NUM
};

extern GameLib::LoadTexture loadTexture[];

//------< vC[ >----------------------------------------------------------

// Ò@
extern GameLib::SpriteData sprPlayer_Idle0;
extern GameLib::SpriteData sprPlayer_Idle1;
 
//ãü«
extern GameLib::SpriteData sprPlayer_Attack_U0;
extern GameLib::SpriteData sprPlayer_Attack_U1;
extern GameLib::SpriteData sprPlayer_Attack_U2;

//Eü«
extern GameLib::SpriteData sprPlayer_Attack_R0;
extern GameLib::SpriteData sprPlayer_Attack_R1;
extern GameLib::SpriteData sprPlayer_Attack_R2;

//ºü«
extern GameLib::SpriteData sprPlayer_Down0;
extern GameLib::SpriteData sprPlayer_Down1;
extern GameLib::SpriteData sprPlayer_Down2;

//¶ü«
extern GameLib::SpriteData sprPlayer_Attack_L0;
extern GameLib::SpriteData sprPlayer_Attack_L1;
extern GameLib::SpriteData sprPlayer_Attack_L2;

//================================
//     è 
//================================
// U
extern GameLib::SpriteData sprEnemy0_Idle0;

// S
extern GameLib::SpriteData sprEnemy0_Dead0;
extern GameLib::SpriteData sprEnemy0_Dead1;
extern GameLib::SpriteData sprEnemy0_Dead2;

//================================
//      NiC
//================================

// U
extern GameLib::SpriteData sprEnemy1_Idle0;

// S
extern GameLib::SpriteData sprEnemy1_Dead0;
extern GameLib::SpriteData sprEnemy1_Dead1;
extern GameLib::SpriteData sprEnemy1_Dead2;

//================================
//      ·µm[c(ã)
//================================

// U
extern GameLib::SpriteData sprEnemy2_1_Idle0;

//================================
//      ·µm[c(¡)
//================================

// U
extern GameLib::SpriteData sprEnemy2_2_Idle0;

// S(ã¡¤Ê)
extern GameLib::SpriteData sprEnemy2_Dead0;
extern GameLib::SpriteData sprEnemy2_Dead1;

//================================
//      AÅm[c(ã)
//================================

// U
extern GameLib::SpriteData sprEnemy3_1_Idle0;
 
//================================
//      AÅm[c(¡)
//================================

// U
extern GameLib::SpriteData sprEnemy3_2_Idle0;

// S(ã¡¤Ê)
extern GameLib::SpriteData sprEnemy3_Dead0;
extern GameLib::SpriteData sprEnemy3_Dead1;

//------< GtFNg >------------------------------------------------------------------

//================================
//      GoodGtFNg
//================================

extern GameLib::SpriteData sprEffect0_Idle0;
extern GameLib::SpriteData sprEffect0_Idle1;
extern GameLib::SpriteData sprEffect0_Idle2;

//================================
//      GreatGtFNg
//================================

extern GameLib::SpriteData sprEffect1_Idle0;
extern GameLib::SpriteData sprEffect1_Idle1;
extern GameLib::SpriteData sprEffect1_Idle2;

//================================
//      PerfectGtFNg
//================================

extern GameLib::SpriteData sprEffect2_Idle0;
extern GameLib::SpriteData sprEffect2_Idle1;
extern GameLib::SpriteData sprEffect2_Idle2;

//================================
//          ¶
//================================

extern GameLib::SpriteData sprRestart;
extern GameLib::SpriteData sprTotitle;
extern GameLib::SpriteData sprTextStart;
extern GameLib::SpriteData sprTextEnd;

//******************************************************************************