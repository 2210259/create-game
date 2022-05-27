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

    float calcIconFlashing(float colorW, int timer);
    float calcIconFade(float colorW);

    void shurikenAct();

    //ゲッターの設定
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
    // 使用するテクスチャのラベル
    enum class TEXNOM {
        BACK,
        TUTORIAL,
        STAGE1,
        L_FUSUMA,
        R_FUSUMA,
        TOTITLE,
        DECORATION,
        SHURIKEN,
        NUM,
    };

    // 使用するスプライトデータ
    GameLib::SpriteData sprBack_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::BACK), 0, 0, 1920, 1080);
    GameLib::SpriteData sprTutorial_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::TUTORIAL), 0, 0, 438, 1050);
    GameLib::SpriteData sprStage1_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::STAGE1), 0, 0, 438, 1050);
    GameLib::SpriteData sprL_fusuma_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::L_FUSUMA), 0, 0, 960, 1080);
    GameLib::SpriteData sprR_fusuma_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::R_FUSUMA), 0, 0, 960, 1080);
    GameLib::SpriteData sprTotitle_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::TOTITLE), 0, 0, 438, 1050);
    GameLib::SpriteData sprShuriken_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::SHURIKEN), 0, 0, 150, 150);
    GameLib::SpriteData sprDecration_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::DECORATION), 0, 0, 438, 1050);

private:
    struct Param {
        VECTOR2 pos;
        VECTOR2 scale;
        VECTOR2 texPos;
        VECTOR2 texSize;
        float angle;
        VECTOR4 color;
    } param_ = {};

    // メンバ変数
    int stageNum_ = 0;
    bool push_flg = false;

    float tutorial_icon_Alpha_ = 1.0f;// チュートリアルのアイコンα
    float stage1_icon_Alpha_ = 1.0f;  // ステージ１のアイコンα
    VECTOR2 tutorial_icon_Scale_ = { 0.5f , 0.5f }; // チュートリアルのアイコンスケール
    VECTOR2 stage1_icon_Scale_ = { 0.5f , 0.5f };   // ステージ１のアイコンスケール
    VECTOR2 tutorial_icon_Pos_ = { GameLib::window::getWidth() / 2 - (GameLib::window::getWidth() / 2) / 2 , GameLib::window::getHeight() / 2 };    //チュートリアルのアイコン位置
    VECTOR2 stage1_icon_Pos_ = { GameLib::window::getWidth() / 2 , GameLib::window::getHeight() / 2 };  //ステージ１のアイコン位置
    VECTOR2 S_L_Fusuma_Pos_ = { 0,0 };  // 左襖の位置
    VECTOR2 S_R_Fusuma_Pos_ = { 0,0 };  // 右襖の位置
    float Fusuma_timer_ = 0.0f;         // 襖が開閉し始めるまでの時間
    VECTOR2 shuriken_Pos_[10] = {};      //手裏剣位置の初期化
    float shuriken_Angle_ = 0;          //手裏剣の角度の初期化
    VECTOR2 title_icon_Scale_ = { 0.5f , 0.5f };   // タイトルのアイコンスケール
    VECTOR2 title_icon_Pos_ = { GameLib::window::getWidth() / 2 - (GameLib::window::getWidth() / 2) / 2 , GameLib::window::getHeight() / 2 };    //タイトルへのアイコン位置
    float title_icon_Alpha_ = 1.0f;  // タイトルのアイコンα
    bool title_push_flg_ = false;

    Param stagingShuriken_[1] = {};
};