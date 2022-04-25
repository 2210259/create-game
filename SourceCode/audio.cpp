#include "all.h"

void Audio::init()
{
    ////// 読み込み ////////
    
    //BGM
    GameLib::music::load(0, L"Data/Musics/game1.wav", 1.0f);        //ゲーム本編BGM１
    //１ゲーム本編BGM２(のつもり)
    //２ゲーム本編BGM３(のつもり)
    //３ゲーム本編BGM４(のつもり)
    GameLib::music::load(4, L"Data/Musics/result.wav", 1.0f);       //リザルトBGM
    GameLib::music::load(5, L"Data/Musics/title.wav", 1.0f);        //タイトルBGM
    GameLib::music::load(6, L"Data/Musics/tutorial.wav", 1.0f);     //チュートリアルBGM

    // 効果音
    GameLib::sound::load(0, L"Data/Sounds/system.xwb");             //システム音

    //////////////////////
    //     音量設定 　  //
    //////////////////////

    // 決定音の音量を３倍にする
    GameLib::sound::setVolume(0, 0, 3.0f);
}

void Audio::deinit()
{
    //クリア
    GameLib::music::clear();
}