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
{   // �����̃f�[�^�͒����̂ŁAVisual Studio�̋@�\�ŕ�����悤��namespace�𕪂��Ă���

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

void BasePlayerBehavior::moveX(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();

    // ���E���͂̎��o��
    using namespace input;
    switch (STATE(0) & (PAD_LEFT | PAD_RIGHT))
    {
    case PAD_LEFT:  // ��������������Ă���ꍇ
        transform->addSpeedX(-getParam()->ACCEL_X);
        renderer->setAnimeData(getParam()->ANIME_LEFT);
        obj->actorComponent()->setXFlip(true);
        break;
    case PAD_RIGHT: // �E������������Ă���ꍇ
        transform->addSpeedX(getParam()->ACCEL_X);
        renderer->setAnimeData(getParam()->ANIME_RIGHT);
        obj->actorComponent()->setXFlip(false);
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

    debug::setString("player hasSword:%d", obj->actorComponent()->hasSword());
    
    ActorBehavior::moveX(obj);
}

bool BasePlayerBehavior::isAlive(OBJ2D* obj) {
    return true;    // �������Ă���i���j
}

//******************************************************************************
//
//      WalkPlayerBehavior
//
//******************************************************************************

WalkPlayerBehavior::WalkPlayerBehavior()
{
    // �A�j���[�V����
    param_.ANIME_UP     = animePlayer_Up;
    param_.ANIME_RIGHT  = animePlayer_Right;
    param_.ANIME_DOWN   = animePlayer_Down;
    param_.ANIME_LEFT   = animePlayer_Left;

    param_.SIZE = VECTOR2(48 / 2, 128 - 16);
    param_.SCALE = VECTOR2(1, 1);
    param_.HIT_BOX = { -20, -104, 20, -20 };

    // ���x�֘A�̃p�����[�^
    param_.ACCEL_X      = 1.0f;
    param_.ACCEL_Y      = 1.0f;
    param_.SPEED_X_MAX  = 8.0f;
    param_.SPEED_Y_MAX  = 16.0f;
    param_.JUMP_POWER_Y = -12.0f;
}

void WalkPlayerBehavior::moveY(OBJ2D* obj)
{
    Transform* transform = obj->transform();

    // ���x�ɉ����x��������
    transform->addSpeedY(getParam()->ACCEL_Y);

    ActorBehavior::moveY(obj);
}

void WalkPlayerBehavior::jump(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    ActorComponent* actorComp = obj->actorComponent();
    BG* bg = obj->bg();

    // �W�����v�`�F�b�N
    using namespace input;
    if (TRG(0) & PAD_TRG1)
    {
        if (actorComp->onGround() || bg->isInWater(obj))
        {
            actorComp->setJumpTimer(16);
        }
    }

    // �W�����v��
    if (actorComp->jumpTimer() > 0)
    {
        if (STATE(0) & PAD_TRG1)
        {   // PAD_TRG1��������Ă���ꍇ
            transform->setSpeedY(getParam()->JUMP_POWER_Y);
            actorComp->addJumpTimer(-1);
        }
        else
        {   // PAD_TRG1��������Ă��Ȃ��ꍇ
            actorComp->setJumpTimer(0);
        }
    }
}

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

void WalkPlayerBehavior::attack(OBJ2D* obj) {
    obj->actorComponent()->subAttackTimer(1);

    using namespace input;
    if (TRG(0) & PAD_TRG3 &&
        obj->actorComponent()->attackTimer() == 0)
    {
        const VECTOR2 pos = obj->transform()->position() + VECTOR2(0, -48);
        OBJ2D* shuriken = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                obj->bg(),
                nullptr,
                nullptr,
                new WeaponComponent),
            &shurikenBehavior, pos);
        shuriken->weaponComponent()->setOwner(obj);
        obj->actorComponent()->setAttackTimer(10);
    }

    if (TRG(0) & PAD_TRG2 &&
        obj->actorComponent()->hasSword() &&
        obj->actorComponent()->attackTimer() == 0)
    {
        const VECTOR2 pos = obj->transform()->position() + VECTOR2(0, -48);
        OBJ2D* sword = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                obj->bg(),
                nullptr,
                nullptr,
                new WeaponComponent),
            &swordBehavior, pos);
        sword->weaponComponent()->setOwner(obj);
        obj->actorComponent()->setAttackTimer(15);
    }
}

HashigoPlayerBehavior::HashigoPlayerBehavior()
{
    // �A�j���[�V����
    param_.ANIME_UP     = animePlayer_Up;
    param_.ANIME_RIGHT  = animePlayer_Up;
    param_.ANIME_DOWN   = animePlayer_Up;
    param_.ANIME_LEFT   = animePlayer_Up;

    // �T�C�Y
    param_.SIZE = VECTOR2(48.0f / 2, 128.0f - 16);
    param_.HIT_BOX = { -24, -112, 24, -12 };

    // ���x�֘A�̃p�����[�^
    param_.ACCEL_X      = 0.4f;
    param_.ACCEL_Y      = 0.4f;
    param_.SPEED_X_MAX  = 4.0f;
    param_.SPEED_Y_MAX  = 4.0f;
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

    ActorBehavior::moveY(obj);
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
