#include "all.h"

//using
using namespace GameLib;
using namespace input;

void BaseWeaponBehavior::move(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();
    Collider* collider = obj->collider();
    WeaponComponent* weaponComponent = obj->weaponComponent();
    BG* bg = obj->bg();

    switch (obj->state())
    {
    case 0:
        //////// 初期設定 ////////
        transform->setScale(getParam()->SCALE);
        renderer->setData(getParam()->SPR_WEAPON);
        obj->setEraser(getParam()->ERASER);
        collider->setJudgeFlag(true);      // あたり判定を行う

        collider->calcAttackBox(getParam()->ATTACK_BOX);
        // collider->calcHitBox(getParam()->HIT_BOX);

        // 左右の向き、速度を設定（プレイヤーにもxFlip_の設定が必要）
        // weaponComponent->copyOwnerXFlip();   // 武器の持ち主のxFlip_を武器に設定する

        obj->nextState();//state++
        /*fallthrough*/

    case 1:
        //////// 通常時 ////////
        collider->calcAttackBox(getParam()->ATTACK_BOX);
        // collider->calcHitBox(getParam()->HIT_BOX);
        update(obj);

        break;
    }
}

void BaseWeaponBehavior::update(OBJ2D* obj)
{
    Renderer* renderer = obj->renderer();
    Transform* transform = obj->transform();

    if (Game::instance()->playerModeFlag() == false) {
        obj->remove();
    }

    // renderer->countAnimeTime();

    // if (Game::instance()->state() <= 1) return;


    // debug::setString("speed%f", transform->speed().x);
    // debug::setString("speedY%f", transform->speed().y);
}

//----------------------------------------//
//         　　コンストラクタ 　          //
//----------------------------------------//
WeaponBehavior::WeaponBehavior()
{
    // param_.SPR_WEAPON = &sprWeapon;
    param_.ERASER = &weaponEraser;

    //TODO 武器パラメータ設定
    param_.SCALE = { 1, 1 };
    param_.ATTACK_BOX = { -25, -25, 25, 25 };
    param_.HIT_BOX    = { -25, -25, 25, 25 };
}

// void WeaponBehavior::calcAttackBox(OBJ2D* obj)
// {
//     obj->collider()->calcAttackBox(getParam()->ATTACK_BOX);
// }
// 
// void WeaponBehavior::calcHitBox(OBJ2D* obj)
// {
//     obj->collider()->calcHitBox(getParam()->HIT_BOX);
// }

// 武器(→)敵に当たった時の処理(Perfect)
void WeaponBehavior::hit(OBJ2D* src, OBJ2D* dst)
{
    // コンボを追加
    Game::instance()->addCombo();

    // 敵にダメージを与える
    dst->actorComponent()->damage();
}

// 武器(→)敵に当たった時の処理(Great)
void WeaponBehavior::hit2(OBJ2D* src, OBJ2D* dst)
{
    // コンボを追加
    Game::instance()->addCombo();
    
    // 敵にダメージを与える
    dst->actorComponent()->damage();
}

// 武器(→)敵に当たった時の処理(Good)
void WeaponBehavior::hit3(OBJ2D* src, OBJ2D* dst)
{
    // コンボを追加
    Game::instance()->addCombo();
    
    // 敵にダメージを与える
    dst->actorComponent()->damage();
}
//----------------------------------------//
//         　　　　　消去 　　　          //
//----------------------------------------//
void WeaponEraser::erase(OBJ2D* obj)
{
    // obj->remove();
}
