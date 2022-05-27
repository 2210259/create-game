//******************************************************************************
//
//
//      enemy.cpp
//
//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

// TODO�F�G�f�[�^�̍쐬

// �G�z�u�p�f�[�^
struct ENEMY_SET1
{
    int         area;       // �o���X�e�[�W
    int         enemyType;  // �G�̎��(0:�藠�� 1:�N�i�C 2:�������m�[�c 3:�A�Ńm�[�c)
    int         posType;    // �o���ʒu(0:�� 1:�� 2:�E)
    VECTOR2     scale;      // �G�̑傫��(�����������߂鏊�ȊO��0�ɐݒ肷��B����X���̑傫���A�E��Y���̑傫�� { X , Y }) �Ⴆ�Ή�1.5�{�ɂ������Ƃ�{ 1.5f, 0 }�Ə���;
    float       timer;      // �o������(���o�����Ԃ�0�b���ƃo�O�邩��)(�Ⴆ��1.5�b�ɐݒ肵�����Ƃ���1.5f��f�𐔎��̌��ɂ���)
} enemySet[] = {

    ////////////////////////////
    /////�@�`���[�g���A���@/////
    ////////////////////////////
    
   // TODO:ENEMY�̃R�����g�A�E�g
   // �藠���̐���
   {  0,  4,  2, { 0,   0 },  0.5f,  },  
   {  0,  4,  0, { 0,   0 },  3.3f,  },
   {  0,  4,  2, { 0,   0 },  5.6f,  },
   {  0,  4,  2, { 0,   0 },  7.8f,  },
   {  0,  4,  1, { 0,   0 },  8.2f,  },
   {  0,  4,  1, { 0,   0 },  10.8f, },
   {  0,  4,  1, { 0,   0 },  13.1f, },
   {  0,  4,  2, { 0,   0 },  13.4f, },
   {  0,  4,  2, { 0,   0 },  16.0f, },
   {  0,  4,  2, { 0,   0 },  18.3f, },
   {  0,  4,  0, { 0,   0 },  18.8f, },

   //�N�i�C�̐���
   {  0,  1,  0, { 0,   0 },  22.7f,  },
   {  0,  1,  0, { 0,   0 },  25.0f,  },
   {  0,  1,  1, { 0,   0 },  25.2f,  },
   {  0,  1,  1, { 0,   0 },  27.7f,  },
   {  0,  1,  1, { 0,   0 },  30.0f,  },
   {  0,  1,  2, { 0,   0 },  30.3f,  },
   {  0,  1,  1, { 0,   0 },  33.0f,  },
   {  0,  1,  0, { 0,   0 },  35.4f,  },
   {  0,  1,  1, { 0,   0 },  35.6f,  },
   {  0,  1,  1, { 0,   0 },  38.3f,  },
   {  0,  1,  1, { 0,   0 },  40.8f,  },// HP35
   
   //�A�Ńm�[�c�̐���
   {  0,  3,  1, { 0.0f,   0 },  42.0f,  },
   {  0,  3,  0, { 0.0f,   0 },  45.0f,  },
   {  0,  3,  2, { 0.0f,   0 },  48.0f,  },
   {  0,  3,  1, { 0.0f,   0 },  51.0f,  },

   //�������m�[�c�̐���
   {  0,  2,  1, { 1.82f,   0 },  54.0f,  },
   {  0,  2,  0, { 0.0f,1.83f },  59.5f,  },
   {  0,  2,  2, { 1.84f,0.0f },  64.5f,  },

   //����
   {  0,  2,  1, { 1.4f,0.0f },  67.4f,  },
   {  0,  2,  1, { 1.4f,0.0f },  70.0f,  },
   {  0,  3,  2, { 2.0f,0.0f },  73.6f,  },
   {  0,  3,  0, { 0.0f,2.0f },  76.2f,  },
   {  0,  3,  1, { 2.5f,0.0f },  78.6f,  },
   {  0,  4,  2, { 0.0f,0.0f },  82.0f,  },
   {  0,  4,  1, { 0.0f,0.0f },  82.4f,  },
   {  0,  4,  0, { 0.0f,0.0f },  83.5f,  },
   {  0,  1,  2, { 0.0f,0.0f },  85.1f,  },
   {  0,  4,  1, { 0.0f,0.0f },  84.6f,  },
   {  0,  4,  0, { 0.0f,0.0f },  85.2f,  },
   {  0,  4,  2, { 0.0f,0.0f },  85.9f,  },
   {  0,  1,  2, { 0.0f,0.0f },  87.8f,  },
   {  0,  4,  1, { 0.0f,0.0f },  87.2f,  },
   {  0,  4,  0, { 0.0f,0.0f },  88.0f,  },
   {  0,  3,  0, { 0.0f,0.5f },  89.3f,  },
   {  0,  1,  1, { 0.0f,0.0f },  90.0f,  },
   {  0,  1,  1, { 0.0f,0.0f },  90.4f,  },

   ////////////////////////////
   /////�@   �X�e�[�W1    /////
   ////////////////////////////
   {  1,  1,  0, {    0,     0 },  1.3f, },
   {  1,  1,  0, {    0,     0 },  1.7f, },
   {  1,  3,  0, {    0,  0.6f },  1.9f, },
   {  1,  3,  2, {    0,     0 },  2.8f, },
   {  1,  1,  1, {    0,     0 },  4.3f, },
   {  1,  3,  1, { 0.6f,     0 },  4.5f, },
   {  1,  3,  0, {    0, 0.75f },  5.6f, },                
   {  1,  1,  0, {    0,     0 },     7, },
   {  1,  1,  0, {    0,     0 }, 7.35f, },
   {  1,  3,  0, {    0,  0.6f },  7.6f, },
   {  1,  3,  0, {    0, 0.78f },  8.5f, },
   {  1,  1,  1, {    0,     0 },  9.7f, },
   {  1,  1,  1, {    0,     0 },    10, },
   {  1,  3,  1, { 0.7f,     0 }, 10.2f, },
   {  1,  3,  0, {    0,  0.9f }, 11.5f, },
   {  1,  2,  1, {    0,     0 },    12, },
   {  1,  3,  1, { 0.8f,     0 }, 14.2f, },
   {  1,  2,  1, {    0,     0 }, 14.9f, },
   {  1,  3,  1, { 0.8f,     0 },    17, },
   {  1,  2,  1, {    0,     0 }, 17.7f, },
   {  1,  3,  1, {    0,     0 },    20, },
   {  1,  3,  1, {    0,     0 },    21, },
   {  1,  3,  1, {    0,     0 },    22, },
   {  1,  1,  2, {    0,     0 }, 23.7f, },
   {  1,  3,  1, { 0.9f,     0 }, 25.3f, },
   {  1,  3,  1, { 0.9f,     0 }, 24.3f, },
   {  1,  3,  0, {    0,     0 }, 26.5f, },
   {  1,  3,  0, {    0,     0 }, 27.5f, },
   {  1,  3,  0, {    0,     0 }, 28.5f, },
   {  1,  3,  0, {    0,     0 }, 29.5f, },
   {  1,  3,  0, {    0,     0 }, 30.5f, },
   {  1,  3,  0, {    0,     0 }, 31.5f, },
   {  1,  3,  0, {    0,     0 }, 32.5f, },
   {  1,  3,  1, {    0,     0 },    34, },
   {  1,  1,  1, {    0,     0 }, 35.2f, },
   {  1,  1,  1, {    0,     0 }, 35.5f, },
   {  1,  3,  1, { 0.6f,     0 }, 35.7f, },
   {  1,  3,  2, {    0,     0 }, 36.6f, },
   {  1,  1,  2, {    0,     0 }, 37.9f, },
   {  1,  1,  2, {    0,     0 }, 38.2f, },
   {  1,  3,  2, { 0.6f,     0 }, 38.5f, },
   {  1,  3,  0, {    0,     0 }, 39.4f, },
   {  1,  1,  1, {    0,     0 }, 40.7f, },
   {  1,  1,  1, {    0,     0 }, 41.1f, },
   {  1,  3,  1, { 0.6f,     0 }, 41.4f, },
   {  1,  3,  0, {    0,     0 }, 42.3f, },
   {  1,  1,  1, {    0,     0 }, 43.6f, },
   {  1,  1,  1, {    0,     0 },    44, },
   {  1,  3,  1, { 0.6f,     0 }, 44.2f, },
   {  1,  3,  0, {    0,     0 }, 45.1f, },
   {  1,  1,  1, {    0,     0 }, 46.4f, },
   {  1,  1,  2, {    0,     0 }, 46.8f, },
   {  1,  3,  0, {    0,  0.6f },    47, },
   {  1,  3,  0, {    0,     0 }, 48.1f, },
   {  1,  1,  1, {    0,     0 }, 49.3f, },
   {  1,  1,  1, {    0,     0 }, 49.7f, },
   {  1,  3,  1, { 0.6f,     0 }, 49.9f, },
   {  1,  3,  0, {    0,     0 },    51, },
   {  1,  1,  2, {    0,     0 }, 52.1f, },
   {  1,  1,  2, {    0,     0 }, 52.5f, },
   {  1,  3,  2, { 0.6f,     0 }, 52.7f, },
   {  1,  3,  0, {    0,     0 }, 53.8f, },
   {  1,  1,  1, {    0,     0 }, 54.9f, },
   {  1,  1,  1, {    0,     0 }, 55.3f, },
   {  1,  3,  1, { 0.6f,     0 }, 55.5f, },
   {  1,  3,  0, {    0,     0 }, 56.9f, },
   {  1,  1,  1, {    0,     0 }, 57.9f, },
   {  1,  1,  2, {    0,     0 }, 58.2f, },
   {  1,  1,  1, {    0,     0 }, 58.7f, },
   {  1,  1,  1, {    0,     0 },    59, },
   {  1,  1,  2, {    0,     0 }, 59.5f, },
   {  1,  1,  2, {    0,     0 }, 59.8f, },
   {  1,  1,  2, {    0,     0 }, 60.3f, },
   {  1,  1,  1, {    0,     0 }, 60.6f, },
   {  1,  1,  1, {    0,     0 }, 61.1f, },
   {  1,  1,  2, {    0,     0 }, 61.4f, },
   {  1,  1,  0, {    0,     0 }, 61.9f, },
   {  1,  1,  0, {    0,     0 }, 62.2f, },
   {  1,  1,  1, {    0,     0 }, 62.7f, },
   {  1,  1,  2, {    0,     0 },    63, },
   {  1,  1,  1, {    0,     0 }, 63.5f, },
   {  1,  1,  1, {    0,     0 }, 63.8f, },
   {  1,  1,  2, {    0,     0 }, 64.3f, },
   {  1,  1,  2, {    0,     0 }, 64.6f, },
   {  1,  1,  0, {    0,     0 }, 65.1f, },
   {  1,  1,  0, {    0,     0 }, 65.4f, },
   {  1,  1,  1, {    0,     0 }, 65.9f, },
   {  1,  1,  0, {    0,     0 }, 66.2f, },
   {  1,  1,  0, {    0,     0 }, 66.7f, },
   {  1,  1,  1, {    0,     0 },    67, },
   {  1,  1,  2, {    0,     0 }, 67.5f, },
   {  1,  1,  1, {    0,     0 }, 67.8f, },
   {  1,  3,  0, {    0,  0.7f }, 68.6f, },
   {  1,  1,  2, {    0,     0 }, 69.4f, },
   {  1,  1,  1, {    0,     0 }, 69.5f, },
   {  1,  3,  0, {    0,  0.7f },    70, },
   {  1,  1,  2, {    0,     0 },70.65f, },
   {  1,  1,  1, {    0,     0 },70.75f, },
   {  1,  3,  0, {    0,  0.7f },71.35f, },
   {  1,  1,  2, {    0,     0 },    72, },
   {  1,  1,  1, {    0,     0 }, 72.1f, },
   {  1,  3,  0, {    0,  0.7f }, 72.7f, },
   {  1,  1,  2, {    0,     0 },73.35f, },
   {  1,  1,  1, {    0,     0 },73.55f, },
   {  1,  3,  0, {    0,  0.7f }, 74.2f, },
   {  1,  1,  2, {    0,     0 },74.85f, },
   {  1,  1,  1, {    0,     0 },75.05f, },
   {  1,  3,  0, {    0,  0.7f },75.55f, },
   {  1,  1,  2, {    0,     0 }, 76.2f, },
   {  1,  1,  1, {    0,     0 }, 76.4f, },
   {  1,  3,  0, {    0,     1 }, 76.9f, },
   {  1,  3,  0, {    0,  0.7f },78.22f, },
   {  1,  1,  2, {    0,     0 },78.87f, },
   {  1,  1,  1, {    0,     0 },79.07f, },
   {  1,  3,  0, {    0,  0.7f },79.57f, },
   {  1,  1,  2, {    0,     0 },80.22f, },
   {  1,  1,  1, {    0,     0 },80.42f, },
   {  1,  3,  0, {    0,  0.7f },80.97f, },
   {  1,  1,  2, {    0,     0 },81.57f, },
   {  1,  1,  1, {    0,     0 },81.77f, },
   {  1,  3,  0, {    0,     1 },82.19f, },
   {  1,  3,  0, {    0,  0.7f },83.54f, },
   {  1,  1,  2, {    0,     0 },84.19f, },
   {  1,  1,  1, {    0,     0 },84.39f, },
   {  1,  3,  0, {    0,  0.7f },84.89f, },
   {  1,  3,  0, {    0,  0.7f },85.99f, },
   {  1,  1,  2, {    0,     0 },86.34f, },
   {  1,  1,  1, {    0,     0 },86.54f, },
   {  1,  3,  0, {    0,  0.7f },87.14f, },
   {  1,  1,  2, {    0,     0 },87.79f, },
   {  1,  1,  1, {    0,     0 },87.99f, },
   {  1,  2,  0, {    0,  1.5f }, 88.5f, },
   {  1,  1,  0, {    0,     0 }, 91.6f, },
   {  1,  1,  0, {    0,     0 },    92, },
   {  1,  3,  0, {    0,  0.6f }, 92.2f, },
   {  1,  3,  1, {    0,     0 },    93, },
   {  1,  1,  1, {    0,     0 }, 94.2f, },
   {  1,  1,  1, {    0,     0 }, 94.6f, },
   {  1,  3,  1, { 0.6f,     0 }, 94.8f, },
   {  1,  3,  0, {    0, 0.75f }, 95.9f, },
   {  1,  1,  0, {    0,     0 }, 97.3f, },
   {  1,  1,  0, {    0,     0 },97.65f, },
   {  1,  3,  0, {    0,  0.6f }, 98.1f, },
   {  1,  3,  0, {    0, 0.78f }, 98.8f, },
   {  1,  1,  1, {    0,     0 },   100, },
   {  1,  1,  1, {    0,     0 },100.3f, },
   {  1,  3,  1, { 0.7f,     0 },100.5f, },
   {  1,  3,  0, {    0,  0.9f },101.8f, },
   {  1,  1,  0, {    0,     0 },102.9f, },

   { -1, -1, -1, { -1, -1 }, -1 }, // ����������Ȃ��悤��
};

void setEnemy(OBJ2DManager* obj2dManager, BG* bg)
{
    // �G�̎��
    BaseEnemyBehavior* enemyBehavior[] = {
        &enemy0Behavior,    // �藠��
        &enemy1Behavior,    // �N�i�C
        &enemy2Behavior,    // �������m�[�c
        &enemy3Behavior,    // �A�Ńm�[�c
        &enemy4Behavior,    // �藠��
    };

    for (int i = 0; enemySet[i].enemyType >= 0; ++i)
    {
        // �X�e�[�W�ƃG���A���قȂ�΃R���e�B�j���[
        if (enemySet[i].area != Game::instance()->stageNo()) continue;

        // �G�̏o�����ԂƃQ�[���^�C�}�[���قȂ�΃R���e�B�j���[
        if (static_cast<int>(enemySet[i].timer * 60) != Game::instance()->timer()) continue;

        // �G�̐���
        OBJ2D* enemy = new OBJ2D(
            new Renderer,
            new Collider,
            bg,
            new ActorComponent,
            nullptr,
            nullptr
        );

        // �G�̏o���ʒu
        VECTOR2 pos = {};
        float posY = Game::instance()->player()->transform()->position().y - (Game::instance()->player()->collider()->size().y / 2);
        if (enemySet[i].posType == 0)      pos = { BG::WINDOW_W / 2, -500 };    // (��)
        else if (enemySet[i].posType == 1) pos = { -500, posY };                // (��)
        else if (enemySet[i].posType == 2) pos = { BG::WINDOW_W + 500, posY };  // (�E)

        obj2dManager->add(enemy,
            enemyBehavior[enemySet[i].enemyType],
            pos,
            enemySet[i].posType, enemySet[i].scale
        );
    }
}

//----------------------------------------//
//        �G�̃A�j���[�V����              //
//----------------------------------------//
namespace
{
    //------< �藠���̃A�j���f�[�^ >---------------------------------------------
    // �U��
    AnimeData animeEnemy0_Idle[] = {
        { &sprEnemy0_Idle0, 5 },
        { &sprEnemy0_Idle0, 5 },
        { nullptr, -1 },// �I���t���O
    };

    // ���S��
    AnimeData animeEnemy0_Dead[] = {
        { &sprEnemy0_Dead0, 6 },
        { &sprEnemy0_Dead1, 6 },
        { &sprEnemy0_Dead2, 6 },
        { nullptr, -1 },// �I���t���O
    };

    //------< �N�i�C�̃A�j���f�[�^ >---------------------------------------------
    // �U��
    AnimeData animeEnemy1_Idle[] = {
        { &sprEnemy1_Idle0, 5 },
        { &sprEnemy1_Idle0, 5 },
        { nullptr, -1 },// �I���t���O
    };

    // ���S��
    AnimeData animeEnemy1_Dead[] = {
        { &sprEnemy1_Dead0, 6 },
        { &sprEnemy1_Dead1, 6 },
        { &sprEnemy1_Dead2, 6 },
        { nullptr, -1 },// �I���t���O
    };

    //------< �������m�[�c(�c)�̃A�j���f�[�^ >---------------------------------------------
    // �U��
    AnimeData animeEnemy2_1_Idle[] = {
        { &sprEnemy2_1_Idle0, 5 },
        { &sprEnemy2_1_Idle0, 5 },
        { nullptr, -1 },// �I���t���O
    };

    //------< �������m�[�c(��)�̃A�j���f�[�^ >---------------------------------------------
    // �U��
    AnimeData animeEnemy2_2_Idle[] = {
        { &sprEnemy2_2_Idle0, 5 },
        { &sprEnemy2_2_Idle0, 5 },
        { nullptr, -1 },// �I���t���O
    };

    // ���S��
    AnimeData animeEnemy2_Dead[] = {
        { &sprEnemy2_Dead0, 6 },
        { &sprEnemy2_Dead1, 6 },
        { nullptr, -1 },// �I���t���O
    };

    //------< �A��(�c)�̃A�j���f�[�^ >---------------------------------------------
    // �U��
    AnimeData animeEnemy3_1_Idle[] = {
        { &sprEnemy3_1_Idle0, 5 },
        { &sprEnemy3_1_Idle0, 5 },
        { nullptr, -1 },// �I���t���O
    };

    //------< �A��(��)�̃A�j���f�[�^ >---------------------------------------------
    // �U��
    AnimeData animeEnemy3_2_Idle[] = {
        { &sprEnemy3_2_Idle0, 5 },
        { &sprEnemy3_2_Idle0, 5 },
        { nullptr, -1 },// �I���t���O
    };

    // ���S��
    AnimeData animeEnemy3_Dead[] = {
        { &sprEnemy3_Dead0, 6 },
        { &sprEnemy3_Dead1, 6 },
        { nullptr, -1 },// �I���t���O
    };
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

void BaseEnemyBehavior::enemyParam(OBJ2D* obj)
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
    // debug::setString("enemyState:%d", obj->enemyState());
    // debug::setString("animeData:%d", obj->renderer()->animeData());
}

// �G�̓���
void BaseEnemyBehavior::moveEnemy(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();
    Collider* collider = obj->collider();

    switch (obj->enemyState())
    {
    case 0: {
        //////// �����ݒ� ////////
        collider->setSize(getParam()->SIZE);
        const VECTOR2 size = {
            collider->size().x * transform->scale().x,
            collider->size().y * transform->scale().y,
        };
        collider->setSize(size);
        collider->setJudgeFlag(true);
        collider->setJudgeBoxFlag(true);    // �����蔻����s��
        collider->setJudgeBoxFlag4(false);
        renderer->setColor(VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
        transform->setOrgPos(transform->position());
        obj->collider()->setJudgeFlag(true);
        obj->actorComponent()->setScore(getParam()->SCORE); // �X�R�A�̐ݒ�
        obj->actorComponent()->setDeleteCombo2Flag(param_.FLAG_DELETE_COMBO2);
        obj->actorComponent()->setDeadTimer(getParam()->DEAD_TIMER); // ���S���^�C�}�[�̏����ݒ�

        obj->addEnemyState(); // enemyState++
        break;
    }
    case 1:
        //////// �v���C���[�ɍU���� ////////
        
        // �v���C���[��HP��0�ɂȂ����炷�ׂĂ̓G�̃X�s�[�h���[���ɂ�����
        if (Game::instance()->state() >= 3) {
            obj->transform()->setSpeed(VECTOR2(0, 0));
            obj->addEnemyState();
        }
        break;
    case 2:
        //////// �G�������� ////////
        obj->renderer()->setAnimeData(getParam()->ANIME_DEAD);
        obj->actorComponent()->countDeadTimer();
        if (obj->actorComponent()->deadTimer() <= 0) {
            obj->remove();
        }
        break;
    }
    // debug::setString("size.x:%f", collider->size().x);
    // debug::setString("size.y:%f", collider->size().y);

    // debug::setString("speed.x:%f", transform->speed().x);
    // debug::setString("speed.y:%f", transform->speed().y);

    transform->addPosition(transform->speed());
}

// �G���v���C���[�ɍU�������Ƃ�����
void BaseEnemyBehavior::hit(OBJ2D* src, OBJ2D* dst)
{
    // false�̏ꍇ���������Ȃ�
    if (src->collider()->judgeFlag() == false) return;
    if (src->enemyState() == 2) return;

    // �W���b�W�t���O���Ȃ���
    src->collider()->setJudgeFlag(false);

    // �}�X�N�̏�������
    Game::instance()->setNotesMaskFlag(false);
    
    //���������~�߂�
    GameLib::music::stop(18);

    // �ʏ�m�[�c���v���C���[�ɓ����������̂�
    if (src->behavior() != &enemy2Behavior && src->behavior() != &enemy3Behavior) {

        // �v���C���[�Ƀ_���[�W��^����
        dst->actorComponent()->damage();

        // �v���C���[�_��
        Game::instance()->player()->actorComponent()->setPlayerHitTimer(24);

        // �m�[�c����𑗂�
        Game::instance()->setDecision(Game::instance()->MISS);

        // �R���{���Ȃ���
        Game::instance()->deleteCombo();

        // �R���{�̃T�C�Y��ݒ�
        Game::instance()->setComboSize(VECTOR2(2, 2));

        // �~�X�J�E���g 
        Game::instance()->addMissNum();
    
        // �_���[�W��
        GameLib::music::play(17);
    }
    // �G������
    src->remove();
}

// �藠��
Enemy0Behavior::Enemy0Behavior()
{
    param_.ANIME_IDLE = animeEnemy0_Idle;
    param_.ANIME_DEAD = animeEnemy0_Dead;

    param_.SIZE         = VECTOR2(150, 150);
    param_.SCALE        = VECTOR2(1.5f, 1.5f);
    const VECTOR2 size = {
        param_.SIZE.x * param_.SCALE.x,
        param_.SIZE.y * param_.SCALE.y
    };
    param_.ATTACK_BOX   = { -size.x / 2, -size.y / 2, size.x / 2, size.y / 2 }; // �G���v���C���[�ɍU������͈�
    param_.HIT_BOX      = { -size.x / 6, -size.y / 6, size.x / 6, size.y / 6 }; // �G������ɍU�������͈�(Perfect)
    param_.HIT_BOX2     = { -size.x / 3, -size.y / 3, size.x / 3, size.y / 3 }; // �G������ɍU�������͈�(Great)
    param_.HIT_BOX3     = { -size.x / 2, -size.y / 2, size.x / 2, size.y / 2 }; // �G������ɍU�������͈�(Good)

    // param_.HIT_BOX2 = { -300 / 4, -300 / 4, 300 / 4, 300 / 4 }; // �G������ɍU�������͈�

    param_.SPEED       = 6.0f;
    param_.SPEED_Y_MAX = 6.0f;
    param_.SPEED_X_MAX = 3.0f;
    param_.HP = 1;    // �q�b�g�|�C���g
    param_.SCORE = 300;
    param_.DEAD_TIMER = 18;
}

void Enemy0Behavior::enemyParam(OBJ2D* obj)
{
    // �o�Ă���ʒu�ɂ���ăX�s�[�h��ݒ�
    switch (obj->actorComponent()->posType())
    {
    case 0:// (�ʒu����̎�)
        obj->transform()->setSpeedY(param_.SPEED);
        break;
    case 1:// (�ʒu�����̎�)
        obj->transform()->setSpeedX(param_.SPEED);
        break;
    case 2:// (�ʒu���E�̎�)
        obj->transform()->setSpeedX(-param_.SPEED);
        break;
    }
    // ��]����
    // obj->transform()->rotate(ToRadian(10));
}

// �N�i�C
Enemy1Behavior::Enemy1Behavior()
{
    param_.ANIME_IDLE = animeEnemy1_Idle;
    param_.ANIME_DEAD = animeEnemy1_Dead;

    param_.SIZE         = VECTOR2(150, 150);
    param_.SCALE        = VECTOR2(1.5f, 1.5f);
    const VECTOR2 size = {
        param_.SIZE.x * param_.SCALE.x,
        param_.SIZE.y * param_.SCALE.y
    };
    param_.ATTACK_BOX   = { -size.x / 2, -size.y / 2, size.x / 2, size.y / 2 }; // �G���v���C���[�ɍU������͈�
    param_.HIT_BOX      = { -size.x / 6, -size.y / 6, size.x / 6, size.y / 6 }; // �G������ɍU�������͈�
    param_.HIT_BOX2     = { -size.x / 3, -size.y / 3, size.x / 3, size.y / 3 }; // �G������ɍU�������͈�
    param_.HIT_BOX3     = { -size.x / 2, -size.y / 2, size.x / 2, size.y / 2 }; // �G������ɍU�������͈�

    param_.SPEED        = 10.0f;
    param_.SPEED_Y_MAX  = 10.0f;
    param_.SPEED_X_MAX  = 5.0f;
    param_.HP           = 1;    // �q�b�g�|�C���g
    param_.SCORE        = 500;
    param_.DEAD_TIMER   = 18;
}

void Enemy1Behavior::enemyParam(OBJ2D* obj)
{
    // �o�Ă���ʒu�ɂ���ĉ摜�̌����ƃX�s�[�h�̐ݒ�
    switch (obj->actorComponent()->posType())
    {
    case 0:// (�ʒu����̎�)
        obj->transform()->setRotation(ToRadian(-90));
        obj->transform()->setSpeedY(param_.SPEED);
        break;
    case 1:// (�ʒu�����̎�)
        obj->transform()->setRotation(ToRadian(180));
        obj->transform()->setSpeedX(param_.SPEED);
        break;
    case 2:// (�ʒu���E�̎�)
        obj->transform()->setRotation(ToRadian(0));
        obj->transform()->setSpeedX(-param_.SPEED);
        break;
    }
    // debug::setString("obj->actorComponent()->posType():%d", obj->actorComponent()->posType());
}

// �������m�[�c
Enemy2Behavior::Enemy2Behavior()
{
    param_.ANIME_IDLE = animeEnemy2_1_Idle;
    param_.ANIME_DEAD = animeEnemy2_Dead;

    param_.SIZE  = VECTOR2(512, 128);
    param_.SCALE = VECTOR2(1, 1);
    param_.HIT_BOX  = { 512 / 2 - (128 / 6), -128 / 2, 512 / 2 + (128 / 6), 128 / 2 }; // �G������ɍU�������͈�
    param_.HIT_BOX2 = { 512 / 2 - (128 / 3), -128 / 2, 512 / 2 + (128 / 3), 128 / 2 }; // �G������ɍU�������͈�
    param_.HIT_BOX3 = { 512 / 2 - (128 / 2), -128 / 2, 512 / 2 + (128 / 2), 128 / 2 }; // �G������ɍU�������͈�

    param_.HIT_BOX4 = { -512 / 2 - (128 / 2), -128 / 2,  512 / 2 + (128 / 2), 128 / 2 }; // �G������ɍU�������͈�
                          
    param_.HIT_BOX5 = { -512 / 2 - (128 / 6), -128 / 2, -512 / 2 + (128 / 6), 128 / 2 }; // �G������ɍU�������͈�
    param_.HIT_BOX6 = { -512 / 2 - (128 / 3), -128 / 2, -512 / 2 + (128 / 3), 128 / 2 }; // �G������ɍU�������͈�
    param_.HIT_BOX7 = { -512 / 2 - (128 / 2), -128 / 2, -512 / 2 + (128 / 2), 128 / 2 }; // �G������ɍU�������͈�
    // param_.ATTACK_BOX   = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // �G���v���C���[�ɍU������͈�

    param_.SPEED        = 6.0f;
    param_.SPEED_Y_MAX  = 6.0f;
    param_.SPEED_X_MAX  = 3.0f;
    param_.HP           = 1;    // �q�b�g�|�C���g
    param_.SCORE        = 1000; // �m�[�c�̃X�R�A�_��
    param_.HIT_TIMER    = 50;
    param_.DEAD_TIMER   = 12;
}

// �������m�[�c
void Enemy2Behavior::enemyParam(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();
    Collider* collider = obj->collider();

    // �o�Ă���ʒu�ɂ���ĉ摜�̌����ƃX�s�[�h�̐ݒ�
    switch (obj->actorComponent()->posType())
    {
    case 0: { // (�ʒu����̎�)
        param_.ANIME_IDLE = animeEnemy2_1_Idle;
        if (obj->enemyState() < 2)
            renderer->setAnimeData(getParam()->ANIME_IDLE);
        param_.SIZE = VECTOR2(128, 512);
        collider->setSize(param_.SIZE);
        transform->setScale(transform->orgScale());
        const VECTOR2 size = {
            collider->size().x * transform->scale().x,
            collider->size().y * transform->scale().y,
        };
        collider->setSize(size);
        transform->setSpeedY(param_.SPEED);
        param_.HIT_BOX = { -size.x / 2, size.y / 2 - (size.x / 6), size.x / 2, size.y / 2 + (size.x / 6) };  // �G������ɍU�������͈�
        param_.HIT_BOX2 = { -size.x / 2, size.y / 2 - (size.x / 3), size.x / 2, size.y / 2 + (size.x / 3) }; // �G������ɍU�������͈�
        param_.HIT_BOX3 = { -size.x / 2, size.y / 2 - (size.x / 2), size.x / 2, size.y / 2 + (size.x / 2) }; // �G������ɍU�������͈�

        param_.HIT_BOX4 = { -size.x / 2, -size.y / 2 - (size.x / 2), size.x / 2, size.y / 2 + (size.x / 2) }; // �G������ɍU�������͈�

        param_.HIT_BOX5 = { -size.x / 2, -size.y / 2 - (size.x / 6), size.x / 2, -size.y / 2 + (size.x / 6) }; // �G������ɍU�������͈�
        param_.HIT_BOX6 = { -size.x / 2, -size.y / 2 - (size.x / 3), size.x / 2, -size.y / 2 + (size.x / 3) }; // �G������ɍU�������͈�
        param_.HIT_BOX7 = { -size.x / 2, -size.y / 2 - (size.x / 2), size.x / 2, -size.y / 2 + (size.x / 2) }; // �G������ɍU�������͈�

        param_.ATTACK_BOX = { -size.x / 2, -size.y / 2 + (size.x / 2), size.x / 2, -size.y / 2 + (size.x) }; // �G���v���C���[�ɍU������͈�

        const float playerHeadPos = Game::instance()->player()->transform()->position().y - Game::instance()->player()->collider()->size().y - 50.0f;
        const float notesPosBottom = transform->position().y + (size.y / 2);
        
        // ���̈ʒu�𒴂�����`��ʒu��ύX
        if (notesPosBottom > playerHeadPos) {
            collider->setMergin({ 0 ,notesPosBottom - playerHeadPos });   
        }
        else {
            collider->setMergin({ 0, 0 });
        }
        debug::setString("scale.y:%f", transform->scale().y);
        debug::setString("size.y:%f", collider->size().y);
        debug::setString("merzin.y:%f", collider->mergin().y);
        break;
    }
    case 1: { // (�ʒu�����̎�)
        param_.ANIME_IDLE = animeEnemy2_2_Idle;
        if (obj->enemyState() < 2)
            obj->renderer()->setAnimeData(getParam()->ANIME_IDLE);
        param_.SIZE = VECTOR2(512, 128);
        collider->setSize(param_.SIZE);
        transform->setScale(transform->orgScale());
        const VECTOR2 size = {
            collider->size().x * transform->scale().x,
            collider->size().y * transform->scale().y,
        };
        collider->setSize(size);
        obj->transform()->setSpeedX(param_.SPEED);    // �X�s�[�h��ݒ�
        param_.HIT_BOX  = { size.x / 2 - (size.y / 6), -size.y / 2, size.x / 2 + (size.y / 6), size.y / 2 }; // �G������ɍU�������͈�
        param_.HIT_BOX2 = { size.x / 2 - (size.y / 3), -size.y / 2, size.x / 2 + (size.y / 3), size.y / 2 }; // �G������ɍU�������͈�
        param_.HIT_BOX3 = { size.x / 2 - (size.y / 2), -size.y / 2, size.x / 2 + (size.y / 2), size.y / 2 }; // �G������ɍU�������͈�

        param_.HIT_BOX4 = { -size.x / 2 - (size.y / 2), -size.y / 2,  size.x / 2 + (size.y / 2), size.y / 2 }; // �G������ɍU�������͈�

        param_.HIT_BOX5 = { -size.x / 2 - (size.y / 6), -size.y / 2, -size.x / 2 + (size.y / 6), size.y / 2 }; // �G������ɍU�������͈�
        param_.HIT_BOX6 = { -size.x / 2 - (size.y / 3), -size.y / 2, -size.x / 2 + (size.y / 3), size.y / 2 }; // �G������ɍU�������͈�
        param_.HIT_BOX7 = { -size.x / 2 - (size.y / 2), -size.y / 2, -size.x / 2 + (size.y / 2), size.y / 2 }; // �G������ɍU�������͈�

        param_.ATTACK_BOX = { -size.x / 2 + (size.y / 2), -size.y / 2, -size.x / 2 + (size.y), size.y / 2 }; // �G���v���C���[�ɍU������͈�

        const float playerMiddlePos = Game::instance()->player()->transform()->position().x - 75.0f;
        const float notesPosRight = transform->position().x + (size.x / 2);

        // ���̈ʒu�𒴂�����`��ʒu��ύX
        if (notesPosRight > playerMiddlePos) {
            collider->setMergin({ notesPosRight - playerMiddlePos, 0 });
        }
        else {
            collider->setMergin({ 0, 0 });
        }
        break;
    }
    case 2: { // (�ʒu���E�̎�)
        param_.ANIME_IDLE = animeEnemy2_2_Idle;
        if (obj->enemyState() < 2)
            obj->renderer()->setAnimeData(getParam()->ANIME_IDLE);
        param_.SIZE = VECTOR2(512, 128);
        collider->setSize(param_.SIZE);
        transform->setScale(transform->orgScale());
        const VECTOR2 size = {
            collider->size().x * transform->scale().x,
            collider->size().y * transform->scale().y,
        };
        collider->setSize(size);
        obj->transform()->setRotation(ToRadian(180)); // ������ύX
        obj->transform()->setSpeedX(-param_.SPEED);
        param_.HIT_BOX = { -size.x / 2 - (size.y / 6), -size.y / 2, -size.x / 2 + (size.y / 6), size.y / 2 }; // �G������ɍU�������͈�
        param_.HIT_BOX2 = { -size.x / 2 - (size.y / 3), -size.y / 2, -size.x / 2 + (size.y / 3), size.y / 2 }; // �G������ɍU�������͈�
        param_.HIT_BOX3 = { -size.x / 2 - (size.y / 2), -size.y / 2, -size.x / 2 + (size.y / 2), size.y / 2 }; // �G������ɍU�������͈�

        param_.HIT_BOX4 = { -size.x / 2 - (size.y / 2), -size.y / 2,  size.x / 2 + (size.y / 2), size.y / 2 }; // �G������ɍU�������͈�

        param_.HIT_BOX5 = { size.x / 2 - (size.y / 6), -size.y / 2, size.x / 2 + (size.y / 6), size.y / 2 }; // �G������ɍU�������͈�
        param_.HIT_BOX6 = { size.x / 2 - (size.y / 3), -size.y / 2, size.x / 2 + (size.y / 3), size.y / 2 }; // �G������ɍU�������͈�
        param_.HIT_BOX7 = { size.x / 2 - (size.y / 2), -size.y / 2, size.x / 2 + (size.y / 2), size.y / 2 }; // �G������ɍU�������͈�
        
        param_.ATTACK_BOX = { size.x / 2 - (size.y / 2), -size.y / 2, size.x / 2 - (size.y), size.y / 2 }; // �G���v���C���[�ɍU������͈�

        const float playerMiddlePos = Game::instance()->player()->transform()->position().x + 75.0f;
        const float notesPosLeft = transform->position().x - (size.x / 2);

        // ���̈ʒu�𒴂�����`��ʒu��ύX
        if (notesPosLeft < playerMiddlePos) {
            collider->setMergin({ playerMiddlePos - notesPosLeft, 0 });
        }
        else {
            collider->setMergin({ 0, 0 });
        }
        break;
    }
    default:

        break;
    }
    
    // debug::setString("scale.x:%f", transform->scale().x);
    // debug::setString("scale.y:%f", transform->scale().y);
}

// �A�Ńm�[�c
Enemy3Behavior::Enemy3Behavior()
{
    param_.ANIME_IDLE = animeEnemy3_1_Idle;
    param_.ANIME_DEAD = animeEnemy3_Dead;

    param_.SIZE = VECTOR2(512, 128);
    param_.SCALE = VECTOR2(1, 1);
    // param_.ATTACK_BOX = { -128 / 2, -128 / 2, 128 / 2, 128 / 2 }; // �G���v���C���[�ɍU������͈�
    param_.HIT_BOX = { -128 / 2, -512 / 2, 128 / 2, 512 / 2}; // �G������ɍU�������͈�

    param_.SPEED        = 8.0f;
    param_.SPEED_Y_MAX  = 8.0f;
    param_.SPEED_X_MAX  = 4.0f;
    param_.HP           = 1;    // �q�b�g�|�C���g
    param_.SCORE        = 50;
    param_.HIT_TIMER    = 50;
    param_.DEAD_TIMER   = 12;
    param_.FLAG_DELETE_COMBO2 = true;
}

// �A�Ńm�[�c
void Enemy3Behavior::enemyParam(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();
    Collider* collider = obj->collider();

    // �o�Ă���ʒu�ɂ���ĉ摜�̌����ƃX�s�[�h�̐ݒ�
    switch (obj->actorComponent()->posType())
    {
    case 0: { // (�ʒu����̎�)
        param_.ANIME_IDLE = animeEnemy3_1_Idle;
        if (obj->enemyState() < 2)
            obj->renderer()->setAnimeData(getParam()->ANIME_IDLE);
        param_.SIZE = VECTOR2(128, 512);
        collider->setSize(param_.SIZE);
        transform->setScale(transform->orgScale());
        const VECTOR2 size = {
            collider->size().x * transform->scale().x,
            collider->size().y * transform->scale().y,
        };
        collider->setSize(size);
        obj->transform()->setSpeedY(param_.SPEED);
        param_.HIT_BOX = { -size.x / 2, -size.y / 2, size.x / 2, size.y / 2 }; // �G������ɍU�������͈�
        param_.ATTACK_BOX = { -size.x / 2, -size.y - (size.x / 6), size.x / 2, -size.y + (size.x / 6) }; // �G���v���C���[�ɍU������͈�
        const float playerHeadPos = Game::instance()->player()->transform()->position().y - Game::instance()->player()->collider()->size().y - 50.0f;
        const float notesPosBottom = transform->position().y + (size.y / 2);

        // ���̈ʒu�𒴂�����`��ʒu��ύX
        if (notesPosBottom > playerHeadPos) {
            collider->setMergin({ 0 ,notesPosBottom - playerHeadPos });
        }
        else {
            collider->setMergin({ 0, 0 });
        }
        break;
    }
    case 1: { // (�ʒu�����̎�)
        param_.ANIME_IDLE = animeEnemy3_2_Idle;
        if (obj->enemyState() < 2)
            obj->renderer()->setAnimeData(getParam()->ANIME_IDLE);
        param_.SIZE = VECTOR2(512, 128);
        collider->setSize(param_.SIZE);
        transform->setScale(transform->orgScale());
        const VECTOR2 size = {
            collider->size().x * transform->scale().x,
            collider->size().y * transform->scale().y,
        };
        collider->setSize(size);
        obj->transform()->setSpeedX(param_.SPEED);
        param_.HIT_BOX = { -size.x / 2, -size.y / 2, size.x / 2, size.y / 2 }; // �G������ɍU�������͈�
        param_.ATTACK_BOX = { -size.x - (size.y / 6), -size.y / 2, -size.x + (size.y / 6), size.y / 2 }; // �G���v���C���[�ɍU������͈�

        const float playerMiddlePos = Game::instance()->player()->transform()->position().x - 75.0f;
        const float notesPosRight = transform->position().x + (size.x / 2);

        // ���̈ʒu�𒴂�����`��ʒu��ύX
        if (notesPosRight > playerMiddlePos) {
            collider->setMergin({ notesPosRight - playerMiddlePos, 0 });
        }
        else {
            collider->setMergin({ 0, 0 });
        }
        break;
    }
    case 2: { // (�ʒu���E�̎�)
        param_.ANIME_IDLE = animeEnemy3_2_Idle;
        if (obj->enemyState() < 2)
            obj->renderer()->setAnimeData(getParam()->ANIME_IDLE);
        param_.SIZE = VECTOR2(512, 128);
        collider->setSize(param_.SIZE);
        transform->setScale(transform->orgScale());
        const VECTOR2 size = {
            collider->size().x * transform->scale().x,
            collider->size().y * transform->scale().y,
        };
        collider->setSize(size);
        obj->transform()->setRotation(ToRadian(180)); // ������ύX
        obj->transform()->setSpeedX(-param_.SPEED);
        param_.HIT_BOX = { -size.x / 2, -size.y / 2, size.x / 2, size.y / 2 }; // �G������ɍU�������͈�
        param_.ATTACK_BOX = { size.x - (size.y / 6), -size.y / 2, size.x + (size.y / 6), size.y / 2 }; // �G���v���C���[�ɍU������͈�

        const float playerMiddlePos = Game::instance()->player()->transform()->position().x + 75.0f;
        const float notesPosLeft = transform->position().x - (size.x / 2);

        // ���̈ʒu�𒴂�����`��ʒu��ύX
        if (notesPosLeft < playerMiddlePos) {
            collider->setMergin({ playerMiddlePos - notesPosLeft, 0 });
        }
        else {
            collider->setMergin({ 0, 0 });
        }
        break;
    }
    default:

        break;
    }
}

// �藠��
Enemy4Behavior::Enemy4Behavior()
{
    param_.ANIME_IDLE = animeEnemy0_Idle;
    param_.ANIME_DEAD = animeEnemy0_Dead;

    param_.SIZE = VECTOR2(150, 150);
    param_.SCALE = VECTOR2(1.5f, 1.5f);
    const VECTOR2 size = {
        param_.SIZE.x * param_.SCALE.x,
        param_.SIZE.y * param_.SCALE.y
    };
    param_.ATTACK_BOX = { -size.x / 2, -size.y / 2, size.x / 2, size.y / 2 }; // �G���v���C���[�ɍU������͈�
    param_.HIT_BOX = { -size.x / 6, -size.y / 6, size.x / 6, size.y / 6 }; // �G������ɍU�������͈�(Perfect)
    param_.HIT_BOX2 = { -size.x / 3, -size.y / 3, size.x / 3, size.y / 3 }; // �G������ɍU�������͈�(Great)
    param_.HIT_BOX3 = { -size.x / 2, -size.y / 2, size.x / 2, size.y / 2 }; // �G������ɍU�������͈�(Good)

    // param_.HIT_BOX2 = { -300 / 4, -300 / 4, 300 / 4, 300 / 4 }; // �G������ɍU�������͈�

    param_.SPEED = 6.0f;
    param_.SPEED_Y_MAX = 6.0f;
    param_.SPEED_X_MAX = 3.0f;
    param_.HP = 1;    // �q�b�g�|�C���g
    param_.SCORE = 300;
    param_.DEAD_TIMER = 18;
}

void Enemy4Behavior::enemyParam(OBJ2D* obj)
{
    // �o�Ă���ʒu�ɂ���ăX�s�[�h��ݒ�
    switch (obj->actorComponent()->posType())
    {
    case 0:// (�ʒu����̎�)
        obj->transform()->setSpeedY(param_.SPEED);
        // ��]����
        obj->transform()->rotate(ToRadian(10));
        break;
    case 1:// (�ʒu�����̎�)
        obj->transform()->setSpeedX(param_.SPEED);
        // ��]����
        obj->transform()->rotate(ToRadian(10));
        break;
    case 2:// (�ʒu���E�̎�)
        obj->transform()->setSpeedX(-param_.SPEED);
        // ��]����
        obj->transform()->rotate(ToRadian(-10));
        break;
    }
}
