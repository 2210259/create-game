#include "all.h"

void ActorBehavior::move(OBJ2D* obj)
{
    obj->renderer()->setAnimeData(nullptr);
    switch (obj->state())
    {
    case 0: {
        //////// 初期設定 ////////
        // アニメの初期設定
        obj->renderer()->setAnimeData(getParam()->ANIME_IDLE);
        if (obj->behavior() != &enemy2Behavior || obj->behavior() != &enemy3Behavior) {
            obj->transform()->setScale(getParam()->SCALE);
            const VECTOR2 size = {
                getParam()->SIZE.x * getParam()->SCALE.x,
                getParam()->SIZE.y * getParam()->SCALE.y,
            };
            if (size.x || size.y) {
                obj->collider()->setSize(size);
            }
        }
        obj->collider()->setJudgeFlag(true);
        // チュートリアル用
        if (Game::instance()->stageNo() == 0) {
            obj->actorComponent()->setHP(35);
            obj->actorComponent()->setMaxHP(35);
        }
        else {
            obj->actorComponent()->setHP(getParam()->HP);
            obj->actorComponent()->setMaxHP(getParam()->HP);
        }
        obj->renderer()->setAnimeTimer(12);
        obj->actorComponent()->setPlayerHitTimer(0);
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
        enemyParam(obj);
        playerAnimetion(obj);
        // GameLib::debug::setString("moveFlag:%d", obj->actorComponent()->moveFlag());
        // GameLib::debug::setString("state:%d", obj->state());
        break;
    }

    obj->collider()->calcHitBox(getParam()->HIT_BOX);
    obj->collider()->calcHitBox2(getParam()->HIT_BOX2);
    obj->collider()->calcHitBox3(getParam()->HIT_BOX3);
    if (getParam()->HIT_BOX4.left) {
        obj->collider()->calcHitBox4(getParam()->HIT_BOX4);
    }
    obj->collider()->calcHitBox5(getParam()->HIT_BOX5);
    obj->collider()->calcHitBox6(getParam()->HIT_BOX6);
    obj->collider()->calcHitBox7(getParam()->HIT_BOX7);
    if (getParam()->ATTACK_BOX.left) {
        obj->collider()->calcAttackBox(getParam()->ATTACK_BOX);
    }
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
    // transform->setSpeedY(clamp(transform->speed().y, -getParam()->SPEED_Y_MAX, getParam()->SPEED_Y_MAX));

    //重力
    // transform->addPositionY(transform->speed().y);

    // 最大速度チェック
    if (transform->speed().y > getParam()->SPEED_Y_MAX)
        transform->setSpeedY(getParam()->SPEED_Y_MAX);
    if (transform->speed().y < -getParam()->SPEED_Y_MAX)
        transform->setSpeedY(-getParam()->SPEED_Y_MAX);

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
    // if (obj->behavior()->getType() != OBJ_TYPE::ENEMY) {
    //     if (transform->position().x < 0 + collider->size().x)
    //     {
    //         transform->setPositionX(collider->size().x);
    //         transform->setSpeedX(0.0f);
    //     }
    //     //右
    //     if (transform->position().x > BG::WIDTH - collider->size().x)
    //     {
    //         transform->setPositionX(BG::WIDTH - collider->size().x);
    //         transform->setSpeedX(0.0f);
    //     }
    //     //下
    //     if (transform->position().y > 980)
    //     {
    //         transform->setPositionY(980);
    //         transform->setSpeedY(0.0f);
    //     }
    // }
}
