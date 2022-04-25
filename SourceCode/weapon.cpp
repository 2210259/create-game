#include "all.h"

//using
using namespace GameLib;
using namespace input;

void BaseWeaponBehavior::move(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();
    Collider* collider = obj->collider();
    WeaponComponent* weaponComponent = obj->weaponComponent();
    BG* bg = obj->bg();

    switch (obj->state())
    {
    case 0:
        //////// �����ݒ� ////////
        transform->setScale(getParam()->SCALE);
        renderer->setData(getParam()->SPR_WEAPON);
        obj->setEraser(getParam()->ERASER);
        collider->setJudgeFlag(true);      // �����蔻����s��

        collider->calcAttackBox(getParam()->ATTACK_BOX);
        // collider->calcHitBox(getParam()->HIT_BOX);

        // ���E�̌����A���x��ݒ�i�v���C���[�ɂ�xFlip_�̐ݒ肪�K�v�j
        // weaponComponent->copyOwnerXFlip();   // ����̎������xFlip_�𕐊�ɐݒ肷��

        obj->nextState();//state++
        /*fallthrough*/

    case 1:
        //////// �ʏ펞 ////////
        collider->calcAttackBox(getParam()->ATTACK_BOX);
        // collider->calcHitBox(getParam()->HIT_BOX);
        update(obj);

        break;
    }
}

void BaseWeaponBehavior::update(OBJ2D* obj)
{
    Renderer* renderer = obj->renderer();
    Transform* transform = obj->transform();

    if (Game::instance()->playerModeFlag() == false) {
        obj->remove();
    }

    // renderer->countAnimeTime();

    // if (Game::instance()->state() <= 1) return;


    // debug::setString("speed%f", transform->speed().x);
    // debug::setString("speedY%f", transform->speed().y);
}

//----------------------------------------//
//         �@�@�R���X�g���N�^ �@          //
//----------------------------------------//
WeaponBehavior::WeaponBehavior()
{
    // param_.SPR_WEAPON = &sprWeapon;
    param_.ERASER = &weaponEraser;

    //TODO ����p�����[�^�ݒ�
    param_.SCALE = { 1, 1 };
    param_.ATTACK_BOX = { -25, -25, 25, 25 };
    param_.HIT_BOX    = { -25, -25, 25, 25 };
}

// void WeaponBehavior::calcAttackBox(OBJ2D* obj)
// {
//     obj->collider()->calcAttackBox(getParam()->ATTACK_BOX);
// }
// 
// void WeaponBehavior::calcHitBox(OBJ2D* obj)
// {
//     obj->collider()->calcHitBox(getParam()->HIT_BOX);
// }

// ����(��)�G�ɓ����������̏���(Perfect)
void WeaponBehavior::hit(OBJ2D* src, OBJ2D* dst)
{
    // �R���{��ǉ�
    Game::instance()->addCombo();

    // �G�Ƀ_���[�W��^����
    dst->actorComponent()->damage();
}

// ����(��)�G�ɓ����������̏���(Great)
void WeaponBehavior::hit2(OBJ2D* src, OBJ2D* dst)
{
    // �R���{��ǉ�
    Game::instance()->addCombo();
    
    // �G�Ƀ_���[�W��^����
    dst->actorComponent()->damage();
}

// ����(��)�G�ɓ����������̏���(Good)
void WeaponBehavior::hit3(OBJ2D* src, OBJ2D* dst)
{
    // �R���{��ǉ�
    Game::instance()->addCombo();
    
    // �G�Ƀ_���[�W��^����
    dst->actorComponent()->damage();
}
//----------------------------------------//
//         �@�@�@�@�@���� �@�@�@          //
//----------------------------------------//
void WeaponEraser::erase(OBJ2D* obj)
{
    // obj->remove();
}
