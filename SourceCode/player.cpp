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

    // ��U��
    AnimeData animePlayer_Attack_U[] = {
        { &sprPlayer_Attack_U0, 5 },
        { &sprPlayer_Attack_U1, 5 },
        { &sprPlayer_Attack_U2, 5 },
        { nullptr, -1 },// �I���t���O
    };
    // �E�U��
    AnimeData animePlayer_Attack_R[] = {
        { &sprPlayer_Attack_R0, 5 },
        { &sprPlayer_Attack_R1, 5 },
        { &sprPlayer_Attack_R2, 5 },
        { nullptr, -1 },// �I���t���O
    };
    // ���U��
    AnimeData animePlayer_Attack_L[] = {
        { &sprPlayer_Attack_L0, 5 },
        { &sprPlayer_Attack_L1, 5 },
        { &sprPlayer_Attack_L2, 5 },
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

    // ���E���͂̎��o��
    // using namespace input;
    // switch (STATE(0) & (PAD_LEFT | PAD_RIGHT | PAD_UP))
    // {
    // case PAD_LEFT:  // ��������������Ă���ꍇ
    //     obj->actorComponent()->setDirection(obj->actorComponent()->LEFT);
    //     //transform->addSpeedX(-getParam()->ACCEL_X);
    //     renderer->setAnimeData(getParam()->ANIME_LEFT);
    // 
    //     // param_.HIT_BOX = { -290, -470, -240, -420 };
    // 
    //     break;
    // case PAD_RIGHT: // �E������������Ă���ꍇ
    //     obj->actorComponent()->setDirection(obj->actorComponent()->RIGHT);
    //     //transform->addSpeedX(getParam()->ACCEL_X);
    //     // renderer->setAnimeData(getParam()->ANIME_RIGHT);
    //     // param_.ATTACK_BOX = { 420, -700, 470, -650 };
    //     // param_.HIT_BOX = { 360, -560, 410, -510 };
    // 
    //     break;
    // default:        // �ǂ����������Ă��Ȃ������E����Ă���ꍇ
    //     // �v���C���[�摜�ݒ荶�E����
    //     if (obj->actorComponent()->direction_ == obj->actorComponent()->RIGHT)
    //         renderer->setAnimeData(getParam()->ANIME_IDLE);
    // 
    //     else if (obj->actorComponent()->direction_ == obj->actorComponent()->LEFT)
    //         renderer->setAnimeData(getParam()->ANIME_IDLE);
    // 
    //     //else if (obj->actorComponent()->DOWN)
    //     //    renderer->setAnimeData(getParam()->ANIME_DOWN);
    // 
    //     //else if (obj->actorComponent()->UP)
    //     //    renderer->setAnimeData(getParam()->ANIME_UP);
    // 
    //     // ����
    //     // if (transform->speed().x > 0)
    //     // {
    //     //     transform->addSpeedX(-getParam()->ACCEL_X / 2);
    //     //     if (transform->speed().x < 0) transform->setSpeedX(0.0f);
    //     // }
    //     // if (transform->speed().x < 0)
    //     // {
    //     //     transform->addSpeedX(getParam()->ACCEL_X / 2);
    //     //     if (transform->speed().x > 0) transform->setSpeedX(0.0f);
    //     // }
    //     // break;
    // }
    // ActorBehavior::moveX(obj);
}

//----------------------------------------//
//        IdlePlayerBehavior  �@          //
//----------------------------------------//

IdlePlayerBehavior::IdlePlayerBehavior()
{
    // �A�j���[�V����
    param_.ANIME_IDLE = animePlayer_Idle;

    param_.SIZE = VECTOR2(150, 150);
    param_.SCALE = VECTOR2(1, 1);
    param_.MARGIN = 50.0f;
    param_.HIT_BOX = { -param_.SIZE.x / 2 + param_.MARGIN, -param_.SIZE.y + param_.MARGIN,
        param_.SIZE.x / 2 - param_.MARGIN, 0 - param_.MARGIN }; // �����
    // param_.ATTACK_BOX   = { -150 / 2, 0, 150 / 2, -150 };
    // float left,top,right,bottom

    // HP
    param_.HP = 4;
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
    if (TRG(0) & PAD_START) {
        // ���[�h�t���O��ς���
        Game::instance()->setPlayerModeFlag(true);
    }

    // Attack���[�h�ɕς���
    if(Game::instance()->playerModeFlag() == true)
    {
        // �������������Ă���
        if (obj->actorComponent()->direction_ == obj->actorComponent()->LEFT)
        {
            //�����蔻��̈ʒu��ݒ�
            attackPosition = { 480, 540 };
        }

        // �����E�������Ă�����
        if(obj->actorComponent()->direction_ == obj->actorComponent()->RIGHT)
        {
            //�����蔻��̈ʒu��ݒ�
            attackPosition = { 800 , 540 };
        }

        //������������Ă�����
        if(obj->actorComponent()->direction_ == obj->actorComponent()->UP)
        {
            //�����蔻��̈ʒu��ݒ�
            attackPosition = { 640 , 540 };
        }
        
        // ������Z�b�g
        OBJ2D* weapon = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                obj->bg(),
                nullptr,
                new WeaponComponent
            ),
            &weaponbehavior, attackPosition, -1);
        weapon->weaponComponent()->setOwner(obj);
        
        // ���[�h��ς���
        obj->setBehavior(&attackPlayerBehavior);
    }
    debug::setString("HP:%d", Game::instance()->player()->actorComponent()->hp());
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

    param_.SIZE     = VECTOR2(150, 150);
    param_.SCALE    = VECTOR2(1, 1);
    param_.MARGIN   = 50.0f;

    // �����蔻��
    param_.HIT_BOX = { -param_.SIZE.x / 2 + param_.MARGIN, -param_.SIZE.y + param_.MARGIN,
        param_.SIZE.x / 2 - param_.MARGIN, 0 - param_.MARGIN }; // �����
    
    // HP
    param_.HP = 5;
}

// void AttackPlayerBehavior::moveX(OBJ2D* obj)
// {
//     Renderer* renderer = obj->renderer();
//     Transform* transform = obj->transform();
// 
//     // �U���A�j���[�V����
//     if (renderer->animeTimer() < 30)
//     {
//         //��
//         if(obj->actorComponent()->direction_ == obj->actorComponent()->LEFT)
//         {
//             // �A�j���Z�b�g
//             renderer->setAnimeData(getParam()->ANIME_ATTACK_L);
//             param_.HIT_BOX   = { -150 / 2, 0, 150 / 2, -150 };
//             // param_.ATTACK_BOX = { -150, -560, 0, -510 };
//             debug::setString("LEFT");
//         }
//         //�E
//         else if(obj->actorComponent()->direction_ == obj->actorComponent()->RIGHT)
//         {
//             // �A�j���Z�b�g
//             renderer->setAnimeData(getParam()->ANIME_ATTACK_R);
//             param_.HIT_BOX    = { -150 / 2, 0, 150 / 2, -150 };
//             // param_.ATTACK_BOX = { 360, -560, 410, -510 };
//             debug::setString("RIGHT");
//         }
//         //��
//         else if(obj->actorComponent()->direction_ == obj->actorComponent()->UP)
//         {
//             //�A�j���Z�b�g
//             renderer->setAnimeData(getParam()->ANIME_ATTACK_U);
//             param_.HIT_BOX      = { -150 / 2, 0, 150, -150 };
//             // param_.ATTACK_BOX   = { 360,-560,410,-510 };
//             debug::setString("UP");
//         }
// 
//         //�A�j���[�V�����J�ڃ^�C�}�[���Z
//         renderer->countAnimeTime();
//     }
//     if (renderer->animeTimer() > 30) {
//         Game::instance()->setPlayerModeFlag(true);
//     }
// 
//     debug::setString("AttackMode");
//     debug::setString("SetPlayerModeFlag:%d",Game::instance()->playerModeFlag());
// }

void AttackPlayerBehavior::playerAnimetion(OBJ2D* obj)
{
    Renderer* renderer = obj->renderer();
    Transform* transform = obj->transform();

    // �U���A�j���[�V����
    if (renderer->animeTimer() < 9)
    {
        //��
        if (obj->actorComponent()->direction_ == obj->actorComponent()->LEFT)
        {
            // �A�j���Z�b�g
            renderer->setAnimeData(getParam()->ANIME_ATTACK_L);
            param_.HIT_BOX = { -param_.SIZE.x / 2 + param_.MARGIN, -param_.SIZE.y + param_.MARGIN,
                param_.SIZE.x / 2 - param_.MARGIN, 0 - param_.MARGIN }; // �����
            debug::setString("LEFT");
        }
        //�E
        else if (obj->actorComponent()->direction_ == obj->actorComponent()->RIGHT)
        {
            // �A�j���Z�b�g
            renderer->setAnimeData(getParam()->ANIME_ATTACK_R);
            param_.HIT_BOX = { -param_.SIZE.x / 2 + param_.MARGIN, -param_.SIZE.y + param_.MARGIN,
                param_.SIZE.x / 2 - param_.MARGIN, 0 - param_.MARGIN }; // �����
            debug::setString("RIGHT");
        }
        //��
        else if (obj->actorComponent()->direction_ == obj->actorComponent()->UP)
        {
            //�A�j���Z�b�g
            renderer->setAnimeData(getParam()->ANIME_ATTACK_U);
            param_.HIT_BOX = { -param_.SIZE.x / 2 + param_.MARGIN, -param_.SIZE.y + param_.MARGIN,
                param_.SIZE.x / 2 - param_.MARGIN, 0 - param_.MARGIN }; // �����
            debug::setString("UP");
        }

        //�A�j���[�V�����J�ڃ^�C�}�[���Z
        renderer->countAnimeTime();
    }
    if (renderer->animeTimer() >= 9) {
        Game::instance()->setPlayerModeFlag(false);
    }

    debug::setString("animeTimer:%d", renderer->animeTimer());
}

void AttackPlayerBehavior::modechange(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();
    using namespace input;

    // �v���C���[�̃��[�h��ς���
    if (Game::instance()->playerModeFlag() == false)
    {
        //�A�j���[�V�����J�ڃ^�C�}�[���Z�b�g
        renderer->animeTimeReset();

        obj->setBehavior(&idlePlayerBehavior);
    }
    debug::setString("AttackMode");
    debug::setString("HP:%d",Game::instance()->player()->actorComponent()->hp());
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