#pragma once
//----------------------------------------//
//         �@�@effect.h    �@    �@       //
//----------------------------------------//


class BaseEffectBehavior : public Behavior
{
protected:
    struct Param 
    {
        GameLib::SpriteData* SPR_EFFECT = nullptr; //�X�v���C�g
        Eraser* ERASER = nullptr;                  //�C���C�T�[
        VECTOR2 SCALE = { 1, 1 };                  //�傫��
        VECTOR2 SIZE  = { 1, 1 };                  //�傫��
        GameLib::fRECT ATTACK_BOX = {};
        GameLib::fRECT HIT_BOX = {};
        GameLib::AnimeData* ANIME_IDLE;     // �ҋ@�i���ʁj
        int EFFECT_TIMER; // �\���^�C�}�[
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

// Good�G�t�F�N�g
class NotesEffect0Behavior : public BaseEffectBehavior
{
public:
    NotesEffect0Behavior();
};

EXTERN NotesEffect0Behavior notesEffect0Behavior;

// Great�G�t�F�N�g
class NotesEffect1Behavior : public BaseEffectBehavior
{
public:
    NotesEffect1Behavior();
};

EXTERN NotesEffect1Behavior notesEffect1Behavior;

// Perfect�G�t�F�N�g
class NotesEffect2Behavior : public BaseEffectBehavior
{
public:
    NotesEffect2Behavior();
};

EXTERN NotesEffect2Behavior notesEffect2Behavior;

void setEffect(OBJ2DManager* obj2dManager, BG* bg, BaseEffectBehavior* effectBehavior, VECTOR2 pos);
