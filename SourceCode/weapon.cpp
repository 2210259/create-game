#include "all.h"

//using
using namespace GameLib;
using namespace input;

void BaseWeaponBehavior::move(OBJ2D* obj)
{
    Transform* transform = obj->transform();
    Renderer* renderer = obj->renderer();
    Collider* collider = obj->collider();
    WeaponComponent* weaponComponent = obj->weaponComponent();
    BG* bg = obj->bg();

    switch (obj->state())
    {
    case 0:
        //////// 初期設定 ////////
        transform->setScale(getParam()->SCALE);
        renderer->setData(getParam()->SPR_WEAPON);
        obj->setEraser(getParam()->ERASER);
        collider->setJudgeFlag(true);       // あたり判定を行う
        collider->setJudgeBoxFlag(true);    // あたり判定を行う

        collider->calcAttackBox(getParam()->ATTACK_BOX);
        // collider->calcHitBox(getParam()->HIT_BOX);
        weaponComponent->setPosType(Game::instance()->player()->actorComponent()->direction());

        // 左右の向き、速度を設定（プレイヤーにもxFlip_の設定が必要）
        // weaponComponent->copyOwnerXFlip();   // 武器の持ち主のxFlip_を武器に設定する

        obj->nextState();//state++
        /*fallthrough*/

    case 1:
        //////// 通常時 ////////
        collider->calcAttackBox(getParam()->ATTACK_BOX);
        // collider->calcHitBox(getParam()->HIT_BOX);
        update(obj);

        break;
    }
}

void BaseWeaponBehavior::update(OBJ2D* obj)
{
    Renderer* renderer = obj->renderer();
    Transform* transform = obj->transform();

    if (Game::instance()->playerModeFlag() == false) {
        obj->remove();
    }

    // renderer->countAnimeTime();

    // if (Game::instance()->state() <= 1) return;

    // debug::setString("speed%f", transform->speed().x);
    // debug::setString("speedY%f", transform->speed().y);
}

//----------------------------------------//
//         　　コンストラクタ 　          //
//----------------------------------------//
WeaponBehavior::WeaponBehavior()
{
    param_.ERASER = &weaponEraser;

    param_.SCALE = { 1, 1 };
    param_.ATTACK_BOX = { -15, -15, 15, 15 };
    // param_.HIT_BOX    = { -15, -15, 15, 15 };
}

// void WeaponBehavior::calcAttackBox(OBJ2D* obj)
// {
//     obj->collider()->calcAttackBox(getParam()->ATTACK_BOX);
// }
// 
// void WeaponBehavior::calcHitBox(OBJ2D* obj)
// {
//     obj->collider()->calcHitBox(getParam()->HIT_BOX);
// }

// 武器(→)敵に当たった時の処理(Perfect)
void WeaponBehavior::hit(OBJ2D* src, OBJ2D* dst)
{
    if (src->weaponComponent()->posType() != dst->actorComponent()->posType()) return;

    // falseの場合処理をしない
    if (dst->collider()->judgeBoxFlag() == false) return;
    // 通常ノーツと長押しノーツ
    if (dst->behavior() != &enemy3Behavior) {
        // コンボを追加
        Game::instance()->addCombo();

        // コンボのサイズを設定
        Game::instance()->setComboSize(VECTOR2(2, 2));

        // スコアの加算(2倍)
        Game::instance()->addScore(dst->actorComponent()->score() * 2);

        // スコアの表示時間を戻す
        Game::instance()->setScoreTimer(Game::instance()->maxAppearTime());

        // スコア情報を送る
        Game::instance()->setAppearScore(dst->actorComponent()->score() * 2);

        // ノーツ判定を送る
        Game::instance()->setDecision(Game::instance()->PERFECT);   
        
        // パーフェクトカウントを足す
        Game::instance()->addPerfectNum();
    }
    // 連打ノーツ
    else if (TRG(0) & PAD_START) {
        // コンボ2を追加
        Game::instance()->addCombo2();

        // スコアの表示時間を戻す
        Game::instance()->setCombo2Timer(Game::instance()->maxAppearTime());

        // スコアの加算
        Game::instance()->addScore(dst->actorComponent()->score());

        // スコアの表示時間を戻す
        Game::instance()->setScoreTimer(Game::instance()->maxAppearTime());

        // スコア情報を送る
        Game::instance()->setAppearScore(dst->actorComponent()->score() * 2);

        // ノーツ判定を送る
        Game::instance()->setDecision(Game::instance()->PERFECT);

        // パーフェクトカウントを足す
        Game::instance()->addPerfectNum();

        if (dst->actorComponent()->deleteCombo2Flag()) {
            Game::instance()->deleteCombo2();
            dst->actorComponent()->setDeleteCombo2Flag(false);
        }
        debug::setString("deleteCombo2Flag:%d", dst->actorComponent()->deleteCombo2Flag());
    }
    // 敵を消滅する状態に設定(長押しノーツと連続ノーツ以外)
    if (dst->behavior() == &enemy0Behavior ||
        dst->behavior() == &enemy1Behavior) {

        // 敵を消滅する状態に設定
        dst->addEnemyState();

        // Perfectエフェクトを生成
        setEffect(Game::instance()->obj2dManager(), Game::instance()->bg(), &notesEffect2Behavior, src->transform()->position());
    }

    // ジャッジフラグをなくす(連打ノーツ以外)
    if (dst->behavior() != &enemy3Behavior)
        dst->collider()->setJudgeBoxFlag(false);
}

// 武器(→)敵に当たった時の処理(Great)
void WeaponBehavior::hit2(OBJ2D* src, OBJ2D* dst)
{
    if (src->weaponComponent()->posType() != dst->actorComponent()->posType()) return;

    // falseの場合処理をしない
    if (dst->collider()->judgeBoxFlag() == false) return;
        
    // コンボを追加
    Game::instance()->addCombo();
    
    // コンボのサイズを設定
    Game::instance()->setComboSize(VECTOR2(2, 2));

    // スコアの加算(1.5倍)
    Game::instance()->addScore(dst->actorComponent()->score() * 3 / 2);
    
    // スコアの表示時間を戻す
    Game::instance()->setScoreTimer(Game::instance()->maxAppearTime());

    // スコア情報を送る
    Game::instance()->setAppearScore(dst->actorComponent()->score() * 3 / 2);

    // ノーツ判定を送る
    Game::instance()->setDecision(Game::instance()->GREAT);
    
    // グレイトカウントを足す 
    Game::instance()->addGreatNum();

    // 敵を消滅する状態に設定(長押しノーツと連続ノーツ以外)
    if (dst->behavior() == &enemy0Behavior ||
        dst->behavior() == &enemy1Behavior) {
        // 敵を消滅する状態に設定
        dst->addEnemyState();

        // Greatエフェクトを生成
        setEffect(Game::instance()->obj2dManager(), Game::instance()->bg(), &notesEffect1Behavior, src->transform()->position());
    }
    // ジャッジフラグをなくす
    dst->collider()->setJudgeBoxFlag(false);
}

// 武器(→)敵に当たった時の処理(Good)
void WeaponBehavior::hit3(OBJ2D* src, OBJ2D* dst)
{
    if (src->weaponComponent()->posType() != dst->actorComponent()->posType()) return;

    // falseの場合処理をしない
    if (dst->collider()->judgeBoxFlag() == false) return;
    
    // コンボを追加
    Game::instance()->addCombo();
    
    // コンボのサイズを設定
    Game::instance()->setComboSize(VECTOR2(2, 2));

    // スコアの加算(1.0倍)
    Game::instance()->addScore(dst->actorComponent()->score());
    
    // スコアの表示時間を戻す
    Game::instance()->setScoreTimer(Game::instance()->maxAppearTime());

    // スコア情報を送る
    Game::instance()->setAppearScore(dst->actorComponent()->score());

    // ノーツ判定を送る
    Game::instance()->setDecision(Game::instance()->GOOD);
    
    // グッドカウントを足す
    Game::instance()->addGoodNum();

    // 敵を消滅する状態に設定(長押しノーツと連続ノーツ以外)
    if (dst->behavior() == &enemy0Behavior ||
        dst->behavior() == &enemy1Behavior) {
        // 敵を消滅する状態に設定
        dst->addEnemyState();

        // Goodエフェクトを生成
        setEffect(Game::instance()->obj2dManager(), Game::instance()->bg(), &notesEffect0Behavior, src->transform()->position());
    }
    
    // ジャッジフラグをなくす
    dst->collider()->setJudgeBoxFlag(false);
}

// 武器(→)敵に当たった時の処理(長押しノーツ判定)
void WeaponBehavior::hit4(OBJ2D* src, OBJ2D* dst)
{
    // 処理をしないようにフラグを設定した時
    if (dst->collider()->judgeBoxFlag3() == true) {
        // ノーツの色を変える
        dst->renderer()->setColor(VECTOR4(0.0f, 0.0f, 0.0f, 1));
    }

    // falseの場合処理をしない
    if (dst->collider()->judgeBoxFlag() == true) return;  // 最初に攻撃されていない
    if (dst->collider()->judgeBoxFlag3() == true) return; // 長押しされてない
    
    if (STATE(0) & PAD_START) // 長押し出来てたら
    {
        dst->collider()->setJudgeBoxFlag2(true);
    }
    if(TRG_RELEASE(0) & PAD_START && dst->collider()->judgeBoxFlag4() == false) // 長押ししてない 且つ hit5,6,7の当たり判定に入っていないとき
    {
        // コンボをなくす
        Game::instance()->deleteCombo();

        // コンボのサイズを設定
        Game::instance()->setComboSize(VECTOR2(2, 2));

        // ノーツ判定を送る
        Game::instance()->setDecision(Game::instance()->MISS);
        
        // ミスカウント 
        Game::instance()->addMissNum();

        // 処理をしないようにフラグを設定
        dst->collider()->setJudgeBoxFlag3(true);
    }
}

// 武器(→)敵に当たった時の処理(Perfect)
void WeaponBehavior::hit5(OBJ2D* src, OBJ2D* dst)
{
    // hit4の長押しされていない時の処理をしないようにフラグを設定
    dst->collider()->setJudgeBoxFlag4(true);

    // falseの場合処理をしない
    if (dst->collider()->judgeBoxFlag2() == false) return; // 長押しされてない
    if (dst->collider()->judgeBoxFlag3() == true) return;  // 長押しされてない
    
    // 離された瞬間に判定
    if (TRG_RELEASE(0) & PAD_START) {

        // コンボを追加
        Game::instance()->addCombo();

        // コンボのサイズを設定
        Game::instance()->setComboSize(VECTOR2(2, 2));

        // スコアの加算(2倍)
        Game::instance()->addScore(dst->actorComponent()->score() * 2);

        // スコアの表示時間を戻す
        Game::instance()->setScoreTimer(Game::instance()->maxAppearTime());

        // スコア情報を送る
        Game::instance()->setAppearScore(dst->actorComponent()->score() * 2);

        // ノーツ判定を送る
        Game::instance()->setDecision(Game::instance()->PERFECT);
        
        // パーフェクトカウントを足す
        Game::instance()->addPerfectNum();

        // 敵を消滅
        dst->remove();
    }
}

// 武器(→)敵に当たった時の処理(Great)
void WeaponBehavior::hit6(OBJ2D* src, OBJ2D* dst)
{
    // hit4の長押しされていない時の処理をしないようにフラグを設定
    dst->collider()->setJudgeBoxFlag4(true);

    // falseの場合処理をしない
    if (dst->collider()->judgeBoxFlag2() == false) return;
    if (dst->collider()->judgeBoxFlag3() == true) return;

    // 離された瞬間に判定
    if (TRG_RELEASE(0) & PAD_START) {

        // コンボを追加
        Game::instance()->addCombo();

        // コンボのサイズを設定
        Game::instance()->setComboSize(VECTOR2(2, 2));

        // スコアの加算(1.5倍)
        Game::instance()->addScore(dst->actorComponent()->score() * 3 / 2);

        // スコアの表示時間を戻す
        Game::instance()->setScoreTimer(Game::instance()->maxAppearTime());

        // スコア情報を送る
        Game::instance()->setAppearScore(dst->actorComponent()->score() * 3 / 2);

        // ノーツ判定を送る
        Game::instance()->setDecision(Game::instance()->GREAT);

        // グレイトカウントを足す
        Game::instance()->addGreatNum();

        // 敵を消滅
        dst->remove();
    }
}

// 武器(→)敵に当たった時の処理(Good)
void WeaponBehavior::hit7(OBJ2D* src, OBJ2D* dst)
{
    // hit4の長押しされていない時の処理をしないようにフラグを設定
    dst->collider()->setJudgeBoxFlag4(true);

    // falseの場合処理をしない
    if (dst->collider()->judgeBoxFlag2() == false) return;
    if (dst->collider()->judgeBoxFlag3() == true) return;

    // 離された瞬間に判定
    if (TRG_RELEASE(0) & PAD_START) {

        // コンボを追加
        Game::instance()->addCombo();

        // コンボのサイズを設定
        Game::instance()->setComboSize(VECTOR2(2, 2));

        // スコアの加算(1.0倍)
        Game::instance()->addScore(dst->actorComponent()->score());

        // スコアの表示時間を戻す
        Game::instance()->setScoreTimer(Game::instance()->maxAppearTime());

        // スコア情報を送る
        Game::instance()->setAppearScore(dst->actorComponent()->score());

        // ノーツ判定を送る
        Game::instance()->setDecision(Game::instance()->GOOD);

        // グッドカウントを進める
        Game::instance()->addGoodNum();

        // 敵を消滅
        dst->remove();
    }
}

//----------------------------------------//
//         　　　　　消去 　　　          //
//----------------------------------------//
void WeaponEraser::erase(OBJ2D* obj)
{
    // obj->remove();
}
