#pragma once

//******************************************************************************
//
//
//      OBJ2Dクラス
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include <list>
#include "../GameLib/vector.h"
#include "../GameLib/obj2d_data.h"

// 前方宣言
class OBJ2D;

//==============================================================================

enum class OBJ_TYPE {
    PLAYER, // 0
    ENEMY,  // 1
    WEAPON, // 2
    EFFECT, // 3

    NONE,   // 4
};

// 移動アルゴリズムクラス（抽象クラス）
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

// 消去アルゴリズムクラス（抽象クラス）
class Eraser
{
public:
    virtual void erase(OBJ2D* obj) = 0;
};

//==============================================================================

//==============================================================================
//
//      OBJ2Dクラス
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
    VECTOR2 orgPos_;    // 最初に出現した位置を保持しておく
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

    // ゲッター
    const VECTOR2& position() const { return position_; }
    const VECTOR2& orgPos() const { return orgPos_; }
    const VECTOR2& scale() const { return scale_; }
    const VECTOR2& orgScale() const { return orgScale_; }
    const float rotation() const { return rotation_; }
    const VECTOR2& speed() const { return speed_; }

    // セッター
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

    // ゲッター
    void draw(const VECTOR2& scrollPos);
    void draw2(const VECTOR2& scrollPos);
    void draw3(const VECTOR2& scrollPos);
    bool animeUpdate();
    
    VECTOR4 color() { return color_; }
    int animeTimer() { return animetimer_; }

    GameLib::AnimeData* animeData() const { return animeData_; }

    // セッター
    void setData(GameLib::SpriteData* d) { data_ = d; }
    void setColor(const VECTOR4& c) { color_ = c; }
    void setAnime(const GameLib::Anime& a) { anime_ = a; }
    void setAnimeData(GameLib::AnimeData* adata) { animeData_ = adata; }
    void setAnimeTimer(int a) { animetimer_ = a; }

    //アニメーションタイマー加算
    void countAnimeTime() { ++animetimer_; }

    //アニメーションタイマーリセット
    void animeTimeReset() { animetimer_ = 0; }

    void addColorW(const float w) { color_.w += w; }
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

    //ゲッター
    const VECTOR2& size() const { return size_; }
    const VECTOR2& mergin() const { return mergin_; }
    bool judgeFlag() const { return judgeFlag_; }
    bool judgeBoxFlag() const { return judgeBoxFlag_; }
    bool judgeBoxFlag2() const { return judgeBoxFlag2_; }
    bool judgeBoxFlag3() const { return judgeBoxFlag3_; }
    bool judgeBoxFlag4() const { return judgeBoxFlag4_; }
    GameLib::fRECT hitbox() const { return hitBox_; }

    // セッター
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
    int  hp_;           // 体力
    int  maxHP_;        // 最大体力
    int  score_;        // スコア数
    bool moveFlag_;     // 餌が敵の感知範囲に入ったかどうかのフラグ
    bool xFlip_;        // X座標の向き
    bool hitFlag_;      // 餌が敵に当たった時かどうかのフラグ
    int  deadTimer_;    // 敵の消滅時間
    int  posType_;      // 敵の出現方向
    bool deleteCombo2Flag_; // コンボ2を消滅するフラグ
    int playerHitTimer_; // プレイヤーの点滅時間 
    
public:
    enum DIRECTON              // 向き
    {
        UP,                    // 上
        LEFT,                  // 左
        RIGHT,                 // 右
        DOWN,                  // 下
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
    // ゲッター
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

    // セッター
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

    // X座標の向きを反転
    void flip() { xFlip_ = !xFlip_; }

    // HPを減らす
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
    OBJ2D* owner_;      // 持ち主
    bool xFlip_;        // true左　false右向き
    bool weaponFlag_;   // 餌があるかどうかのフラグ
    bool removeLFlag_;
    int  posType_;      // 武器の出現方向
    int weaponTimer_;  
    bool weaponNotesHitFlag_; // 武器がノーツに当たった時のフラグ

public:
    WeaponComponent()
        :owner_(nullptr)
        , xFlip_(false)
        , weaponFlag_(false)
        , removeLFlag_(false)
        , posType_(0)
        , weaponTimer_(0)
        , weaponNotesHitFlag_(false)
    {}

    //ゲッター
    OBJ2D* owner() const { return owner_; }
    bool xFlip() const { return xFlip_; }
    bool weaponFlag() const { return weaponFlag_; }
    bool removeLFlag() const { return removeLFlag_; }
    int posType() const { return posType_; }
    int weaponTimer() const { return weaponTimer_; }
    bool weaponNotesHitFlag() const { return weaponNotesHitFlag_; }

    //セッター
    void setOwner(OBJ2D* o) { if (!o) owner_ = o; }
    void setXFlip(bool b) { xFlip_ = b; }
    void setweaponFlag(bool f) { weaponFlag_ = f; }
    void setRemoveLFlag(bool f) { removeLFlag_ = f; }
    void setPosType(int t) { posType_ = t; }
    void setWeaponTimer(int t) { weaponTimer_ = t; }
    void setWeaponNotesHitFlag(bool f) { weaponNotesHitFlag_ = f; }

    void countWeaponTimer() { weaponTimer_--; }
    // void copyOwnerXFlip();
};

//----------------------------------------
//            EffectComponent
//----------------------------------------
class EffectComponent : public Component
{
private:
    OBJ2D* owner_;      // 持ち主
    int  effectTimer_;    // エフェクトの描画時間

public:
    EffectComponent()
        :owner_(nullptr)
        , effectTimer_(0)
    {}

    //ゲッター
    OBJ2D* owner() const { return owner_; }
    int effectTimer() const { return effectTimer_; }

    //セッター
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
    // 基本的なメンバ
    int       state_    = 0; //状態
    int       timer_    = 0; //タイマー
    int       enemyState_;   // 敵の状態
    Behavior* behavior_ = nullptr;
    Eraser*   eraser_ = nullptr;

    BG* bg_ = nullptr;

    // 各コンポーネント
    Transform* transform_;
    Renderer* renderer_;
    Collider* collider_;
    ActorComponent* actorComponent_;
    WeaponComponent* weaponComponent_;
    EffectComponent* effectComponent_;
public:
    // メンバ関数
    OBJ2D(Renderer* renderer,
        Collider* collider,
        BG* bg,
        ActorComponent* actorComponent,
        WeaponComponent* weaponComponent,
        EffectComponent* effectComponent
    );

    ~OBJ2D();
    void move();    // 移動

    // コンポーネントのゲッター
    Transform* transform() const { return transform_; }
    Renderer* renderer() const { return renderer_; }
    Collider* collider() const { return collider_; }
    ActorComponent* actorComponent() const { return actorComponent_; }
    WeaponComponent* weaponComponent() const { return weaponComponent_; }
    EffectComponent* effectComponent() const { return effectComponent_; }

    // ゲッター
    int state() const { return state_; }
    int timer() const { return timer_; }
    int enemyState() const { return enemyState_; }
    Behavior* behavior() const { return behavior_; }
    BG* bg() const { return bg_; }

    // セッター
    void setState(int s) { state_ = s; }
    void setEnemyState(int s) { enemyState_ = s; }
    void setBehavior(Behavior* behavior) { behavior_ = behavior; }
    void setEraser(Eraser* eraser) { eraser_ = eraser; }

    // インクリメント
    void nextState() { state_++; }
    void addEnemyState() { enemyState_++; }

    void remove() { setBehavior(nullptr); }
};

//==============================================================================

// OBJ2DManagerクラス
class OBJ2DManager
{
private:
    VECTOR2* scrollPos_;
protected:
    std::list<OBJ2D*> objList_;
public:
    // デストラクタ
    ~OBJ2DManager();
    void setScrollPos(VECTOR2* s) { scrollPos_ = s; }

    void init();    // 初期化
    void update();  // 更新
    void draw(const VECTOR2&);          // 描画
    void draw2(const VECTOR2&);         // 描画
    void draw3(const VECTOR2&);         // 描画
    void draw4(const VECTOR2&);         // 描画
    void drawPlayer(const VECTOR2&);    // 描画
    void drawEffect(const VECTOR2&);    // 描画

    OBJ2D* add(OBJ2D* obj, Behavior* behavior, const VECTOR2& pos, int posType, VECTOR2 size);
    std::list<OBJ2D*>* getList() { return &objList_; }
};

//******************************************************************************

