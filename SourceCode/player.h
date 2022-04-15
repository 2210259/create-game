#pragma once

//******************************************************************************
//
//
//      Player.h
//
//
//******************************************************************************

//------< �C���N���[�h >---------------------------------------------------------
#include "../SourceCode/obj2d.h"

class BasePlayerBehavior : public Behavior
{
protected:
    struct Param
    {
        // �A�j���[�V����
        GameLib::AnimeData* ANIME_UP = nullptr;
        GameLib::AnimeData* ANIME_RIGHT = nullptr;
        GameLib::AnimeData* ANIME_DOWN = nullptr;
        GameLib::AnimeData* ANIME_LEFT = nullptr;

        // �T�C�Y
        VECTOR2 SIZE = { 0, 0 };

        GameLib::fRECT HIT_BOX = { 0, 0, 0, 0 };

        // ���x�֘A�̃p�����[�^
        float ACCEL_X = 0.0f;
        float ACCEL_Y = 0.0f;
        float SPEED_X_MAX = 0.0f;
        float SPEED_Y_MAX = 0.0f;
        float JUMP_POWER_Y = 0.0f;
    } param_;
protected:
    const Param* getParam() const { return &param_; }
    virtual void moveY(OBJ2D* obj);
private:
    void move(OBJ2D* obj) override;
    void moveX(OBJ2D* obj);
    // virtual void jump(OBJ2D* obj) = 0;
    virtual void hashigo(OBJ2D* obj) = 0;
    void areaCheck(OBJ2D* obj);

    OBJ_TYPE getType() override { return OBJ_TYPE::PLAYER; };
    OBJ_TYPE attackType() override { return OBJ_TYPE::ENEMY; };
    void hit(OBJ2D*, OBJ2D*) override {};
};

class WalkPlayerBehavior : public BasePlayerBehavior
{
public:
    WalkPlayerBehavior();
private:
    void moveY(OBJ2D* obj) override;
    // void jump(OBJ2D* obj) override;
    void hashigo(OBJ2D* obj) override;
};
EXTERN WalkPlayerBehavior walkPlayerBehavior;

class HashigoPlayerBehavior : public BasePlayerBehavior
{
public:
    HashigoPlayerBehavior();
private:
    void moveY(OBJ2D* obj) override;
    // void jump(OBJ2D*) override {}
    void hashigo(OBJ2D* obj) override;
};
EXTERN HashigoPlayerBehavior hashigoPlayerBehavior;

//==============================================================================
//
//      �����A���S���Y��
//
//==============================================================================

// �����A���S���Y��
class ErasePlayer : public Eraser
{
    void erase(OBJ2D* obj);
};

// �����A���S���Y���̎���
//EXTERN ErasePlayer      erasePlayer;

