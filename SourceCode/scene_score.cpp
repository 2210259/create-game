//******************************************************************************
//
//
//      scene_score.cpp
//
//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;
using namespace input;

//------< �ϐ� >----------------------------------------------------------------
Score Score::instance_;

//�����ݒ�
void Score::init()
{
    Scene::init();	    // ���N���X��init���Ă�

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

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);  //�ʏ�̃A���t�@����

        state_++;
        /*fallthrough*/

    case 1:
        if(TRG(0) & PAD_SELECT)
        {
            changeScene(Title::instance());
            break;
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

    GameLib::font::textOut(4, "Score",
    { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 3) },
      VECTOR2(5.0f, 5.0f),
      { 1.0f, 1.0f, 1.0f, 1.0f },
      GameLib::TEXT_ALIGN::UPPER_MIDDLE
    );

        // Push Enter Key �̕`��
    if (timer_ >> 5 & 0x01) {
        GameLib::font::textOut(4, "Push BackSpace Key",
            { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 6) * 5 },
            VECTOR2(1.5f, 1.5f),
            { 1.0f, 1.0f, 1.0f, 1.0f },
            GameLib::TEXT_ALIGN::LOWER_MIDDLE
        );
    }

}