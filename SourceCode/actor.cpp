#include "all.h"

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
        obj->collider()->setSize(size);
        obj->collider()->setJudgeFlag(true);

        obj->nextState();//state_++
        break;
    }
    case 1:
        //////// 通常時 ////////
        moveY(obj);
        moveX(obj);
        areaCheck(obj);
        modechange(obj);
        moveEnemy(obj);
        enemyAnime(obj);
        playerAnimetion(obj);
        // GameLib::debug::setString("moveFlag:%d", obj->actorComponent()->moveFlag());
        // GameLib::debug::setString("state:%d", obj->state());
        break;
    }

    obj->collider()->calcHitBox(getParam()->HIT_BOX);
    obj->collider()->calcAttackBox(getParam()->ATTACK_BOX);
    // obj->collider()->calcAttackBox2(getParam()->ATTACK_BOX2);

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

    // 最大速度制限
    transform->setSpeedY(clamp(transform->speed().y, -getParam()->SPEED_Y_MAX, getParam()->SPEED_Y_MAX));

    //重力
    transform->addPositionY(transform->speed().y);
}

void ActorBehavior::moveX(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    BG* bg = obj->bg();
    Collider* collider = obj->collider();

    // 最大速度チェック
    if (transform->speed().x > getParam()->SPEED_X_MAX)
        transform->setSpeedX(getParam()->SPEED_X_MAX);
    if (transform->speed().x < -getParam()->SPEED_X_MAX)
        transform->setSpeedX(-getParam()->SPEED_X_MAX);

    transform->addPositionX(transform->speed().x);
}

void ActorBehavior::areaCheck(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Collider* collider = obj->collider();

    //左
    if (obj->behavior()->getType() != OBJ_TYPE::ENEMY) {
        if (transform->position().x < 0 + collider->size().x)
        {
            transform->setPositionX(collider->size().x);
            transform->setSpeedX(0.0f);
        }
        //右
        if (transform->position().x > BG::WIDTH - collider->size().x)
        {
            transform->setPositionX(BG::WIDTH - collider->size().x);
            transform->setSpeedX(0.0f);
        }
        //下
        if (transform->position().y > 980)
        {
            transform->setPositionY(980);
            transform->setSpeedY(0.0f);
        }
    }
}
