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

    // �ǂݍ��ރe�N�X�`��
    GameLib::LoadTexture loadTextureSelect[static_cast<size_t>(TEXNOM::NUM)] = {
        { static_cast<int>(TEXNOM::BACK),  L"./Data/Images/stage_select.png", 1U },
        { static_cast<int>(TEXNOM::TUTORIAL),  L"./Data/Images/tutorial_icon.png", 1U },
        { static_cast<int>(TEXNOM::STAGE1),  L"./Data/Images/stage1_icon.png", 1U },
        { static_cast<int>(TEXNOM::L_FUSUMA),  L"./Data/Images/L_fusuma.png", 1U },
        { static_cast<int>(TEXNOM::R_FUSUMA),  L"./Data/Images/R_fusuma.png", 1U },
        { static_cast<int>(TEXNOM::TOTITLE),  L"./Data/Images/to_title_icon.png", 1U },
        { static_cast<int>(TEXNOM::SHURIKEN),  L"./Data/Images/no-tsu01.png", 12U },
        { static_cast<int>(TEXNOM::DECORATION),  L"./Data/Images/decoration_icon.png", 1U },
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

        //�S�ẴA�C�R���̈ʒu�̏�����        
        title_icon_Pos_ = { window::getWidth() / 4 - 200, window::getHeight() / 2 + 150 };
        tutorial_icon_Pos_ = { window::getWidth() / 2 - 200, window::getHeight() / 2 + 150 };
        stage1_icon_Pos_ = { window::getWidth() / 2 + window::getWidth() / 4 - 200, window::getHeight() / 2 + 150 };

        //�S�ẴA�C�R���̃��l�̏�����
        tutorial_icon_Alpha_ = 0.2f;
        stage1_icon_Alpha_ = 0.2f;
        title_icon_Alpha_ = 1.0f;

        //�S�ẴA�C�R���̃X�P�[���̏�����
        tutorial_icon_Scale_ = { 0.5f + 0.1f, 0.5f + 0.1f };
        stage1_icon_Scale_ = { 0.5f + 0.1f, 0.5f + 0.1f };
        title_icon_Scale_ = { 0.5f + 0.1f,0.5f + 0.1f };

        //�V�[���؂�ւ��p�̉摜�ʒu�̏�����
        S_L_Fusuma_Pos_ = { 960 / 2,540 };     // �����̈ʒu�̏�����
        S_R_Fusuma_Pos_ = { (960 * 2) - (960 / 2) , 540 }; // �E���̈ʒu�̏�����

        //���̃^�C�}�[�̏�����
        Fusuma_timer_ = 0;

        //�t���O�̏�����
        push_flg = false;

        //�J�ڗp�藠���ʒu�̏�����
        for (int i = 0; i < 10; i++)
        {
            shuriken_Pos_[i].x = static_cast<float>(2400 + (128 * i));
            shuriken_Pos_[i].y = static_cast<float>(128 * i);
        }

        //�J�ڗp�藠���̏�����
        shuriken_Angle_ = 0;

        //�^�C�g�������������ǂ���
        title_push_flg_ = false;

        // �N�i�C�̏����ݒ�
        stagingShuriken_[0].pos = { -150, 150 };
        stagingShuriken_[1].pos = { 2070,150 }; // 1770
        stagingShuriken_[0].scale = { 1.5f, 1.5f };
        stagingShuriken_[1].scale = { 1.5f, 1.5f };
        stagingShuriken_[0].angle = {};
        stagingShuriken_[1].angle = {};

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

        //�Z���N�g���BGM�̍Đ�
        music::play(7, true);

        //���̊J��
        GameLib::music::play(11, false);

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

        //Enter���P��������ĂȂ�������
        if (push_flg == false)
        {
            //�X�e�[�W�I��(�v���C���[����)
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
            //�^�C�g���֑I��
        case 0:

            //���l���Œ�
            title_icon_Alpha_ = 1.0f;

            //�A�C�R���̃X�P�[�����傫���Ȃ�������w��̑傫���܂ő傫������
            if (title_icon_Scale_.x < 0.6f + 0.1f && title_icon_Scale_.y < 0.6f + 0.1f)
            {
                title_icon_Scale_.x += 0.005f;
                title_icon_Scale_.y += 0.005f;
            }

            //���l���Œ�
            tutorial_icon_Alpha_ = 0.2f;

            //�A�C�R���̃X�P�[�����傫��������w��̑傫���܂ŏ���������
            if (tutorial_icon_Scale_.x > 0.5f + 0.1f && tutorial_icon_Scale_.y > 0.5f + 0.1f)
            {
                tutorial_icon_Scale_.x -= 0.005f;
                tutorial_icon_Scale_.y -= 0.005f;
            }

            //���l���Œ�
            stage1_icon_Alpha_ = 0.2f;

            //�A�C�R���̃X�P�[�����傫��������w��̑傫���܂ŏ���������
            if (stage1_icon_Scale_.x > 0.5f + 0.1f && stage1_icon_Scale_.y > 0.5f + 0.1f)
            {
                stage1_icon_Scale_.x -= 0.005f;
                stage1_icon_Scale_.y -= 0.005f;
            }

            break;
            //�`���[�g���A���I��
        case 1:

            //���l���Œ�
            title_icon_Alpha_ = 0.2f;

            //�A�C�R���̃X�P�[�����傫��������w��̑傫���܂ŏ���������
            if (title_icon_Scale_.x > 0.5f + 0.1f && title_icon_Scale_.y > 0.5f + 0.1f)
            {
                title_icon_Scale_.x -= 0.005f;
                title_icon_Scale_.y -= 0.005f;
            }

            //���l���Œ�
            tutorial_icon_Alpha_ = 1.0f;

            //�A�C�R���̃X�P�[�����傫���Ȃ�������w��̑傫���܂ő傫������
            if (tutorial_icon_Scale_.x < 0.6f + 0.1f && tutorial_icon_Scale_.y < 0.6f + 0.1f)
            {
                tutorial_icon_Scale_.x += 0.005f;
                tutorial_icon_Scale_.y += 0.005f;
            }

            //���l���Œ�
            stage1_icon_Alpha_ = 0.2f;

            //�A�C�R���̃X�P�[�����傫��������w��̑傫���܂ŏ���������
            if (stage1_icon_Scale_.x > 0.5f + 0.1f && stage1_icon_Scale_.y > 0.5f + 0.1f)
            {
                stage1_icon_Scale_.x -= 0.005f;
                stage1_icon_Scale_.y -= 0.005f;
            }
            break;

            //�X�e�[�W�P�I��
        case 2:

            //���l���Œ�
            title_icon_Alpha_ = 0.2f;

            //�A�C�R���̃X�P�[�����傫��������w��̑傫���܂ŏ���������
            if (title_icon_Scale_.x > 0.5f + 0.1f && title_icon_Scale_.y > 0.5f + 0.1f)
            {
                title_icon_Scale_.x -= 0.005f;
                title_icon_Scale_.y -= 0.005f;
            }

            //���l���Œ�
            tutorial_icon_Alpha_ = 0.2f;

            //�A�C�R���̃X�P�[�����傫��������w��̑傫���܂ŏ���������
            if (tutorial_icon_Scale_.x > 0.5f + 0.1f && tutorial_icon_Scale_.y > 0.5f + 0.1f)
            {
                tutorial_icon_Scale_.x -= 0.005f;
                tutorial_icon_Scale_.y -= 0.005f;
            }

            //���l���Œ�
            stage1_icon_Alpha_ = 1.0f;

            //�A�C�R���̃X�P�[�����傫���Ȃ�������w��̑傫���܂ő傫������
            if (stage1_icon_Scale_.x < 0.6f + 0.1f && stage1_icon_Scale_.y < 0.6f + 0.1f)
            {
                stage1_icon_Scale_.x += 0.005f;
                stage1_icon_Scale_.y += 0.005f;
            }
            break;
        }

        //Enter�������ꂽ��
        if (TRG(0) & PAD_START)
        {
            //���艹
            GameLib::music::play(8, false);

            state_++;
            timer_ = 0;
            break;
        }
        break;
    case 3:
        if (timer_ > 60) {
            // �Q�[����ʂɑJ��
            if (stageNum_ > 0) {
                //���̊J��
                GameLib::music::play(11, false);
                state_++;
                break;
            }
            // �^�C�g���ɑJ��
            else {
                state_ = 5;
                break;
            }
        }
        break;
    case 4:
        //////// �Q�[����ʂɑJ�� ////////

        //���̏���
        if (S_L_Fusuma_Pos_.x <= 960 && S_R_Fusuma_Pos_.x >= (960 * 1.5f))
        {
            S_L_Fusuma_Pos_.x += 30;
            S_R_Fusuma_Pos_.x -= 30;
        }

        if (S_L_Fusuma_Pos_.x >= 480 && S_R_Fusuma_Pos_.x <= (960 * 1.5f))
        {
            S_L_Fusuma_Pos_.x = 480;
            S_R_Fusuma_Pos_.x = (960 * 1.5f);

            //�P�b�u���Ă���J��
            if (Fusuma_timer_ > 60) {
                GameLib::music::stop(7);
                changeScene(Game::instance());
                break;
            }
            Fusuma_timer_++;
        }
        break;
    case 5:
        //////// �^�C�g���ɑJ�� /////////
        for (int i = 0; i < 10; i++)
        {
            shuriken_Pos_[i].x -= 20;
            shuriken_Angle_++;
        }

        if (shuriken_Pos_[9].x <= -500)
        {
            GameLib::music::stop(7);
            changeScene(Title::instance());
            break;
        }
        break;
    }

    // �藠���̍s��
    shurikenAct();

    // �f�o�b�O
    // GameLib::debug::setString("state_:%d", state_);
    // GameLib::debug::setString("timer_:%d", timer_);
    // GameLib::debug::setString("stageNum_:%d", stageNum_);

    // �����̓_��
    if (state_ > 2) {
        if (stageNum_ == 0) {
            title_icon_Alpha_ = calcIconFlashing(title_icon_Alpha_, timer_);
            stage1_icon_Alpha_ = calcIconFade(stage1_icon_Alpha_);
            tutorial_icon_Alpha_ = calcIconFade(tutorial_icon_Alpha_);
        }
        else if (stageNum_ == 1) {
            tutorial_icon_Alpha_ = calcIconFlashing(tutorial_icon_Alpha_, timer_);
            title_icon_Alpha_ = calcIconFade(title_icon_Alpha_);
            stage1_icon_Alpha_ = calcIconFade(stage1_icon_Alpha_);
        }
        else if (stageNum_ == 2) {
            stage1_icon_Alpha_ = calcIconFlashing(stage1_icon_Alpha_, timer_);
            title_icon_Alpha_ = calcIconFade(title_icon_Alpha_);
            tutorial_icon_Alpha_ = calcIconFade(tutorial_icon_Alpha_);
        }
    }
    timer_++;
}

// �`��
void Select::draw() {

    //�}�X�N�����̍폜���`��̒ǉ�
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
        { 1.0f,1.0f,1.0f,tutorial_icon_Alpha_ }
    );

    //�X�e�[�W�P�A�C�R���̕`��
    sprStage1_.draw(
        stage1_icon_Pos_,
        stage1_icon_Scale_,
        ToRadian(0),
        { 1.0f,1.0f,1.0f,stage1_icon_Alpha_ }
    );

    //�^�C�g���ւ̕����̕`��
    sprTotitle_.draw(
        title_icon_Pos_,
        title_icon_Scale_,
        ToRadian(0),
        { 1.0f,1.0f,1.0f,title_icon_Alpha_ }
    );

    GameLib::setBlendMode(GameLib::Blender::BS_MULTIPLY);   // �ʏ�̃A���t�@����

    //��ԉE�̏���̊|����
    sprDecration_.draw(
        { window::getWidth() / 2 + window::getWidth() / 3 + 100 , window::getHeight() / 2 + 150 },
        { 0.6f,0.6f }
    );
    
    GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

    // �N�i�C�̕`��
    for (int i = 0; i < 2; i++) {
        sprShuriken_.draw(
            stagingShuriken_[i].pos, stagingShuriken_[i].scale,
            ToRadian(stagingShuriken_[i].angle)
        );
    }

    //���̕`��
    sprL_fusuma_.draw(
        S_L_Fusuma_Pos_
    );

    sprR_fusuma_.draw(
        S_R_Fusuma_Pos_
    );

    //�藠���̕`��
    for (int i = 0; i < 10; i++)
    {
        sprShuriken_.draw(
            shuriken_Pos_[i], { 1.0f,1.0f },
            ToRadian(shuriken_Angle_)
        );
    }

    //�藠���̎l�p
    for (int i = 0; i < 10; i++)
    {
        primitive::rect({ 2400 , shuriken_Pos_[i].y + 64 }, { shuriken_Pos_[i].x - 2400 + 64 , 128 }, { 0,128 }, ToRadian(0), { 0.0f,0.0f,0.0f,1.0f });
    }
}

float Select::calcIconFlashing(float colorW, int timer)
{
    if (timer % 15 == 0 && colorW <= 0) {
        colorW = 1;
    }
    else if (timer % 15 == 0 && colorW >= 1) {
        colorW = 0;
    }
    timer++;

    return colorW;
}

float Select::calcIconFade(float colorW)
{
    if (colorW > 0) {
        colorW -= 0.005f;
    }
    return colorW;
}

void Select::shurikenAct()
{
    switch (state_) {
    case 2:
        if (stagingShuriken_[0].pos.x < 200) {
            stagingShuriken_[0].pos.x += 10;
            stagingShuriken_[0].angle += 10;
        }
        if (stagingShuriken_[1].pos.x > 1720) {
            stagingShuriken_[1].pos.x -= 10;
            stagingShuriken_[1].angle -= 10;
        }
        stagingShuriken_[0].angle += 2;
        stagingShuriken_[1].angle -= 2;
        break;
    case 3:
    case 4:
    case 5:
        stagingShuriken_[0].pos.x -= 10;
        stagingShuriken_[0].angle -= 10;
        stagingShuriken_[1].pos.x += 10;
        stagingShuriken_[1].angle += 10;
        break;
    default:
        break;
    }
}
