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
    WeaponComponent* weaponComponent)
    : renderer_(renderer)
    , collider_(collider)
    , bg_(bg)
    , actorComponent_(actorComponent)
    , weaponComponent_(weaponComponent)
{
    transform_ = new Transform;
    if (transform_)         transform_->setParent(this);
    if (renderer_)          renderer_->setParent(this);
    if (collider_)          collider_->setParent(this);
    if (actorComponent_)    actorComponent_->setParent(this);
    if (weaponComponent_)   weaponComponent_->setParent(this);
}

//--------------------------------------------------------------
//  デストラクタ
//--------------------------------------------------------------
OBJ2D::~OBJ2D()
{
    safe_delete(transform_);
    safe_delete(renderer_);
    safe_delete(collider_);
    safe_delete(actorComponent_);
    safe_delete(weaponComponent_);
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

//--------------------------------------------------------------
//  描画
//--------------------------------------------------------------
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

void Collider::draw(const VECTOR2& scrollPos) {
    // 食らいBOX
    {
        const VECTOR2 pos{ hitBox_.left - scrollPos.x, hitBox_.top - scrollPos.y };
        const VECTOR2 size{ hitBox_.right - hitBox_.left, hitBox_.bottom - hitBox_.top };
        primitive::rect(pos, size, { 0, 0 }, 0, { 0, 0, 1, 0.5f });
    }
    // primitive::rect(
    //     VECTOR2(hitBox_.left, hitBox_.top) - scrollPos,
    //     { hitBox_.right - hitBox_.left, hitBox_.bottom - hitBox_.top },
    //     { 0, 0 }, 0.0f,
    //     { 0.0f, 0.0f, 1.0f, 0.5f }
    // );

    // 攻撃BOX
    {
        const VECTOR2 pos{ attackBox_.left - scrollPos.x, attackBox_.top - scrollPos.y };
        const VECTOR2 size{ attackBox_.right - attackBox_.left, attackBox_.bottom - attackBox_.top };
        primitive::rect(pos, size, { 0, 0 }, 0, { 1, 0, 0, 0.5f });
    }
    // primitive::rect(
    //     VECTOR2(attackBox_.left, attackBox_.top) - scrollPos,
    //     { attackBox_.right - attackBox_.left, attackBox_.bottom - attackBox_.top },
    //     { 0, 0}, 0.0f,
    //     { 1.0f, 0.0f, 0.0f, 0.5f }
    // );
};

// Componentの親（OBJ2D）のTransform_のposition_の座標に、引数のrcの値を足したもの
// をhitBox_及び、attackBox_に設定する。

void Collider::calcHitBox(const GameLib::fRECT& rc) {
    const VECTOR2* pos = &parent()->transform()->position();

    hitBox_ = {
        pos->x + rc.left,  pos->y + rc.top,
        pos->x + rc.right, pos->y + rc.bottom,
    };
}
void Collider::calcAttackBox(const GameLib::fRECT& rc) {
    const VECTOR2* pos = &parent()->transform()->position();

    attackBox_ = {
        pos->x + rc.left,   pos->y + rc.top,
        pos->x + rc.right,  pos->y + rc.bottom,
    };
}

bool Collider::hitcheck(Collider* coll) {
    // this->attackBox_とcoll->hitBox_があたっているかどうか
    if (this->attackBox_.right < coll->hitBox_.left) return false;
    if (this->attackBox_.left > coll->hitBox_.right) return false;
    if (this->attackBox_.bottom < coll->hitBox_.top) return false;
    if (this->attackBox_.top > coll->hitBox_.bottom) return false;
    return true;
}

bool Collider::hitcheck(OBJ2D* obj) {
    return hitcheck(obj->collider());
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
    constexpr float LIMIT = 256.0f; // これ以上スクリーンから出ているものはとばす
    int cnt = 0;
    for (auto& obj : objList_)
    {
        const VECTOR2 pos = obj->transform()->position() - scrollPos;
        if (pos.x < -LIMIT || pos.x > window::getWidth() + LIMIT ||
            pos.y < -LIMIT || pos.y > window::getHeight() + LIMIT)
        {
            cnt++;
            continue;
        }
        obj->renderer()->draw(scrollPos);
        obj->collider()->draw(scrollPos);
    }
    debug::setString("cnt:%d", cnt);
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
