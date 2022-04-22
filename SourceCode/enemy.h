#pragma once

void setEnemy(OBJ2DManager* obj2dManager, BG* bg);

class BaseEnemyBehavior : public ActorBehavior
{
private:
    void moveY(OBJ2D* obj);
    void moveX(OBJ2D* obj);
    void turn(OBJ2D* obj);
    virtual void gakeTurn(OBJ2D* obj);
    OBJ_TYPE getType() const override { return OBJ_TYPE::ENEMY; }
    OBJ_TYPE attackType() const override { return OBJ_TYPE::PLAYER; }
    void hit(OBJ2D*, OBJ2D*) {}
    bool isAlive(OBJ2D*) override;
};

class Enemy0Behavior : public BaseEnemyBehavior
{
public:
    Enemy0Behavior();
};

class Enemy1Behavior : public BaseEnemyBehavior
{
public:
    Enemy1Behavior();
private:
    void gakeTurn(OBJ2D*) override {}
};

class Enemy5Behavior : public BaseEnemyBehavior
{
public:
    Enemy5Behavior();
private:
    void moveX(OBJ2D* obj);
};

EXTERN Enemy0Behavior enemy0Behavior;
EXTERN Enemy1Behavior enemy1Behavior;
EXTERN Enemy5Behavior enemy5Behavior;
