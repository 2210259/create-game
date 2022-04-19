//******************************************************************************
//
//
//      player.cpp
//
//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;


//----------------------------------------//
//        �v���C���[�ړ�����  �@          //
//----------------------------------------//


//----------------------------------------//
//        �v���C���[�A�j���[�V����        //
//----------------------------------------//

//------< �v���C���[�̃A�j���f�[�^ >----------------------------------------------
namespace
{
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

//----------------------------------------//
//        BasePlayerBehavior  �@          //
//----------------------------------------//

void BasePlayerBehavior::moveX(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();

    if (Game::instance()->state() <= 1) return;

    // ���E���͂̎��o��
    using namespace input;
    switch (STATE(0) & (PAD_LEFT | PAD_RIGHT))
    {
    case PAD_LEFT:  // ��������������Ă���ꍇ
        transform->addSpeedX(-getParam()->ACCEL_X);
        renderer->setAnimeData(getParam()->ANIME_LEFT);
        obj->actorComponent()->setFlip(true);


        param_.HIT_BOX = { -290, -470, -240, -420 };

        break;
    case PAD_RIGHT: // �E������������Ă���ꍇ
        transform->addSpeedX(getParam()->ACCEL_X);
        renderer->setAnimeData(getParam()->ANIME_RIGHT);
        obj->actorComponent()->setFlip(false);
        // param_.ATTACK_BOX = { 420, -700, 470, -650 };
        param_.HIT_BOX = { 360, -560, 410, -510 };

        break;
    default:        // �ǂ����������Ă��Ȃ������E����Ă���ꍇ

        // �v���C���[�摜�ݒ荶�E����
        if (obj->actorComponent()->xFlip())
            renderer->setAnimeData(getParam()->ANIME_LIDLE);
        else
            renderer->setAnimeData(getParam()->ANIME_RIDLE);

        // ����
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

    ActorBehavior::moveX(obj);
}

//----------------------------------------//
//        IdlePlayerBehavior  �@          //
//----------------------------------------//

IdlePlayerBehavior::IdlePlayerBehavior()
{
    // �A�j���[�V����
    param_.ANIME_RIGHT = animePlayer_Right;
    param_.ANIME_LEFT = animePlayer_Left;
    // param_.ANIME_RIDLE = animePlayer_RIdle;
    // param_.ANIME_LIDLE = animePlayer_LIdle;

    param_.SIZE = VECTOR2(300 / 2, 510 - 10);
    param_.SCALE = VECTOR2(1, 1);
    // param_.HIT_BOX      = { 420, -700, 470, -650 };
    // param_.ATTACK_BOX   = { 420, -700, 470, -650 };
    // param_.HIT_BOX = { -150, -510, 150, 0 };

    // ���x�֘A�̃p�����[�^
    param_.ACCEL_X = 1.0f;
    param_.ACCEL_Y = 1.0f;
    param_.SPEED_X_MAX = 8.0f;
    param_.SPEED_Y_MAX = 16.0f;
}

void IdlePlayerBehavior::moveY(OBJ2D* obj)
{
    Transform* transform = obj->transform();

    // ���x�ɉ����x��������
    transform->addSpeedY(getParam()->ACCEL_Y);

    ActorBehavior::moveY(obj);
}

void IdlePlayerBehavior::modechange(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    using namespace input;

    if (Game::instance()->state() <= 1) return;

    //�E�N���b�N�������ꂽ��
    if (TRG(0) & PAD_TRG2)
    {
        //�X�s�[�h��0��
        transform->setSpeedX(0.0f);

        OBJ2D* weapon = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                obj->bg(),
                nullptr,
                new WeaponComponent
            ),
            &weaponbehavior, VECTOR2(960, 540));
        weapon->weaponComponent()->setOwner(obj);
        obj->setBehavior(&attackPlayerBehavior);
    }
    //debug::setString("PPP%f", pos);
}

//----------------------------------------//
//        AttackPlayerBehavior  �@       //
//----------------------------------------//
AttackPlayerBehavior::AttackPlayerBehavior()
{
    // �A�j���[�V����
    // param_.ANIME_RIGHT = animePlayer_RFthrow;
    // param_.ANIME_LEFT  = animePlayer_LFthrow;

    // param_.ANIME_LHIT = animePlayer_LFroll;
    // param_.ANIME_RHIT = animePlayer_RFroll;

    param_.SIZE = VECTOR2(300 / 2, 510 - 10);
    param_.SCALE = VECTOR2(1, 1);
    // param_.ATTACK_BOX   = { 420, -700, 470, -650 };
    // param_.HIT_BOX      = { 420, -700, 470, -650 };

    // ���x�֘A�̃p�����[�^
    param_.ACCEL_X = 0.0f;
    param_.ACCEL_Y = 1.0f;
    param_.SPEED_X_MAX = 0.0f;
    param_.SPEED_Y_MAX = 16.0f;
}

void AttackPlayerBehavior::moveX(OBJ2D* obj)
{
    Renderer* renderer = obj->renderer();
    Transform* transform = obj->transform();

    // �U���A�j���[�V����
    if (renderer->animeTimer() < 40)
    {
        //��
        if (obj->actorComponent()->xFlip())
        {
            // �A�j���Z�b�g
            renderer->setAnimeData(getParam()->ANIME_LEFT);
            param_.ATTACK_BOX = { -410, -560, -360, -510 };
            param_.HIT_BOX = { -410, -560, -360, -510 };
        }
        //�E
        else
        {
            // �A�j���Z�b�g
            renderer->setAnimeData(getParam()->ANIME_RIGHT);
            param_.ATTACK_BOX = { 360, -560, 410, -510 };
            param_.HIT_BOX = { 360, -560, 410, -510 };
        }

        //�A�j���[�V�����J�ڃ^�C�}�[���Z
        renderer->countaniTime();
    }
}

void AttackPlayerBehavior::modechange(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();
    using namespace input;

    // �v���C���[�̃��[�h��ς���
    if (Game::instance()->playerModeFlag() == true)
    {
        //�A�j���[�V�����J�ڃ^�C�}�[���Z�b�g
        renderer->aniTimeReset();

        obj->setBehavior(&idlePlayerBehavior);
    }
}

// �����g��Ȃ�
// �v���C���[(��)�G�ɓ����������̏���
// void AttackPlayerBehavior::hit(OBJ2D* src, OBJ2D* dst) {
//     if (Game::instance()->esaFlag() == false && dst->enemyState() == 3)
//     {
//         dst->setEnemyState(4);
//         Game::instance()->setHit(true);
//     }
// }

void ErasePlayer::erase(OBJ2D* obj)
{
    obj->setBehavior(nullptr);
}