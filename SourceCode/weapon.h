#pragma once

#if 7
//******************************************************************************
// HACK:07 BaseWeaponBehaviorクラスの作成
//------------------------------------------------------------------------------
/*
確認）
    BaseWeaponBehaviorクラスを作成しています。
*/
//******************************************************************************
#endif
class BaseWeaponBehavior : public Behavior
{
protected:
    struct Param {
        GameLib::SpriteData*    SPR_WEAPON;     // スプライト
        Eraser*                 ERASER;         // イレイサー（削除用のアルゴリズム）
        float                   SPEED_X;        // 横方向の速度（手裏剣用）
        float                   ROT_SPEED;      // 回転速度（手裏剣用）
        int                     ATTACK_POWER;   // 攻撃力
        VECTOR2                 SCALE;          // スケール
        GameLib::fRECT          ATTACK_BOX;     // 攻撃用あたり領域
    } param_ = {};

protected:
    const Param* getParam() { return &param_; }
private:
    void move(OBJ2D* obj) override;
    virtual void update(OBJ2D* obj) = 0;        // 位置に速度を足す
    virtual void calcAttackBox(OBJ2D* obj) = 0; // 攻撃用あたり領域の計算
    OBJ_TYPE getType() const override { return OBJ_TYPE::WEAPON; }
    OBJ_TYPE attackType() const override { return OBJ_TYPE::ENEMY; }
};

//----------------------------------------------------------------------
//  ShurikenBehavior
//----------------------------------------------------------------------
#if 9
//******************************************************************************
// HACK:09 ShurikenBehaviorの作成
//------------------------------------------------------------------------------
/*
確認）
    ShurikenBehaviorクラスを作成しています。
    どんな関数をオーバーライドする必要があるか確認しておくこと。
*/
//******************************************************************************
#endif
class ShurikenBehavior : public BaseWeaponBehavior
{
public:
    ShurikenBehavior();
private:
    void update(OBJ2D* obj) override;
    void calcAttackBox(OBJ2D* obj) override;
    void hit(OBJ2D* src, OBJ2D* dst) override;
};
EXTERN ShurikenBehavior shurikenBehavior;

//----------------------------------------------------------------------
//  SwordBehavior
//----------------------------------------------------------------------
class SwordBehavior : public BaseWeaponBehavior
{
public:
    SwordBehavior();
private:
    void update(OBJ2D* obj) override;
    void calcAttackBox(OBJ2D* obj) override;
    void hit(OBJ2D* src, OBJ2D* dst) override;
};
EXTERN SwordBehavior swordBehavior;

#if 10
//******************************************************************************
// HACK:10 ShurikenEraserクラスの作成
//------------------------------------------------------------------------------
/*
確認）
    ここでShurikenBehaviorのコンストラクタで必要になる、手裏剣のEraserを用意しています。
    Eraserは、オブジェクトを削除する専用のアルゴリズムです。
*/
//******************************************************************************
#endif
class ShurikenEraser : public Eraser
{
private:
    void erase(OBJ2D* obj) override;
};
EXTERN ShurikenEraser shurikenEraser;

class SwordEraser : public Eraser
{
private:
    void erase(OBJ2D* obj) override;
};
EXTERN SwordEraser swordEraser;