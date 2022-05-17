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
    EFFECT, // 3

    NONE,   // 4
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
    virtual void hit3(OBJ2D* src, OBJ2D* dst) {};
    virtual void hit4(OBJ2D* src, OBJ2D* dst) {};
    virtual void hit5(OBJ2D* src, OBJ2D* dst) {};
    virtual void hit6(OBJ2D* src, OBJ2D* dst) {};
    virtual void hit7(OBJ2D* src, OBJ2D* dst) {};
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
    VECTOR2 orgScale_ = {};
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
    const VECTOR2& orgScale() const { return orgScale_; }
    const float rotation() const { return rotation_; }
    const VECTOR2& speed() const { return speed_; }

    // �Z�b�^�[
    void setPosition(const VECTOR2& position) { position_ = position; }
    void setPositionX(float x) { position_.x = x; }
    void setPositionY(float y) { position_.y = y; }
    void addPositionX(float x) { position_.x += x; }
    void addPositionY(float y) { position_.y += y; }
    void addPosition(VECTOR2 p) { position_ += p; }

    void setOrgPos(const VECTOR2& pos) { orgPos_ = pos; }
    void setScale(const VECTOR2& s) { scale_ = s; }
    void setOrgScale(const VECTOR2& s) { orgScale_ = s; }
    void setRotation(float r) { rotation_ = r; }
    void rotate(float r) { rotation_ += r; }

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
    void draw2(const VECTOR2& scrollPos);
    void draw3(const VECTOR2& scrollPos);
    bool animeUpdate();
    
    VECTOR4 color() { return color_; }
    int animeTimer() { return animetimer_; }

    GameLib::AnimeData* animeData() const { return animeData_; }

    // �Z�b�^�[
    void setData(GameLib::SpriteData* d) { data_ = d; }
    void setColor(const VECTOR4& c) { color_ = c; }
    void setAnime(const GameLib::Anime& a) { anime_ = a; }
    void setAnimeData(GameLib::AnimeData* adata) { animeData_ = adata; }
    void setAnimeTimer(int a) { animetimer_ = a; }

    //�A�j���[�V�����^�C�}�[���Z
    void countAnimeTime() { ++animetimer_; }

    //�A�j���[�V�����^�C�}�[���Z�b�g
    void animeTimeReset() { animetimer_ = 0; }
};

//----------------------------------------
//            Collider
//----------------------------------------
class Collider : public Component
{
private:
    VECTOR2 size_ = {};
    VECTOR2 mergin_ = {};

    GameLib::fRECT hitBox_;
    GameLib::fRECT hitBox2_;
    GameLib::fRECT hitBox3_;
    GameLib::fRECT hitBox4_;
    GameLib::fRECT hitBox5_;
    GameLib::fRECT hitBox6_;
    GameLib::fRECT hitBox7_;

    GameLib::fRECT attackBox_;
    GameLib::fRECT attackBox2_;

    bool judgeFlag_;
    bool judgeBoxFlag_;
    bool judgeBoxFlag2_;
    bool judgeBoxFlag3_;
    bool judgeBoxFlag4_;
    bool isDrawHitRect_;
public:
    Collider()
        :size_()
        , mergin_()
        , judgeFlag_(false)
        , judgeBoxFlag_(false)
        , judgeBoxFlag2_(false)
        , judgeBoxFlag3_(false)
        , judgeBoxFlag4_(false)
        , isDrawHitRect_(false)
        , hitBox_()
        , hitBox2_()
        , hitBox3_()
        , hitBox4_()
        , hitBox5_()
        , hitBox6_()
        , hitBox7_()
        , attackBox_()
    {}

    void draw(const VECTOR2&) override;
    void calcHitBox(const GameLib::fRECT& rc);
    void calcHitBox2(const GameLib::fRECT& rc);
    void calcHitBox3(const GameLib::fRECT& rc);
    void calcHitBox4(const GameLib::fRECT& rc);
    void calcHitBox5(const GameLib::fRECT& rc);
    void calcHitBox6(const GameLib::fRECT& rc);
    void calcHitBox7(const GameLib::fRECT& rc);

    void calcAttackBox(const GameLib::fRECT& rc);

    bool hitCheck(Collider* coll);
    bool hitCheck(OBJ2D* obj);

    bool hitCheck2(Collider* coll);
    bool hitCheck2(OBJ2D* obj);

    bool hitCheck3(Collider* coll);
    bool hitCheck3(OBJ2D* obj);

    bool hitCheck4(Collider* coll);
    bool hitCheck4(OBJ2D* obj);

    bool hitCheck5(Collider* coll);
    bool hitCheck5(OBJ2D* obj);

    bool hitCheck6(Collider* coll);
    bool hitCheck6(OBJ2D* obj);

    bool hitCheck7(Collider* coll);
    bool hitCheck7(OBJ2D* obj);

    //�Q�b�^�[
    const VECTOR2& size() const { return size_; }
    const VECTOR2& mergin() const { return mergin_; }
    bool judgeFlag() const { return judgeFlag_; }
    bool judgeBoxFlag() const { return judgeBoxFlag_; }
    bool judgeBoxFlag2() const { return judgeBoxFlag2_; }
    bool judgeBoxFlag3() const { return judgeBoxFlag3_; }
    bool judgeBoxFlag4() const { return judgeBoxFlag4_; }
    GameLib::fRECT hitbox() const { return hitBox_; }

    // �Z�b�^�[
    void setSize(const VECTOR2& s) { size_ = s; }
    void setMergin(const VECTOR2& m) { mergin_ = m; }
    void setJudgeFlag(bool f) { judgeFlag_ = f; }
    void setJudgeBoxFlag(bool f) { judgeBoxFlag_ = f; }
    void setJudgeBoxFlag2(bool f) { judgeBoxFlag2_ = f; }
    void setJudgeBoxFlag3(bool f) { judgeBoxFlag3_ = f; }
    void setJudgeBoxFlag4(bool f) { judgeBoxFlag4_ = f; }
    void setIsDrawHitRect(bool b) { isDrawHitRect_ = b; }
};

//----------------------------------------
//            ActorComponent
//----------------------------------------
class ActorComponent : public Component
{
private:
    int  hp_;           // �̗�
    int  maxHP_;        // �ő�̗�
    int  score_;        // �X�R�A��
    bool moveFlag_;     // �a���G�̊��m�͈͂ɓ��������ǂ����̃t���O
    bool xFlip_;        // X���W�̌���
    bool hitFlag_;      // �a���G�ɓ������������ǂ����̃t���O
    int  deadTimer_;    // �G�̏��Ŏ���
    int  posType_;      // �G�̏o������
    bool deleteCombo2Flag_; // �R���{2�����ł���t���O
    int playerHitTimer_; // �v���C���[�̓_�Ŏ��� 
    
public:
    enum DIRECTON              // ����
    {
        UP,                    // ��
        LEFT,                  // ��
        RIGHT,                 // �E
        DOWN,                  // ��
    } direction_;
    
    ActorComponent()
        : hp_(0)
        , maxHP_(0)
        , score_(0)
        , moveFlag_(false)
        , xFlip_(false)
        , hitFlag_(false)
        , deadTimer_(0)
        , posType_(0)
        , deleteCombo2Flag_(false)
        , playerHitTimer_(0)
        , direction_(UP)
    {}
    // �Q�b�^�[
    int hp() const { return hp_; }
    int maxHP() const { return maxHP_; }
    bool moveFlag() const { return moveFlag_; }
    bool hitFlag() const { return hitFlag_; }
    bool xFlip() const { return xFlip_; }
    int direction() const { return direction_; }
    int deadTimer() const { return deadTimer_; }
    int posType() const { return posType_; }
    int score() { return score_; }
    int playerHitTimer() { return playerHitTimer_; }
    bool deleteCombo2Flag() const { return deleteCombo2Flag_; }

    // �Z�b�^�[
    void setHP(int h) { hp_ = h; }
    void setMaxHP(int h) { maxHP_ = h; }
    void setmoveFlag(bool f) { moveFlag_ = f; }
    void setHitFlag(bool f) { hitFlag_ = f; }
    void setDirection(DIRECTON d) { direction_ = d; }
    void setFlip(bool b) { xFlip_ = b; }
    void setDeadTimer(int t) { deadTimer_ = t; }
    void setPosType(int p) { posType_ = p; }
    void setScore(int s) { score_ = s; }
    void setPlayerHitTimer(int t) { playerHitTimer_ = t; }
    void setDeleteCombo2Flag(bool f) { deleteCombo2Flag_ = f; }

    // X���W�̌����𔽓]
    void flip() { xFlip_ = !xFlip_; }

    // HP�����炷
    void damage() { --hp_; }
    void countDeadTimer() { --deadTimer_; }
    void countPlayerHitTimer() { --playerHitTimer_; }
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
    int  posType_;      // ����̏o������
    int weaponTimer_;  

public:
    WeaponComponent()
        :owner_(nullptr)
        , xFlip_(false)
        , weaponFlag_(false)
        , removeLFlag_(false)
        , posType_(0)
        , weaponTimer_(0)
    {}

    //�Q�b�^�[
    OBJ2D* owner() const { return owner_; }
    bool xFlip() const { return xFlip_; }
    bool weaponFlag() const { return weaponFlag_; }
    bool removeLFlag() const { return removeLFlag_; }
    int posType() const { return posType_; }
    int weaponTimer() const { return weaponTimer_; }

    //�Z�b�^�[
    void setOwner(OBJ2D* o) { if (!o) owner_ = o; }
    void setXFlip(bool b) { xFlip_ = b; }
    void setweaponFlag(bool f) { weaponFlag_ = f; }
    void setRemoveLFlag(bool f) { removeLFlag_ = f; }
    void setPosType(int t) { posType_ = t; }
    void setWeaponTimer(int t) { weaponTimer_ = t; }

    void countWeaponTimer() { weaponTimer_--; }
    // void copyOwnerXFlip();
};

//----------------------------------------
//            EffectComponent
//----------------------------------------
class EffectComponent : public Component
{
private:
    OBJ2D* owner_;      // ������
    int  effectTimer_;    // �G�t�F�N�g�̕`�掞��

public:
    EffectComponent()
        :owner_(nullptr)
        , effectTimer_(0)
    {}

    //�Q�b�^�[
    OBJ2D* owner() const { return owner_; }
    int effectTimer() const { return effectTimer_; }

    //�Z�b�^�[
    void setOwner(OBJ2D* o) { if (!o) owner_ = o; }
    void setEffectTimer(int t) { effectTimer_ = t; }

    void countEffectTimer() { --effectTimer_; }
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
    EffectComponent* effectComponent_;
public:
    // �����o�֐�
    OBJ2D(Renderer* renderer,
        Collider* collider,
        BG* bg,
        ActorComponent* actorComponent,
        WeaponComponent* weaponComponent,
        EffectComponent* effectComponent
    );

    ~OBJ2D();
    void move();    // �ړ�

    // �R���|�[�l���g�̃Q�b�^�[
    Transform* transform() const { return transform_; }
    Renderer* renderer() const { return renderer_; }
    Collider* collider() const { return collider_; }
    ActorComponent* actorComponent() const { return actorComponent_; }
    WeaponComponent* weaponComponent() const { return weaponComponent_; }
    EffectComponent* effectComponent() const { return effectComponent_; }

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
    void addEnemyState() { enemyState_++; }

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
    void draw(const VECTOR2&);          // �`��
    void draw2(const VECTOR2&);         // �`��
    void draw3(const VECTOR2&);         // �`��
    void draw4(const VECTOR2&);         // �`��
    void drawPlayer(const VECTOR2&);    // �`��
    void drawEffect(const VECTOR2&);    // �`��

    OBJ2D* add(OBJ2D* obj, Behavior* behavior, const VECTOR2& pos, int posType, VECTOR2 size);
    std::list<OBJ2D*>* getList() { return &objList_; }
};

//******************************************************************************

