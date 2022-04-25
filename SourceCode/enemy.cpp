#include "all.h"
using namespace GameLib;

// 敵配置用データ
struct ENEMY_SET1
{
    int         area;       // 出現ステージ
    int         enemyType;  // 敵の種類
    int         posType;    // 出現位置(0:上 1:左 2:右)
    int         timer;      // 出現時間
} enemySet[] = {
    {  0,  0,  0,    0},  // 0
    {  0,  1,  1,    0},  // 1
    {  0,  0,  0,   60},  // 2
    {  0,  1,  0,  150},  // 3
    {  0,  1,  2,  150},  // 3
    {  0,  0,  0,  240},  // 4

    // {  1,  0, {  0,   0 },  0 }, // 2
    // {  1,  0, {  0,   0 },  0 }, // 3
    // {  1,  0, {  0,   0 },  0 }, // 4
    // {  1,  0, {  0,   0 },  0 }, // 5
    // {  1,  0, {  0,   0 },  0 }, // 6
    { -1, -1, -1,  -1 },
};

//   640, -150(上)
//  -150,  625(左)
// 1280 + 150,  625 (右)

void setEnemy(OBJ2DManager* obj2dManager, BG* bg)
{
    // 敵の種類
    BaseEnemyBehavior* enemyBehavior[] = {
        &enemy0Behavior,
        &enemy1Behavior,
        &enemy2Behavior,
    };

    for (int i = 0; enemySet[i].enemyType >= 0; ++i)
    {
        // ステージとエリアが異なればコンティニュー
        if (enemySet[i].area != Game::instance()->stageNo()) continue;

        // 敵の出現時間とゲームタイマーが異なればコンティニュー
        if (enemySet[i].timer != Game::instance()->timer()) continue;

        // 敵の生成
        OBJ2D* enemy = new OBJ2D(
            new Renderer,
            new Collider,
            bg,
            new ActorComponent,
            nullptr
        );
        // 敵の出現位置
        VECTOR2 pos = {};
        if (enemySet[i].posType == 0)      pos = {  640, -150 };         // (上)
        else if (enemySet[i].posType == 1) pos = { -150,  625 };         // (左)
        else if (enemySet[i].posType == 2) pos = { 1280 + 150,  625 };   // (右)

        obj2dManager->add(enemy,
            enemyBehavior[enemySet[i].enemyType],
            pos,
            enemySet[i].posType
        );
    }
}

//----------------------------------------//
//        敵のアニメーション              //
//----------------------------------------//
namespace
{
    //------< Enemy0のアニメデータ >---------------------------------------------
    // 攻撃
    AnimeData animeEnemy0_Idle[] = {
        { &sprEnemy0_Idle0, 5 },
        { &sprEnemy0_Idle0, 5 },
        { nullptr, -1 },// 終了フラグ
    };

    // 死亡時
    //AnimeData animeEnemy0_Dead[] = {
    //    { &sprEnemy0_Dead0, 20 },
    //    { &sprEnemy0_Dead1, 10 },
    //    { &sprEnemy0_Dead2, 10 },
    //    { nullptr, -1 },// 終了フラグ
    //};

    //------< Enemy1のアニメデータ >---------------------------------------------
    // 攻撃
    AnimeData animeEnemy1_Idle[] = {
        { &sprEnemy1_Idle0, 5 },
        { &sprEnemy1_Idle0, 5 },
        { nullptr, -1 },// 終了フラグ
    };

    // 死亡時
    //AnimeData animeEnemy1_Dead[] = {
    //    { &sprEnemy1_Dead0, 20 },
    //    { &sprEnemy1_Dead1, 10 },
    //    { &sprEnemy1_Dead2, 10 },
    //    { nullptr, -1 },// 終了フラグ
    //};

    //------< Enemy2のアニメデータ >---------------------------------------------
    // 攻撃
    AnimeData animeEnemy2_Idle[] = {
        { &sprEnemy2_Idle0, 5 },
        { &sprEnemy2_Idle0, 5 },
        { nullptr, -1 },// 終了フラグ
    };

    // 死亡時
    //AnimeData animeEnemy2_Dead[] = {
    //    { &sprEnemy2_Dead0, 20 },
    //    { &sprEnemy2_Dead1, 10 },
    //    { &sprEnemy2_Dead2, 10 },
    //    { nullptr, -1 },// 終了フラグ
    //};
}

// 敵のY座標の速度（重力）
void BaseEnemyBehavior::moveY(OBJ2D* obj)
{
    // Transform* transform = obj->transform();
    // Game::instance()->setEnemyPos(transform->position());
    
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
        // obj->renderer()->setAnimeData(getParam()->ANIME_IDLE);
    case 1:
        // obj->renderer()->setAnimeData(getParam()->ANIME_IDLE);
        break;
    }
    debug::setString("enemyState:%d", obj->enemyState());
    debug::setString("animeData:%d", obj->renderer()->animeData());
}

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
        renderer->setColor(VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
        transform->setOrgPos(transform->position());
        obj->actorComponent()->setDeadTimer(getParam()->DEAD_TIMER); // 死亡時タイマーの初期設定
        // Sounds_ = false;

        obj->addEnemyState(); // enemyState++
        break;

    case 1:
        //////// プレイヤーに攻撃中 ////////
        // 自分と敵の位置の距離を計算
        {
            auto vecP = (Game::instance()->player()->transform()->position() + VECTOR2(0, -75.0f) - obj->transform()->position());
            float dist = sqrtf(vecP.x * vecP.x + vecP.y * vecP.y);

            // スピードを計算
            obj->transform()->setSpeed(4 * vecP / dist);
        }
        break;
    case 2:
        //////// 敵が消える ////////
        obj->remove();
        break;
    }

    // HPが0以下であれば敵を消滅
    if (obj->actorComponent()->hp() <= 0)
        obj->setEnemyState(2);

    transform->addPosition(transform->speed());
}

// 敵がプレイヤーに攻撃したとき処理
void BaseEnemyBehavior::hit(OBJ2D* src, OBJ2D* dst)
{
    if (src->enemyState() > 1) return;

    // プレイヤーにダメージを与える
    dst->actorComponent()->damage();

    // コンボをなくす
    Game::instance()->deleteCombo();
    
    // 当たり判定をなくす
    // param_.ATTACK_BOX = {}; // 敵がプレイヤーに攻撃する範囲
    // param_.HIT_BOX = {};    // 敵が武器に攻撃される範囲

    // moveEnemyのstateを一つ進める
    src->addEnemyState();
}

// 敵がプレイヤーに攻撃したとき処理
// void BaseEnemyBehavior::hit2(OBJ2D* src, OBJ2D* dst)
// {
//     // プレイヤーにダメージを与える
//     dst->actorComponent()->damage();
// 
//     // 当たり判定をなくす
//     param_.ATTACK_BOX = {}; // 敵がプレイヤーに攻撃する範囲
//     param_.HIT_BOX = {};    // 敵が武器に攻撃される範囲
// 
//     // moveEnemyのstateを一つ進める
//     src->addEnemyState();
// }

Enemy0Behavior::Enemy0Behavior()
{
    param_.ANIME_IDLE = animeEnemy0_Idle;
    //param_.ANIME_DEAD = animeEnemy0_Dead;

    param_.SIZE         = VECTOR2(128 / 2, 128 / 2);
    param_.SCALE        = VECTOR2(1, 1);
    param_.ATTACK_BOX   = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // 敵がプレイヤーに攻撃する範囲
    param_.HIT_BOX      = { -128 / 6, -128 / 6, 128 / 6, 128 / 6 }; // 敵が武器に攻撃される範囲(Perfect)
    param_.HIT_BOX2     = { -128 / 3, -128 / 3, 128 / 3, 128 / 3 }; // 敵が武器に攻撃される範囲(Great)
    param_.HIT_BOX3     = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // 敵が武器に攻撃される範囲(Good)

    // param_.HIT_BOX2 = { -300 / 4, -300 / 4, 300 / 4, 300 / 4 }; // 敵が武器に攻撃される範囲

    param_.ACCEL_X = 0.4f;
    param_.ACCEL_Y = 0.4f;
    param_.SPEED_X_MAX = 1.0f;
    param_.SPEED_Y_MAX = 1.0f;
    param_.HP = 1;    // ヒットポイント
    param_.HIT_TIMER = 90;
    param_.DEAD_TIMER = 40;
}

void Enemy0Behavior::enemyAnime(OBJ2D* obj)
{
    // 回転処理
    obj->transform()->rotate(ToRadian(5));
}

Enemy1Behavior::Enemy1Behavior()
{
    param_.ANIME_IDLE = animeEnemy1_Idle;  
    //param_.ANIME_DEAD = animeEnemy1_Dead;

    param_.SIZE         = VECTOR2(128 / 2, 128 / 2);
    param_.SCALE        = VECTOR2(1, 1);
    param_.ATTACK_BOX   = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // 敵がプレイヤーに攻撃する範囲
    param_.HIT_BOX      = { -128 / 6, -128 / 6, 128 / 6, 128 / 6 }; // 敵が武器に攻撃される範囲
    param_.HIT_BOX2     = { -128 / 4, -128 / 3, 128 / 3, 128 / 3 }; // 敵が武器に攻撃される範囲
    param_.HIT_BOX3     = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // 敵が武器に攻撃される範囲

    param_.SPEED_X_MAX = 1.0f;
    param_.HP          = 1;    // ヒットポイント
    param_.DEAD_TIMER  = 40;
}

void Enemy1Behavior::enemyAnime(OBJ2D* obj)
{
    // 画像の向きを変更
    switch (obj->actorComponent()->posType())
    {
    case 0:// (上)
        obj->transform()->setRotation(ToRadian(-90));
        break;
    case 1:// (左)
        obj->transform()->setRotation(ToRadian(180));
        break;
    case 2:// (右)
        obj->transform()->setRotation(ToRadian(0));
        break;
    }
}

Enemy2Behavior::Enemy2Behavior()
{
    param_.ANIME_IDLE = animeEnemy2_Idle;  
    //param_.ANIME_DEAD = animeEnemy2_Dead;

    param_.SIZE         = VECTOR2(128 / 2, 128 / 2);
    param_.SCALE        = VECTOR2(1, 1);
    param_.ATTACK_BOX   = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // 敵がプレイヤーに攻撃する範囲
    param_.HIT_BOX      = { -128 / 6, -128 / 6, 128 / 6, 128 / 6 }; // 敵が武器に攻撃される範囲
    param_.HIT_BOX2     = { -128 / 3, -128 / 3, 128 / 3, 128 / 3 }; // 敵が武器に攻撃される範囲
    param_.HIT_BOX3     = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // 敵が武器に攻撃される範囲

    param_.ACCEL_X = 0.4f;
    param_.ACCEL_Y = 0.4f;
    param_.SPEED_X_MAX = 1.0f;
    param_.SPEED_Y_MAX = 1.0f;
    param_.HP          = 1;    // ヒットポイント
    param_.HIT_TIMER = 50;
    param_.DEAD_TIMER = 50;
}