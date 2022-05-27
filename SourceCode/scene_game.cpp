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

    // 音楽のクリア 
    // music::clear();
}

//--------------------------------------------------------------
//  更新処理
//--------------------------------------------------------------
void Game::update()
{
    using namespace input;

     debug::setString("isPaused_%d", isPaused_);

    // ポーズ処理
     if (TRG(0) & PAD_TRG1 && title_push_flg == false && restart_push_flg == false)
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
             if (TRG(0) & PAD_RIGHT) {
                 if (pause_num_ > 0)
                 {
                     pause_num_--;
                 }
             }

             //　Dキーが押された時
             if (TRG(0) & PAD_LEFT) {
                 if (pause_num_ < 2)
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

         //１(再開)を選んでいるとき
         if (pause_num_ == 1 && title_push_flg == false && restart_push_flg == false)
         {
             if (TRG(0) & PAD_START)
             {
                 //music::play(8, false);
                 isPaused_ = !isPaused_;
             }

         }
         
         //２(再挑戦)を選んでいるとき
         if (pause_num_ == 2 && title_push_flg == false && restart_push_flg == false)
         {
             if (TRG(0) & PAD_START)
             {
                 music::play(8,false);
                 restart_push_flg = true;
             }
         }

         //０(たいとるへ)を選んでいるとき
         if (pause_num_ == 0 && title_push_flg == false && restart_push_flg == false) 
         {
             if (TRG(0) & PAD_START)
             {
                 music::play(8,false);
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
        
        combo2Timer_ = 0;    // コンボタイマー
        scoreTimer_  = 0;    // スコアタイマー
        notesTimer_  = 0;    // ノーツタイマー
        score_       = 0;    // スコア
        combo_       = 0;    // コンボ数
        combo2_      = 0;    // コンボ数(連打)
        maxCombo_    = 0;    // 最大コンボ数

        // HPバーの設定
        hpPos01      = { 1290, 10 };         // HPバーの位置
        hpTexPos01   = { 0,  0 };            // HPバーの大きさ
        hpColor01    = { 1, 1, 1, 1.0f };    // HPバーの色

        hpPos02      = { 1390,  80 };        // HPバーの位置
        hpSize02     = { 0,  70 };           // HPバーの大きさ
        hpColor02    = { 1, 0, 0, 0.8f };    // HPバーの色

        comboSize    = { 1.5f, 1.5f };       // コンボの大きさ
        comboColor   = { 1, 1, 1, 1 };       // コンボの色
        combo2Pos    = { 1890, 360 };        // コンボ2の位置
        combo2Size   = { 1.5f, 1.5f };       // コンボ2の大きさ             
        combo2Color  = { 1, 1, 1, 0 };       // コンボ2の色

        scorePos     = { 10, 140 };          // スコアの位置
        scoreSize    = { 1.5f, 1.5f };       // スコアの大きさ             
        scoreColor   = { 1, 1, 1, 0 };       // スコアの色
        
        notesPos     = { 1890, 180 };        // ノーツの位置
        notesSize    = { 1.5f, 1.5f };       // ノーツの大きさ             
        notesColor   = { 1, 1, 1, 0 };       // ノーツの色

        t_StartPos   = { BG::CLIENT_W / 2, -500 }; // 文字の位置
        t_StartSize  = { 600,  200 };              // 文字の大きさ
        t_StartScale = { 8.0f, 8.0f };             // 文字の大きさ             
        t_StartColor = { 1, 1, 1, 1 };             // 文字の色

        t_EndPos   = { BG::CLIENT_W / 2, -500 };   // 文字の位置
        t_EndSize  = {  600,  200 };               // 文字の大きさ
        t_EndScale = { 8.0f, 8.0f };               // 文字の大きさ             
        t_EndColor = { 1, 1, 1, 1 };               // 文字の色

        t_FullComboPos    = { -BG::CLIENT_W / 2, BG::CLIENT_H / 2 }; // 文字の位置
        t_FullComboSize   = { 600,  200 };                           // 文字の大きさ
        t_FullComboScale  = { 2.0f, 2.0f };                          // 文字の大きさ             
        t_FullComboColor  = { 1, 1, 1, 1 };                          // 文字の色

        perfectNum_ = 0; // パーフェクト数  
        greatNum_   = 0; // グレイト数 
        goodNum_    = 0; // グッド数 
        missNum_    = 0; // ミス数

        pause_num_       = 0; // ポーズ中の選択用
        pause_alpha_     = 0; // ポーズ中に表示するテキストのα値
        pause_alpha_num_ = 0; // α値を０～１まで往復させるための値
        HPAnimeTimer_    = 0;

        playerAlive_   = true; //生存しているかどうか
        notesMaskFlag_ = false;

        G_L_Fusuma_Pos_ = { 960 / 2,540 };     // 左襖の位置の初期化
        G_R_Fusuma_Pos_ = { (960 * 2) - (960 / 2) , 540 }; // 右襖の位置の初期化

        G_Fusuma_timer_ = 0;                   //襖が閉じるまでの時間の初期化

        for (int i = 0; i < 11; i++)           //手裏剣位置の初期化
        {
            shuriken_Pos_[i].x = static_cast<float>(2400 + (128 * i));
            shuriken_Pos_[i].y = static_cast<float>(128 * i);
        }

        shuriken_Angle_ = 0;                   //手裏剣の角度の初期化

        title_push_flg = false;                // タイトルへを選んだ時のフラグの初期化
        restart_push_flg = false;              // 再挑戦を選んだ時のフラグの初期化

        tutorial_pos_ = { -300,420 };          // チュートリアル画像の初期位置  

        tutorial_State_ = 0;                   // チュートリアルステート

        tutorial_timer_ = 0;                   // チュートリアル画像の表示時間の初期化

        setStageNo(Select::instance()->stageNum() - 1);

        GameLib::setBlendMode(Blender::BS_ALPHA);   // 通常のアルファ処理

        // テクスチャの読み込み
        texture::load(loadTexture);

        // プレイヤーマネージャの初期設定
        obj2dManager()->init();

        // 敵をセット
        setEnemy(obj2dManager(), bg());

        // BGMの再生
        music::play(stageNo_, false);
        music::pause(stageNo_);

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

        player_->renderer()->setColor(VECTOR4(1, 1, 1, 0));

        // BGの初期設定
        bg()->init(player_);

        //襖開閉音
        GameLib::music::play(11, false);

        state_++;    // 初期設定処理の終了
        /*fallthrough*/

    case 1:
        //////// 襖が開ける処理 ////////
        // 襖の処理
        if (G_L_Fusuma_Pos_.x > -960 / 2 && G_R_Fusuma_Pos_.x < (960 * 2) + (960 / 2) && timer_ > 3)
        {
            G_L_Fusuma_Pos_.x -= 30;
            G_R_Fusuma_Pos_.x += 30;
        }
        // 襖が画面外に移動
        if (G_L_Fusuma_Pos_.x <= -960 / 2 && G_R_Fusuma_Pos_.x >= (960 * 2) + (960 / 2))
        {
            G_L_Fusuma_Pos_.x = -960 / 2;
            G_R_Fusuma_Pos_.x = (960 * 2) + (960 / 2);

            // 開始演出を出す
            if (timer_ > 110) {
                if (t_StartScale.x > 1.5f) {
                    t_StartScale -= { 0.25f, 0.25f };
                    t_StartPos.y += 30;
                }

                // caseを一つ動かす
                if (t_StartScale.x <= 1.5f) {
                    // 効果音
                    music::play(8, false);

                    timer_ = 0;
                    state_++;
                    break;
                }
            }
        }
        // オブジェクトの更新
        obj2dManager()->update();

        // BGの更新
        bg()->update();

        // HPバーのアニメーション
        AnimetionHP();

        if (player_->renderer()->color().w < 1) {
            player_->renderer()->addColorW(0.02f);
        }
        timer_++;
        break;
    case 2:
        //////// 通常時の処理 ////////
        
        // 開幕のアルファ値を下げる 
        if(timer_ > 30 && t_StartColor.w > 0)
            t_StartColor.w -= 0.02f;

        //１秒後に音楽を開始
        if (timer_ > 60) {
            music::resume(stageNo_);
        }

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

        // HPバーのアニメーション
        AnimetionHP();

        // ゲームの終了時間の調整
        if ((stageNo_ == 0 && timer_ > 5640) || (stageNo_ == 1 && timer_ > 6500)) {
            setPlayerAlive(true);
            GameLib::music::stop(stageNo_);
            state_++;
            break;
        }

        // プレイヤーの体力がなくなったら
        if (player()->actorComponent()->hp() < 1) {
            setPlayerAlive(false);
            GameLib::music::stop(stageNo_);
            state_++;
            break;
        }

        timer_++;
        break;
    case 3:
        //////// ノーツが全て流れた後、HPが0になった時の処理 ////////
        
        // オブジェクトの更新
        obj2dManager()->update();

        // BGの更新
        bg()->update();  

        // HPバーのアニメーション
        AnimetionHP();

        // スコアの計算
        calcScore();

        // コンボの計算
        calcCombo();

        // ノーツ判定の更新
        decisionJudge();

        // 止める演出を出す
        if (t_EndScale.x > 1.5f) {
            t_EndScale -= { 0.25f, 0.25f };
            t_EndPos.y += 30;
        }

        // caseを一つ動かす
        if(t_EndScale.x <= 1.5f) {
            // 効果音
            music::play(8, false);

            timer_ = 0;
            state_++;
            break;
        }
        break;
    case 4:
        //////// ノーツが全て流れた後、HPが0になった時の処理 ////////

        // オブジェクトの更新
        obj2dManager()->update();

        // BGの更新
        bg()->update();

        // HPバーのアニメーション
        AnimetionHP();

        // スコアの計算
        calcScore();

        // コンボの計算
        calcCombo();

        // ノーツ判定の更新
        decisionJudge();

        // 閉幕のアルファ値を下げる 
        if (timer_ > 60 && t_EndColor.w > 0)
            t_EndColor.w -= 0.02f;

        // ミスの有無、HPによって処理を変更
        if (timer_ > 120) {
            // ミスがなし＋プレイヤーが生きてる状態であれば演出を追加
            if (missNum_ <= 0 && player()->actorComponent()->hp() > 0){
            
            //襖開閉音
            GameLib::music::play(11, false);

            state_++;
            }
            // スコア画面にそのまま遷移
            else { 
                //襖開閉音
                GameLib::music::play(11, false);

                state_ = 6;
            }
        }
        timer_++;
        break;
    case 5:
        //////// ミスがないときの処理 ////////
        // オブジェクトの更新
        obj2dManager()->update();

        // BGの更新
        bg()->update();

        // HPバーのアニメーション
        AnimetionHP();

        // 文字を横に移動
        t_FullComboPos.x += 30;
        
        // 真ん中に止まるように設定
        if (t_FullComboPos.x > BG::CLIENT_W / 2) {
            t_FullComboPos.x = BG::CLIENT_W / 2;

            //フルコンボ音
            GameLib::music::play(10,false);

            // 真ん中にとまった後エフェクトを出す
            if (timer_ % 6 == 0) {
                setEffect(Game::instance()->obj2dManager(), Game::instance()->bg(), &notesEffect0Behavior, { static_cast<float>(rand() % BG::WINDOW_W), static_cast<float>(rand() % BG::WINDOW_H) });
                setEffect(Game::instance()->obj2dManager(), Game::instance()->bg(), &notesEffect1Behavior, { static_cast<float>(rand() % BG::WINDOW_W), static_cast<float>(rand() % BG::WINDOW_H) });
                setEffect(Game::instance()->obj2dManager(), Game::instance()->bg(), &notesEffect2Behavior, { static_cast<float>(rand() % BG::WINDOW_W), static_cast<float>(rand() % BG::WINDOW_H) });
            }
            
            // スコア画面に遷移
            if (TRG(0) & PAD_START || timer_ > 1000) {
            
            // 襖開閉音
            GameLib::music::play(11, false);
            
            state_++;
            }
        }
        timer_++;
        break;
    case 6:
        //////// 襖が閉まる処理 ////////
        
        // オブジェクトの更新
        obj2dManager()->update();

        // BGの更新
        bg()->update();

        // HPバーのアニメーション
        AnimetionHP();

        if (G_L_Fusuma_Pos_.x <= 960 && G_R_Fusuma_Pos_.x >= (960 * 1.5f)) {
            G_L_Fusuma_Pos_.x += 30;
            G_R_Fusuma_Pos_.x -= 30;
        }

        if (G_L_Fusuma_Pos_.x >= 480 && G_R_Fusuma_Pos_.x <= (960 * 1.5f)) {
            G_L_Fusuma_Pos_.x = 480;
            G_R_Fusuma_Pos_.x = (960 * 1.5f);
            state_++;
        }
        break;
    case 7:
        //////// スコア画面に遷移 ////////
        // BGMを止める
        music::stop(stageNo_);

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
        if (Game::instance()->player()->actorComponent()->direction() == Game::instance()->player()->actorComponent()->LEFT
            && notesMaskFlag_ == true) {
            GameLib::primitive::rect(
                { player()->transform()->position().x - player()->collider()->size().x,
                  player()->transform()->position().y - player()->collider()->size().y },
                { BG::CLIENT_W, player()->collider()->size().y },
                { 0, 0 },
                ToRadian(0),
                { 0.0f, 0.0f, 0.0f, 0.0f }
            );
        }
        // ステンシルモード：マスク以外に描画
        DepthStencil::instance().set(DepthStencil::MODE::EXCLUSIVE);

        // 長押しノーツ(左)と連続ノーツ(左)の描画
        obj2dManager()->draw3(bg()->getScrollPos());
    }

    // 長押しノーツ(右)と連続ノーツ(右)の描画
    {
        // ステンシルモード：マスク生成
        DepthStencil::instance().set(DepthStencil::MODE::MASK);

        // 四角形
        if (Game::instance()->player()->actorComponent()->direction() == Game::instance()->player()->actorComponent()->RIGHT
            && notesMaskFlag_ == true) {
            GameLib::primitive::rect(
                { 0,
                  player()->transform()->position().y - player()->collider()->size().y },
                { player()->transform()->position().x + player()->collider()->size().x, player()->collider()->size().y },
                { 0, 0 },
                ToRadian(0),
                { 0.0f, 0.0f, 0.0f, 0.0f }
            );
        }

        // ステンシルモード：マスク以外に描画
        DepthStencil::instance().set(DepthStencil::MODE::EXCLUSIVE);

        // 長押しノーツ(右)と連続ノーツ(右)の描画
        obj2dManager()->draw4(bg()->getScrollPos());
    }

    // 長押しノーツ(上)と連続ノーツ(上)の描画
    {
        // ステンシルモード：マスク生成
        DepthStencil::instance().set(DepthStencil::MODE::MASK);

        // 四角形
        if (Game::instance()->player()->actorComponent()->direction() == Game::instance()->player()->actorComponent()->UP
            && notesMaskFlag_ == true) {
            GameLib::primitive::rect(
                { player()->transform()->position().x - (player()->collider()->size().x / 2),
                player()->transform()->position().y - (player()->collider()->size().y * 3 / 2) },
                { player()->collider()->size().x, player()->collider()->size().y * 2 },
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
    if ((player_->actorComponent()->playerHitTimer() >= 1 && player_->actorComponent()->playerHitTimer() <= 6) || 
        (player_->actorComponent()->playerHitTimer() >= 13 && player_->actorComponent()->playerHitTimer() <= 18)){
        GameLib::setBlendMode(Blender::BS_ADD);   // 通常のアルファ処理
    }
    
    obj2dManager()->drawPlayer(bg()->getScrollPos());

    GameLib::setBlendMode(Blender::BS_ALPHA);   // 通常のアルファ処理

    // エフェクトの描画
    obj2dManager()->drawEffect(bg()->getScrollPos());

    // HPバーの描画
    {
        if (player()->actorComponent()->hp() >= 0) {
            GameLib::setBlendMode(Blender::BS_ALPHA);   // 通常のアルファ処理
            // プレイヤーがダメージを食らったとき点滅させる
            if ((player_->actorComponent()->playerHitTimer() >= 1 && player_->actorComponent()->playerHitTimer() <= 6) ||
                (player_->actorComponent()->playerHitTimer() >= 13 && player_->actorComponent()->playerHitTimer() <= 18)) {
                GameLib::setBlendMode(Blender::BS_MULTIPLY);   // アルファ処理
            }

            primitive::rect(hpPos02,
                { hpSize02.x / player()->actorComponent()->maxHP() * player()->actorComponent()->hp(), hpSize02.y },
                { 0, 0 }, 0, hpColor02);
        }

        GameLib::setBlendMode(Blender::BS_ADD);   // 通常のアルファ処理

        texture::begin(TEXNO::HP_BAR);
        texture::draw(TEXNO::HP_BAR, hpPos01, { 1, 1 }, hpTexPos01, { 600, 150 });
        texture::end(TEXNO::HP_BAR);
        GameLib::setBlendMode(Blender::BS_ALPHA);   // 通常のアルファ処理
    }

    // スコア,コンボ数の描画
    scoreDraw();
    comboDraw();

    // ノーツ判定の描画
    decisionDraw();

    // 開幕の文字描画
    if (state_ == 1 || state_ == 2) {
        texture::begin(TEXNO::T_START);
        texture::draw(TEXNO::T_START, t_StartPos.x, t_StartPos.y, t_StartScale.x, t_StartScale.y,
            0, 0, t_StartSize.x, t_StartSize.y, t_StartSize.x / 2, t_StartSize.y / 2, 
            0, t_StartColor.x, t_StartColor.y, t_StartColor.z, t_StartColor.w);
        texture::end(TEXNO::T_START);
    }

    // 閉幕の文字描画
    if (state_ == 3 || state_ == 4 || state_ == 5) {
        texture::begin(TEXNO::T_END);
        texture::draw(TEXNO::T_END, t_EndPos.x, t_EndPos.y, t_EndScale.x, t_EndScale.y,
            0, 0, t_EndSize.x, t_EndSize.y, t_EndSize.x / 2, t_EndSize.y / 2,
            0, t_EndColor.x, t_EndColor.y, t_EndColor.z, t_EndColor.w);
        texture::end(TEXNO::T_END);
    }

    // フルコンボの文字の描画
    if (state_ == 5) {
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
        // 背景を少し暗くする
         GameLib::primitive::rect({ 0, 0 }, 
         { GameLib::window::getWidth(), GameLib::window::getHeight() },
         { 0, 0 }, 0, { 0, 0, 0, 0.3f }
         );

        GameLib::font::textOut(4, "PAUSE",
            { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 4) },
            VECTOR2(5.0f, 5.0f),
            { 1.0f, 1.0f, 1.0f, 1.0f },
            GameLib::TEXT_ALIGN::UPPER_MIDDLE
        );

        // 再開を選んでいるとき
        if (pause_num_ == 1)
        {
            // "再開"の描画
            sprContinue_.draw(
                { GameLib::window::getWidth() / 2 , GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,pause_alpha_ }
            );

            // "再挑戦"の文字の描画
            sprRestart_.draw(
                { GameLib::window::getWidth() / 2 - GameLib::window::getWidth() / 3, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,1 }
            );

            // "たいとるへ"の文字の描画
            sprTotitle_.draw(
                { GameLib::window::getWidth() / 2 + GameLib::window::getWidth() / 3, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,1 }
            );
        }
        
        // たいとるへを選んでいるとき
        if (pause_num_ == 2)
        {
            // "再開"の描画
            sprContinue_.draw(
                { GameLib::window::getWidth() / 2 , GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,1 }
            );

            // 位置の変更
            // "再挑戦"の文字の描画
            sprRestart_.draw(
                { GameLib::window::getWidth() / 2 - GameLib::window::getWidth() / 3, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,pause_alpha_ }
            );

            // 位置の変更
            // "たいとるへ"の文字の描画
            sprTotitle_.draw(
                { GameLib::window::getWidth() / 2 + GameLib::window::getWidth() / 3, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,1 }
            );
        }
        
        // たいとるへを選んでいるとき
        if (pause_num_ == 0)
        {
            // "再開"の描画
            sprContinue_.draw(
                { GameLib::window::getWidth() / 2 , GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,1 }
            );

            // 位置の変更
            //"再挑戦"の文字の描画
            sprRestart_.draw(
                { GameLib::window::getWidth() / 2 - GameLib::window::getWidth() / 3, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,1 }
            );
            //位置の変更
            //"たいとるへ"の文字の描画
            sprTotitle_.draw(
                { GameLib::window::getWidth() / 2 + GameLib::window::getWidth() / 3, GameLib::window::getHeight() / 2 + GameLib::window::getHeight() / 4 },
                { 1.0f,1.0f },
                ToRadian(0),
                { 1,1,1,pause_alpha_ }
            );
        }
    }

    // 攻撃当たり判定
    if(state_ < 3){
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
    for (int i = 0; i < 11; i++) {
        primitive::rect({ 2400 , shuriken_Pos_[i].y + 64 }, { shuriken_Pos_[i].x - 2400 + 64 , 128 }, { 0,128 }, ToRadian(0), { 0.0f,0.0f,0.0f,1.0f });
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

//--------------------------------------------------------------
//  UI
//--------------------------------------------------------------

void Game::calcCombo()
{
    // 最大コンボの更新
    if (combo() > maxCombo()) {
        setMaxCombo(combo());
    }

    // コンボ数に応じて色を変更
    if (combo() >= 50) {
        comboColor = { 1.0f, 1.0f, 0.0f, 1.0f };   // 黄色
    }
    else if (combo() >= 25) {
        comboColor = { 0.2f, 1.0f, 1.0f, 1.0f };   // 水色
    }
    else {
        comboColor = { 1, 1, 1, 1 };       // 白色
    }

    // スコア表示をもとに戻す
    if (combo2Timer_ >= maxAppearTime_) {
        combo2Pos   = { 1890, 360 };        // コンボの位置
        combo2Size  = { 1.5f, 1.5f };       // コンボの大きさ
        if (combo2() >= 10) {
            combo2Color = { 1.0f, 1.0f, 0.0f, 0.0f }; // 黄色
        }
        else if (combo2() >= 5) {
            combo2Color = { 0.2f, 1.0f, 1.0f, 0.0f }; // 水色
        }
        else {
            combo2Color = { 1, 1, 1, 0 }; // 白色
        }
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
    if (combo2Pos.y < 300)        combo2Pos.y = 300;
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
        { 1890, 200 },
        { 1.5f, 1.5f },
        { 1.0f, 1.0f, 1.0f, 1.0f },
        TEXT_ALIGN::MIDDLE_RIGHT
    );

    font::textOut(6,
        ss1.str(),
        { 1897, 207 },
        { 1.5f, 1.5f },
        { 1.0f, 1.0f, 1.0f, 0.1f },
        TEXT_ALIGN::MIDDLE_RIGHT
    );

    // コンボ数の描画
    font::textOut(6,
        ss2.str(),
        { 1890, 200 },
        comboSize,
        comboColor,
        TEXT_ALIGN::MIDDLE_RIGHT
    );

    font::textOut(6,
        ss2.str(),
        1897, 207,
        comboSize.x, comboSize.y,
        comboColor.x, comboColor.y, comboColor.z, comboColor.w - 0.9f,
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

        font::textOut(6,
            ss3.str(),
            combo2Pos.x + 7, combo2Pos.y + 7,
            combo2Size.x, combo2Size.y,
            combo2Color.x, combo2Color.y, combo2Color.z, combo2Color.w - 0.9f,
            TEXT_ALIGN::MIDDLE_RIGHT
        );
    }
}

void Game::calcScore()
{
    // スコア表示をもとに戻す
    if (scoreTimer_ >= maxAppearTime_) {
        scorePos    = { 10, 80 };           // スコアの位置
        scoreColor.w  = 0;       // スコアの色
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

    font::textOut(6,
        ss1.str(),
        { 17, 17 },
        { 1.5f, 1.5f },
        { 1.0f, 1.0f, 1.0f, 0.1f },
        TEXT_ALIGN::UPPER_LEFT
    );

    if (scoreTimer_) {
        // スコア数をテキスト表示
        font::textOut(6,
            ss2.str(),
            scorePos.x, scorePos.y,
            scoreSize.x, scoreSize.y,
            notesColor.x, notesColor.y, notesColor.z, scoreColor.w,
            TEXT_ALIGN::UPPER_LEFT
        );

        font::textOut(6,
            ss2.str(),
            scorePos.x + 7, scorePos.y + 7,
            scoreSize.x, scoreSize.y,
            notesColor.x, notesColor.y, notesColor.z, scoreColor.w - 0.9f,
            TEXT_ALIGN::UPPER_LEFT
        );
    }
}

// ノーツ判定の判別
void Game::decisionJudge()
{
    VECTOR2 BGThreeQuarters = { BG::WINDOW_W / 4 * 3 - 320, BG::WINDOW_H / 4 * 3 - 75 };

    switch (decision_)
    {
    case Game::MISS:
        notesText.str("MISS");
        notesTimer_ = maxAppearTime_;
        notesPos    = { BGThreeQuarters.x, BGThreeQuarters.y };
        notesSize   = { 0.2f, 0.2f };
        notesColor  = { 0.0f, 0.0f, 1.0f, 0.0f };
        decision_   = NONE;
        break;
    case Game::GOOD:
        notesText.str("GOOD");
        notesTimer_ = maxAppearTime_;
        notesPos    = { BGThreeQuarters.x, BGThreeQuarters.y };
        notesSize   = { 0.2f, 0.2f };
        notesColor  = { 1.0f, 1.0f, 1.0f, 0.0f };
        decision_   = NONE;
        break;
    case Game::GREAT:
        notesText.str("GREAT");
        notesTimer_ = maxAppearTime_;
        notesPos    = { BGThreeQuarters.x, BGThreeQuarters.y };
        notesSize   = { 0.2f, 0.2f };
        notesColor  = { 0.2f, 1.0f, 1.0f, 0.0f };
        decision_   = NONE;
        break;
    case Game::PERFECT:
        notesText.str("PERFECT");
        notesTimer_ = maxAppearTime_;
        notesPos    = { BGThreeQuarters.x, BGThreeQuarters.y };
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
    if (notesPos.y < BGThreeQuarters.y - 20)       notesPos.y   = BGThreeQuarters.y - 20;
    if (notesSize.x > 1.5f)     notesSize    = { 1.5f, 1.5f };
    notesColor.w = clamp(notesColor.w, 0.0f, 1.0f);
    debug::setString("notesTimer:%d", notesTimer_);
    debug::setString("notesColor.w:%f", notesColor.w);
}

// ノーツ判定の描画
void Game::decisionDraw()
{
    if (notesTimer_ > 0) {
        // コンボ数をテキスト表示
        font::textOut(6,
            notesText.str(),
            notesPos,
            notesSize,
            notesColor,
            TEXT_ALIGN::LOWER_LEFT
        );

        // コンボ数をテキスト表示
        font::textOut(6,
            notesText.str(),
            notesPos.x + 7, notesPos.y + 7,
            notesSize.x, notesSize.y,
            notesColor.x, notesColor.y, notesColor.z, notesColor.w - 0.9f,
            TEXT_ALIGN::LOWER_LEFT
        );
    }
}

// HPのアニメーション
void Game::AnimetionHP() {
    // 6フレームごとにアニメーション切替
    if (HPAnimeTimer_ % 6 == 0) {
        if (hpTexPos01.x == 0) {
            hpTexPos01.x = 600;
        }
        else if (hpTexPos01.x == 600) {
            hpTexPos01.x = 1200;
        }
        else if (hpTexPos01.x == 1200) {
            hpTexPos01.x = 0;
        }
    }
    // HPを増やす処理
    if (state_ > 1 && hpSize02.x < 490) {
        hpSize02.x += 5;
    }
    HPAnimeTimer_++;
}

// チュートリアル
void Game::operationDraw() {
    //チュートリアル画像の移動処理
    if (stageNo_ == 0 && state_ != 1 && timer_ > 30)
    {
        switch (tutorial_State_)
        {
        case 0:
            sprTutorial0_.draw(
                tutorial_pos_
            );

            if (isPaused_) return;

            tutorial_pos_.x += 10;

            if (tutorial_pos_.x > 300)
            {
                tutorial_pos_.x = 300;
                tutorial_timer_++;
            }

            if (tutorial_timer_ > 360)
            {
                tutorial_timer_ = 0;
                tutorial_State_++;
                break;
            }

            break;

        case 1:
            sprTutorial0_.draw(
                tutorial_pos_
            );

            if (isPaused_) return;

            tutorial_pos_.x -= 10;

            if (tutorial_pos_.x < -300)
            {
                tutorial_pos_.x = -300;
                tutorial_State_++;
                break;
            }
            break;

        case 2:
            sprTutorial1_.draw(
                tutorial_pos_
            );

            if (isPaused_) return;

            tutorial_pos_.x += 10;

            if (tutorial_pos_.x > 300)
            {
                tutorial_pos_.x = 300;
                tutorial_timer_++;
            }

            if (tutorial_timer_ > 1900)
            {
                tutorial_timer_ = 0;
                tutorial_State_++;
                break;
            }

            break;

        case 3:
            sprTutorial1_.draw(
                tutorial_pos_
            );

            if (isPaused_) return;

            tutorial_pos_.x -= 10;

            if (tutorial_pos_.x < -300)
            {
                tutorial_pos_.x = -300;
                tutorial_State_++;
                break;
            }
            break;

        case 4:
            sprTutorial3_.draw(
                tutorial_pos_
            );

            if (isPaused_) return;

            tutorial_pos_.x += 10;

            if (tutorial_pos_.x > 300)
            {
                tutorial_pos_.x = 300;
                tutorial_timer_++;
            }

            if (tutorial_timer_ > 600)
            {
                tutorial_timer_ = 0;
                tutorial_State_++;
                break;
            }

            break;

        case 5:
            sprTutorial3_.draw(
                tutorial_pos_
            );

            if (isPaused_) return;

            tutorial_pos_.x -= 10;

            if (tutorial_pos_.x < -300)
            {
                tutorial_pos_.x = -300;
                tutorial_State_++;
                break;
            }
            break;

        case 6:
            sprTutorial2_.draw(
                tutorial_pos_
            );

            if (isPaused_) return;

            tutorial_pos_.x += 10;

            if (tutorial_pos_.x > 300)
            {
                tutorial_pos_.x = 300;
                tutorial_timer_++;
            }

            if (tutorial_timer_ > 900)
            {
                tutorial_timer_ = 0;
                tutorial_State_++;
                break;
            }

            break;

        case 7:
            sprTutorial2_.draw(
                tutorial_pos_
            );

            if (isPaused_) return;

            tutorial_pos_.x -= 10;

            if (tutorial_pos_.x < -300)
            {
                tutorial_pos_.x = -300;
                tutorial_State_++;
                break;
            }
            break;

        case 8:
            sprTutorial4_.draw(
                tutorial_pos_
            );

            if (isPaused_) return;

            tutorial_pos_.x += 10;

            if (tutorial_pos_.x > 300)
            {
                tutorial_pos_.x = 300;
                tutorial_timer_++;
            }

            if (tutorial_timer_ > 600)
            {
                tutorial_timer_ = 0;
                tutorial_State_++;
                break;
            }

            break;

        case 9:
            sprTutorial4_.draw(
                tutorial_pos_
            );

            if (isPaused_) return;

            tutorial_pos_.x -= 10;

            if (tutorial_pos_.x < -300)
            {
                tutorial_pos_.x = -300;
                tutorial_State_++;
                break;
            }
            break;

        }
    }
}

//******************************************************************************