#pragma once

//******************************************************************************
//
//
//      weapon.h
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
class BaseWeaponBehavior : public Behavior
{
protected:
    struct Param {
    GameLib::SpriteData* SPR_WEAPON = nullptr; //スプライト
    Eraser* ERASER = nullptr;               //イレイサー
    VECTOR2 SCALE = { 1, 1 };               //大きさ

    GameLib::fRECT ATTACK_BOX = {};
    GameLib::fRECT HIT_BOX = {};

    } param_ = {};
protected:
    const Param* getParam() { return &param_; }
private:
    void move(OBJ2D* obj) override;
    void update(OBJ2D* obj);
    OBJ_TYPE getType() const { return OBJ_TYPE::WEAPON; }
    OBJ_TYPE attackType() const override { return OBJ_TYPE::ENEMY; }

    void hit(OBJ2D*, OBJ2D*) override {};
};

class WeaponBehavior : public BaseWeaponBehavior
{
public:
    WeaponBehavior();
private:
    void hit(OBJ2D* src, OBJ2D* dst) override;
};
EXTERN WeaponBehavior weaponbehavior;

//----------------------------------------//
//         　　    武器消去               //
//----------------------------------------//
class EsaEraser : public Eraser
{
private:
    void erase(OBJ2D* obj) override;
};
EXTERN EsaEraser esaEraser;

