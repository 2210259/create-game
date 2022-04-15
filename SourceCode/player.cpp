//******************************************************************************
//
//
//      �v���C���[�N���X
//
//
//******************************************************************************

//------< �C���N���[�h >---------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//******************************************************************************
//
//      �v���C���[�ړ�����
//
//******************************************************************************

//------< �v���C���[�̃A�j���f�[�^ >----------------------------------------------
namespace
{   

    //------< �v���C���[�̃A�j���f�[�^ >------------------------------------------
    //�����
    AnimeData animePlayer_Up[] = {
        { &sprPlayer_Up0, 10 },
        { &sprPlayer_Up1, 10 },
        { &sprPlayer_Up2, 10 },
        { &sprPlayer_Up1, 10 },
        { nullptr, -1 },// �I���t���O
    };
    //�E����
    AnimeData animePlayer_Right[] = {
        { &sprPlayer_Right0, 10 },
        { &sprPlayer_Right1, 10 },
        { &sprPlayer_Right2, 10 },
        { &sprPlayer_Right1, 10 },
        { nullptr, -1 },// �I���t���O
    };
    //������
    AnimeData animePlayer_Down[] = {
        { &sprPlayer_Down0, 10 },
        { &sprPlayer_Down1, 10 },
        { &sprPlayer_Down2, 10 },
        { &sprPlayer_Down1, 10 },
        { nullptr, -1 },// �I���t���O
    };
    //������
    AnimeData animePlayer_Left[] = {
        { &sprPlayer_Left0, 10 },
        { &sprPlayer_Left1, 10 },
        { &sprPlayer_Left2, 10 },
        { &sprPlayer_Left1, 10 },
        { nullptr, -1 },// �I���t���O
    };
}

//******************************************************************************
//
//      BasePlayerBehavior
//
//******************************************************************************

void BasePlayerBehavior::move(OBJ2D* obj)
{
    Renderer* renderer = obj->renderer();
    Collider* collider = obj->collider();

    renderer->setAnimeData(nullptr);
    switch (obj->state())
    {
    case 0:
        //////// �����ݒ� ////////
        // �A�j���̏����ݒ�
        renderer->setAnimeData(getParam()->ANIME_RIGHT);
        collider->setSize(getParam()->SIZE);
        collider->setJudgeFlag(true);
        collider->setIsDrawHitRect(true);

        obj->nextState();//state_++
        break;

    case 1:
        //////// �ʏ펞 ////////
        moveY(obj);
        moveX(obj);
        // jump(obj);
        hashigo(obj);
        areaCheck(obj);
        break;
    }

    debug::setString("player hasSword:%d", obj->actorComponent()->hasSword());

    collider->calcHitBox(getParam()->HIT_BOX);

    // �A�j���[�V�����X�V
    if (renderer->animeData())
        renderer->animeUpdate();
}
void BasePlayerBehavior::moveY(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();
    BG* bg = obj->bg();
    ActorComponent* actorComp = obj->actorComponent();
    Collider* collider = obj->collider();

    // �㉺���͂̎��o��
    using namespace input;
    switch (STATE(0) & (PAD_UP | PAD_DOWN))
    {
    case PAD_UP:  // �ゾ����������Ă���ꍇ
        transform->addSpeedY(-getParam()->ACCEL_Y);
        renderer->setAnimeData(getParam()->ANIME_UP);
        break;
    case PAD_DOWN: // ��������������Ă���ꍇ
        transform->addSpeedY(getParam()->ACCEL_Y);
        renderer->setAnimeData(getParam()->ANIME_DOWN);
        break;
    default:        // �ǂ����������Ă��Ȃ������E����Ă���ꍇ
        if (transform->speed().y > 0)
        {
            transform->addSpeedY(-getParam()->ACCEL_Y / 2);
            if (transform->speed().y < 0) transform->setSpeedX(0.0f);
        }
        if (transform->speed().y < 0)
        {
            transform->addSpeedY(getParam()->ACCEL_Y / 2);
            if (transform->speed().y > 0) transform->setSpeedY(0.0f);
        }
        break;
    }

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

    float angle = 0;
    angle += ToRadian(3);
}
void BasePlayerBehavior::moveX(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();
    BG* bg = obj->bg();
    Collider* collider = obj->collider();

    // ���E���͂̎��o��
    using namespace input;
    switch (STATE(0) & (PAD_LEFT | PAD_RIGHT))
    {
    case PAD_LEFT:  // ��������������Ă���ꍇ
        transform->addSpeedX(-getParam()->ACCEL_X);
        renderer->setAnimeData(getParam()->ANIME_LEFT);
        break;
    case PAD_RIGHT: // �E������������Ă���ꍇ
        transform->addSpeedX(getParam()->ACCEL_X);
        renderer->setAnimeData(getParam()->ANIME_RIGHT);
        break;
    default:        // �ǂ����������Ă��Ȃ������E����Ă���ꍇ
        if (transform->speed().x > 0)
        {
            transform->addSpeedX(-getParam()->ACCEL_X / 2);
            if (transform->speed().x < 0) transform->setSpeedX(0.0f);
        }
        if (transform->speed().x < 0)
        {
            transform->addSpeedX(getParam()->ACCEL_X / 2);
            if (transform->speed().x > 0) transform->setSpeedX(0.0f);
        }
        break;
    }

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

    bool kabeFlag = false;  // �ǃt���O��false�ɂ��Ă����i�v���C���[�ł͎g�p���Ȃ��j

    // �E���������蔻��
    if (deltaX > 0)
    {
        if (bg->isWall(transform->position().x + collider->size().x,
            transform->position().y, collider->size().y))
        {
            bg->mapHoseiRight(obj);     // �E�����̕␳����
            kabeFlag = true;                    // �ǃt���O��true�ɂ��Ă���
        }
    }

    // �����������蔻��
    if (deltaX < 0)
    {
        if (bg->isWall(transform->position().x - collider->size().x,
            transform->position().y, collider->size().y))
        {
            bg->mapHoseiLeft(obj);
            kabeFlag = true;
        }
    }
}
void BasePlayerBehavior::areaCheck(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Collider* collider = obj->collider();

    if (transform->position().x < 0 + collider->size().x)
    {
        transform->setPositionX(collider->size().x);
        transform->setSpeedX(0.0f);
    }
    if (transform->position().x > BG::WIDTH - collider->size().x)
    {
        transform->setPositionX(BG::WIDTH - collider->size().x);
        transform->setSpeedX(0.0f);
    }
}

//******************************************************************************
//
//      WalkPlayerBehavior
//
//******************************************************************************

WalkPlayerBehavior::WalkPlayerBehavior()
{
    // �A�j���[�V����
    param_.ANIME_UP = animePlayer_Up;
    param_.ANIME_RIGHT = animePlayer_Right;
    param_.ANIME_DOWN = animePlayer_Down;
    param_.ANIME_LEFT = animePlayer_Left;

    param_.SIZE = VECTOR2(48 / 2, 64 - 16);
    param_.HIT_BOX = { -20, -40, 20, -10 };

    // ���x�֘A�̃p�����[�^
    param_.ACCEL_X = 1.0f;
    param_.ACCEL_Y = 1.0f;
    param_.SPEED_X_MAX = 4.0f;
    param_.SPEED_Y_MAX = 4.0f;
    param_.JUMP_POWER_Y = -12.0f;
}

void WalkPlayerBehavior::moveY(OBJ2D* obj)
{
    Transform* transform = obj->transform();

    // ���x�ɉ����x��������
    // transform->addSpeedY(getParam()->ACCEL_Y);

    BasePlayerBehavior::moveY(obj);
}

//void WalkPlayerBehavior::jump(OBJ2D* obj)
//{
//    Transform* transform = obj->transform();
//    ActorComponent* actorComp = obj->actorComponent();
//    BG* bg = obj->bg();
//
//     �W�����v�`�F�b�N
//    using namespace input;
//    if (TRG(0) & PAD_TRG1)
//    {
//        if (actorComp->onGround() || bg->isInWater(obj))
//        {
//            actorComp->setJumpTimer(16);
//        }
//    }
//
//     �W�����v��
//    if (actorComp->jumpTimer() > 0)
//    {
//        if (STATE(0) & PAD_TRG1)
//        {   // PAD_TRG1��������Ă���ꍇ
//            transform->setSpeedY(getParam()->JUMP_POWER_Y);
//            actorComp->addJumpTimer(-1);
//        }
//        else
//        {   // PAD_TRG1��������Ă��Ȃ��ꍇ
//            actorComp->setJumpTimer(0);
//        }
//    }
//}

void WalkPlayerBehavior::hashigo(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Collider* collider = obj->collider();
    BG* bg = obj->bg();
    ActorComponent* actorComp = obj->actorComponent();

    if (!bg) assert(!"�v���C���[��bgManager_��nullptr");
    const BG::TR_ATTR attrCenter =    // �̂̒��S�����̒n�`�̑���
        bg->getTerrainAttr(VECTOR2(transform->position().x, transform->position().y - collider->size().y / 2));
    const BG::TR_ATTR attrBottom =    // �����̕����̒n�`�̑���
        bg->getTerrainAttr(transform->position());
    const BG::TR_ATTR attrBelow =     // �����̂P�h�b�g���̒n�`�̑���
        bg->getTerrainAttr(VECTOR2(transform->position().x, transform->position().y + 1.0f));

    using namespace input;
    switch (STATE(0) & (PAD_UP | PAD_DOWN | PAD_LEFT | PAD_RIGHT))
    {
    case PAD_UP:
        if (attrBottom == BG::TR_ATTR::HASHIGO ||
            attrCenter == BG::TR_ATTR::HASHIGO)
        {
            obj->setBehavior(&hashigoPlayerBehavior);
        }
        break;

    case PAD_DOWN:
        if (attrBottom == BG::TR_ATTR::HASHIGO ||
            attrCenter == BG::TR_ATTR::HASHIGO)
        {
            obj->setBehavior(&hashigoPlayerBehavior);
        }

        // �͂����~��͂��߁i�v���C���[�����鍂���Ɂu�͂����v�������A���ɂ���P�[�X�j
        if (attrBelow == BG::TR_ATTR::HASHIGO)
        {
            obj->setBehavior(&hashigoPlayerBehavior);
        }
        break;
    }

    // ��������͂����i�����̒n�`�������͂����ŁA���������Ȃ����A�͂����̎��ɗ����鎖�ւ̑΍�j
    if (actorComp->onGround() &&                             // �n��ɂ���
        attrBottom == BG::TR_ATTR::HASHIGO &&   // �����̒n�`�������͂���
        (attrBelow == BG::TR_ATTR::TR_NONE || attrBelow == BG::TR_ATTR::HASHIGO))   // �����̂P�h�b�g�����󔒂��͂���
    {
        obj->setBehavior(&hashigoPlayerBehavior);
    }
}

HashigoPlayerBehavior::HashigoPlayerBehavior()
{
    // �A�j���[�V����
    param_.ANIME_UP = animePlayer_Up;
    param_.ANIME_RIGHT = animePlayer_Up;
    param_.ANIME_DOWN = animePlayer_Up;
    param_.ANIME_LEFT = animePlayer_Up;

    // �T�C�Y
    param_.SIZE = VECTOR2(48.0f / 2, 128.0f - 16);
    param_.HIT_BOX = { -24, -112, 24, -12 };

    // ���x�֘A�̃p�����[�^
    param_.ACCEL_X = 0.4f;
    param_.ACCEL_Y = 0.4f;
    param_.SPEED_X_MAX = 4.0f;
    param_.SPEED_Y_MAX = 4.0f;
}

void HashigoPlayerBehavior::moveY(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();

    // �͂������~��
    using namespace input;
    switch (STATE(0) & (PAD_UP | PAD_DOWN))
    {
    case PAD_UP:    // �ゾ����������Ă���
        transform->addSpeedY(-getParam()->ACCEL_Y);
        renderer->setAnimeData(getParam()->ANIME_UP);
        break;

    case PAD_DOWN:  // ��������������Ă���
        transform->addSpeedY(getParam()->ACCEL_Y);
        renderer->setAnimeData(getParam()->ANIME_UP);
        break;

    default:        // ����������Ă��Ȃ������E���Ă���
        if (transform->speed().y > 0)
        {
            transform->addSpeedY(-getParam()->ACCEL_Y / 2);
            transform->setSpeedY(std::max(transform->speed().y, 0.0f));
        }
        if (transform->speed().y < 0)
        {
            transform->addSpeedY(getParam()->ACCEL_Y / 2);
            transform->setSpeedY(std::min(transform->speed().y, 0.0f));
        }
        break;
    }

    BasePlayerBehavior::moveY(obj);
}

void HashigoPlayerBehavior::hashigo(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Collider* collider = obj->collider();
    BG* bg = obj->bg();

    const BG::TR_ATTR attrCenter =    // �̂̒��S�����̒n�`�̑���
        bg->getTerrainAttr(VECTOR2(transform->position().x, transform->position().y - collider->size().y / 2));
    const BG::TR_ATTR attrBottom =    // �����̕����̒n�`�̑���
        bg->getTerrainAttr(transform->position());

    // �͂������[�h���A�ʏ탂�[�h�ւ̈ڍs����
    if (attrBottom != BG::TR_ATTR::HASHIGO &&       // �����̒n�`���͂����łȂ�
        attrCenter != BG::TR_ATTR::HASHIGO)         // �̂̒��S�̒n�`���͂����łȂ�
    {
        obj->setBehavior(&walkPlayerBehavior);      // �ʏ펞�ɖ߂�
        transform->setSpeedY(0.0f);                 // ���R�����J�n�̏�ԂɂȂ�
    }
}

//--------------------------------------------------------------
//  ����
//--------------------------------------------------------------
void ErasePlayer::erase(OBJ2D* obj)
{
    obj->setBehavior(nullptr);
}
