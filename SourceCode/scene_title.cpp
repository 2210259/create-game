//******************************************************************************
//
//
//      scene_title.cpp
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;
using namespace input;

//------< 変数 >----------------------------------------------------------------
Title Title::instance_;

// 初期設定
void Title::init() {
    Scene::init();	    // 基底クラスのinitを呼ぶ

    //データ、TEXNUMの変更
    // 読み込むテクスチャ
    LoadTexture loadTextureTitle[static_cast<size_t>(TEXNUM::NUM)] = {
        { static_cast<int>(TEXNUM::SQUARE),  L"./Data/Images/stage2_icon.png",    1U },
        { static_cast<int>(TEXNUM::L_FUSUMA), L"./Data/Images/L_fusuma.png",      1U },
        { static_cast<int>(TEXNUM::R_FUSUMA), L"./Data/Images/R_fusuma.png",      1U },
        { static_cast<int>(TEXNUM::START), L"./Data/Images/start.png",            1U },
        { static_cast<int>(TEXNUM::TITLE_BACK), L"./Data/Images/title.png",       7U }, // タイトル背景
        { static_cast<int>(TEXNUM::T_AORENTER), L"./Data/Images/textAorEnter.png",1U }
    };

    // テクスチャのロード
    texture::load(loadTextureTitle);
}

// 終了処理
void Title::deinit()
{    
    // テクスチャを全て解放
    texture::releaseAll();
}

// 更新
void Title::update() {
    
    switch (state_) {
    case 0:
        //////// 初期設定 ////////
        timer_ = 0;                         // タイマーを初期化
        switchNum = 0;

        squarePos_ = { -window::getWidth() , -window::getHeight() };
        squareScale_ = { 8.0f, 0.02f };
        squareAngle_ = 29.0f;

        playerPos_ = { BG::WINDOW_W / 4, 1000 };
        playerScale_ = { 5.0f, 5.0f };
        playerColor_ = { 1, 1, 1, 1 };
        playerTexPos_ = { 0, 0 };
        titleColor_ = { 1, 1 ,1 ,1 };
        titleBackTexPos_ = {};

        //シーン切り替え用の画像位置の初期化
        T_L_Fusuma_Pos_ = { -960 / 2, 540 };
        T_R_Fusuma_Pos_ = { (960 * 2) + (960 / 2) , 540 };

        Fusuma_timer_ = 0;

        //BGMを再生
        GameLib::music::play(6, false);

        GameLib::music::play(12, false);

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // 通常のアルファ処理

        state_++;                                            // 初期化処理の終了

        /*fallthrough*/

    case 1:
        //////// フェードイン中 ////////

        //四角形の移動
        if (squarePos_.x < window::getWidth() / 2 && squarePos_.y < window::getHeight() / 2)
        {
            squarePos_.x += 100 * 3;
            squarePos_.y += 56.2f * 3;
        }
        //四角形が指定の位置に行ったら固定
        else {
            squarePos_.x = window::getWidth() / 2;
            squarePos_.y = window::getHeight() / 2;
        }

        //スケールを変化させる(ゆっくり)
        if (squarePos_.x >= window::getWidth() / 2 && squarePos_.y >= window::getHeight() / 2 &&
            squareScale_.y < 0.05f) {
            squareScale_.y += 0.001f;
        }
        //スケールを変化させる(早い)
        else if (squarePos_.x >= window::getWidth() / 2 && squarePos_.y >= window::getHeight() / 2 &&
            squareScale_.y >= 0.05f)
        {
            squareScale_.y += 0.1f;
            //スケールの値を固定
            if (squareScale_.y >= 5.5f)
            {
                squareScale_.y = 5.5f;
                state_++;
                break;
            }
        }
        break;

    case 2:
        //////// 通常時の処理 ////////

        if (TRG(0) & PAD_START) {
            //決定音
            GameLib::music::play(8, false);

            // プレイヤーの処理へ
            timer_ = 0;
            state_++;
        }
        break;
    case 3:
        //////// 通常時の処理 ////////
        if (timer_ % 10 == 0 && titleColor_.w > 0) {
            titleColor_.w = 0;
        }
        else if (timer_ % 10 == 0 && titleColor_.w <= 0) {
            titleColor_.w = 1;
        }
        if (timer_ > 50)
        {
            //襖開閉音
            GameLib::music::play(11, false);
            state_++;
            timer_ = 0;
        }
        break;
    case 4:
        //////// 襖の処理 ////////
        if (T_L_Fusuma_Pos_.x <= 960 && T_R_Fusuma_Pos_.x >= (960 * 1.5f))
        {
            T_L_Fusuma_Pos_.x += 30;
            T_R_Fusuma_Pos_.x -= 30;
        }

        if (T_L_Fusuma_Pos_.x >= 480 && T_R_Fusuma_Pos_.x <= (960 * 1.5f))
        {
            T_L_Fusuma_Pos_.x = 480;
            T_R_Fusuma_Pos_.x = (960 * 1.5f);

            if (Fusuma_timer_ > 60) {
                music::stop(6);
                changeScene(Select::instance());
                break;
            }
            Fusuma_timer_++;
        }
        break;
    }
    // プレイヤーのアニメーション
    if (state_ == 3 && timer_ > 35 && timer_ % 5 == 1 || state_ == 4 && timer_ % 5 == 1 && titleBackTexPos_.x < 11520) {
        titleBackTexPos_.x += BG::WINDOW_W;
    }

    timer_++;
}

// 描画
void Title::draw() {
    // 画面クリア
    GameLib::clear(VECTOR4(0.5f, 0.5f, 0.5f, 1.0f));

    // ステンシルモード：通常
    DepthStencil::instance().set(DepthStencil::MODE::NONE);

    // ステンシルモード：マスク生成
    DepthStencil::instance().set(DepthStencil::MODE::MASK);

    // 四角を描画
    sprSquare_.draw(
        squarePos_,
        squareScale_,
        squareAngle_ * PI / 180
    );

    // ステンシルモード：マスクに描画
    DepthStencil::instance().set(DepthStencil::MODE::APPLY_MASK);
    
    // タイトルの描画
    sprTitleBack_.draw(
        { BG::WINDOW_W / 2, BG::WINDOW_H / 2 },
        VECTOR2(1,1),
        titleBackTexPos_.x, titleBackTexPos_.y, GameLib::window::getWidth(), GameLib::window::getHeight()
    );

    //"開始"の文字の描画
    sprStart_.draw(
        { GameLib::window::getWidth() - sprStart_.width / 2, GameLib::window::getHeight() - sprStart_.height / 2},
        VECTOR2(1,1), ToRadian(0), titleColor_
    );

    // textの描画
    if (timer_ >> 5 & 0x01 && state_ < 3) {
        sprAorEnter.draw(1450, 680);
    }

    // ステンシルモード：マスク以外に描画
    DepthStencil::instance().set(DepthStencil::MODE::EXCLUSIVE);
    
    // 四角形
    GameLib::primitive::rect({ 0, 0 },
        { GameLib::window::getWidth(), GameLib::window::getHeight() },
        { 0, 0 },
        ToRadian(0),
        { 0.0f, 0.0f, 0.0f, 1.0f }
    );

    // ステンシルモード：通常
    DepthStencil::instance().set(DepthStencil::MODE::NONE);

    // 襖の描画
    sprL_fusuma_.draw(T_L_Fusuma_Pos_);
    sprR_fusuma_.draw(T_R_Fusuma_Pos_);
}

void Title::playerAnime() {
    switch (switchNum)
    {
    case 0:
        playerTexPos_ = { 0, 0 };
        if (timer_ % 10 == 0)
            switchNum++;
        break;
    case 1:
        playerTexPos_ = { 150, 0 };
        if (timer_ % 10 == 0)
            switchNum--;
        break;
    }
    debug::setString("playerTexPos_:%f", playerTexPos_.x);
    debug::setString("switchNum:%d", switchNum);
}