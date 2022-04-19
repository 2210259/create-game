#pragma once

void setEnemy(OBJ2DManager* obj2dManager, BG* bg);

class BaseEnemyBehavior : public ActorBehavior
{
public:
    VECTOR4 color_ = { 1.0f, 1.0f, 1.0f, 0.0f };
    // bool Sounds_;

private:
    void moveY(OBJ2D* obj);
    void enemyAnime(OBJ2D* obj) override;
    void moveEnemy(OBJ2D* obj) override;
    OBJ_TYPE getType() const override { return OBJ_TYPE::ENEMY; }
    OBJ_TYPE attackType() const override { return OBJ_TYPE::PLAYER; }
    void hit(OBJ2D* src, OBJ2D* dst) override;
    void hit2(OBJ2D* src, OBJ2D* dst) override;
};

class Enemy0Behavior : public BaseEnemyBehavior
{
public:
    Enemy0Behavior();
};

EXTERN Enemy0Behavior enemy0Behavior;

class Enemy1Behavior : public BaseEnemyBehavior
{
public:
    Enemy1Behavior();
};

EXTERN Enemy1Behavior enemy1Behavior;

class Enemy2Behavior : public BaseEnemyBehavior
{
public:
    Enemy2Behavior();
};

EXTERN Enemy2Behavior enemy2Behavior;