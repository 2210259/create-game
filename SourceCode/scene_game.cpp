//******************************************************************************
//
//
//      �Q�[�����
//
//
//******************************************************************************

//------< �C���N���[�h >---------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< �ϐ� >----------------------------------------------------------------
Game Game::instance_;

//--------------------------------------------------------------
//  ����������
//--------------------------------------------------------------
void Game::init()
{
    Scene::init();	    // ���N���X��init���Ă�

    obj2dManager_   = new OBJ2DManager;
    bg_             = new BG;

    isPaused_ = false;   // �|�[�Y�t���O�̏�����
}

//--------------------------------------------------------------
//  �I������
//--------------------------------------------------------------
void Game::deinit()
{
    // �e�}�l�[�W���̉��
    safe_delete(bg_);
    safe_delete(obj2dManager_);

    // �e�N�X�`���̉��
    texture::releaseAll();

    // TODO:���y����Ȃ�������R�����g�A�E�g
    // ���y�̃N���A 
    music::clear();
}

//--------------------------------------------------------------
//  �X�V����
//--------------------------------------------------------------
void Game::update()
{
    using namespace input;

    // �X�e�[�W�Z���N�g
    if ((STATE(0) & PAD_SELECT) && (STATE(0) & PAD_START))
    {
        changeScene(Title::instance()); // �^�C�g���V�[���ɐ؂�ւ���
        return;
    }

     debug::setString("isPaused_%d", isPaused_);

    // �|�[�Y����
     if (TRG(0) & PAD_TRG1)
     {
         //���y���ĊJ
         GameLib::music::resume(0);

         // 0�R���̃X�^�[�g�{�^���������ꂽ��|�[�Y��Ԃ����]
         isPaused_ = !isPaused_;        
     }
     if (isPaused_)
     {
         if (TRG(0) & PAD_START)
         {
            //���艹
            GameLib::sound::play(0,0);

             changeScene(Title::instance());
         }

         if (TRG(0) & PAD_SELECT)
         {
            //���艹
             GameLib::sound::play(0, 0);

             changeScene(Game::instance());
         }

         //���y���~�߂�
         GameLib::music::pause(0);

         return;              // ���̎��_�Ń|�[�Y���Ȃ烊�^�[��
     }

    switch (state_)
    {
    case 0:
        //////// �����ݒ� ////////
        timer_ = 0;

        //BGM�̍Đ�
        GameLib::music::play(0, false);

        GameLib::setBlendMode(Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

        // �e�N�X�`���̓ǂݍ���
        texture::load(loadTexture);

        // �v���C���[�}�l�[�W���̏����ݒ�
        obj2dManager()->init();

        // �G���Z�b�g
        setEnemy(obj2dManager(), bg());

        // �v���C���[��ǉ�
        player_ = obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                bg(),
                new ActorComponent,
                nullptr
            ),
            &idlePlayerBehavior, VECTOR2(640, 700), -1);

        // BG�̏����ݒ�
        bg()->init(player_);

        state_++;    // �����ݒ菈���̏I��
        /*fallthrough*/

    case 1:
        //////// �ʏ펞�̏��� ////////

        // �I�u�W�F�N�g�̍X�V
        obj2dManager()->update();

        bg()->update();   // BG�̍X�V

        // �G���Z�b�g
        setEnemy(obj2dManager(), bg());

        judge();

        if (TRG(0) & PAD_SELECT)
        {
            GameLib::music::stop(0);
            changeScene(Score::instance());
            break;
        }
        timer_++;

        break;
    }
    debug::setString("Combo:%d", combo());
    debug::setString("maxCombo:%d", maxCombo());
   
    debug::setString("stageNo:%d", Game::instance()->stageNo());
    debug::setString("GameTimer:%d", timer_);
}

//--------------------------------------------------------------
//  �`�揈��
//--------------------------------------------------------------
void Game::draw()
{
    // ��ʃN���A
    GameLib::clear(VECTOR4(0.2f, 0.2f, 0.2f, 1));

    bg()->drawBack();   // �I�u�W�F�N�g�̕`��

    // �I�u�W�F�N�g�̕`��
    obj2dManager()->draw(bg()->getScrollPos());

    // �|�[�Y���
    if (isPaused_)
    {
        GameLib::font::textOut(4, "PAUSE",
            { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 4) },
            VECTOR2(5.0f, 5.0f),
            { 1.0f, 1.0f, 1.0f, 1.0f },
            GameLib::TEXT_ALIGN::UPPER_MIDDLE
        );

        GameLib::font::textOut(4, "ENTER : Return To Title",
            { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 2) },
            VECTOR2(2.0f, 2.0f),
            { 1.0f, 1.0f, 1.0f, 1.0f },
            GameLib::TEXT_ALIGN::UPPER_MIDDLE
        );

        GameLib::font::textOut(4, "BACKSPACE : RESTART",
            { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 2 + 100) },
            VECTOR2(2.0f, 2.0f),
            { 1.0f, 1.0f, 1.0f, 1.0f },
            GameLib::TEXT_ALIGN::UPPER_MIDDLE
        );
    }
}

//--------------------------------------------------------------
//  �����蔻��
//--------------------------------------------------------------
void Game::judge()
{
    for (auto& src : *obj2dManager()->getList())
    {
        if (!src->behavior()) continue;
        if (!src->collider()->judgeFlag()) continue;

        for (auto& dst : *obj2dManager()->getList())
        {
            if (!dst->behavior()) break;
            if (src == dst) continue;   // �������g�͂Ƃ΂�
            if (!dst->behavior()) continue;
            if (!dst->collider()->judgeFlag()) continue;

            // src�̍U���^�C�v��dst�̃^�C�v����v���Ȃ����̂��Ƃ΂�
            if (src->behavior()->attackType() != dst->behavior()->getType())
                continue;

            // �����蔻����s��
            if (src->collider()->hitCheck(dst))
            {
                // ���������ꍇ�̏���
                src->behavior()->hit(src, dst);
            }
            else if (src->collider()->hitCheck2(dst))
            {
                src->behavior()->hit2(src, dst);
            }
            else if (src->collider()->hitCheck3(dst))
            {
                src->behavior()->hit3(src, dst);
            }
        }
    }
}

//******************************************************************************