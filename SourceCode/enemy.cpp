#include "all.h"
using namespace GameLib;

// 敵配置用データ
struct ENEMY_SET1
{
    int         area;
    int         enemyType;
    VECTOR2     pos;
} enemySet[] = {
    {  1,  0, {  640, 100 } }, // 0
    {  1,  0, {   10,  10 } }, // 1
    // {  1,  0, {  0,   0 } }, // 2
    // {  1,  0, {  0,   0 } }, // 3
    // {  1,  0, {  0,   0 } }, // 4
    // {  1,  0, {  0,   0 } }, // 5
    // {  1,  0, {  0,   0 } }, // 6
    { -1, -1, { -1,  -1 } },
};

void setEnemy(OBJ2DManager* obj2dManager, BG* bg)
{
    BaseEnemyBehavior* enemyBehavior[] = {
        &enemy0Behavior,
        &enemy1Behavior,
        &enemy2Behavior,
    };

    for (int i = 0; enemySet[i].enemyType >= 0; ++i)
    {
        // ステージとエリアが異なればコンティニュー
        if (enemySet[i].area != Game::instance()->stageNo()) continue;
        OBJ2D* enemy = new OBJ2D(
            new Renderer,
            new Collider,
            bg,
            new ActorComponent,
            nullptr
        );
        obj2dManager->add(enemy,
            enemyBehavior[enemySet[i].enemyType],
            enemySet[i].pos
        );
    }
}

//----------------------------------------//
//        敵のアニメーション              //
//----------------------------------------//
namespace
{
    //------< Enemy0のアニメデータ >---------------------------------------------
    // 左方向
    AnimeData animeEnemy0_Left[] = {
        { &sprEnemy0_Left0, 10 },
        { &sprEnemy0_Left1, 10 },
        { nullptr, -1 },// 終了フラグ
    };

    // 右方向
    AnimeData animeEnemy0_Right[] = {
        { &sprEnemy0_Right0, 10 },
        { &sprEnemy0_Right1, 10 },
        { nullptr, -1 },// 終了フラグ
    };

    // 死亡時
    AnimeData animeEnemy0_Dead[] = {
        { &sprEnemy0_Dead0, 20 },
        { &sprEnemy0_Dead1, 10 },
        { &sprEnemy0_Dead2, 10 },
        { nullptr, -1 },// 終了フラグ
    };

    //------< Enemy1のアニメデータ >---------------------------------------------
    // 左方向
    AnimeData animeEnemy1_Left[] = {
        { &sprEnemy1_Left0, 10 },
        { &sprEnemy1_Left1, 10 },
        { nullptr, -1 },// 終了フラグ
    };

    // 右方向
    AnimeData animeEnemy1_Right[] = {
        { &sprEnemy1_Right0, 10 },
        { &sprEnemy1_Right1, 10 },
        { nullptr, -1 },// 終了フラグ
    };

    // 死亡時
    AnimeData animeEnemy1_Dead[] = {
        { &sprEnemy1_Dead0, 20 },
        { &sprEnemy1_Dead1, 10 },
        { &sprEnemy1_Dead2, 10 },
        { nullptr, -1 },// 終了フラグ
    };

    //------< Enemy2のアニメデータ >---------------------------------------------
    // 左方向
    AnimeData animeEnemy2_Left[] = {
        { &sprEnemy2_Left0, 10 },
        { &sprEnemy2_Left1, 10 },
        { nullptr, -1 },// 終了フラグ
    };

    // 右方向
    AnimeData animeEnemy2_Right[] = {
        { &sprEnemy2_Right0, 10 },
        { &sprEnemy2_Right1, 10 },
        { nullptr, -1 },// 終了フラグ
    };

    // 死亡時
    AnimeData animeEnemy2_Dead[] = {
        { &sprEnemy2_Dead0, 20 },
        { &sprEnemy2_Dead1, 10 },
        { &sprEnemy2_Dead2, 10 },
        { nullptr, -1 },// 終了フラグ
    };
}

// 敵のY座標の速度（重力）
void BaseEnemyBehavior::moveY(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    //Game::instance()->setEnemyPos(transform->position());
    // 速度に加速度を加える
    // transform->addSpeedY( getParam()->ACCEL_Y );

    // ActorBehavior::moveY(obj);
}

void BaseEnemyBehavior::enemyAnime(OBJ2D* obj)
{
    switch (obj->enemyState())
    {
    case 0:
        //////// 初期設定 ////////
        break;
    }
}

// TODO:moveEnemy
// 餌に敵が近づく
void BaseEnemyBehavior::moveEnemy(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();
    Collider* collider = obj->collider();

    switch (obj->enemyState())
    {
    case 0:
        //////// 初期設定 ////////
        transform->setScale(getParam()->SCALE);
        collider->setSize(getParam()->SIZE);
        collider->setJudgeFlag(true);
        renderer->setColor(VECTOR4(1.0f, 1.0f, 1.0f, 0.0f));
        transform->setOrgPos(transform->position());
        obj->actorComponent()->setDeadTimer(getParam()->DEAD_TIMER); // 死亡時タイマーの初期設定
        // Sounds_ = false;

        obj->nextEnemyState(); // enemyState++
        break;

    case 1:
        //////// 待機中 ////////

        break;
    }

    ActorBehavior::moveX(obj);
    ActorBehavior::moveY(obj);
}

// 敵が餌に食いついたときの処理
void BaseEnemyBehavior::hit(OBJ2D* src, OBJ2D* dst)
{

}

// 餌が敵の感知範囲に入った時の処理
void BaseEnemyBehavior::hit2(OBJ2D* src, OBJ2D* dst)
{
}

Enemy0Behavior::Enemy0Behavior()
{
    param_.ANIME_LEFT = animeEnemy0_Left;
    param_.ANIME_RIGHT = animeEnemy0_Right;
    param_.ANIME_DEAD = animeEnemy0_Dead;

    param_.SIZE = VECTOR2(600 / 2, 600 / 2);
    param_.SCALE = VECTOR2(1, 1);
    param_.ATTACK_BOX = { -300 / 4, -300 / 4, 300 / 4, 300 / 4 }; // 敵が餌に食いつく範囲
    param_.ATTACK_BOX2 = { -300, -300, 300, 300 };                 // 感知範囲
    param_.HIT_BOX = { -300 / 4, -300 / 4, 300 / 4, 300 / 4 }; // 敵がプレイヤーに回収される

    param_.ACCEL_X = 0.4f;
    param_.ACCEL_Y = 0.4f;
    param_.SPEED_X_MAX = 1.0f;
    param_.SPEED_Y_MAX = 1.0f;
    // param_.HP           = 10;
    param_.HIT_TIMER = 90;
    param_.DEAD_TIMER = 40;
}

Enemy1Behavior::Enemy1Behavior()
{
    param_.ANIME_LEFT = animeEnemy1_Left;
    param_.ANIME_RIGHT = animeEnemy1_Right;
    param_.ANIME_DEAD = animeEnemy1_Dead;

    param_.SIZE = VECTOR2(740 / 2, 380 / 2);
    param_.SCALE = VECTOR2(1, 1);
    param_.ATTACK_BOX = { -370 / 4, -190 / 4, 370 / 4, 190 / 4 }; // 敵がプレイヤーに回収される
    param_.ATTACK_BOX2 = { -370, -190, 370, 190 };                 // 感知範囲
    param_.HIT_BOX = { -370 / 4, -190 / 4, 370 / 4, 190 / 4 }; // 敵が餌に食いつく範囲

    param_.ACCEL_X = 0.4f;
    param_.ACCEL_Y = 0.4f;
    param_.SPEED_X_MAX = 1.0f;
    param_.SPEED_Y_MAX = 1.0f;
    // param_.HP           = 10;
    param_.HIT_TIMER = 75;
    param_.DEAD_TIMER = 40;
}

Enemy2Behavior::Enemy2Behavior()
{
    param_.ANIME_LEFT = animeEnemy2_Left;
    param_.ANIME_RIGHT = animeEnemy2_Right;
    param_.ANIME_DEAD = animeEnemy2_Dead;

    param_.SIZE = VECTOR2(600 / 2, 600 / 2);
    param_.SCALE = VECTOR2(1, 1);
    param_.ATTACK_BOX = { -125 / 2, -325 / 2, 125 / 2, 325 / 2 }; // 敵が餌に食いつく範囲
    param_.ATTACK_BOX2 = { -125, -325, 125, 325 };                 // 感知範囲
    param_.HIT_BOX = { -125 / 2, -325 / 2, 125 / 2, 325 / 2 }; // 敵がプレイヤーに回収される範囲

    param_.ACCEL_X = 0.4f;
    param_.ACCEL_Y = 0.4f;
    param_.SPEED_X_MAX = 1.0f;
    param_.SPEED_Y_MAX = 1.0f;
    // param_.HP           = 1;
    param_.HIT_TIMER = 50;
    param_.DEAD_TIMER = 50;
}