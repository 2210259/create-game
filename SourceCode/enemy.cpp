#include "all.h"
using namespace GameLib;

// �G�z�u�p�f�[�^
struct ENEMY_SET1
{
    int         area;       // �o���X�e�[�W
    int         enemyType;  // �G�̎��
    int         posType;    // �o���ʒu(0:�� 1:�� 2:�E)
    int         timer;      // �o������
} enemySet[] = {
    {  0,  0,  0,    0},  // 0
    {  0,  1,  1,    0},  // 1
    {  0,  0,  0,   60},  // 2
    {  0,  1,  0,  150},  // 3
    {  0,  1,  2,  150},  // 3
    {  0,  0,  0,  240},  // 4

    // {  1,  0, {  0,   0 },  0 }, // 2
    // {  1,  0, {  0,   0 },  0 }, // 3
    // {  1,  0, {  0,   0 },  0 }, // 4
    // {  1,  0, {  0,   0 },  0 }, // 5
    // {  1,  0, {  0,   0 },  0 }, // 6
    { -1, -1, -1,  -1 },
};

//   640, -150(��)
//  -150,  625(��)
// 1280 + 150,  625 (�E)

void setEnemy(OBJ2DManager* obj2dManager, BG* bg)
{
    // �G�̎��
    BaseEnemyBehavior* enemyBehavior[] = {
        &enemy0Behavior,
        &enemy1Behavior,
        &enemy2Behavior,
    };

    for (int i = 0; enemySet[i].enemyType >= 0; ++i)
    {
        // �X�e�[�W�ƃG���A���قȂ�΃R���e�B�j���[
        if (enemySet[i].area != Game::instance()->stageNo()) continue;

        // �G�̏o�����ԂƃQ�[���^�C�}�[���قȂ�΃R���e�B�j���[
        if (enemySet[i].timer != Game::instance()->timer()) continue;

        // �G�̐���
        OBJ2D* enemy = new OBJ2D(
            new Renderer,
            new Collider,
            bg,
            new ActorComponent,
            nullptr
        );
        // �G�̏o���ʒu
        VECTOR2 pos = {};
        if (enemySet[i].posType == 0)      pos = {  640, -150 };         // (��)
        else if (enemySet[i].posType == 1) pos = { -150,  625 };         // (��)
        else if (enemySet[i].posType == 2) pos = { 1280 + 150,  625 };   // (�E)

        obj2dManager->add(enemy,
            enemyBehavior[enemySet[i].enemyType],
            pos,
            enemySet[i].posType
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
    AnimeData animeEnemy0_Idle[] = {
        { &sprEnemy0_Idle0, 5 },
        { &sprEnemy0_Idle0, 5 },
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
    AnimeData animeEnemy1_Idle[] = {
        { &sprEnemy1_Idle0, 5 },
        { &sprEnemy1_Idle0, 5 },
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
    AnimeData animeEnemy2_Idle[] = {
        { &sprEnemy2_Idle0, 5 },
        { &sprEnemy2_Idle0, 5 },
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
    // Transform* transform = obj->transform();
    // Game::instance()->setEnemyPos(transform->position());
    
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
        // obj->renderer()->setAnimeData(getParam()->ANIME_IDLE);
    case 1:
        // obj->renderer()->setAnimeData(getParam()->ANIME_IDLE);
        break;
    }
    debug::setString("enemyState:%d", obj->enemyState());
    debug::setString("animeData:%d", obj->renderer()->animeData());
}

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

        obj->addEnemyState(); // enemyState++
        break;

    case 1:
        //////// �v���C���[�ɍU���� ////////
        // �����ƓG�̈ʒu�̋������v�Z
        {
            auto vecP = (Game::instance()->player()->transform()->position() + VECTOR2(0, -75.0f) - obj->transform()->position());
            float dist = sqrtf(vecP.x * vecP.x + vecP.y * vecP.y);

            // �X�s�[�h���v�Z
            obj->transform()->setSpeed(4 * vecP / dist);
        }
        break;
    case 2:
        //////// �G�������� ////////
        obj->remove();
        break;
    }

    // HP��0�ȉ��ł���ΓG������
    if (obj->actorComponent()->hp() <= 0)
        obj->setEnemyState(2);

    transform->addPosition(transform->speed());
}

// �G���v���C���[�ɍU�������Ƃ�����
void BaseEnemyBehavior::hit(OBJ2D* src, OBJ2D* dst)
{
    if (src->enemyState() > 1) return;

    // �v���C���[�Ƀ_���[�W��^����
    dst->actorComponent()->damage();

    // �R���{���Ȃ���
    Game::instance()->deleteCombo();
    
    // �����蔻����Ȃ���
    // param_.ATTACK_BOX = {}; // �G���v���C���[�ɍU������͈�
    // param_.HIT_BOX = {};    // �G������ɍU�������͈�

    // moveEnemy��state����i�߂�
    src->addEnemyState();
}

// �G���v���C���[�ɍU�������Ƃ�����
// void BaseEnemyBehavior::hit2(OBJ2D* src, OBJ2D* dst)
// {
//     // �v���C���[�Ƀ_���[�W��^����
//     dst->actorComponent()->damage();
// 
//     // �����蔻����Ȃ���
//     param_.ATTACK_BOX = {}; // �G���v���C���[�ɍU������͈�
//     param_.HIT_BOX = {};    // �G������ɍU�������͈�
// 
//     // moveEnemy��state����i�߂�
//     src->addEnemyState();
// }

Enemy0Behavior::Enemy0Behavior()
{
    param_.ANIME_IDLE = animeEnemy0_Idle;
    //param_.ANIME_DEAD = animeEnemy0_Dead;

    param_.SIZE         = VECTOR2(128 / 2, 128 / 2);
    param_.SCALE        = VECTOR2(1, 1);
    param_.ATTACK_BOX   = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // �G���v���C���[�ɍU������͈�
    param_.HIT_BOX      = { -128 / 6, -128 / 6, 128 / 6, 128 / 6 }; // �G������ɍU�������͈�(Perfect)
    param_.HIT_BOX2     = { -128 / 3, -128 / 3, 128 / 3, 128 / 3 }; // �G������ɍU�������͈�(Great)
    param_.HIT_BOX3     = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // �G������ɍU�������͈�(Good)

    // param_.HIT_BOX2 = { -300 / 4, -300 / 4, 300 / 4, 300 / 4 }; // �G������ɍU�������͈�

    param_.ACCEL_X = 0.4f;
    param_.ACCEL_Y = 0.4f;
    param_.SPEED_X_MAX = 1.0f;
    param_.SPEED_Y_MAX = 1.0f;
    param_.HP = 1;    // �q�b�g�|�C���g
    param_.HIT_TIMER = 90;
    param_.DEAD_TIMER = 40;
}

void Enemy0Behavior::enemyAnime(OBJ2D* obj)
{
    // ��]����
    obj->transform()->rotate(ToRadian(5));
}

Enemy1Behavior::Enemy1Behavior()
{
    param_.ANIME_IDLE = animeEnemy1_Idle;  
    //param_.ANIME_DEAD = animeEnemy1_Dead;

    param_.SIZE         = VECTOR2(128 / 2, 128 / 2);
    param_.SCALE        = VECTOR2(1, 1);
    param_.ATTACK_BOX   = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // �G���v���C���[�ɍU������͈�
    param_.HIT_BOX      = { -128 / 6, -128 / 6, 128 / 6, 128 / 6 }; // �G������ɍU�������͈�
    param_.HIT_BOX2     = { -128 / 4, -128 / 3, 128 / 3, 128 / 3 }; // �G������ɍU�������͈�
    param_.HIT_BOX3     = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // �G������ɍU�������͈�

    param_.SPEED_X_MAX = 1.0f;
    param_.HP          = 1;    // �q�b�g�|�C���g
    param_.DEAD_TIMER  = 40;
}

void Enemy1Behavior::enemyAnime(OBJ2D* obj)
{
    // �摜�̌�����ύX
    switch (obj->actorComponent()->posType())
    {
    case 0:// (��)
        obj->transform()->setRotation(ToRadian(-90));
        break;
    case 1:// (��)
        obj->transform()->setRotation(ToRadian(180));
        break;
    case 2:// (�E)
        obj->transform()->setRotation(ToRadian(0));
        break;
    }
}

Enemy2Behavior::Enemy2Behavior()
{
    param_.ANIME_IDLE = animeEnemy2_Idle;  
    //param_.ANIME_DEAD = animeEnemy2_Dead;

    param_.SIZE         = VECTOR2(128 / 2, 128 / 2);
    param_.SCALE        = VECTOR2(1, 1);
    param_.ATTACK_BOX   = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // �G���v���C���[�ɍU������͈�
    param_.HIT_BOX      = { -128 / 6, -128 / 6, 128 / 6, 128 / 6 }; // �G������ɍU�������͈�
    param_.HIT_BOX2     = { -128 / 3, -128 / 3, 128 / 3, 128 / 3 }; // �G������ɍU�������͈�
    param_.HIT_BOX3     = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // �G������ɍU�������͈�

    param_.ACCEL_X = 0.4f;
    param_.ACCEL_Y = 0.4f;
    param_.SPEED_X_MAX = 1.0f;
    param_.SPEED_Y_MAX = 1.0f;
    param_.HP          = 1;    // �q�b�g�|�C���g
    param_.HIT_TIMER = 50;
    param_.DEAD_TIMER = 50;
}