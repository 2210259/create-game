//******************************************************************************
//
//
//      scene_score.cpp
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;
using namespace input;

//------< 変数 >----------------------------------------------------------------
Score Score::instance_;

//初期設定
void Score::init()
{
    Scene::init();	    // 基底クラスのinitを呼ぶ

}

//終了処理
void Score::deinit()
{
    //テクスチャを全て開放
    texture::releaseAll();
}

//更新
void Score::update()
{
    switch(state_)
    {
    case 0:
        ///////　初期設定　///////
        timer_ = 0;                 //タイマーの初期化  

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);  //通常のアルファ処理

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

//描画
void  Score::draw()
{
    //画面クリア
    GameLib::clear(VECTOR4(0.5f, 0.5f, 0.5f, 1.0f));

    GameLib::font::textOut(4, "Score",
    { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 3) },
      VECTOR2(5.0f, 5.0f),
      { 1.0f, 1.0f, 1.0f, 1.0f },
      GameLib::TEXT_ALIGN::UPPER_MIDDLE
    );

        // Push Enter Key の描画
    if (timer_ >> 5 & 0x01) {
        GameLib::font::textOut(4, "Push BackSpace Key",
            { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 6) * 5 },
            VECTOR2(1.5f, 1.5f),
            { 1.0f, 1.0f, 1.0f, 1.0f },
            GameLib::TEXT_ALIGN::LOWER_MIDDLE
        );
    }

}