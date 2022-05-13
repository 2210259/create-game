#pragma once

//******************************************************************************
//
//
//      ゲームシーン
//
//
//******************************************************************************

// Gameクラス
class Game : public Scene
{
public:
    // メンバ変数
    VECTOR2 hpPos01;    // HPバーの位置
    VECTOR2 hpSize01;   // HPバーの大きさ
    VECTOR4 hpColor01;  // HPバーの色
    VECTOR2 hpPos02;    // HPバーの位置
    VECTOR2 hpSize02;   // HPバーの大きさ
    VECTOR4 hpColor02;  // HPバーの色

    VECTOR2 squarePos_ = { 0,0 };
    VECTOR2 squareScale_ = { 0.0f, 0.0f };
    float squareAngle_ = 0.0f;

private:
    // メンバ変数
    OBJ2DManager*   obj2dManager_;
    BG*             bg_;
    bool            isPaused_;
    OBJ2D*          player_;
    static Game     instance_;
    bool playerModeFlag_;   // プレイヤーモードの切り替えフラグ
    int stageNo_;           // ステージ番号
    bool enemyXFlip_;       // 敵の向きを保存
    int combo_;             // コンボ数
    int combo2_;            // コンボ数（連打）
    int combo2Timer_;       // コンボの出現時間
    int maxCombo_;          // 最大コンボ数
    int score_;             // スコア数
    int appearScore_;       // スコアの出現
    int scoreTimer_;        // スコアの出現時間
    int maxScore_;          // 最大スコア
    int pause_num_;         // ポーズ中の選択用
    float pause_alpha_;     // ポーズ中に表示するテキストのα値
    int pause_alpha_num_;   // α値を０～１まで往復させるための値
    int perfectNum_;        // パーフェクト数
    int greatNum_;          // グレイト数
    int goodNum_;           // グッド数
    int missNum_;           // ミス数
    bool playerAlive_;      // 生存確認
    VECTOR2 G_L_Fusuma_Pos_ = { 0,0 };  // 左襖位置
    VECTOR2 G_R_Fusuma_Pos_ = { 0,0 };  // 右襖位置
    int Fusuma_timer_ = 0;            // 襖タイマー
    float G_Fusuma_timer_ = 0;          // 襖が閉じ始めるまでの時間
    bool title_push_flg = false;        // タイトルへを選んだ時のフラグ
    bool restart_push_flg = false;      // 再挑戦を選んだ時のフラグ
    VECTOR2 shuriken_Pos_[11] = {};     //手裏剣位置の初期化
    float shuriken_Angle_ = 0;          //手裏剣の角度の初期化


    static const int maxAppearTime_ = 120; // 最大表示時間

    // ノーツ判定の表示時間
    int notesTimer_;
    std::ostringstream notesText;

    VECTOR2 comboSize;   // コンボの大きさ
    VECTOR2 combo2Pos;   // コンボ2の位置
    VECTOR2 combo2Size;  // コンボ2の大きさ
    VECTOR4 combo2Color; // コンボ2の色

    VECTOR2 scorePos;    // スコアの位置
    VECTOR2 scoreSize;   // スコアの大きさ
    VECTOR4 scoreColor;  // スコアの色

    VECTOR2 notesPos;    // ノーツ判定の位置
    VECTOR2 notesSize;   // ノーツ判定の大きさ
    VECTOR4 notesColor;  // ノーツ判定の色

    VECTOR2 t_EndPos;    // 文字の位置
    VECTOR2 t_EndScale;  // 文字の大きさ
    VECTOR2 t_EndSize;   // 文字の大きさ
    VECTOR4 t_EndColor;  // 文字の色

    VECTOR2 t_FullComboPos;    // 文字の位置
    VECTOR2 t_FullComboScale;  // 文字の大きさ
    VECTOR2 t_FullComboSize;   // 文字の大きさ
    VECTOR4 t_FullComboColor;  // 文字の色
public:
    enum DECISION {
        MISS,
        GOOD,
        GREAT,
        PERFECT,
        NONE
    }decision_;

    void init() override;
    void deinit() override;
    void update() override;
    void draw() override;
    
    // ゲッター
    static Game* instance() { return &instance_; }

    OBJ2DManager* obj2dManager() { return obj2dManager_; }
    BG* bg() { return bg_; }
    bool playerModeFlag() { return playerModeFlag_; }
    int stageNo() { return stageNo_; }
    bool enemyXFlip() { return enemyXFlip_; }
    int timer() { return timer_; }
    int combo() { return combo_; }
    int combo2() { return combo2_; }
    int maxCombo() { return maxCombo_; }
    int score() { return score_; }
    int appearScore() { return appearScore_; }
    int maxScore() { return maxScore_; }
    int decision() { return decision_; }
    int maxAppearTime() { return maxAppearTime_; }
    int perfectNum() { return perfectNum_; }
    int greatNum() { return greatNum_; }
    int goodNum() { return goodNum_; }
    int missNum() { return missNum_; }
    bool playerAlive() { return playerAlive_; }

    // セッター
    OBJ2D* player() const { return player_; }
    void setPlayerModeFlag(bool f) { playerModeFlag_ = f; }
    void setStageNo(int n) { stageNo_ = n; }
    void setEnemyXFlip(bool f) { enemyXFlip_ = f; }
    void setCombo(int c) { combo_ = c; }
    void setCombo2(int c) { combo2_ = c; }
    void addCombo() { combo_++; }
    void addCombo2() { combo2_++; }
    void setComboSize(VECTOR2 s) { comboSize = s; }
    void setCombo2Timer(int t) { combo2Timer_ = t; }
    void setMaxCombo(int c) { maxCombo_ = c; }
    void setScore(int s) { score_ = s; }
    void setScoreTimer(int t) { scoreTimer_ = t; }
    void setAppearScore(int s) { appearScore_ = s; }
    void addScore(int s) { score_ += s; }
    void setMaxScore(int s) { maxScore_ = s; }
    void setDecision(DECISION d) {decision_ = d; }
    void deleteCombo() { combo_ = 0; }
    void deleteCombo2() { combo2_ = 0; }
    void addPerfectNum() { perfectNum_++; }
    void addGreatNum() { greatNum_++; }
    void addGoodNum() { goodNum_++; }
    void addMissNum() { missNum_++; }
    void setPlayerAlive(bool a) { playerAlive_ = a; }

private:
    // コンストラクタ
    Game()
        :obj2dManager_(nullptr)
        , bg_(nullptr)
        , isPaused_(false)
        , player_(nullptr)
        , playerModeFlag_(false)
        , stageNo_(0)
        , enemyXFlip_(false)
        , combo_(0)
        , combo2_(0)
        , combo2Timer_(0)
        , maxCombo_(0)
        , score_(0)
        , scoreTimer_(0)
        , appearScore_(500)
        , maxScore_(0)
        , decision_(NONE)
        , notesTimer_(0)
        , hpPos01(0, 0)
        , hpSize01(0, 0)
        , hpColor01(0, 0, 0, 0)
        , hpPos02(0, 0)
        , hpSize02(0, 0)
        , hpColor02(0, 0, 0, 0)
        , pause_num_(0)
        , pause_alpha_(1.0f)
        , pause_alpha_num_(0)
        , perfectNum_(0)
        , greatNum_(0)
        , goodNum_(0)
        , missNum_(0)
        , playerAlive_(true)
        , squarePos_({0,0})
        , squareScale_({0.0f,0.0f})
        , squareAngle_(0.0f)
        , G_L_Fusuma_Pos_({ 0.0f,0.0f })  
        , G_R_Fusuma_Pos_({ 0.0f,0.0f })
        , G_Fusuma_timer_(0)
        , title_push_flg(false)
        , restart_push_flg(false)
        , Fusuma_timer_(0)

    {}
    Game(const Game&) = delete; // = delete コピーコンストラクタが存在しないことを明示
    // 当たり判定
    void judge();
    
    // コンボの計算
    void calcCombo();
    
    // コンボの描画
    void comboDraw();

    // スコアの計算
    void calcScore();

    // スコアの描画
    void scoreDraw();

    // ノーツ判定
    void decisionJudge();

    // ノーツ判定の描画
    void decisionDraw();

    // 操作方法UI
    void operationDraw();


public:
    //使用するスプライトデータ
    GameLib::SpriteData sprRestart_ = SPRITE_CENTER(static_cast<INT>(TEXNO::RESTART), 0, 0, 600, 300);
    GameLib::SpriteData sprTotitle_ = SPRITE_CENTER(static_cast<INT>(TEXNO::TOTITLE), 0, 0, 600, 300);
    GameLib::SpriteData sprL_Fusuma_ = SPRITE_CENTER(static_cast<INT>(TEXNO::L_FUSUMA), 0, 0, 960, 1080);
    GameLib::SpriteData sprR_Fusuma_ = SPRITE_CENTER(static_cast<INT>(TEXNO::R_FUSUMA), 0, 0, 960, 1080);
    GameLib::SpriteData sprShuriken_ = SPRITE_CENTER(static_cast<INT>(TEXNO::ENEMY0), 0, 0, 128, 128);
};

//******************************************************************************

