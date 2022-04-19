class ActorBehavior : public Behavior
{
private:

protected:
    struct Param {
        // アニメーション
        GameLib::AnimeData* ANIME_RIDLE;    // 右待機
        GameLib::AnimeData* ANIME_LIDLE;    // 右待機
        GameLib::AnimeData* ANIME_UP;       
        GameLib::AnimeData* ANIME_RIGHT;
        GameLib::AnimeData* ANIME_DOWN;
        GameLib::AnimeData* ANIME_LEFT;
        GameLib::AnimeData* ANIME_DEAD;

        // サイズ
        VECTOR2 SIZE;
        VECTOR2 SCALE;
        GameLib::fRECT HIT_BOX;
        GameLib::fRECT ATTACK_BOX;
        GameLib::fRECT ATTACK_BOX2;

        // 速度関連のパラメータ
        float ACCEL_X;
        float ACCEL_Y;
        float SPEED_X_MAX;
        float SPEED_Y_MAX;

        VECTOR4 RANGE_BOX;
        int HP;
        int HIT_TIMER;
        int DEAD_TIMER;
    }param_ = {};

protected:
    const Param* getParam() const { return &param_; }
    virtual void moveY(OBJ2D* obj);
    virtual void moveX(OBJ2D* obj);
    virtual void turn(OBJ2D* obj) {};
    virtual void modechange(OBJ2D* obj) {};
    virtual void moveEnemy(OBJ2D* obj) {};
    virtual void enemyAnime(OBJ2D* obj) {};
private:
    void move(OBJ2D* obj) override;
    void areaCheck(OBJ2D* obj);
};
