//******************************************************************************
//
//
//      player.cpp
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;


//----------------------------------------//
//        プレイヤー移動処理  　          //
//----------------------------------------//


//----------------------------------------//
//        プレイヤーアニメーション        //
//----------------------------------------//

//------< プレイヤーのアニメデータ >----------------------------------------------
namespace
{
    //上方向
    AnimeData animePlayer_Up[] = {
        { &sprPlayer_Up0, 10 },
        { &sprPlayer_Up1, 10 },
        { &sprPlayer_Up2, 10 },
        { &sprPlayer_Up1, 10 },
        { nullptr, -1 },// 終了フラグ
    };
    //右方向
    AnimeData animePlayer_Right[] = {
        { &sprPlayer_Right0, 10 },
        { &sprPlayer_Right1, 10 },
        { &sprPlayer_Right2, 10 },
        { &sprPlayer_Right1, 10 },
        { nullptr, -1 },// 終了フラグ
    };
    //下方向
    AnimeData animePlayer_Down[] = {
        { &sprPlayer_Down0, 10 },
        { &sprPlayer_Down1, 10 },
        { &sprPlayer_Down2, 10 },
        { &sprPlayer_Down1, 10 },
        { nullptr, -1 },// 終了フラグ
    };
    //左方向
    AnimeData animePlayer_Left[] = {
        { &sprPlayer_Left0, 10 },
        { &sprPlayer_Left1, 10 },
        { &sprPlayer_Left2, 10 },
        { &sprPlayer_Left1, 10 },
        { nullptr, -1 },// 終了フラグ
    };
}

//----------------------------------------//
//        BasePlayerBehavior  　          //
//----------------------------------------//

void BasePlayerBehavior::moveX(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();

    if (Game::instance()->state() <= 1) return;

    // 左右入力の取り出し
    using namespace input;
    switch (STATE(0) & (PAD_LEFT | PAD_RIGHT))
    {
    case PAD_LEFT:  // 左だけが押されている場合
        transform->addSpeedX(-getParam()->ACCEL_X);
        renderer->setAnimeData(getParam()->ANIME_LEFT);
        obj->actorComponent()->setFlip(true);


        param_.HIT_BOX = { -290, -470, -240, -420 };

        break;
    case PAD_RIGHT: // 右だけが押されている場合
        transform->addSpeedX(getParam()->ACCEL_X);
        renderer->setAnimeData(getParam()->ANIME_RIGHT);
        obj->actorComponent()->setFlip(false);
        // param_.ATTACK_BOX = { 420, -700, 470, -650 };
        param_.HIT_BOX = { 360, -560, 410, -510 };

        break;
    default:        // どちらも押されていないか相殺されている場合

        // プレイヤー画像設定左右判定
        if (obj->actorComponent()->xFlip())
            renderer->setAnimeData(getParam()->ANIME_LIDLE);
        else
            renderer->setAnimeData(getParam()->ANIME_RIDLE);

        // 減速
        if (transform->speed().x > 0)
        {
            transform->addSpeedX(-getParam()->ACCEL_X / 2);
            if (transform->speed().x < 0) transform->setSpeedX(0.0f);
        }
        if (transform->speed().x < 0)
        {
            transform->addSpeedX(getParam()->ACCEL_X / 2);
            if (transform->speed().x > 0) transform->setSpeedX(0.0f);
        }
        break;
    }

    ActorBehavior::moveX(obj);
}

//----------------------------------------//
//        IdlePlayerBehavior  　          //
//----------------------------------------//

IdlePlayerBehavior::IdlePlayerBehavior()
{
    // アニメーション
    param_.ANIME_RIGHT = animePlayer_Right;
    param_.ANIME_LEFT = animePlayer_Left;
    // param_.ANIME_RIDLE = animePlayer_RIdle;
    // param_.ANIME_LIDLE = animePlayer_LIdle;

    param_.SIZE = VECTOR2(300 / 2, 510 - 10);
    param_.SCALE = VECTOR2(1, 1);
    // param_.HIT_BOX      = { 420, -700, 470, -650 };
    // param_.ATTACK_BOX   = { 420, -700, 470, -650 };
    // param_.HIT_BOX = { -150, -510, 150, 0 };

    // 速度関連のパラメータ
    param_.ACCEL_X = 1.0f;
    param_.ACCEL_Y = 1.0f;
    param_.SPEED_X_MAX = 8.0f;
    param_.SPEED_Y_MAX = 16.0f;
}

void IdlePlayerBehavior::moveY(OBJ2D* obj)
{
    Transform* transform = obj->transform();

    // 速度に加速度を加える
    transform->addSpeedY(getParam()->ACCEL_Y);

    ActorBehavior::moveY(obj);
}

void IdlePlayerBehavior::modechange(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    using namespace input;

    if (Game::instance()->state() <= 1) return;

    //右クリックが押されたら
    if (TRG(0) & PAD_TRG2)
    {
        //スピードを0に
        transform->setSpeedX(0.0f);

        OBJ2D* weapon = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                obj->bg(),
                nullptr,
                new WeaponComponent
            ),
            &weaponbehavior, VECTOR2(960, 540));
        weapon->weaponComponent()->setOwner(obj);
        obj->setBehavior(&attackPlayerBehavior);
    }
    //debug::setString("PPP%f", pos);
}

//----------------------------------------//
//        AttackPlayerBehavior  　       //
//----------------------------------------//
AttackPlayerBehavior::AttackPlayerBehavior()
{
    // アニメーション
    // param_.ANIME_RIGHT = animePlayer_RFthrow;
    // param_.ANIME_LEFT  = animePlayer_LFthrow;

    // param_.ANIME_LHIT = animePlayer_LFroll;
    // param_.ANIME_RHIT = animePlayer_RFroll;

    param_.SIZE = VECTOR2(300 / 2, 510 - 10);
    param_.SCALE = VECTOR2(1, 1);
    // param_.ATTACK_BOX   = { 420, -700, 470, -650 };
    // param_.HIT_BOX      = { 420, -700, 470, -650 };

    // 速度関連のパラメータ
    param_.ACCEL_X = 0.0f;
    param_.ACCEL_Y = 1.0f;
    param_.SPEED_X_MAX = 0.0f;
    param_.SPEED_Y_MAX = 16.0f;
}

void AttackPlayerBehavior::moveX(OBJ2D* obj)
{
    Renderer* renderer = obj->renderer();
    Transform* transform = obj->transform();

    // 攻撃アニメーション
    if (renderer->animeTimer() < 40)
    {
        //左
        if (obj->actorComponent()->xFlip())
        {
            // アニメセット
            renderer->setAnimeData(getParam()->ANIME_LEFT);
            param_.ATTACK_BOX = { -410, -560, -360, -510 };
            param_.HIT_BOX = { -410, -560, -360, -510 };
        }
        //右
        else
        {
            // アニメセット
            renderer->setAnimeData(getParam()->ANIME_RIGHT);
            param_.ATTACK_BOX = { 360, -560, 410, -510 };
            param_.HIT_BOX = { 360, -560, 410, -510 };
        }

        //アニメーション遷移タイマー加算
        renderer->countaniTime();
    }
}

void AttackPlayerBehavior::modechange(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();
    using namespace input;

    // プレイヤーのモードを変える
    if (Game::instance()->playerModeFlag() == true)
    {
        //アニメーション遷移タイマーリセット
        renderer->aniTimeReset();

        obj->setBehavior(&idlePlayerBehavior);
    }
}

// 多分使わない
// プレイヤー(→)敵に当たった時の処理
// void AttackPlayerBehavior::hit(OBJ2D* src, OBJ2D* dst) {
//     if (Game::instance()->esaFlag() == false && dst->enemyState() == 3)
//     {
//         dst->setEnemyState(4);
//         Game::instance()->setHit(true);
//     }
// }

void ErasePlayer::erase(OBJ2D* obj)
{
    obj->setBehavior(nullptr);
}