#pragma once

class ActorBehavior : public Behavior
{
protected:
    struct Param {
        // �A�j���[�V����
        GameLib::AnimeData* ANIME_UP;
        GameLib::AnimeData* ANIME_RIGHT;
        GameLib::AnimeData* ANIME_DOWN;
        GameLib::AnimeData* ANIME_LEFT;

        // �T�C�Y
        VECTOR2 SIZE;
        VECTOR2 SCALE;
        GameLib::fRECT HIT_BOX;

        // ���x�֘A�̃p�����[�^
        float ACCEL_X;
        float ACCEL_Y;
        float SPEED_X_MAX;
        float SPEED_Y_MAX;
        float JUMP_POWER_Y;
        int HP;
    }param_ = {};

protected:
    const Param* getParam() const { return &param_; }
    virtual void moveY(OBJ2D* obj);
    virtual void moveX(OBJ2D* obj);
private:
    void move(OBJ2D* obj) override;
    virtual void jump(OBJ2D*) {}
    virtual void hashigo(OBJ2D*) {}
    void areaCheck(OBJ2D* obj);
    virtual void turn(OBJ2D*) {}
    virtual void attack(OBJ2D*) {}
    virtual bool isAlive(OBJ2D*) = 0;
};
