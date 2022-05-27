//******************************************************************************
//
//
//      �Q�[�����
//
//
//******************************************************************************

//------< �C���N���[�h >---------------------------------------------------------
#include "all.h"
#include <sstream>
#include <iomanip>

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
    // music::clear();
}

//--------------------------------------------------------------
//  �X�V����
//--------------------------------------------------------------
void Game::update()
{
    using namespace input;

     debug::setString("isPaused_%d", isPaused_);

    // �|�[�Y����
     if (TRG(0) & PAD_TRG1 && title_push_flg == false && restart_push_flg == false)
     {
         //���y���ĊJ
         GameLib::music::resume(stageNo_);

         // 0�R���̃X�^�[�g�{�^���������ꂽ��|�[�Y��Ԃ����]
         isPaused_ = !isPaused_;        
     }

     //�|�[�Y��
     if (isPaused_)
     {
         if (title_push_flg == false && restart_push_flg == false)
         {
             // A�L�[�������ꂽ��
             if (TRG(0) & PAD_RIGHT) {
                 if (pause_num_ > 0)
                 {
                     pause_num_--;
                 }
             }

             //�@D�L�[�������ꂽ��
             if (TRG(0) & PAD_LEFT) {
                 if (pause_num_ < 2)
                 {
                     pause_num_++;
                 }
             }
         }
         //���y���~�߂�
         GameLib::music::pause(stageNo_);

         //�����̃��l���O�`�P�̊Ԃŉ��������鏈��
         switch (pause_alpha_num_)
         {
         case 0:
             pause_alpha_ -= 0.03f;
             if (pause_alpha_ <= 0)   pause_alpha_num_++;
             break;

         case 1:
             pause_alpha_ += 0.03f;
             if (pause_alpha_ >= 1)   pause_alpha_num_--;
             break;
         }

         //�P(�ĊJ)��I��ł���Ƃ�
         if (pause_num_ == 1 && title_push_flg == false && restart_push_flg == false)
         {
             if (TRG(0) & PAD_START)
             {
                 //music::play(8, false);
                 isPaused_ = !isPaused_;
             }

         }
         
         //�Q(�Ē���)��I��ł���Ƃ�
         if (pause_num_ == 2 && title_push_flg == false && restart_push_flg == false)
         {
             if (TRG(0) & PAD_START)
             {
                 music::play(8,false);
                 restart_push_flg = true;
             }
         }

         //�O(�����Ƃ��)��I��ł���Ƃ�
         if (pause_num_ == 0 && title_push_flg == false && restart_push_flg == false) 
         {
             if (TRG(0) & PAD_START)
             {
                 music::play(8,false);
                 title_push_flg = true;
             }
         }

         //�^�C�g���ւ�I�񂾎�
         if (title_push_flg)
         {
             for (int i = 0; i < 11; i++)
             {
                 shuriken_Pos_[i].x -= 20;
                 shuriken_Angle_++;
             }

             if (shuriken_Pos_[9].x <= -500)
             {
                 changeScene(Title::instance());
             }
         }

         //�Ē����I�񂾎�
         if (restart_push_flg)
         {
             if (G_L_Fusuma_Pos_.x <= 960 && G_R_Fusuma_Pos_.x >= (960 * 1.5f))
             {
                 G_L_Fusuma_Pos_.x += 30;
                 G_R_Fusuma_Pos_.x -= 30;
             }

             if (G_L_Fusuma_Pos_.x >= 480 && G_R_Fusuma_Pos_.x <= (960 * 1.5f))
             {
                 G_L_Fusuma_Pos_.x = 480;
                 G_R_Fusuma_Pos_.x = (960 * 1.5f);

                 if (Fusuma_timer_ > 60)
                 {
                     Fusuma_timer_ = 0;
                     changeScene(Game::instance());
                 }
                 Fusuma_timer_++;
             }
         }

         return;              // ���̎��_�Ń|�[�Y���Ȃ烊�^�[��
     }

    switch (state_)
    {
    case 0:
        //////// �����ݒ� ////////
        
        combo2Timer_ = 0;    // �R���{�^�C�}�[
        scoreTimer_  = 0;    // �X�R�A�^�C�}�[
        notesTimer_  = 0;    // �m�[�c�^�C�}�[
        score_       = 0;    // �X�R�A
        combo_       = 0;    // �R���{��
        combo2_      = 0;    // �R���{��(�A��)
        maxCombo_    = 0;    // �ő�R���{��

        // HP�o�[�̐ݒ�
        hpPos01      = { 1290, 10 };         // HP�o�[�̈ʒu
        hpTexPos01   = { 0,  0 };            // HP�o�[�̑傫��
        hpColor01    = { 1, 1, 1, 1.0f };    // HP�o�[�̐F

        hpPos02      = { 1390,  80 };        // HP�o�[�̈ʒu
        hpSize02     = { 0,  70 };           // HP�o�[�̑傫��
        hpColor02    = { 1, 0, 0, 0.8f };    // HP�o�[�̐F

        comboSize    = { 1.5f, 1.5f };       // �R���{�̑傫��
        comboColor   = { 1, 1, 1, 1 };       // �R���{�̐F
        combo2Pos    = { 1890, 360 };        // �R���{2�̈ʒu
        combo2Size   = { 1.5f, 1.5f };       // �R���{2�̑傫��             
        combo2Color  = { 1, 1, 1, 0 };       // �R���{2�̐F

        scorePos     = { 10, 140 };          // �X�R�A�̈ʒu
        scoreSize    = { 1.5f, 1.5f };       // �X�R�A�̑傫��             
        scoreColor   = { 1, 1, 1, 0 };       // �X�R�A�̐F
        
        notesPos     = { 1890, 180 };        // �m�[�c�̈ʒu
        notesSize    = { 1.5f, 1.5f };       // �m�[�c�̑傫��             
        notesColor   = { 1, 1, 1, 0 };       // �m�[�c�̐F

        t_StartPos   = { BG::CLIENT_W / 2, -500 }; // �����̈ʒu
        t_StartSize  = { 600,  200 };              // �����̑傫��
        t_StartScale = { 8.0f, 8.0f };             // �����̑傫��             
        t_StartColor = { 1, 1, 1, 1 };             // �����̐F

        t_EndPos   = { BG::CLIENT_W / 2, -500 };   // �����̈ʒu
        t_EndSize  = {  600,  200 };               // �����̑傫��
        t_EndScale = { 8.0f, 8.0f };               // �����̑傫��             
        t_EndColor = { 1, 1, 1, 1 };               // �����̐F

        t_FullComboPos    = { -BG::CLIENT_W / 2, BG::CLIENT_H / 2 }; // �����̈ʒu
        t_FullComboSize   = { 600,  200 };                           // �����̑傫��
        t_FullComboScale  = { 2.0f, 2.0f };                          // �����̑傫��             
        t_FullComboColor  = { 1, 1, 1, 1 };                          // �����̐F

        perfectNum_ = 0; // �p�[�t�F�N�g��  
        greatNum_   = 0; // �O���C�g�� 
        goodNum_    = 0; // �O�b�h�� 
        missNum_    = 0; // �~�X��

        pause_num_       = 0; // �|�[�Y���̑I��p
        pause_alpha_     = 0; // �|�[�Y���ɕ\������e�L�X�g�̃��l
        pause_alpha_num_ = 0; // ���l���O�`�P�܂ŉ��������邽�߂̒l
        HPAnimeTimer_    = 0;

        playerAlive_   = true; //�������Ă��邩�ǂ���
        notesMaskFlag_ = false;

        G_L_Fusuma_Pos_ = { 960 / 2,540 };     // �����̈ʒu�̏�����
        G_R_Fusuma_Pos_ = { (960 * 2) - (960 / 2) , 540 }; // �E���̈ʒu�̏�����

        G_Fusuma_timer_ = 0;                   //��������܂ł̎��Ԃ̏�����

        for (int i = 0; i < 11; i++)           //�藠���ʒu�̏�����
        {
            shuriken_Pos_[i].x = static_cast<float>(2400 + (128 * i));
            shuriken_Pos_[i].y = static_cast<float>(128 * i);
        }

        shuriken_Angle_ = 0;                   //�藠���̊p�x�̏�����

        title_push_flg = false;                // �^�C�g���ւ�I�񂾎��̃t���O�̏�����
        restart_push_flg = false;              // �Ē����I�񂾎��̃t���O�̏�����

        tutorial_pos_ = { -300,420 };          // �`���[�g���A���摜�̏����ʒu  

        tutorial_State_ = 0;                   // �`���[�g���A���X�e�[�g

        tutorial_timer_ = 0;                   // �`���[�g���A���摜�̕\�����Ԃ̏�����

        setStageNo(Select::instance()->stageNum() - 1);

        GameLib::setBlendMode(Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

        // �e�N�X�`���̓ǂݍ���
        texture::load(loadTexture);

        // �v���C���[�}�l�[�W���̏����ݒ�
        obj2dManager()->init();

        // �G���Z�b�g
        setEnemy(obj2dManager(), bg());

        // BGM�̍Đ�
        music::play(stageNo_, false);
        music::pause(stageNo_);

        // �v���C���[��ǉ�
        player_ = obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                bg(),
                new ActorComponent,
                nullptr,
                nullptr
            ),
            &idlePlayerBehavior, VECTOR2(BG::WINDOW_W / 2, BG::WINDOW_H - (BG::WINDOW_H / 18)), -1, {});

        player_->renderer()->setColor(VECTOR4(1, 1, 1, 0));

        // BG�̏����ݒ�
        bg()->init(player_);

        //���J��
        GameLib::music::play(11, false);

        state_++;    // �����ݒ菈���̏I��
        /*fallthrough*/

    case 1:
        //////// �����J���鏈�� ////////
        // ���̏���
        if (G_L_Fusuma_Pos_.x > -960 / 2 && G_R_Fusuma_Pos_.x < (960 * 2) + (960 / 2) && timer_ > 3)
        {
            G_L_Fusuma_Pos_.x -= 30;
            G_R_Fusuma_Pos_.x += 30;
        }
        // ������ʊO�Ɉړ�
        if (G_L_Fusuma_Pos_.x <= -960 / 2 && G_R_Fusuma_Pos_.x >= (960 * 2) + (960 / 2))
        {
            G_L_Fusuma_Pos_.x = -960 / 2;
            G_R_Fusuma_Pos_.x = (960 * 2) + (960 / 2);

            // �J�n���o���o��
            if (timer_ > 110) {
                if (t_StartScale.x > 1.5f) {
                    t_StartScale -= { 0.25f, 0.25f };
                    t_StartPos.y += 30;
                }

                // case���������
                if (t_StartScale.x <= 1.5f) {
                    // ���ʉ�
                    music::play(8, false);

                    timer_ = 0;
                    state_++;
                    break;
                }
            }
        }
        // �I�u�W�F�N�g�̍X�V
        obj2dManager()->update();

        // BG�̍X�V
        bg()->update();

        // HP�o�[�̃A�j���[�V����
        AnimetionHP();

        if (player_->renderer()->color().w < 1) {
            player_->renderer()->addColorW(0.02f);
        }
        timer_++;
        break;
    case 2:
        //////// �ʏ펞�̏��� ////////
        
        // �J���̃A���t�@�l�������� 
        if(timer_ > 30 && t_StartColor.w > 0)
            t_StartColor.w -= 0.02f;

        //�P�b��ɉ��y���J�n
        if (timer_ > 60) {
            music::resume(stageNo_);
        }

        // �I�u�W�F�N�g�̍X�V
        obj2dManager()->update();

        // BG�̍X�V
        bg()->update();  
        
        // �G���Z�b�g
        setEnemy(obj2dManager(), bg());

        // �����蔻��
        judge();

        // �X�R�A�̌v�Z
        calcScore();

        // �R���{�̌v�Z
        calcCombo();

        // �m�[�c����̍X�V
        decisionJudge();

        // HP�o�[�̃A�j���[�V����
        AnimetionHP();

        // �Q�[���̏I�����Ԃ̒���
        if ((stageNo_ == 0 && timer_ > 5640) || (stageNo_ == 1 && timer_ > 6500)) {
            setPlayerAlive(true);
            GameLib::music::stop(stageNo_);
            state_++;
            break;
        }

        // �v���C���[�̗̑͂��Ȃ��Ȃ�����
        if (player()->actorComponent()->hp() < 1) {
            setPlayerAlive(false);
            GameLib::music::stop(stageNo_);
            state_++;
            break;
        }

        timer_++;
        break;
    case 3:
        //////// �m�[�c���S�ė��ꂽ��AHP��0�ɂȂ������̏��� ////////
        
        // �I�u�W�F�N�g�̍X�V
        obj2dManager()->update();

        // BG�̍X�V
        bg()->update();  

        // HP�o�[�̃A�j���[�V����
        AnimetionHP();

        // �X�R�A�̌v�Z
        calcScore();

        // �R���{�̌v�Z
        calcCombo();

        // �m�[�c����̍X�V
        decisionJudge();

        // �~�߂鉉�o���o��
        if (t_EndScale.x > 1.5f) {
            t_EndScale -= { 0.25f, 0.25f };
            t_EndPos.y += 30;
        }

        // case���������
        if(t_EndScale.x <= 1.5f) {
            // ���ʉ�
            music::play(8, false);

            timer_ = 0;
            state_++;
            break;
        }
        break;
    case 4:
        //////// �m�[�c���S�ė��ꂽ��AHP��0�ɂȂ������̏��� ////////

        // �I�u�W�F�N�g�̍X�V
        obj2dManager()->update();

        // BG�̍X�V
        bg()->update();

        // HP�o�[�̃A�j���[�V����
        AnimetionHP();

        // �X�R�A�̌v�Z
        calcScore();

        // �R���{�̌v�Z
        calcCombo();

        // �m�[�c����̍X�V
        decisionJudge();

        // ���̃A���t�@�l�������� 
        if (timer_ > 60 && t_EndColor.w > 0)
            t_EndColor.w -= 0.02f;

        // �~�X�̗L���AHP�ɂ���ď�����ύX
        if (timer_ > 120) {
            // �~�X���Ȃ��{�v���C���[�������Ă��Ԃł���Ή��o��ǉ�
            if (missNum_ <= 0 && player()->actorComponent()->hp() > 0){
            
            //���J��
            GameLib::music::play(11, false);

            state_++;
            }
            // �X�R�A��ʂɂ��̂܂ܑJ��
            else { 
                //���J��
                GameLib::music::play(11, false);

                state_ = 6;
            }
        }
        timer_++;
        break;
    case 5:
        //////// �~�X���Ȃ��Ƃ��̏��� ////////
        // �I�u�W�F�N�g�̍X�V
        obj2dManager()->update();

        // BG�̍X�V
        bg()->update();

        // HP�o�[�̃A�j���[�V����
        AnimetionHP();

        // ���������Ɉړ�
        t_FullComboPos.x += 30;
        
        // �^�񒆂Ɏ~�܂�悤�ɐݒ�
        if (t_FullComboPos.x > BG::CLIENT_W / 2) {
            t_FullComboPos.x = BG::CLIENT_W / 2;

            //�t���R���{��
            GameLib::music::play(10,false);

            // �^�񒆂ɂƂ܂�����G�t�F�N�g���o��
            if (timer_ % 6 == 0) {
                setEffect(Game::instance()->obj2dManager(), Game::instance()->bg(), &notesEffect0Behavior, { static_cast<float>(rand() % BG::WINDOW_W), static_cast<float>(rand() % BG::WINDOW_H) });
                setEffect(Game::instance()->obj2dManager(), Game::instance()->bg(), &notesEffect1Behavior, { static_cast<float>(rand() % BG::WINDOW_W), static_cast<float>(rand() % BG::WINDOW_H) });
                setEffect(Game::instance()->obj2dManager(), Game::instance()->bg(), &notesEffect2Behavior, { static_cast<float>(rand() % BG::WINDOW_W), static_cast<float>(rand() % BG::WINDOW_H) });
            }
            
            // �X�R�A��ʂɑJ��
            if (TRG(0) & PAD_START || timer_ > 1000) {
            
            // ���J��
            GameLib::music::play(11, false);
            
            state_++;
            }
        }
        timer_++;
        break;
    case 6:
        //////// �����܂鏈�� ////////
        
        // �I�u�W�F�N�g�̍X�V
        obj2dManager()->update();

        // BG�̍X�V
        bg()->update();

        // HP�o�[�̃A�j���[�V����
        AnimetionHP();

        if (G_L_Fusuma_Pos_.x <= 960 && G_R_Fusuma_Pos_.x >= (960 * 1.5f)) {
            G_L_Fusuma_Pos_.x += 30;
            G_R_Fusuma_Pos_.x -= 30;
        }

        if (G_L_Fusuma_Pos_.x >= 480 && G_R_Fusuma_Pos_.x <= (960 * 1.5f)) {
            G_L_Fusuma_Pos_.x = 480;
            G_R_Fusuma_Pos_.x = (960 * 1.5f);
            state_++;
        }
        break;
    case 7:
        //////// �X�R�A��ʂɑJ�� ////////
        // BGM���~�߂�
        music::stop(stageNo_);

        changeScene(Score::instance());
        break;

    }
    // debug::setString("Combo:%d", combo());
    // debug::setString("maxCombo:%d", maxCombo());
    
    // debug::setString("stageNo:%d", Game::instance()->stageNo());
    // debug::setString("GameTimer:%d", timer_);
}

//--------------------------------------------------------------
//  �`�揈��
//--------------------------------------------------------------
void Game::draw()
{
    // ��ʃN���A
    GameLib::clear(VECTOR4(0.5f, 0.5f, 0.5f, 1));

    // �X�e���V�����[�h�F�ʏ�
    DepthStencil::instance().set(DepthStencil::MODE::NONE);

    // �w�i�̕`��
    bg()->drawBack();

    // �ʏ�m�[�c�̕`��
    obj2dManager()->draw(bg()->getScrollPos());

    // �������m�[�c(��)�ƘA���m�[�c(��)�̕`��
    {
        // �X�e���V�����[�h�F�}�X�N����
        DepthStencil::instance().set(DepthStencil::MODE::MASK);

        // �l�p�`
        if (Game::instance()->player()->actorComponent()->direction() == Game::instance()->player()->actorComponent()->LEFT
            && notesMaskFlag_ == true) {
            GameLib::primitive::rect(
                { player()->transform()->position().x - player()->collider()->size().x,
                  player()->transform()->position().y - player()->collider()->size().y },
                { BG::CLIENT_W, player()->collider()->size().y },
                { 0, 0 },
                ToRadian(0),
                { 0.0f, 0.0f, 0.0f, 0.0f }
            );
        }
        // �X�e���V�����[�h�F�}�X�N�ȊO�ɕ`��
        DepthStencil::instance().set(DepthStencil::MODE::EXCLUSIVE);

        // �������m�[�c(��)�ƘA���m�[�c(��)�̕`��
        obj2dManager()->draw3(bg()->getScrollPos());
    }

    // �������m�[�c(�E)�ƘA���m�[�c(�E)�̕`��
    {
        // �X�e���V�����[�h�F�}�X�N����
        DepthStencil::instance().set(DepthStencil::MODE::MASK);

        // �l�p�`
        if (Game::instance()->player()->actorComponent()->direction() == Game::instance()->player()->actorComponent()->RIGHT
            && notesMaskFlag_ == true) {
            GameLib::primitive::rect(
                { 0,
                  player()->transform()->position().y - player()->collider()->size().y },
                { player()->transform()->position().x + player()->collider()->size().x, player()->collider()->size().y },
                { 0, 0 },
                ToRadian(0),
                { 0.0f, 0.0f, 0.0f, 0.0f }
            );
        }

        // �X�e���V�����[�h�F�}�X�N�ȊO�ɕ`��
        DepthStencil::instance().set(DepthStencil::MODE::EXCLUSIVE);

        // �������m�[�c(�E)�ƘA���m�[�c(�E)�̕`��
        obj2dManager()->draw4(bg()->getScrollPos());
    }

    // �������m�[�c(��)�ƘA���m�[�c(��)�̕`��
    {
        // �X�e���V�����[�h�F�}�X�N����
        DepthStencil::instance().set(DepthStencil::MODE::MASK);

        // �l�p�`
        if (Game::instance()->player()->actorComponent()->direction() == Game::instance()->player()->actorComponent()->UP
            && notesMaskFlag_ == true) {
            GameLib::primitive::rect(
                { player()->transform()->position().x - (player()->collider()->size().x / 2),
                player()->transform()->position().y - (player()->collider()->size().y * 3 / 2) },
                { player()->collider()->size().x, player()->collider()->size().y * 2 },
                { 0, 0 },
                ToRadian(0),
                { 0.0f, 0.0f, 0.0f, 0.0f }
            );
        }
        // �X�e���V�����[�h�F�}�X�N�ȊO�ɕ`��
        DepthStencil::instance().set(DepthStencil::MODE::EXCLUSIVE);
        
        // �������m�[�c(��)�ƘA���m�[�c(��)�̕`��
        obj2dManager()->draw2(bg()->getScrollPos());
    }

    // �X�e���V�����[�h�F�ʏ�
    DepthStencil::instance().set(DepthStencil::MODE::NONE);

    // �v���C���[�̕`��
    if ((player_->actorComponent()->playerHitTimer() >= 1 && player_->actorComponent()->playerHitTimer() <= 6) || 
        (player_->actorComponent()->playerHitTimer() >= 13 && player_->actorComponent()->playerHitTimer() <= 18)){
        GameLib::setBlendMode(Blender::BS_ADD);   // �ʏ�̃A���t�@����
    }
    
    obj2dManager()->drawPlayer(bg()->getScrollPos());

    GameLib::setBlendMode(Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

    // �G�t�F�N�g�̕`��
    obj2dManager()->drawEffect(bg()->getScrollPos());

    // HP�o�[�̕`��
    {
        if (player()->actorComponent()->hp() >= 0) {
            GameLib::setBlendMode(Blender::BS_ALPHA);   // �ʏ�̃A���t�@����
            // �v���C���[���_���[�W��H������Ƃ��_�ł�����
            if ((player_->actorComponent()->playerHitTimer() >= 1 && player_->actorComponent()->playerHitTimer() <= 6) ||
                (player_->actorComponent()->playerHitTimer() >= 13 && player_->actorComponent()->playerHitTimer() <= 18)) {
                GameLib::setBlendMode(Blender::BS_MULTIPLY);   // �A���t�@����
            }

            primitive::rect(hpPos02,
                { hpSize02.x / player()->actorComponent()->maxHP() * player()->actorComponent()->hp(), hpSize02.y },
                { 0, 0 }, 0, hpColor02);
        }

        GameLib::setBlendMode(Blender::BS_ADD);   // �ʏ�̃A���t�@����

        texture::begin(TEXNO::HP_BAR);
        texture::draw(TEXNO::HP_BAR, hpPos01, { 1, 1 }, hpTexPos01, { 600, 150 });
        texture::end(TEXNO::HP_BAR);
        GameLib::setBlendMode(Blender::BS_ALPHA);   // �ʏ�̃A���t�@����
    }

    // �X�R�A,�R���{���̕`��
    scoreDraw();
    comboDraw();

    // �m�[�c����̕`��
    decisionDraw();

    // �J���̕����`��
    if (state_ == 1 || state_ == 2) {
        texture::begin(TEXNO::T_START);
        texture::draw(TEXNO::T_START, t_StartPos.x, t_StartPos.y, t_StartScale.x, t_StartScale.y,
            0, 0, t_StartSize.x, t_StartSize.y, t_StartSize.x / 2, t_StartSize.y / 2, 
            0, t_StartColor.x, t_StartColor.y, t_StartColor.z, t_StartColor.w);
        texture::end(TEXNO::T_START);
    }

    // ���̕����`��
    if (state_ == 3 || state_ == 4 || state_ == 5) {
        texture::begin(TEXNO::T_END);
        texture::draw(TEXNO::T_END, t_EndPos.x, t_EndPos.y, t_EndScale.x, t_EndScale.y,
            0, 0, t_EndSize.x, t_EndSize.y, t_EndSize.x / 2, t_EndSize.y / 2,
            0, t_EndColor.x, t_EndColor.y, t_EndColor.z, t_EndColor.w);
        texture::end(TEXNO::T_END);
    }

    // �t���R���{�̕����̕`��
    if (state_ == 5) {
        // �l�p�`
        GameLib::primitive::rect(
            { t_FullComboPos.x, t_FullComboPos.y },
            { BG::CLIENT_W, BG::CLIENT_H / 5},
            { BG::CLIENT_W / 2, BG::CLIENT_H / 10 },
            ToRadian(0),
            { 0.0f, 0.0f, 0.0f, 0.5f }
        );
        
        texture::begin(TEXNO::T_FULLCOMBO);
        texture::draw(TEXNO::T_FULLCOMBO, t_FullComboPos.x, t_FullComboPos.y, t_FullComboScale.x, t_FullComboScale.y,
            0, 0, t_FullComboSize.x, t_FullComboSize.y, t_FullComboSize.x / 2, t_FullComboSize.y / 2);
        texture::end(TEXNO::T_FULLCOMBO);
    }

    // ��������̕`��
    operationDraw();

    // �|�[�Y���
    if (isPaused_)
    {
        // �w�i�������Â�����
         GameLib::primitive::rect({ 0, 0 }, 
         { GameLib::window::getWidth(), GameLib::window::getHeight() },
         { 0, 0 }, 0, { 0, 0, 0, 0.3f }
         );

        GameLib::font::textOut(4, "PAUSE",
            { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 4) },
            VECTOR2(5.0f, 5.0f),
            { 1.0f, 1.0f, 1.0f, 1.0f },
            GameLib::TEXT_ALIGN::UPPER_MIDDLE
        );

        // �ĊJ��I��ł���Ƃ�
        if (pause_num_ == 1)
        {
            // "�ĊJ"�̕`��
            sprContinue_.draw(
                { GameLib::window::getWidth() / 2 , GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,pause_alpha_ }
            );

            // "�Ē���"�̕����̕`��
            sprRestart_.draw(
                { GameLib::window::getWidth() / 2 - GameLib::window::getWidth() / 3, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,1 }
            );

            // "�����Ƃ��"�̕����̕`��
            sprTotitle_.draw(
                { GameLib::window::getWidth() / 2 + GameLib::window::getWidth() / 3, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,1 }
            );
        }
        
        // �����Ƃ�ւ�I��ł���Ƃ�
        if (pause_num_ == 2)
        {
            // "�ĊJ"�̕`��
            sprContinue_.draw(
                { GameLib::window::getWidth() / 2 , GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,1 }
            );

            // �ʒu�̕ύX
            // "�Ē���"�̕����̕`��
            sprRestart_.draw(
                { GameLib::window::getWidth() / 2 - GameLib::window::getWidth() / 3, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,pause_alpha_ }
            );

            // �ʒu�̕ύX
            // "�����Ƃ��"�̕����̕`��
            sprTotitle_.draw(
                { GameLib::window::getWidth() / 2 + GameLib::window::getWidth() / 3, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,1 }
            );
        }
        
        // �����Ƃ�ւ�I��ł���Ƃ�
        if (pause_num_ == 0)
        {
            // "�ĊJ"�̕`��
            sprContinue_.draw(
                { GameLib::window::getWidth() / 2 , GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,1 }
            );

            // �ʒu�̕ύX
            //"�Ē���"�̕����̕`��
            sprRestart_.draw(
                { GameLib::window::getWidth() / 2 - GameLib::window::getWidth() / 3, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,1 }
            );
            //�ʒu�̕ύX
            //"�����Ƃ��"�̕����̕`��
            sprTotitle_.draw(
                { GameLib::window::getWidth() / 2 + GameLib::window::getWidth() / 3, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,pause_alpha_ }
            );
        }
    }

    // �U�������蔻��
    if(state_ < 3){
        // ��̍U���͈͕\��
        // primitive::rect(BG::WINDOW_W / 2 - 15, player()->transform()->position().y - (player()->collider()->size().y * 3 / 2) - 15,
        //     30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.2f);

        primitive::circle(BG::WINDOW_W / 2, player()->transform()->position().y - (player()->collider()->size().y * 3 / 2),
            15, 1, 1, ToRadian(0), 1.0f, 1.0f, 1.5f, 0.2f);

        // ���̍U���͈͕\��
        // primitive::rect(player()->transform()->position().x - player()->collider()->size().x - 15, player()->transform()->position().y - player()->collider()->size().y / 2 - 15,
        //     30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.2f);

        primitive::circle(player()->transform()->position().x - player()->collider()->size().x, player()->transform()->position().y - player()->collider()->size().y / 2,
            15, 1, 1, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.2f);

        // �E�̍U���͈͕\��
        // primitive::rect(player()->transform()->position().x + player()->collider()->size().x - 15, player()->transform()->position().y - player()->collider()->size().y / 2 - 15,
        //     30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.2f);

        primitive::circle(player()->transform()->position().x + player()->collider()->size().x, player()->transform()->position().y - player()->collider()->size().y / 2,
            15, 1, 1, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.2f);

        // �v���C���[����������Ă�����
        if (player()->actorComponent()->direction() == player()->actorComponent()->UP) {
            // ��̍U���͈͕\��
            // primitive::rect(BG::WINDOW_W / 2 - 15, player()->transform()->position().y - (player()->collider()->size().y * 3 / 2) - 15,
            //     30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.6f);

            primitive::circle(BG::WINDOW_W / 2, player()->transform()->position().y - (player()->collider()->size().y * 3 / 2),
                15, 1, 1, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.6f);
        }
        // �v���C���[�����������Ă�����
        if (player()->actorComponent()->direction() == player()->actorComponent()->LEFT) {
            // ���̍U���͈͕\��
            // primitive::rect(player()->transform()->position().x - player()->collider()->size().x - 15, player()->transform()->position().y - player()->collider()->size().y / 2 - 15,
            //     30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.6f);

            primitive::circle(player()->transform()->position().x - player()->collider()->size().x, player()->transform()->position().y - player()->collider()->size().y / 2,
                15, 1, 1, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.6f);
        }
        // �v���C���[���E�������Ă�����
        if (player()->actorComponent()->direction() == player()->actorComponent()->RIGHT)
        {
            // �E�̍U���͈͕\��
            // primitive::rect(player()->transform()->position().x + player()->collider()->size().x - 15, player()->transform()->position().y - player()->collider()->size().y / 2 - 15,
            //     30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.6f);

            primitive::circle(player()->transform()->position().x + player()->collider()->size().x, player()->transform()->position().y - player()->collider()->size().y / 2,
                15, 1, 1, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.6f);
        }
    }

    //���̕`��
    sprL_Fusuma_.draw(G_L_Fusuma_Pos_);
    sprR_Fusuma_.draw(G_R_Fusuma_Pos_);

    //�藠���̕`��
    for (int i = 0; i < 11; i++)
    {
        sprShuriken_.draw(
            shuriken_Pos_[i], { 1.0f,1.0f },
            ToRadian(shuriken_Angle_)
        );
    }

    //�藠���̎l�p
    for (int i = 0; i < 11; i++) {
        primitive::rect({ 2400 , shuriken_Pos_[i].y + 64 }, { shuriken_Pos_[i].x - 2400 + 64 , 128 }, { 0,128 }, ToRadian(0), { 0.0f,0.0f,0.0f,1.0f });
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
            if (!src->behavior()) break;

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
            else if (src->collider()->hitCheck5(dst))
            {
                src->behavior()->hit5(src, dst);
            }
            else if (src->collider()->hitCheck6(dst))
            {
                src->behavior()->hit6(src, dst);
            }
            else if (src->collider()->hitCheck7(dst))
            {
                src->behavior()->hit7(src, dst);
            }
            // ����������
            if (src->collider()->hitCheck4(dst))
            {
                src->behavior()->hit4(src, dst);
            }
        }
    }
}

//--------------------------------------------------------------
//  UI
//--------------------------------------------------------------

void Game::calcCombo()
{
    // �ő�R���{�̍X�V
    if (combo() > maxCombo()) {
        setMaxCombo(combo());
    }

    // �R���{���ɉ����ĐF��ύX
    if (combo() >= 50) {
        comboColor = { 1.0f, 1.0f, 0.0f, 1.0f };   // ���F
    }
    else if (combo() >= 25) {
        comboColor = { 0.2f, 1.0f, 1.0f, 1.0f };   // ���F
    }
    else {
        comboColor = { 1, 1, 1, 1 };       // ���F
    }

    // �X�R�A�\�������Ƃɖ߂�
    if (combo2Timer_ >= maxAppearTime_) {
        combo2Pos   = { 1890, 360 };        // �R���{�̈ʒu
        combo2Size  = { 1.5f, 1.5f };       // �R���{�̑傫��
        if (combo2() >= 10) {
            combo2Color = { 1.0f, 1.0f, 0.0f, 0.0f }; // ���F
        }
        else if (combo2() >= 5) {
            combo2Color = { 0.2f, 1.0f, 1.0f, 0.0f }; // ���F
        }
        else {
            combo2Color = { 1, 1, 1, 0 }; // ���F
        }
    }
    // �^�C�}�[�����炷
    if (combo2Timer_ > 0) combo2Timer_--;

    // �p�����[�^��ύX
    // �R���{1�̐ݒ�
    if (comboSize.x > 1.5f) 
        comboSize -= { 0.05f, 0.05f };

    // �R���{2�̐ݒ�
    if (combo2Timer_ > 30) {
        combo2Color.w += 0.5f;
    }
    else {
        combo2Color.w -= 0.04f;
    }
    if (combo2Timer_ > 115)
        combo2Size += { 0.1f, 0.1f };
    else
        combo2Size -= { 0.1f, 0.1f };

    // ���̒l�𒴂��Ȃ��悤�ɐݒ�
    comboSize.x = clamp(comboSize.x, 1.5f, 2.0f);
    comboSize.y = clamp(comboSize.y, 1.5f, 2.0f);
    if (combo2Pos.y < 300)        combo2Pos.y = 300;
    combo2Size.x = clamp(combo2Size.x, 1.5f, 1.8f);
    combo2Size.y = clamp(combo2Size.y, 1.5f, 1.8f);
    combo2Color.w = clamp(combo2Color.w, 0.0f, 1.0f);
}

// �R���{�̕`��ݒ�
void Game::comboDraw()
{
    std::ostringstream ss1, ss2, ss3;

    ss1 << "COMBO" << std::setw(4) << " ";
    ss2 << std::setw(9) << combo_;
    ss3 << combo2_;

    // �R���{�����e�L�X�g�\��
    font::textOut(6,
        ss1.str(),
        { 1890, 200 },
        { 1.5f, 1.5f },
        { 1.0f, 1.0f, 1.0f, 1.0f },
        TEXT_ALIGN::MIDDLE_RIGHT
    );

    font::textOut(6,
        ss1.str(),
        { 1897, 207 },
        { 1.5f, 1.5f },
        { 1.0f, 1.0f, 1.0f, 0.1f },
        TEXT_ALIGN::MIDDLE_RIGHT
    );

    // �R���{���̕`��
    font::textOut(6,
        ss2.str(),
        { 1890, 200 },
        comboSize,
        comboColor,
        TEXT_ALIGN::MIDDLE_RIGHT
    );

    font::textOut(6,
        ss2.str(),
        1897, 207,
        comboSize.x, comboSize.y,
        comboColor.x, comboColor.y, comboColor.z, comboColor.w - 0.9f,
        TEXT_ALIGN::MIDDLE_RIGHT
    );
    
    if (combo2_ > 0 && combo2Timer_ > 0) {
        font::textOut(6,
            ss3.str(),
            combo2Pos,
            combo2Size,
            combo2Color,
            TEXT_ALIGN::MIDDLE_RIGHT
        );

        font::textOut(6,
            ss3.str(),
            combo2Pos.x + 7, combo2Pos.y + 7,
            combo2Size.x, combo2Size.y,
            combo2Color.x, combo2Color.y, combo2Color.z, combo2Color.w - 0.9f,
            TEXT_ALIGN::MIDDLE_RIGHT
        );
    }
}

void Game::calcScore()
{
    // �X�R�A�\�������Ƃɖ߂�
    if (scoreTimer_ >= maxAppearTime_) {
        scorePos    = { 10, 80 };           // �X�R�A�̈ʒu
        scoreColor.w  = 0;       // �X�R�A�̐F
    }
    // �^�C�}�[�����炷
    if (scoreTimer_ > 0) scoreTimer_--;

    // �p�����[�^��ύX
    if (scoreTimer_ > 100) {
        scorePos.y -= 1.0f;
        scoreColor.w += 0.2f;
    }
    else{
        scorePos.y -= 1.0f;
        scoreColor.w -= 0.02f;
    }
    // ���̒l�𒴂��Ȃ��悤�ɐݒ�
    if (scorePos.y < 10)        scorePos.y = 10;
    scoreColor.w = clamp(scoreColor.w, 0.0f, 1.0f);
}

// �X�R�A�̕`��ݒ�
void Game::scoreDraw()
{
    std::ostringstream ss1, ss2;
    
    ss1 << "SCORE " << std::setw(8) << std::setfill('0') << score_;
    ss2 << std::setw(14) << appearScore_;
    
    // �X�R�A�����e�L�X�g�\��
    font::textOut(6,
        ss1.str(),
        { 10, 10 },
        { 1.5f, 1.5f },
        { 1.0f, 1.0f, 1.0f, 1.0f },
        TEXT_ALIGN::UPPER_LEFT
    );

    font::textOut(6,
        ss1.str(),
        { 17, 17 },
        { 1.5f, 1.5f },
        { 1.0f, 1.0f, 1.0f, 0.1f },
        TEXT_ALIGN::UPPER_LEFT
    );

    if (scoreTimer_) {
        // �X�R�A�����e�L�X�g�\��
        font::textOut(6,
            ss2.str(),
            scorePos.x, scorePos.y,
            scoreSize.x, scoreSize.y,
            notesColor.x, notesColor.y, notesColor.z, scoreColor.w,
            TEXT_ALIGN::UPPER_LEFT
        );

        font::textOut(6,
            ss2.str(),
            scorePos.x + 7, scorePos.y + 7,
            scoreSize.x, scoreSize.y,
            notesColor.x, notesColor.y, notesColor.z, scoreColor.w - 0.9f,
            TEXT_ALIGN::UPPER_LEFT
        );
    }
}

// �m�[�c����̔���
void Game::decisionJudge()
{
    VECTOR2 BGThreeQuarters = { BG::WINDOW_W / 4 * 3 - 320, BG::WINDOW_H / 4 * 3 - 75 };

    switch (decision_)
    {
    case Game::MISS:
        notesText.str("MISS");
        notesTimer_ = maxAppearTime_;
        notesPos    = { BGThreeQuarters.x, BGThreeQuarters.y };
        notesSize   = { 0.2f, 0.2f };
        notesColor  = { 0.0f, 0.0f, 1.0f, 0.0f };
        decision_   = NONE;
        break;
    case Game::GOOD:
        notesText.str("GOOD");
        notesTimer_ = maxAppearTime_;
        notesPos    = { BGThreeQuarters.x, BGThreeQuarters.y };
        notesSize   = { 0.2f, 0.2f };
        notesColor  = { 1.0f, 1.0f, 1.0f, 0.0f };
        decision_   = NONE;
        break;
    case Game::GREAT:
        notesText.str("GREAT");
        notesTimer_ = maxAppearTime_;
        notesPos    = { BGThreeQuarters.x, BGThreeQuarters.y };
        notesSize   = { 0.2f, 0.2f };
        notesColor  = { 0.2f, 1.0f, 1.0f, 0.0f };
        decision_   = NONE;
        break;
    case Game::PERFECT:
        notesText.str("PERFECT");
        notesTimer_ = maxAppearTime_;
        notesPos    = { BGThreeQuarters.x, BGThreeQuarters.y };
        notesSize   = { 0.2f, 0.2f };
        notesColor  = { 1.0f, 1.0f, 0.0f, 0.0f };
        decision_   = NONE;
        break;
    default:
        break;
    }
    // �^�C�}�[�����炷
    if (notesTimer_ > 0) notesTimer_--;
    
    // �p�����[�^��ύX
    if (notesTimer_ > 30) {
        notesPos.y -= 2.0f;
        notesSize += {0.2f, 0.2f};
        notesColor.w += 0.2f;
    }
    else {
        notesColor.w -= 0.04f;
    }
    // ���̒l�𒴂��Ȃ��悤�ɐݒ�
    if (notesPos.y < BGThreeQuarters.y - 20)       notesPos.y   = BGThreeQuarters.y - 20;
    if (notesSize.x > 1.5f)     notesSize    = { 1.5f, 1.5f };
    notesColor.w = clamp(notesColor.w, 0.0f, 1.0f);
    debug::setString("notesTimer:%d", notesTimer_);
    debug::setString("notesColor.w:%f", notesColor.w);
}

// �m�[�c����̕`��
void Game::decisionDraw()
{
    if (notesTimer_ > 0) {
        // �R���{�����e�L�X�g�\��
        font::textOut(6,
            notesText.str(),
            notesPos,
            notesSize,
            notesColor,
            TEXT_ALIGN::LOWER_LEFT
        );

        // �R���{�����e�L�X�g�\��
        font::textOut(6,
            notesText.str(),
            notesPos.x + 7, notesPos.y + 7,
            notesSize.x, notesSize.y,
            notesColor.x, notesColor.y, notesColor.z, notesColor.w - 0.9f,
            TEXT_ALIGN::LOWER_LEFT
        );
    }
}

// HP�̃A�j���[�V����
void Game::AnimetionHP() {
    // 6�t���[�����ƂɃA�j���[�V�����ؑ�
    if (HPAnimeTimer_ % 6 == 0) {
        if (hpTexPos01.x == 0) {
            hpTexPos01.x = 600;
        }
        else if (hpTexPos01.x == 600) {
            hpTexPos01.x = 1200;
        }
        else if (hpTexPos01.x == 1200) {
            hpTexPos01.x = 0;
        }
    }
    // HP�𑝂₷����
    if (state_ > 1 && hpSize02.x < 490) {
        hpSize02.x += 5;
    }
    HPAnimeTimer_++;
}

// �`���[�g���A��
void Game::operationDraw() {
    //�`���[�g���A���摜�̈ړ�����
    if (stageNo_ == 0 && state_ != 1 && timer_ > 30)
    {
        switch (tutorial_State_)
        {
        case 0:
            sprTutorial0_.draw(
                tutorial_pos_
            );

            if (isPaused_) return;

            tutorial_pos_.x += 10;

            if (tutorial_pos_.x > 300)
            {
                tutorial_pos_.x = 300;
                tutorial_timer_++;
            }

            if (tutorial_timer_ > 360)
            {
                tutorial_timer_ = 0;
                tutorial_State_++;
                break;
            }

            break;

        case 1:
            sprTutorial0_.draw(
                tutorial_pos_
            );

            if (isPaused_) return;

            tutorial_pos_.x -= 10;

            if (tutorial_pos_.x < -300)
            {
                tutorial_pos_.x = -300;
                tutorial_State_++;
                break;
            }
            break;

        case 2:
            sprTutorial1_.draw(
                tutorial_pos_
            );

            if (isPaused_) return;

            tutorial_pos_.x += 10;

            if (tutorial_pos_.x > 300)
            {
                tutorial_pos_.x = 300;
                tutorial_timer_++;
            }

            if (tutorial_timer_ > 1900)
            {
                tutorial_timer_ = 0;
                tutorial_State_++;
                break;
            }

            break;

        case 3:
            sprTutorial1_.draw(
                tutorial_pos_
            );

            if (isPaused_) return;

            tutorial_pos_.x -= 10;

            if (tutorial_pos_.x < -300)
            {
                tutorial_pos_.x = -300;
                tutorial_State_++;
                break;
            }
            break;

        case 4:
            sprTutorial3_.draw(
                tutorial_pos_
            );

            if (isPaused_) return;

            tutorial_pos_.x += 10;

            if (tutorial_pos_.x > 300)
            {
                tutorial_pos_.x = 300;
                tutorial_timer_++;
            }

            if (tutorial_timer_ > 600)
            {
                tutorial_timer_ = 0;
                tutorial_State_++;
                break;
            }

            break;

        case 5:
            sprTutorial3_.draw(
                tutorial_pos_
            );

            if (isPaused_) return;

            tutorial_pos_.x -= 10;

            if (tutorial_pos_.x < -300)
            {
                tutorial_pos_.x = -300;
                tutorial_State_++;
                break;
            }
            break;

        case 6:
            sprTutorial2_.draw(
                tutorial_pos_
            );

            if (isPaused_) return;

            tutorial_pos_.x += 10;

            if (tutorial_pos_.x > 300)
            {
                tutorial_pos_.x = 300;
                tutorial_timer_++;
            }

            if (tutorial_timer_ > 900)
            {
                tutorial_timer_ = 0;
                tutorial_State_++;
                break;
            }

            break;

        case 7:
            sprTutorial2_.draw(
                tutorial_pos_
            );

            if (isPaused_) return;

            tutorial_pos_.x -= 10;

            if (tutorial_pos_.x < -300)
            {
                tutorial_pos_.x = -300;
                tutorial_State_++;
                break;
            }
            break;

        case 8:
            sprTutorial4_.draw(
                tutorial_pos_
            );

            if (isPaused_) return;

            tutorial_pos_.x += 10;

            if (tutorial_pos_.x > 300)
            {
                tutorial_pos_.x = 300;
                tutorial_timer_++;
            }

            if (tutorial_timer_ > 600)
            {
                tutorial_timer_ = 0;
                tutorial_State_++;
                break;
            }

            break;

        case 9:
            sprTutorial4_.draw(
                tutorial_pos_
            );

            if (isPaused_) return;

            tutorial_pos_.x -= 10;

            if (tutorial_pos_.x < -300)
            {
                tutorial_pos_.x = -300;
                tutorial_State_++;
                break;
            }
            break;

        }
    }
}

//******************************************************************************