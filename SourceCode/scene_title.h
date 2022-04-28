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

public:
    // 使用するテクスチャのラベル
    enum class TEXNOM {
        STAR,
        NUM,
    };

    // 使用するスプライトデータ
    GameLib::SpriteData sprStar_    = SPRITE_CENTER(static_cast<INT>(TEXNOM::STAR), 0, 0, 500, 500);
    //GameLib::SpriteData sprPlayer_  = SPRITE_BOTTOM(static_cast<INT>(TEXNO::PLAYER), 0, 0, 150, 150);

    // フェードアウト用タイマー
    float fadeOutTimer_ = 0.0f;

    // メンバ変数
    VECTOR2 starScale_ = { 0.0f, 0.0f };
    float starAngle_ = 0.0f;

    VECTOR2 playerPos_     = { BG::WINDOW_W / 4, BG::WINDOW_H / 10 * 9 };
    VECTOR2 playerScale_   = { 4.0f, 4.0f };
    VECTOR2 playerTexPos_  = {  150,   150 };
    VECTOR2 playerTexSize_ = { 1, 1 };

    // VECTOR2 playerTexSize_;
};
