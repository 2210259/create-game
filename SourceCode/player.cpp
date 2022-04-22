//******************************************************************************
//
//
//      プレイヤークラス
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//******************************************************************************
//
//      プレイヤー移動処理
//
//******************************************************************************

//------< プレイヤーのアニメデータ >----------------------------------------------
namespace
{   // ※このデータは長いので、Visual Studioの機能で閉じられるようにnamespaceを分けている

    //------< プレイヤーのアニメデータ >------------------------------------------
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

//******************************************************************************
//
//      BasePlayerBehavior
//
//******************************************************************************

void BasePlayerBehavior::moveX(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();

    // 左右入力の取り出し
    using namespace input;
    switch (STATE(0) & (PAD_LEFT | PAD_RIGHT))
    {
    case PAD_LEFT:  // 左だけが押されている場合
        transform->addSpeedX(-getParam()->ACCEL_X);
        renderer->setAnimeData(getParam()->ANIME_LEFT);
        obj->actorComponent()->setXFlip(true);
        break;
    case PAD_RIGHT: // 右だけが押されている場合
        transform->addSpeedX(getParam()->ACCEL_X);
        renderer->setAnimeData(getParam()->ANIME_RIGHT);
        obj->actorComponent()->setXFlip(false);
        break;
    default:        // どちらも押されていないか相殺されている場合
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

    debug::setString("player hasSword:%d", obj->actorComponent()->hasSword());
    
    ActorBehavior::moveX(obj);
}

bool BasePlayerBehavior::isAlive(OBJ2D* obj) {
    return true;    // 生存している（仮）
}

//******************************************************************************
//
//      WalkPlayerBehavior
//
//******************************************************************************

WalkPlayerBehavior::WalkPlayerBehavior()
{
    // アニメーション
    param_.ANIME_UP     = animePlayer_Up;
    param_.ANIME_RIGHT  = animePlayer_Right;
    param_.ANIME_DOWN   = animePlayer_Down;
    param_.ANIME_LEFT   = animePlayer_Left;

    param_.SIZE = VECTOR2(48 / 2, 128 - 16);
    param_.SCALE = VECTOR2(1, 1);
    param_.HIT_BOX = { -20, -104, 20, -20 };

    // 速度関連のパラメータ
    param_.ACCEL_X      = 1.0f;
    param_.ACCEL_Y      = 1.0f;
    param_.SPEED_X_MAX  = 8.0f;
    param_.SPEED_Y_MAX  = 16.0f;
    param_.JUMP_POWER_Y = -12.0f;
}

void WalkPlayerBehavior::moveY(OBJ2D* obj)
{
    Transform* transform = obj->transform();

    // 速度に加速度を加える
    transform->addSpeedY(getParam()->ACCEL_Y);

    ActorBehavior::moveY(obj);
}

void WalkPlayerBehavior::jump(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    ActorComponent* actorComp = obj->actorComponent();
    BG* bg = obj->bg();

    // ジャンプチェック
    using namespace input;
    if (TRG(0) & PAD_TRG1)
    {
        if (actorComp->onGround() || bg->isInWater(obj))
        {
            actorComp->setJumpTimer(16);
        }
    }

    // ジャンプ中
    if (actorComp->jumpTimer() > 0)
    {
        if (STATE(0) & PAD_TRG1)
        {   // PAD_TRG1が押されている場合
            transform->setSpeedY(getParam()->JUMP_POWER_Y);
            actorComp->addJumpTimer(-1);
        }
        else
        {   // PAD_TRG1が押されていない場合
            actorComp->setJumpTimer(0);
        }
    }
}

void WalkPlayerBehavior::hashigo(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Collider* collider = obj->collider();
    BG* bg = obj->bg();
    ActorComponent* actorComp = obj->actorComponent();

    if (!bg) assert(!"プレイヤーのbgManager_がnullptr");
    const BG::TR_ATTR attrCenter =    // 体の中心部分の地形の属性
        bg->getTerrainAttr(VECTOR2(transform->position().x, transform->position().y - collider->size().y / 2));
    const BG::TR_ATTR attrBottom =    // 足元の部分の地形の属性
        bg->getTerrainAttr(transform->position());
    const BG::TR_ATTR attrBelow =     // 足元の１ドット下の地形の属性
        bg->getTerrainAttr(VECTOR2(transform->position().x, transform->position().y + 1.0f));

    using namespace input;
    switch (STATE(0) & (PAD_UP | PAD_DOWN | PAD_LEFT | PAD_RIGHT))
    {
    case PAD_UP:
        if (attrBottom == BG::TR_ATTR::HASHIGO ||
            attrCenter == BG::TR_ATTR::HASHIGO)
        {
            obj->setBehavior(&hashigoPlayerBehavior);
        }
        break;

    case PAD_DOWN:
        if (attrBottom == BG::TR_ATTR::HASHIGO ||
            attrCenter == BG::TR_ATTR::HASHIGO)
        {
            obj->setBehavior(&hashigoPlayerBehavior);
        }

        // はしご降りはじめ（プレイヤーがいる高さに「はしご」が無く、下にあるケース）
        if (attrBelow == BG::TR_ATTR::HASHIGO)
        {
            obj->setBehavior(&hashigoPlayerBehavior);
        }
        break;
    }

    // 歩きからはしご（足元の地形属性がはしごで、下が何もないか、はしごの時に落ちる事への対策）
    if (actorComp->onGround() &&                             // 地上にいて
        attrBottom == BG::TR_ATTR::HASHIGO &&   // 足元の地形属性がはしご
        (attrBelow == BG::TR_ATTR::TR_NONE || attrBelow == BG::TR_ATTR::HASHIGO))   // 足元の１ドット下が空白かはしご
    {
        obj->setBehavior(&hashigoPlayerBehavior);
    }
}

void WalkPlayerBehavior::attack(OBJ2D* obj) {
    obj->actorComponent()->subAttackTimer(1);

    using namespace input;
    if (TRG(0) & PAD_TRG3 &&
        obj->actorComponent()->attackTimer() == 0)
    {
        const VECTOR2 pos = obj->transform()->position() + VECTOR2(0, -48);
        OBJ2D* shuriken = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                obj->bg(),
                nullptr,
                nullptr,
                new WeaponComponent),
            &shurikenBehavior, pos);
        shuriken->weaponComponent()->setOwner(obj);
        obj->actorComponent()->setAttackTimer(10);
    }

    if (TRG(0) & PAD_TRG2 &&
        obj->actorComponent()->hasSword() &&
        obj->actorComponent()->attackTimer() == 0)
    {
        const VECTOR2 pos = obj->transform()->position() + VECTOR2(0, -48);
        OBJ2D* sword = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                obj->bg(),
                nullptr,
                nullptr,
                new WeaponComponent),
            &swordBehavior, pos);
        sword->weaponComponent()->setOwner(obj);
        obj->actorComponent()->setAttackTimer(15);
    }
}

HashigoPlayerBehavior::HashigoPlayerBehavior()
{
    // アニメーション
    param_.ANIME_UP     = animePlayer_Up;
    param_.ANIME_RIGHT  = animePlayer_Up;
    param_.ANIME_DOWN   = animePlayer_Up;
    param_.ANIME_LEFT   = animePlayer_Up;

    // サイズ
    param_.SIZE = VECTOR2(48.0f / 2, 128.0f - 16);
    param_.HIT_BOX = { -24, -112, 24, -12 };

    // 速度関連のパラメータ
    param_.ACCEL_X      = 0.4f;
    param_.ACCEL_Y      = 0.4f;
    param_.SPEED_X_MAX  = 4.0f;
    param_.SPEED_Y_MAX  = 4.0f;
}

void HashigoPlayerBehavior::moveY(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();

    // はしご昇降時
    using namespace input;
    switch (STATE(0) & (PAD_UP | PAD_DOWN))
    {
    case PAD_UP:    // 上だけが押されている
        transform->addSpeedY(-getParam()->ACCEL_Y);
        renderer->setAnimeData(getParam()->ANIME_UP);
        break;

    case PAD_DOWN:  // 下だけが押されている
        transform->addSpeedY(getParam()->ACCEL_Y);
        renderer->setAnimeData(getParam()->ANIME_UP);
        break;

    default:        // 何も押されていないか相殺している
        if (transform->speed().y > 0)
        {
            transform->addSpeedY(-getParam()->ACCEL_Y / 2);
            transform->setSpeedY(std::max(transform->speed().y, 0.0f));
        }
        if (transform->speed().y < 0)
        {
            transform->addSpeedY(getParam()->ACCEL_Y / 2);
            transform->setSpeedY(std::min(transform->speed().y, 0.0f));
        }
        break;
    }

    ActorBehavior::moveY(obj);
}

void HashigoPlayerBehavior::hashigo(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Collider* collider = obj->collider();
    BG* bg = obj->bg();

    const BG::TR_ATTR attrCenter =    // 体の中心部分の地形の属性
        bg->getTerrainAttr(VECTOR2(transform->position().x, transform->position().y - collider->size().y / 2));
    const BG::TR_ATTR attrBottom =    // 足元の部分の地形の属性
        bg->getTerrainAttr(transform->position());

    // はしごモード時、通常モードへの移行判定
    if (attrBottom != BG::TR_ATTR::HASHIGO &&       // 足元の地形がはしごでなく
        attrCenter != BG::TR_ATTR::HASHIGO)         // 体の中心の地形がはしごでない
    {
        obj->setBehavior(&walkPlayerBehavior);      // 通常時に戻る
        transform->setSpeedY(0.0f);                 // 自然落下開始の状態になる
    }
}

//--------------------------------------------------------------
//  消去
//--------------------------------------------------------------
void ErasePlayer::erase(OBJ2D* obj)
{
    obj->setBehavior(nullptr);
}
