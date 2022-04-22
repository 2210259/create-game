#include "all.h"

#if 8
//******************************************************************************
// HACK:08 武器のmove関数
//------------------------------------------------------------------------------
/*
確認）
    BaseWeaponBehaviorのmove関数です。
    OBJ2DクラスにsetEraserが追加されています。
*/
//******************************************************************************
#endif
void BaseWeaponBehavior::move(OBJ2D* obj)
{
    switch (obj->state())
    {
    case 0:
        //////// 初期設定 ////////
        obj->renderer()->setData(getParam()->SPR_WEAPON);
        obj->transform()->setScale(getParam()->SCALE);
        obj->setEraser(getParam()->ERASER);
        obj->collider()->setJudgeFlag(true);      // あたり判定を行う
        obj->collider()->setIsDrawHitRect(true);  // あたり判定の領域を描画する（デバッグ用）

        // 左右の向き、速度を設定（プレイヤーにもxFlip_の設定が必要）
        obj->weaponComponent()->copyOwnerXFlip();   // 武器の持ち主のxFlip_を武器に設定する
        obj->transform()->setSpeedX(
            obj->weaponComponent()->xFlip()
            ? -getParam()->SPEED_X : getParam()->SPEED_X);
        obj->transform()->setSpeedY(0.0f);        // 念のため

        obj->nextState();//state++
        /*fallthrough*/

    case 1:
        //////// 通常時 ////////
        update(obj);    // 武器の位置更新
        calcAttackBox(obj);
        break;
    }
}

#if 12
//******************************************************************************
// HACK:12 ShurikenBehaviorのコンストラクタ
//------------------------------------------------------------------------------
/*
確認）
    手裏剣のパラメータは以下のようになっています。
*/
//******************************************************************************
#endif
ShurikenBehavior::ShurikenBehavior()
{
    param_.SPR_WEAPON   = &sprWeapon_Shuriken;
    param_.ERASER       = &shurikenEraser;
    param_.SPEED_X      = 20.0f;
    param_.ROT_SPEED    = ToRadian(24);
    param_.ATTACK_POWER = 1;
    param_.SCALE        = { 0.5f, 0.5f };
    param_.ATTACK_BOX   = { -24, -24, 24, 24 };
}

#if 3
//******************************************************************************
// TODO:03 手裏剣のupdate関数
//------------------------------------------------------------------------------
/*
手順）
    □ 手裏剣の位置に速度を足す。
    □ 手裏剣に回転を加える。（右に進む際は時計回り、左は反時計回りに）

解説）
    位置に速度を足すために、Transform::update関数が用意されています。

    手裏剣がどちらを向いているかは、WeaponComponent::xFlip_に保持されています。
    オブジェクトを回転させるために、Transform::rotate関数が用意されています。
    １フレームでどれだけ回転するかは、パラメータのROT_SPEEDに値が入っています。
*/
//******************************************************************************
#endif
void ShurikenBehavior::update(OBJ2D* obj)
{
    //TODO_03
    // 手裏剣の位置に速度を足す
    obj->transform()->update();

    // 手裏剣に回転を加える（右に進む際は時計回り、左は反時計回りに）
    obj->transform()->rotate(
        obj->weaponComponent()->xFlip()
        ? -getParam()->ROT_SPEED : getParam()->ROT_SPEED);
}

#if 4
//******************************************************************************
// TODO:04 手裏剣の攻撃領域の計算
//------------------------------------------------------------------------------
/*
手順）
    ColliderクラスのcalcAttackBoxメソッドで攻撃領域を計算しましょう。
*/
//******************************************************************************
#endif
void ShurikenBehavior::calcAttackBox(OBJ2D* obj)
{
    //TODO_04
    // 攻撃判定の計算
    obj->collider()->calcAttackBox(getParam()->ATTACK_BOX);
};

#if 5
//******************************************************************************
// TODO:05 手裏剣のhit関数
//------------------------------------------------------------------------------
/*
手順）
    □ 手裏剣が当たった敵のHPから手裏剣の攻撃力分を引く。
      （dstのactorComponentのsubHpメソッドを使用する）

    □ 手裏剣を削除する。

解説）
    武器のattackTypeはOBJ_TYPE::ENEMYなので、下記の引数srcは手裏剣、dstには手裏剣が
    当たった敵のポインタになっています。
    ActorComponent::subHpメソッド内では、hp_がマイナスにならないような処理が入っています。
    手裏剣の攻撃力は、getParam()->ATTACK_POWERです。
*/
//******************************************************************************
#endif
void ShurikenBehavior::hit(OBJ2D* src, OBJ2D* dst)
{
    //TODO_05
    // 手裏剣が当たった敵のHPから手裏剣の攻撃力分を引く
    dst->actorComponent()->subHp(getParam()->ATTACK_POWER);

    // 手裏剣を削除する
    src->remove();
}

#if 11
//******************************************************************************
// HACK:11 erase関数の作成
//------------------------------------------------------------------------------
/*
確認）
    erase関数では、オブジェクトがどういう条件で削除されるかを記述します。
*/
//******************************************************************************
#endif
void ShurikenEraser::erase(OBJ2D* obj)
{
    const VECTOR2* scrollPos = &obj->bg()->getScrollPos();
    const VECTOR2* size = &obj->collider()->size();
    const VECTOR2* pos = &obj->transform()->position();

    const float leftLimit = scrollPos->x - size->x;
    const float rightLimit = scrollPos->x + BG::CLIENT_W + size->x;
    const float topLimit = scrollPos->y - size->y;
    const float bottomLimit = scrollPos->y + BG::CLIENT_H + size->y;

    if (pos->x < leftLimit ||
        pos->x > rightLimit ||
        pos->y < topLimit ||
        pos->y > bottomLimit)
    {
        obj->remove();
    }
}

SwordBehavior::SwordBehavior()
{
    param_.SPR_WEAPON   = &sprWeapon_Sword;
    param_.ERASER       = &swordEraser;
    param_.ATTACK_POWER = 2;
    param_.SCALE        = { 1, 1 };
    param_.ATTACK_BOX   = { -32, -32, 32, 32 };
}

void SwordBehavior::update(OBJ2D* obj)
{
    bool xFlip = obj->weaponComponent()->xFlip();
    float ang = 0.0f;
    if (!xFlip) {
        // 右を向いている
        ang = -30 + obj->timer() * 15;
        if (ang > 105) ang = 105;
    }
    else {
        // 左を向いている
        ang = 30 - obj->timer() * 15;
        if (ang < -105) ang = -105;
    }
    obj->transform()->setRotation(ToRadian(ang));// ラジアンにする

    obj->transform()->setPosition(
        obj->weaponComponent()->owner()->transform()->position()
        + VECTOR2(0, -48));
}

void SwordBehavior::calcAttackBox(OBJ2D* obj)
{
    float angle = obj->transform()->rotation();
    VECTOR2 pos = { sinf(angle) * 96, -cosf(angle) * 96 };
    obj->collider()->calcAttackBox(
        {
            pos.x + getParam()->ATTACK_BOX.left,
            pos.y + getParam()->ATTACK_BOX.top,
            pos.x + getParam()->ATTACK_BOX.right,
            pos.y + getParam()->ATTACK_BOX.bottom,
        }
    );
}

void SwordBehavior::hit(OBJ2D* src, OBJ2D* dst)
{
    // 剣が当たった敵のHPから剣の攻撃力分を引く
    dst->actorComponent()->subHp(getParam()->ATTACK_POWER);
    src->collider()->setJudgeFlag(false);
}

void SwordEraser::erase(OBJ2D* obj)
{
    if (obj->timer() > 15)
    {
        obj->remove();
    }
}
