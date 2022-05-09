//******************************************************************************
//
//
//      OBJ2D�N���X
//
//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
#include "all.h"

using namespace GameLib;

//--------------------------------------------------------------
//  �R���X�g���N�^
//--------------------------------------------------------------
OBJ2D::OBJ2D(Renderer* renderer,
    Collider* collider,
    BG* bg,
    ActorComponent* actorComponent,
    WeaponComponent* weaponComponent
    )
    : renderer_(renderer)
    , collider_(collider)
    , bg_(bg)
    , actorComponent_(actorComponent)
    , weaponComponent_(weaponComponent)
{
    transform_ = new Transform;
    if (transform_)         transform_->setParent(this);
    if (renderer_)          renderer_->setParent(this);
    if (collider_)          collider_->setParent(this);
    if (actorComponent_)    actorComponent_->setParent(this);
    if (weaponComponent_)   weaponComponent_->setParent(this);
}

//--------------------------------------------------------------
//  �f�X�g���N�^
//--------------------------------------------------------------
OBJ2D::~OBJ2D()
{
    safe_delete(transform_);
    safe_delete(renderer_);
    safe_delete(collider_);
    safe_delete(actorComponent_);
    safe_delete(weaponComponent_);
}

//--------------------------------------------------------------
//  �ړ�
//--------------------------------------------------------------
void OBJ2D::move()
{
    if (behavior_) behavior_->move(this);
    if (eraser_) eraser_->erase(this);

    timer_++;
}

//----------------------------------------//
//            Renderer                    //
//----------------------------------------//
void Renderer::draw(const VECTOR2& scrollPos)
{
    Transform* transform = parent()->transform();
    if (data_)
    {
        data_->draw(transform->position() - scrollPos,
            transform->scale(), transform->rotation(), color_);  // data��draw���\�b�h�ŃX�v���C�g��`�悷��
    }
}

//--------------------------------------------------------------
//  �A�j���[�V�����X�V
//--------------------------------------------------------------
bool Renderer::animeUpdate()
{
    if (animeData_ == nullptr)
    {
        assert(!"animeUpdate�֐���AnimeData��nullptr");
        return false;
    }

    if (anime_.pPrev != animeData_)         // �A�j���f�[�^���؂�ւ�����Ƃ�
    {
        anime_.pPrev = animeData_;
        anime_.patNum = 0;	                // �擪����Đ�
        anime_.frame = 0;
    }

    animeData_ += anime_.patNum;
    data_ = animeData_->data;               // ���݂̃p�^�[���ԍ��ɊY������摜��ݒ�

    anime_.frame++;
    if (anime_.frame >= animeData_->frame)  // �ݒ�t���[�����\��������
    {
        anime_.frame = 0;
        anime_.patNum++;                    // ���̃p�^�[����
        if ((animeData_ + 1)->frame < 0)    // �I���R�[�h�̂Ƃ�
        {
            anime_.patNum = 0;              // �擪�֖߂�
            return true;
        }
    }

    return false;
}

// TODO:�����蔻��̕`��
//----------------------------------------//
//             Collider                   //
//----------------------------------------//
void Collider::draw(const VECTOR2& scrollPos) 
{
    VECTOR2 size, pos;
    VECTOR4 color;

    // hitBox
    size = {
        hitBox_.right - hitBox_.left,
        hitBox_.bottom - hitBox_.top 
    };
    if(size.x * size.y != 0.0f)
    {
        pos = VECTOR2(hitBox_.left, hitBox_.top) - scrollPos;
        color = { 0, 0, 1, 0.6f };
        // primitive::rect(pos, size, { 0,0 }, 0, color);
    }

    // hitBox2
    size = {
        hitBox2_.right - hitBox2_.left,
        hitBox2_.bottom - hitBox2_.top
    };
    if (size.x * size.y != 0.0f)
    {
        pos = VECTOR2(hitBox2_.left, hitBox2_.top) - scrollPos;

        color = { 0, 0, 0.7f, 0.5f };
        // primitive::rect(pos, size, { 0,0 }, 0, color);
    }

    // hitBox3
    size = {
        hitBox3_.right - hitBox3_.left,
        hitBox3_.bottom - hitBox3_.top
    };
    if (size.x * size.y != 0.0f)
    {
        pos = VECTOR2(hitBox3_.left, hitBox3_.top) - scrollPos;

        color = { 0, 0, 0.4f, 0.3f };
        // primitive::rect(pos, size, { 0,0 }, 0, color);
    }

    // hitBox4
    size = {
        hitBox4_.right - hitBox4_.left,
        hitBox4_.bottom - hitBox4_.top
    };
    if (size.x * size.y != 0.0f)
    {
        pos = VECTOR2(hitBox4_.left, hitBox4_.top) - scrollPos;

        color = { 1.0f, 0, 0, 0.6f };
        // primitive::rect(pos, size, { 0,0 }, 0, color);
    }

    // hitBox5
    size = {
        hitBox5_.right - hitBox5_.left,
        hitBox5_.bottom - hitBox5_.top
    };
    if (size.x * size.y != 0.0f)
    {
        pos = VECTOR2(hitBox5_.left, hitBox5_.top) - scrollPos;
        color = { 0, 0, 1, 0.6f };
        // primitive::rect(pos, size, { 0,0 }, 0, color);
    }

    // hitBox6
    size = {
        hitBox6_.right - hitBox6_.left,
        hitBox6_.bottom - hitBox6_.top
    };
    if (size.x * size.y != 0.0f)
    {
        pos = VECTOR2(hitBox6_.left, hitBox6_.top) - scrollPos;

        color = { 0, 0, 0.7f, 0.5f };
        // primitive::rect(pos, size, { 0,0 }, 0, color);
    }

    // hitBox7
    size = {
        hitBox7_.right - hitBox7_.left,
        hitBox7_.bottom - hitBox7_.top
    };
    if (size.x * size.y != 0.0f)
    {
        pos = VECTOR2(hitBox7_.left, hitBox7_.top) - scrollPos;

        color = { 0, 0, 0.4f, 0.3f };
        // primitive::rect(pos, size, { 0,0 }, 0, color);
    }

    // attackBox
    size = {
        attackBox_.right - attackBox_.left,
        attackBox_.bottom - attackBox_.top
    };
    if (size.x * size.y != 0.0f)
    {
        pos = VECTOR2(attackBox_.left, attackBox_.top) - scrollPos;
        color = { 1, 0, 0, 0.5f };
        primitive::rect(pos, size, { 0,0 }, 0, color);
    }
};

//----------------------------------------//
//             �H�炢�̈�v�Z             //
//----------------------------------------//
void Collider::calcHitBox(const GameLib::fRECT& rc) {
    const VECTOR2* pos = &parent()->transform()->position();

    hitBox_ = {
        pos->x + rc.left,  pos->y + rc.top,
        pos->x + rc.right, pos->y + rc.bottom,
    };
}

void Collider::calcHitBox2(const GameLib::fRECT& rc) {
    const VECTOR2* pos = &parent()->transform()->position();

    hitBox2_ = {
        pos->x + rc.left,  pos->y + rc.top,
        pos->x + rc.right, pos->y + rc.bottom,
    };
}

void Collider::calcHitBox3(const GameLib::fRECT& rc) {
    const VECTOR2* pos = &parent()->transform()->position();

    hitBox3_ = {
        pos->x + rc.left,  pos->y + rc.top,
        pos->x + rc.right, pos->y + rc.bottom,
    };
}

void Collider::calcHitBox4(const GameLib::fRECT& rc) {
    const VECTOR2* pos = &parent()->transform()->position();

    hitBox4_ = {
        pos->x + rc.left,  pos->y + rc.top,
        pos->x + rc.right, pos->y + rc.bottom,
    };
}

void Collider::calcHitBox5(const GameLib::fRECT& rc) {
    const VECTOR2* pos = &parent()->transform()->position();

    hitBox5_ = {
        pos->x + rc.left,  pos->y + rc.top,
        pos->x + rc.right, pos->y + rc.bottom,
    };
}

void Collider::calcHitBox6(const GameLib::fRECT& rc) {
    const VECTOR2* pos = &parent()->transform()->position();

    hitBox6_ = {
        pos->x + rc.left,  pos->y + rc.top,
        pos->x + rc.right, pos->y + rc.bottom,
    };
}

void Collider::calcHitBox7(const GameLib::fRECT& rc) {
    const VECTOR2* pos = &parent()->transform()->position();

    hitBox7_ = {
        pos->x + rc.left,  pos->y + rc.top,
        pos->x + rc.right, pos->y + rc.bottom,
    };
}

//----------------------------------------//
//             �U���͈͌v�Z               //
//----------------------------------------//
void Collider::calcAttackBox(const GameLib::fRECT& rc) {
    const VECTOR2* pos = &parent()->transform()->position();

    attackBox_ = {
        pos->x + rc.left,   pos->y + rc.top,
        pos->x + rc.right,  pos->y + rc.bottom,
    };
}

//----------------------------------------//
//             �������Ă��邩             //
//----------------------------------------//
bool Collider::hitCheck(Collider* coll) {
    if (attackBox_.right < coll->hitBox_.left) return false;
    if (attackBox_.left > coll->hitBox_.right) return false;
    if (attackBox_.bottom < coll->hitBox_.top) return false;
    if (attackBox_.top > coll->hitBox_.bottom) return false;
    return true;
}

bool Collider::hitCheck2(Collider* coll) {
    if (attackBox_.right < coll->hitBox2_.left) return false;
    if (attackBox_.left > coll->hitBox2_.right) return false;
    if (attackBox_.bottom < coll->hitBox2_.top) return false;
    if (attackBox_.top > coll->hitBox2_.bottom) return false;
    return true;
}

bool Collider::hitCheck3(Collider* coll) {
    if (attackBox_.right < coll->hitBox3_.left) return false;
    if (attackBox_.left > coll->hitBox3_.right) return false;
    if (attackBox_.bottom < coll->hitBox3_.top) return false;
    if (attackBox_.top > coll->hitBox3_.bottom) return false;
    return true;
}

bool Collider::hitCheck4(Collider* coll) {
    if (attackBox_.right < coll->hitBox4_.left) return false;
    if (attackBox_.left > coll->hitBox4_.right) return false;
    if (attackBox_.bottom < coll->hitBox4_.top) return false;
    if (attackBox_.top > coll->hitBox4_.bottom) return false;
    return true;
}

bool Collider::hitCheck5(Collider* coll) {
    if (attackBox_.right < coll->hitBox5_.left) return false;
    if (attackBox_.left > coll->hitBox5_.right) return false;
    if (attackBox_.bottom < coll->hitBox5_.top) return false;
    if (attackBox_.top > coll->hitBox5_.bottom) return false;
    return true;
}

bool Collider::hitCheck6(Collider* coll) {
    if (attackBox_.right < coll->hitBox6_.left) return false;
    if (attackBox_.left > coll->hitBox6_.right) return false;
    if (attackBox_.bottom < coll->hitBox6_.top) return false;
    if (attackBox_.top > coll->hitBox6_.bottom) return false;
    return true;
}

bool Collider::hitCheck7(Collider* coll) {
    if (attackBox_.right < coll->hitBox7_.left) return false;
    if (attackBox_.left > coll->hitBox7_.right) return false;
    if (attackBox_.bottom < coll->hitBox7_.top) return false;
    if (attackBox_.top > coll->hitBox7_.bottom) return false;
    return true;
}


bool Collider::hitCheck(OBJ2D* obj) {
    return hitCheck(obj->collider());
}

bool Collider::hitCheck2(OBJ2D* obj)
{
    return hitCheck2(obj->collider());
}

bool Collider::hitCheck3(OBJ2D* obj)
{
    return hitCheck3(obj->collider());
}

bool Collider::hitCheck4(OBJ2D* obj)
{
    return hitCheck4(obj->collider());
}

bool Collider::hitCheck5(OBJ2D* obj)
{
    return hitCheck5(obj->collider());
}

bool Collider::hitCheck6(OBJ2D* obj)
{
    return hitCheck6(obj->collider());
}

bool Collider::hitCheck7(OBJ2D* obj)
{
    return hitCheck7(obj->collider());
}

//******************************************************************************
//
//
//      OBJ2DManager�N���X
//
//
//******************************************************************************

//--------------------------------------------------------------
//  ������
//--------------------------------------------------------------
void OBJ2DManager::init()
{
    //���X�g��OBJ2D��S�ăN���A����
    objList_.clear();
}

//--------------------------------------------------------------
//  ���X�g�֒ǉ�
//--------------------------------------------------------------
OBJ2D* OBJ2DManager::add(OBJ2D* obj, Behavior* behavior, const VECTOR2& pos, int posType, VECTOR2 scale)
{
    obj->setBehavior(behavior);
    obj->transform()->setPosition(pos);
    
     //�m�[�c�̏o���ʒu�̐ݒ�
    if (posType >= 0){
        obj->actorComponent()->setPosType(posType);
    }

    //������(��)�m�[�c�̎�
    if (scale.y > 0 && scale.y != 1.0f ) {
        //�����͌Œ�Ȃ̂�1������
        scale.x = 1.0f;

        //�傫���̐ݒ�
        obj->transform()->setOrgScale(scale);
    }
    //������(��)�m�[�c�̎�
    else if (scale.x > 0 && scale.x != 1.0f) {
        //�c���͌Œ�Ȃ̂�1������
        scale.y = 1.0f;
        //�傫���̐ݒ�
        obj->transform()->setOrgScale(scale);
    }
    else {
        scale.x = 1.0f;
        scale.y = 1.0f;
        obj->transform()->setOrgScale(scale);
    }

    objList_.emplace_back(obj);
    return obj;
}

//--------------------------------------------------------------
//  �X�V
//--------------------------------------------------------------
void OBJ2DManager::update()
{
    // �ړ�
    for (auto& obj : objList_)   // objList�̑S�Ă̗v�f�����[�v���Ait�Ƃ������O�Ŋe�v�f�ɃA�N�Z�X
    {
        obj->move();              // it��move���\�b�h���Ă�
    }

    // ��m�[�h�̍폜
    auto iter = objList_.begin();
    while (iter != objList_.end())
    {
        if ((*iter)->behavior())
        {
            iter++;
        }
        else
        {
            safe_delete(*iter);
            iter = objList_.erase(iter);
        }
    }
}

//--------------------------------------------------------------
//  �`��
//--------------------------------------------------------------
// �ʏ�m�[�c�݂̂�`�悷��
void OBJ2DManager::draw(const VECTOR2& scrollPos)
{
    constexpr float LIMIT = 512.0f; // ����ȏ�X�N���[������o�Ă�����̂͂Ƃ΂�
    int cnt = 0;
    for (auto& obj : objList_)
    {
        if (obj->behavior() != &enemy0Behavior && obj->behavior() != &enemy1Behavior) continue;
        const VECTOR2 pos = obj->transform()->position() - scrollPos;
        if (pos.x < -LIMIT || pos.x > window::getWidth() + LIMIT ||
            pos.y < -LIMIT || pos.y > window::getHeight() + LIMIT)
        {
            cnt++;
            continue;
        }
        obj->renderer()->draw(scrollPos);
        obj->collider()->draw(scrollPos);
    }
}

// �������m�[�c(��)�ƘA�Ńm�[�c(��)�݂̂�`�悷��
void OBJ2DManager::draw2(const VECTOR2& scrollPos)
{
    constexpr float LIMIT = 512.0f; // ����ȏ�X�N���[������o�Ă�����̂͂Ƃ΂�
    int cnt = 0;
    for (auto& obj : objList_)
    {
        if (obj->behavior() != &enemy2Behavior && obj->behavior() != &enemy3Behavior) continue;
        if (obj->actorComponent()->posType() != 0) continue;

        const VECTOR2 pos = obj->transform()->position() - scrollPos;
        if (pos.x < -LIMIT || pos.x > window::getWidth() + LIMIT ||
            pos.y < -LIMIT || pos.y > window::getHeight() + LIMIT)
        {
            cnt++;
            continue;
        }
        obj->renderer()->draw(scrollPos);
        obj->collider()->draw(scrollPos);
    }
}

// �������m�[�c(��)�ƘA�Ńm�[�c(��)�݂̂�`�悷��
void OBJ2DManager::draw3(const VECTOR2& scrollPos)
{
    constexpr float LIMIT = 512.0f; // ����ȏ�X�N���[������o�Ă�����̂͂Ƃ΂�
    int cnt = 0;
    for (auto& obj : objList_)
    {
        if (obj->behavior() != &enemy2Behavior && obj->behavior() != &enemy3Behavior) continue;
        if (obj->actorComponent()->posType() != 1) continue;

        const VECTOR2 pos = obj->transform()->position() - scrollPos;
        if (pos.x < -LIMIT || pos.x > window::getWidth() + LIMIT ||
            pos.y < -LIMIT || pos.y > window::getHeight() + LIMIT)
        {
            cnt++;
            continue;
        }
        obj->renderer()->draw(scrollPos);
        obj->collider()->draw(scrollPos);
    }
}

// �������m�[�c(�E)�ƘA�Ńm�[�c(�E)�݂̂�`�悷��
void OBJ2DManager::draw4(const VECTOR2& scrollPos)
{
    constexpr float LIMIT = 512.0f; // ����ȏ�X�N���[������o�Ă�����̂͂Ƃ΂�
    int cnt = 0;
    for (auto& obj : objList_)
    {
        if (obj->behavior() != &enemy2Behavior && obj->behavior() != &enemy3Behavior) continue;
        if (obj->actorComponent()->posType() != 2) continue;

        const VECTOR2 pos = obj->transform()->position() - scrollPos;
        if (pos.x < -LIMIT || pos.x > window::getWidth() + LIMIT ||
            pos.y < -LIMIT || pos.y > window::getHeight() + LIMIT)
        {
            cnt++;
            continue;
        }
        obj->renderer()->draw(scrollPos);
        obj->collider()->draw(scrollPos);
    }
}

// �v���C���[�����`�悷��
void OBJ2DManager::drawPlayer(const VECTOR2& scrollPos)
{
    constexpr float LIMIT = 512.0f; // ����ȏ�X�N���[������o�Ă�����̂͂Ƃ΂�
    int cnt = 0;
    for (auto& obj : objList_)
    {
        if (obj->behavior() != &idlePlayerBehavior && obj->behavior() != &attackPlayerBehavior && obj->behavior() != &weaponBehavior) continue;
        const VECTOR2 pos = obj->transform()->position() - scrollPos;
        if (pos.x < -LIMIT || pos.x > window::getWidth() + LIMIT ||
            pos.y < -LIMIT || pos.y > window::getHeight() + LIMIT)
        {
            cnt++;
            continue;
        }
        obj->renderer()->draw(scrollPos);
        obj->collider()->draw(scrollPos);
    }
}
//--------------------------------------------------------------
//  �f�X�g���N�^
//--------------------------------------------------------------
OBJ2DManager::~OBJ2DManager()
{
    for (auto& obj : objList_)
    {
        safe_delete(obj);
    }

    //���X�g��OBJ2D��S�ăN���A����
    objList_.clear();
}
