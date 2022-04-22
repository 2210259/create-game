#pragma once

//******************************************************************************
//
//
//      Player.h
//
//
//******************************************************************************

//==============================================================================
//
//      �ړ��A���S���Y��
//
//==============================================================================

class BasePlayerBehavior : public ActorBehavior
{
private:
    void moveX(OBJ2D* obj) override;
    OBJ_TYPE getType() const override { return OBJ_TYPE::PLAYER; }
    OBJ_TYPE attackType() const override { return OBJ_TYPE::ENEMY; }
    void hit(OBJ2D*, OBJ2D*) override {}
    bool isAlive(OBJ2D*) override;
};

class WalkPlayerBehavior : public BasePlayerBehavior
{
public:
    WalkPlayerBehavior();
private:
    void moveY(OBJ2D* obj) override;
    void jump(OBJ2D* obj) override;
    void hashigo(OBJ2D* obj) override;
    void attack(OBJ2D* obj) override;
};
EXTERN WalkPlayerBehavior walkPlayerBehavior;

class HashigoPlayerBehavior : public BasePlayerBehavior
{
public:
    HashigoPlayerBehavior();
private:
    void moveY(OBJ2D* obj) override;
    void jump(OBJ2D*) override {}
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
