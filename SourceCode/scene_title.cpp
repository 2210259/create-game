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
    LoadTexture loadTextureTitle[static_cast<size_t>(TEXNOM::NUM)] = {
        { static_cast<int>(TEXNOM::STAR),  L"./Data/Images/star.png", 1U },
        { static_cast<int>(TEXNOM::START),  L"./Data/Images/start.png", 1U },
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

        starScale_ = { 0.0f, 0.0f };
        starAngle_ = 0.0f;

        playerPos_      = { 320, 600 };
        playerScale_    = { 1.0f, 1.0f };
        playerTexPos_   = { 0, 0 };
        playerTexSize_  = { 150, 150 };

        //BGMを再生
        GameLib::music::play(5, false);

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // 通常のアルファ処理
                 
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

        if (TRG(0) & PAD_START) {

            //決定音
            GameLib::music::play(7, false);

            ++state_;   // フェードアウトへ
        }

        break;

    case 3:
        //////// フェードアウト中 ////////
        starAngle_ += ToRadian(4);
        starScale_ -= { 0.1f , 0.1f };

        if (starScale_.x < 0) {
            starScale_ = { 0.0f, 0.0f };
        }

        fadeOutTimer_ += 0.01167f;
        if (fadeOutTimer_ >= 1.0f) {
            //BGMを止める
            GameLib::music::stop(5);
            changeScene(Game::instance());
            break;
        }
        break;
    }

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
    // texture::begin(TEXNO::PLAYER);
    // texture::draw(TEXNO::PLAYER, playerPos_, playerScale_,
    //     playerTexPos_, playerTexSize_);
    // texture::end(TEXNO::PLAYER);

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