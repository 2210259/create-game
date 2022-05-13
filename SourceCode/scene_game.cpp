//******************************************************************************
//
//
//      ゲーム画面
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include "all.h"
#include <sstream>
#include <iomanip>

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< 変数 >----------------------------------------------------------------
Game Game::instance_;

//--------------------------------------------------------------
//  初期化処理
//--------------------------------------------------------------
void Game::init()
{
    Scene::init();	    // 基底クラスのinitを呼ぶ

    obj2dManager_   = new OBJ2DManager;
    bg_             = new BG;

    isPaused_ = false;   // ポーズフラグの初期化
}

//--------------------------------------------------------------
//  終了処理
//--------------------------------------------------------------
void Game::deinit()
{
    // 各マネージャの解放
    safe_delete(bg_);
    safe_delete(obj2dManager_);

    // テクスチャの解放
    texture::releaseAll();

    // TODO:音楽流れなかったらコメントアウト
    // 音楽のクリア 
    // music::clear();
}

//--------------------------------------------------------------
//  更新処理
//--------------------------------------------------------------
void Game::update()
{
    using namespace input;

    // ステージセレクト
    if ((STATE(0) & PAD_SELECT) && (STATE(0) & PAD_START))
    {
        changeScene(Title::instance()); // タイトルシーンに切り替える
        return;
    }

     debug::setString("isPaused_%d", isPaused_);

    // ポーズ処理
     if (TRG(0) & PAD_TRG1)
     {
         //音楽を再開
         GameLib::music::resume(stageNo_);

         // 0コンのスタートボタンが押されたらポーズ状態が反転
         isPaused_ = !isPaused_;        
     }

     //ポーズ中
     if (isPaused_)
     {
         if (title_push_flg == false && restart_push_flg == false)
         {
             // Aキーが押された時
             if (TRG(0) & PAD_RIGHT)
             {
                 if (pause_num_ > 0)
                 {
                     pause_num_--;
                 }
             }

             //　Dキーが押された時
             if (TRG(0) & PAD_LEFT)
             {
                 if (pause_num_ < 1)
                 {
                     pause_num_++;
                 }
             }
         }
             //音楽を止める
             GameLib::music::pause(stageNo_);

             //文字のα値を０～１の間で往復させる処理
             switch (pause_alpha_num_)
             {
             case 0:
                 pause_alpha_ -= 0.03f;
                 if (pause_alpha_ <= 0)   pause_alpha_num_++;
                 break;

             case 1:
                 pause_alpha_ += 0.03f;
                 if (pause_alpha_ >= 1)   pause_alpha_num_--;
                 break;
             }
         
         //０(再挑戦)を選んでいるとき
         if (pause_num_)
         {
             if (TRG(0) & PAD_START)
             {
                 music::play(7);
                 restart_push_flg = true;
             }
         }

         //１(たいとるへ)を選んでいるとき
         if (pause_num_ == false) 
         {
             if (TRG(0) & PAD_START)
             {
                 music::play(7);
                 title_push_flg = true;
             }
         }

         //タイトルへを選んだ時
         if (title_push_flg)
         {
             for (int i = 0; i < 11; i++)
             {
                 shuriken_Pos_[i].x -= 20;
                 shuriken_Angle_++;
             }

             if (shuriken_Pos_[9].x <= -500)
             {
                 changeScene(Title::instance());
             }
         }

         //再挑戦を選んだ時
         if (restart_push_flg)
         {
             if (G_L_Fusuma_Pos_.x <= 960 && G_R_Fusuma_Pos_.x >= (960 * 1.5f))
             {
                 G_L_Fusuma_Pos_.x += 30;
                 G_R_Fusuma_Pos_.x -= 30;
             }

             if (G_L_Fusuma_Pos_.x >= 480 && G_R_Fusuma_Pos_.x <= (960 * 1.5f))
             {
                 G_L_Fusuma_Pos_.x = 480;
                 G_R_Fusuma_Pos_.x = (960 * 1.5f);

                 if (Fusuma_timer_ > 60)
                 {
                     Fusuma_timer_ = 0;
                     changeScene(Game::instance());
                 }
                 Fusuma_timer_++;
             }
         }

         return;              // この時点でポーズ中ならリターン
     }

    switch (state_)
    {
    case 0:
        //////// 初期設定 ////////
        
        timer_       = 0;    // ゲームタイマー
        combo2Timer_ = 0;    // コンボタイマー
        scoreTimer_  = 0;    // スコアタイマー
        notesTimer_  = 0;    // ノーツタイマー
        score_       = 0;    // スコア
        combo_       = 0;    // コンボ数
        combo2_      = 0;    // コンボ数(連打)
        maxCombo_    = 0;    // 最大コンボ数

        // HPバーの設定
        hpPos01      = { 1390,  20 };        // HPバーの位置
        hpSize01     = { 500,  80 };         // HPバーの大きさ
        hpColor01    = { 0, 0, 0, 1.0f };    // HPバーの色

        hpPos02      = { 1395,  25 };        // HPバーの位置
        hpSize02     = { 490,  70 };         // HPバーの大きさ
        hpColor02    = { 1, 0, 0, 0.8f };    // HPバーの色

        comboSize    = { 1.5f, 1.5f };       // コンボの大きさ
        combo2Pos    = { 1890, 280 };        // コンボ2の位置
        combo2Size   = { 1.5f, 1.5f };       // コンボ2の大きさ             
        combo2Color  = { 1, 1, 1, 0 };       // コンボ2の色

        scorePos     = { 10, 80 };           // スコアの位置
        scoreSize    = { 1.5f, 1.5f };       // スコアの大きさ             
        scoreColor   = { 1, 1, 1, 0 };       // スコアの色
        
        notesPos     = { 1890, 240 };        // ノーツの位置
        notesSize    = { 1.5f, 1.5f };       // ノーツの大きさ             
        notesColor   = { 1, 1, 1, 0 };       // ノーツの色

        t_EndPos   = { BG::CLIENT_W / 2, -300 };    // 文字の位置
        t_EndSize  = {  350,  94 };                 // 文字の大きさ
        t_EndScale = { 10.0f, 10.0f };              // 文字の大きさ             
        t_EndColor = { 1, 1, 1, 1 };                // 文字の色

        t_FullComboPos    = { -BG::CLIENT_W / 2, BG::CLIENT_H / 2 }; // 文字の位置
        t_FullComboSize   = { 782,  94 };                            // 文字の大きさ
        t_FullComboScale  = { 2.0f, 2.0f };                          // 文字の大きさ             
        t_FullComboColor  = { 1, 1, 1, 1 };                          // 文字の色

        perfectNum_ = 0; // パーフェクト数  
        greatNum_   = 0; // グレイト数 
        goodNum_    = 0; // グッド数 
        missNum_    = 0; // ミス数

        pause_num_       = 0; // ポーズ中の選択用
        pause_alpha_     = 0; // ポーズ中に表示するテキストのα値
        pause_alpha_num_ = 0; // α値を０～１まで往復させるための値
        
        playerAlive_ = true; //生存しているかどうか

        G_L_Fusuma_Pos_ = { 960 / 2,540 };     // 左襖の位置の初期化
        G_R_Fusuma_Pos_ = { (960 * 2) - (960 / 2) , 540 }; // 右襖の位置の初期化

        G_Fusuma_timer_ = 0;                   //襖が閉じるまでの時間の初期化

        for (int i = 0; i < 11; i++)            //手裏剣位置の初期化
        {
            shuriken_Pos_[i].x = 2400 + (128 * i);
            shuriken_Pos_[i].y = 128 * i;
        }

        shuriken_Angle_ = 0;                   //手裏剣の角度の初期化

        title_push_flg = false;                // タイトルへを選んだ時のフラグの初期化
        restart_push_flg = false;              // 再挑戦を選んだ時のフラグの初期化

        setStageNo(Select::instance()->stageNum());

        // BGMの再生
        music::play(stageNo_, false);

        GameLib::setBlendMode(Blender::BS_ALPHA);   // 通常のアルファ処理

        // テクスチャの読み込み
        texture::load(loadTexture);

        // プレイヤーマネージャの初期設定
        obj2dManager()->init();

        // 敵をセット
        setEnemy(obj2dManager(), bg());

        // プレイヤーを追加
        player_ = obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                bg(),
                new ActorComponent,
                nullptr,
                nullptr
            ),
            &idlePlayerBehavior, VECTOR2(BG::WINDOW_W / 2, BG::WINDOW_H - (BG::WINDOW_H / 18)), -1, {});

        // BGの初期設定
        bg()->init(player_);

        state_++;    // 初期設定処理の終了
        /*fallthrough*/

    case 1:
        //////// 通常時の処理 ////////

        // オブジェクトの更新
        obj2dManager()->update();

        // BGの更新
        bg()->update();  
        
        // 敵をセット
        setEnemy(obj2dManager(), bg());

        // 当たり判定
        judge();

        // スコアの計算
        calcScore();

        // コンボの計算
        calcCombo();

        // ノーツ判定の更新
        decisionJudge();
        
        //ゲームの終了時間の調整
        if (timer_ > 1000) {
            if (G_L_Fusuma_Pos_.x <= 960 && G_R_Fusuma_Pos_.x >= (960 * 1.5f))
            {
                G_L_Fusuma_Pos_.x += 30;
                G_R_Fusuma_Pos_.x -= 30;
            }

            if (G_L_Fusuma_Pos_.x >= 480 && G_R_Fusuma_Pos_.x <= (960 * 1.5f))
            {
                G_L_Fusuma_Pos_.x = 480;
                G_R_Fusuma_Pos_.x = (960 * 1.5f);

                setPlayerAlive(true);
                changeScene(Score::instance());
                break;
            }
        }

        //プレイヤーの体力がなくなったら
        if (player()->actorComponent()->hp() < 1)
        {
            if (G_L_Fusuma_Pos_.x <= 960 && G_R_Fusuma_Pos_.x >= (960 * 1.5f))
            {
                G_L_Fusuma_Pos_.x += 30;
                G_R_Fusuma_Pos_.x -= 30;
            }

            if (G_L_Fusuma_Pos_.x >= 480 && G_R_Fusuma_Pos_.x <= (960 * 1.5f))
            {
                G_L_Fusuma_Pos_.x = 480;
                G_R_Fusuma_Pos_.x = (960 * 1.5f);

                setPlayerAlive(false);
                changeScene(Score::instance());
                break;
            }
        }

        //襖の処理
        if (G_L_Fusuma_Pos_.x > -960 / 2 && G_R_Fusuma_Pos_.x < (960 * 2) + (960 / 2) && player()->actorComponent()->hp() >= 1 && timer_ < 100)
        {
            G_L_Fusuma_Pos_.x -= 30;
            G_R_Fusuma_Pos_.x += 30;

            if (G_L_Fusuma_Pos_.x <= -960 / 2 && G_R_Fusuma_Pos_.x >= (960 * 2) + (960 / 2))
            {
                G_L_Fusuma_Pos_.x = -960 / 2;
                G_R_Fusuma_Pos_.x = (960 * 2) + (960 / 2);
            }
        }

        timer_++;
        break;
    case 2:
        //////// ノーツが全て流れた後の処理 ////////
        
        // オブジェクトの更新
        obj2dManager()->update();

        // BGの更新
        bg()->update();  

        // 止める演出を出す
        if (t_EndScale.x > 2.0f) {
            t_EndScale -= { 0.4f, 0.4f };
            t_EndPos.y += 30;
        }

        // ミスの有無によって処理を変更
        if(t_EndScale.x <= 2.0f) {
            if (missNum_ <= 0) {
                state_++;
                break;
            }
            else {
                state_ = 4;
                break;
            }
        }
        break;
    case 3:
        //////// ミスがないときの処理 ////////
        // オブジェクトの更新
        obj2dManager()->update();

        // BGの更新
        bg()->update();

        // 文字を横に移動
        t_FullComboPos.x += 30;
        
        // 真ん中に止まるように設定
        if (t_FullComboPos.x > BG::CLIENT_W / 2) {
            t_FullComboPos.x = BG::CLIENT_W / 2;
        }

        // エフェクトを出す
        if (timer_ % 6 == 0) {
            setEffect(Game::instance()->obj2dManager(), Game::instance()->bg(), &notesEffect0Behavior, { static_cast<float>(rand() % BG::WINDOW_W), static_cast<float>(rand() % BG::WINDOW_H) });
            setEffect(Game::instance()->obj2dManager(), Game::instance()->bg(), &notesEffect1Behavior, { static_cast<float>(rand() % BG::WINDOW_W), static_cast<float>(rand() % BG::WINDOW_H) });
            setEffect(Game::instance()->obj2dManager(), Game::instance()->bg(), &notesEffect2Behavior, { static_cast<float>(rand() % BG::WINDOW_W), static_cast<float>(rand() % BG::WINDOW_H) });
        }
        
        // スコア画面に遷移
        if (TRG(0) & PAD_START) {
            state_++;
        }

        timer_++;
        break;
    case 4:
        //////// スコア画面に遷移 ////////
        changeScene(Score::instance());
        break;
    }
    // debug::setString("Combo:%d", combo());
    // debug::setString("maxCombo:%d", maxCombo());
    
    // debug::setString("stageNo:%d", Game::instance()->stageNo());
    // debug::setString("GameTimer:%d", timer_);
}

//--------------------------------------------------------------
//  描画処理
//--------------------------------------------------------------
void Game::draw()
{
    // 画面クリア
    GameLib::clear(VECTOR4(0.5f, 0.5f, 0.5f, 1));

    // ステンシルモード：通常
    DepthStencil::instance().set(DepthStencil::MODE::NONE);

    // 背景の描画
    bg()->drawBack();

    // 通常ノーツの描画
    obj2dManager()->draw(bg()->getScrollPos());

    // 長押しノーツ(左)と連続ノーツ(左)の描画
    {
        // ステンシルモード：マスク生成
        DepthStencil::instance().set(DepthStencil::MODE::MASK);

        // 四角形
        // if (input::STATE(0) & input::PAD_START) {
        //     { player()->transform()->position().x,
        //     player()->transform()->position().y - player()->collider()->size().y },
        //     { player()->transform()->position().x, player()->collider()->size().y },
        //     { 0, 0 },
        //     ToRadian(0),
        //     { 0.0f, 0.0f, 0.0f, 0.0f }
        // );

        // ステンシルモード：マスク以外に描画
        DepthStencil::instance().set(DepthStencil::MODE::NONE);

        // 長押しノーツ(左)と連続ノーツ(左)の描画
        obj2dManager()->draw3(bg()->getScrollPos());
    }

    // 長押しノーツ(右)と連続ノーツ(右)の描画
    {
        // ステンシルモード：マスク生成
        DepthStencil::instance().set(DepthStencil::MODE::MASK);

        // ステンシルモード：マスク以外に描画
        DepthStencil::instance().set(DepthStencil::MODE::NONE);

        // 長押しノーツ(右)と連続ノーツ(右)の描画
        obj2dManager()->draw4(bg()->getScrollPos());
    }

    // 長押しノーツ(上)と連続ノーツ(上)の描画
    {
        // ステンシルモード：マスク生成
        DepthStencil::instance().set(DepthStencil::MODE::MASK);

        // 四角形
        if (input::STATE(0) & input::PAD_START) {
            GameLib::primitive::rect(
                { player()->transform()->position().x - (player()->collider()->size().x / 2),
                player()->transform()->position().y - (player()->collider()->size().y * 3 / 2) },
                { player()->collider()->size().x, player()->collider()->size().y / 2 },
                { 0, 0 },
                ToRadian(0),
                { 0.0f, 0.0f, 0.0f, 0.0f }
            );
        }
        // ステンシルモード：マスク以外に描画
        DepthStencil::instance().set(DepthStencil::MODE::EXCLUSIVE);
        
        // 長押しノーツ(上)と連続ノーツ(上)の描画
        obj2dManager()->draw2(bg()->getScrollPos());
    }

    // ステンシルモード：通常
    DepthStencil::instance().set(DepthStencil::MODE::NONE);

    // プレイヤーの描画
    obj2dManager()->drawPlayer(bg()->getScrollPos());

    // エフェクトの描画
    obj2dManager()->drawEffect(bg()->getScrollPos());

    // HPバーの描画
    primitive::rect(hpPos01, hpSize01, { 0, 0 }, 0, hpColor01);
    if (player()->actorComponent()->hp() >= 0) {
        primitive::rect(hpPos02,
            { hpSize02.x / player()->actorComponent()->maxHP() * player()->actorComponent()->hp(), hpSize02.y },
            { 0, 0 }, 0, hpColor02);
    }

    // スコア,コンボ数の描画
    // TODO:スコアの表示
    scoreDraw();
    comboDraw();

    // ノーツ判定の描画
    decisionDraw();

    // 閉幕の文字描画
    if (state_ == 2 || state_ == 3) {
        texture::begin(TEXNO::T_END);
        texture::draw(TEXNO::T_END, t_EndPos.x, t_EndPos.y, t_EndScale.x, t_EndScale.y,
            0, 0, t_EndSize.x, t_EndSize.y, t_EndSize.x / 2, t_EndSize.y / 2);
        texture::end(TEXNO::T_END);
    }

    // フルコンボの文字の描画
    if (state_ == 3) {
        // 四角形
        GameLib::primitive::rect(
            { t_FullComboPos.x, t_FullComboPos.y },
            { BG::CLIENT_W, BG::CLIENT_H / 5},
            { BG::CLIENT_W / 2, BG::CLIENT_H / 10 },
            ToRadian(0),
            { 0.0f, 0.0f, 0.0f, 0.5f }
        );

        texture::begin(TEXNO::T_FULLCOMBO);
        texture::draw(TEXNO::T_FULLCOMBO, t_FullComboPos.x, t_FullComboPos.y, t_FullComboScale.x, t_FullComboScale.y,
            0, 0, t_FullComboSize.x, t_FullComboSize.y, t_FullComboSize.x / 2, t_FullComboSize.y / 2);
        texture::end(TEXNO::T_FULLCOMBO);

    }

    // 操作説明の描画
    operationDraw();

    // ポーズ画面
    if (isPaused_)
    {
        GameLib::font::textOut(4, "PAUSE",
            { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 4) },
            VECTOR2(5.0f, 5.0f),
            { 1.0f, 1.0f, 1.0f, 1.0f },
            GameLib::TEXT_ALIGN::UPPER_MIDDLE
        );

        //再挑戦を選んでいるとき
        if (pause_num_)
        {
            //"再挑戦"の文字の描画
            sprRestart_.draw(
                { GameLib::window::getWidth() / 4, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,pause_alpha_ }
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
        if (pause_num_ == false)
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
                { 1,1,1,pause_alpha_ }
            );
        }
    }

    // 当たり判定
    {
        // 上の攻撃範囲表示
        // primitive::rect(BG::WINDOW_W / 2 - 15, player()->transform()->position().y - (player()->collider()->size().y * 3 / 2) - 15,
        //     30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.2f);

        primitive::circle(BG::WINDOW_W / 2, player()->transform()->position().y - (player()->collider()->size().y * 3 / 2),
            15, 1, 1, ToRadian(0), 1.0f, 1.0f, 1.5f, 0.2f);

        // 左の攻撃範囲表示
        // primitive::rect(player()->transform()->position().x - player()->collider()->size().x - 15, player()->transform()->position().y - player()->collider()->size().y / 2 - 15,
        //     30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.2f);

        primitive::circle(player()->transform()->position().x - player()->collider()->size().x, player()->transform()->position().y - player()->collider()->size().y / 2,
            15, 1, 1, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.2f);

        // 右の攻撃範囲表示
        // primitive::rect(player()->transform()->position().x + player()->collider()->size().x - 15, player()->transform()->position().y - player()->collider()->size().y / 2 - 15,
        //     30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.2f);

        primitive::circle(player()->transform()->position().x + player()->collider()->size().x, player()->transform()->position().y - player()->collider()->size().y / 2,
            15, 1, 1, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.2f);

        // プレイヤーが上を向いていたら
        if (player()->actorComponent()->direction() == player()->actorComponent()->UP) {
            // 上の攻撃範囲表示
            // primitive::rect(BG::WINDOW_W / 2 - 15, player()->transform()->position().y - (player()->collider()->size().y * 3 / 2) - 15,
            //     30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.6f);

            primitive::circle(BG::WINDOW_W / 2, player()->transform()->position().y - (player()->collider()->size().y * 3 / 2),
                15, 1, 1, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.6f);
        }
        // プレイヤーが左を向いていたら
        if (player()->actorComponent()->direction() == player()->actorComponent()->LEFT) {
            // 左の攻撃範囲表示
            // primitive::rect(player()->transform()->position().x - player()->collider()->size().x - 15, player()->transform()->position().y - player()->collider()->size().y / 2 - 15,
            //     30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.6f);

            primitive::circle(player()->transform()->position().x - player()->collider()->size().x, player()->transform()->position().y - player()->collider()->size().y / 2,
                15, 1, 1, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.6f);
        }
        // プレイヤーが右を向いていたら
        if (player()->actorComponent()->direction() == player()->actorComponent()->RIGHT)
        {
            // 右の攻撃範囲表示
            // primitive::rect(player()->transform()->position().x + player()->collider()->size().x - 15, player()->transform()->position().y - player()->collider()->size().y / 2 - 15,
            //     30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.6f);

            primitive::circle(player()->transform()->position().x + player()->collider()->size().x, player()->transform()->position().y - player()->collider()->size().y / 2,
                15, 1, 1, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.6f);
        }
    }

    //襖の描画
    sprL_Fusuma_.draw(G_L_Fusuma_Pos_);
    sprR_Fusuma_.draw(G_R_Fusuma_Pos_);

    //手裏剣の描画
    for (int i = 0; i < 11; i++)
    {
        sprShuriken_.draw(
            shuriken_Pos_[i], { 1.0f,1.0f },
            ToRadian(shuriken_Angle_)
        );
    }

    //手裏剣の四角
    for (int i = 0; i < 11; i++)
    {
        primitive::rect({ 2400 , shuriken_Pos_[i].y + 32 }, { shuriken_Pos_[i].x - 2400 + 64 , 128 }, { 0,128 }, ToRadian(0), { 0.0f,0.0f,0.0f,1.0f });
    }

}

//--------------------------------------------------------------
//  あたり判定
//--------------------------------------------------------------
void Game::judge()
{
    for (auto& src : *obj2dManager()->getList())
    {
        if (!src->behavior()) continue;
        if (!src->collider()->judgeFlag()) continue;

        for (auto& dst : *obj2dManager()->getList())
        {
            if (!src->behavior()) break;

            if (src == dst) continue;   // 自分自身はとばす
            if (!dst->behavior()) continue;
            if (!dst->collider()->judgeFlag()) continue;

            // srcの攻撃タイプとdstのタイプが一致しないものをとばす
            if (src->behavior()->attackType() != dst->behavior()->getType())
                continue;

            // あたり判定を行う
            if (src->collider()->hitCheck(dst))
            {
                // あたった場合の処理
                src->behavior()->hit(src, dst);
            }
            else if (src->collider()->hitCheck2(dst))
            {
                src->behavior()->hit2(src, dst);
            }
            else if (src->collider()->hitCheck3(dst))
            {
                src->behavior()->hit3(src, dst);
            }
            else if (src->collider()->hitCheck5(dst))
            {
                src->behavior()->hit5(src, dst);
            }
            else if (src->collider()->hitCheck6(dst))
            {
                src->behavior()->hit6(src, dst);
            }
            else if (src->collider()->hitCheck7(dst))
            {
                src->behavior()->hit7(src, dst);
            }
            // 長押し判定
            if (src->collider()->hitCheck4(dst))
            {
                src->behavior()->hit4(src, dst);
            }
        }
    }
}

void Game::calcCombo()
{
    // 最大コンボの更新
    if (combo() > maxCombo()) {
        setMaxCombo(combo());
    }

    // スコア表示をもとに戻す
    if (combo2Timer_ >= maxAppearTime_) {
        combo2Pos   = { 1890, 300 };        // コンボの位置
        combo2Size  = { 1.5f, 1.5f };       // コンボの大きさ
        combo2Color = { 1, 1, 1, 0 };       // コンボの色
    }
    // タイマーを減らす
    if (combo2Timer_ > 0) combo2Timer_--;

    // パラメータを変更
    // コンボ1の設定
    if (comboSize.x > 1.5f) 
        comboSize -= { 0.05f, 0.05f };

    // コンボ2の設定
    if (combo2Timer_ > 30) {
        combo2Color.w += 0.5f;
    }
    else {
        combo2Color.w -= 0.04f;
    }
    if (combo2Timer_ > 115)
        combo2Size += { 0.1f, 0.1f };
    else
        combo2Size -= { 0.1f, 0.1f };

    // 一定の値を超えないように設定
    comboSize.x = clamp(comboSize.x, 1.5f, 2.0f);
    comboSize.y = clamp(comboSize.y, 1.5f, 2.0f);
    if (combo2Pos.y < 240)        combo2Pos.y = 240;
    combo2Size.x = clamp(combo2Size.x, 1.5f, 1.8f);
    combo2Size.y = clamp(combo2Size.y, 1.5f, 1.8f);
    combo2Color.w = clamp(combo2Color.w, 0.0f, 1.0f);
}

// コンボの描画設定
void Game::comboDraw()
{
    std::ostringstream ss1, ss2, ss3;

    ss1 << "COMBO" << std::setw(4) << " ";
    ss2 << std::setw(9) << combo_;
    ss3 << combo2_;
    // コンボ数をテキスト表示
    font::textOut(6,
        ss1.str(),
        { 1890, 140 },
        { 1.5f, 1.5f },
        { 1.0f, 1.0f, 1.0f, 1.0f },
        TEXT_ALIGN::MIDDLE_RIGHT
    );

    font::textOut(6,
        ss2.str(),
        { 1890, 140 },
        comboSize,
        { 1.0f, 1.0f, 1.0f, 1.0f },
        TEXT_ALIGN::MIDDLE_RIGHT
    );
    
    if (combo2_ > 0 && combo2Timer_ > 0) {
        font::textOut(6,
            ss3.str(),
            combo2Pos,
            combo2Size,
            combo2Color,
            TEXT_ALIGN::MIDDLE_RIGHT
        );
    }
}

void Game::calcScore()
{
    // スコア表示をもとに戻す
    if (scoreTimer_ >= maxAppearTime_) {
        scorePos    = { 10, 80 };           // スコアの位置
        scoreColor  = { 1.0f, 1.0f, 0.5f, 0 };       // スコアの色
    }
    // タイマーを減らす
    if (scoreTimer_ > 0) scoreTimer_--;

    // パラメータを変更
    if (scoreTimer_ > 100) {
        scorePos.y -= 1.0f;
        scoreColor.w += 0.2f;
    }
    else{
        scorePos.y -= 1.0f;
        scoreColor.w -= 0.02f;
    }
    // 一定の値を超えないように設定
    if (scorePos.y < 10)        scorePos.y = 10;
    scoreColor.w = clamp(scoreColor.w, 0.0f, 1.0f);
}

// スコアの描画設定
void Game::scoreDraw()
{
    std::ostringstream ss1, ss2;
    
    ss1 << "SCORE " << std::setw(8) << std::setfill('0') << score_;
    ss2 << std::setw(14) << appearScore_;
    
    // スコア数をテキスト表示
    font::textOut(6,
        ss1.str(),
        { 10, 10 },
        { 1.5f, 1.5f },
        { 1.0f, 1.0f, 1.0f, 1.0f },
        TEXT_ALIGN::UPPER_LEFT
    );

    if (scoreTimer_) {
        // スコア数をテキスト表示
        font::textOut(6,
            ss2.str(),
            scorePos,
            scoreSize,
            scoreColor,
            TEXT_ALIGN::UPPER_LEFT
        );
    }
}

// ノーツ判定の判別
void Game::decisionJudge()
{
    switch (decision_)
    {
    case Game::MISS:
        notesText.str("MISS");
        notesTimer_ = maxAppearTime_;
        notesPos    = { 1890, 240 };
        notesSize   = { 0.2f, 0.2f };
        notesColor  = { 0.0f, 0.0f, 1.0f, 0.0f };
        decision_   = NONE;
        break;
    case Game::GOOD:
        notesText.str("GOOD");
        notesTimer_ = maxAppearTime_;
        notesPos    = { 1890, 240 };
        notesSize   = { 0.2f, 0.2f };
        notesColor  = { 1.0f, 1.0f, 1.0f, 0.0f };
        decision_   = NONE;
        break;
    case Game::GREAT:
        notesText.str("GREAT");
        notesTimer_ = maxAppearTime_;
        notesPos    = { 1890, 240 };
        notesSize   = { 0.2f, 0.2f };
        notesColor  = { 0.2f, 1.0f, 1.0f, 0.0f };
        decision_   = NONE;
        break;
    case Game::PERFECT:
        notesText.str("PERFECT");
        notesTimer_ = maxAppearTime_;
        notesPos    = { 1890, 240 };
        notesSize   = { 0.2f, 0.2f };
        notesColor  = { 1.0f, 1.0f, 0.0f, 0.0f };
        decision_   = NONE;
        break;
    default:
        break;
    }
    // タイマーを減らす
    if (notesTimer_ > 0) notesTimer_--;
    
    // パラメータを変更
    if (notesTimer_ > 30) {
        notesPos.y -= 2.0f;
        notesSize += {0.2f, 0.2f};
        notesColor.w += 0.2f;
    }
    else {
        notesColor.w -= 0.04f;
    }
    // 一定の値を超えないように設定
    if (notesPos.y < 220)       notesPos.y   = 220;
    if (notesSize.x > 1.5f)     notesSize    = { 1.5f, 1.5f };
    notesColor.w = clamp(notesColor.w, 0.0f, 1.0f);
    debug::setString("notesTimer:%d", notesTimer_);
    debug::setString("notesColor.w:%f", notesColor.w);
}

void Game::decisionDraw()
{
    if (notesTimer_ > 0) {
        // コンボ数をテキスト表示
        font::textOut(6,
            notesText.str(),
            notesPos,
            notesSize,
            notesColor,
            TEXT_ALIGN::MIDDLE_RIGHT
        );
    }
}

// TODO: 試遊会用
// 操作説明（仮）
void Game::operationDraw() {
    // std::ostringstream ss1, ss2, ss3;
    // 
    // ss1 << "[W]+Enter->UpAttack";
    // 
    // // コンボ数をテキスト表示
    // font::textOut(6,
    //     ss1.str(),
    //     { 10, 70 },
    //     { 0.6f, 0.6f },
    //     { 1.0f, 1.0f, 1.0f, 1.0f },
    //     TEXT_ALIGN::LOWER_LEFT
    // );
    // ss2 << "[A]+Enter->LeftAttack";
    // 
    // // コンボ数をテキスト表示
    // font::textOut(6,
    //     ss2.str(),
    //     { 10, 90 },
    //     { 0.6f, 0.6f },
    //     { 1.0f, 1.0f, 1.0f, 1.0f },
    //     TEXT_ALIGN::LOWER_LEFT
    // );
    // 
    // ss3 << "[D]+Enter->RightAttack";
    // 
    // // コンボ数をテキスト表示
    // font::textOut(6,
    //     ss3.str(),
    //     { 10, 110 },
    //     { 0.6f, 0.6f },
    //     { 1.0f, 1.0f, 1.0f, 1.0f },
    //     TEXT_ALIGN::LOWER_LEFT
    // );
}

//******************************************************************************