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
    void enemyAnime(OBJ2D* obj) override;
    void moveEnemy(OBJ2D* obj) override;
    OBJ_TYPE getType() const override { return OBJ_TYPE::ENEMY; }
    OBJ_TYPE attackType() const override { return OBJ_TYPE::PLAYER; }
    void hit(OBJ2D* src, OBJ2D* dst) override;
    // void hit2(OBJ2D* src, OBJ2D* dst) override;
};

//手裏剣
class Enemy0Behavior : public BaseEnemyBehavior
{
public:
    Enemy0Behavior();
private:
    void enemyAnime(OBJ2D* obj) override;
};

EXTERN Enemy0Behavior enemy0Behavior;

//クナイ
class Enemy1Behavior : public BaseEnemyBehavior
{
public:
    Enemy1Behavior();
private:
    void enemyAnime(OBJ2D* obj) override;
};

EXTERN Enemy1Behavior enemy1Behavior;

//長押し　上
class Enemy2Behavior : public BaseEnemyBehavior
{
public:
    Enemy2Behavior();
};

EXTERN Enemy2Behavior enemy2Behavior;

//長押し　横
class Enemy3Behavior : public BaseEnemyBehavior
{
public:
    Enemy3Behavior();
};

EXTERN Enemy3Behavior enemy3Behavior;

//連打(仮)
class Enemy4Behavior : public BaseEnemyBehavior
{
public:
    Enemy4Behavior();
};

EXTERN Enemy4Behavior enemy4Behavior;