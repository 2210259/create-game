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

    // 読み込むテクスチャ
    LoadTexture loadTextureTitle[static_cast<size_t>(TEXNUM::NUM)] = {
        { static_cast<int>(TEXNUM::STAR),  L"./Data/Images/star.png", 1U },
        { static_cast<int>(TEXNUM::START), L"./Data/Images/start.png", 1U },
        { static_cast<int>(TEXNUM::PLAYER), L"./Data/Images/player.png", 1U },
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
        fadeOutTimer_ = 0.0f;               // フェードアウト用変数の初期設定
        switchNum = 0;
        starScale_ = { 0.0f, 0.0f };
        starAngle_ = 0.0f;

        playerPos_      = { BG::WINDOW_W / 4, 1000 };
        playerScale_    = { 5.0f, 5.0f };
        playerColor_    = { 1, 1, 1, 1 };
        playerTexPos_   = { 0, 0 };
        
        //BGMを再生
        GameLib::music::play(5, false);

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // 通常のアルファ処理
                 
        state_++;                                            // 初期化処理の終了

        /*fallthrough*/

    case 1:
        //////// フェードイン中 ////////
        starAngle_ -= ToRadian(4);
        starScale_ += { 0.2f, 0.2f };

        if (starScale_.x > 15.0) {
            starScale_ = { 15.0f , 15.0f };
            ++state_;   // 通常の処理へ
        }
        break;

    case 2:
        //////// 通常時の処理 ////////

        if (TRG(0) & PAD_START) {

            //決定音
            GameLib::music::play(7, false);

            ++state_;   // フェードアウトへ
        }

        break;

    case 3:
        //////// フェードアウト中 ////////
        starAngle_ += ToRadian(4);
        starScale_ -= { 0.2f , 0.2f };

        if (starScale_.x < 0) {
            starScale_ = { 0.0f, 0.0f };
            //BGMを止める
            GameLib::music::stop(5);
            changeScene(Select::instance());
            break;
        }
        break;
    }
    // プレイヤーのアニメーション
    // playerAnime();

    debug::setString("timer_:%d", timer_);
    debug::setString("state_:%d", state_);
    debug::setString("playerPos_.x:%f", playerPos_.x);
    debug::setString("playerPos_.y:%f", playerPos_.y);
    debug::setString("playerScale_.x:%f", playerScale_.x);
    debug::setString("playerScale_.y:%f", playerScale_.y);

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

    // 星を描画
    sprStar_.draw(
        { GameLib::window::getWidth() / 2, GameLib::window::getHeight() / 2 },
        { starScale_.x , starScale_.y },
        starAngle_
    );

    // ステンシルモード：マスクに描画
    DepthStencil::instance().set(DepthStencil::MODE::APPLY_MASK);

    // タイトルの描画
    GameLib::font::textOut(4, "NoName",
        { GameLib::window::getWidth() / 4 * 3, (GameLib::window::getHeight() / 4) },
        VECTOR2(2.0f, 2.0f),
        { 1.0f, 1.0f, 1.0f, 1.0f },
        GameLib::TEXT_ALIGN::UPPER_RIGHT
    );

    //"開始"の文字の描画
    sprStart_.draw(
        { GameLib::window::getWidth() - sprStart_.width / 2, GameLib::window::getHeight() - sprStart_.height / 2 }
    );

    // プレイヤーの描画

    // sprPlayer_.draw(
    //     { playerPos_.x, playerPos_.y }, 
    //     { playerScale_.x, playerScale_.y },
    //     0,
    //     playerColor_
    // );

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