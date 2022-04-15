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
    enum class TEXNO {
        STAR,
        NUM,
    };

    // 使用するスプライトデータ
    GameLib::SpriteData sprStar_ = SPRITE_CENTER(static_cast<INT>(TEXNO::STAR), 0, 0, 500, 500);

    // フェードアウト用タイマー
    float fadeOutTimer_ = 0.0f;

    // 変数
    VECTOR2 starScale_ = { 0.0f, 0.0f };
    float starAngle_ = 0.0f;
};
