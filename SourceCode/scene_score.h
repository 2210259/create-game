#pragma once
class Score : public Scene
{
private:
    static Score instance_;

public:
    // インスタンスの取得
    static Score* instance() { return &instance_; }

    void init() override;
    void deinit() override;
    void update() override;
    void draw() override;

private:
    Score() {}
    ~Score() {}

    Score(const Score&) = delete;                 // コピーコンストラクター
    Score& operator=(const Score&) = delete;      // コピー代入演算子
    Score(Score&&) noexcept = delete;             // ムーブコンストラクター
    Score& operator=(Score&&) noexcept = delete;  // ムーブ代入演算子

//public:
//    // 使用するテクスチャのラベル
//    enum class TEXNO {
//        STAR,
//        NUM,
//    };

//    // 使用するスプライトデータ
//    GameLib::SpriteData sprStar_ = SPRITE_CENTER(static_cast<INT>(TEXNO::STAR), 0, 0, 500, 500);

//private:
//    // フェードアウト用タイマー
//    //float fadeOutTimer_ = 0.0f;

//    // メンバ変数
//    VECTOR2 starScale_ = { 0.0f, 0.0f };
//    float   starAngle_ = 0.0f;
//    int stageNum_ = 0;
};