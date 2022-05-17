//******************************************************************************
//
//
//      BGクラス
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

bool isDebugDraw;

//----------------------------------------------------------------------
//  コンストラクタ
//----------------------------------------------------------------------
BG::BG()
    :scroll(VECTOR2(0, 0))
    , player_(nullptr)
{
}

//----------------------------------------------------------------------
//  デストラクタ
//----------------------------------------------------------------------
BG::~BG()
{
}

//----------------------------------------------------------------------
//  初期設定
//----------------------------------------------------------------------
void BG::init(OBJ2D* player)
{
    player_ = player;

    // BG用データのクリア
    clear();
}

//----------------------------------------------------------------------
//  メンバ変数のクリア
//----------------------------------------------------------------------
void BG::clear()
{
    scroll = {}; // スクロール座標（画面左上の位置のワールド座標）
}

//----------------------------------------------------------------------
//  更新処理
//----------------------------------------------------------------------
void BG::update()
{
    scrollMap();
}

//----------------------------------------------------------------------
//  マップのスクロール
//----------------------------------------------------------------------
void BG::scrollMap()
{
    Transform* transform = player_->transform();
    Collider* collision = player_->collider();

    // スクロール処理
    // if (player_) {
    //     // 右方向のスクロール処理
    //     if (scroll.x < transform->position().x + collision->size().x - CLIENT_W + SCROLL_MERGIN_X)
    //         scroll.x = transform->position().x + collision->size().x - CLIENT_W + SCROLL_MERGIN_X;
    // 
    //     // 左方向のスクロール処理
    //     if (scroll.x > transform->position().x - collision->size().x - SCROLL_MERGIN_X)
    //         scroll.x = transform->position().x - collision->size().x - SCROLL_MERGIN_X;
    // 
    //     // 下方向のスクロール処理
    //     if (scroll.y < transform->position().y - CLIENT_H + SCROLL_MERGIN_Y)
    //         scroll.y = transform->position().y - CLIENT_H + SCROLL_MERGIN_Y;
    // 
    //     // 上方向のスクロール処理
    //     if (scroll.y > transform->position().y - collision->size().y - SCROLL_MERGIN_Y)
    //         scroll.y = transform->position().y - collision->size().y - SCROLL_MERGIN_Y;
    // 
    //     // エリア制限（右）
    //     if (scroll.x > BG::WIDTH - CLIENT_W)
    //         scroll.x = BG::WIDTH - CLIENT_W;
    // 
    //     // エリア制限（左）
    //     if (scroll.x < 0)
    //         scroll.x = 0;
    // 
    //     // エリア制限（下）
    //     if (scroll.y > BG::HEIGHT - CLIENT_H)
    //         scroll.y = BG::HEIGHT - CLIENT_H;
    // 
    //     // エリア制限（上）
    //     if (scroll.y < 0)
    //         scroll.y = 0;
    // }

    using namespace input;
    if (TRG(0) & PAD_TRG2)
    {
        isDebugDraw = !isDebugDraw;
    }
    // TODO:debug
    // debug::setString("transform->position().x:%f", transform->position().x);
    // debug::setString("transform->position().y:%f", transform->position().y);
}

//----------------------------------------//
//              背景描画   　　           //
//----------------------------------------//
void BG::drawBack()
{
    // const int REM_X = static_cast<int>(scroll.x);
    // const int REM_Y = static_cast<int>(scroll.y);

    texture::begin(TEXNO::MAP_BACK);
    texture::draw(TEXNO::MAP_BACK, 0, 0, 1, 1, 0, 0, 1920, 1080, 0, 0, 0);
    texture::end(TEXNO::MAP_BACK);
}