#pragma once
//******************************************************************************
//
//      scene_select.h
//
//******************************************************************************

#include "scene.h"
#include "../GameLib/obj2d_data.h"

class Select : public Scene
{
private:
    static Select instance_;

public:
    // インスタンスの取得
    static Select* instance() { return &instance_; }

    void init() override;
    void deinit() override;
    void update() override;
    void draw() override;

    //TODO:ゲッターの設定
    //ゲッター
    int stageNum() { return stageNum_; }

private:
    Select() {}
    ~Select() {}

    Select(const Select&) = delete;                 // コピーコンストラクター
    Select& operator=(const Select&) = delete;      // コピー代入演算子
    Select(Select&&) noexcept = delete;             // ムーブコンストラクター
    Select& operator=(Select&&) noexcept = delete;  // ムーブ代入演算子

public:
    //TODO:変更
    // 使用するテクスチャのラベル
    enum class TEXNO {
        BACK,
        TUTORIAL,
        STAGE1,
        STAGE2,
        L_FUSUMA,
        R_FUSUMA,
        NUM,
    };

    //TODO:変更
    // 使用するスプライトデータ
    GameLib::SpriteData sprBack_ = SPRITE_CENTER(static_cast<INT>(TEXNO::BACK), 0, 0, 1920, 1080);
    GameLib::SpriteData sprTutorial_ = SPRITE_CENTER(static_cast<INT>(TEXNO::TUTORIAL), 0, 0, 700, 700);
    GameLib::SpriteData sprStage1_ = SPRITE_CENTER(static_cast<INT>(TEXNO::STAGE1), 0, 0, 700, 700);
    GameLib::SpriteData sprStage2_ = SPRITE_CENTER(static_cast<INT>(TEXNO::STAGE2), 0, 0, 700, 700);
    GameLib::SpriteData sprL_fusuma_ = SPRITE_CENTER(static_cast<INT>(TEXNO::L_FUSUMA), 0, 0, 960, 1080);
    GameLib::SpriteData sprR_fusuma_ = SPRITE_CENTER(static_cast<INT>(TEXNO::R_FUSUMA), 0, 0, 960, 1080);


private:

    // メンバ変数
    int stageNum_ = 0;
    bool push_flg = false;

    //TODO:変数の追加＆変更
    float tutorial_icon_Alpha_ = 1.0f;
    float stage1_icon_Alpha_ = 1.0f;
    float stage2_icon_Alpha_ = 1.0f;
    VECTOR2 tutorial_icon_Scale_ = { 0.5f , 0.5f };
    VECTOR2 stage1_icon_Scale_ = { 0.5f , 0.5f };
    VECTOR2 stage2_icon_Scale_ = { 0.5f , 0.5f };
    VECTOR2 tutorial_icon_Pos_ = { GameLib::window::getWidth() / 2 - (GameLib::window::getWidth() / 2) / 2 , GameLib::window::getHeight() / 2 };
    VECTOR2 stage1_icon_Pos_ = { GameLib::window::getWidth() / 2 , GameLib::window::getHeight() / 2 };
    VECTOR2 stage2_icon_Pos_ = { GameLib::window::getWidth() / 2 + (GameLib::window::getWidth() / 2) / 2 , GameLib::window::getHeight() / 2 };
    VECTOR2 S_L_Fusuma_Pos_ = { 0,0 };
    VECTOR2 S_R_Fusuma_Pos_ = { 0,0 };
    float Fusuma_timer_ = 0.0f;
};