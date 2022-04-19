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

private:
    Select() {}
    ~Select() {}

    Select(const Select&) = delete;                 // コピーコンストラクター
    Select& operator=(const Select&) = delete;      // コピー代入演算子
    Select(Select&&) noexcept = delete;             // ムーブコンストラクター
    Select& operator=(Select&&) noexcept = delete;  // ムーブ代入演算子

public:
    // 使用するテクスチャのラベル
    enum class TEXNO {
        STAR,
        NUM,
    };

    // 使用するスプライトデータ
    GameLib::SpriteData sprStar_ = SPRITE_CENTER(static_cast<INT>(TEXNO::STAR), 0, 0, 500, 500);

private:
    // フェードアウト用タイマー
    float fadeOutTimer_ = 0.0f;

    // メンバ変数
    VECTOR2 starScale_ = { 0.0f, 0.0f };
    float   starAngle_ = 0.0f;
    int stageNum_ = 0;
};