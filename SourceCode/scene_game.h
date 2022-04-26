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
    int maxCombo_;          // 最大コンボ
    int score_;             // スコア数
    int maxScore_;          // 最大スコア

    // ノーツ判定の表示時間(仮)
    int goodTimer;
    int greatTimer;
    int perfectTimer;

public:
    enum DECISION {
        MISS,
        GOOD,
        GREAT,
        PERFECT,
        MAX
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
    int maxCombo() { return maxCombo_; }
    int score() { return score_; }
    int maxScore() { return maxScore_; }
    int decision() { return decision_; }

    // セッター
    OBJ2D* player() const { return player_; }
    void setPlayerModeFlag(bool f) { playerModeFlag_ = f; }
    void setStageNo(int n) { stageNo_ = n; }
    void setEnemyXFlip(bool f) { enemyXFlip_ = f; }
    void setCombo(int c) { combo_ = c; }
    void addCombo() { combo_++; }
    void setMaxCombo(int c) { maxCombo_ = c; }
    void setScore(int s) { score_ = s; }
    void addScore(int s) { score_ += s; }
    void setMaxScore(int c) { maxScore_ = c; }
    void setDecision(DECISION d) {decision_ = d; }
    void deleteCombo() { combo_ = 0; }

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
        , maxCombo_(0)
        , score_(0)
        , maxScore_(0)
        , decision_(MISS)
        , goodTimer(0)
        , greatTimer(0)
        , perfectTimer(0)
        , hpPos01(0, 0)
        , hpSize01(0, 0)
        , hpColor01(0, 0, 0, 0)
        , hpPos02(0, 0)
        , hpSize02(0, 0)
        , hpColor02(0, 0, 0, 0)
    {}
    Game(const Game&) = delete; // = delete コピーコンストラクタが存在しないことを明示
    // 当たり判定
    void judge();
    
    // 最大コンボの計算
    void calcMaxCombo();
    
    // コンボの描画
    void comboDraw();

    // スコアの描画
    void scoreDraw();

    // ノーツ判定
    void decisionJudge();

    // ノーツ判定の描画
    void decisionDraw();
};

//******************************************************************************

