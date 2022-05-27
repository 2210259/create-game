#pragma once

void setEnemy(OBJ2DManager* obj2dManager, BG* bg);

class BaseEnemyBehavior : public ActorBehavior
{
public:
    // VECTOR4 color_ = { 1.0f, 1.0f, 1.0f, 0.0f };
    // bool Sounds_;

private:
    // void moveX(OBJ2D* obj);
    void moveY(OBJ2D* obj);
    void enemyParam(OBJ2D* obj) override;
    void moveEnemy(OBJ2D* obj) override;
    OBJ_TYPE getType() const override { return OBJ_TYPE::ENEMY; }
    OBJ_TYPE attackType() const override { return OBJ_TYPE::PLAYER; }
    void hit(OBJ2D* src, OBJ2D* dst) override;
};

// 手裏剣
class Enemy0Behavior : public BaseEnemyBehavior
{
public:
    Enemy0Behavior();
private:
    void enemyParam(OBJ2D* obj) override;
};

EXTERN Enemy0Behavior enemy0Behavior;

// クナイ
class Enemy1Behavior : public BaseEnemyBehavior
{
public:
    Enemy1Behavior();
private:
    void enemyParam(OBJ2D* obj) override;
};

EXTERN Enemy1Behavior enemy1Behavior;

// 長押しノーツ
class Enemy2Behavior : public BaseEnemyBehavior
{
public:
    Enemy2Behavior();
private:
    void enemyParam(OBJ2D* obj) override;
};

EXTERN Enemy2Behavior enemy2Behavior;

// 連打ノーツ
class Enemy3Behavior : public BaseEnemyBehavior
{
public:
    Enemy3Behavior();
private:
    void enemyParam(OBJ2D* obj) override;
};

EXTERN Enemy3Behavior enemy3Behavior;

// 手裏剣
class Enemy4Behavior : public BaseEnemyBehavior
{
public:
    Enemy4Behavior();
private:
    void enemyParam(OBJ2D* obj) override;
};

EXTERN Enemy4Behavior enemy4Behavior;
