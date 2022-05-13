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

    VECTOR2 C_L_Fusuma_Pos_ = { 0,0 };  // 左襖位置

    VECTOR2 C_R_Fusuma_Pos_ = { 0,0 };  // 右襖位置

    float C_Fusuma_timer_ = 0;          // 襖が閉じ始めるまでの時間

    bool restart_push_flg_ = false;     // リスタートを選択した時に立つフラグ

    bool title_push_flg_ = false;       // タイトルへを選択した時に立つフラグ

    VECTOR2 shuriken_Pos_[10] = {};      //手裏剣位置の初期化

    float shuriken_Angle_ = 0;          //手裏剣の角度の初期化


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
        , C_L_Fusuma_Pos_({ 0.0f,0.0f })       
        , C_R_Fusuma_Pos_({ 0.0f,0.0f })
        , C_Fusuma_timer_(0)
        , restart_push_flg_(false)
        , title_push_flg_(false)
        , shuriken_Angle_(0)

    {}
    ~Score() {}

    Score(const Score&) = delete;                 // コピーコンストラクター
    Score& operator=(const Score&) = delete;      // コピー代入演算子
    Score(Score&&) noexcept = delete;             // ムーブコンストラクター
    Score& operator=(Score&&) noexcept = delete;  // ムーブ代入演算子

    void scoreDraw();
    void scoreRusult();
public:
    // 使用するテクスチャのラベル
    enum class TEXNOM {
        RESTART,
        TOTITLE,
        CLEAR,
        GAMEOVER,
        L_FUSUMA,    
        R_FUSUMA,
        SHURIKEN,

        NUM,

    };

    //使用するスプライトデータ
    GameLib::SpriteData sprRestart_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::RESTART), 0, 0, 600, 300);
    GameLib::SpriteData sprTotitle_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::TOTITLE), 0, 0, 600, 300);
    GameLib::SpriteData sprClear_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::CLEAR), 0, 0, 1920, 1080);
    GameLib::SpriteData sprGameover_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::GAMEOVER), 0, 0, 1920, 1080);
    GameLib::SpriteData sprL_fusuma_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::L_FUSUMA), 0, 0, 960, 1080);
    GameLib::SpriteData sprR_fusuma_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::R_FUSUMA), 0, 0, 960, 1080);
    GameLib::SpriteData sprShuriken_ = SPRITE_CENTER(static_cast<INT>(TEXNOM::SHURIKEN), 0, 0, 128, 128);

};