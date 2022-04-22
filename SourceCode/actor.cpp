#include "all.h"
using namespace GameLib;

void ActorBehavior::move(OBJ2D* obj)
{
    obj->renderer()->setAnimeData(nullptr);

    switch (obj->state())
    {
    case 0: {
        //////// �����ݒ� ////////
        // �A�j���̏����ݒ�
        obj->renderer()->setAnimeData(getParam()->ANIME_RIGHT);

        obj->transform()->setScale(getParam()->SCALE);
        const VECTOR2 size = {
            getParam()->SIZE.x * getParam()->SCALE.x,
            getParam()->SIZE.y * getParam()->SCALE.y,
        };
        obj->collider()->setSize( size );
        obj->collider()->setJudgeFlag(true);
        obj->collider()->setIsDrawHitRect(true);
        obj->actorComponent()->setHp(getParam()->HP);
        obj->nextState();//state_++
        break;
    }

    case 1:
        //////// �ʏ펞 ////////
        if (isAlive(obj) == false) break;
        moveY(obj);
        moveX(obj);
        jump(obj);
        hashigo(obj);
        areaCheck(obj);
        turn(obj);
        attack(obj);
        break;
    }

    obj->collider()->calcHitBox(getParam()->HIT_BOX);

    // �A�j���[�V�����X�V
    if (obj->renderer()->animeData())
        obj->renderer()->animeUpdate();
}

void ActorBehavior::moveY(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    BG* bg = obj->bg();
    ActorComponent* actorComp = obj->actorComponent();
    Collider* collider = obj->collider();

    // Y�����̍R�͂̌v�Z
    transform->addSpeedY(bg->calcResistance(obj, transform->speed().y));

    // �ő呬�x����
    transform->setSpeedY(clamp(transform->speed().y, -getParam()->SPEED_Y_MAX, getParam()->SPEED_Y_MAX));

    // �ʒu�X�V
    float oldY = transform->position().y;           // �ړ��O�̈ʒu��ێ�
    transform->addPositionY(transform->speed().y);
    float deltaY = transform->position().y - oldY;  // �ړ���̈ʒu����ړ��O�̈ʒu������

    actorComp->setOnGround(false);

    // �������̂����蔻��
    if (deltaY > 0)
    {
        if (bg->isFloor(transform->position().x, transform->position().y, collider->size().x))
        {
            // ���ɂ������Ă�����
            bg->mapHoseiDown(obj);    //  �������̕␳����
            actorComp->setOnGround(true);   // �n�ʃt���O
        }
    }

    // ������̂����蔻��
    if (deltaY < 0)
    {
        if (bg->isCeiling(transform->position().x, transform->position().y - collider->size().y, collider->size().x))
        {
            // �V��ɂ������Ă�����
            bg->mapHoseiUp(obj);
            actorComp->setJumpTimer(0);
        }
    }
}

void ActorBehavior::moveX(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    BG* bg = obj->bg();
    Collider* collider = obj->collider();

    // X�����̍R�͂̌v�Z
    transform->addSpeedX(bg->calcResistance(obj, transform->speed().x));

    // �ő呬�x�`�F�b�N
    if (transform->speed().x > getParam()->SPEED_X_MAX)
        transform->setSpeedX(getParam()->SPEED_X_MAX);
    if (transform->speed().x < -getParam()->SPEED_X_MAX)
        transform->setSpeedX(-getParam()->SPEED_X_MAX);

    // X�����ړ�
    float oldX = transform->position().x;
    transform->addPositionX(transform->speed().x);
    float deltaX = transform->position().x - oldX;

    //bool kabeFlag = false;  // �ǃt���O��false�ɂ��Ă����i�v���C���[�ł͎g�p���Ȃ��j

    // �E���������蔻��
    if (deltaX > 0)
    {
        if (bg->isWall(transform->position().x + collider->size().x,
            transform->position().y, collider->size().y))
        {
            bg->mapHoseiRight(obj);     // �E�����̕␳����
            obj->actorComponent()->setKabeFlag(true);
            //kabeFlag = true;                    // �ǃt���O��true�ɂ��Ă���
        }
    }

    // �����������蔻��
    if (deltaX < 0)
    {
        if (bg->isWall(transform->position().x - collider->size().x,
            transform->position().y, collider->size().y))
        {
            bg->mapHoseiLeft(obj);
            obj->actorComponent()->setKabeFlag(true);
            //kabeFlag = true;
        }
    }
}

void ActorBehavior::areaCheck(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Collider* collider = obj->collider();

    const float LIMIT = 512.0f; // ���E�̉��[���炱�̐��l�������������
    if (transform->position().y > BG::HEIGHT + LIMIT)
    {
        obj->remove();
        return;
    }

    if (transform->position().x < 0 + collider->size().x)
    {
        transform->setPositionX( collider->size().x );
        transform->setSpeedX( 0.0f );

        obj->actorComponent()->setKabeFlag(true);
    }
    if (transform->position().x > BG::WIDTH - collider->size().x)
    {
        transform->setPositionX(BG::WIDTH - collider->size().x);
        transform->setSpeedX( 0.0f );

        obj->actorComponent()->setKabeFlag(true);
    }
}
