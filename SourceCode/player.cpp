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
    // �ҋ@�i���ʁj
    AnimeData animePlayer_Idle[] = {
        { &sprPlayer_Idle0, 10 },
        { &sprPlayer_Idle1, 10 },
        { nullptr, -1}, // �I���t���O
    };

    // �����
    AnimeData animePlayer_Attack_U[] = {
        { &sprPlayer_Attack_U0, 10 },
        { &sprPlayer_Attack_U1, 10 },
        { &sprPlayer_Attack_U2, 10 },
        { nullptr, -1 },// �I���t���O
    };
    // �E����
    AnimeData animePlayer_Attack_R[] = {
        { &sprPlayer_Attack_R0, 10 },
        { &sprPlayer_Attack_R1, 10 },
        { &sprPlayer_Attack_R2, 10 },
        { nullptr, -1 },// �I���t���O
    };
    // ������
    AnimeData animePlayer_Attack_L[] = {
        { &sprPlayer_Attack_L0, 10 },
        { &sprPlayer_Attack_L1, 10 },
        { &sprPlayer_Attack_L2, 10 },
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
        //transform->addSpeedX(-getParam()->ACCEL_X);
        renderer->setAnimeData(getParam()->ANIME_LEFT);
        obj->actorComponent()->setDirection(obj->actorComponent()->LEFT);

        param_.HIT_BOX = { -290, -470, -240, -420 };

        break;
    case PAD_RIGHT: // �E������������Ă���ꍇ
        //transform->addSpeedX(getParam()->ACCEL_X);
        renderer->setAnimeData(getParam()->ANIME_RIGHT);
        obj->actorComponent()->setDirection(obj->actorComponent()->RIGHT);
        // param_.ATTACK_BOX = { 420, -700, 470, -650 };
        param_.HIT_BOX = { 360, -560, 410, -510 };

        break;
    default:        // �ǂ����������Ă��Ȃ������E����Ă���ꍇ
        // �v���C���[�摜�ݒ荶�E����
        if (obj->actorComponent()->direction_ == obj->actorComponent()->RIGHT)
            renderer->setAnimeData(getParam()->ANIME_IDLE);

        else if (obj->actorComponent()->direction_ == obj->actorComponent()->LEFT)
            renderer->setAnimeData(getParam()->ANIME_IDLE);

        //else if (obj->actorComponent()->DOWN)
        //    renderer->setAnimeData(getParam()->ANIME_DOWN);

        //else if (obj->actorComponent()->UP)
        //    renderer->setAnimeData(getParam()->ANIME_UP);

        // ����
        // if (transform->speed().x > 0)
        // {
        //     transform->addSpeedX(-getParam()->ACCEL_X / 2);
        //     if (transform->speed().x < 0) transform->setSpeedX(0.0f);
        // }
        // if (transform->speed().x < 0)
        // {
        //     transform->addSpeedX(getParam()->ACCEL_X / 2);
        //     if (transform->speed().x > 0) transform->setSpeedX(0.0f);
        // }
        // break;
    }
    debug::setString("speed:%f", obj->transform()->speed().x);
    ActorBehavior::moveX(obj);
}

//----------------------------------------//
//        IdlePlayerBehavior  �@          //
//----------------------------------------//

IdlePlayerBehavior::IdlePlayerBehavior()
{
    // �A�j���[�V����
    param_.ANIME_IDLE = animePlayer_Idle;
    // param_.ANIME_LEFT = animePlayer_Left;
    //param_.ANIME_LIDLE = animePlayer_LIdle;
    //param_.ANIME_RIDLE = animePlayer_RIdle;

    param_.SIZE = VECTOR2(300 / 2, 510 - 10);
    param_.SCALE = VECTOR2(1, 1);
    param_.HIT_BOX      = { -150 / 2, 0, 150 / 2, -150 };
    // param_.ATTACK_BOX   = { -150 / 2, 0, 150 / 2, -150 };
    // param_.HIT_BOX = { -150, -510, 150, 0 };
    // float left,top,right,bottom

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
    // transform->addSpeedY(getParam()->ACCEL_Y);

    ActorBehavior::moveY(obj);
}

// void IdlePlayerBehavior::moveX(OBJ2D* obj)
// {
//     Transform* transform = obj->transform();
// 
//     // ���x�ɉ����x��������
//     transform->addSpeedX(getParam()->ACCEL_X);
//     obj->renderer()->setAnimeData(getParam()->ANIME_RIGHT);
// 
//     debug::setString("aaaaaaaaaaaaaaaaaaaaa");
//     ActorBehavior::moveX(obj);
// }

void IdlePlayerBehavior::modechange(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    using namespace input;

    debug::setString("IdleMode");
    // if (Game::instance()->state() <= 1) return;

    // Enter�������ꂽ��
    if (TRG(0) & PAD_START)
    {
        OBJ2D* weapon = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                obj->bg(),
                nullptr,
                new WeaponComponent
            ),
            &weaponbehavior, VECTOR2(10, 10));
        weapon->weaponComponent()->setOwner(obj);
        obj->setBehavior(&attackPlayerBehavior);
    }
}

void IdlePlayerBehavior::playerAnimetion(OBJ2D* obj) 
{
    Renderer* renderer = obj->renderer();

    renderer->setAnimeData(getParam()->ANIME_IDLE);

    using namespace input;
    switch (STATE(0) & (PAD_LEFT | PAD_RIGHT | PAD_UP | PAD_DOWN))
    {
    case PAD_LEFT:  // ��������������Ă���ꍇ
        obj->actorComponent()->setDirection(obj->actorComponent()->LEFT);
        break;
    case PAD_RIGHT: // �E������������Ă���ꍇ
        obj->actorComponent()->setDirection(obj->actorComponent()->RIGHT);
        break;
    case PAD_DOWN:  // ��������������Ă���ꍇ
        obj->actorComponent()->setDirection(obj->actorComponent()->DOWN);
        break;
    case PAD_UP:    // �ゾ����������Ă���ꍇ
        obj->actorComponent()->setDirection(obj->actorComponent()->UP);
        break;
    }
    // if(obj->actorComponent()->direction() == obj->actorComponent()->UP)
    // if (obj->actorComponent()->direction() == obj->actorComponent()->DOWN)
    //     renderer->setAnimeData(getParam()->ANIME_DOWN);
    // 
    // if (obj->actorComponent()->direction() == obj->actorComponent()->LEFT)
    //     renderer->setAnimeData(getParam()->ANIME_LEFT);
    // 
    // if (obj->actorComponent()->direction() == obj->actorComponent()->RIGHT)
    //     renderer->setAnimeData(getParam()->ANIME_RIGHT);

    debug::setString("direction:%d", obj->actorComponent()->direction());
}

//----------------------------------------//
//        AttackPlayerBehavior  �@       //
//----------------------------------------//
AttackPlayerBehavior::AttackPlayerBehavior()
{
    // �A�j���[�V����
    param_.ANIME_ATTACK_R = animePlayer_Attack_R;
    param_.ANIME_ATTACK_L = animePlayer_Attack_L;
    param_.ANIME_ATTACK_U = animePlayer_Attack_U;

    param_.SIZE         = VECTOR2(300 / 2, 510 - 10);
    param_.SCALE        = VECTOR2(1, 1);
    param_.ATTACK_BOX   = { 0, 0, -300, -300 };
    param_.HIT_BOX      = { 0, 0, -300, -300 };

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
        if(obj->actorComponent()->direction_ == obj->actorComponent()->LEFT)
        {
            // �A�j���Z�b�g
            renderer->setAnimeData(getParam()->ANIME_ATTACK_L);
            param_.HIT_BOX   = { -150 / 2, 0, 150 / 2, -150 };
            // param_.ATTACK_BOX = { -150, -560, 0, -510 };
        }
        //�E
        else if(obj->actorComponent()->direction_ == obj->actorComponent()->RIGHT)
        {
            // �A�j���Z�b�g
            renderer->setAnimeData(getParam()->ANIME_ATTACK_R);
            param_.HIT_BOX    = { -150 / 2, 0, 150 / 2, -150 };
            // param_.ATTACK_BOX = { 360, -560, 410, -510 };
        }
        //��
        else if(obj->actorComponent()->direction_ == obj->actorComponent()->UP)
        {
            //�A�j���Z�b�g
            renderer->setAnimeData(getParam()->ANIME_ATTACK_U);
            param_.HIT_BOX      = { -150 / 2, 0, 150, -150 };
            // param_.ATTACK_BOX   = { 360,-560,410,-510 };;
        }

        //�A�j���[�V�����J�ڃ^�C�}�[���Z
        renderer->countaniTime();
    }
    if (renderer->animeTimer() > 40) {
        Game::instance()->setPlayerModeFlag(true);
    }

    debug::setString("AttackMode");
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