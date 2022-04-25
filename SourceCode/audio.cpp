#include "all.h"

void Audio::init()
{
    ////// �ǂݍ��� ////////
    
    //BGM
    GameLib::music::load(0, L"Data/Musics/game1.wav", 1.0f);        //�Q�[���{��BGM�P
    //�P�Q�[���{��BGM�Q(�̂���)
    //�Q�Q�[���{��BGM�R(�̂���)
    //�R�Q�[���{��BGM�S(�̂���)
    GameLib::music::load(4, L"Data/Musics/result.wav", 1.0f);       //���U���gBGM
    GameLib::music::load(5, L"Data/Musics/title.wav", 1.0f);        //�^�C�g��BGM
    GameLib::music::load(6, L"Data/Musics/tutorial.wav", 1.0f);     //�`���[�g���A��BGM

    // ���ʉ�
    GameLib::sound::load(0, L"Data/Sounds/system.xwb");             //�V�X�e����

    //////////////////////
    //     ���ʐݒ� �@  //
    //////////////////////

    // ���艹�̉��ʂ��R�{�ɂ���
    GameLib::sound::setVolume(0, 0, 3.0f);
}

void Audio::deinit()
{
    //�N���A
    GameLib::music::clear();
}