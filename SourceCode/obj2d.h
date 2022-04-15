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
    PLAYER, // 0
    ITEM,   // 1
    ENEMY,  // 2
    WEAPON, // 3

    MAX,    // 4
};

// �ړ��A���S���Y���N���X�i���ۃN���X�j
class Behavior
{
public:
    virtual void move(OBJ2D* obj) = 0;
    virtual OBJ_TYPE getType() = 0;
    virtual OBJ_TYPE attackType() = 0;
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

    const VECTOR2& position() const { return position_; }
    const VECTOR2& scale() const { return scale_; }
    const float rotation() const { return rotation_; }
    const VECTOR2& speed() const { return speed_; }

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

};

class Renderer : public Component
{
private:
    GameLib::SpriteData* data_;
    VECTOR4 color_;
    GameLib::Anime anime_;
    GameLib::AnimeData* animeData_;
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
    void setAnime(const GameLib::Anime& a) { anime_ = a; }
    void setAnimeData(GameLib::AnimeData* adata) { animeData_ = adata; }
};

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
        , judgeFlag_(false)
        , isDrawHitRect_(false)
        , hitBox_()
        , attackBox_()
    {}
    bool judgeFlag() { return judgeFlag_; };
    void draw(const VECTOR2&) override;

    void calcHitBox(const GameLib::fRECT& rc);
    void calcAttackBox(const GameLib::fRECT& rc);

    bool hitcheck(Collider* coll);
    bool hitcheck(OBJ2D* obj);

    const VECTOR2& size() const { return size_; }

    void setSize(const VECTOR2& s) { size_ = s; }
    void setJudgeFlag(bool b) { judgeFlag_ = b; }
    void setIsDrawHitRect(bool b) { isDrawHitRect_ = b; }
};

class ActorComponent : public Component
{
private:
    int jumpTimer_ = 0;
    bool onGround_ = false;
    bool hasSword_ = false;
public:
    ActorComponent()
        :jumpTimer_(0)
        , onGround_(false)
        , hasSword_(false) {}

    int jumpTimer() const { return jumpTimer_; }
    bool onGround() const { return onGround_; }
    bool hasSword() const { return hasSword_; }

    void setJumpTimer(int j) { jumpTimer_ = j; }
    void addJumpTimer(int a) { jumpTimer_ += a; }
    void setOnGround(bool b) { onGround_ = b; }
    void setHasSword(bool b) { hasSword_ = b; }
};

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

class BG;
class OBJ2D
{
private:
    // ��{�I�ȃ����o
    int         state_ = 0;
    int         timer_ = 0;
    Behavior* behavior_ = nullptr;
    Eraser* eraser_ = nullptr;

    BG* bg_ = nullptr;

    // �e�R���|�[�l���g
    Transform* transform_;
    Renderer* renderer_;
    Collider* collider_;
    ActorComponent* actorComponent_;
    ItemComponent* itemComponent_;

public:
    // �����o�֐�
    OBJ2D(Renderer* renderer,
        Collider* collider,
        BG* bg,
        ActorComponent* actorComponent,
        ItemComponent* itemComponent
    );
    ~OBJ2D();
    void move();    // �ړ�

    int state() const { return state_; }
    Behavior* behavior() const { return behavior_; }
    BG* bg() const { return bg_; }

    // �R���|�[�l���g�̃Q�b�^�[
    Transform* transform() const { return transform_; }
    Renderer* renderer() const { return renderer_; }
    Collider* collider() const { return collider_; }
    ActorComponent* actorComponent() const { return actorComponent_; }
    ItemComponent* itemComponent() const { return itemComponent_; }

    void setState(int s) { state_ = s; }
    void nextState() { state_++; }
    void setBehavior(Behavior* behavior) { behavior_ = behavior; }
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

