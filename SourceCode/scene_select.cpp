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
    GameLib::LoadTexture loadTextureSelect[static_cast<size_t>(TEXNOM::NUM)] = {
        { static_cast<int>(TEXNOM::BACK),  L"./Data/Images/stage_select.png", 1U },
        { static_cast<int>(TEXNOM::TUTORIAL),  L"./Data/Images/tutorial_icon.png", 1U },
        { static_cast<int>(TEXNOM::STAGE1),  L"./Data/Images/stage1_icon.png", 1U },
        { static_cast<int>(TEXNOM::L_FUSUMA),  L"./Data/Images/L_fusuma.png", 1U },
        { static_cast<int>(TEXNOM::R_FUSUMA),  L"./Data/Images/R_fusuma.png", 1U },
        { static_cast<int>(TEXNOM::TOTITLE),  L"./Data/Images/to_title_icon.png", 1U },
        { static_cast<int>(TEXNOM::SHURIKEN),  L"./Data/Images/no-tsu01.png", 12U },
        { static_cast<int>(TEXNOM::DECORATION),  L"./Data/Images/decoration_icon.png", 1U },
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

        //全てのアイコンの位置の初期化        
        title_icon_Pos_ = { window::getWidth() / 4 - 200, window::getHeight() / 2 + 150 };
        tutorial_icon_Pos_ = { window::getWidth() / 2 - 200, window::getHeight() / 2 + 150 };
        stage1_icon_Pos_ = { window::getWidth() / 2 + window::getWidth() / 4 - 200, window::getHeight() / 2 + 150 };

        //全てのアイコンのα値の初期化
        tutorial_icon_Alpha_ = 0.2f;
        stage1_icon_Alpha_ = 0.2f;
        title_icon_Alpha_ = 1.0f;

        //全てのアイコンのスケールの初期化
        tutorial_icon_Scale_ = { 0.5f + 0.1f, 0.5f + 0.1f };
        stage1_icon_Scale_ = { 0.5f + 0.1f, 0.5f + 0.1f };
        title_icon_Scale_ = { 0.5f + 0.1f,0.5f + 0.1f };

        //シーン切り替え用の画像位置の初期化
        S_L_Fusuma_Pos_ = { 960 / 2,540 };     // 左襖の位置の初期化
        S_R_Fusuma_Pos_ = { (960 * 2) - (960 / 2) , 540 }; // 右襖の位置の初期化

        //襖のタイマーの初期化
        Fusuma_timer_ = 0;

        //フラグの初期化
        push_flg = false;

        //遷移用手裏剣位置の初期化
        for (int i = 0; i < 10; i++)
        {
            shuriken_Pos_[i].x = static_cast<float>(2400 + (128 * i));
            shuriken_Pos_[i].y = static_cast<float>(128 * i);
        }

        //遷移用手裏剣の初期化
        shuriken_Angle_ = 0;

        //タイトルを押したかどうか
        title_push_flg_ = false;

        // クナイの初期設定
        stagingShuriken_[0].pos = { -150, 150 };
        stagingShuriken_[1].pos = { 2070,150 }; // 1770
        stagingShuriken_[0].scale = { 1.5f, 1.5f };
        stagingShuriken_[1].scale = { 1.5f, 1.5f };
        stagingShuriken_[0].angle = {};
        stagingShuriken_[1].angle = {};

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // 通常のアルファ処理

        //セレクト画面BGMの再生
        music::play(7, true);

        //襖の開閉音
        GameLib::music::play(11, false);

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

        //Enterを１回も押してなかったら
        if (push_flg == false)
        {
            //ステージ選択(プレイヤー入力)
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
            //タイトルへ選択中
        case 0:

            //α値を固定
            title_icon_Alpha_ = 1.0f;

            //アイコンのスケールが大きくなかったら指定の大きさまで大きくする
            if (title_icon_Scale_.x < 0.6f + 0.1f && title_icon_Scale_.y < 0.6f + 0.1f)
            {
                title_icon_Scale_.x += 0.005f;
                title_icon_Scale_.y += 0.005f;
            }

            //α値を固定
            tutorial_icon_Alpha_ = 0.2f;

            //アイコンのスケールが大きかったら指定の大きさまで小さくする
            if (tutorial_icon_Scale_.x > 0.5f + 0.1f && tutorial_icon_Scale_.y > 0.5f + 0.1f)
            {
                tutorial_icon_Scale_.x -= 0.005f;
                tutorial_icon_Scale_.y -= 0.005f;
            }

            //α値を固定
            stage1_icon_Alpha_ = 0.2f;

            //アイコンのスケールが大きかったら指定の大きさまで小さくする
            if (stage1_icon_Scale_.x > 0.5f + 0.1f && stage1_icon_Scale_.y > 0.5f + 0.1f)
            {
                stage1_icon_Scale_.x -= 0.005f;
                stage1_icon_Scale_.y -= 0.005f;
            }

            break;
            //チュートリアル選択中
        case 1:

            //α値を固定
            title_icon_Alpha_ = 0.2f;

            //アイコンのスケールが大きかったら指定の大きさまで小さくする
            if (title_icon_Scale_.x > 0.5f + 0.1f && title_icon_Scale_.y > 0.5f + 0.1f)
            {
                title_icon_Scale_.x -= 0.005f;
                title_icon_Scale_.y -= 0.005f;
            }

            //α値を固定
            tutorial_icon_Alpha_ = 1.0f;

            //アイコンのスケールが大きくなかったら指定の大きさまで大きくする
            if (tutorial_icon_Scale_.x < 0.6f + 0.1f && tutorial_icon_Scale_.y < 0.6f + 0.1f)
            {
                tutorial_icon_Scale_.x += 0.005f;
                tutorial_icon_Scale_.y += 0.005f;
            }

            //α値を固定
            stage1_icon_Alpha_ = 0.2f;

            //アイコンのスケールが大きかったら指定の大きさまで小さくする
            if (stage1_icon_Scale_.x > 0.5f + 0.1f && stage1_icon_Scale_.y > 0.5f + 0.1f)
            {
                stage1_icon_Scale_.x -= 0.005f;
                stage1_icon_Scale_.y -= 0.005f;
            }
            break;

            //ステージ１選択中
        case 2:

            //α値を固定
            title_icon_Alpha_ = 0.2f;

            //アイコンのスケールが大きかったら指定の大きさまで小さくする
            if (title_icon_Scale_.x > 0.5f + 0.1f && title_icon_Scale_.y > 0.5f + 0.1f)
            {
                title_icon_Scale_.x -= 0.005f;
                title_icon_Scale_.y -= 0.005f;
            }

            //α値を固定
            tutorial_icon_Alpha_ = 0.2f;

            //アイコンのスケールが大きかったら指定の大きさまで小さくする
            if (tutorial_icon_Scale_.x > 0.5f + 0.1f && tutorial_icon_Scale_.y > 0.5f + 0.1f)
            {
                tutorial_icon_Scale_.x -= 0.005f;
                tutorial_icon_Scale_.y -= 0.005f;
            }

            //α値を固定
            stage1_icon_Alpha_ = 1.0f;

            //アイコンのスケールが大きくなかったら指定の大きさまで大きくする
            if (stage1_icon_Scale_.x < 0.6f + 0.1f && stage1_icon_Scale_.y < 0.6f + 0.1f)
            {
                stage1_icon_Scale_.x += 0.005f;
                stage1_icon_Scale_.y += 0.005f;
            }
            break;
        }

        //Enterが押された時
        if (TRG(0) & PAD_START)
        {
            //決定音
            GameLib::music::play(8, false);

            state_++;
            timer_ = 0;
            break;
        }
        break;
    case 3:
        if (timer_ > 60) {
            // ゲーム画面に遷移
            if (stageNum_ > 0) {
                //襖の開閉音
                GameLib::music::play(11, false);
                state_++;
                break;
            }
            // タイトルに遷移
            else {
                state_ = 5;
                break;
            }
        }
        break;
    case 4:
        //////// ゲーム画面に遷移 ////////

        //襖の処理
        if (S_L_Fusuma_Pos_.x <= 960 && S_R_Fusuma_Pos_.x >= (960 * 1.5f))
        {
            S_L_Fusuma_Pos_.x += 30;
            S_R_Fusuma_Pos_.x -= 30;
        }

        if (S_L_Fusuma_Pos_.x >= 480 && S_R_Fusuma_Pos_.x <= (960 * 1.5f))
        {
            S_L_Fusuma_Pos_.x = 480;
            S_R_Fusuma_Pos_.x = (960 * 1.5f);

            //１秒置いてから遷移
            if (Fusuma_timer_ > 60) {
                GameLib::music::stop(7);
                changeScene(Game::instance());
                break;
            }
            Fusuma_timer_++;
        }
        break;
    case 5:
        //////// タイトルに遷移 /////////
        for (int i = 0; i < 10; i++)
        {
            shuriken_Pos_[i].x -= 20;
            shuriken_Angle_++;
        }

        if (shuriken_Pos_[9].x <= -500)
        {
            GameLib::music::stop(7);
            changeScene(Title::instance());
            break;
        }
        break;
    }

    // 手裏剣の行動
    shurikenAct();

    // デバッグ
    // GameLib::debug::setString("state_:%d", state_);
    // GameLib::debug::setString("timer_:%d", timer_);
    // GameLib::debug::setString("stageNum_:%d", stageNum_);

    // 文字の点滅
    if (state_ > 2) {
        if (stageNum_ == 0) {
            title_icon_Alpha_ = calcIconFlashing(title_icon_Alpha_, timer_);
            stage1_icon_Alpha_ = calcIconFade(stage1_icon_Alpha_);
            tutorial_icon_Alpha_ = calcIconFade(tutorial_icon_Alpha_);
        }
        else if (stageNum_ == 1) {
            tutorial_icon_Alpha_ = calcIconFlashing(tutorial_icon_Alpha_, timer_);
            title_icon_Alpha_ = calcIconFade(title_icon_Alpha_);
            stage1_icon_Alpha_ = calcIconFade(stage1_icon_Alpha_);
        }
        else if (stageNum_ == 2) {
            stage1_icon_Alpha_ = calcIconFlashing(stage1_icon_Alpha_, timer_);
            title_icon_Alpha_ = calcIconFade(title_icon_Alpha_);
            tutorial_icon_Alpha_ = calcIconFade(tutorial_icon_Alpha_);
        }
    }
    timer_++;
}

// 描画
void Select::draw() {

    //マスク処理の削除＆描画の追加
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
        { 1.0f,1.0f,1.0f,tutorial_icon_Alpha_ }
    );

    //ステージ１アイコンの描画
    sprStage1_.draw(
        stage1_icon_Pos_,
        stage1_icon_Scale_,
        ToRadian(0),
        { 1.0f,1.0f,1.0f,stage1_icon_Alpha_ }
    );

    //タイトルへの文字の描画
    sprTotitle_.draw(
        title_icon_Pos_,
        title_icon_Scale_,
        ToRadian(0),
        { 1.0f,1.0f,1.0f,title_icon_Alpha_ }
    );

    GameLib::setBlendMode(GameLib::Blender::BS_MULTIPLY);   // 通常のアルファ処理

    //一番右の飾りの掛け軸
    sprDecration_.draw(
        { window::getWidth() / 2 + window::getWidth() / 3 + 100 , window::getHeight() / 2 + 150 },
        { 0.6f,0.6f }
    );
    
    GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // 通常のアルファ処理

    // クナイの描画
    for (int i = 0; i < 2; i++) {
        sprShuriken_.draw(
            stagingShuriken_[i].pos, stagingShuriken_[i].scale,
            ToRadian(stagingShuriken_[i].angle)
        );
    }

    //襖の描画
    sprL_fusuma_.draw(
        S_L_Fusuma_Pos_
    );

    sprR_fusuma_.draw(
        S_R_Fusuma_Pos_
    );

    //手裏剣の描画
    for (int i = 0; i < 10; i++)
    {
        sprShuriken_.draw(
            shuriken_Pos_[i], { 1.0f,1.0f },
            ToRadian(shuriken_Angle_)
        );
    }

    //手裏剣の四角
    for (int i = 0; i < 10; i++)
    {
        primitive::rect({ 2400 , shuriken_Pos_[i].y + 64 }, { shuriken_Pos_[i].x - 2400 + 64 , 128 }, { 0,128 }, ToRadian(0), { 0.0f,0.0f,0.0f,1.0f });
    }
}

float Select::calcIconFlashing(float colorW, int timer)
{
    if (timer % 15 == 0 && colorW <= 0) {
        colorW = 1;
    }
    else if (timer % 15 == 0 && colorW >= 1) {
        colorW = 0;
    }
    timer++;

    return colorW;
}

float Select::calcIconFade(float colorW)
{
    if (colorW > 0) {
        colorW -= 0.005f;
    }
    return colorW;
}

void Select::shurikenAct()
{
    switch (state_) {
    case 2:
        if (stagingShuriken_[0].pos.x < 200) {
            stagingShuriken_[0].pos.x += 10;
            stagingShuriken_[0].angle += 10;
        }
        if (stagingShuriken_[1].pos.x > 1720) {
            stagingShuriken_[1].pos.x -= 10;
            stagingShuriken_[1].angle -= 10;
        }
        stagingShuriken_[0].angle += 2;
        stagingShuriken_[1].angle -= 2;
        break;
    case 3:
    case 4:
    case 5:
        stagingShuriken_[0].pos.x -= 10;
        stagingShuriken_[0].angle -= 10;
        stagingShuriken_[1].pos.x += 10;
        stagingShuriken_[1].angle += 10;
        break;
    default:
        break;
    }
}
