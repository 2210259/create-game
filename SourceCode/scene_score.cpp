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
        { static_cast<int>(TEXNOM::CLEAR),  L"./Data/Images/clear.png", 1U },
        { static_cast<int>(TEXNOM::GAMEOVER),  L"./Data/Images/gameover.png", 1U },
        { static_cast<int>(TEXNOM::L_FUSUMA), L"./Data/Images/L_fusuma.png", 1U },
        { static_cast<int>(TEXNOM::R_FUSUMA), L"./Data/Images/R_fusuma.png", 1U },
        { static_cast<int>(TEXNOM::SHURIKEN), L"./Data/Images/no-tsu01.png", 1U },
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

        score_select_num_ = 0;              //選択用数値の初期化  
        score_alpha_ = 0.0f;                //表示するテキストのα値の初期化  
        score_alpha_num_ = 0;               //α値を０～１まで往復させるための値の初期化  

        scoreText_pos_ = { 1920.0f,0.0f };  //スコアテキストの位置の初期化  
        scoreNum_ = 0;                      //スコアの初期化  

        comboText_pos_ = { 1920.0f,0.0f };  //コンボテキストの位置の初期化  
        comboNum_ = 0;                      //コンボの初期化  

        perfectText_pos_ = { 1920.0f,0.0f };//パーフェクトテキストの位置の初期化  
        perfectNum_ = 0;                    //パーフェクトの初期化  

        greatText_pos_ = { 1920.0f,0.0f };     //グレイトテキストの位置の初期化  
        greatNum_ = 0;                      //グレイトの初期化  

        goodText_pos_ = { 1920.0f,0.0f };   //グッドテキストの位置の初期化  
        goodNum_ = 0;                       //グッドの初期化  
        
        missText_pos_ = { 1920.0f,0.0f };   //ミステキストの位置の初期化  
        missNum_ = 0;                       //ミスの初期化  

        rank_Scale = 150.0f;     //ランクスケールの初期化

        performState_ = 0;                  //演出用ステートの初期化

        C_L_Fusuma_Pos_ = { 960 / 2,540 };     // 左襖の位置の初期化
        C_R_Fusuma_Pos_ = { (960 * 2) - (960 / 2) , 540 }; // 右襖の位置の初期化

        C_Fusuma_timer_ = 0;                   //襖が閉じるまでの時間の初期化

        restart_push_flg_ = false;          //再挑戦を押したときのフラグ

        title_push_flg_ = false;            //タイトルへを押したときのフラグ

        //手裏剣位置の初期化
        for (int i = 0; i < 10; i++)
        {
            shuriken_Pos_[i].x = 2400 + (128 * i);
            shuriken_Pos_[i].y = 128 * i;
        }

        shuriken_Angle_ = 0;

        //BGM再生
        GameLib::music::play(5, false);

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);  //通常のアルファ処理

        state_++;
        /*fallthrough*/

    case 1:
        ///// リザルトの演出 /////
        scoreRusult();
        break;
    }

    debug::setString("timer_:%d", timer_);
    debug::setString("Game::instance()->perfectNum():%d", Game::instance()->perfectNum());
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

    ///// 画像分岐 /////
    //生存したとき
    if (Game::instance()->playerAlive())
    {
        sprClear_.draw(
            { 960,540 },
            { 1.0f,1.0f },
            ToRadian(0),
            { 1.0f, 1.0f, 1.0f, 1.0f }
        );
    }
    //死亡した時
    else
    {
        sprGameover_.draw(
            { 960,540 },
            { 1.0f,1.0f },
            ToRadian(0),
            { 1.0f, 1.0f, 1.0f, 1.0f }
        );
    }
    // スコアの表示
    scoreDraw();
}

void Score::scoreRusult() {
    switch (performState_)
    {
    case 0:
        //TODO:襖の処理
        if (C_L_Fusuma_Pos_.x > -960 / 2 && C_R_Fusuma_Pos_.x < (960 * 2) + (960 / 2) && C_Fusuma_timer_ > 60)
        {
            C_L_Fusuma_Pos_.x -= 30;
            C_R_Fusuma_Pos_.x += 30;

            if (C_L_Fusuma_Pos_.x <= -960 / 2 && C_R_Fusuma_Pos_.x >= (960 * 2) + (960 / 2))
            {
                C_L_Fusuma_Pos_.x = -960 / 2;
                C_R_Fusuma_Pos_.x = (960 * 2) + (960 / 2);
                C_Fusuma_timer_ = 0;
                performState_++;
            }
        }
        C_Fusuma_timer_++;
        break;

        //"MAXCONBO"の文字の移動
    case 1:
        if (comboText_pos_.x > GameLib::window::getWidth() - 800)
        {
            comboText_pos_.x -= 30.0f;
            if (comboText_pos_.x <= GameLib::window::getWidth() - 800 || TRG(0) & PAD_START)
            {
                comboText_pos_.x = GameLib::window::getWidth() - 800;
                performState_++;
                break;
            }
            break;
        }
        //"MAXCONBO"の数値を加算
    case 2:
        if (comboNum_ <= Game::instance()->maxCombo())
        {

            if (timer_ % 5 == 0 && comboNum_ < 12)
                comboNum_++;
            else if (timer_ % 2 == 0 && 12 <= comboNum_ && comboNum_ < 100)
                comboNum_++;
            else if (timer_ % 1 == 0 && comboNum_ >= 100)
                comboNum_++;

            if (comboNum_ >= Game::instance()->maxCombo() || TRG(0) & PAD_START)
            {
                comboNum_ = Game::instance()->maxCombo();
                performState_++;
                break;
            }
            break;
        }
        //"PERFECT"の文字の移動
    case 3:
        if (perfectText_pos_.x > GameLib::window::getWidth() - 800)
        {
            perfectText_pos_.x -= 30.0f;
            if (perfectText_pos_.x <= GameLib::window::getWidth() - 800 || TRG(0) & PAD_START)
            {
                perfectText_pos_.x = GameLib::window::getWidth() - 800;
                performState_++;
                break;
            }
            break;
        }
        //"PERFECT"の数値を加算
    case 4:
        if (perfectNum_ <= Game::instance()->perfectNum())
        {
            if (timer_ % 5 == 0 && perfectNum_ < 12)
                perfectNum_++;
            else if (timer_ % 2 == 0 && 12 <= perfectNum_ && perfectNum_ < 100)
                perfectNum_++;
            else if (timer_ % 1 == 0 && perfectNum_ >= 100)
                perfectNum_++;

            if (perfectNum_ >= Game::instance()->perfectNum() || TRG(0) & PAD_START)
            {
                perfectNum_ = Game::instance()->perfectNum();
                performState_++;
                break;
            }
            break;
        }
        //"GREAT"の文字の移動
    case 5:
        if (greatText_pos_.x > GameLib::window::getWidth() - 800)
        {
            greatText_pos_.x -= 30.0f;
            if (greatText_pos_.x <= GameLib::window::getWidth() - 800 || TRG(0) & PAD_START)
            {
                greatText_pos_.x = GameLib::window::getWidth() - 800;
                performState_++;
                break;
            }
            break;
        }
        //"GREAT"の数値を加算
    case 6:
        if (greatNum_ <= Game::instance()->greatNum())
        {

            if (timer_ % 5 == 0 && greatNum_ < 12)
                greatNum_++;
            else if (timer_ % 2 == 0 && 12 <= greatNum_ && greatNum_ < 100)
                greatNum_++;
            else if (timer_ % 1 == 0 && greatNum_ >= 100)
                greatNum_++;

            if (greatNum_ >= Game::instance()->greatNum() || TRG(0) & PAD_START)
            {
                greatNum_ = Game::instance()->greatNum();
                performState_++;
                break;
            }
            break;
        }
        //"GOOD"の文字の移動
    case 7:
        if (goodText_pos_.x > GameLib::window::getWidth() - 800)
        {
            goodText_pos_.x -= 30.0f;
            if (goodText_pos_.x <= GameLib::window::getWidth() - 800 || TRG(0) & PAD_START)
            {
                goodText_pos_.x = GameLib::window::getWidth() - 800;
                performState_++;
                break;
            }
            break;
        }
        //"GOOD"の数値を加算
    case 8:
        if (goodNum_ <= Game::instance()->goodNum())
        {

            if (timer_ % 5 == 0 && goodNum_ < 12)
                goodNum_++;
            else if (timer_ % 2 == 0 && 12 <= goodNum_ && goodNum_ < 100)
                goodNum_++;
            else if (timer_ % 1 == 0 && goodNum_ >= 100)
                goodNum_++;

            if (goodNum_ >= Game::instance()->goodNum() || TRG(0) & PAD_START)
            {
                goodNum_ = Game::instance()->goodNum();
                performState_++;
                break;
            }
            break;
        }
        //"MISS"の文字の移動
    case 9:
        if (missText_pos_.x > GameLib::window::getWidth() - 800)
        {
            missText_pos_.x -= 30.0f;
            if (missText_pos_.x <= GameLib::window::getWidth() - 800 || TRG(0) & PAD_START)
            {
                missText_pos_.x = GameLib::window::getWidth() - 800;
                performState_++;
                break;
            }
            break;
        }
        // "MISS"の数値を加算
    case 10:
        if (missNum_ <= Game::instance()->missNum())
        {
            if (timer_ % 5 == 0 && missNum_ < 12)
                missNum_++;
            else if (timer_ % 2 == 0 && 12 <= missNum_ && missNum_ < 100)
                missNum_++;
            else if (timer_ % 1 == 0 && missNum_ >= 100)
                missNum_++;

            if (missNum_ >= Game::instance()->missNum() || TRG(0) & PAD_START)
            {
                missNum_ = Game::instance()->missNum();
                performState_++;
                break;
            }
            break;
        }
        //"SCORE"の文字の移動
    case 11:
        if (scoreText_pos_.x > GameLib::window::getHeight() / 2 + 60)
        {
            scoreText_pos_.x -= 30.0f;
            if (scoreText_pos_.x <= GameLib::window::getHeight() / 2 + 60 || TRG(0) & PAD_START)
            {
                scoreText_pos_.x = GameLib::window::getHeight() / 2 + 60;
                performState_++;
                break;
            }
            break;
        }
        //"SCORE"の数値を加算
    case 12:
        if (scoreNum_ <= Game::instance()->score())
        {

            scoreNum_ += 100;

            if (scoreNum_ >= Game::instance()->score() || TRG(0) & PAD_START)
            {
                scoreNum_ = Game::instance()->score();
                performState_++;
                break;
            }

            break;
        }
        //ランクの表示
    case 13:

        rank_Scale--;

        if (rank_Scale < 6.0f || TRG(0) & PAD_START)
        {
            rank_Scale = 6.0f;
            performState_++;
            break;
        }

        //プレイヤー入力
    case 14:
        if (title_push_flg_ == false)
        {

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
        }

        switch (score_alpha_num_)
        {
        case 0:
            score_alpha_ -= 0.03f;
            if (score_alpha_ <= 0)   score_alpha_num_++;
            break;

        case 1:
            score_alpha_ += 0.03f;
            if (score_alpha_ >= 1)   score_alpha_num_--;
            break;
        }

        //１(再挑戦)を選んでいるとき
        if (score_select_num_)
        {
            if (TRG(0) & PAD_START)
            {
                music::play(7);
                restart_push_flg_ = true;
            }
        }

        //０(たいとるへ)を選んでいるとき
        if (score_select_num_ == false)
        {
            if (TRG(0) & PAD_START)
            {
                music::play(7);
                title_push_flg_ = true;
                break;
            }
        }
        //restart_push_flg_がtrueの時
        if (restart_push_flg_)
        {
            //TODO:襖の処理
            if (C_L_Fusuma_Pos_.x <= 960 && C_R_Fusuma_Pos_.x >= (960 * 1.5f))
            {
                C_L_Fusuma_Pos_.x += 30;
                C_R_Fusuma_Pos_.x -= 30;
            }

            if (C_L_Fusuma_Pos_.x >= 480 && C_R_Fusuma_Pos_.x <= (960 * 1.5f))
            {
                C_L_Fusuma_Pos_.x = 480;
                C_R_Fusuma_Pos_.x = (960 * 1.5f);

                if (C_Fusuma_timer_ > 60)
                {
                    changeScene(Game::instance());
                    break;
                }

                C_Fusuma_timer_++;
            }
        }

        //title_push_flg_がtrueの時
        if (title_push_flg_)
        {
            for (int i = 0; i < 10; i++)
            {
                shuriken_Pos_[i].x -= 20;
                shuriken_Angle_++;
            }

            if (shuriken_Pos_[9].x <= -500)
            {
                changeScene(Title::instance());
                break;
            }
        }

        break;
    }
}

void Score::scoreDraw() {

    ///// 画像分岐 /////
    //生存したとき
    if (Game::instance()->playerAlive())
    {
        sprClear_.draw(
            { 960,540 },
            { 1.0f,1.0f },
            ToRadian(0),
            { 1.0f, 1.0f, 1.0f, 1.0f }
        );
    }
    //死亡した時
    else
    {
        sprGameover_.draw(
            { 960,540 },
            { 1.0f,1.0f },
            ToRadian(0),
            { 1.0f, 1.0f, 1.0f, 1.0f }
        );
    }

    //スコアの表示
    std::ostringstream ss1, ss2, ss3, ss4, ss5, ss6, ss7;

    ss1 << "SCORE:" << std::setfill('0') << scoreNum_;

    // スコア数をテキスト表示
    font::textOut(6,
        ss1.str(),
        { scoreText_pos_.x, GameLib::window::getHeight() / 2 + 60 },
        { 2.5f, 2.5f },
        { 1.0f, 1.0f, 1.0f, 1.0f },
        TEXT_ALIGN::MIDDLE_LEFT
    );

    ss2 << "MAXCOMBO:" << std::setfill('0') << comboNum_;

    // コンボ数をテキスト表示
    font::textOut(6,
        ss2.str(),
        { comboText_pos_.x, 80 },
        { 2.0f, 2.0f },
        { 1.0f, 1.0f, 1.0f, 1.0f },
        TEXT_ALIGN::MIDDLE_LEFT
    );

    ss3 << "PERFECT X" << std::setfill('0') << perfectNum_;

    // パーフェクト数をテキスト表示
    font::textOut(6,
        ss3.str(),
        { perfectText_pos_.x, 160 },
        { 2.0f, 2.0f },
        { 1.0f, 1.0f, 1.0f, 1.0f },
        TEXT_ALIGN::MIDDLE_LEFT
    );

    ss4 << "GREAT   X" << std::setfill('0') << greatNum_;

    // グレイト数をテキスト表示
    font::textOut(6,
        ss4.str(),
        { greatText_pos_.x , 240 },
        { 2.0f, 2.0f },
        { 1.0f, 1.0f, 1.0f, 1.0f },
        TEXT_ALIGN::MIDDLE_LEFT
    );

    ss5 << "GOOD    X" << std::setfill('0') << goodNum_;

    // グッド数をテキスト表示
    font::textOut(6,
        ss5.str(),
        { goodText_pos_.x, 320 },
        { 2.0f, 2.0f },
        { 1.0f, 1.0f, 1.0f, 1.0f },
        TEXT_ALIGN::MIDDLE_LEFT
    );

    ss6 << "MISS    X" << std::setfill('0') << missNum_;

    // ミス数をテキスト表示
    font::textOut(6,
        ss6.str(),
        { missText_pos_.x, 400 },
        { 2.0f, 2.0f },
        { 1.0f, 1.0f, 1.0f, 1.0f },
        TEXT_ALIGN::MIDDLE_LEFT
    );

    ss7 << "S";

    //ランクをテキスト表示
    font::textOut(6,
        ss7.str(),
        { GameLib::window::getWidth() / 2 + 670 , GameLib::window::getHeight() / 2 + 60 },
        { rank_Scale , rank_Scale },
        { 1.0f, 1.0f, 1.0f, 1.0f },
        TEXT_ALIGN::MIDDLE_LEFT
    );

    if (performState_ == 14)
    {
        //再挑戦を選んでいるとき
        if (score_select_num_)
        {
            //"再挑戦"の文字の描画
            sprRestart_.draw(
                { GameLib::window::getWidth() / 3, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 3 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,score_alpha_ }
            );

            //"たいとるへ"の文字の描画
            sprTotitle_.draw(
                { GameLib::window::getWidth() / 2 + GameLib::window::getWidth() / 4, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 3 },
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
                { GameLib::window::getWidth() / 3, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 3 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,1 }
            );

            //"たいとるへ"の文字の描画
            sprTotitle_.draw(
                { GameLib::window::getWidth() / 2 + GameLib::window::getWidth() / 4, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 3 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,score_alpha_ }
            );
        }
    }

    //手裏剣の描画
    for (int i = 0; i < 10; i++)
    {
        sprShuriken_.draw(
            shuriken_Pos_[i], {1.0f,1.0f},
            ToRadian(shuriken_Angle_)
        );
    }

    //TODO:描画
    //手裏剣の四角
    for (int i = 0; i < 10; i++)
    {
        primitive::rect({ 2400 , shuriken_Pos_[i].y + 32 }, { shuriken_Pos_[i].x - 2400 + 64 , 128 }, { 0,128 }, ToRadian(0) ,{ 0.0f,0.0f,0.0f,1.0f });
    }

    //TODO:描画
    //襖の描画
    sprL_fusuma_.draw(
        C_L_Fusuma_Pos_
    );

    sprR_fusuma_.draw(
        C_R_Fusuma_Pos_
    );


}