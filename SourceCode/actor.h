class ActorBehavior : public Behavior
{
private:

protected:
    struct Param {
        // �A�j���[�V����
        GameLib::AnimeData* ANIME_RIDLE;    // �E�ҋ@
        GameLib::AnimeData* ANIME_LIDLE;    // �E�ҋ@
        GameLib::AnimeData* ANIME_IDLE;     // �ҋ@�i���ʁj
        GameLib::AnimeData* ANIME_ATTACK;   // �U�� (����)
        GameLib::AnimeData* ANIME_ATTACK_U; // �U����
        GameLib::AnimeData* ANIME_ATTACK_R; // �U���E
        GameLib::AnimeData* ANIME_ATTACK_D; // �U����
        GameLib::AnimeData* ANIME_ATTACK_L; // �U����
        GameLib::AnimeData* ANIME_UP;       
        GameLib::AnimeData* ANIME_RIGHT;
        GameLib::AnimeData* ANIME_DOWN;
        GameLib::AnimeData* ANIME_LEFT;
        GameLib::AnimeData* ANIME_DEAD;

        // �傫��
        VECTOR2 SIZE;
        VECTOR2 SCALE;
        FLOAT MARGIN; // �]��
        GameLib::fRECT HIT_BOX;     

        GameLib::fRECT HIT_BOX2;
        GameLib::fRECT HIT_BOX3;
        GameLib::fRECT HIT_BOX4;
        GameLib::fRECT HIT_BOX5;
        GameLib::fRECT HIT_BOX6;
        GameLib::fRECT HIT_BOX7;

        GameLib::fRECT ATTACK_BOX;
        GameLib::fRECT ATTACK_BOX2;

        // ���x�֘A�̃p�����[�^
        float SPEED;
        float ACCEL_X;
        float ACCEL_Y;
        float SPEED_X_MAX;
        float SPEED_Y_MAX;

        VECTOR4 RANGE_BOX;
        int HP;         // �q�b�g�|�C���g
        int SCORE;      // �X�R�A
        int HIT_TIMER;  
        int DEAD_TIMER; // ���S���^�C�}�[
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
