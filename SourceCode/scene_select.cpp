//******************************************************************************
//
//
//      �Z���N�g���
//
//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< �ϐ� >----------------------------------------------------------------
Select Select::instance_;

// �����ݒ�
void Select::init() {
    Scene::init();	    // ���N���X��init���Ă�

    //TODO:�ύX
    // �ǂݍ��ރe�N�X�`��
    GameLib::LoadTexture loadTextureSelect[static_cast<size_t>(TEXNO::NUM)] = {
        { static_cast<int>(TEXNO::BACK),  L"./Data/Images/stage_select.png", 1U },
        { static_cast<int>(TEXNO::TUTORIAL),  L"./Data/Images/tutorial_icon.png", 1U },
        { static_cast<int>(TEXNO::STAGE1),  L"./Data/Images/stage1_icon.png", 1U },
        { static_cast<int>(TEXNO::STAGE2),  L"./Data/Images/stage2_icon.png", 1U },
        { static_cast<int>(TEXNO::L_FUSUMA),  L"./Data/Images/L_fusuma.png", 1U },
        { static_cast<int>(TEXNO::R_FUSUMA),  L"./Data/Images/R_fusuma.png", 1U },

    };                    
                        
    // �e�N�X�`���̃��[�h
    GameLib::texture::load(loadTextureSelect);
}

// �I������
void Select::deinit() {
    // �e�N�X�`����S�ĉ��
    GameLib::texture::releaseAll();
}

// �X�V
void Select::update() {

    using namespace input;
    switch (state_) {
    case 0:
        //////// �����ݒ� ////////
        timer_ = 0;                         // �^�C�}�[��������

        stageNum_ = 0;                      //�X�e�[�W�ԍ��̏�����

        //�A�C�R���̈ʒu�̏�����
        tutorial_icon_Pos_ = { GameLib::window::getWidth() / 2 - (GameLib::window::getWidth() / 2) / 2 , GameLib::window::getHeight() / 2 };
        stage1_icon_Pos_ = { GameLib::window::getWidth() / 2 , GameLib::window::getHeight() / 2 };
        stage2_icon_Pos_ = { GameLib::window::getWidth() / 2 + (GameLib::window::getWidth() / 2) / 2 , GameLib::window::getHeight() / 2 };

        //�A�C�R���̃��l�̏�����
        tutorial_icon_Alpha_ = 1.0f;
        stage1_icon_Alpha_ = 1.0f;
        stage2_icon_Alpha_ = 1.0f;

        //�A�C�R���̃X�P�[���̏�����
        tutorial_icon_Scale_ = { 0.5f , 0.5f };
        stage1_icon_Scale_ = { 0.5f , 0.5f };
        stage2_icon_Scale_ = { 0.5f , 0.5f };
        
        //�V�[���؂�ւ��p�̉摜�ʒu�̏�����
        S_L_Fusuma_Pos_ = { 960 / 2,540 };     // �����̈ʒu�̏�����
        S_R_Fusuma_Pos_ = { (960 * 2) - (960 / 2) , 540 }; // �E���̈ʒu�̏�����

        //���̃^�C�}�[�̏�����
        Fusuma_timer_ = 0;

        //�t���O�̏�����
        push_flg = false;

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

        music::play(7, true);   //BGM�̍Đ�

        state_++;                                            // �����������̏I��

        /*fallthrough*/

    case 1:
        //////// �t�F�[�h�C���� ////////

        // ���̏���
        if (S_L_Fusuma_Pos_.x > -960 / 2 && S_R_Fusuma_Pos_.x < (960 * 2) + (960 / 2))
        {
            S_L_Fusuma_Pos_.x -= 30;
            S_R_Fusuma_Pos_.x += 30;

            if (S_L_Fusuma_Pos_.x <= -960 / 2 && S_R_Fusuma_Pos_.x >= (960 * 2) + (960 / 2))
            {
                S_L_Fusuma_Pos_.x = -960 / 2;
                S_R_Fusuma_Pos_.x = (960 * 2) + (960 / 2);
                state_++;
            }
        }

        break;

    case 2:
        //////// �ʏ펞�̏��� ////////

        // �ǉ�
        if (push_flg == false)
        {
            //�X�e�[�W�I��p
            if (TRG(0) & PAD_LEFT)
            {
                if (stageNum_ > 0)
                    stageNum_--;
            }

            if (TRG(0) & PAD_RIGHT)
            {
                if (stageNum_ < 2)
                    stageNum_++;
            }
        }
        //�I�����Ă���摜�̃��l�ƃX�P�[���̕ύX
        switch (stageNum_)
        {
        //�`���[�g���A���I��
        case 0:
            tutorial_icon_Alpha_ = 1.0f;
            
            //�A�C�R���̃X�P�[�����傫���Ȃ�������傫������
            if (tutorial_icon_Scale_.x < 0.6f && tutorial_icon_Scale_.y < 0.6f)
            {
                tutorial_icon_Scale_.x += 0.005f;
                tutorial_icon_Scale_.y += 0.005f;
            }

            stage1_icon_Alpha_ = 0.2f;

            //�A�C�R���̃X�P�[�����傫�������珬��������
            if (stage1_icon_Scale_.x > 0.5f && stage1_icon_Scale_.y > 0.5f)
            {
                stage1_icon_Scale_.x -= 0.005f;
                stage1_icon_Scale_.y -= 0.005f;
            }

            stage2_icon_Alpha_ = 0.2f;

            //�A�C�R���̃X�P�[�����傫�������珬��������
            if (stage2_icon_Scale_.x > 0.5f && stage2_icon_Scale_.y > 0.5f)
            {
                stage2_icon_Scale_.x -= 0.005f;
                stage2_icon_Scale_.y -= 0.005f;
            }
            break;

        //�X�e�[�W�P�I��
        case 1:
            tutorial_icon_Alpha_ = 0.2f;

            //�A�C�R���̃X�P�[�����傫�������珬��������
            if (tutorial_icon_Scale_.x > 0.5f && tutorial_icon_Scale_.y > 0.5f)
            {
                tutorial_icon_Scale_.x -= 0.005f;
                tutorial_icon_Scale_.y -= 0.005f;
            }

            stage1_icon_Alpha_ = 1.0f;

            //�A�C�R���̃X�P�[�����傫���Ȃ�������傫������
            if (stage1_icon_Scale_.x < 0.6f && stage1_icon_Scale_.y < 0.6f)
            {
                stage1_icon_Scale_.x += 0.005f;
                stage1_icon_Scale_.y += 0.005f;
            }

            stage2_icon_Alpha_ = 0.2f;

            //�A�C�R���̃X�P�[�����傫�������珬��������
            if (stage2_icon_Scale_.x > 0.5f && stage2_icon_Scale_.y > 0.5f)
            {
                stage2_icon_Scale_.x -= 0.005f;
                stage2_icon_Scale_.y -= 0.005f;
            }
            break;

        //�X�e�[�W�Q�I��
        case 2:
            tutorial_icon_Alpha_ = 0.2f;

            //�A�C�R���̃X�P�[�����傫�������珬��������
            if (tutorial_icon_Scale_.x > 0.5f && tutorial_icon_Scale_.y > 0.5f)
            {
                tutorial_icon_Scale_.x -= 0.005f;
                tutorial_icon_Scale_.y -= 0.005f;
            }

            stage1_icon_Alpha_ = 0.2f;

            //�A�C�R���̃X�P�[�����傫�������珬��������
            if (stage1_icon_Scale_.x > 0.5f && stage1_icon_Scale_.y > 0.5f)
            {
                stage1_icon_Scale_.x -= 0.005f;
                stage1_icon_Scale_.y -= 0.005f;
            }

            stage2_icon_Alpha_ = 1.0f;

            //�A�C�R���̃X�P�[�����傫���Ȃ�������傫������
            if (stage2_icon_Scale_.x < 0.6f && stage2_icon_Scale_.y < 0.6f)
            {
                stage2_icon_Scale_.x += 0.005f;
                stage2_icon_Scale_.y += 0.005f;
            }
            break;
        }

        //Enter�������ꂽ��
        if (TRG(0) & PAD_START && push_flg == false)
        {
            //���艹
            GameLib::music::play(8, false);
            push_flg = true;
        }

        //����push_flg��true��������
        if (push_flg)
        {
            if (S_L_Fusuma_Pos_.x <= 960 && S_R_Fusuma_Pos_.x >= (960 * 1.5f))
            {
                S_L_Fusuma_Pos_.x += 30;
                S_R_Fusuma_Pos_.x -= 30;
            }

            if (S_L_Fusuma_Pos_.x >= 480 && S_R_Fusuma_Pos_.x <= (960 * 1.5f))
            {
                S_L_Fusuma_Pos_.x = 480;
                S_R_Fusuma_Pos_.x = (960 * 1.5f);

                if (Fusuma_timer_ > 60) {
                    GameLib::music::stop(5);
                    changeScene(Game::instance());
                }
                Fusuma_timer_++;
            }
        }
    }

    GameLib::debug::setString("state_:%d", state_);
    GameLib::debug::setString("timer_:%d", timer_);
    GameLib::debug::setString("stageNum_:%d", stageNum_);
    timer_++;
}

// �`��
void Select::draw() {

    //TODO:�}�X�N�����̍폜���`��̒ǉ�
    // ��ʃN���A
    GameLib::clear(VECTOR4(0.0f, 0.0f, 1.0f, 1));

    //�w�i�̕`��
    sprBack_.draw(
        { 960,540 },
        { 1.0f,1.0f }
    );

    //�`���[�g���A���A�C�R���̕`��
    sprTutorial_.draw(
        tutorial_icon_Pos_,
        tutorial_icon_Scale_,
        ToRadian(0),
        { 1.0f,1.0f,1.0f,tutorial_icon_Alpha_}
    );

    //�X�e�[�W�P�A�C�R���̕`��
    sprStage1_.draw(
        stage1_icon_Pos_,
        stage1_icon_Scale_,
        ToRadian(0),
        { 1.0f,1.0f,1.0f,stage1_icon_Alpha_}
    );

    //�X�e�[�W�Q�A�C�R���̕`��
    sprStage2_.draw(
        stage2_icon_Pos_,
        stage2_icon_Scale_,
        ToRadian(0),
        { 1.0f,1.0f,1.0f,stage2_icon_Alpha_}
    );

    //���̕`��
    sprL_fusuma_.draw(
        S_L_Fusuma_Pos_
    );

    sprR_fusuma_.draw(
        S_R_Fusuma_Pos_
    );
}
