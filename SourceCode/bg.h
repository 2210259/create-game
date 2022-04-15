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
    static const int WINDOW_W = 1280;                   // ウインドウの幅
    static const int WINDOW_H = 720;                    // ウインドウの高さ
    static const int CLIENT_W = 1280;                   // クライアント領域の幅
    static const int CLIENT_H = 720;                    // クライアント領域の高さ

    static const int CHIP_SIZE = 64;                    // %演算子を使用するためint型を使用する
    static const int LOOP_X = CLIENT_W / CHIP_SIZE + (CLIENT_W % CHIP_SIZE ? 2 : 1);
    static const int LOOP_Y = CLIENT_H / CHIP_SIZE + (CLIENT_H % CHIP_SIZE ? 2 : 1);

    static const int CHIP_NUM_X = 20;                   // マップの横方向のチップ数
    static const int CHIP_NUM_Y = 12;                   // マップの縦方向のチップ数
    static const int CHIP_NUM_PER_LINE = 6;             // マップチップの1列が8個
    static const int CHIP_LINE_NUM = 2;                 // マップチップが４行

    static constexpr float CHIP_SIZE_F = static_cast<float>(CHIP_SIZE);
    static constexpr float WIDTH = static_cast<float>(CHIP_NUM_X * CHIP_SIZE);  // マップの幅（ドット）
    static constexpr float HEIGHT = static_cast<float>(CHIP_NUM_Y * CHIP_SIZE); // マップの高さ（ドット）
    static constexpr float SCROLL_MERGIN_X = 240.f;     // この数値より画面端に近づいたらスクロールする（横）
    static constexpr float SCROLL_MERGIN_Y = 160.f;     // この数値より画面端に近づいたらスクロールする（縦）
    static constexpr float ADJUST_Y = 0.25f;            // あたり判定での位置調整用（縦）
    static constexpr float ADJUST_X = 0.025f;           // あたり判定での位置調整用（横）

    // 地形（Terrain）の属性
    enum class TR_ATTR
    {
        TR_NONE = -1,   // -1:何もなし
        ALL_BLOCK,      //  0:四方ブロック
        UPPER_BLOCK,    //  1:上だけブロック
        HASHIGO,        //  2:はしご
    };

    // オブジェクト（Back）の属性
    enum class OB_ATTR
    {
        BG_NONE = -1,   // -1:何もなし
        NORMAL,         //  0:普通（特に何もなし）
        WATER,          //  1:水中（抵抗を受ける）
    };

private:
    // 地形チップテクスチャの各部分の属性を定義する
    const TR_ATTR terrainAttr[CHIP_LINE_NUM * CHIP_NUM_PER_LINE] = {
        TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::ALL_BLOCK,   TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK,
        TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK,   TR_ATTR::ALL_BLOCK,
    };

    // オブジェクトチップテクスチャの各部分の属性を定義する
    const OB_ATTR ObjectAttr[CHIP_LINE_NUM * CHIP_NUM_PER_LINE] = {
        OB_ATTR::NORMAL,      OB_ATTR::NORMAL,      OB_ATTR::NORMAL,      OB_ATTR::NORMAL,      OB_ATTR::NORMAL,    OB_ATTR::NORMAL,
        OB_ATTR::BG_NONE,     OB_ATTR::BG_NONE,     OB_ATTR::BG_NONE,     OB_ATTR::BG_NONE,     OB_ATTR::BG_NONE,   OB_ATTR::BG_NONE,
    };

    //------< 変数 >------------------------------------------------------------
    VECTOR2 scroll;                                         // 現在表示されている左上の地点の座標
    OBJ2D* player_;

    char terrain[CHIP_NUM_Y][CHIP_NUM_X];                   // 地形データ
    char object[CHIP_NUM_Y][CHIP_NUM_X];                    // オブジェクトデータ

public:
    BG();
    ~BG();

    // 初期化
    void init(OBJ2D* player);

    // 更新
    void update();

    // 描画
    void drawObject();                                      // オブジェクト描画
    void drawTerrain();                                     // 地形描画

    // スクロール位置取得
    float getScrollX() { return scroll.x; }
    float getScrollY() { return scroll.y; }
    const VECTOR2& getScrollPos() { return scroll; }

    // 当たり判定
    // 下方向
    bool isFloor(float, float, float);          // 床にめり込んでいるか
    void mapHoseiDown(OBJ2D*);                  // 下方向補正処理

    // 上方向
    bool isCeiling(float, float, float);        // 天井にあたっているか
    void mapHoseiUp(OBJ2D*);                    // 上方向補正処理

    // 横方向
    bool isWall(float, float, float);           // 横方向に壁にめり込んでいるか
    void mapHoseiRight(OBJ2D*);                 // 右方向補正処理
    void mapHoseiLeft(OBJ2D*);                  // 左方向補正処理

    // 抵抗
    float calcResistance(const OBJ2D*, float);
    OB_ATTR getObjectAttr(const VECTOR2&);
    float getTeikou(OB_ATTR, float);
    bool isInWater(const OBJ2D*);

    TR_ATTR getTerrainAttr(const VECTOR2&);

private:
    // クリア
    void clear();

    // マップデータのロード
    bool loadMapData(const char[][CHIP_NUM_X], char[][CHIP_NUM_X]);

    // BG、Terrain共通の描画関数
    void draw(int, char[][CHIP_NUM_X]);  // 描画処理（スムーズなスクロール）

    // マップスクロール用
    void scrollMap();

    bool isHitDown(float, float);
    bool isHitAll(float, float);
    bool isUpperQuater(float);
    int getData(char[][BG::CHIP_NUM_X], const VECTOR2&);
};

//******************************************************************************
