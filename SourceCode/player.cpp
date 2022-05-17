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

    // 上攻撃
    AnimeData animePlayer_Attack_U[] = {
        { &sprPlayer_Attack_U0, 4 },
        { &sprPlayer_Attack_U1, 4 },
        { &sprPlayer_Attack_U2, 4 },
        { nullptr, -1 },// 終了フラグ
    };
    // 右攻撃
    AnimeData animePlayer_Attack_R[] = {
        { &sprPlayer_Attack_R0, 4 },
        { &sprPlayer_Attack_R1, 4 },
        { &sprPlayer_Attack_R2, 4 },
        { nullptr, -1 },// 終了フラグ
    };
    // 左攻撃
    AnimeData animePlayer_Attack_L[] = {
        { &sprPlayer_Attack_L0, 4 },
        { &sprPlayer_Attack_L1, 4 },
        { &sprPlayer_Attack_L2, 4 },
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

    // 左右入力の取り出し
    // using namespace input;
    // switch (STATE(0) & (PAD_LEFT | PAD_RIGHT | PAD_UP))
    // {
    // case PAD_LEFT:  // 左だけが押されている場合
    //     obj->actorComponent()->setDirection(obj->actorComponent()->LEFT);
    //     //transform->addSpeedX(-getParam()->ACCEL_X);
    //     renderer->setAnimeData(getParam()->ANIME_LEFT);
    // 
    //     // param_.HIT_BOX = { -290, -470, -240, -420 };
    // 
    //     break;
    // case PAD_RIGHT: // 右だけが押されている場合
    //     obj->actorComponent()->setDirection(obj->actorComponent()->RIGHT);
    //     //transform->addSpeedX(getParam()->ACCEL_X);
    //     // renderer->setAnimeData(getParam()->ANIME_RIGHT);
    //     // param_.ATTACK_BOX = { 420, -700, 470, -650 };
    //     // param_.HIT_BOX = { 360, -560, 410, -510 };
    // 
    //     break;
    // default:        // どちらも押されていないか相殺されている場合
    //     // プレイヤー画像設定左右判定
    //     if (obj->actorComponent()->direction_ == obj->actorComponent()->RIGHT)
    //         renderer->setAnimeData(getParam()->ANIME_IDLE);
    // 
    //     else if (obj->actorComponent()->direction_ == obj->actorComponent()->LEFT)
    //         renderer->setAnimeData(getParam()->ANIME_IDLE);
    // 
    //     //else if (obj->actorComponent()->DOWN)
    //     //    renderer->setAnimeData(getParam()->ANIME_DOWN);
    // 
    //     //else if (obj->actorComponent()->UP)
    //     //    renderer->setAnimeData(getParam()->ANIME_UP);
    // 
    //     // 減速
    //     // if (transform->speed().x > 0)
    //     // {
    //     //     transform->addSpeedX(-getParam()->ACCEL_X / 2);
    //     //     if (transform->speed().x < 0) transform->setSpeedX(0.0f);
    //     // }
    //     // if (transform->speed().x < 0)
    //     // {
    //     //     transform->addSpeedX(getParam()->ACCEL_X / 2);
    //     //     if (transform->speed().x > 0) transform->setSpeedX(0.0f);
    //     // }
    //     // break;
    // }
    // ActorBehavior::moveX(obj);
}

//----------------------------------------//
//        IdlePlayerBehavior  　          //
//----------------------------------------//

IdlePlayerBehavior::IdlePlayerBehavior()
{
    // アニメーション
    param_.ANIME_IDLE = animePlayer_Idle;

    param_.SIZE = VECTOR2(150, 150);
    param_.SCALE = VECTOR2(2, 2);
    const VECTOR2 size = {
        param_.SIZE.x * param_.SCALE.x,
        param_.SIZE.y * param_.SCALE.y
    };
    param_.MARGIN = 100.0f;
    param_.HIT_BOX = { -size.x / 2 + param_.MARGIN, -size.y + param_.MARGIN,
        size.x / 2 - param_.MARGIN, 0 - param_.MARGIN }; // 足元基準

    // param_.ATTACK_BOX   = { -150 / 2, 0, 150 / 2, -150 };
    // float left,top,right,bottom

    // HP
    param_.HP = 1;
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
    if (obj->actorComponent()->playerHitTimer() > 0) {
        obj->actorComponent()->countPlayerHitTimer();
    }
    if (Game::instance()->state() > 2) return;

    // Enterが押されたら
    if (TRG(0) & PAD_START) {
        // モードフラグを変える
        Game::instance()->setPlayerModeFlag(true);
    }

    // Attackモードに変える
    if(Game::instance()->playerModeFlag() == true)
    {
        //もし上を向いていたら
        if(obj->actorComponent()->direction_ == obj->actorComponent()->UP) 
        {
            //当たり判定の位置を設定
            attackPosition = { BG::WINDOW_W / 2, obj->transform()->position().y - (obj->collider()->size().y * 3 / 2) };
        }
        // もし左を向いてたら
        if (obj->actorComponent()->direction_ == obj->actorComponent()->LEFT)
        {
            //当たり判定の位置を設定
            attackPosition = { obj->transform()->position().x - obj->collider()->size().x, obj->transform()->position().y - obj->collider()->size().y / 2 };
        }
        // もし右を向いていたら
        if(obj->actorComponent()->direction_ == obj->actorComponent()->RIGHT)
        {
            //当たり判定の位置を設定
            attackPosition = { obj->transform()->position().x + obj->collider()->size().x, obj->transform()->position().y - obj->collider()->size().y / 2 };
        }
        // 武器をセット
        OBJ2D* weapon = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                obj->bg(),
                nullptr,
                new WeaponComponent,
                nullptr
            ),
            &weaponBehavior, attackPosition, -1, {});
        weapon->weaponComponent()->setOwner(obj);
        
        // モードを変える
        obj->setBehavior(&attackPlayerBehavior);
    }
    debug::setString("IdleMode");
    // debug::setString("HP:%d", Game::instance()->player()->actorComponent()->hp());
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

    // debug::setString("direction:%d", obj->actorComponent()->direction());
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

    param_.SIZE = VECTOR2(150, 150);
    param_.SCALE = VECTOR2(2, 2);
    const VECTOR2 size = {
        param_.SIZE.x * param_.SCALE.x,
        param_.SIZE.y * param_.SCALE.y
    };
    param_.MARGIN = 100.0f;

    param_.HIT_BOX = { -size.x / 2 + param_.MARGIN, -size.y + param_.MARGIN,
        size.x / 2 - param_.MARGIN, 0 - param_.MARGIN }; // 足元基準

    // HP
    param_.HP = 1;
}

// void AttackPlayerBehavior::moveX(OBJ2D* obj)
// {
//     Renderer* renderer = obj->renderer();
//     Transform* transform = obj->transform();
// 
//     // 攻撃アニメーション
//     if (renderer->animeTimer() < 30)
//     {
//         //左
//         if(obj->actorComponent()->direction_ == obj->actorComponent()->LEFT)
//         {
//             // アニメセット
//             renderer->setAnimeData(getParam()->ANIME_ATTACK_L);
//             param_.HIT_BOX   = { -150 / 2, 0, 150 / 2, -150 };
//             // param_.ATTACK_BOX = { -150, -560, 0, -510 };
//             debug::setString("LEFT");
//         }
//         //右
//         else if(obj->actorComponent()->direction_ == obj->actorComponent()->RIGHT)
//         {
//             // アニメセット
//             renderer->setAnimeData(getParam()->ANIME_ATTACK_R);
//             param_.HIT_BOX    = { -150 / 2, 0, 150 / 2, -150 };
//             // param_.ATTACK_BOX = { 360, -560, 410, -510 };
//             debug::setString("RIGHT");
//         }
//         //上
//         else if(obj->actorComponent()->direction_ == obj->actorComponent()->UP)
//         {
//             //アニメセット
//             renderer->setAnimeData(getParam()->ANIME_ATTACK_U);
//             param_.HIT_BOX      = { -150 / 2, 0, 150, -150 };
//             // param_.ATTACK_BOX   = { 360,-560,410,-510 };
//             debug::setString("UP");
//         }
// 
//         //アニメーション遷移タイマー加算
//         renderer->countAnimeTime();
//     }
//     if (renderer->animeTimer() > 30) {
//         Game::instance()->setPlayerModeFlag(true);
//     }
// 
//     debug::setString("AttackMode");
//     debug::setString("SetPlayerModeFlag:%d",Game::instance()->playerModeFlag());
// }

void AttackPlayerBehavior::playerAnimetion(OBJ2D* obj)
{
    Renderer* renderer = obj->renderer();
    Transform* transform = obj->transform();
    using namespace input;

    if (obj->actorComponent()->playerHitTimer() > 0) {
        obj->actorComponent()->countPlayerHitTimer();
    }

    // 攻撃アニメーション
    if (renderer->animeTimer() < 12)
    {
        //左
        if (obj->actorComponent()->direction_ == obj->actorComponent()->LEFT)
        {
            // アニメセット
            renderer->setAnimeData(getParam()->ANIME_ATTACK_L);
            // param_.HIT_BOX = { -param_.SIZE.x / 2 + param_.MARGIN, -param_.SIZE.y + param_.MARGIN,
            //     param_.SIZE.x / 2 - param_.MARGIN, 0 - param_.MARGIN }; // 足元基準
            // debug::setString("LEFT");
        }
        //右
        else if (obj->actorComponent()->direction_ == obj->actorComponent()->RIGHT)
        {
            // アニメセット
            renderer->setAnimeData(getParam()->ANIME_ATTACK_R);

            // param_.HIT_BOX = { -param_.SIZE.x / 2 + param_.MARGIN, -param_.SIZE.y + param_.MARGIN,
            //     param_.SIZE.x / 2 - param_.MARGIN, 0 - param_.MARGIN }; // 足元基準
            // debug::setString("RIGHT");
        }
        //上
        else if (obj->actorComponent()->direction_ == obj->actorComponent()->UP)
        {
            //アニメセット
            renderer->setAnimeData(getParam()->ANIME_ATTACK_U);
            // param_.HIT_BOX = { -param_.SIZE.x / 2 + param_.MARGIN, -param_.SIZE.y + param_.MARGIN,
            //     param_.SIZE.x / 2 - param_.MARGIN, 0 - param_.MARGIN }; // 足元基準
            // debug::setString("UP");
        }

        //アニメーション遷移タイマー加算
        renderer->countAnimeTime();
    }
    else if (renderer->animeTimer() >= 12 && STATE(0) & PAD_START && Game::instance()->state() < 3)
    {
        renderer->setAnimeTimer(0);
    }
    else if (renderer->animeTimer() >= 12)
    {
        Game::instance()->setPlayerModeFlag(false);
    }
    // debug::setString("animeTimer:%d", renderer->animeTimer());
}

void AttackPlayerBehavior::modechange(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();
    using namespace input;

    // プレイヤーのモードを変える
    if (Game::instance()->playerModeFlag() == false)
    {
        //アニメーション遷移タイマーリセット
        renderer->animeTimeReset();

        obj->setBehavior(&idlePlayerBehavior);
    }
    debug::setString("AttackMode");
    // debug::setString("HP:%d",Game::instance()->player()->actorComponent()->hp());
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