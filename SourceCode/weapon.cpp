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
        collider->setJudgeFlag(true);       // �����蔻����s��
        collider->setJudgeBoxFlag(true);    // �����蔻����s��

        collider->calcAttackBox(getParam()->ATTACK_BOX);
        // collider->calcHitBox(getParam()->HIT_BOX);
        weaponComponent->setPosType(Game::instance()->player()->actorComponent()->direction());

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
    param_.ERASER = &weaponEraser;

    param_.SCALE = { 1, 1 };
    param_.ATTACK_BOX = { -15, -15, 15, 15 };
    // param_.HIT_BOX    = { -15, -15, 15, 15 };
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
    if (src->weaponComponent()->posType() != dst->actorComponent()->posType()) return;

    // false�̏ꍇ���������Ȃ�
    if (dst->collider()->judgeBoxFlag() == false) return;
    // �ʏ�m�[�c�ƒ������m�[�c
    if (dst->behavior() != &enemy3Behavior) {
        // �R���{��ǉ�
        Game::instance()->addCombo();

        // �R���{�̃T�C�Y��ݒ�
        Game::instance()->setComboSize(VECTOR2(2, 2));

        // �X�R�A�̉��Z(2�{)
        Game::instance()->addScore(dst->actorComponent()->score() * 2);

        // �X�R�A�̕\�����Ԃ�߂�
        Game::instance()->setScoreTimer(Game::instance()->maxAppearTime());

        // �X�R�A���𑗂�
        Game::instance()->setAppearScore(dst->actorComponent()->score() * 2);

        // �m�[�c����𑗂�
        Game::instance()->setDecision(Game::instance()->PERFECT);   
        
        // �p�[�t�F�N�g�J�E���g�𑫂�
        Game::instance()->addPerfectNum();
    }
    // �A�Ńm�[�c
    else if (TRG(0) & PAD_START) {
        // �R���{2��ǉ�
        Game::instance()->addCombo2();

        // �X�R�A�̕\�����Ԃ�߂�
        Game::instance()->setCombo2Timer(Game::instance()->maxAppearTime());

        // �X�R�A�̉��Z
        Game::instance()->addScore(dst->actorComponent()->score());

        // �X�R�A�̕\�����Ԃ�߂�
        Game::instance()->setScoreTimer(Game::instance()->maxAppearTime());

        // �X�R�A���𑗂�
        Game::instance()->setAppearScore(dst->actorComponent()->score() * 2);

        // �m�[�c����𑗂�
        Game::instance()->setDecision(Game::instance()->PERFECT);

        // �p�[�t�F�N�g�J�E���g�𑫂�
        Game::instance()->addPerfectNum();

        if (dst->actorComponent()->deleteCombo2Flag()) {
            Game::instance()->deleteCombo2();
            dst->actorComponent()->setDeleteCombo2Flag(false);
        }
        debug::setString("deleteCombo2Flag:%d", dst->actorComponent()->deleteCombo2Flag());
    }
    // �G�����ł����Ԃɐݒ�(�������m�[�c�ƘA���m�[�c�ȊO)
    if (dst->behavior() == &enemy0Behavior ||
        dst->behavior() == &enemy1Behavior) {

        // �G�����ł����Ԃɐݒ�
        dst->addEnemyState();

        // Perfect�G�t�F�N�g�𐶐�
        setEffect(Game::instance()->obj2dManager(), Game::instance()->bg(), &notesEffect2Behavior, src->transform()->position());
    }

    // �W���b�W�t���O���Ȃ���(�A�Ńm�[�c�ȊO)
    if (dst->behavior() != &enemy3Behavior)
        dst->collider()->setJudgeBoxFlag(false);
}

// ����(��)�G�ɓ����������̏���(Great)
void WeaponBehavior::hit2(OBJ2D* src, OBJ2D* dst)
{
    if (src->weaponComponent()->posType() != dst->actorComponent()->posType()) return;

    // false�̏ꍇ���������Ȃ�
    if (dst->collider()->judgeBoxFlag() == false) return;
        
    // �R���{��ǉ�
    Game::instance()->addCombo();
    
    // �R���{�̃T�C�Y��ݒ�
    Game::instance()->setComboSize(VECTOR2(2, 2));

    // �X�R�A�̉��Z(1.5�{)
    Game::instance()->addScore(dst->actorComponent()->score() * 3 / 2);
    
    // �X�R�A�̕\�����Ԃ�߂�
    Game::instance()->setScoreTimer(Game::instance()->maxAppearTime());

    // �X�R�A���𑗂�
    Game::instance()->setAppearScore(dst->actorComponent()->score() * 3 / 2);

    // �m�[�c����𑗂�
    Game::instance()->setDecision(Game::instance()->GREAT);
    
    // �O���C�g�J�E���g�𑫂� 
    Game::instance()->addGreatNum();

    // �G�����ł����Ԃɐݒ�(�������m�[�c�ƘA���m�[�c�ȊO)
    if (dst->behavior() == &enemy0Behavior ||
        dst->behavior() == &enemy1Behavior) {
        // �G�����ł����Ԃɐݒ�
        dst->addEnemyState();

        // Great�G�t�F�N�g�𐶐�
        setEffect(Game::instance()->obj2dManager(), Game::instance()->bg(), &notesEffect1Behavior, src->transform()->position());
    }
    // �W���b�W�t���O���Ȃ���
    dst->collider()->setJudgeBoxFlag(false);
}

// ����(��)�G�ɓ����������̏���(Good)
void WeaponBehavior::hit3(OBJ2D* src, OBJ2D* dst)
{
    if (src->weaponComponent()->posType() != dst->actorComponent()->posType()) return;

    // false�̏ꍇ���������Ȃ�
    if (dst->collider()->judgeBoxFlag() == false) return;
    
    // �R���{��ǉ�
    Game::instance()->addCombo();
    
    // �R���{�̃T�C�Y��ݒ�
    Game::instance()->setComboSize(VECTOR2(2, 2));

    // �X�R�A�̉��Z(1.0�{)
    Game::instance()->addScore(dst->actorComponent()->score());
    
    // �X�R�A�̕\�����Ԃ�߂�
    Game::instance()->setScoreTimer(Game::instance()->maxAppearTime());

    // �X�R�A���𑗂�
    Game::instance()->setAppearScore(dst->actorComponent()->score());

    // �m�[�c����𑗂�
    Game::instance()->setDecision(Game::instance()->GOOD);
    
    // �O�b�h�J�E���g�𑫂�
    Game::instance()->addGoodNum();

    // �G�����ł����Ԃɐݒ�(�������m�[�c�ƘA���m�[�c�ȊO)
    if (dst->behavior() == &enemy0Behavior ||
        dst->behavior() == &enemy1Behavior) {
        // �G�����ł����Ԃɐݒ�
        dst->addEnemyState();

        // Good�G�t�F�N�g�𐶐�
        setEffect(Game::instance()->obj2dManager(), Game::instance()->bg(), &notesEffect0Behavior, src->transform()->position());
    }
    
    // �W���b�W�t���O���Ȃ���
    dst->collider()->setJudgeBoxFlag(false);
}

// ����(��)�G�ɓ����������̏���(�������m�[�c����)
void WeaponBehavior::hit4(OBJ2D* src, OBJ2D* dst)
{
    // ���������Ȃ��悤�Ƀt���O��ݒ肵����
    if (dst->collider()->judgeBoxFlag3() == true) {
        // �m�[�c�̐F��ς���
        dst->renderer()->setColor(VECTOR4(0.0f, 0.0f, 0.0f, 1));
    }

    // false�̏ꍇ���������Ȃ�
    if (dst->collider()->judgeBoxFlag() == true) return;  // �ŏ��ɍU������Ă��Ȃ�
    if (dst->collider()->judgeBoxFlag3() == true) return; // ����������ĂȂ�
    
    if (STATE(0) & PAD_START) // �������o���Ă���
    {
        dst->collider()->setJudgeBoxFlag2(true);
    }
    if(TRG_RELEASE(0) & PAD_START && dst->collider()->judgeBoxFlag4() == false) // ���������ĂȂ� ���� hit5,6,7�̓����蔻��ɓ����Ă��Ȃ��Ƃ�
    {
        // �R���{���Ȃ���
        Game::instance()->deleteCombo();

        // �R���{�̃T�C�Y��ݒ�
        Game::instance()->setComboSize(VECTOR2(2, 2));

        // �m�[�c����𑗂�
        Game::instance()->setDecision(Game::instance()->MISS);
        
        // �~�X�J�E���g 
        Game::instance()->addMissNum();

        // ���������Ȃ��悤�Ƀt���O��ݒ�
        dst->collider()->setJudgeBoxFlag3(true);
    }
}

// ����(��)�G�ɓ����������̏���(Perfect)
void WeaponBehavior::hit5(OBJ2D* src, OBJ2D* dst)
{
    // hit4�̒���������Ă��Ȃ����̏��������Ȃ��悤�Ƀt���O��ݒ�
    dst->collider()->setJudgeBoxFlag4(true);

    // false�̏ꍇ���������Ȃ�
    if (dst->collider()->judgeBoxFlag2() == false) return; // ����������ĂȂ�
    if (dst->collider()->judgeBoxFlag3() == true) return;  // ����������ĂȂ�
    
    // �����ꂽ�u�Ԃɔ���
    if (TRG_RELEASE(0) & PAD_START) {

        // �R���{��ǉ�
        Game::instance()->addCombo();

        // �R���{�̃T�C�Y��ݒ�
        Game::instance()->setComboSize(VECTOR2(2, 2));

        // �X�R�A�̉��Z(2�{)
        Game::instance()->addScore(dst->actorComponent()->score() * 2);

        // �X�R�A�̕\�����Ԃ�߂�
        Game::instance()->setScoreTimer(Game::instance()->maxAppearTime());

        // �X�R�A���𑗂�
        Game::instance()->setAppearScore(dst->actorComponent()->score() * 2);

        // �m�[�c����𑗂�
        Game::instance()->setDecision(Game::instance()->PERFECT);
        
        // �p�[�t�F�N�g�J�E���g�𑫂�
        Game::instance()->addPerfectNum();

        // �G������
        dst->remove();
    }
}

// ����(��)�G�ɓ����������̏���(Great)
void WeaponBehavior::hit6(OBJ2D* src, OBJ2D* dst)
{
    // hit4�̒���������Ă��Ȃ����̏��������Ȃ��悤�Ƀt���O��ݒ�
    dst->collider()->setJudgeBoxFlag4(true);

    // false�̏ꍇ���������Ȃ�
    if (dst->collider()->judgeBoxFlag2() == false) return;
    if (dst->collider()->judgeBoxFlag3() == true) return;

    // �����ꂽ�u�Ԃɔ���
    if (TRG_RELEASE(0) & PAD_START) {

        // �R���{��ǉ�
        Game::instance()->addCombo();

        // �R���{�̃T�C�Y��ݒ�
        Game::instance()->setComboSize(VECTOR2(2, 2));

        // �X�R�A�̉��Z(1.5�{)
        Game::instance()->addScore(dst->actorComponent()->score() * 3 / 2);

        // �X�R�A�̕\�����Ԃ�߂�
        Game::instance()->setScoreTimer(Game::instance()->maxAppearTime());

        // �X�R�A���𑗂�
        Game::instance()->setAppearScore(dst->actorComponent()->score() * 3 / 2);

        // �m�[�c����𑗂�
        Game::instance()->setDecision(Game::instance()->GREAT);

        // �O���C�g�J�E���g�𑫂�
        Game::instance()->addGreatNum();

        // �G������
        dst->remove();
    }
}

// ����(��)�G�ɓ����������̏���(Good)
void WeaponBehavior::hit7(OBJ2D* src, OBJ2D* dst)
{
    // hit4�̒���������Ă��Ȃ����̏��������Ȃ��悤�Ƀt���O��ݒ�
    dst->collider()->setJudgeBoxFlag4(true);

    // false�̏ꍇ���������Ȃ�
    if (dst->collider()->judgeBoxFlag2() == false) return;
    if (dst->collider()->judgeBoxFlag3() == true) return;

    // �����ꂽ�u�Ԃɔ���
    if (TRG_RELEASE(0) & PAD_START) {

        // �R���{��ǉ�
        Game::instance()->addCombo();

        // �R���{�̃T�C�Y��ݒ�
        Game::instance()->setComboSize(VECTOR2(2, 2));

        // �X�R�A�̉��Z(1.0�{)
        Game::instance()->addScore(dst->actorComponent()->score());

        // �X�R�A�̕\�����Ԃ�߂�
        Game::instance()->setScoreTimer(Game::instance()->maxAppearTime());

        // �X�R�A���𑗂�
        Game::instance()->setAppearScore(dst->actorComponent()->score());

        // �m�[�c����𑗂�
        Game::instance()->setDecision(Game::instance()->GOOD);

        // �O�b�h�J�E���g��i�߂�
        Game::instance()->addGoodNum();

        // �G������
        dst->remove();
    }
}

//----------------------------------------//
//         �@�@�@�@�@���� �@�@�@          //
//----------------------------------------//
void WeaponEraser::erase(OBJ2D* obj)
{
    // obj->remove();
}
