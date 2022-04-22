//******************************************************************************
//
//
//      OBJ2Dクラス
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include "all.h"

using namespace GameLib;

//--------------------------------------------------------------
//  コンストラクタ
//--------------------------------------------------------------
OBJ2D::OBJ2D(Renderer* renderer,
    Collider* collider,
    BG* bg,
    ActorComponent* actorComponent,
    ItemComponent* itemComponent, 
    WeaponComponent* weaponComponent)
    :state_(0)
    , timer_(0)
    , behavior_(nullptr)
    , eraser_(nullptr)
    , transform_(new Transform)
    , renderer_(renderer)
    , collider_(collider)
    , bg_(bg)
    , actorComponent_(actorComponent)
    , itemComponent_(itemComponent)
    , weaponComponent_(weaponComponent)
{
    if (transform_)         transform_->setParent(this);
    if (renderer_)          renderer_->setParent(this);
    if (collider_)          collider_->setParent(this);
    if (actorComponent_)    actorComponent_->setParent(this);
    if (itemComponent_)     itemComponent_->setParent(this);
    if (weaponComponent_)   weaponComponent_->setParent(this);
}

//--------------------------------------------------------------
//  デストラクタ
//--------------------------------------------------------------
OBJ2D::~OBJ2D()
{
    safe_delete(transform_);
    safe_delete(weaponComponent_);
    safe_delete(itemComponent_);
    safe_delete(actorComponent_);
    safe_delete(collider_);
    safe_delete(renderer_);
}

//--------------------------------------------------------------
//  移動
//--------------------------------------------------------------
void OBJ2D::move()
{
    if (behavior_) behavior_->move(this);
    if (eraser_) eraser_->erase(this);

    timer_++;
}

//----------------------------------------------------------------------
//  Renderer
//----------------------------------------------------------------------
void Renderer::draw(const VECTOR2& scrollPos)
{
    Transform* transform = parent()->transform();
    if (data_)
    {
        data_->draw(transform->position() - scrollPos,
            transform->scale(), transform->rotation(), color_);  // dataのdrawメソッドでスプライトを描画する
    }
}

//--------------------------------------------------------------
//  アニメーション更新
//--------------------------------------------------------------
//  戻り値：true  アニメが先頭に戻る瞬間
//        :false それ以外
//--------------------------------------------------------------
bool Renderer::animeUpdate()
{
    if (animeData_ == nullptr)
    {
        assert(!"animeUpdate関数でAnimeDataがnullptr");
        return false;
    }

    if (anime_.pPrev != animeData_)         // アニメデータが切り替わったとき
    {
        anime_.pPrev = animeData_;
        anime_.patNum = 0;	                // 先頭から再生
        anime_.frame = 0;
    }

    animeData_ += anime_.patNum;
    data_ = animeData_->data;               // 現在のパターン番号に該当する画像を設定

    anime_.frame++;
    if (anime_.frame >= animeData_->frame)  // 設定フレーム数表示したら
    {
        anime_.frame = 0;
        anime_.patNum++;                    // 次のパターンへ
        if ((animeData_ + 1)->frame < 0)    // 終了コードのとき
        {
            anime_.patNum = 0;              // 先頭へ戻る
            return true;
        }
    }

    return false;
}

//----------------------------------------------------------------------
//  Collider
//----------------------------------------------------------------------
void Collider::draw(const VECTOR2& scrollPos)
{
    VECTOR2 size, pos;
    VECTOR4 color;

    // 攻撃Box
    size = {
        attackBox_.right - attackBox_.left,
        attackBox_.bottom - attackBox_.top
    };
    if (size.x * size.y != 0.0f)
    {
        pos = VECTOR2(attackBox_.left, attackBox_.top) - scrollPos;
        color = { 1, 0, 0, 0.5f };
        primitive::rect(pos, size, { 0, 0 }, 0, color);
    }

    // 食らいBox
    size = {
        hitBox_.right - hitBox_.left,
        hitBox_.bottom - hitBox_.top
    };
    if (size.x * size.y != 0.0f)
    {
        pos = VECTOR2(hitBox_.left, hitBox_.top) - scrollPos;
        color = { 0, 0, 1, 0.5f };
        primitive::rect(pos, size, { 0, 0 }, 0, color);
    }
}

void Collider::calcHitBox(const GameLib::fRECT& rc)
{
    Transform* t = parent()->transform();
    hitBox_ = {
        t->position().x + rc.left,  t->position().y + rc.top,
        t->position().x + rc.right, t->position().y + rc.bottom
    };
}

void Collider::calcAttackBox(const GameLib::fRECT& rc)
{
    Transform* t = parent()->transform();
    attackBox_ = {
        t->position().x + rc.left,  t->position().y + rc.top,
        t->position().x + rc.right, t->position().y + rc.bottom
    };
}

bool Collider::hitCheck(Collider* coll)
{
    if (attackBox_.right < coll->hitBox_.left) return false;
    if (attackBox_.left > coll->hitBox_.right) return false;
    if (attackBox_.bottom < coll->hitBox_.top) return false;
    if (attackBox_.top > coll->hitBox_.bottom) return false;

    return true;
}

bool Collider::hitCheck(OBJ2D* obj)
{
    return hitCheck(obj->collider());
}

//----------------------------------------------------------------------
//  WeaponComponent
//----------------------------------------------------------------------
void WeaponComponent::copyOwnerXFlip()
{
    // 武器の持ち主のxFlip_をコピーしてくる。
    if (owner_ && owner_->actorComponent())
        xFlip_ = owner_->actorComponent()->xFlip();
}

//******************************************************************************
//
//
//      OBJ2DManagerクラス
//
//
//******************************************************************************

//--------------------------------------------------------------
//  初期化
//--------------------------------------------------------------
void OBJ2DManager::init()
{
    //リストのOBJ2Dを全てクリアする
    objList_.clear();
}

//--------------------------------------------------------------
//  リストへ追加
//--------------------------------------------------------------
OBJ2D* OBJ2DManager::add(OBJ2D* obj, Behavior* behavior, const VECTOR2& pos)
{
    obj->setBehavior(behavior);
    obj->transform()->setPosition(pos);
    objList_.emplace_back(obj);
    return obj;
}

//--------------------------------------------------------------
//  更新
//--------------------------------------------------------------
void OBJ2DManager::update()
{
    // 移動
    for (auto& obj : objList_)   // objListの全ての要素をループし、itという名前で各要素にアクセス
    {
        obj->move();              // itのmoveメソッドを呼ぶ
    }

    // 空ノードの削除
    auto iter = objList_.begin();
    while (iter != objList_.end())
    {
        if ((*iter)->behavior())
        {
            iter++;
        }
        else
        {
            // プレイヤーが落ちて消えた場合、Gameクラスのplayerにnullptrを代入する
            if (Game::instance()->player() == *iter)
                Game::instance()->setPlayer(nullptr);

            safe_delete(*iter);
            iter = objList_.erase(iter);
        }
    }
}

//--------------------------------------------------------------
//  描画
//--------------------------------------------------------------
void OBJ2DManager::draw(const VECTOR2& scrollPos)
{
    const float LIMIT = 256.0f; // これ以上スクリーンから出ているものはとばす

    for (auto& obj : objList_)
    {
        const VECTOR2 pos = obj->transform()->position() - scrollPos;
        if (pos.x < -LIMIT || pos.x > window::getWidth() + LIMIT ||
            pos.y < -LIMIT || pos.y > window::getHeight() + LIMIT) continue;

        obj->renderer()->draw(scrollPos);
        obj->collider()->draw(scrollPos);
    }
}

//--------------------------------------------------------------
//  デストラクタ
//--------------------------------------------------------------
OBJ2DManager::~OBJ2DManager()
{
    for (auto& obj : objList_)
    {
        safe_delete(obj);
    }

    //リストのOBJ2Dを全てクリアする
    objList_.clear();
}
