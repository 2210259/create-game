#include "all.h"

#if 8
//******************************************************************************
// HACK:08 �����move�֐�
//------------------------------------------------------------------------------
/*
�m�F�j
    BaseWeaponBehavior��move�֐��ł��B
    OBJ2D�N���X��setEraser���ǉ�����Ă��܂��B
*/
//******************************************************************************
#endif
void BaseWeaponBehavior::move(OBJ2D* obj)
{
    switch (obj->state())
    {
    case 0:
        //////// �����ݒ� ////////
        obj->renderer()->setData(getParam()->SPR_WEAPON);
        obj->transform()->setScale(getParam()->SCALE);
        obj->setEraser(getParam()->ERASER);
        obj->collider()->setJudgeFlag(true);      // �����蔻����s��
        obj->collider()->setIsDrawHitRect(true);  // �����蔻��̗̈��`�悷��i�f�o�b�O�p�j

        // ���E�̌����A���x��ݒ�i�v���C���[�ɂ�xFlip_�̐ݒ肪�K�v�j
        obj->weaponComponent()->copyOwnerXFlip();   // ����̎������xFlip_�𕐊�ɐݒ肷��
        obj->transform()->setSpeedX(
            obj->weaponComponent()->xFlip()
            ? -getParam()->SPEED_X : getParam()->SPEED_X);
        obj->transform()->setSpeedY(0.0f);        // �O�̂���

        obj->nextState();//state++
        /*fallthrough*/

    case 1:
        //////// �ʏ펞 ////////
        update(obj);    // ����̈ʒu�X�V
        calcAttackBox(obj);
        break;
    }
}

#if 12
//******************************************************************************
// HACK:12 ShurikenBehavior�̃R���X�g���N�^
//------------------------------------------------------------------------------
/*
�m�F�j
    �藠���̃p�����[�^�͈ȉ��̂悤�ɂȂ��Ă��܂��B
*/
//******************************************************************************
#endif
ShurikenBehavior::ShurikenBehavior()
{
    param_.SPR_WEAPON   = &sprWeapon_Shuriken;
    param_.ERASER       = &shurikenEraser;
    param_.SPEED_X      = 20.0f;
    param_.ROT_SPEED    = ToRadian(24);
    param_.ATTACK_POWER = 1;
    param_.SCALE        = { 0.5f, 0.5f };
    param_.ATTACK_BOX   = { -24, -24, 24, 24 };
}

#if 3
//******************************************************************************
// TODO:03 �藠����update�֐�
//------------------------------------------------------------------------------
/*
�菇�j
    �� �藠���̈ʒu�ɑ��x�𑫂��B
    �� �藠���ɉ�]��������B�i�E�ɐi�ލۂ͎��v���A���͔����v���Ɂj

����j
    �ʒu�ɑ��x�𑫂����߂ɁATransform::update�֐����p�ӂ���Ă��܂��B

    �藠�����ǂ���������Ă��邩�́AWeaponComponent::xFlip_�ɕێ�����Ă��܂��B
    �I�u�W�F�N�g����]�����邽�߂ɁATransform::rotate�֐����p�ӂ���Ă��܂��B
    �P�t���[���łǂꂾ����]���邩�́A�p�����[�^��ROT_SPEED�ɒl�������Ă��܂��B
*/
//******************************************************************************
#endif
void ShurikenBehavior::update(OBJ2D* obj)
{
    //TODO_03
    // �藠���̈ʒu�ɑ��x�𑫂�
    obj->transform()->update();

    // �藠���ɉ�]��������i�E�ɐi�ލۂ͎��v���A���͔����v���Ɂj
    obj->transform()->rotate(
        obj->weaponComponent()->xFlip()
        ? -getParam()->ROT_SPEED : getParam()->ROT_SPEED);
}

#if 4
//******************************************************************************
// TODO:04 �藠���̍U���̈�̌v�Z
//------------------------------------------------------------------------------
/*
�菇�j
    Collider�N���X��calcAttackBox���\�b�h�ōU���̈���v�Z���܂��傤�B
*/
//******************************************************************************
#endif
void ShurikenBehavior::calcAttackBox(OBJ2D* obj)
{
    //TODO_04
    // �U������̌v�Z
    obj->collider()->calcAttackBox(getParam()->ATTACK_BOX);
};

#if 5
//******************************************************************************
// TODO:05 �藠����hit�֐�
//------------------------------------------------------------------------------
/*
�菇�j
    �� �藠�������������G��HP����藠���̍U���͕��������B
      �idst��actorComponent��subHp���\�b�h���g�p����j

    �� �藠�����폜����B

����j
    �����attackType��OBJ_TYPE::ENEMY�Ȃ̂ŁA���L�̈���src�͎藠���Adst�ɂ͎藠����
    ���������G�̃|�C���^�ɂȂ��Ă��܂��B
    ActorComponent::subHp���\�b�h���ł́Ahp_���}�C�i�X�ɂȂ�Ȃ��悤�ȏ����������Ă��܂��B
    �藠���̍U���͂́AgetParam()->ATTACK_POWER�ł��B
*/
//******************************************************************************
#endif
void ShurikenBehavior::hit(OBJ2D* src, OBJ2D* dst)
{
    //TODO_05
    // �藠�������������G��HP����藠���̍U���͕�������
    dst->actorComponent()->subHp(getParam()->ATTACK_POWER);

    // �藠�����폜����
    src->remove();
}

#if 11
//******************************************************************************
// HACK:11 erase�֐��̍쐬
//------------------------------------------------------------------------------
/*
�m�F�j
    erase�֐��ł́A�I�u�W�F�N�g���ǂ����������ō폜����邩���L�q���܂��B
*/
//******************************************************************************
#endif
void ShurikenEraser::erase(OBJ2D* obj)
{
    const VECTOR2* scrollPos = &obj->bg()->getScrollPos();
    const VECTOR2* size = &obj->collider()->size();
    const VECTOR2* pos = &obj->transform()->position();

    const float leftLimit = scrollPos->x - size->x;
    const float rightLimit = scrollPos->x + BG::CLIENT_W + size->x;
    const float topLimit = scrollPos->y - size->y;
    const float bottomLimit = scrollPos->y + BG::CLIENT_H + size->y;

    if (pos->x < leftLimit ||
        pos->x > rightLimit ||
        pos->y < topLimit ||
        pos->y > bottomLimit)
    {
        obj->remove();
    }
}

SwordBehavior::SwordBehavior()
{
    param_.SPR_WEAPON   = &sprWeapon_Sword;
    param_.ERASER       = &swordEraser;
    param_.ATTACK_POWER = 2;
    param_.SCALE        = { 1, 1 };
    param_.ATTACK_BOX   = { -32, -32, 32, 32 };
}

void SwordBehavior::update(OBJ2D* obj)
{
    bool xFlip = obj->weaponComponent()->xFlip();
    float ang = 0.0f;
    if (!xFlip) {
        // �E�������Ă���
        ang = -30 + obj->timer() * 15;
        if (ang > 105) ang = 105;
    }
    else {
        // ���������Ă���
        ang = 30 - obj->timer() * 15;
        if (ang < -105) ang = -105;
    }
    obj->transform()->setRotation(ToRadian(ang));// ���W�A���ɂ���

    obj->transform()->setPosition(
        obj->weaponComponent()->owner()->transform()->position()
        + VECTOR2(0, -48));
}

void SwordBehavior::calcAttackBox(OBJ2D* obj)
{
    float angle = obj->transform()->rotation();
    VECTOR2 pos = { sinf(angle) * 96, -cosf(angle) * 96 };
    obj->collider()->calcAttackBox(
        {
            pos.x + getParam()->ATTACK_BOX.left,
            pos.y + getParam()->ATTACK_BOX.top,
            pos.x + getParam()->ATTACK_BOX.right,
            pos.y + getParam()->ATTACK_BOX.bottom,
        }
    );
}

void SwordBehavior::hit(OBJ2D* src, OBJ2D* dst)
{
    // �������������G��HP���猕�̍U���͕�������
    dst->actorComponent()->subHp(getParam()->ATTACK_POWER);
    src->collider()->setJudgeFlag(false);
}

void SwordEraser::erase(OBJ2D* obj)
{
    if (obj->timer() > 15)
    {
        obj->remove();
    }
}
