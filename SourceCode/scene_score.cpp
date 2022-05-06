//******************************************************************************
//
//
//      scene_score.cpp
//
//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
#include "all.h"
#include <sstream>
#include <iomanip>

//------< using >---------------------------------------------------------------
using namespace GameLib;
using namespace input;

//------< �ϐ� >----------------------------------------------------------------
Score Score::instance_;

//�����ݒ�
void Score::init()
{
    Scene::init();	    // ���N���X��init���Ă�

    // �ǂݍ��ރe�N�X�`��
    LoadTexture loadTextureTitle[static_cast<size_t>(TEXNOM::NUM)] = {
        { static_cast<int>(TEXNOM::RESTART),  L"./Data/Images/continue.png", 1U },
        { static_cast<int>(TEXNOM::TOTITLE),  L"./Data/Images/to title.png", 1U },
    };

    // �e�N�X�`���̃��[�h
    texture::load(loadTextureTitle);


}

//�I������
void Score::deinit()
{
    //�e�N�X�`����S�ĊJ��
    texture::releaseAll();
}

//�X�V
void Score::update()
{
    switch(state_)
    {
    case 0:
        ///////�@�����ݒ�@///////
        timer_ = 0;                 //�^�C�}�[�̏�����  

        //BGM�Đ�
        GameLib::music::play(4, false);

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);  //�ʏ�̃A���t�@����

        state_++;
        /*fallthrough*/

    case 1:
        // A�L�[�������ꂽ��
        if (TRG(0) & PAD_RIGHT)
        {
            if (score_select_num_ > 0)
            {
                score_select_num_--;
            }
        }

        //�@D�L�[�������ꂽ��
        if (TRG(0) & PAD_LEFT)
        {
            if (score_select_num_ < 1)
            {
                score_select_num_++;
            }
        }

        switch (score_alpha_num_)
        {
        case 0:
            score_alpha_ -= 0.03;
            if (score_alpha_ <= 0)   score_alpha_num_++;
            break;

        case 1:
            score_alpha_ += 0.03;
            if (score_alpha_ >= 1)   score_alpha_num_--;
            break;
        }

        //�O(�Ē���)��I��ł���Ƃ�
        if (score_select_num_)
        {
            if (TRG(0) & PAD_START)
            {
                music::play(7);
                changeScene(Game::instance());
                break;
            }
        }

        //�P(�����Ƃ��)��I��ł���Ƃ�
        if (score_select_num_ == false)
        {
            if (TRG(0) & PAD_START)
            {
                music::play(7);
                changeScene(Title::instance());
                break;
            }
        }

        break;
    }

    debug::setString("timer_:%d", timer_);
    timer_++;
}

//�`��
void  Score::draw()
{
    //��ʃN���A
    GameLib::clear(VECTOR4(0.5f, 0.5f, 0.5f, 1.0f));

    //GameLib::font::textOut(4, "Score",
    //{ GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 3) },
    //  VECTOR2(5.0f, 5.0f),
    //  { 1.0f, 1.0f, 1.0f, 1.0f },
    //  GameLib::TEXT_ALIGN::UPPER_MIDDLE
    //);

    //    // Push Enter Key �̕`��
    //if (timer_ >> 5 & 0x01) {
    //    GameLib::font::textOut(4, "Push BackSpace Key",
    //        { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 6) * 5 },
    //        VECTOR2(1.5f, 1.5f),
    //        { 1.0f, 1.0f, 1.0f, 1.0f },
    //        GameLib::TEXT_ALIGN::LOWER_MIDDLE
    //    );
    //}

        //�X�R�A�̕\��
    std::ostringstream ss1;

    ss1 << "SCORE:" << std::setfill('0') << Game::instance()->score();

     // �X�R�A�����e�L�X�g�\��
     font::textOut(6,
         ss1.str(),
         { GameLib::window::getWidth() / 3 , GameLib::window::getHeight() / 2 - GameLib::window::getHeight() / 3 },
         { 2.0f, 2.0f },
         { 1.0f, 1.0f, 1.0f, 1.0f },
         TEXT_ALIGN::UPPER_LEFT
     );


     //�Ē����I��ł���Ƃ�
     if (score_select_num_)
     {
         //"�Ē���"�̕����̕`��
         sprRestart_.draw(
             { GameLib::window::getWidth() / 4, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
             { 1.0f,1.0f },
             ToRadian(0),
             { 1,1,1,score_alpha_ }
         );

         //"�����Ƃ��"�̕����̕`��
         sprTotitle_.draw(
             { GameLib::window::getWidth() / 2 + GameLib::window::getWidth() / 4, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
             { 1.0f,1.0f },
             ToRadian(0),
             { 1,1,1,1 }
         );
     }

     //�����Ƃ�ւ�I��ł���Ƃ�
     if (score_select_num_ == false)
     {
         //"�Ē���"�̕����̕`��
         sprRestart_.draw(
             { GameLib::window::getWidth() / 4, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
             { 1.0f,1.0f },
             ToRadian(0),
             { 1,1,1,1 }
         );

         //"�����Ƃ��"�̕����̕`��
         sprTotitle_.draw(
             { GameLib::window::getWidth() / 2 + GameLib::window::getWidth() / 4, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
             { 1.0f,1.0f },
             ToRadian(0),
             { 1,1,1,score_alpha_ }
         );
     }


}