#include "all.h"
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
    {  0,  2,  0, {   0,   0 },  1, },  // �������m�[�c(��)
    {  0,  2,  1, {   0,   0 },  3, },  // �������m�[�c(��)
    {  0,  2,  2, {   0,   0 },  5, },  // �������m�[�c(�E)
    {  0,  3,  0, {   0,   0 },  7, },  // �A�Ńm�[�c(��)
    {  0,  3,  1, {   0,   0 },  9, },  // �A�Ńm�[�c(��)
    {  0,  3,  2, {   0,   0 }, 11, },  // �A�Ńm�[�c(�E)

    {  0,  0,  0, {   0,   0 }, 13, },  // �藠��(��)
    {  0,  0,  1, {   0,   0 }, 14, },  // �藠��(��)
    {  0,  0,  2, {   0,   0 }, 15, },  // �藠��(�E)
    {  0,  1,  0, {   0,   0 }, 16, },  // �N�i�C(��)
    {  0,  1,  1, {   0,   0 }, 17, },  // �N�i�C(��)
    {  0,  1,  2, {   0,   0 }, 18, },  // �N�i�C(�E)

    // {  0,  0,  0, {   0,   0 }, 19, },  // 
    // {  0,  0,  1, {   0,   0 }, 20, },  // 
    // {  0,  0,  2, {   0,   0 }, 21, },  // 
    // {  0,  1,  1, {   0,   0 }, 25, },  // 

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

    //------< Enemy3�̃A�j���f�[�^ >---------------------------------------------
    // �U��
    AnimeData animeEnemy3_Idle[] = {
        { &sprEnemy3_Idle0, 5 },
        { &sprEnemy3_Idle0, 5 },
        { nullptr, -1 },// �I���t���O
    };

    // ���S��
    //AnimeData animeEnemy3_Dead[] = {
    //    { &sprEnemy3_Dead0, 20 },
    //    { &sprEnemy3_Dead1, 10 },
    //    { &sprEnemy3_Dead2, 10 },
    //    { nullptr, -1 },// �I���t���O
    //};

    //------< Enemy4�̃A�j���f�[�^ >---------------------------------------------
    // �U��
    AnimeData animeEnemy4_Idle[] = {
        { &sprEnemy4_Idle0, 5 },
        { &sprEnemy4_Idle0, 5 },
        { nullptr, -1 },// �I���t���O
    };

    // ���S��
    //AnimeData animeEnemy4_Dead[] = {
    //    { &sprEnemy4_Dead0, 20 },
    //    { &sprEnemy4_Dead1, 10 },
    //    { &sprEnemy4_Dead2, 10 },
    //    { nullptr, -1 },// �I���t���O
    //};

    //------< Enemy5�̃A�j���f�[�^ >---------------------------------------------
    // �U��
    AnimeData animeEnemy5_Idle[] = {
        { &sprEnemy5_Idle0, 5 },
        { &sprEnemy5_Idle0, 5 },
        { nullptr, -1 },// �I���t���O
    };

    // ���S��
    //AnimeData animeEnemy5_Dead[] = {
    //    { &sprEnemy5_Dead0, 20 },
    //    { &sprEnemy5_Dead1, 10 },
    //    { &sprEnemy5_Dead2, 10 },
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
        collider->setSize(param_.SIZE);
        const VECTOR2 size = {
            collider->size().x * transform->scale().x,
            collider->size().y * transform->scale().y,
        };
        collider->setSize(size);
        collider->setJudgeFlag(true);
        collider->setJudgeBoxFlag(true);    // �����蔻����s��
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
        // �����ƓG�̈ʒu�̋������v�Z���ăX�s�[�h��ݒ�
    {
        // auto vecP = (Game::instance()->player()->transform()->position() + VECTOR2(0, -75.0f) - obj->transform()->position());
        // float dist = sqrtf(vecP.x * vecP.x + vecP.y * vecP.y);
        // 
        // // �X�s�[�h���v�Z
        // if (!(dist < 1.0f && dist > -1.0f))
        //     obj->transform()->setSpeed(4 * vecP / dist);
        // else
        //     obj->transform()->setSpeed(VECTOR2(0.0f, 0.0f));

        obj->addEnemyState(); // enemyState++
        break;
    }
    case 2:

        break;
    case 3:
        //////// �G�������� ////////
        obj->remove();
        break;
    }
    // debug::setString("size.x:%f", collider->size().x);
    // debug::setString("size.y:%f", collider->size().y);

    debug::setString("speed.x:%f", transform->speed().x);
    debug::setString("speed.y:%f", transform->speed().y);

    // HP��0�ȉ��ł���ΓG������
    if (obj->actorComponent()->hp() <= 0)
        obj->setEnemyState(2);

    transform->addPosition(transform->speed());
}

// �G���v���C���[�ɍU�������Ƃ�����
void BaseEnemyBehavior::hit(OBJ2D* src, OBJ2D* dst)
{
    // false�̏ꍇ���������Ȃ�
    if (src->collider()->judgeFlag() == false) return;
    
    // �W���b�W�t���O���Ȃ���
    src->collider()->setJudgeFlag(false);
    
    // �ʏ�m�[�c���v���C���[�ɓ����������̂�
    if (src->behavior() != &enemy2Behavior && src->behavior() != &enemy3Behavior) {

        // �v���C���[�Ƀ_���[�W��^����
        dst->actorComponent()->damage();

        // �m�[�c����𑗂�
        Game::instance()->setDecision(Game::instance()->MISS);

        // �R���{���Ȃ���
        Game::instance()->deleteCombo();

        // �R���{�̃T�C�Y��ݒ�
        Game::instance()->setComboSize(VECTOR2(2, 2));

        // �~�X�J�E���g 
        Game::instance()->addMissNum();
    }
    // �G������
    src->remove();
}

// �藠��
Enemy0Behavior::Enemy0Behavior()
{
    param_.ANIME_IDLE = animeEnemy0_Idle;
    //param_.ANIME_DEAD = animeEnemy0_Dead;

    param_.SIZE         = VECTOR2(128, 128);
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
    param_.HIT_TIMER = 90;
    param_.DEAD_TIMER = 40;
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
    obj->transform()->rotate(ToRadian(10));
}

// �N�i�C
Enemy1Behavior::Enemy1Behavior()
{
    param_.ANIME_IDLE = animeEnemy1_Idle;
    //param_.ANIME_DEAD = animeEnemy1_Dead;

    param_.SIZE         = VECTOR2(128, 128);
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
    param_.DEAD_TIMER   = 40;
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
    param_.ANIME_IDLE = animeEnemy3_Idle;
    // param_.ANIME_DEAD = animeEnemy3_Dead;

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
    param_.DEAD_TIMER   = 50;
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
        param_.ANIME_IDLE = animeEnemy2_Idle;
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
        param_.HIT_BOX  = { -size.x / 2, size.y / 2 - (size.x / 6), size.x / 2, size.y / 2 + (size.x / 6) }; // �G������ɍU�������͈�
        param_.HIT_BOX2 = { -size.x / 2, size.y / 2 - (size.x / 3), size.x / 2, size.y / 2 + (size.x / 3) }; // �G������ɍU�������͈�
        param_.HIT_BOX3 = { -size.x / 2, size.y / 2 - (size.x / 2), size.x / 2, size.y / 2 + (size.x / 2) }; // �G������ɍU�������͈�
        
        param_.HIT_BOX4 = { -size.x / 2, -size.y / 2 - (size.x / 2), size.x / 2, size.y / 2 + (size.x / 2) }; // �G������ɍU�������͈�
        
        param_.HIT_BOX5 = { -size.x / 2, -size.y / 2 - (size.x / 6), size.x / 2, -size.y / 2 + (size.x / 6) }; // �G������ɍU�������͈�
        param_.HIT_BOX6 = { -size.x / 2, -size.y / 2 - (size.x / 3), size.x / 2, -size.y / 2 + (size.x / 3) }; // �G������ɍU�������͈�
        param_.HIT_BOX7 = { -size.x / 2, -size.y / 2 - (size.x / 2), size.x / 2, -size.y / 2 + (size.x / 2) }; // �G������ɍU�������͈�

        param_.ATTACK_BOX = { -size.x / 2, -size.y - (size.x / 6), size.x / 2, -size.y + (size.x / 6) }; // �G���v���C���[�ɍU������͈�
        break;
    }
    case 1: { // (�ʒu�����̎�)
        param_.ANIME_IDLE = animeEnemy3_Idle;
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
        param_.HIT_BOX  = { size.x / 2 - (size.y / 6), -size.y / 2, size.x / 2 + (size.y / 6), size.y / 2 }; // �G������ɍU�������͈�
        param_.HIT_BOX2 = { size.x / 2 - (size.y / 3), -size.y / 2, size.x / 2 + (size.y / 3), size.y / 2 }; // �G������ɍU�������͈�
        param_.HIT_BOX3 = { size.x / 2 - (size.y / 2), -size.y / 2, size.x / 2 + (size.y / 2), size.y / 2 }; // �G������ɍU�������͈�

        param_.HIT_BOX4 = { -size.x / 2 - (size.y / 2), -size.y / 2,  size.x / 2 + (size.y / 2), size.y / 2 }; // �G������ɍU�������͈�

        param_.HIT_BOX5 = { -size.x / 2 - (size.y / 6), -size.y / 2, -size.x / 2 + (size.y / 6), size.y / 2 }; // �G������ɍU�������͈�
        param_.HIT_BOX6 = { -size.x / 2 - (size.y / 3), -size.y / 2, -size.x / 2 + (size.y / 3), size.y / 2 }; // �G������ɍU�������͈�
        param_.HIT_BOX7 = { -size.x / 2 - (size.y / 2), -size.y / 2, -size.x / 2 + (size.y / 2), size.y / 2 }; // �G������ɍU�������͈�

        param_.ATTACK_BOX = { -size.x - (size.y / 6), -size.y / 2, -size.x + (size.y / 6), size.y / 2 }; // �G���v���C���[�ɍU������͈�

        break;
    }
    case 2: { // (�ʒu���E�̎�)
        param_.ANIME_IDLE = animeEnemy3_Idle;
        obj->renderer()->setAnimeData(getParam()->ANIME_IDLE);
        param_.SIZE = VECTOR2(512, 128);
        collider->setSize(param_.SIZE);
        transform->setScale(transform->orgScale());
        const VECTOR2 size = {
            collider->size().x * transform->scale().x,
            collider->size().y * transform->scale().y,
        };
        collider->setSize(size);
        obj->transform()->setSpeedX(-param_.SPEED);
        param_.HIT_BOX = { -size.x / 2 - (size.y / 6), -size.y / 2, -size.x / 2 + (size.y / 6), size.y / 2 }; // �G������ɍU�������͈�
        param_.HIT_BOX2 = { -size.x / 2 - (size.y / 3), -size.y / 2, -size.x / 2 + (size.y / 3), size.y / 2 }; // �G������ɍU�������͈�
        param_.HIT_BOX3 = { -size.x / 2 - (size.y / 2), -size.y / 2, -size.x / 2 + (size.y / 2), size.y / 2 }; // �G������ɍU�������͈�

        param_.HIT_BOX4 = { -size.x / 2 - (size.y / 2), -size.y / 2,  size.x / 2 + (size.y / 2), size.y / 2 }; // �G������ɍU�������͈�

        param_.HIT_BOX5 = { size.x / 2 - (size.y / 6), -size.y / 2, size.x / 2 + (size.y / 6), size.y / 2 }; // �G������ɍU�������͈�
        param_.HIT_BOX6 = { size.x / 2 - (size.y / 3), -size.y / 2, size.x / 2 + (size.y / 3), size.y / 2 }; // �G������ɍU�������͈�
        param_.HIT_BOX7 = { size.x / 2 - (size.y / 2), -size.y / 2, size.x / 2 + (size.y / 2), size.y / 2 }; // �G������ɍU�������͈�
        
        param_.ATTACK_BOX = { size.x - (size.y / 6), -size.y / 2, size.x + (size.y / 6), size.y / 2 }; // �G���v���C���[�ɍU������͈�

        break;
    }
    default:

        break;
    }
    debug::setString("scale.x:%f", transform->scale().x);
    debug::setString("scale.y:%f", transform->scale().y);
}

// �A�Ńm�[�c
Enemy3Behavior::Enemy3Behavior()
{
    param_.ANIME_IDLE = animeEnemy5_Idle;
    //param_.ANIME_DEAD = animeEnemy4_Dead;

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
    param_.DEAD_TIMER   = 50;
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
        param_.ANIME_IDLE = animeEnemy4_Idle;
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

        break;
    }
    case 1: { // (�ʒu�����̎�)
        param_.ANIME_IDLE = animeEnemy5_Idle;
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
        obj->transform()->setRotation(ToRadian(180));
        param_.HIT_BOX = { -size.x / 2, -size.y / 2, size.x / 2, size.y / 2 }; // �G������ɍU�������͈�
        param_.ATTACK_BOX = { -size.x - (size.y / 6), -size.y / 2, -size.x + (size.y / 6), size.y / 2 }; // �G���v���C���[�ɍU������͈�

        break;
    }
    case 2: { // (�ʒu���E�̎�)
        param_.ANIME_IDLE = animeEnemy5_Idle;
        obj->renderer()->setAnimeData(getParam()->ANIME_IDLE);
        param_.SIZE = VECTOR2(512, 128);
        collider->setSize(param_.SIZE);
        transform->setScale(transform->orgScale());
        const VECTOR2 size = {
            collider->size().x * transform->scale().x,
            collider->size().y * transform->scale().y,
        };
        collider->setSize(size);
        obj->transform()->setRotation(ToRadian(0));
        obj->transform()->setSpeedX(-param_.SPEED);
        param_.HIT_BOX = { -size.x / 2, -size.y / 2, size.x / 2, size.y / 2 }; // �G������ɍU�������͈�
        param_.ATTACK_BOX = { size.x - (size.y / 6), -size.y / 2, size.x + (size.y / 6), size.y / 2 }; // �G���v���C���[�ɍU������͈�

        break;
    }
    default:

        break;
    }
}