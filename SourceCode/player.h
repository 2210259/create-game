#pragma once
//----------------------------------------//
//         �@�@Player.h    �@    �@       //
//----------------------------------------//

//----------------------------------------//
//         �@�@�ړ��A���S���Y��           //
//----------------------------------------//

class BasePlayerBehavior : public ActorBehavior
{
private:
    void moveX(OBJ2D* obj) override;
    OBJ_TYPE getType() const override { return OBJ_TYPE::PLAYER; }
    OBJ_TYPE attackType() const override { return OBJ_TYPE::ENEMY; }
    void hit(OBJ2D*, OBJ2D*) {};
};

class IdlePlayerBehavior : public BasePlayerBehavior
{
public:
    IdlePlayerBehavior();
private:
    void moveY(OBJ2D* obj) override;
    // void moveX(OBJ2D* obj) override;
    void playerAnimetion(OBJ2D* obj) override;
    void modechange(OBJ2D* obj) override;
};
EXTERN IdlePlayerBehavior idlePlayerBehavior;

class AttackPlayerBehavior :public IdlePlayerBehavior
{
public:
    AttackPlayerBehavior();
private:
    OBJ_TYPE getType() const override { return OBJ_TYPE::PLAYER; }
    OBJ_TYPE attackType() const override { return OBJ_TYPE::ENEMY; }
    void moveX(OBJ2D* obj) override;
    void modechange(OBJ2D* obj) override;
    void hit(OBJ2D* src, OBJ2D* dst) {};
};
EXTERN AttackPlayerBehavior attackPlayerBehavior;

//----------------------------------------//
//         �@�@�����A���S���Y��           //
//----------------------------------------//

class ErasePlayer : public Eraser
{
    void erase(OBJ2D* obj);
};