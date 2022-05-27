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
        { &sprPlayer_Attack_U0, 2 },
        { &sprPlayer_Attack_U1, 2 },
        { &sprPlayer_Attack_U2, 2 },
        { nullptr, -1 },// 終了フラグ
    };
    // 右攻撃
    AnimeData animePlayer_Attack_R[] = {
        { &sprPlayer_Attack_R0, 2 },
        { &sprPlayer_Attack_R1, 2 },
        { &sprPlayer_Attack_R2, 2 },
        { nullptr, -1 },// 終了フラグ
    };
    // 左攻撃
    AnimeData animePlayer_Attack_L[] = {
        { &sprPlayer_Attack_L0, 2 },
        { &sprPlayer_Attack_L1, 2 },
        { &sprPlayer_Attack_L2, 2 },
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

    // HP
    param_.HP = 10;
}

void IdlePlayerBehavior::modechange(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    using namespace input;
    if (obj->actorComponent()->playerHitTimer() > 0) {
        obj->actorComponent()->countPlayerHitTimer();
    }

    Game::instance()->setNotesMaskFlag(false);
    
    // ゲーム
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
    param_.HP = 10;
}

void AttackPlayerBehavior::playerAnimetion(OBJ2D* obj)
{
    Renderer* renderer = obj->renderer();
    Transform* transform = obj->transform();
    using namespace input;

    if (obj->actorComponent()->playerHitTimer() > 0) {
        obj->actorComponent()->countPlayerHitTimer();
    }

    // 攻撃アニメーション
    if (renderer->animeTimer() < 6)
    {
        //左
        if (obj->actorComponent()->direction_ == obj->actorComponent()->LEFT)
        {
            // アニメセット
            renderer->setAnimeData(getParam()->ANIME_ATTACK_L);
        }
        //右
        else if (obj->actorComponent()->direction_ == obj->actorComponent()->RIGHT)
        {
            // アニメセット
            renderer->setAnimeData(getParam()->ANIME_ATTACK_R);
        }
        //上
        else if (obj->actorComponent()->direction_ == obj->actorComponent()->UP)
        {
            //アニメセット
            renderer->setAnimeData(getParam()->ANIME_ATTACK_U);
        }

        //アニメーション遷移タイマー加算
        renderer->countAnimeTime();
    }
    else if (renderer->animeTimer() >= 6 && STATE(0) & PAD_START && Game::instance()->state() < 3)
    {
        renderer->setAnimeTimer(0);
    }
    else if (renderer->animeTimer() >= 6)
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

void ErasePlayer::erase(OBJ2D* obj)
{
    obj->setBehavior(nullptr);
}