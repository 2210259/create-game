#include "all.h"
using namespace GameLib;

void ActorBehavior::move(OBJ2D* obj)
{
    obj->renderer()->setAnimeData(nullptr);

    switch (obj->state())
    {
    case 0: {
        //////// 初期設定 ////////
        // アニメの初期設定
        obj->renderer()->setAnimeData(getParam()->ANIME_RIGHT);

        obj->transform()->setScale(getParam()->SCALE);
        const VECTOR2 size = {
            getParam()->SIZE.x * getParam()->SCALE.x,
            getParam()->SIZE.y * getParam()->SCALE.y,
        };
        obj->collider()->setSize( size );
        obj->collider()->setJudgeFlag(true);
        obj->collider()->setIsDrawHitRect(true);
        obj->actorComponent()->setHp(getParam()->HP);
        obj->nextState();//state_++
        break;
    }

    case 1:
        //////// 通常時 ////////
        if (isAlive(obj) == false) break;
        moveY(obj);
        moveX(obj);
        jump(obj);
        hashigo(obj);
        areaCheck(obj);
        turn(obj);
        attack(obj);
        break;
    }

    obj->collider()->calcHitBox(getParam()->HIT_BOX);

    // アニメーション更新
    if (obj->renderer()->animeData())
        obj->renderer()->animeUpdate();
}

void ActorBehavior::moveY(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    BG* bg = obj->bg();
    ActorComponent* actorComp = obj->actorComponent();
    Collider* collider = obj->collider();

    // Y方向の抗力の計算
    transform->addSpeedY(bg->calcResistance(obj, transform->speed().y));

    // 最大速度制限
    transform->setSpeedY(clamp(transform->speed().y, -getParam()->SPEED_Y_MAX, getParam()->SPEED_Y_MAX));

    // 位置更新
    float oldY = transform->position().y;           // 移動前の位置を保持
    transform->addPositionY(transform->speed().y);
    float deltaY = transform->position().y - oldY;  // 移動後の位置から移動前の位置を引く

    actorComp->setOnGround(false);

    // 下方向のあたり判定
    if (deltaY > 0)
    {
        if (bg->isFloor(transform->position().x, transform->position().y, collider->size().x))
        {
            // 床にあたっていたら
            bg->mapHoseiDown(obj);    //  下方向の補正処理
            actorComp->setOnGround(true);   // 地面フラグ
        }
    }

    // 上方向のあたり判定
    if (deltaY < 0)
    {
        if (bg->isCeiling(transform->position().x, transform->position().y - collider->size().y, collider->size().x))
        {
            // 天井にあたっていたら
            bg->mapHoseiUp(obj);
            actorComp->setJumpTimer(0);
        }
    }
}

void ActorBehavior::moveX(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    BG* bg = obj->bg();
    Collider* collider = obj->collider();

    // X方向の抗力の計算
    transform->addSpeedX(bg->calcResistance(obj, transform->speed().x));

    // 最大速度チェック
    if (transform->speed().x > getParam()->SPEED_X_MAX)
        transform->setSpeedX(getParam()->SPEED_X_MAX);
    if (transform->speed().x < -getParam()->SPEED_X_MAX)
        transform->setSpeedX(-getParam()->SPEED_X_MAX);

    // X方向移動
    float oldX = transform->position().x;
    transform->addPositionX(transform->speed().x);
    float deltaX = transform->position().x - oldX;

    //bool kabeFlag = false;  // 壁フラグをfalseにしておく（プレイヤーでは使用しない）

    // 右方向あたり判定
    if (deltaX > 0)
    {
        if (bg->isWall(transform->position().x + collider->size().x,
            transform->position().y, collider->size().y))
        {
            bg->mapHoseiRight(obj);     // 右方向の補正処理
            obj->actorComponent()->setKabeFlag(true);
            //kabeFlag = true;                    // 壁フラグをtrueにしておく
        }
    }

    // 左方向あたり判定
    if (deltaX < 0)
    {
        if (bg->isWall(transform->position().x - collider->size().x,
            transform->position().y, collider->size().y))
        {
            bg->mapHoseiLeft(obj);
            obj->actorComponent()->setKabeFlag(true);
            //kabeFlag = true;
        }
    }
}

void ActorBehavior::areaCheck(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Collider* collider = obj->collider();

    const float LIMIT = 512.0f; // 世界の下端からこの数値分落ちたら消す
    if (transform->position().y > BG::HEIGHT + LIMIT)
    {
        obj->remove();
        return;
    }

    if (transform->position().x < 0 + collider->size().x)
    {
        transform->setPositionX( collider->size().x );
        transform->setSpeedX( 0.0f );

        obj->actorComponent()->setKabeFlag(true);
    }
    if (transform->position().x > BG::WIDTH - collider->size().x)
    {
        transform->setPositionX(BG::WIDTH - collider->size().x);
        transform->setSpeedX( 0.0f );

        obj->actorComponent()->setKabeFlag(true);
    }
}
