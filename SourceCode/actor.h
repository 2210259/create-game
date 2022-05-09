class ActorBehavior : public Behavior
{
private:

protected:
    struct Param {
        // アニメーション
        GameLib::AnimeData* ANIME_RIDLE;    // 右待機
        GameLib::AnimeData* ANIME_LIDLE;    // 右待機
        GameLib::AnimeData* ANIME_IDLE;     // 待機（正面）
        GameLib::AnimeData* ANIME_ATTACK;   // 攻撃 (正面)
        GameLib::AnimeData* ANIME_ATTACK_U; // 攻撃上
        GameLib::AnimeData* ANIME_ATTACK_R; // 攻撃右
        GameLib::AnimeData* ANIME_ATTACK_D; // 攻撃下
        GameLib::AnimeData* ANIME_ATTACK_L; // 攻撃左
        GameLib::AnimeData* ANIME_UP;       
        GameLib::AnimeData* ANIME_RIGHT;
        GameLib::AnimeData* ANIME_DOWN;
        GameLib::AnimeData* ANIME_LEFT;
        GameLib::AnimeData* ANIME_DEAD;

        // 大きさ
        VECTOR2 SIZE;
        VECTOR2 SCALE;
        FLOAT MARGIN; // 余白
        GameLib::fRECT HIT_BOX;     

        GameLib::fRECT HIT_BOX2;
        GameLib::fRECT HIT_BOX3;
        GameLib::fRECT HIT_BOX4;
        GameLib::fRECT HIT_BOX5;
        GameLib::fRECT HIT_BOX6;
        GameLib::fRECT HIT_BOX7;

        GameLib::fRECT ATTACK_BOX;
        GameLib::fRECT ATTACK_BOX2;

        // 速度関連のパラメータ
        float SPEED;
        float ACCEL_X;
        float ACCEL_Y;
        float SPEED_X_MAX;
        float SPEED_Y_MAX;

        VECTOR4 RANGE_BOX;
        int HP;         // ヒットポイント
        int SCORE;      // スコア
        int HIT_TIMER;  
        int DEAD_TIMER; // 死亡時タイマー
        bool FLAG_DELETE_COMBO2;   
    }param_ = {};

protected:
    const Param* getParam() const { return &param_; }
    virtual void moveY(OBJ2D* obj);
    virtual void moveX(OBJ2D* obj);
    virtual void modechange(OBJ2D* obj) {};
    virtual void moveEnemy(OBJ2D* obj) {};
    virtual void enemyParam(OBJ2D* obj) {};
    virtual void playerAnimetion(OBJ2D* obj) {};
private:
    void move(OBJ2D* obj) override;
    void areaCheck(OBJ2D* obj);
};
