#pragma once

//******************************************************************************
//
//
//      item.h
//
//
//******************************************************************************

void setItem(OBJ2DManager* obj2dManager, BG* bg);

//==============================================================================
//
//      BaseItemBehavior
//
//==============================================================================

class BaseItemBehavior : public Behavior
{
protected:
    struct Param {
        GameLib::SpriteData* SPR_ITEM = nullptr;
        VECTOR2 SIZE = {};
        GameLib::fRECT ATTACK_BOX = {};
        VECTOR2 SCALE = { 1, 1 };
    } param_;

protected:
    const Param* getParam() const { return &param_; }
private:
    void move(OBJ2D* obj) override;

    OBJ_TYPE getType() const override { return OBJ_TYPE::ITEM; }
    OBJ_TYPE attackType() const override { return OBJ_TYPE::PLAYER; }
};

//==============================================================================
//
//      ItemSword
//
//==============================================================================

class ItemSword : public BaseItemBehavior
{
public:
    ItemSword();
    void hit(OBJ2D* src, OBJ2D* dst) override;
};

//==============================================================================
//
//      ItemKey
//
//==============================================================================

class ItemKey : public BaseItemBehavior
{
public:
    ItemKey();
    void hit(OBJ2D* src, OBJ2D* dst) override;
};

//==============================================================================
//
//      ItemOrb
//
//==============================================================================

class ItemOrb : public BaseItemBehavior
{
public:
    ItemOrb();
    void hit(OBJ2D* src, OBJ2D* dst) override;
};

EXTERN ItemSword    itemSword;
EXTERN ItemKey      itemKey;
EXTERN ItemOrb      itemOrb;