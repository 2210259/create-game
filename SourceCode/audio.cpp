#include "all.h"

void Audio::init()
{
    ////// 読み込み ////////
    
    //BGM
    GameLib::music::load(0, L"Data/Musics/tutorial.wav", 0.2f);     //チュートリアルBGM
    GameLib::music::load(1, L"Data/Musics/game1.wav", 0.2f);        //ゲーム本編BGM１
    GameLib::music::load(2, L"Data/Musics/game2.wav", 0.2f);        //ゲーム本編BGM2
    //3ゲーム本編３
    //4ゲーム本編４
    GameLib::music::load(5, L"Data/Musics/result.wav", 0.2f);       //リザルトBGM
    GameLib::music::load(6, L"Data/Musics/title.wav",  0.2f);        //タイトルBGM
    GameLib::music::load(7, L"Data/Musics/select.wav", 0.2f);       //セレクトBGM

    // 効果音
    GameLib::music::load(8, L"Data/Sounds/decision.wav", 1.0f);     //決定音
    GameLib::music::load(9, L"Data/Sounds/Attack_notes.wav", 0.3f); //ノーツ撃墜音(パーフェクト)
    GameLib::music::load(10, L"Data/Sounds/fullcombo.wav", 1.0f);   //フルコンボ達成音
    GameLib::music::load(11, L"Data/Sounds/husuma.wav", 1.0f);      //襖の開閉音
    GameLib::music::load(12, L"Data/Sounds/katana.wav", 1.0f);      //刀の斬る音
    GameLib::music::load(13, L"Data/Sounds/number_up.wav", 1.0f);   //数値の上がる音
    GameLib::music::load(14, L"Data/Sounds/rank.wav", 1.0f);        //ランク音
    GameLib::music::load(15, L"Data/Sounds/Attack_notes.wav", 0.1f); //ノーツ撃墜音(グレイト)
    GameLib::music::load(16, L"Data/Sounds/Attack_notes.wav", 0.05f); //ノーツ撃墜音(グッド)
    GameLib::music::load(17, L"Data/Sounds/damaged.wav", 0.5f);      //ダメージ音
    GameLib::music::load(18, L"Data/Sounds/long_nots.wav", 0.5f);      //長押しノーツ音

}

void Audio::deinit()
{
    //クリア
    GameLib::music::clear();
}