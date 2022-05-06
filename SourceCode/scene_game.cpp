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
         GameLib::music::resume(0);

         // 0コンのスタートボタンが押されたらポーズ状態が反転
         isPaused_ = !isPaused_;        
     }

     //ポーズ中
     if (isPaused_)
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

         //音楽を止める
         GameLib::music::pause(0);

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
                 changeScene(Game::instance());
             }
         }

         //１(たいとるへ)を選んでいるとき
         if (pause_num_ == false)
         {
             if (TRG(0) & PAD_START)
             {
                 music::play(7);
                 changeScene(Title::instance());
             }
         }

         return;              // この時点でポーズ中ならリターン
     }

    switch (state_)
    {
    case 0:
        //////// 初期設定 ////////
        
        timer_       = 0;    // ゲームタイマー
        combo2Timer_ = 0;
        scoreTimer_  = 0;    // スコアタイマー
        notesTimer_  = 0;    // ノーツタイマー
        score_       = 0;    // スコア
        combo_       = 0;    // コンボ数
        combo2_      = 0;    // コンボ数(連打)
        maxCombo_    = 0;    // 最大コンボ数

        // HPバーの設定
        hpPos01      = { 950,  20 };         // HPバーの位置
        hpSize01     = { 300,  60 };         // HPバーの大きさ
        hpColor01    = { 0, 0, 0, 1.0f };    // HPバーの色
        hpPos02      = { 955,  25 };         // HPバーの位置
        hpSize02     = { 290,  50 };         // HPバーの大きさ
        hpColor02    = { 1, 0, 0, 0.8f };    // HPバーの色
        comboSize    = { 1, 1 };             // コンボの大きさ
        combo2Pos    = { 1250, 240 };        // コンボ2の位置
        combo2Size   = { 1, 1 };             // コンボ2の大きさ             
        combo2Color  = { 1, 1, 1, 0 };       // コンボ2の色
        scorePos     = { 10, 80 };           // スコアの位置
        scoreSize    = { 1, 1 };             // スコアの大きさ             
        scoreColor   = { 1, 1, 1, 0 };       // スコアの色
        notesPos     = { 1250, 200 };        // ノーツの位置
        notesSize    = { 1, 1 };             // ノーツの大きさ             
        notesColor   = { 1, 1, 1, 0 };       // ノーツの色

        // BGMの再生
        music::play(0, false);

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
                nullptr
            ),
            &idlePlayerBehavior, VECTOR2(640, 700), -1, {});

        // BGの初期設定
        bg()->init(player_);

        state_++;    // 初期設定処理の終了
        /*fallthrough*/

    case 1:
        //////// 通常時の処理 ////////

        // オブジェクトの更新
        obj2dManager()->update();

        bg()->update();   // BGの更新

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

        // TODO:ゲームの終了時間の調整
        if (timer_ > 100) {
            GameLib::music::stop(0);
            changeScene(Score::instance());
            break;
        }
        timer_++;
        break;
    }
    // debug::setString("Combo:%d", combo());
    // debug::setString("maxCombo:%d", maxCombo());
    // 
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

    bg()->drawBack();   // オブジェクトの描画

    // オブジェクトの描画
    obj2dManager()->draw(bg()->getScrollPos());

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

    //左の攻撃範囲表示
    primitive::rect(445, 610, 30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.2f);
    //右の攻撃範囲表示
    primitive::rect(805, 610, 30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.2f);
    //上の攻撃範囲表示
    primitive::rect(625, 430, 30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.2f);

    //プレイヤーが左を向いていたら
    if (player()->actorComponent()->direction() == player()->actorComponent()->LEFT)
    {
        //左の攻撃範囲表示
        primitive::rect(445, 610, 30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.6f);
    }
    //プレイヤーが左を向いていたら
    if (player()->actorComponent()->direction() == player()->actorComponent()->RIGHT)
    {
        //右の攻撃範囲表示
        primitive::rect(805, 610, 30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.6f);
    }
     //プレイヤーが左を向いていたら
    if (player()->actorComponent()->direction() == player()->actorComponent()->UP)
    {
        //上の攻撃範囲表示
        primitive::rect(625, 430, 30, 30, 0, 0, ToRadian(0), 1.0f, 1.0f, 1.0f, 0.6f);
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
        combo2Pos   = { 1250, 240 };        // コンボの位置
        combo2Size  = { 1, 1 };             // コンボの大きさ
        combo2Color = { 1, 1, 1, 0 };       // コンボの色
    }
    // タイマーを減らす
    if (combo2Timer_ > 0) combo2Timer_--;

    // パラメータを変更
    
    // コンボ1の設定
    if (comboSize.x > 1.0f) 
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
    combo2Size.x = clamp(combo2Size.x, 1.0f, 1.5f);
    combo2Size.y = clamp(combo2Size.y, 1.0f, 1.5f);
    if (combo2Pos.y < 240)        combo2Pos.y = 240;
    combo2Size.x = clamp(combo2Size.x, 1.0f, 1.3f);
    combo2Size.y = clamp(combo2Size.y, 1.0f, 1.3f);
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
        { 1250, 120 },
        { 1.0f, 1.0f },
        { 1.0f, 1.0f, 1.0f, 1.0f },
        TEXT_ALIGN::MIDDLE_RIGHT
    );

    font::textOut(6,
        ss2.str(),
        { 1250, 120 },
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
        { 1.0f, 1.0f },
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
        notesPos    = { 1250, 200 };
        notesSize   = { 0.2f, 0.2f };
        notesColor  = { 0.0f, 0.0f, 1.0f, 0.0f };
        decision_   = NONE;
        break;
    case Game::GOOD:
        notesText.str("GOOD");
        notesTimer_ = maxAppearTime_;
        notesPos    = { 1250, 200 };
        notesSize   = { 0.2f, 0.2f };
        notesColor  = { 1.0f, 1.0f, 1.0f, 0.0f };
        decision_   = NONE;
        break;
    case Game::GREAT:
        notesText.str("GREAT");
        notesTimer_ = maxAppearTime_;
        notesPos    = { 1250, 200 };
        notesSize   = { 0.2f, 0.2f };
        notesColor  = { 0.2f, 1.0f, 1.0f, 0.0f };
        decision_   = NONE;
        break;
    case Game::PERFECT:
        notesText.str("PERFECT");
        notesTimer_ = maxAppearTime_;
        notesPos    = { 1250, 200 };
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
    if (notesPos.y < 180)       notesPos.y   = 180;
    if (notesSize.x > 1.0f)     notesSize    = { 1.0f,1.0f };
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