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
        { static_cast<int>(TEXNOM::TOSELECT), L"./Data/Images/to_select.png", 1U },
        { static_cast<int>(TEXNOM::RESTART),  L"./Data/Images/restart.png", 1U },
        { static_cast<int>(TEXNOM::CLEAR),    L"./Data/Images/clear.png", 1U },
        { static_cast<int>(TEXNOM::GAMEOVER), L"./Data/Images/gameover.png", 1U },
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

        rank_Scale = 50.0f;     //ランクスケールの初期化

        performState_ = 0;                  //演出用ステートの初期化

        C_L_Fusuma_Pos_ = { 960 / 2,540 };     // 左襖の位置の初期化
        C_R_Fusuma_Pos_ = { (960 * 2) - (960 / 2) , 540 }; // 右襖の位置の初期化

        C_Fusuma_timer_ = 0;                   //襖が閉じるまでの時間の初期化

        restart_push_flg_ = false;          //再挑戦を押したときのフラグ

        select_push_flg_ = false;            //TODO:選択へを押したときのフラグ
                                             //ここから下の"title_push_flg_"を
                                             //"select_push_flg_"に変更

        // BGM再生
        GameLib::music::play(5, false);

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);  //通常のアルファ処理

        state_++;
        /*fallthrough*/

    case 1:
        ///// リザルトの演出 /////
        scoreRusult();
        break;
    }

    // デバッグ
    debug::setString("timer_:%d", timer_);
    debug::setString("Game::instance()->perfectNum():%d", Game::instance()->perfectNum());
    timer_++;
}

//描画
void  Score::draw()
{
    //画面クリア
    GameLib::clear(VECTOR4(0.5f, 0.5f, 0.5f, 1.0f));

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

// リザルト表示の処理
void Score::scoreRusult() {
    switch (performState_)
    {
        //ケースの追加
    case 0:
        //音楽が流れるのが早すぎるので一時的に止める
        GameLib::music::pause(5);

        //１秒置いてからスコア表示へ
        if (C_Fusuma_timer_ > 60)
        {
            // 襖開閉音
            GameLib::music::play(11, false);
            C_Fusuma_timer_ = 0;
            performState_++;
            break;
        }
        C_Fusuma_timer_++;
        break;
    case 1:
        // 襖の処理
        if (C_L_Fusuma_Pos_.x > -960 / 2 && C_R_Fusuma_Pos_.x < (960 * 2) + (960 / 2))
        {
            C_L_Fusuma_Pos_.x -= 30;
            C_R_Fusuma_Pos_.x += 30;

            if (C_L_Fusuma_Pos_.x <= -960 / 2 && C_R_Fusuma_Pos_.x >= (960 * 2) + (960 / 2))
            {
                C_L_Fusuma_Pos_.x = -960 / 2;
                C_R_Fusuma_Pos_.x = (960 * 2) + (960 / 2);
                performState_++;
                break;
            }
        }
        break;

        // "MAXCONBO"の文字の移動
    case 2:
        // 音楽の再生
        music::resume(5);
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
    case 3:
        if (comboNum_ <= Game::instance()->maxCombo())
        {
            // SEの再生
            GameLib::music::play(13, false);
            
            //数値の増加速度を数値が高くなるに連れて早くする処理
            if (timer_ % 5 == 0 && comboNum_ < 12)
                comboNum_++;
            else if (timer_ % 2 == 0 && 12 <= comboNum_ && comboNum_ < 100)
                comboNum_++;
            else if (timer_ % 1 == 0 && comboNum_ >= 100)
                comboNum_++;

            //Enterを押してスキップできるように
            if (comboNum_ >= Game::instance()->maxCombo() || TRG(0) & PAD_START)
            {
                comboNum_ = Game::instance()->maxCombo();
                performState_++;
                break;
            }
            break;
        }
        //"PERFECT"の文字の移動
    case 4:
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
        // "PERFECT"の数値を加算
    case 5:
        if (perfectNum_ <= Game::instance()->perfectNum())
        {
            // SEの再生
            GameLib::music::play(13, false);

            //数値の増加速度を数値が高くなるに連れて早くする処理
            if (timer_ % 5 == 0 && perfectNum_ < 12)
                perfectNum_++;
            else if (timer_ % 2 == 0 && 12 <= perfectNum_ && perfectNum_ < 100)
                perfectNum_++;
            else if (timer_ % 1 == 0 && perfectNum_ >= 100)
                perfectNum_++;

            // Enterを押してスキップできるように
            if (perfectNum_ >= Game::instance()->perfectNum() || TRG(0) & PAD_START)
            {
                perfectNum_ = Game::instance()->perfectNum();
                performState_++;
                break;
            }
            break;
        }
        //"GREAT"の文字の移動
    case 6:
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
    case 7:
        if (greatNum_ <= Game::instance()->greatNum())
        {
            // SEの再生
            GameLib::music::play(13, false);

            //数値の増加速度を数値が高くなるに連れて早くする処理
            if (timer_ % 5 == 0 && greatNum_ < 12)
                greatNum_++;
            else if (timer_ % 2 == 0 && 12 <= greatNum_ && greatNum_ < 100)
                greatNum_++;
            else if (timer_ % 1 == 0 && greatNum_ >= 100)
                greatNum_++;

            //Enterを押してスキップできるように
            if (greatNum_ >= Game::instance()->greatNum() || TRG(0) & PAD_START)
            {
                greatNum_ = Game::instance()->greatNum();
                performState_++;
                break;
            }
            break;
        }
        //"GOOD"の文字の移動
    case 8:
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
    case 9:
        if (goodNum_ <= Game::instance()->goodNum())
        {
            // SEの再生
            GameLib::music::play(13, false);

            //数値の増加速度を数値が高くなるに連れて早くする処理
            if (timer_ % 5 == 0 && goodNum_ < 12)
                goodNum_++;
            else if (timer_ % 2 == 0 && 12 <= goodNum_ && goodNum_ < 100)
                goodNum_++;
            else if (timer_ % 1 == 0 && goodNum_ >= 100)
                goodNum_++;

            // Enterを押してスキップできるように
            if (goodNum_ >= Game::instance()->goodNum() || TRG(0) & PAD_START)
            {
                goodNum_ = Game::instance()->goodNum();
                performState_++;
                break;
            }
            break;
        }
        //"MISS"の文字の移動
    case 10:
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
    case 11:
        if (missNum_ <= Game::instance()->missNum())
        {
            // SEの再生
            GameLib::music::play(13, false);

            //数値の増加速度を数値が高くなるに連れて早くする処理
            if (timer_ % 5 == 0 && missNum_ < 12)
                missNum_++;
            else if (timer_ % 2 == 0 && 12 <= missNum_ && missNum_ < 100)
                missNum_++;
            else if (timer_ % 1 == 0 && missNum_ >= 100)
                missNum_++;

            //Enterを押してスキップできるように
            if (missNum_ >= Game::instance()->missNum() || TRG(0) & PAD_START)
            {
                missNum_ = Game::instance()->missNum();
                performState_++;
                break;
            }
            break;
        }
        //"SCORE"の文字の移動
    case 12:
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
    case 13:
        if (scoreNum_ <= Game::instance()->score())
        {
            // SEの再生
            GameLib::music::play(13, false);

            scoreNum_ += 100;

            //Enterを押してスキップできるように
            if (scoreNum_ >= Game::instance()->score() || TRG(0) & PAD_START)
            {
                scoreNum_ = Game::instance()->score();
                performState_++;
                break;
            }

            break;
        }
        //TODO:ランクの表示(分岐処理あり)
    case 14:
        rank_Scale--;

        if (rank_Scale < 6.0f || TRG(0) & PAD_START)
        {
            // ランク音
            GameLib::music::play(14, false);

            rank_Scale = 6.0f;
            performState_++;
            break;
        }
        break;

        //プレイヤー入力
    case 15:
        if (select_push_flg_ == false)
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
            if (TRG(0) & PAD_START&& restart_push_flg_ == false && select_push_flg_ == false)
            {
                music::play(8,false);
                restart_push_flg_ = true;
                performState_++;
                break;
            }
        }

        //０(たいとるへ)を選んでいるとき
        if (score_select_num_ == false&& restart_push_flg_ == false && select_push_flg_ == false)
        {
            if (TRG(0) & PAD_START)
            {
                music::play(8,false);
                select_push_flg_ = true;
                performState_++;
                break;
            }
        }
        break;

    case 16:

        if (C_Fusuma_timer_ > 30) {
            // 襖開閉音
            GameLib::music::play(11, false);
            performState_++;
            C_Fusuma_timer_ = 0;
        }

        C_Fusuma_timer_++;
        break;
    case 17:
        //restart_push_flg_がtrueの時
        if (restart_push_flg_) {
            // 襖の処理
            if (C_L_Fusuma_Pos_.x <= 960 && C_R_Fusuma_Pos_.x >= (960 * 1.5f))
            {
                C_L_Fusuma_Pos_.x += 30;
                C_R_Fusuma_Pos_.x -= 30;
            }

            if (C_L_Fusuma_Pos_.x >= 480 && C_R_Fusuma_Pos_.x <= (960 * 1.5f))
            {
                C_L_Fusuma_Pos_.x = 480;
                C_R_Fusuma_Pos_.x = (960 * 1.5f);

                //１秒置いてから遷移
                if (C_Fusuma_timer_ > 60)
                {
                    changeScene(Game::instance());
                    break;
                }

                C_Fusuma_timer_++;
            }
        }

        // title_push_flg_がtrueの時
        if (select_push_flg_)
        {
            //襖の処理
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
                    changeScene(Select::instance());
                    break;
                }

                C_Fusuma_timer_++;
            }
        }
        break;
    }
    // デバッグ
    debug::setString("state:%d", performState_);
}

void Score::scoreDraw()
{

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

    if (performState_ >= 14)
    {
        //ランクをテキスト表示(分岐あり)
        //プレイヤーが生きていたら
        if (Game::instance()->playerAlive())
        {
            //チュートリアルステージの時
            if (Game::instance()->stageNo() == 0)
            {
                if (Game::instance()->score() < 30000) ss7 << "C";
                else if (Game::instance()->score() < 40000) ss7 << "B";
                else if (Game::instance()->score() < 50000) ss7 << "A";
                else                                        ss7 << "S";
            }
            //ステージ１の時
            if (Game::instance()->stageNo() == 1)
            {
                //完成してから決める
                if (Game::instance()->score() < 50000) ss7 << "C";
                else if (Game::instance()->score() < 70000) ss7 << "B";
                else if (Game::instance()->score() < 90000) ss7 << "A";
                else                                        ss7 << "S";
            }
        }
        //プレイヤーが死んでいたら
        else
        {
            ss7 << "E";
        }

        // ランクをテキスト表示(分岐あり)
        font::textOut(6,
            ss7.str(),
            { GameLib::window::getWidth() / 2 + 670 , GameLib::window::getHeight() / 2 + 60 },
            { rank_Scale , rank_Scale },
            { 1.0f, 1.0f, 1.0f, 1.0f },
            TEXT_ALIGN::MIDDLE_LEFT
        );
    }
    //スコア表示が終わってから
    if (performState_ == 15)
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

            // "選択へ"の文字の描画
            sprToselect_.draw(
                { GameLib::window::getWidth() / 2 + GameLib::window::getWidth() / 4, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 3 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,1 }
            );
        }

        // 選択へを選んでいるとき
        if (score_select_num_ == false)
        {
            //"再挑戦"の文字の描画
            sprRestart_.draw(
                { GameLib::window::getWidth() / 3, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 3 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,1 }
            );

            // "選択へ"の文字の描画
            sprToselect_.draw(
                { GameLib::window::getWidth() / 2 + GameLib::window::getWidth() / 4, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 3 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,score_alpha_ }
            );
        }
    }

    // 襖の描画
    sprL_fusuma_.draw(
        C_L_Fusuma_Pos_
    );

    sprR_fusuma_.draw(
        C_R_Fusuma_Pos_
    );
}