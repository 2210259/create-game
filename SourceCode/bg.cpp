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

//------< データ >---------------------------------------------------------------

char st1_terrain[BG::CHIP_NUM_Y][BG::CHIP_NUM_X] = {
// 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
// 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
// 8,8,8,8,8,0,0,0,0,0,0,0,0,0,0,8,8,8,8,8,
// 8,8,8,8,8,0,1,0,0,0,2,0,3,0,0,8,8,8,8,8,
// 8,8,8,8,8,0,0,1,2,3,0,0,0,0,2,8,8,8,8,8,
// 8,8,8,8,0,0,0,0,0,0,0,2,0,0,0,0,8,8,8,8,
// 8,8,8,8,0,0,2,3,0,0,1,3,0,2,0,0,8,8,8,8,
// 8,8,8,8,8,0,0,0,1,0,0,0,3,0,0,8,8,8,8,8,
// 8,8,8,8,8,0,1,3,0,0,1,0,0,0,2,8,8,8,8,8,
// 8,8,8,8,8,0,0,2,0,0,3,0,2,0,0,8,8,8,8,8,
// 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
// 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
};

char st1_object[BG::CHIP_NUM_Y][BG::CHIP_NUM_X] = {
// -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
// -1,-1,-1,-1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,-1,-1,-1,-1,
// -1,-1,-1,-1, 5,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1, 5,-1,-1,-1,-1,
// -1,-1,-1,-1, 5,-1,-1, 3,-1,-1,-1,-1,-1,-1,-1, 5,-1,-1,-1,-1,
// -1,-1,-1, 5, 5,-1,-1,-1,-1,-1,-1, 2,-1,-1,-1, 5, 5,-1,-1,-1,
// -1,-1,-1, 5,-1,-1,-1,-1,-1,-1, 3,-1,-1, 3,-1,-1, 5,-1,-1,-1,
// -1,-1,-1, 5,-1,-1,-1,-1, 2,-1,-1,-1,-1,-1,-1,-1, 5,-1,-1,-1,
// -1,-1,-1, 5, 5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 5, 5,-1,-1,-1,
// -1,-1,-1,-1, 5,-1,-1,-1, 3,-1,-1,-1,-1,-1,-1, 5,-1,-1,-1,-1,
// -1,-1,-1,-1, 5,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1, 5,-1,-1,-1,-1,
// -1,-1,-1,-1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,-1,-1,-1,-1,
// -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
};

bool isDebugDraw;

//----------------------------------------------------------------------
//  コンストラクタ
//----------------------------------------------------------------------
BG::BG()
    :scroll(VECTOR2(0, 0))
    , terrain()
    , object()
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

    // マップデータのロード
    if (!loadMapData(st1_terrain, terrain))
    {
        assert(!"地形データのロードに失敗");
    }

    if (!loadMapData(st1_object, object))
    {
        assert(!"背景データのロードに失敗");
    }

    isDebugDraw = false;
}

//----------------------------------------------------------------------
//  メンバ変数のクリア
//----------------------------------------------------------------------
void BG::clear()
{
    for (int y = 0; y < CHIP_NUM_Y; y++)
    {
        for (int x = 0; x < CHIP_NUM_X; x++)
        {
            terrain[y][x] = 0;
            object[y][x] = 0;
        }
    }

    scroll = {};                                // スクロール座標（画面左上の位置のワールド座標）
}

//----------------------------------------------------------------------
//  マップデータのロード（仮）
//----------------------------------------------------------------------
bool BG::loadMapData(const char data[][CHIP_NUM_X], char map[][CHIP_NUM_X])
{
    for (int y = 0; y < BG::CHIP_NUM_Y; y++)
    {
        for (int x = 0; x < BG::CHIP_NUM_X; x++)
        {
            map[y][x] = data[y][x];
        }
    }

    return true;
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
    // 右方向のスクロール処理
    if (scroll.x < transform->position().x + collision->size().x - CLIENT_W + SCROLL_MERGIN_X)
        scroll.x = transform->position().x + collision->size().x - CLIENT_W + SCROLL_MERGIN_X;

    // 左方向のスクロール処理
    if (scroll.x > transform->position().x - collision->size().x - SCROLL_MERGIN_X)
        scroll.x = transform->position().x - collision->size().x - SCROLL_MERGIN_X;

    // 下方向のスクロール処理
    if (scroll.y < transform->position().y - CLIENT_H + SCROLL_MERGIN_Y)
        scroll.y = transform->position().y - CLIENT_H + SCROLL_MERGIN_Y;

    // 上方向のスクロール処理
    if (scroll.y > transform->position().y - collision->size().y - SCROLL_MERGIN_Y)
        scroll.y = transform->position().y - collision->size().y - SCROLL_MERGIN_Y;

    // エリア制限（右）
    if (scroll.x > BG::WIDTH - CLIENT_W)
        scroll.x = BG::WIDTH - CLIENT_W;

    // エリア制限（左）
    if (scroll.x < 0)
        scroll.x = 0;

    // エリア制限（下）
    if (scroll.y > BG::HEIGHT - CLIENT_H)
        scroll.y = BG::HEIGHT - CLIENT_H;

    // エリア制限（上）
    if (scroll.y < 0)
        scroll.y = 0;

    using namespace input;
    if (TRG(0) & PAD_TRG2)
    {
        isDebugDraw = !isDebugDraw;
    }
}

//----------------------------------------------------------------------
//  背景描画
//----------------------------------------------------------------------
void BG::drawObject()
{
    draw(TEXNO::MAP_OBJECT, object);
}

//----------------------------------------------------------------------
//  地形描画
//----------------------------------------------------------------------
void BG::drawTerrain()
{
    draw(TEXNO::MAP_TERRAIN, terrain);
}

//----------------------------------------------------------------------
//  BGデータ描画
//----------------------------------------------------------------------
void BG::draw(int texNo, char map[][CHIP_NUM_X])
{
    const int DIV_X = static_cast<int>(scroll.x) / CHIP_SIZE; // division x
    const int DIV_Y = static_cast<int>(scroll.y) / CHIP_SIZE; // division y
    const int REM_X = static_cast<int>(scroll.x) % CHIP_SIZE; // remainder x
    const int REM_Y = static_cast<int>(scroll.y) % CHIP_SIZE; // remainder y

    texture::begin(texNo);
    for (int y = 0; y < LOOP_Y; y++)
    {
        for (int x = 0; x < LOOP_X; x++)
        {
            const int mx = DIV_X + x;
            const int my = DIV_Y + y;
            if (mx >= CHIP_NUM_X || mx < 0 ||
                my >= CHIP_NUM_Y || my < 0) continue;   // 添え字の範囲チェック

            char chip = map[my][mx];
            if (-1 == chip) continue;

            texture::draw(texNo,
                x * CHIP_SIZE_F - REM_X, y * CHIP_SIZE_F - REM_Y,
                1, 1,
                chip % CHIP_NUM_PER_LINE * CHIP_SIZE_F,
                chip / CHIP_NUM_PER_LINE * CHIP_SIZE_F,
                CHIP_SIZE_F, CHIP_SIZE_F
            );
        }
    }
    texture::end(texNo);
}

//******************************************************************************
//
//      あたり判定
//
//******************************************************************************

//----------------------------------------------------------------------
//  指定した座標のマップチップの種類を取得する
//----------------------------------------------------------------------
int BG::getData(char map[][CHIP_NUM_X], const VECTOR2& pos)
{
    int divX = static_cast<int>(pos.x) / CHIP_SIZE;      // x方向のインデックス
    int divY = static_cast<int>(pos.y) / CHIP_SIZE;      // y方向のインデックス

    if (divX < 0 || divX >= CHIP_NUM_X ||
        divY < 0 || divY >= CHIP_NUM_Y)
        return -1;

    return map[divY][divX];
}

//----------------------------------------------------------------------
//  指定した座標の地形の属性を取得する
//----------------------------------------------------------------------
BG::TR_ATTR BG::getTerrainAttr(const VECTOR2& pos)
{
    // インデックス取得（1次元配列で処理）
    int index = getData(terrain, pos);
    if (index < 0) return TR_ATTR::TR_NONE;
    assert(index < CHIP_NUM_PER_LINE* CHIP_LINE_NUM);
    return terrainAttr[index];
}

//----------------------------------------------------------------------
//  指定したy座標が、マップチップの上側4分の1にあるかどうかを返す
//----------------------------------------------------------------------
bool BG::isUpperQuater(float y)
{
    return static_cast<int>(y) % CHIP_SIZE < CHIP_SIZE / 4;
}

//----------------------------------------------------------------------
//  下方向に向けて、指定した座標が壁であるかどうか
//----------------------------------------------------------------------
bool BG::isHitDown(float x, float y)
{
    switch (getTerrainAttr(VECTOR2(x, y)))                  // 地形の属性を取得する
    {
    case TR_ATTR::ALL_BLOCK:    return true;                // 全て壁の地形であった
    case TR_ATTR::UPPER_BLOCK:  return isUpperQuater(y);    // 上側４分の１が地形で、上４分の１に含まれるか

    case TR_ATTR::HASHIGO:
        // はしご状態中は下方向へのあたり判定を行わないようにする
        if (player_->behavior() == &hashigoPlayerBehavior)
            break;

        // はしごに乗れるようにしている
        if (getTerrainAttr(VECTOR2(x, y - CHIP_SIZE)) != TR_ATTR::HASHIGO)
            return isUpperQuater(y);

        break;
    }
    return false;   // 地形ではなかった場合
}

//----------------------------------------------------------------------
//  全て壁のブロックかどうか
//----------------------------------------------------------------------
bool BG::isHitAll(float x, float y)
{
    return (getTerrainAttr(VECTOR2(x, y)) == TR_ATTR::ALL_BLOCK);
}

//----------------------------------------------------------------------
//  床方向へのあたり判定
//----------------------------------------------------------------------
bool BG::isFloor(float x, float y, float width)
{
    for (; width > 0; width -= CHIP_SIZE)       // widthをCHIP_SIZE分減らしていく
    {
        const float left = x - width;
        const float right = x + width;

        // エリアチェック
        if (left < 0)       continue;
        if (right >= WIDTH) continue;

        if (isHitDown(left, y))  return true;   // 左端から
        if (isHitDown(right, y)) return true;   // 右端から
    }
    return isHitDown(x, y);                     // 最後に真ん中で判定
}

//----------------------------------------------------------------------
//  下方向にあたっている場合の補正処理
//----------------------------------------------------------------------
void BG::mapHoseiDown(OBJ2D* obj)
{
    Transform* transform = obj->transform();

    float y = transform->position().y;
    transform->addPositionY(-(fmodf(y, CHIP_SIZE_F) + ADJUST_Y));
    transform->setSpeedY(std::min(transform->speed().y, 0.0f));
}

//----------------------------------------------------------------------
//  天井にあたっているか
//----------------------------------------------------------------------
bool BG::isCeiling(float x, float y, float width)
{
    for (; width > 0; width -= CHIP_SIZE)
    {
        const float left = x - width;
        const float right = x + width;

        // エリアチェック
        if (left < 0)       continue;
        if (right >= WIDTH) continue;

        if (isHitAll(left, y))  return true;
        if (isHitAll(right, y)) return true;
    }
    return isHitAll(x, y);
}

//----------------------------------------------------------------------
//  上方向にあたっている場合の補正処理
//----------------------------------------------------------------------
void BG::mapHoseiUp(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Collider* collider = obj->collider();

    float y = transform->position().y - collider->size().y;
    transform->addPositionY(CHIP_SIZE_F - fmodf(y, CHIP_SIZE_F));
    transform->setSpeedY(std::max(transform->speed().y, 0.0f));
}

//----------------------------------------------------------------------
//  横の壁にあたっているか
//----------------------------------------------------------------------
bool BG::isWall(float x, float y, float height)
{
    for (; height > 0; height -= CHIP_SIZE)
    {
        const float yPos = y - height;
        if (yPos < 0)      continue;
        if (yPos > HEIGHT) continue;

        if (isHitAll(x, yPos))
            return true;
    }

    return isHitAll(x, y);
}

//----------------------------------------------------------------------
//  右方向にあたっている場合の補正処理
//----------------------------------------------------------------------
void BG::mapHoseiRight(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Collider* collider = obj->collider();

    float x = transform->position().x + collider->size().x;
    transform->addPositionX(-(fmodf(x, CHIP_SIZE) + ADJUST_X));
    transform->setSpeedX(0.0f);
}

//----------------------------------------------------------------------
//  左方向にあたっている場合の補正処理
//----------------------------------------------------------------------
void BG::mapHoseiLeft(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Collider* collider = obj->collider();

    float x = transform->position().x - collider->size().x;
    transform->addPositionX(CHIP_SIZE_F - fmodf(x, CHIP_SIZE_F) + ADJUST_X);
    transform->setSpeedX(0.0f);
}

//----------------------------------------------------------------------
//  その位置で速度に対する抗力を計算する
//----------------------------------------------------------------------
float BG::calcResistance(const OBJ2D* obj, float speed)
{
    Transform* transform = obj->transform();
    Collider* collider = obj->collider();
    return getTeikou(
        getObjectAttr(VECTOR2(transform->position().x, transform->position().y - collider->size().y * 0.5f)),
        speed);
}

//----------------------------------------------------------------------
//  指定した地点のオブジェクトの属性を取得
//----------------------------------------------------------------------
BG::OB_ATTR BG::getObjectAttr(const VECTOR2& pos)
{
    int index = getData(object, pos);
    if (index < 0) return OB_ATTR::BG_NONE;
    assert(index < CHIP_NUM_PER_LINE* CHIP_LINE_NUM);
    return ObjectAttr[index];
}

//----------------------------------------------------------------------
//  背景の属性に応じた抵抗を返す
//----------------------------------------------------------------------
float BG::getTeikou(OB_ATTR attr, float speed)
{
    switch (attr)
    {
    case OB_ATTR::WATER:
        return speed / -4.0f;

    default:
        break;
    }
    return 0.0f;
}

//----------------------------------------------------------------------
//  OBJ2Dが水中にいるかどうか
//----------------------------------------------------------------------
bool BG::isInWater(const OBJ2D* obj)
{
    Transform* transform = obj->transform();
    return (getObjectAttr(transform->position()) == OB_ATTR::WATER);
}
