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
    ENEMY,  // 1
    WEAPON, // 2

    MAX,    // 3
};

// �ړ��A���S���Y���N���X�i���ۃN���X�j
class Behavior
{
public:
    virtual void move(OBJ2D* obj) = 0;
    virtual OBJ_TYPE getType() const = 0;
    virtual OBJ_TYPE attackType() const = 0;
    virtual void hit(OBJ2D* src, OBJ2D* dst) = 0;
    virtual void hit2(OBJ2D* src, OBJ2D* dst) {};
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

//----------------------------------------
//            Component
//----------------------------------------
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

//----------------------------------------
//            Transform
//----------------------------------------
class Transform : public Component
{
private:
    VECTOR2 position_ = {};
    VECTOR2 orgPos_;    // �ŏ��ɏo�������ʒu��ێ����Ă���
    VECTOR2 scale_ = {};
    float rotation_ = 0;
    VECTOR2 speed_ = {};
public:
    Transform()
        :position_()
        , orgPos_()
        , scale_(VECTOR2(1, 1))
        , rotation_(0.0f)
        , speed_() {}

    // �Q�b�^�[
    const VECTOR2& position() const { return position_; }
    const VECTOR2& orgPos() const { return orgPos_; }
    const VECTOR2& scale() const { return scale_; }
    const float rotation() const { return rotation_; }
    const VECTOR2& speed() const { return speed_; }

    // �Z�b�^�[
    void setPosition(const VECTOR2& position) { position_ = position; }
    void setPositionX(float x) { position_.x = x; }
    void setPositionY(float y) { position_.y = y; }
    void addPositionX(float x) { position_.x += x; }
    void addPositionY(float y) { position_.y += y; }

    void setOrgPos(const VECTOR2& pos) { orgPos_ = pos; }
    void setScale(const VECTOR2& s) { scale_ = s; }
    void setRotation(float r) { rotation_ = r; }

    void setSpeed(const VECTOR2& s) { speed_ = s; }
    void setSpeedX(float x) { speed_.x = x; }
    void setSpeedY(float y) { speed_.y = y; }
    void addSpeedX(float x) { speed_.x += x; }
    void addSpeedY(float y) { speed_.y += y; }
};

//----------------------------------------
//            Renderer
//----------------------------------------
class Renderer : public Component
{
private:
    GameLib::SpriteData* data_ = nullptr;
    VECTOR4 color_ = {};
    GameLib::Anime anime_ = {};
    GameLib::AnimeData* animeData_ = nullptr;
    int animetimer_ = 0;
public:
    Renderer()
        :data_(nullptr)
        , color_(VECTOR4(1, 1, 1, 1))
        , anime_()
        , animeData_(nullptr) 
        , animetimer_(0)
    {}

    // �Q�b�^�[
    void draw(const VECTOR2& scrollPos);
    bool animeUpdate();
    VECTOR4 color() { return color_; }
    int animeTimer() { return animetimer_; }

    GameLib::AnimeData* animeData() const { return animeData_; }

    // �Z�b�^�[
    void setData(GameLib::SpriteData* d) { data_ = d; }
    void setColor(const VECTOR4& c) { color_ = c; }
    void setAnime(const GameLib::Anime& a) { anime_ = a; }
    void setAnimeData(GameLib::AnimeData* adata) { animeData_ = adata; }

    //�A�j���[�V�����^�C�}�[���Z
    void countaniTime() { ++animetimer_; }

    //�A�j���[�V�����^�C�}�[���Z�b�g
    void aniTimeReset() { animetimer_ = 0; }
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

    void draw(const VECTOR2&) override;
    void calcHitBox(const GameLib::fRECT& rc); // �q�b�g�{�b�N�X�v�Z
    void calcAttackBox(const GameLib::fRECT& rc);

    bool hitcheck(Collider* coll);
    bool hitcheck(OBJ2D* obj);

    //�Q�b�^�[
    const VECTOR2& size() const { return size_; }
    bool judgeFlag() const { return judgeFlag_; }
    GameLib::fRECT hitbox() const { return hitBox_; }

    // �Z�b�^�[
    void setSize(const VECTOR2& s) { size_ = s; }
    void setJudgeFlag(bool b) { judgeFlag_ = b; }
    void setIsDrawHitRect(bool b) { isDrawHitRect_ = b; }
};

//----------------------------------------
//            ActorComponent
//----------------------------------------
class ActorComponent : public Component
{
private:
    int  hp_;           // �̗�
    bool moveFlag_;     // �a���G�̊��m�͈͂ɓ��������ǂ����̃t���O
    bool xFlip_;        // X���W�̌���
    bool hitFlag_;      // �a���G�ɓ������������ǂ����̃t���O
    int  deadTimer_;    // �G�̏��Ŏ���

public:
    ActorComponent()
        : hp_(0)
        , moveFlag_(false)
        , xFlip_(false)
        , hitFlag_(false)
        , deadTimer_(0)
    {}

    // �Q�b�^�[
    int hp() const { return hp_; }
    bool moveFlag() const { return moveFlag_; }
    bool hitFlag() const { return hitFlag_; }
    bool xFlip() const { return xFlip_; }
    int deadTimer() const { return deadTimer_; }

    // �Z�b�^�[
    void setHP(int h) { hp_ = h; }
    void setmoveFlag(bool f) { moveFlag_ = f; }
    void sethitFlag(bool f) { hitFlag_ = f; }
    void setFlip(bool b) { xFlip_ = b; }
    void setDeadTimer(int t) { deadTimer_ = t; }

    // X���W�̌����𔽓]
    void flip() { xFlip_ = !xFlip_; }

    // HP�����炷
    void damage() { --hp_; }
};

//----------------------------------------
//            WeaponComponent
//----------------------------------------
class WeaponComponent : public Component
{
private:
    OBJ2D* owner_;      // ������
    bool xFlip_;        // true���@false�E����
    bool weaponFlag_;   // �a�����邩�ǂ����̃t���O
    bool removeLFlag_;

public:
    WeaponComponent()
        :owner_(nullptr)
        , xFlip_(false)
        , weaponFlag_(false)
        , removeLFlag_(false)
    {}

    //�Q�b�^�[
    OBJ2D* owner() const { return owner_; }
    bool xFlip() const { return xFlip_; }
    bool weaponFlag() const { return weaponFlag_; }
    bool removeLFlag() const { return removeLFlag_; }

    //�Z�b�^�[
    void setOwner(OBJ2D* o) { if (!o) owner_ = o; }
    void setXFlip(bool b) { xFlip_ = b; }
    void setweaponFlag(bool f) { weaponFlag_ = f; }
    void setRemoveLFlag(bool f) { removeLFlag_ = f; }

    // void copyOwnerXFlip();
};
//----------------------------------------
//            OBJ2D
//----------------------------------------
class BG;
class OBJ2D
{
private:
    // ��{�I�ȃ����o
    int       state_    = 0; //���
    int       timer_    = 0; //�^�C�}�[
    int       enemyState_;   // �G�̏��
    Behavior* behavior_ = nullptr;
    Eraser*   eraser_ = nullptr;

    BG* bg_ = nullptr;

    // �e�R���|�[�l���g
    Transform* transform_;
    Renderer* renderer_;
    Collider* collider_;
    ActorComponent* actorComponent_;
    WeaponComponent* weaponComponent_;

public:
    // �����o�֐�
    OBJ2D(Renderer* renderer,
        Collider* collider,
        BG* bg,
        ActorComponent* actorComponent,
        WeaponComponent* weaponComponent
    );
    ~OBJ2D();
    void move();    // �ړ�


    // �R���|�[�l���g�̃Q�b�^�[
    Transform* transform() const { return transform_; }
    Renderer* renderer() const { return renderer_; }
    Collider* collider() const { return collider_; }
    ActorComponent* actorComponent() const { return actorComponent_; }
    WeaponComponent* weaponComponent() const { return weaponComponent_; }

    // �Q�b�^�[
    int state() const { return state_; }
    int timer() const { return timer_; }
    int enemyState() const { return enemyState_; }
    Behavior* behavior() const { return behavior_; }
    BG* bg() const { return bg_; }

    // �Z�b�^�[
    void setState(int s) { state_ = s; }
    void setEnemyState(int s) { enemyState_ = s; }
    void setBehavior(Behavior* behavior) { behavior_ = behavior; }
    void setEraser(Eraser* eraser) { eraser_ = eraser; }

    // �C���N�������g
    void nextState() { state_++; }
    void nextEnemyState() { enemyState_++; }

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

