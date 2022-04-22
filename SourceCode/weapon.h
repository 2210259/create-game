#pragma once

#if 7
//******************************************************************************
// HACK:07 BaseWeaponBehavior�N���X�̍쐬
//------------------------------------------------------------------------------
/*
�m�F�j
    BaseWeaponBehavior�N���X���쐬���Ă��܂��B
*/
//******************************************************************************
#endif
class BaseWeaponBehavior : public Behavior
{
protected:
    struct Param {
        GameLib::SpriteData*    SPR_WEAPON;     // �X�v���C�g
        Eraser*                 ERASER;         // �C���C�T�[�i�폜�p�̃A���S���Y���j
        float                   SPEED_X;        // �������̑��x�i�藠���p�j
        float                   ROT_SPEED;      // ��]���x�i�藠���p�j
        int                     ATTACK_POWER;   // �U����
        VECTOR2                 SCALE;          // �X�P�[��
        GameLib::fRECT          ATTACK_BOX;     // �U���p������̈�
    } param_ = {};

protected:
    const Param* getParam() { return &param_; }
private:
    void move(OBJ2D* obj) override;
    virtual void update(OBJ2D* obj) = 0;        // �ʒu�ɑ��x�𑫂�
    virtual void calcAttackBox(OBJ2D* obj) = 0; // �U���p������̈�̌v�Z
    OBJ_TYPE getType() const override { return OBJ_TYPE::WEAPON; }
    OBJ_TYPE attackType() const override { return OBJ_TYPE::ENEMY; }
};

//----------------------------------------------------------------------
//  ShurikenBehavior
//----------------------------------------------------------------------
#if 9
//******************************************************************************
// HACK:09 ShurikenBehavior�̍쐬
//------------------------------------------------------------------------------
/*
�m�F�j
    ShurikenBehavior�N���X���쐬���Ă��܂��B
    �ǂ�Ȋ֐����I�[�o�[���C�h����K�v�����邩�m�F���Ă������ƁB
*/
//******************************************************************************
#endif
class ShurikenBehavior : public BaseWeaponBehavior
{
public:
    ShurikenBehavior();
private:
    void update(OBJ2D* obj) override;
    void calcAttackBox(OBJ2D* obj) override;
    void hit(OBJ2D* src, OBJ2D* dst) override;
};
EXTERN ShurikenBehavior shurikenBehavior;

//----------------------------------------------------------------------
//  SwordBehavior
//----------------------------------------------------------------------
class SwordBehavior : public BaseWeaponBehavior
{
public:
    SwordBehavior();
private:
    void update(OBJ2D* obj) override;
    void calcAttackBox(OBJ2D* obj) override;
    void hit(OBJ2D* src, OBJ2D* dst) override;
};
EXTERN SwordBehavior swordBehavior;

#if 10
//******************************************************************************
// HACK:10 ShurikenEraser�N���X�̍쐬
//------------------------------------------------------------------------------
/*
�m�F�j
    ������ShurikenBehavior�̃R���X�g���N�^�ŕK�v�ɂȂ�A�藠����Eraser��p�ӂ��Ă��܂��B
    Eraser�́A�I�u�W�F�N�g���폜�����p�̃A���S���Y���ł��B
*/
//******************************************************************************
#endif
class ShurikenEraser : public Eraser
{
private:
    void erase(OBJ2D* obj) override;
};
EXTERN ShurikenEraser shurikenEraser;

class SwordEraser : public Eraser
{
private:
    void erase(OBJ2D* obj) override;
};
EXTERN SwordEraser swordEraser;