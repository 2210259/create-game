#include "all.h"
using namespace GameLib;

// �G�z�u�p�f�[�^
struct ENEMY_SET1
{
    int         area;
    int         enemyType;
    VECTOR2     pos;
} enemySet[] = {
    {  0,  0, {  640, 100 } }, // 0
    {  0,  0, {  350, 400 } }, // 1
    // {  1,  0, {  0,   0 } }, // 2
    // {  1,  0, {  0,   0 } }, // 3
    // {  1,  0, {  0,   0 } }, // 4
    // {  1,  0, {  0,   0 } }, // 5
    // {  1,  0, {  0,   0 } }, // 6
    { -1, -1, { -1,  -1 } },
};

void setEnemy(OBJ2DManager* obj2dManager, BG* bg)
{
    BaseEnemyBehavior* enemyBehavior[] = {
        &enemy0Behavior,
        &enemy1Behavior,
        &enemy2Behavior,
    };

    for (int i = 0; enemySet[i].enemyType >= 0; ++i)
    {
        // �X�e�[�W�ƃG���A���قȂ�΃R���e�B�j���[
        if (enemySet[i].area != Game::instance()->stageNo()) continue;
        OBJ2D* enemy = new OBJ2D(
            new Renderer,
            new Collider,
            bg,
            new ActorComponent,
            nullptr
        );
        obj2dManager->add(enemy,
            enemyBehavior[enemySet[i].enemyType],
            enemySet[i].pos
        );
    }
}

//----------------------------------------//
//        �G�̃A�j���[�V����              //
//----------------------------------------//
namespace
{
    //------< Enemy0�̃A�j���f�[�^ >---------------------------------------------
    // �U��
    AnimeData animeEnemy0_Attack[] = {
        { &sprEnemy0_Attack0, 10 },
        { nullptr, -1 },// �I���t���O
    };

    // ���S��
    //AnimeData animeEnemy0_Dead[] = {
    //    { &sprEnemy0_Dead0, 20 },
    //    { &sprEnemy0_Dead1, 10 },
    //    { &sprEnemy0_Dead2, 10 },
    //    { nullptr, -1 },// �I���t���O
    //};

    //------< Enemy1�̃A�j���f�[�^ >---------------------------------------------
    // �U��
    AnimeData animeEnemy1_Attack[] = {
        { &sprEnemy1_Attack0, 10 },
        { nullptr, -1 },// �I���t���O
    };

    // ���S��
    //AnimeData animeEnemy1_Dead[] = {
    //    { &sprEnemy1_Dead0, 20 },
    //    { &sprEnemy1_Dead1, 10 },
    //    { &sprEnemy1_Dead2, 10 },
    //    { nullptr, -1 },// �I���t���O
    //};

    //------< Enemy2�̃A�j���f�[�^ >---------------------------------------------
    // �U��
    AnimeData animeEnemy2_Attack[] = {
        { &sprEnemy2_Attack0, 10 },
        { nullptr, -1 },// �I���t���O
    };

    // ���S��
    //AnimeData animeEnemy2_Dead[] = {
    //    { &sprEnemy2_Dead0, 20 },
    //    { &sprEnemy2_Dead1, 10 },
    //    { &sprEnemy2_Dead2, 10 },
    //    { nullptr, -1 },// �I���t���O
    //};
}

// �G��Y���W�̑��x�i�d�́j
void BaseEnemyBehavior::moveY(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    // Game::instance()->setEnemyPos(transform->position());
    
    // ���x�ɉ����x��������
    transform->addSpeedY( getParam()->ACCEL_Y );

    ActorBehavior::moveY(obj);
}

void BaseEnemyBehavior::enemyAnime(OBJ2D* obj)
{
    switch (obj->enemyState())
    {
    case 0:
        //////// �����ݒ� ////////
        obj->renderer()->setAnimeData(getParam()->ANIME_ATTACK);
    case 1:
        break;
    }
}

// TODO:moveEnemy
// �a�ɓG���߂Â�
void BaseEnemyBehavior::moveEnemy(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();
    Collider* collider = obj->collider();

    switch (obj->enemyState())
    {
    case 0:
        //////// �����ݒ� ////////
        transform->setScale(getParam()->SCALE);
        collider->setSize(getParam()->SIZE);
        collider->setJudgeFlag(true);
        renderer->setColor(VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
        transform->setOrgPos(transform->position());
        obj->actorComponent()->setDeadTimer(getParam()->DEAD_TIMER); // ���S���^�C�}�[�̏����ݒ�
        // Sounds_ = false;

        obj->nextEnemyState(); // enemyState++
        break;

    case 1:
        //////// �ҋ@�� ////////

        break;
    }

    ActorBehavior::moveX(obj);
    ActorBehavior::moveY(obj);
}

// �G���v���C���[�ɍU�������Ƃ�����
void BaseEnemyBehavior::hit(OBJ2D* src, OBJ2D* dst)
{

}

// �a���G�̊��m�͈͂ɓ��������̏���
void BaseEnemyBehavior::hit2(OBJ2D* src, OBJ2D* dst)
{

}

Enemy0Behavior::Enemy0Behavior()
{
    param_.ANIME_ATTACK = animeEnemy0_Attack;
    //param_.ANIME_DEAD = animeEnemy0_Dead;

    param_.SIZE = VECTOR2(128 / 2, 128 / 2);
    param_.SCALE = VECTOR2(1, 1);
    param_.ATTACK_BOX   = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // �G���v���C���[�ɍU������͈�
    param_.HIT_BOX      = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // �G������ɍU�������͈�
    
    // param_.HIT_BOX2 = { -300 / 4, -300 / 4, 300 / 4, 300 / 4 }; // �G������ɍU�������͈�

    param_.ACCEL_X = 0.4f;
    param_.ACCEL_Y = 0.4f;
    param_.SPEED_X_MAX = 1.0f;
    param_.SPEED_Y_MAX = 1.0f;
    // param_.HP           = 10;
    param_.HIT_TIMER = 90;
    param_.DEAD_TIMER = 40;
}

Enemy1Behavior::Enemy1Behavior()
{
    param_.ANIME_ATTACK = animeEnemy1_Attack;  
    //param_.ANIME_DEAD = animeEnemy1_Dead;

    param_.SIZE = VECTOR2(128 / 2, 128 / 2);
    param_.SCALE = VECTOR2(1, 1);
    param_.ATTACK_BOX   = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // �G���v���C���[�ɍU������͈�
    param_.HIT_BOX      = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // �G������ɍU�������͈�

    // param_.HIT_BOX2 = { -300 / 4, -300 / 4, 300 / 4, 300 / 4 }; // �G������ɍU�������͈�

    param_.ACCEL_X = 0.4f;
    param_.ACCEL_Y = 0.4f;
    param_.SPEED_X_MAX = 1.0f;
    param_.SPEED_Y_MAX = 1.0f;
    param_.HP           = 1;
    param_.HIT_TIMER = 75;
    param_.DEAD_TIMER = 40;
}

Enemy2Behavior::Enemy2Behavior()
{
    param_.ANIME_ATTACK = animeEnemy2_Attack;  
    //param_.ANIME_DEAD = animeEnemy2_Dead;

    param_.SIZE = VECTOR2(600 / 2, 600 / 2);
    param_.SCALE = VECTOR2(1, 1);
    param_.ATTACK_BOX   = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // �G���v���C���[�ɍU������͈�
    param_.HIT_BOX      = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // �G������ɍU�������͈�

    // param_.HIT_BOX2 = { -300 / 4, -300 / 4, 300 / 4, 300 / 4 }; // �G������ɍU�������͈�

    param_.ACCEL_X = 0.4f;
    param_.ACCEL_Y = 0.4f;
    param_.SPEED_X_MAX = 1.0f;
    param_.SPEED_Y_MAX = 1.0f;
    param_.HP           = 1;
    param_.HIT_TIMER = 50;
    param_.DEAD_TIMER = 50;
}