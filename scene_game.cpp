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

    // �|�[�Y����
    // if (TRG(0) & PAD_START)
    //     isPaused_ = !isPaused_;         // 0�R���̃X�^�[�g�{�^���������ꂽ��|�[�Y��Ԃ����]
    // if (isPaused_) return;              // ���̎��_�Ń|�[�Y���Ȃ烊�^�[��

    switch (state_)
    {
    case 0:
        //////// �����ݒ� ////////
        timer_ = 0;

        GameLib::setBlendMode(Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

        // �e�N�X�`���̓ǂݍ���
        texture::load(loadTexture);

        // �v���C���[�}�l�[�W���̏����ݒ�
        obj2dManager()->init();

        // �G���Z�b�g
        // setEnemy(obj2dManager(), bg());

        // �v���C���[��ǉ�
        player_ = obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                bg(),
                new ActorComponent,
                nullptr
            ),
            &idlePlayerBehavior, VECTOR2(300, 400));

        // BG�̏����ݒ�
        bg()->init(player_);

        state_++;    // �����ݒ菈���̏I��
        /*fallthrough*/

    case 1:
        //////// �ʏ펞�̏��� ////////

        // �I�u�W�F�N�g�̍X�V
        obj2dManager()->update();

        bg()->update();   // BG�̍X�V

        judge();

        timer_++;

        break;
    }
}

//--------------------------------------------------------------
//  �`�揈��
//--------------------------------------------------------------
void Game::draw()
{
    // ��ʃN���A
    GameLib::clear(VECTOR4(0, 0, 0, 1));

    bg()->drawBack();   // �I�u�W�F�N�g�̕`��

    // �I�u�W�F�N�g�̕`��
    obj2dManager()->draw(bg()->getScrollPos());
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
            if (src == dst) continue;
            if (!dst->behavior()) continue;
            if (!dst->collider()->judgeFlag()) continue;

            if (src->behavior()->attackType() != dst->behavior()->getType())
                continue;

            // �����蔻����s��
            if (src->collider()->hitcheck(dst))
            {
                // ���������ꍇ�̏���
                src->behavior()->hit(src, dst);
            }
        }
    }
}

//******************************************************************************
