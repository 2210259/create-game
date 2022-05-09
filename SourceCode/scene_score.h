#pragma once
class Score : public Scene
{
private:
    static Score instance_;

    int score_select_num_;   //選択用
    float score_alpha_;      //表示するテキストのα値
    int score_alpha_num_;    //α値を０～１まで往復させるための値

    VECTOR2 scoreText_pos_;  //スコアテキストの位置
    int     scoreNum_;       //スコア

    VECTOR2 comboText_pos_;  //コンボテキストの位置
    int     comboNum_;       //コンボ

    VECTOR2 perfectText_pos_;//パーフェクトテキストの位置
    int     perfectNum_;     //パーフェクト

    VECTOR2 greatText_pos_;  //グレイトテキストの位置
    int     greatNum_;       //グレイト

    VECTOR2 goodText_pos_;   //グッドテキストの位置
    int     goodNum_;        //グッド

    VECTOR2 missText_pos_;   //ミステキストの位置
    int     missNum_;        //ミス

    float rank_Scale;        //ランクテキストのスケール

    int     performState_;   //演出用ステート



public:
    // インスタンスの取得
    static Score* instance() { return &instance_; }

    void init() override;
    void deinit() override;
    void update() override;
    void draw() override;

private:
    Score() 
        : score_select_num_(0)
        ,score_alpha_(1.0f)
        ,score_alpha_num_(0)
        , scoreText_pos_({ 1920.0f,0.0f })
        , scoreNum_(0)
        , perfectText_pos_({ 1920.0f,0.0f })
        , perfectNum_(0)
        , greatText_pos_({ 1920.0f,0.0f })
        , greatNum_(0)
        , goodText_pos_({ 1920.0f,0.0f })
        , goodNum_(0)
        , performState_(0)
        , missNum_(0)
        , missText_pos_({ 1920.0f,0.0f })
        , rank_Scale( 130.0f )
    {}
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

public:
    // 使用するテクスチャのラベル
    enum class TEXNOM {
        RESTART,
        TOTITLE,
        CLEAR,
        GAMEOVER,
        NUM,
    };

    //使用するスプライトデータ
    GameLib::SpriteData sprRestart_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::RESTART), 0, 0, 600, 300);
    GameLib::SpriteData sprTotitle_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::TOTITLE), 0, 0, 600, 300);
    GameLib::SpriteData sprClear_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::CLEAR), 0, 0, 1920, 1080);
    GameLib::SpriteData sprGameover_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::GAMEOVER), 0, 0, 1920, 1080);

};