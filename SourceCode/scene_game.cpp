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
     if (isPaused_)
     {
         if (TRG(0) & PAD_START)
         {
            //決定音
             GameLib::music::play(7, false);

             changeScene(Title::instance());
         }

         if (TRG(0) & PAD_SELECT)
         {
            //決定音
             GameLib::music::play(7, false);

             changeScene(Game::instance());
         }

         //音楽を止める
         GameLib::music::pause(0);

         return;              // この時点でポーズ中ならリターン
     }

    switch (state_)
    {
    case 0:
        //////// 初期設定 ////////
        
        timer_ = 0;     // ゲームタイマー
        combo_ = 0;     // コンボ数
        maxCombo_ = 0;  // 最大コンボ数

        // HPバーの設定
        hpPos01     = { 950,  20 };        // HPバーの位置
        hpSize01    = { 300,  60 };        // HPバーの大きさ
        hpColor01   = { 0, 0, 0, 1.0f };   // HPバーの色
        hpPos02     = { 955,  25 };        // HPバーの位置
        hpSize02    = { 290,  50 };        // HPバーの大きさ
        hpColor02   = { 1, 0, 0, 0.5f };   // HPバーの色

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
            &idlePlayerBehavior, VECTOR2(640, 700), -1);

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

        // 最大コンボの更新
        calcMaxCombo();

        // ノーツ判定の更新
        decisionJudge();

        if (TRG(0) & PAD_SELECT)
        {
            GameLib::music::stop(0);
            changeScene(Score::instance());
            break;
        }
        timer_++;

        break;
    }
    debug::setString("Combo:%d", combo());
    debug::setString("maxCombo:%d", maxCombo());
   
    debug::setString("stageNo:%d", Game::instance()->stageNo());
    debug::setString("GameTimer:%d", timer_);
}

//--------------------------------------------------------------
//  描画処理
//--------------------------------------------------------------
void Game::draw()
{
    // 画面クリア
    GameLib::clear(VECTOR4(0.2f, 0.2f, 0.2f, 1));

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
    scoreDraw();
    comboDraw();

    // ノーツ判定の描画
    decisionDraw();

    // ポーズ画面
    if (isPaused_)
    {
        GameLib::font::textOut(4, "PAUSE",
            { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 4) },
            VECTOR2(5.0f, 5.0f),
            { 1.0f, 1.0f, 1.0f, 1.0f },
            GameLib::TEXT_ALIGN::UPPER_MIDDLE
        );

        GameLib::font::textOut(4, "ENTER : Return To Title",
            { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 2) },
            VECTOR2(2.0f, 2.0f),
            { 1.0f, 1.0f, 1.0f, 1.0f },
            GameLib::TEXT_ALIGN::UPPER_MIDDLE
        );

        GameLib::font::textOut(4, "BACKSPACE : RESTART",
            { GameLib::window::getWidth() / 2, (GameLib::window::getHeight() / 2 + 100) },
            VECTOR2(2.0f, 2.0f),
            { 1.0f, 1.0f, 1.0f, 1.0f },
            GameLib::TEXT_ALIGN::UPPER_MIDDLE
        );
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
        }
    }
}

void Game::calcMaxCombo()
{
    // 最大コンボの更新
    if (combo() > maxCombo()) {
        setMaxCombo(combo());
    }
}

// コンボの描画設定
void Game::comboDraw()
{
    std::ostringstream ss1;

    ss1 << "COMBO" << std::setw(4) << combo_;
    
    // コンボ数をテキスト表示
    font::textOut(6,
        ss1.str(),
        { 1250, 120 },
        { 1.0f, 1.0f },
        { 1.0f, 1.0f, 1.0f, 1.0f },
        TEXT_ALIGN::MIDDLE_RIGHT
    );
}

// スコアの描画設定
void Game::scoreDraw()
{
    std::ostringstream ss1;

    ss1 << "SCORE" << std::setw(8) << std::setfill('0') << score_;

    // スコア数をテキスト表示
    font::textOut(6,
        ss1.str(),
        { 10, 10 },
        { 1.0f, 1.0f },
        { 1.0f, 1.0f, 1.0f, 1.0f },
        TEXT_ALIGN::UPPER_LEFT
    );
}

// ノーツの判定判別
void Game::decisionJudge()
{
    switch (decision_)
    {
    case Game::MISS:
        break;
    case Game::GOOD:
        goodTimer = 60;
        greatTimer, perfectTimer = 0;       
        decision_ = MAX;
        break;
    case Game::GREAT:
        greatTimer = 60;
        goodTimer, perfectTimer = 0;
        decision_ = MAX;
        break;
    case Game::PERFECT:
        perfectTimer = 60;
        goodTimer, greatTimer = 0;
        decision_ = MAX;
        break;
    default:
        break;
    }
    if (goodTimer > 0)
        goodTimer--;
    if (greatTimer > 0)
        greatTimer--;
    if (perfectTimer > 0)
        perfectTimer--;
}

void Game::decisionDraw()
{
    std::ostringstream ss1;

    // GOODを描画
    if (goodTimer > 0) {
        ss1 << "GOOD";

        // コンボ数をテキスト表示
        font::textOut(6,
            ss1.str(),
            { 1250, 180 },
            { 1.0f, 1.0f },
            { 1.0f, 1.0f, 1.0f, 1.0f },
            TEXT_ALIGN::MIDDLE_RIGHT
        );
    }
    // GREATを描画
    if (greatTimer > 0)
    {
        ss1 << "GREAT";

        // コンボ数をテキスト表示
        font::textOut(6,
            ss1.str(),
            { 1250, 180 },
            { 1.0f, 1.0f },
            { 0.0f, 1.0f, 1.0f, 1.0f },
            TEXT_ALIGN::MIDDLE_RIGHT
        );
    }
    // PERFECTを描画
    if (perfectTimer > 0)
    {
        ss1 << "PERFECT";

        // コンボ数をテキスト表示
        font::textOut(6,
            ss1.str(),
            { 1250, 180 },
            { 1.0f, 1.0f },
            { 1.0f, 1.0f, 0.0f, 1.0f },
            TEXT_ALIGN::MIDDLE_RIGHT
        );
    }
}

//******************************************************************************