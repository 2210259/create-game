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
    enum DECISION {
        MISS,
        GOOD,
        GREAT,
        PERFECT,
        MAX
    }decision_;

public:
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
    int decision() { return decision_; }

    // セッター
    OBJ2D* player() const { return player_; }
    void setPlayerModeFlag(bool f) { playerModeFlag_ = f; }
    void setStageNo(int n) { stageNo_ = n; }
    void setEnemyXFlip(bool f) { enemyXFlip_ = f; }
    void setCombo(int c) { combo_ = c; }
    void addCombo() { combo_++; }
    void setMaxCombo(int c) { maxCombo_ = c; }
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
    {}
    Game(const Game&) = delete; // = delete コピーコンストラクタが存在しないことを明示
    // 当たり判定
    void judge();
};

//******************************************************************************

