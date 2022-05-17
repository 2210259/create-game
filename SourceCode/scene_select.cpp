//******************************************************************************
//
//
//      セレクト画面
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< 変数 >----------------------------------------------------------------
Select Select::instance_;

// 初期設定
void Select::init() {
    Scene::init();	    // 基底クラスのinitを呼ぶ

    //TODO:変更
    // 読み込むテクスチャ
    GameLib::LoadTexture loadTextureSelect[static_cast<size_t>(TEXNO::NUM)] = {
        { static_cast<int>(TEXNO::BACK),  L"./Data/Images/stage_select.png", 1U },
        { static_cast<int>(TEXNO::TUTORIAL),  L"./Data/Images/tutorial_icon.png", 1U },
        { static_cast<int>(TEXNO::STAGE1),  L"./Data/Images/stage1_icon.png", 1U },
        { static_cast<int>(TEXNO::STAGE2),  L"./Data/Images/stage2_icon.png", 1U },
        { static_cast<int>(TEXNO::L_FUSUMA),  L"./Data/Images/L_fusuma.png", 1U },
        { static_cast<int>(TEXNO::R_FUSUMA),  L"./Data/Images/R_fusuma.png", 1U },

    };                    
                        
    // テクスチャのロード
    GameLib::texture::load(loadTextureSelect);
}

// 終了処理
void Select::deinit() {
    // テクスチャを全て解放
    GameLib::texture::releaseAll();
}

// 更新
void Select::update() {

    using namespace input;
    switch (state_) {
    case 0:
        //////// 初期設定 ////////
        timer_ = 0;                         // タイマーを初期化

        stageNum_ = 0;                      //ステージ番号の初期化

        //アイコンの位置の初期化
        tutorial_icon_Pos_ = { GameLib::window::getWidth() / 2 - (GameLib::window::getWidth() / 2) / 2 , GameLib::window::getHeight() / 2 };
        stage1_icon_Pos_ = { GameLib::window::getWidth() / 2 , GameLib::window::getHeight() / 2 };
        stage2_icon_Pos_ = { GameLib::window::getWidth() / 2 + (GameLib::window::getWidth() / 2) / 2 , GameLib::window::getHeight() / 2 };

        //アイコンのα値の初期化
        tutorial_icon_Alpha_ = 1.0f;
        stage1_icon_Alpha_ = 1.0f;
        stage2_icon_Alpha_ = 1.0f;

        //アイコンのスケールの初期化
        tutorial_icon_Scale_ = { 0.5f , 0.5f };
        stage1_icon_Scale_ = { 0.5f , 0.5f };
        stage2_icon_Scale_ = { 0.5f , 0.5f };
        
        //シーン切り替え用の画像位置の初期化
        S_L_Fusuma_Pos_ = { 960 / 2,540 };     // 左襖の位置の初期化
        S_R_Fusuma_Pos_ = { (960 * 2) - (960 / 2) , 540 }; // 右襖の位置の初期化

        //襖のタイマーの初期化
        Fusuma_timer_ = 0;

        //フラグの初期化
        push_flg = false;

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // 通常のアルファ処理

        music::play(7, true);   //BGMの再生

        state_++;                                            // 初期化処理の終了

        /*fallthrough*/

    case 1:
        //////// フェードイン中 ////////

        // 襖の処理
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
        //////// 通常時の処理 ////////

        // 追加
        if (push_flg == false)
        {
            //ステージ選択用
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
        //選択している画像のα値とスケールの変更
        switch (stageNum_)
        {
        //チュートリアル選択中
        case 0:
            tutorial_icon_Alpha_ = 1.0f;
            
            //アイコンのスケールが大きくなかったら大きくする
            if (tutorial_icon_Scale_.x < 0.6f && tutorial_icon_Scale_.y < 0.6f)
            {
                tutorial_icon_Scale_.x += 0.005f;
                tutorial_icon_Scale_.y += 0.005f;
            }

            stage1_icon_Alpha_ = 0.2f;

            //アイコンのスケールが大きかったら小さくする
            if (stage1_icon_Scale_.x > 0.5f && stage1_icon_Scale_.y > 0.5f)
            {
                stage1_icon_Scale_.x -= 0.005f;
                stage1_icon_Scale_.y -= 0.005f;
            }

            stage2_icon_Alpha_ = 0.2f;

            //アイコンのスケールが大きかったら小さくする
            if (stage2_icon_Scale_.x > 0.5f && stage2_icon_Scale_.y > 0.5f)
            {
                stage2_icon_Scale_.x -= 0.005f;
                stage2_icon_Scale_.y -= 0.005f;
            }
            break;

        //ステージ１選択中
        case 1:
            tutorial_icon_Alpha_ = 0.2f;

            //アイコンのスケールが大きかったら小さくする
            if (tutorial_icon_Scale_.x > 0.5f && tutorial_icon_Scale_.y > 0.5f)
            {
                tutorial_icon_Scale_.x -= 0.005f;
                tutorial_icon_Scale_.y -= 0.005f;
            }

            stage1_icon_Alpha_ = 1.0f;

            //アイコンのスケールが大きくなかったら大きくする
            if (stage1_icon_Scale_.x < 0.6f && stage1_icon_Scale_.y < 0.6f)
            {
                stage1_icon_Scale_.x += 0.005f;
                stage1_icon_Scale_.y += 0.005f;
            }

            stage2_icon_Alpha_ = 0.2f;

            //アイコンのスケールが大きかったら小さくする
            if (stage2_icon_Scale_.x > 0.5f && stage2_icon_Scale_.y > 0.5f)
            {
                stage2_icon_Scale_.x -= 0.005f;
                stage2_icon_Scale_.y -= 0.005f;
            }
            break;

        //ステージ２選択中
        case 2:
            tutorial_icon_Alpha_ = 0.2f;

            //アイコンのスケールが大きかったら小さくする
            if (tutorial_icon_Scale_.x > 0.5f && tutorial_icon_Scale_.y > 0.5f)
            {
                tutorial_icon_Scale_.x -= 0.005f;
                tutorial_icon_Scale_.y -= 0.005f;
            }

            stage1_icon_Alpha_ = 0.2f;

            //アイコンのスケールが大きかったら小さくする
            if (stage1_icon_Scale_.x > 0.5f && stage1_icon_Scale_.y > 0.5f)
            {
                stage1_icon_Scale_.x -= 0.005f;
                stage1_icon_Scale_.y -= 0.005f;
            }

            stage2_icon_Alpha_ = 1.0f;

            //アイコンのスケールが大きくなかったら大きくする
            if (stage2_icon_Scale_.x < 0.6f && stage2_icon_Scale_.y < 0.6f)
            {
                stage2_icon_Scale_.x += 0.005f;
                stage2_icon_Scale_.y += 0.005f;
            }
            break;
        }

        //Enterが押された時
        if (TRG(0) & PAD_START && push_flg == false)
        {
            //決定音
            GameLib::music::play(8, false);
            push_flg = true;
        }

        //もしpush_flgがtrueだったら
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

// 描画
void Select::draw() {

    //TODO:マスク処理の削除＆描画の追加
    // 画面クリア
    GameLib::clear(VECTOR4(0.0f, 0.0f, 1.0f, 1));

    //背景の描画
    sprBack_.draw(
        { 960,540 },
        { 1.0f,1.0f }
    );

    //チュートリアルアイコンの描画
    sprTutorial_.draw(
        tutorial_icon_Pos_,
        tutorial_icon_Scale_,
        ToRadian(0),
        { 1.0f,1.0f,1.0f,tutorial_icon_Alpha_}
    );

    //ステージ１アイコンの描画
    sprStage1_.draw(
        stage1_icon_Pos_,
        stage1_icon_Scale_,
        ToRadian(0),
        { 1.0f,1.0f,1.0f,stage1_icon_Alpha_}
    );

    //ステージ２アイコンの描画
    sprStage2_.draw(
        stage2_icon_Pos_,
        stage2_icon_Scale_,
        ToRadian(0),
        { 1.0f,1.0f,1.0f,stage2_icon_Alpha_}
    );

    //襖の描画
    sprL_fusuma_.draw(
        S_L_Fusuma_Pos_
    );

    sprR_fusuma_.draw(
        S_R_Fusuma_Pos_
    );
}
