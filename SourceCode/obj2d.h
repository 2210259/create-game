#pragma once

//******************************************************************************
//
//
//      OBJ2D�N���X
//
//
//******************************************************************************

//------< �C���N���[�h >---------------------------------------------------------
#include <list>
#include "../GameLib/vector.h"
#include "../GameLib/obj2d_data.h"

// �O���錾
class OBJ2D;

//==============================================================================

enum class OBJ_TYPE {
    PLAYER,
    ITEM,
    ENEMY,
    WEAPON,
    MAX,
};

// �ړ��A���S���Y���N���X�i���ۃN���X�j
class Behavior
{
public:
    virtual void move(OBJ2D* obj) = 0;
    virtual OBJ_TYPE getType() const = 0;
    virtual OBJ_TYPE attackType() const = 0;
    virtual void hit(OBJ2D* src, OBJ2D* dst) = 0;
};

// �����A���S���Y���N���X�i���ۃN���X�j
class Eraser
{
public:
    virtual void erase(OBJ2D* obj) = 0;
};

//==============================================================================

//==============================================================================
//
//      OBJ2D�N���X
//
//==============================================================================

//----------------------------------------------------------------------
//  Component
//----------------------------------------------------------------------
class Component
{
private:
    OBJ2D* parent_;
public:
    Component()
        :parent_(nullptr) {}
    virtual void draw(const VECTOR2&) {}

    OBJ2D* parent() const { return parent_; }
    void setParent(OBJ2D* parent) { parent_ = parent; }
};

//----------------------------------------------------------------------
//  Transform
//----------------------------------------------------------------------
class Transform : public Component
{
private:
    VECTOR2 position_ = {};
    VECTOR2 scale_ = {};
    float rotation_ = 0;
    VECTOR2 speed_ = {};
public:
    Transform()
        :position_()
        , scale_(VECTOR2(1, 1))
        , rotation_(0.0f)
        , speed_() {}

    // getter
    const VECTOR2& position() const { return position_; }
    const VECTOR2& scale() const { return scale_; }
    const float rotation() const { return rotation_; }
    const VECTOR2& speed() const { return speed_; }

    // setter
    void setPosition(const VECTOR2& position) { position_ = position; }
    void setPositionX(float x) { position_.x = x; }
    void setPositionY(float y) { position_.y = y; }
    void addPositionX(float x) { position_.x += x; }
    void addPositionY(float y) { position_.y += y; }
    void setScale(const VECTOR2& s) { scale_ = s; }
    void setRotation(float r) { rotation_ = r; }
    void setSpeed(const VECTOR2& s) { speed_ = s; }
    void setSpeedX(float x) { speed_.x = x; }
    void setSpeedY(float y) { speed_.y = y; }
    void addSpeedX(float x) { speed_.x += x; }
    void addSpeedY(float y) { speed_.y += y; }

    void update() { position_ += speed_; }
    void rotate(float r) { rotation_ += r; }
};

//----------------------------------------------------------------------
//  Renderer
//----------------------------------------------------------------------
class Renderer : public Component
{
private:
    GameLib::SpriteData* data_ = nullptr;
    VECTOR4 color_ = {};
    GameLib::Anime anime_ = {};
    GameLib::AnimeData* animeData_ = nullptr;
public:
    Renderer()
        :data_(nullptr)
        , color_(VECTOR4(1, 1, 1, 1))
        , anime_()
        , animeData_(nullptr) {}
    void draw(const VECTOR2& scrollPos);
    bool animeUpdate();

    GameLib::AnimeData* animeData() const { return animeData_; }

    void setData(GameLib::SpriteData* d) { data_ = d; }
    void setColor(const VECTOR4& c) { color_ = c; }
    void setAnimeData(GameLib::AnimeData* adata) { animeData_ = adata; }
};

//----------------------------------------------------------------------
//  Collider
//----------------------------------------------------------------------
class Collider : public Component
{
private:
    VECTOR2 size_ = {};
    GameLib::fRECT hitBox_;
    GameLib::fRECT attackBox_;
    bool judgeFlag_;
    bool isDrawHitRect_;
public:
    Collider()
        :size_()
        , hitBox_()
        , attackBox_()
        , judgeFlag_(false)
        , isDrawHitRect_(false) {}
    void draw(const VECTOR2& scrollPos) override;
    void calcHitBox(const GameLib::fRECT& rc);
    void calcAttackBox(const GameLib::fRECT& rc);
    bool hitCheck(Collider* coll);
    bool hitCheck(OBJ2D* obj);

    const VECTOR2& size() const { return size_; }
    bool judgeFlag() const { return judgeFlag_; }

    void setSize(const VECTOR2& s) { size_ = s; }
    void setJudgeFlag(bool b) { judgeFlag_ = b; }
    void setIsDrawHitRect(bool b) { isDrawHitRect_ = b; }
};

//----------------------------------------------------------------------
//  ActorComponent
//----------------------------------------------------------------------
class ActorComponent : public Component
{
private:
    int jumpTimer_;
    int attackTimer_;
    int hp_;
    bool onGround_;
    bool kabeFlag_;
    bool gakeFlag_;
    bool xFlip_;
    bool hasSword_;
public:
    ActorComponent()
        :jumpTimer_(0)
        , attackTimer_(0)
        , hp_(1)
        , onGround_(false)
        , kabeFlag_(false)
        , gakeFlag_(false)
        , xFlip_(false)
        , hasSword_(false) {}

    // getter
    int jumpTimer() const { return jumpTimer_; }
    int attackTimer() const { return attackTimer_; }
    int hp() const { return hp_; }
    bool onGround() const { return onGround_; }
    bool hasSword() const { return hasSword_; }
    bool kabeFlag() const { return kabeFlag_; }
    bool gakeFlag() const { return gakeFlag_; }
    bool xFlip() const { return xFlip_; }

    // setter
    void setJumpTimer(int j) { jumpTimer_ = j; }
    void addJumpTimer(int a) { jumpTimer_ += a; }
    void setAttackTimer(int a) { attackTimer_ = a; }
    void subAttackTimer(int a) { attackTimer_ = std::max(attackTimer_ - a, 0); }
    void setHp(int h) { hp_ = h; }
    void addHp(int h) { hp_ += h; }
    void subHp(int h) { hp_ -= h; hp_ = std::max(hp_, 0); }
    void setOnGround(bool b) { onGround_ = b; }
    void setHasSword(bool b) { hasSword_ = b; }
    void setKabeFlag(bool b) { kabeFlag_ = b; }
    void setGakeFlag(bool b) { gakeFlag_ = b; }
    void setXFlip(bool b) { xFlip_ = b; }

    void flip() { xFlip_ = !xFlip_; }
    bool isAlive() const { return hp_ > 0; }
};

//----------------------------------------------------------------------
//  ItemComponent
//----------------------------------------------------------------------
class ItemComponent : public Component
{
private:
    VECTOR2 orgPos_;    // �ŏ��ɏo�������ʒu��ێ����Ă���
    float angle_;       // �T�C���J�[�u�Ȃǂŗh�炷�ꍇ�Ȃǂ̂��߂̔ėp�̕ϐ��i���R�Ɏg���Ă悢�j
public:
    ItemComponent()
        :orgPos_()
        , angle_(0) {}

    float angle() const { return angle_; }
    const VECTOR2& orgPos() const { return orgPos_; }

    void setOrgPos(const VECTOR2& pos) { orgPos_ = pos; }
    void setAngle(float a) { angle_ = a; }
    void addAngle(float a) { angle_ += a; }
};

#if 5
//******************************************************************************
// HACK:05 WeaponComponent�̍쐬
//------------------------------------------------------------------------------
/*
�m�F�j
    ���L��WeaponComponent�̍쐬�����Ă��܂��B
    �����o�֐��̊m�F�����Ă������ƁB
*/
//******************************************************************************
#endif
//HACK_05
//----------------------------------------------------------------------
//  WeaponComponent
//----------------------------------------------------------------------
class WeaponComponent : public Component
{
private:
    OBJ2D* owner_;  // ���̕���̎�����
    bool xFlip_;    // true �c ������ / false �c �E����
public:
    WeaponComponent()
        :owner_(nullptr)
        , xFlip_(false) {}

    // getter
    OBJ2D* owner() const { return owner_; }
    bool xFlip() const { return xFlip_; }

    // setter
    void setOwner(OBJ2D* o) { owner_ = o; }
    void setXFlip(bool b) { xFlip_ = b; }

    // ����̎������xFlip_�𕐊�ɐݒ肷��
    void copyOwnerXFlip();
};

//----------------------------------------------------------------------
//  OBJ2D
//----------------------------------------------------------------------
class BG;
class OBJ2D
{
private:
    // ��{�I�ȃ����o
    int         state_;
    int         timer_;
    Behavior*   behavior_;
    Eraser*     eraser_;

    BG* bg_;

    // �e�R���|�[�l���g
    Transform* transform_;
    Renderer* renderer_;
    Collider* collider_;
    ActorComponent* actorComponent_;
    ItemComponent* itemComponent_;
#if 6
//******************************************************************************
// HACK:06 WeaponComponent��OBJ2D�ɒǉ�
//------------------------------------------------------------------------------
/*
�m�F�j
    OBJ2D��WeaponComponent��ǉ����Ă��܂��B
    �R���X�g���N�^�A�C�j�V�����C�U�A�Q�b�^�[�Ȃǂ��p�ӂ��K�v�ł��B
*/
//******************************************************************************
#endif
    WeaponComponent* weaponComponent_;

public:
    // �����o�֐�
    OBJ2D(Renderer* renderer,
        Collider* collider,
        BG* bg,
        ActorComponent* actorComponent,
        ItemComponent* itemComponent, 
        WeaponComponent* weaponComponent
    );
    ~OBJ2D();
    void move();    // �ړ�

    // �R���|�[�l���g�̃Q�b�^�[
    Transform* transform() const { return transform_; }
    Renderer* renderer() const { return renderer_; }
    Collider* collider() const { return collider_; }
    ActorComponent* actorComponent() const { return actorComponent_; }
    ItemComponent* itemComponent() const { return itemComponent_; }
    WeaponComponent* weaponComponent() const { return weaponComponent_; }

    // getter
    int state() const { return state_; }
    int timer() const { return timer_; }
    Behavior* behavior() const { return behavior_; }
    BG* bg() const { return bg_; }

    // setter
    void setState(int s) { state_ = s; }
    void setBehavior(Behavior* behavior) { behavior_ = behavior; }
    void setEraser(Eraser* eraser) { eraser_ = eraser; }

    void nextState() { state_++; }
    void remove() { setBehavior(nullptr); }
};

//==============================================================================

// OBJ2DManager�N���X
class OBJ2DManager
{
private:
    VECTOR2* scrollPos_;
protected:
    std::list<OBJ2D*> objList_;
public:
    // �f�X�g���N�^
    ~OBJ2DManager();
    void setScrollPos(VECTOR2* s) { scrollPos_ = s; }

    void init();    // ������
    void update();  // �X�V
    void draw(const VECTOR2&);    // �`��

    OBJ2D* add(OBJ2D* obj, Behavior* behavior, const VECTOR2& pos);
    std::list<OBJ2D*>* getList() { return &objList_; }
};

//******************************************************************************
