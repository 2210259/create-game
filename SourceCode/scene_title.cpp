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
        { static_cast<int>(TEXNUM::SQUARE),  L"./Data/Images/tutorial_icon.png",    1U },
        { static_cast<int>(TEXNUM::START), L"./Data/Images/start.png",              1U },
        { static_cast<int>(TEXNUM::PLAYER), L"./Data/Images/player.png",            1U },
        { static_cast<int>(TEXNUM::L_FUSUMA), L"./Data/Images/L_fusuma.png",        1U },
        { static_cast<int>(TEXNUM::R_FUSUMA), L"./Data/Images/R_fusuma.png",        1U },
        { static_cast<int>(TEXNUM::TITLE_BACK), L"./Data/Images/title.png",         1U }, // タイトル背景
    };

    // テクスチャのロード
    texture::load(loadTextureTitle);
}

// 終了処理
void Title::deinit() {
    
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

        //シーン切り替え用の画像位置の初期化
        T_L_Fusuma_Pos_ = { -960 / 2,540 };
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
        if (timer_ > 120) 
            state_++;
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

            if (Fusuma_timer_ > 60)
                music::stop(6);
                changeScene(Select::instance());

            Fusuma_timer_++;
        }
        break;
    }
    // プレイヤーのアニメーション
    // playerAnime();

    debug::setString("timer_:%d", timer_);
    debug::setString("state_:%d", state_);
    //debug::setString("playerPos_.x:%f", playerPos_.x);
    //debug::setString("playerPos_.y:%f", playerPos_.y);
    //debug::setString("playerScale_.x:%f", playerScale_.x);
    //debug::setString("playerScale_.y:%f", playerScale_.y);
    debug::setString("squareScale_.x%f", squareScale_.x);
    debug::setString("squareScale_.y%f", squareScale_.y);

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
        { GameLib::window::getWidth() / 2, GameLib::window::getHeight() / 2 }
    );

    //"開始"の文字の描画
    sprStart_.draw(
        { GameLib::window::getWidth() - sprStart_.width / 2, GameLib::window::getHeight() - sprStart_.height / 2},
        VECTOR2(1,1), ToRadian(0), titleColor_
    );

    // プレイヤーの描画

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