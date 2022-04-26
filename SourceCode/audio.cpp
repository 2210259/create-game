#include "all.h"

void Audio::init()
{
    ////// �ǂݍ��� ////////
    
    //BGM
    GameLib::music::load(0, L"Data/Musics/game1.wav", 0.5f);        //�Q�[���{��BGM�P
    //�P�Q�[���{��BGM�Q(�̂���)
    //�Q�Q�[���{��BGM�R(�̂���)
    //�R�Q�[���{��BGM�S(�̂���)
    GameLib::music::load(4, L"Data/Musics/result.wav", 0.5f);       //���U���gBGM
    GameLib::music::load(5, L"Data/Musics/title.wav", 0.5f);        //�^�C�g��BGM
    GameLib::music::load(6, L"Data/Musics/tutorial.wav", 0.5f);     //�`���[�g���A��BGM

    // ���ʉ�
    GameLib::music::load(7, L"Data/Sounds/decision.wav", 1.0f);     //���艹
    GameLib::music::load(8, L"Data/Sounds/Attack_notes.wav", 1.0f); //�m�[�c���ĉ�
}

void Audio::deinit()
{
    //�N���A
    GameLib::music::clear();
}