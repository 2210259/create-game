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

    // 読み込むテクスチャ
    GameLib::LoadTexture loadTextureSelect[static_cast<size_t>(TEXNO::NUM)] = {
        { static_cast<int>(TEXNO::STAR),  L"./Data/Images/star.png", 1U },
        { static_cast<int>(TEXNO::BACK),  L"./Data/Images/stage_select.png", 1U },
        { static_cast<int>(TEXNO::TUTORIAL),  L"./Data/Images/tutorial_icon.png", 1U },
        { static_cast<int>(TEXNO::STAGE1),  L"./Data/Images/stage1_icon.png", 1U },
        { static_cast<int>(TEXNO::STAGE2),  L"./Data/Images/stage2_icon.png", 1U },
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
        fadeOutTimer_ = 0.0f;               // フェードアウト用変数の初期設定

        stageNum_ = 0;
        starScale_ = { 0.0f, 0.0f };
        starAngle_ = 0.0f;

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // 通常のアルファ処理

        music::play(4, true);   //BGMの再生

        state_++;                                            // 初期化処理の終了

        /*fallthrough*/

    case 1:
        //////// フェードイン中 ////////
        starAngle_ -= ToRadian(4);
        starScale_ += { 0.1f, 0.1f };

        if (starScale_.x > 8.0) {
            starScale_ = { 8.0f , 8.0f };
            ++state_;   // 通常の処理へ
        }
        break;

    case 2:
        //////// 通常時の処理 ////////

        //ステージ選択用
        if (TRG(0) & PAD_LEFT)
        {
            if(stageNum_ > 0)
            stageNum_--;
        }

        if (TRG(0) & PAD_RIGHT)
        {
            if(stageNum_ < 2)
            stageNum_++;
        }

        //選択している画像のα値とスケールの変更
        switch (stageNum_)
        {
        //チュートリアル選択中
        case 0:
            tutorialAlpha_ = 1.0f;            
            tutorialScale_ = { 0.6f , 0.6f };

            stage1Alpha_ = 0.2f;
            stage1Scale_ = { 0.5f , 0.5f };

            stage2Alpha_ = 0.2f;
            stage2Scale_ = { 0.5f , 0.5f };
            break;

        //ステージ１選択中
        case 1:
            tutorialAlpha_ = 0.2f;
            tutorialScale_ = { 0.5f , 0.5f };

            stage1Alpha_ = 1.0f;
            stage1Scale_ = { 0.6f , 0.6f };

            stage2Alpha_ = 0.2f;
            stage2Scale_ = { 0.5f , 0.5f };
            break;

        //ステージ２選択中
        case 2:
            tutorialAlpha_ = 0.2f;
            tutorialScale_ = { 0.5f , 0.5f };

            stage1Alpha_ = 0.2f;
            stage1Scale_ = { 0.5f , 0.5f };

            stage2Alpha_ = 1.0f;
            stage2Scale_ = { 0.6f , 0.6f };
            break;
        }

        if (TRG(0) & PAD_START)
        {
            ++state_;
        }
        break;

    case 3:
        //////// フェードアウト中 ////////
        starAngle_ += ToRadian(4);
        starScale_ -= { 0.1f, 0.1f };

        if (starScale_.x < 0) {
            starScale_ = { 0.0f, 0.0f };
        }

        fadeOutTimer_ += 0.01167f;
        if (fadeOutTimer_ >= 1.0f) {
            changeScene(Game::instance());
            break;
        }

        break;
    }

    GameLib::debug::setString("state_:%d", state_);
    GameLib::debug::setString("timer_:%d", timer_);
    GameLib::debug::setString("stageNum_:%d", stageNum_);
    timer_++;
}

// 描画
void Select::draw() {
    // 画面クリア
    GameLib::clear(VECTOR4(0.0f, 0.0f, 1.0f, 1));

    // ステンシルモード：通常
    DepthStencil::instance().set(DepthStencil::MODE::NONE);

    // ステンシルモード：マスク生成
    DepthStencil::instance().set(DepthStencil::MODE::MASK);

    // 星を描画
    sprStar_.draw(
        { GameLib::window::getWidth() / 2, GameLib::window::getHeight() / 2 },
        { starScale_.x , starScale_.y },
        starAngle_
    );

    // ステンシルモード：マスクに描画
    DepthStencil::instance().set(DepthStencil::MODE::APPLY_MASK);

    // タイトルの描画
    //GameLib::font::textOut(4, "StageSelect",
    //    { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 3) },
    //    VECTOR2(5.0f, 5.0f),
    //    { 1.0f, 1.0f, 1.0f, 1.0f },
    //    GameLib::TEXT_ALIGN::UPPER_MIDDLE
    //);

    //背景の描画
    sprBack_.draw(
        { 960,540 },
        { 1.0f,1.0f }
    );

    //チュートリアルアイコンの描画
    sprTutorial_.draw(
        { GameLib::window::getWidth() / 2 - (GameLib::window::getWidth() / 2) / 2 , GameLib::window::getHeight() / 2 },
        tutorialScale_,
        ToRadian(0),
        { 1.0f,1.0f,1.0f,tutorialAlpha_}
    );

    //ステージ１アイコンの描画
    sprStage1_.draw(
        { GameLib::window::getWidth() / 2 , GameLib::window::getHeight() / 2 },
        stage1Scale_,
        ToRadian(0),
        { 1.0f,1.0f,1.0f,stage1Alpha_}
    );

    //ステージ２アイコンの描画
    sprStage2_.draw(
        { GameLib::window::getWidth() / 2 + (GameLib::window::getWidth() / 2) / 2 , GameLib::window::getHeight() / 2 },
        stage2Scale_,
        ToRadian(0),
        { 1.0f,1.0f,1.0f,stage2Alpha_}
    );


    // Push Enter Key の描画
    //if (timer_ >> 5 & 0x01) {
    //    GameLib::font::textOut(4, "Push Enter Key",
    //        { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 6) * 5 },
    //        VECTOR2(1.5f, 1.5f),
    //        { 1.0f, 1.0f, 1.0f, 1.0f },
    //        GameLib::TEXT_ALIGN::LOWER_MIDDLE
    //    );
    //}

    // フェードアウト
    // if (fadeOutTimer_ > 0.0f) {
    //     DepthStencil::instance().set(DepthStencil::MODE::APPLY_MASK);
    //     GameLib::primitive::rect({ 0, 0 }, 
    //         { GameLib::window::getWidth(), GameLib::window::getHeight() },
    //         { 0, 0 }, 0, { 0, 0, 0, fadeOutTimer_ });
    // }

    // ステンシルモード：マスク以外に描画
    DepthStencil::instance().set(DepthStencil::MODE::EXCLUSIVE);

    // 四角形
    GameLib::primitive::rect({ 0, 0 },
        { GameLib::window::getWidth(), GameLib::window::getHeight() },
        { 0, 0 },
        ToRadian(0),
        { 0.0f, 0.0f, 0.0f, 1.0f }
    );
}
