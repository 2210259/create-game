//******************************************************************************
//
//
//      ゲーム画面
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include "all.h"

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
    music::clear();
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
            GameLib::sound::play(0,0);

             changeScene(Title::instance());
         }

         if (TRG(0) & PAD_SELECT)
         {
            //決定音
             GameLib::sound::play(0, 0);

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
        timer_ = 0;

        //BGMの再生
        GameLib::music::play(0, false);

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

        judge();

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
            if (!dst->behavior()) break;
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

//******************************************************************************