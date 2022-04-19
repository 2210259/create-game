#include "all.h"
using namespace GameLib;

// �G�z�u�p�f�[�^
struct ENEMY_SET1
{
    int         area;
    int         enemyType;
    VECTOR2     pos;
} enemySet[] = {
    {  1,  0, {  640, 100 } }, // 0
    {  1,  0, {   10,  10 } }, // 1
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
    // ������
    AnimeData animeEnemy0_Left[] = {
        { &sprEnemy0_Left0, 10 },
        { &sprEnemy0_Left1, 10 },
        { nullptr, -1 },// �I���t���O
    };

    // �E����
    AnimeData animeEnemy0_Right[] = {
        { &sprEnemy0_Right0, 10 },
        { &sprEnemy0_Right1, 10 },
        { nullptr, -1 },// �I���t���O
    };

    // ���S��
    AnimeData animeEnemy0_Dead[] = {
        { &sprEnemy0_Dead0, 20 },
        { &sprEnemy0_Dead1, 10 },
        { &sprEnemy0_Dead2, 10 },
        { nullptr, -1 },// �I���t���O
    };

    //------< Enemy1�̃A�j���f�[�^ >---------------------------------------------
    // ������
    AnimeData animeEnemy1_Left[] = {
        { &sprEnemy1_Left0, 10 },
        { &sprEnemy1_Left1, 10 },
        { nullptr, -1 },// �I���t���O
    };

    // �E����
    AnimeData animeEnemy1_Right[] = {
        { &sprEnemy1_Right0, 10 },
        { &sprEnemy1_Right1, 10 },
        { nullptr, -1 },// �I���t���O
    };

    // ���S��
    AnimeData animeEnemy1_Dead[] = {
        { &sprEnemy1_Dead0, 20 },
        { &sprEnemy1_Dead1, 10 },
        { &sprEnemy1_Dead2, 10 },
        { nullptr, -1 },// �I���t���O
    };

    //------< Enemy2�̃A�j���f�[�^ >---------------------------------------------
    // ������
    AnimeData animeEnemy2_Left[] = {
        { &sprEnemy2_Left0, 10 },
        { &sprEnemy2_Left1, 10 },
        { nullptr, -1 },// �I���t���O
    };

    // �E����
    AnimeData animeEnemy2_Right[] = {
        { &sprEnemy2_Right0, 10 },
        { &sprEnemy2_Right1, 10 },
        { nullptr, -1 },// �I���t���O
    };

    // ���S��
    AnimeData animeEnemy2_Dead[] = {
        { &sprEnemy2_Dead0, 20 },
        { &sprEnemy2_Dead1, 10 },
        { &sprEnemy2_Dead2, 10 },
        { nullptr, -1 },// �I���t���O
    };
}

// �G��Y���W�̑��x�i�d�́j
void BaseEnemyBehavior::moveY(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    //Game::instance()->setEnemyPos(transform->position());
    // ���x�ɉ����x��������
    // transform->addSpeedY( getParam()->ACCEL_Y );

    // ActorBehavior::moveY(obj);
}

void BaseEnemyBehavior::enemyAnime(OBJ2D* obj)
{
    switch (obj->enemyState())
    {
    case 0:
        //////// �����ݒ� ////////
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
        renderer->setColor(VECTOR4(1.0f, 1.0f, 1.0f, 0.0f));
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

// �G���a�ɐH�������Ƃ��̏���
void BaseEnemyBehavior::hit(OBJ2D* src, OBJ2D* dst)
{

}

// �a���G�̊��m�͈͂ɓ��������̏���
void BaseEnemyBehavior::hit2(OBJ2D* src, OBJ2D* dst)
{
}

Enemy0Behavior::Enemy0Behavior()
{
    param_.ANIME_LEFT = animeEnemy0_Left;
    param_.ANIME_RIGHT = animeEnemy0_Right;
    param_.ANIME_DEAD = animeEnemy0_Dead;

    param_.SIZE = VECTOR2(600 / 2, 600 / 2);
    param_.SCALE = VECTOR2(1, 1);
    param_.ATTACK_BOX = { -300 / 4, -300 / 4, 300 / 4, 300 / 4 }; // �G���a�ɐH�����͈�
    param_.ATTACK_BOX2 = { -300, -300, 300, 300 };                 // ���m�͈�
    param_.HIT_BOX = { -300 / 4, -300 / 4, 300 / 4, 300 / 4 }; // �G���v���C���[�ɉ�������

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
    param_.ANIME_LEFT = animeEnemy1_Left;
    param_.ANIME_RIGHT = animeEnemy1_Right;
    param_.ANIME_DEAD = animeEnemy1_Dead;

    param_.SIZE = VECTOR2(740 / 2, 380 / 2);
    param_.SCALE = VECTOR2(1, 1);
    param_.ATTACK_BOX = { -370 / 4, -190 / 4, 370 / 4, 190 / 4 }; // �G���v���C���[�ɉ�������
    param_.ATTACK_BOX2 = { -370, -190, 370, 190 };                 // ���m�͈�
    param_.HIT_BOX = { -370 / 4, -190 / 4, 370 / 4, 190 / 4 }; // �G���a�ɐH�����͈�

    param_.ACCEL_X = 0.4f;
    param_.ACCEL_Y = 0.4f;
    param_.SPEED_X_MAX = 1.0f;
    param_.SPEED_Y_MAX = 1.0f;
    // param_.HP           = 10;
    param_.HIT_TIMER = 75;
    param_.DEAD_TIMER = 40;
}

Enemy2Behavior::Enemy2Behavior()
{
    param_.ANIME_LEFT = animeEnemy2_Left;
    param_.ANIME_RIGHT = animeEnemy2_Right;
    param_.ANIME_DEAD = animeEnemy2_Dead;

    param_.SIZE = VECTOR2(600 / 2, 600 / 2);
    param_.SCALE = VECTOR2(1, 1);
    param_.ATTACK_BOX = { -125 / 2, -325 / 2, 125 / 2, 325 / 2 }; // �G���a�ɐH�����͈�
    param_.ATTACK_BOX2 = { -125, -325, 125, 325 };                 // ���m�͈�
    param_.HIT_BOX = { -125 / 2, -325 / 2, 125 / 2, 325 / 2 }; // �G���v���C���[�ɉ�������͈�

    param_.ACCEL_X = 0.4f;
    param_.ACCEL_Y = 0.4f;
    param_.SPEED_X_MAX = 1.0f;
    param_.SPEED_Y_MAX = 1.0f;
    // param_.HP           = 1;
    param_.HIT_TIMER = 50;
    param_.DEAD_TIMER = 50;
}