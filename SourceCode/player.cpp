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
    // 待機（正面）
    AnimeData animePlayer_Idle[] = {
        { &sprPlayer_Idle0, 10 },
        { &sprPlayer_Idle1, 10 },
        { nullptr, -1}, // 終了フラグ
    };

    // 上方向
    AnimeData animePlayer_Attack_U[] = {
        { &sprPlayer_Attack_U0, 10 },
        { &sprPlayer_Attack_U1, 10 },
        { &sprPlayer_Attack_U2, 10 },
        { nullptr, -1 },// 終了フラグ
    };
    // 右方向
    AnimeData animePlayer_Attack_R[] = {
        { &sprPlayer_Attack_R0, 10 },
        { &sprPlayer_Attack_R1, 10 },
        { &sprPlayer_Attack_R2, 10 },
        { nullptr, -1 },// 終了フラグ
    };
    // 左方向
    AnimeData animePlayer_Attack_L[] = {
        { &sprPlayer_Attack_L0, 10 },
        { &sprPlayer_Attack_L1, 10 },
        { &sprPlayer_Attack_L2, 10 },
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
        //transform->addSpeedX(-getParam()->ACCEL_X);
        renderer->setAnimeData(getParam()->ANIME_LEFT);
        obj->actorComponent()->setDirection(obj->actorComponent()->LEFT);

        param_.HIT_BOX = { -290, -470, -240, -420 };

        break;
    case PAD_RIGHT: // 右だけが押されている場合
        //transform->addSpeedX(getParam()->ACCEL_X);
        renderer->setAnimeData(getParam()->ANIME_RIGHT);
        obj->actorComponent()->setDirection(obj->actorComponent()->RIGHT);
        // param_.ATTACK_BOX = { 420, -700, 470, -650 };
        param_.HIT_BOX = { 360, -560, 410, -510 };

        break;
    default:        // どちらも押されていないか相殺されている場合
        // プレイヤー画像設定左右判定
        if (obj->actorComponent()->direction_ == obj->actorComponent()->RIGHT)
            renderer->setAnimeData(getParam()->ANIME_IDLE);

        else if (obj->actorComponent()->direction_ == obj->actorComponent()->LEFT)
            renderer->setAnimeData(getParam()->ANIME_IDLE);

        //else if (obj->actorComponent()->DOWN)
        //    renderer->setAnimeData(getParam()->ANIME_DOWN);

        //else if (obj->actorComponent()->UP)
        //    renderer->setAnimeData(getParam()->ANIME_UP);

        // 減速
        // if (transform->speed().x > 0)
        // {
        //     transform->addSpeedX(-getParam()->ACCEL_X / 2);
        //     if (transform->speed().x < 0) transform->setSpeedX(0.0f);
        // }
        // if (transform->speed().x < 0)
        // {
        //     transform->addSpeedX(getParam()->ACCEL_X / 2);
        //     if (transform->speed().x > 0) transform->setSpeedX(0.0f);
        // }
        // break;
    }
    debug::setString("speed:%f", obj->transform()->speed().x);
    ActorBehavior::moveX(obj);
}

//----------------------------------------//
//        IdlePlayerBehavior  　          //
//----------------------------------------//

IdlePlayerBehavior::IdlePlayerBehavior()
{
    // アニメーション
    param_.ANIME_IDLE = animePlayer_Idle;
    // param_.ANIME_LEFT = animePlayer_Left;
    //param_.ANIME_LIDLE = animePlayer_LIdle;
    //param_.ANIME_RIDLE = animePlayer_RIdle;

    param_.SIZE = VECTOR2(300 / 2, 510 - 10);
    param_.SCALE = VECTOR2(1, 1);
    param_.HIT_BOX      = { -150 / 2, 0, 150 / 2, -150 };
    // param_.ATTACK_BOX   = { -150 / 2, 0, 150 / 2, -150 };
    // param_.HIT_BOX = { -150, -510, 150, 0 };
    // float left,top,right,bottom

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
    // transform->addSpeedY(getParam()->ACCEL_Y);

    ActorBehavior::moveY(obj);
}

// void IdlePlayerBehavior::moveX(OBJ2D* obj)
// {
//     Transform* transform = obj->transform();
// 
//     // 速度に加速度を加える
//     transform->addSpeedX(getParam()->ACCEL_X);
//     obj->renderer()->setAnimeData(getParam()->ANIME_RIGHT);
// 
//     debug::setString("aaaaaaaaaaaaaaaaaaaaa");
//     ActorBehavior::moveX(obj);
// }

void IdlePlayerBehavior::modechange(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    using namespace input;

    debug::setString("IdleMode");
    // if (Game::instance()->state() <= 1) return;

    // Enterが押されたら
    if (TRG(0) & PAD_START)
    {
        OBJ2D* weapon = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                obj->bg(),
                nullptr,
                new WeaponComponent
            ),
            &weaponbehavior, VECTOR2(10, 10));
        weapon->weaponComponent()->setOwner(obj);
        obj->setBehavior(&attackPlayerBehavior);
    }
}

void IdlePlayerBehavior::playerAnimetion(OBJ2D* obj) 
{
    Renderer* renderer = obj->renderer();

    renderer->setAnimeData(getParam()->ANIME_IDLE);

    using namespace input;
    switch (STATE(0) & (PAD_LEFT | PAD_RIGHT | PAD_UP | PAD_DOWN))
    {
    case PAD_LEFT:  // 左だけが押されている場合
        obj->actorComponent()->setDirection(obj->actorComponent()->LEFT);
        break;
    case PAD_RIGHT: // 右だけが押されている場合
        obj->actorComponent()->setDirection(obj->actorComponent()->RIGHT);
        break;
    case PAD_DOWN:  // 下だけが押されている場合
        obj->actorComponent()->setDirection(obj->actorComponent()->DOWN);
        break;
    case PAD_UP:    // 上だけが押されている場合
        obj->actorComponent()->setDirection(obj->actorComponent()->UP);
        break;
    }
    // if(obj->actorComponent()->direction() == obj->actorComponent()->UP)
    // if (obj->actorComponent()->direction() == obj->actorComponent()->DOWN)
    //     renderer->setAnimeData(getParam()->ANIME_DOWN);
    // 
    // if (obj->actorComponent()->direction() == obj->actorComponent()->LEFT)
    //     renderer->setAnimeData(getParam()->ANIME_LEFT);
    // 
    // if (obj->actorComponent()->direction() == obj->actorComponent()->RIGHT)
    //     renderer->setAnimeData(getParam()->ANIME_RIGHT);

    debug::setString("direction:%d", obj->actorComponent()->direction());
}

//----------------------------------------//
//        AttackPlayerBehavior  　       //
//----------------------------------------//
AttackPlayerBehavior::AttackPlayerBehavior()
{
    // アニメーション
    param_.ANIME_ATTACK_R = animePlayer_Attack_R;
    param_.ANIME_ATTACK_L = animePlayer_Attack_L;
    param_.ANIME_ATTACK_U = animePlayer_Attack_U;

    param_.SIZE         = VECTOR2(300 / 2, 510 - 10);
    param_.SCALE        = VECTOR2(1, 1);
    param_.ATTACK_BOX   = { 0, 0, -300, -300 };
    param_.HIT_BOX      = { 0, 0, -300, -300 };

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
        if(obj->actorComponent()->direction_ == obj->actorComponent()->LEFT)
        {
            // アニメセット
            renderer->setAnimeData(getParam()->ANIME_ATTACK_L);
            param_.HIT_BOX   = { -150 / 2, 0, 150 / 2, -150 };
            // param_.ATTACK_BOX = { -150, -560, 0, -510 };
        }
        //右
        else if(obj->actorComponent()->direction_ == obj->actorComponent()->RIGHT)
        {
            // アニメセット
            renderer->setAnimeData(getParam()->ANIME_ATTACK_R);
            param_.HIT_BOX    = { -150 / 2, 0, 150 / 2, -150 };
            // param_.ATTACK_BOX = { 360, -560, 410, -510 };
        }
        //上
        else if(obj->actorComponent()->direction_ == obj->actorComponent()->UP)
        {
            //アニメセット
            renderer->setAnimeData(getParam()->ANIME_ATTACK_U);
            param_.HIT_BOX      = { -150 / 2, 0, 150, -150 };
            // param_.ATTACK_BOX   = { 360,-560,410,-510 };;
        }

        //アニメーション遷移タイマー加算
        renderer->countaniTime();
    }
    if (renderer->animeTimer() > 40) {
        Game::instance()->setPlayerModeFlag(true);
    }

    debug::setString("AttackMode");
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