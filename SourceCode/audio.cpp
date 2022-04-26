#include "all.h"

void Audio::init()
{
    ////// 読み込み ////////
    
    //BGM
    GameLib::music::load(0, L"Data/Musics/game1.wav", 0.5f);        //ゲーム本編BGM１
    //１ゲーム本編BGM２(のつもり)
    //２ゲーム本編BGM３(のつもり)
    //３ゲーム本編BGM４(のつもり)
    GameLib::music::load(4, L"Data/Musics/result.wav", 0.5f);       //リザルトBGM
    GameLib::music::load(5, L"Data/Musics/title.wav", 0.5f);        //タイトルBGM
    GameLib::music::load(6, L"Data/Musics/tutorial.wav", 0.5f);     //チュートリアルBGM

    // 効果音
    GameLib::music::load(7, L"Data/Sounds/decision.wav", 1.0f);     //決定音
    GameLib::music::load(8, L"Data/Sounds/Attack_notes.wav", 1.0f); //ノーツ撃墜音
}

void Audio::deinit()
{
    //クリア
    GameLib::music::clear();
}