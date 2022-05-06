//******************************************************************************
//
//
//      scene_score.cpp
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include "all.h"
#include <sstream>
#include <iomanip>

//------< using >---------------------------------------------------------------
using namespace GameLib;
using namespace input;

//------< 変数 >----------------------------------------------------------------
Score Score::instance_;

//初期設定
void Score::init()
{
    Scene::init();	    // 基底クラスのinitを呼ぶ

    // 読み込むテクスチャ
    LoadTexture loadTextureTitle[static_cast<size_t>(TEXNOM::NUM)] = {
        { static_cast<int>(TEXNOM::RESTART),  L"./Data/Images/continue.png", 1U },
        { static_cast<int>(TEXNOM::TOTITLE),  L"./Data/Images/to title.png", 1U },
    };

    // テクスチャのロード
    texture::load(loadTextureTitle);


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

        //BGM再生
        GameLib::music::play(4, false);

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);  //通常のアルファ処理

        state_++;
        /*fallthrough*/

    case 1:
        // Aキーが押された時
        if (TRG(0) & PAD_RIGHT)
        {
            if (score_select_num_ > 0)
            {
                score_select_num_--;
            }
        }

        //　Dキーが押された時
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

        //０(再挑戦)を選んでいるとき
        if (score_select_num_)
        {
            if (TRG(0) & PAD_START)
            {
                music::play(7);
                changeScene(Game::instance());
                break;
            }
        }

        //１(たいとるへ)を選んでいるとき
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

//描画
void  Score::draw()
{
    //画面クリア
    GameLib::clear(VECTOR4(0.5f, 0.5f, 0.5f, 1.0f));

    //GameLib::font::textOut(4, "Score",
    //{ GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 3) },
    //  VECTOR2(5.0f, 5.0f),
    //  { 1.0f, 1.0f, 1.0f, 1.0f },
    //  GameLib::TEXT_ALIGN::UPPER_MIDDLE
    //);

    //    // Push Enter Key の描画
    //if (timer_ >> 5 & 0x01) {
    //    GameLib::font::textOut(4, "Push BackSpace Key",
    //        { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 6) * 5 },
    //        VECTOR2(1.5f, 1.5f),
    //        { 1.0f, 1.0f, 1.0f, 1.0f },
    //        GameLib::TEXT_ALIGN::LOWER_MIDDLE
    //    );
    //}

        //スコアの表示
    std::ostringstream ss1;

    ss1 << "SCORE:" << std::setfill('0') << Game::instance()->score();

     // スコア数をテキスト表示
     font::textOut(6,
         ss1.str(),
         { GameLib::window::getWidth() / 3 , GameLib::window::getHeight() / 2 - GameLib::window::getHeight() / 3 },
         { 2.0f, 2.0f },
         { 1.0f, 1.0f, 1.0f, 1.0f },
         TEXT_ALIGN::UPPER_LEFT
     );


     //再挑戦を選んでいるとき
     if (score_select_num_)
     {
         //"再挑戦"の文字の描画
         sprRestart_.draw(
             { GameLib::window::getWidth() / 4, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
             { 1.0f,1.0f },
             ToRadian(0),
             { 1,1,1,score_alpha_ }
         );

         //"たいとるへ"の文字の描画
         sprTotitle_.draw(
             { GameLib::window::getWidth() / 2 + GameLib::window::getWidth() / 4, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
             { 1.0f,1.0f },
             ToRadian(0),
             { 1,1,1,1 }
         );
     }

     //たいとるへを選んでいるとき
     if (score_select_num_ == false)
     {
         //"再挑戦"の文字の描画
         sprRestart_.draw(
             { GameLib::window::getWidth() / 4, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
             { 1.0f,1.0f },
             ToRadian(0),
             { 1,1,1,1 }
         );

         //"たいとるへ"の文字の描画
         sprTotitle_.draw(
             { GameLib::window::getWidth() / 2 + GameLib::window::getWidth() / 4, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
             { 1.0f,1.0f },
             ToRadian(0),
             { 1,1,1,score_alpha_ }
         );
     }


}