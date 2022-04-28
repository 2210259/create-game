#pragma once
//******************************************************************************
//
//      bg.h
//
//******************************************************************************

//==============================================================================
//
//      BGクラス
//
//==============================================================================

class BG
{
public:
    //------< 定数 >------------------------------------------------------------
    // TOOD:フルスクリーンの表示に変える
    static const int WINDOW_W = 1280;                   // ウインドウの幅
    static const int WINDOW_H = 720;                    // ウインドウの高さ
    static const int CLIENT_W = 1280;                   // クライアント領域の幅
    static const int CLIENT_H = 720;                    // クライアント領域の高さ

    // static const int CHIP_SIZE = 64;                    // %演算子を使用するためint型を使用する
    // static const int LOOP_X = CLIENT_W / CHIP_SIZE + (CLIENT_W % CHIP_SIZE ? 2 : 1);
    // static const int LOOP_Y = CLIENT_H / CHIP_SIZE + (CLIENT_H % CHIP_SIZE ? 2 : 1);

    // static const int CHIP_NUM_X = 20;                   // マップの横方向のチップ数
    // static const int CHIP_NUM_Y = 12;                   // マップの縦方向のチップ数
    // static const int CHIP_NUM_PER_LINE = 6;             // マップチップの1列が8個
    // static const int CHIP_LINE_NUM = 2;                 // マップチップが４行

    // static constexpr float CHIP_SIZE_F = static_cast<float>(CHIP_SIZE);
    static constexpr float WIDTH  = WINDOW_W;  // マップの幅
    static constexpr float HEIGHT = WINDOW_H; // マップの高さ
    static constexpr float SCROLL_MERGIN_X = 240.f;     // この数値より画面端に近づいたらスクロールする（横）
    static constexpr float SCROLL_MERGIN_Y = 160.f;     // この数値より画面端に近づいたらスクロールする（縦）
    // static constexpr float ADJUST_Y = 0.25f;            // あたり判定での位置調整用（縦）
    // static constexpr float ADJUST_X = 0.025f;           // あたり判定での位置調整用（横）

private:

    //------< 変数 >------------------------------------------------------------
    VECTOR2 scroll;                                         // 現在表示されている左上の地点の座標
    OBJ2D* player_;

public:
    BG();
    ~BG();

    // 初期化
    void init(OBJ2D* player);

    // 更新
    void update();

    // 描画
    void drawBack(); //背景描画

    // void drawObject();                                      // オブジェクト描画
    // void drawTerrain();                                     // 地形描画
    
    // スクロール位置取得
    float getScrollX() { return scroll.x; }
    float getScrollY() { return scroll.y; }
    const VECTOR2& getScrollPos() { return scroll; }

private:
    // クリア
    void clear();

    // マップスクロール用
    void scrollMap();
};

//******************************************************************************
