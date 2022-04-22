//******************************************************************************
//
//
//      ゲーム
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

    // 音楽のクリア
    music::clear();
}

//--------------------------------------------------------------
//  更新処理
//--------------------------------------------------------------
void Game::update()
{
    using namespace input;

    // ソフトリセット
    if ((STATE(0) & PAD_SELECT) &&      // 0コンのセレクトボタンが押されている状態で
        (TRG(0) & PAD_START))           // 0コンのスタートボタンが押された瞬間
    {
        changeScene(Title::instance()); // タイトルシーンに切り替える
        return;
    }

    // ポーズ処理
    if (TRG(0) & PAD_START)
        isPaused_ = !isPaused_;         // 0コンのスタートボタンが押されたらポーズ状態が反転
    if (isPaused_) return;              // この時点でポーズ中ならリターン

    switch (state_)
    {
    case 0:
        //////// 初期設定 ////////
        timer_ = 0;

        GameLib::setBlendMode(Blender::BS_ALPHA);   // 通常のアルファ処理

        // テクスチャの読み込み
        texture::load(loadTexture);

        // OBJ2Dマネージャの初期設定
        obj2dManager()->init();

        // アイテムをセット
        setItem(obj2dManager(), bg());

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
            &walkPlayerBehavior, VECTOR2(160, 1152));

        // BGの初期設定
        bg()->init(player_);

        state_++;    // 初期設定処理の終了
        /*fallthrough*/

    case 1:
        //////// 通常時の処理 ////////

        // オブジェクトの更新
        obj2dManager()->update();

        // プレイヤーがいなくなったらタイトルに戻す
        if (player_ == nullptr)
        {
            changeScene(Title::instance());
            break;
        }

        bg()->update();   // BGの更新
        judge();

        timer_++;

        break;
    }
}

//--------------------------------------------------------------
//  描画処理
//--------------------------------------------------------------
void Game::draw()
{
    // 画面クリア
    GameLib::clear(VECTOR4(0, 0, 0, 1));

    bg()->drawBack();     // 背景の描画
    bg()->drawTerrain();  // 地形の描画

    // オブジェクトの描画
    obj2dManager()->draw(bg()->getScrollPos());
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
            if (!src->behavior()) continue;

            if (src == dst) continue;       // 自分自身はとばす
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
        }
    }
}

//******************************************************************************
