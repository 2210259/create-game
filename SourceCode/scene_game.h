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
    bool playerModeFlag_;  // プレイヤーモードの切り替えフラグ
    int stageNo_;          // ステージ番号
    bool enemyXFilip_;     // 敵の向きを保存

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
    bool enemyXFlip() { return enemyXFilip_; }

    // セッター
    void setPlayerModeFlag(bool f) { playerModeFlag_ = f; }
    void setStageNo(int n) { stageNo_ = n; }
    void setEnemyXFilip(bool f) { enemyXFilip_ = f; }

private:
    // コンストラクタ
    Game()
        :obj2dManager_(nullptr)
        , bg_(nullptr)
        , isPaused_(false)
        , player_(nullptr)
        , playerModeFlag_(false)
        , stageNo_(0)
        , enemyXFilip_(false)
    {}
    Game(const Game&) = delete; // = delete コピーコンストラクタが存在しないことを明示
    // 当たり判定
    void judge();
};

//******************************************************************************

