#pragma once
//******************************************************************************
//
//      scene_title.h
//
//******************************************************************************

#include "scene.h"
#include "../GameLib/obj2d_data.h"

class Title : public Scene
{
private:
    static Title instance_;

public:
    // インスタンスの取得
    static Title* instance() { return &instance_; }

    void init() override;
    void deinit() override;
    void update() override;
    void draw() override;

private:
    Title() {}
    ~Title() {}

    Title(const Title&) = delete;                 // コピーコンストラクター
    Title& operator=(const Title&) = delete;      // コピー代入演算子
    Title(Title&&) noexcept = delete;             // ムーブコンストラクター
    Title& operator=(Title&&) noexcept = delete;  // ムーブ代入演算子

    // メンバ関数
    void playerAnime();

public:
    // メンバ変数
    VECTOR2 squarePos_ = { 0,0 };
    VECTOR2 squareScale_ = { 0.0f, 0.0f };
    float squareAngle_ = 0.0f;

    VECTOR2 playerPos_     = { BG::WINDOW_W / 4, 1000 };
    VECTOR2 playerScale_   = { 5, 5 };
    VECTOR2 playerTexPos_  = { 0, 0 };
    VECTOR4 playerColor_   = { 1, 1, 1, 1 };
    
    bool push_flg_ = false;
    float Fusuma_timer_ = 0;
    int switchNum = 0;
    VECTOR2 T_L_Fusuma_Pos_ = { 0.0f,0.0f };
    VECTOR2 T_R_Fusuma_Pos_ = { 0.0f,0.0f };

    // 使用するテクスチャのラベル
    enum class TEXNUM {
        L_FUSUMA,
        R_FUSUMA,
        SQUARE,
        START,
        PLAYER,
        NUM,
    };

    GameLib::SpriteData sprSquare_  = SPRITE_CENTER(static_cast<INT>(TEXNUM::SQUARE), 0, 0, 500, 500);
    GameLib::SpriteData sprPlayer_  = SPRITE_BOTTOM(static_cast<INT>(TEXNUM::PLAYER), 0, 0, 150, 150);
    GameLib::SpriteData sprStart_   = SPRITE_CENTER(static_cast<INT>(TEXNUM::START), 0, 0, 600, 300);
    GameLib::SpriteData sprL_fusuma_ = SPRITE_CENTER(static_cast<INT>(TEXNUM::L_FUSUMA), 0, 0, 960, 1080);
    GameLib::SpriteData sprR_fusuma_ = SPRITE_CENTER(static_cast<INT>(TEXNUM::R_FUSUMA), 0, 0, 960, 1080);
};
