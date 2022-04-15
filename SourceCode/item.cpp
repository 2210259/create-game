#include "all.h"

void setItem(OBJ2DManager* obj2dManager, BG* bg)
{
    char st1_item[BG::CHIP_NUM_Y][BG::CHIP_NUM_X] = {
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    };

    BaseItemBehavior* itemBehavior[] = {
        &itemSword,
        nullptr,
        &itemKey,
        nullptr,
        &itemOrb,
    };

    for (int y = 0; y < BG::CHIP_NUM_Y; y++)
    {
        for (int x = 0; x < BG::CHIP_NUM_X; x++)
        {
            const char chip = st1_item[y][x];
            if (chip < 0) continue;
            assert(chip < ARRAYSIZE(itemBehavior));
            if (!itemBehavior[chip]) continue;

            const VECTOR2 pos = {
                x * BG::CHIP_SIZE_F + BG::CHIP_SIZE_F * 0.5f,
                y * BG::CHIP_SIZE_F + BG::CHIP_SIZE_F * 0.5f,
            };
            OBJ2D* item = new OBJ2D(
                new Renderer,
                new Collider,
                bg,
                nullptr,
                new ItemComponent
            );
            obj2dManager->add(item, itemBehavior[chip], pos);
        }
    }
}

//==============================================================================
//
//      BaseItemBehavior
//
//==============================================================================

void BaseItemBehavior::move(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();
    Collider* collider = obj->collider();

    switch (obj->state())
    {
    case 0:
        //////// ‰ŠúÝ’è ////////
        transform->setScale(getParam()->SCALE);
        renderer->setData(getParam()->SPR_ITEM);
        collider->setSize(getParam()->SIZE);
        collider->setJudgeFlag(true);
        collider->setIsDrawHitRect(true);

        collider->calcAttackBox(getParam()->ATTACK_BOX);

        obj->nextState();//state++
        break;
    case 1:
        //////// ’ÊíŽž ////////
        break;
    }
}

//==============================================================================
//
//      ItemSword
//
//==============================================================================

ItemSword::ItemSword()
{
    param_.SPR_ITEM = &sprItemSword;
    param_.SIZE = { BG::CHIP_SIZE * 0.5f, BG::CHIP_SIZE * 0.5f };
    param_.ATTACK_BOX = { -28, -28, 28, 28 };
    param_.SCALE = { 1, 1 };
}

void ItemSword::hit(OBJ2D* src, OBJ2D* dst)
{
    switch (dst->behavior()->getType())
    {
    case OBJ_TYPE::PLAYER:
        if (dst->actorComponent())
            dst->actorComponent()->setHasSword(true);
        break;
    }
    src->setBehavior(nullptr);
}

//==============================================================================
//
//      ItemKey
//
//==============================================================================

ItemKey::ItemKey()
{
    param_.SPR_ITEM = &sprItemKey;
    param_.SIZE = { BG::CHIP_SIZE * 0.5f, BG::CHIP_SIZE * 0.5f };
    param_.ATTACK_BOX = { -28, -28, 28, 28 };
    param_.SCALE = { 1, 1 };
}

void ItemKey::hit(OBJ2D* src, OBJ2D* dst)
{
    src->setBehavior(nullptr);
}
//==============================================================================
//
//      ItemOrb
//
//==============================================================================

ItemOrb::ItemOrb()
{
    param_.SPR_ITEM = &sprItemOrb;
    param_.SIZE = { BG::CHIP_SIZE * 0.5f, BG::CHIP_SIZE * 0.5f };
    param_.ATTACK_BOX = { -28, -28, 28, 28 };
    param_.SCALE = { 1, 1 };
}

void ItemOrb::hit(OBJ2D* src, OBJ2D* dst)
{
    src->setBehavior(nullptr);
}