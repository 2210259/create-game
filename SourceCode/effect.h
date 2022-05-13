#pragma once
//----------------------------------------//
//         　　effect.h    　    　       //
//----------------------------------------//


class BaseEffectBehavior : public Behavior
{
protected:
    struct Param 
    {
        GameLib::SpriteData* SPR_EFFECT = nullptr; //スプライト
        Eraser* ERASER = nullptr;                  //イレイサー
        VECTOR2 SCALE = { 1, 1 };                  //大きさ
        VECTOR2 SIZE  = { 1, 1 };                  //大きさ
        GameLib::fRECT ATTACK_BOX = {};
        GameLib::fRECT HIT_BOX = {};
        GameLib::AnimeData* ANIME_IDLE;     // 待機（正面）
        int EFFECT_TIMER; // 表示タイマー
    } param_ = {};
protected:
    const Param* getParam() { return &param_; }
private:
    void move(OBJ2D* obj) override;
    void update(OBJ2D* obj);
    OBJ_TYPE getType() const { return OBJ_TYPE::WEAPON; }
    OBJ_TYPE attackType() const override { return OBJ_TYPE::NONE; }

    void hit(OBJ2D*, OBJ2D*) override {};
};

// Goodエフェクト
class NotesEffect0Behavior : public BaseEffectBehavior
{
public:
    NotesEffect0Behavior();
};

EXTERN NotesEffect0Behavior notesEffect0Behavior;

// Greatエフェクト
class NotesEffect1Behavior : public BaseEffectBehavior
{
public:
    NotesEffect1Behavior();
};

EXTERN NotesEffect1Behavior notesEffect1Behavior;

// Perfectエフェクト
class NotesEffect2Behavior : public BaseEffectBehavior
{
public:
    NotesEffect2Behavior();
};

EXTERN NotesEffect2Behavior notesEffect2Behavior;

void setEffect(OBJ2DManager* obj2dManager, BG* bg, BaseEffectBehavior* effectBehavior, VECTOR2 pos);
