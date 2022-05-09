#include "all.h"
using namespace GameLib;

// TODO：敵データの作成

// 敵配置用データ
struct ENEMY_SET1
{
    int         area;       // 出現ステージ
    int         enemyType;  // 敵の種類(0:手裏剣 1:クナイ 2:長押しノーツ 3:連打ノーツ)
    int         posType;    // 出現位置(0:上 1:左 2:右)
    VECTOR2     scale;      // 敵の大きさ(※長さを決める所以外は0に設定する。左がX軸の大きさ、右がY軸の大きさ { X , Y }) 例えば横1.5倍にしたいとき{ 1.5f, 0 }と書く;
    float       timer;      // 出現時間(※出現時間が0秒だとバグるかも)(例えば1.5秒に設定したいときは1.5fとfを数字の後ろにつける)
} enemySet[] = {
    {  0,  2,  0, {   0,   0 },  1, },  // 長押しノーツ(上)
    {  0,  2,  1, {   0,   0 },  3, },  // 長押しノーツ(左)
    {  0,  2,  2, {   0,   0 },  5, },  // 長押しノーツ(右)
    {  0,  3,  0, {   0,   0 },  7, },  // 連打ノーツ(上)
    {  0,  3,  1, {   0,   0 },  9, },  // 連打ノーツ(左)
    {  0,  3,  2, {   0,   0 }, 11, },  // 連打ノーツ(右)

    {  0,  0,  0, {   0,   0 }, 13, },  // 手裏剣(上)
    {  0,  0,  1, {   0,   0 }, 14, },  // 手裏剣(左)
    {  0,  0,  2, {   0,   0 }, 15, },  // 手裏剣(右)
    {  0,  1,  0, {   0,   0 }, 16, },  // クナイ(上)
    {  0,  1,  1, {   0,   0 }, 17, },  // クナイ(左)
    {  0,  1,  2, {   0,   0 }, 18, },  // クナイ(右)

    // {  0,  0,  0, {   0,   0 }, 19, },  // 
    // {  0,  0,  1, {   0,   0 }, 20, },  // 
    // {  0,  0,  2, {   0,   0 }, 21, },  // 
    // {  0,  1,  1, {   0,   0 }, 25, },  // 

    { -1, -1, -1, { -1, -1 }, -1 }, // ※これ消さないように
};

void setEnemy(OBJ2DManager* obj2dManager, BG* bg)
{
    // 敵の種類
    BaseEnemyBehavior* enemyBehavior[] = {
        &enemy0Behavior,    // 手裏剣
        &enemy1Behavior,    // クナイ
        &enemy2Behavior,    // 長押しノーツ
        &enemy3Behavior,    // 連打ノーツ
    };

    for (int i = 0; enemySet[i].enemyType >= 0; ++i)
    {
        // ステージとエリアが異なればコンティニュー
        if (enemySet[i].area != Game::instance()->stageNo()) continue;

        // 敵の出現時間とゲームタイマーが異なればコンティニュー
        if (static_cast<int>(enemySet[i].timer * 60) != Game::instance()->timer()) continue;

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
        float posY = Game::instance()->player()->transform()->position().y - (Game::instance()->player()->collider()->size().y / 2);
        if (enemySet[i].posType == 0)      pos = { BG::WINDOW_W / 2, -500 };    // (上)
        else if (enemySet[i].posType == 1) pos = { -500, posY };                // (左)
        else if (enemySet[i].posType == 2) pos = { BG::WINDOW_W + 500, posY };  // (右)

        obj2dManager->add(enemy,
            enemyBehavior[enemySet[i].enemyType],
            pos,
            enemySet[i].posType, enemySet[i].scale
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

    //------< Enemy3のアニメデータ >---------------------------------------------
    // 攻撃
    AnimeData animeEnemy3_Idle[] = {
        { &sprEnemy3_Idle0, 5 },
        { &sprEnemy3_Idle0, 5 },
        { nullptr, -1 },// 終了フラグ
    };

    // 死亡時
    //AnimeData animeEnemy3_Dead[] = {
    //    { &sprEnemy3_Dead0, 20 },
    //    { &sprEnemy3_Dead1, 10 },
    //    { &sprEnemy3_Dead2, 10 },
    //    { nullptr, -1 },// 終了フラグ
    //};

    //------< Enemy4のアニメデータ >---------------------------------------------
    // 攻撃
    AnimeData animeEnemy4_Idle[] = {
        { &sprEnemy4_Idle0, 5 },
        { &sprEnemy4_Idle0, 5 },
        { nullptr, -1 },// 終了フラグ
    };

    // 死亡時
    //AnimeData animeEnemy4_Dead[] = {
    //    { &sprEnemy4_Dead0, 20 },
    //    { &sprEnemy4_Dead1, 10 },
    //    { &sprEnemy4_Dead2, 10 },
    //    { nullptr, -1 },// 終了フラグ
    //};

    //------< Enemy5のアニメデータ >---------------------------------------------
    // 攻撃
    AnimeData animeEnemy5_Idle[] = {
        { &sprEnemy5_Idle0, 5 },
        { &sprEnemy5_Idle0, 5 },
        { nullptr, -1 },// 終了フラグ
    };

    // 死亡時
    //AnimeData animeEnemy5_Dead[] = {
    //    { &sprEnemy5_Dead0, 20 },
    //    { &sprEnemy5_Dead1, 10 },
    //    { &sprEnemy5_Dead2, 10 },
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

void BaseEnemyBehavior::enemyParam(OBJ2D* obj)
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
    // debug::setString("enemyState:%d", obj->enemyState());
    // debug::setString("animeData:%d", obj->renderer()->animeData());
}

// 敵の動き
void BaseEnemyBehavior::moveEnemy(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();
    Collider* collider = obj->collider();

    switch (obj->enemyState())
    {
    case 0: {
        //////// 初期設定 ////////
        collider->setSize(param_.SIZE);
        const VECTOR2 size = {
            collider->size().x * transform->scale().x,
            collider->size().y * transform->scale().y,
        };
        collider->setSize(size);
        collider->setJudgeFlag(true);
        collider->setJudgeBoxFlag(true);    // あたり判定を行う
        renderer->setColor(VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
        transform->setOrgPos(transform->position());
        obj->collider()->setJudgeFlag(true);
        obj->actorComponent()->setScore(getParam()->SCORE); // スコアの設定
        obj->actorComponent()->setDeleteCombo2Flag(param_.FLAG_DELETE_COMBO2);
        obj->actorComponent()->setDeadTimer(getParam()->DEAD_TIMER); // 死亡時タイマーの初期設定

        obj->addEnemyState(); // enemyState++
        break;
    }
    case 1:
        //////// プレイヤーに攻撃中 ////////
        // 自分と敵の位置の距離を計算してスピードを設定
    {
        // auto vecP = (Game::instance()->player()->transform()->position() + VECTOR2(0, -75.0f) - obj->transform()->position());
        // float dist = sqrtf(vecP.x * vecP.x + vecP.y * vecP.y);
        // 
        // // スピードを計算
        // if (!(dist < 1.0f && dist > -1.0f))
        //     obj->transform()->setSpeed(4 * vecP / dist);
        // else
        //     obj->transform()->setSpeed(VECTOR2(0.0f, 0.0f));

        obj->addEnemyState(); // enemyState++
        break;
    }
    case 2:

        break;
    case 3:
        //////// 敵が消える ////////
        obj->remove();
        break;
    }
    // debug::setString("size.x:%f", collider->size().x);
    // debug::setString("size.y:%f", collider->size().y);

    debug::setString("speed.x:%f", transform->speed().x);
    debug::setString("speed.y:%f", transform->speed().y);

    // HPが0以下であれば敵を消滅
    if (obj->actorComponent()->hp() <= 0)
        obj->setEnemyState(2);

    transform->addPosition(transform->speed());
}

// 敵がプレイヤーに攻撃したとき処理
void BaseEnemyBehavior::hit(OBJ2D* src, OBJ2D* dst)
{
    // falseの場合処理をしない
    if (src->collider()->judgeFlag() == false) return;
    
    // ジャッジフラグをなくす
    src->collider()->setJudgeFlag(false);
    
    // 通常ノーツがプレイヤーに当たった時のみ
    if (src->behavior() != &enemy2Behavior && src->behavior() != &enemy3Behavior) {

        // プレイヤーにダメージを与える
        dst->actorComponent()->damage();

        // ノーツ判定を送る
        Game::instance()->setDecision(Game::instance()->MISS);

        // コンボをなくす
        Game::instance()->deleteCombo();

        // コンボのサイズを設定
        Game::instance()->setComboSize(VECTOR2(2, 2));

        // ミスカウント 
        Game::instance()->addMissNum();
    }
    // 敵を消滅
    src->remove();
}

// 手裏剣
Enemy0Behavior::Enemy0Behavior()
{
    param_.ANIME_IDLE = animeEnemy0_Idle;
    //param_.ANIME_DEAD = animeEnemy0_Dead;

    param_.SIZE         = VECTOR2(128, 128);
    param_.SCALE        = VECTOR2(1.5f, 1.5f);
    const VECTOR2 size = {
        param_.SIZE.x * param_.SCALE.x,
        param_.SIZE.y * param_.SCALE.y
    };
    param_.ATTACK_BOX   = { -size.x / 2, -size.y / 2, size.x / 2, size.y / 2 }; // 敵がプレイヤーに攻撃する範囲
    param_.HIT_BOX      = { -size.x / 6, -size.y / 6, size.x / 6, size.y / 6 }; // 敵が武器に攻撃される範囲(Perfect)
    param_.HIT_BOX2     = { -size.x / 3, -size.y / 3, size.x / 3, size.y / 3 }; // 敵が武器に攻撃される範囲(Great)
    param_.HIT_BOX3     = { -size.x / 2, -size.y / 2, size.x / 2, size.y / 2 }; // 敵が武器に攻撃される範囲(Good)

    // param_.HIT_BOX2 = { -300 / 4, -300 / 4, 300 / 4, 300 / 4 }; // 敵が武器に攻撃される範囲

    param_.SPEED       = 6.0f;
    param_.SPEED_Y_MAX = 6.0f;
    param_.SPEED_X_MAX = 3.0f;
    param_.HP = 1;    // ヒットポイント
    param_.SCORE = 300;
    param_.HIT_TIMER = 90;
    param_.DEAD_TIMER = 40;
}

void Enemy0Behavior::enemyParam(OBJ2D* obj)
{
    // 出てくる位置によってスピードを設定
    switch (obj->actorComponent()->posType())
    {
    case 0:// (位置が上の時)
        obj->transform()->setSpeedY(param_.SPEED);
        break;
    case 1:// (位置が左の時)
        obj->transform()->setSpeedX(param_.SPEED);
        break;
    case 2:// (位置が右の時)
        obj->transform()->setSpeedX(-param_.SPEED);
        break;
    }
    // 回転処理
    obj->transform()->rotate(ToRadian(10));
}

// クナイ
Enemy1Behavior::Enemy1Behavior()
{
    param_.ANIME_IDLE = animeEnemy1_Idle;
    //param_.ANIME_DEAD = animeEnemy1_Dead;

    param_.SIZE         = VECTOR2(128, 128);
    param_.SCALE        = VECTOR2(1.5f, 1.5f);
    const VECTOR2 size = {
        param_.SIZE.x * param_.SCALE.x,
        param_.SIZE.y * param_.SCALE.y
    };
    param_.ATTACK_BOX   = { -size.x / 2, -size.y / 2, size.x / 2, size.y / 2 }; // 敵がプレイヤーに攻撃する範囲
    param_.HIT_BOX      = { -size.x / 6, -size.y / 6, size.x / 6, size.y / 6 }; // 敵が武器に攻撃される範囲
    param_.HIT_BOX2     = { -size.x / 3, -size.y / 3, size.x / 3, size.y / 3 }; // 敵が武器に攻撃される範囲
    param_.HIT_BOX3     = { -size.x / 2, -size.y / 2, size.x / 2, size.y / 2 }; // 敵が武器に攻撃される範囲

    param_.SPEED        = 10.0f;
    param_.SPEED_Y_MAX  = 10.0f;
    param_.SPEED_X_MAX  = 5.0f;
    param_.HP           = 1;    // ヒットポイント
    param_.SCORE        = 500;
    param_.DEAD_TIMER   = 40;
}

void Enemy1Behavior::enemyParam(OBJ2D* obj)
{
    // 出てくる位置によって画像の向きとスピードの設定
    switch (obj->actorComponent()->posType())
    {
    case 0:// (位置が上の時)
        obj->transform()->setRotation(ToRadian(-90));
        obj->transform()->setSpeedY(param_.SPEED);
        break;
    case 1:// (位置が左の時)
        obj->transform()->setRotation(ToRadian(180));
        obj->transform()->setSpeedX(param_.SPEED);
        break;
    case 2:// (位置が右の時)
        obj->transform()->setRotation(ToRadian(0));
        obj->transform()->setSpeedX(-param_.SPEED);
        break;
    }
    // debug::setString("obj->actorComponent()->posType():%d", obj->actorComponent()->posType());
}

// 長押しノーツ
Enemy2Behavior::Enemy2Behavior()
{
    param_.ANIME_IDLE = animeEnemy3_Idle;
    // param_.ANIME_DEAD = animeEnemy3_Dead;

    param_.SIZE  = VECTOR2(512, 128);
    param_.SCALE = VECTOR2(1, 1);
    param_.HIT_BOX  = { 512 / 2 - (128 / 6), -128 / 2, 512 / 2 + (128 / 6), 128 / 2 }; // 敵が武器に攻撃される範囲
    param_.HIT_BOX2 = { 512 / 2 - (128 / 3), -128 / 2, 512 / 2 + (128 / 3), 128 / 2 }; // 敵が武器に攻撃される範囲
    param_.HIT_BOX3 = { 512 / 2 - (128 / 2), -128 / 2, 512 / 2 + (128 / 2), 128 / 2 }; // 敵が武器に攻撃される範囲

    param_.HIT_BOX4 = { -512 / 2 - (128 / 2), -128 / 2,  512 / 2 + (128 / 2), 128 / 2 }; // 敵が武器に攻撃される範囲
                                                                              
    param_.HIT_BOX5 = { -512 / 2 - (128 / 6), -128 / 2, -512 / 2 + (128 / 6), 128 / 2 }; // 敵が武器に攻撃される範囲
    param_.HIT_BOX6 = { -512 / 2 - (128 / 3), -128 / 2, -512 / 2 + (128 / 3), 128 / 2 }; // 敵が武器に攻撃される範囲
    param_.HIT_BOX7 = { -512 / 2 - (128 / 2), -128 / 2, -512 / 2 + (128 / 2), 128 / 2 }; // 敵が武器に攻撃される範囲
    // param_.ATTACK_BOX   = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // 敵がプレイヤーに攻撃する範囲

    param_.SPEED        = 6.0f;
    param_.SPEED_Y_MAX  = 6.0f;
    param_.SPEED_X_MAX  = 3.0f;
    param_.HP           = 1;    // ヒットポイント
    param_.SCORE        = 1000; // ノーツのスコア点数
    param_.HIT_TIMER    = 50;
    param_.DEAD_TIMER   = 50;
}

// 長押しノーツ
void Enemy2Behavior::enemyParam(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();
    Collider* collider = obj->collider();

    // 出てくる位置によって画像の向きとスピードの設定
    switch (obj->actorComponent()->posType())
    {
    case 0: { // (位置が上の時)
        param_.ANIME_IDLE = animeEnemy2_Idle;
        obj->renderer()->setAnimeData(getParam()->ANIME_IDLE);
        param_.SIZE = VECTOR2(128, 512);
        collider->setSize(param_.SIZE);
        transform->setScale(transform->orgScale());
        const VECTOR2 size = {
            collider->size().x * transform->scale().x,
            collider->size().y * transform->scale().y,
        };
        collider->setSize(size);
        obj->transform()->setSpeedY(param_.SPEED);
        param_.HIT_BOX  = { -size.x / 2, size.y / 2 - (size.x / 6), size.x / 2, size.y / 2 + (size.x / 6) }; // 敵が武器に攻撃される範囲
        param_.HIT_BOX2 = { -size.x / 2, size.y / 2 - (size.x / 3), size.x / 2, size.y / 2 + (size.x / 3) }; // 敵が武器に攻撃される範囲
        param_.HIT_BOX3 = { -size.x / 2, size.y / 2 - (size.x / 2), size.x / 2, size.y / 2 + (size.x / 2) }; // 敵が武器に攻撃される範囲
        
        param_.HIT_BOX4 = { -size.x / 2, -size.y / 2 - (size.x / 2), size.x / 2, size.y / 2 + (size.x / 2) }; // 敵が武器に攻撃される範囲
        
        param_.HIT_BOX5 = { -size.x / 2, -size.y / 2 - (size.x / 6), size.x / 2, -size.y / 2 + (size.x / 6) }; // 敵が武器に攻撃される範囲
        param_.HIT_BOX6 = { -size.x / 2, -size.y / 2 - (size.x / 3), size.x / 2, -size.y / 2 + (size.x / 3) }; // 敵が武器に攻撃される範囲
        param_.HIT_BOX7 = { -size.x / 2, -size.y / 2 - (size.x / 2), size.x / 2, -size.y / 2 + (size.x / 2) }; // 敵が武器に攻撃される範囲

        param_.ATTACK_BOX = { -size.x / 2, -size.y - (size.x / 6), size.x / 2, -size.y + (size.x / 6) }; // 敵がプレイヤーに攻撃する範囲
        break;
    }
    case 1: { // (位置が左の時)
        param_.ANIME_IDLE = animeEnemy3_Idle;
        obj->renderer()->setAnimeData(getParam()->ANIME_IDLE);
        param_.SIZE = VECTOR2(512, 128);
        collider->setSize(param_.SIZE);
        transform->setScale(transform->orgScale());
        const VECTOR2 size = {
            collider->size().x * transform->scale().x,
            collider->size().y * transform->scale().y,
        };
        collider->setSize(size);
        obj->transform()->setSpeedX(param_.SPEED);
        param_.HIT_BOX  = { size.x / 2 - (size.y / 6), -size.y / 2, size.x / 2 + (size.y / 6), size.y / 2 }; // 敵が武器に攻撃される範囲
        param_.HIT_BOX2 = { size.x / 2 - (size.y / 3), -size.y / 2, size.x / 2 + (size.y / 3), size.y / 2 }; // 敵が武器に攻撃される範囲
        param_.HIT_BOX3 = { size.x / 2 - (size.y / 2), -size.y / 2, size.x / 2 + (size.y / 2), size.y / 2 }; // 敵が武器に攻撃される範囲

        param_.HIT_BOX4 = { -size.x / 2 - (size.y / 2), -size.y / 2,  size.x / 2 + (size.y / 2), size.y / 2 }; // 敵が武器に攻撃される範囲

        param_.HIT_BOX5 = { -size.x / 2 - (size.y / 6), -size.y / 2, -size.x / 2 + (size.y / 6), size.y / 2 }; // 敵が武器に攻撃される範囲
        param_.HIT_BOX6 = { -size.x / 2 - (size.y / 3), -size.y / 2, -size.x / 2 + (size.y / 3), size.y / 2 }; // 敵が武器に攻撃される範囲
        param_.HIT_BOX7 = { -size.x / 2 - (size.y / 2), -size.y / 2, -size.x / 2 + (size.y / 2), size.y / 2 }; // 敵が武器に攻撃される範囲

        param_.ATTACK_BOX = { -size.x - (size.y / 6), -size.y / 2, -size.x + (size.y / 6), size.y / 2 }; // 敵がプレイヤーに攻撃する範囲

        break;
    }
    case 2: { // (位置が右の時)
        param_.ANIME_IDLE = animeEnemy3_Idle;
        obj->renderer()->setAnimeData(getParam()->ANIME_IDLE);
        param_.SIZE = VECTOR2(512, 128);
        collider->setSize(param_.SIZE);
        transform->setScale(transform->orgScale());
        const VECTOR2 size = {
            collider->size().x * transform->scale().x,
            collider->size().y * transform->scale().y,
        };
        collider->setSize(size);
        obj->transform()->setSpeedX(-param_.SPEED);
        param_.HIT_BOX = { -size.x / 2 - (size.y / 6), -size.y / 2, -size.x / 2 + (size.y / 6), size.y / 2 }; // 敵が武器に攻撃される範囲
        param_.HIT_BOX2 = { -size.x / 2 - (size.y / 3), -size.y / 2, -size.x / 2 + (size.y / 3), size.y / 2 }; // 敵が武器に攻撃される範囲
        param_.HIT_BOX3 = { -size.x / 2 - (size.y / 2), -size.y / 2, -size.x / 2 + (size.y / 2), size.y / 2 }; // 敵が武器に攻撃される範囲

        param_.HIT_BOX4 = { -size.x / 2 - (size.y / 2), -size.y / 2,  size.x / 2 + (size.y / 2), size.y / 2 }; // 敵が武器に攻撃される範囲

        param_.HIT_BOX5 = { size.x / 2 - (size.y / 6), -size.y / 2, size.x / 2 + (size.y / 6), size.y / 2 }; // 敵が武器に攻撃される範囲
        param_.HIT_BOX6 = { size.x / 2 - (size.y / 3), -size.y / 2, size.x / 2 + (size.y / 3), size.y / 2 }; // 敵が武器に攻撃される範囲
        param_.HIT_BOX7 = { size.x / 2 - (size.y / 2), -size.y / 2, size.x / 2 + (size.y / 2), size.y / 2 }; // 敵が武器に攻撃される範囲
        
        param_.ATTACK_BOX = { size.x - (size.y / 6), -size.y / 2, size.x + (size.y / 6), size.y / 2 }; // 敵がプレイヤーに攻撃する範囲

        break;
    }
    default:

        break;
    }
    debug::setString("scale.x:%f", transform->scale().x);
    debug::setString("scale.y:%f", transform->scale().y);
}

// 連打ノーツ
Enemy3Behavior::Enemy3Behavior()
{
    param_.ANIME_IDLE = animeEnemy5_Idle;
    //param_.ANIME_DEAD = animeEnemy4_Dead;

    param_.SIZE = VECTOR2(512, 128);
    param_.SCALE = VECTOR2(1, 1);
    // param_.ATTACK_BOX = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // 敵がプレイヤーに攻撃する範囲
    param_.HIT_BOX = { -128 / 2, -512 / 2, 128 / 2, 512 / 2}; // 敵が武器に攻撃される範囲

    param_.SPEED        = 8.0f;
    param_.SPEED_Y_MAX  = 8.0f;
    param_.SPEED_X_MAX  = 4.0f;
    param_.HP           = 1;    // ヒットポイント
    param_.SCORE        = 50;
    param_.HIT_TIMER    = 50;
    param_.DEAD_TIMER   = 50;
    param_.FLAG_DELETE_COMBO2 = true;
}

// 連打ノーツ
void Enemy3Behavior::enemyParam(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();
    Collider* collider = obj->collider();

    // 出てくる位置によって画像の向きとスピードの設定
    switch (obj->actorComponent()->posType())
    {
    case 0: { // (位置が上の時)
        param_.ANIME_IDLE = animeEnemy4_Idle;
        obj->renderer()->setAnimeData(getParam()->ANIME_IDLE);
        param_.SIZE = VECTOR2(128, 512);
        collider->setSize(param_.SIZE);
        transform->setScale(transform->orgScale());
        const VECTOR2 size = {
            collider->size().x * transform->scale().x,
            collider->size().y * transform->scale().y,
        };
        collider->setSize(size);
        obj->transform()->setSpeedY(param_.SPEED);
        param_.HIT_BOX = { -size.x / 2, -size.y / 2, size.x / 2, size.y / 2 }; // 敵が武器に攻撃される範囲
        param_.ATTACK_BOX = { -size.x / 2, -size.y - (size.x / 6), size.x / 2, -size.y + (size.x / 6) }; // 敵がプレイヤーに攻撃する範囲

        break;
    }
    case 1: { // (位置が左の時)
        param_.ANIME_IDLE = animeEnemy5_Idle;
        obj->renderer()->setAnimeData(getParam()->ANIME_IDLE);
        param_.SIZE = VECTOR2(512, 128);
        collider->setSize(param_.SIZE);
        transform->setScale(transform->orgScale());
        const VECTOR2 size = {
            collider->size().x * transform->scale().x,
            collider->size().y * transform->scale().y,
        };
        collider->setSize(size);
        obj->transform()->setSpeedX(param_.SPEED);
        obj->transform()->setRotation(ToRadian(180));
        param_.HIT_BOX = { -size.x / 2, -size.y / 2, size.x / 2, size.y / 2 }; // 敵が武器に攻撃される範囲
        param_.ATTACK_BOX = { -size.x - (size.y / 6), -size.y / 2, -size.x + (size.y / 6), size.y / 2 }; // 敵がプレイヤーに攻撃する範囲

        break;
    }
    case 2: { // (位置が右の時)
        param_.ANIME_IDLE = animeEnemy5_Idle;
        obj->renderer()->setAnimeData(getParam()->ANIME_IDLE);
        param_.SIZE = VECTOR2(512, 128);
        collider->setSize(param_.SIZE);
        transform->setScale(transform->orgScale());
        const VECTOR2 size = {
            collider->size().x * transform->scale().x,
            collider->size().y * transform->scale().y,
        };
        collider->setSize(size);
        obj->transform()->setRotation(ToRadian(0));
        obj->transform()->setSpeedX(-param_.SPEED);
        param_.HIT_BOX = { -size.x / 2, -size.y / 2, size.x / 2, size.y / 2 }; // 敵が武器に攻撃される範囲
        param_.ATTACK_BOX = { size.x - (size.y / 6), -size.y / 2, size.x + (size.y / 6), size.y / 2 }; // 敵がプレイヤーに攻撃する範囲

        break;
    }
    default:

        break;
    }
}