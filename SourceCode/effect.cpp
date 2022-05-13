//******************************************************************************
//
//
//      effect.cpp
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;
using namespace input;

// エフェクトの配置
void setEffect(OBJ2DManager* obj2dManager, BG* bg, BaseEffectBehavior* effectBehavior, VECTOR2 pos)
{
    // エフェクトの生成
    OBJ2D* effect = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        nullptr,
        nullptr,
        new EffectComponent
    );

    obj2dManager->add(effect,
        effectBehavior,
        pos,
        -1, {}
    );
}
//----------------------------------------//
//        エフェクトのアニメーション      //
//----------------------------------------//
namespace
{
    //------< Goodエフェクトのアニメデータ >---------------------------------------------
    // 通常
    AnimeData animeEffect0_Idle[] = {
        { &sprEffect0_Idle0, 4 },
        { &sprEffect0_Idle1, 4 },
        { &sprEffect0_Idle2, 4 },
        { nullptr, -1 },// 終了フラグ
    };
    
    //------< Greatエフェクトのアニメデータ >---------------------------------------------
    // 通常
    AnimeData animeEffect1_Idle[] = {
        { &sprEffect1_Idle0, 4 },
        { &sprEffect1_Idle1, 4 },
        { &sprEffect1_Idle2, 4 },
        { nullptr, -1 },// 終了フラグ
    };

    //------< perfectエフェクトのアニメデータ >---------------------------------------------
    // 通常
    AnimeData animeEffect2_Idle[] = {
        { &sprEffect2_Idle0, 4 },
        { &sprEffect2_Idle1, 4 },
        { &sprEffect2_Idle2, 4 },
        { nullptr, -1 },// 終了フラグ
    };
}

void BaseEffectBehavior::move(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();
    Collider* collider = obj->collider();
    EffectComponent* effectComponent = obj->effectComponent();
    BG* bg = obj->bg();

    switch (obj->state())
    {
    case 0: {
        //////// 初期設定 ////////
        transform->setScale(getParam()->SCALE);
        const VECTOR2 size = {
            getParam()->SIZE.x * getParam()->SCALE.x,
            getParam()->SIZE.y * getParam()->SCALE.y,
        };
        collider->setSize(size);

        renderer->setData(getParam()->SPR_EFFECT);
        obj->setEraser(getParam()->ERASER);
        obj->renderer()->setAnimeData(getParam()->ANIME_IDLE);
        obj->effectComponent()->setEffectTimer(getParam()->EFFECT_TIMER);

        obj->nextState();//state++
        /*fallthrough*/
    }
    case 1:
        //////// 通常時 ////////
        update(obj);

        break;
    }

    // アニメーション更新
    if (obj->renderer()->animeData())
        obj->renderer()->animeUpdate();
}

void BaseEffectBehavior::update(OBJ2D* obj)
{
    Renderer* renderer = obj->renderer();
    Transform* transform = obj->transform();
    
    obj->effectComponent()->countEffectTimer();

    // エフェクトを削除
    if (obj->effectComponent()->effectTimer() < 0) {
        obj->remove();
    }
}

NotesEffect0Behavior::NotesEffect0Behavior()
{
    param_.ANIME_IDLE = animeEffect0_Idle;  // 待機（正面）
    param_.SIZE  = { 150, 150 };
    param_.SCALE = { 1.5f, 1.5f };
    param_.EFFECT_TIMER = 12;
}

NotesEffect1Behavior::NotesEffect1Behavior()
{
    param_.ANIME_IDLE = animeEffect1_Idle;  // 待機（正面）
    param_.SIZE = { 150, 150 };
    param_.SCALE = { 1.5f, 1.5f };
    param_.EFFECT_TIMER = 12;
}

NotesEffect2Behavior::NotesEffect2Behavior()
{
    param_.ANIME_IDLE = animeEffect2_Idle;  // 待機（正面）
    param_.SIZE = { 150, 150 };
    param_.SCALE = { 1.5f, 1.5f };
    param_.EFFECT_TIMER = 12;
}
