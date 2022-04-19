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
    WeaponComponent* weaponComponent)
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

//--------------------------------------------------------------
//  �`��
//--------------------------------------------------------------
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
//  �߂�l�Ftrue  �A�j�����擪�ɖ߂�u��
//        :false ����ȊO
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

void Collider::draw(const VECTOR2& scrollPos) {
    // �H�炢BOX
    {
        const VECTOR2 pos{ hitBox_.left - scrollPos.x, hitBox_.top - scrollPos.y };
        const VECTOR2 size{ hitBox_.right - hitBox_.left, hitBox_.bottom - hitBox_.top };
        primitive::rect(pos, size, { 0, 0 }, 0, { 0, 0, 1, 0.5f });
    }
    // primitive::rect(
    //     VECTOR2(hitBox_.left, hitBox_.top) - scrollPos,
    //     { hitBox_.right - hitBox_.left, hitBox_.bottom - hitBox_.top },
    //     { 0, 0 }, 0.0f,
    //     { 0.0f, 0.0f, 1.0f, 0.5f }
    // );

    // �U��BOX
    {
        const VECTOR2 pos{ attackBox_.left - scrollPos.x, attackBox_.top - scrollPos.y };
        const VECTOR2 size{ attackBox_.right - attackBox_.left, attackBox_.bottom - attackBox_.top };
        primitive::rect(pos, size, { 0, 0 }, 0, { 1, 0, 0, 0.5f });
    }
    // primitive::rect(
    //     VECTOR2(attackBox_.left, attackBox_.top) - scrollPos,
    //     { attackBox_.right - attackBox_.left, attackBox_.bottom - attackBox_.top },
    //     { 0, 0}, 0.0f,
    //     { 1.0f, 0.0f, 0.0f, 0.5f }
    // );
};

// Component�̐e�iOBJ2D�j��Transform_��position_�̍��W�ɁA������rc�̒l�𑫂�������
// ��hitBox_�y�сAattackBox_�ɐݒ肷��B

void Collider::calcHitBox(const GameLib::fRECT& rc) {
    const VECTOR2* pos = &parent()->transform()->position();

    hitBox_ = {
        pos->x + rc.left,  pos->y + rc.top,
        pos->x + rc.right, pos->y + rc.bottom,
    };
}
void Collider::calcAttackBox(const GameLib::fRECT& rc) {
    const VECTOR2* pos = &parent()->transform()->position();

    attackBox_ = {
        pos->x + rc.left,   pos->y + rc.top,
        pos->x + rc.right,  pos->y + rc.bottom,
    };
}

bool Collider::hitcheck(Collider* coll) {
    // this->attackBox_��coll->hitBox_���������Ă��邩�ǂ���
    if (this->attackBox_.right < coll->hitBox_.left) return false;
    if (this->attackBox_.left > coll->hitBox_.right) return false;
    if (this->attackBox_.bottom < coll->hitBox_.top) return false;
    if (this->attackBox_.top > coll->hitBox_.bottom) return false;
    return true;
}

bool Collider::hitcheck(OBJ2D* obj) {
    return hitcheck(obj->collider());
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
OBJ2D* OBJ2DManager::add(OBJ2D* obj, Behavior* behavior, const VECTOR2& pos)
{
    obj->setBehavior(behavior);
    obj->transform()->setPosition(pos);
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
void OBJ2DManager::draw(const VECTOR2& scrollPos)
{
    constexpr float LIMIT = 256.0f; // ����ȏ�X�N���[������o�Ă�����̂͂Ƃ΂�
    int cnt = 0;
    for (auto& obj : objList_)
    {
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
    debug::setString("cnt:%d", cnt);
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
