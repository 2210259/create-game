#include "all.h"

void Audio::init()
{
    ////// �ǂݍ��� ////////
    
    //BGM
    GameLib::music::load(0, L"Data/Musics/tutorial.wav", 0.2f);     //�`���[�g���A��BGM
    GameLib::music::load(1, L"Data/Musics/game1.wav", 0.2f);        //�Q�[���{��BGM�P
    GameLib::music::load(2, L"Data/Musics/game2.wav", 0.2f);        //�Q�[���{��BGM2
    //3�Q�[���{�҂R
    //4�Q�[���{�҂S
    GameLib::music::load(5, L"Data/Musics/result.wav", 0.2f);       //���U���gBGM
    GameLib::music::load(6, L"Data/Musics/title.wav",  0.2f);        //�^�C�g��BGM
    GameLib::music::load(7, L"Data/Musics/select.wav", 0.2f);       //�Z���N�gBGM

    // ���ʉ�
    GameLib::music::load(8, L"Data/Sounds/decision.wav", 1.0f);     //���艹
    GameLib::music::load(9, L"Data/Sounds/Attack_notes.wav", 0.3f); //�m�[�c���ĉ�(�p�[�t�F�N�g)
    GameLib::music::load(10, L"Data/Sounds/fullcombo.wav", 1.0f);   //�t���R���{�B����
    GameLib::music::load(11, L"Data/Sounds/husuma.wav", 1.0f);      //���̊J��
    GameLib::music::load(12, L"Data/Sounds/katana.wav", 1.0f);      //���̎a�鉹
    GameLib::music::load(13, L"Data/Sounds/number_up.wav", 1.0f);   //���l�̏オ�鉹
    GameLib::music::load(14, L"Data/Sounds/rank.wav", 1.0f);        //�����N��
    GameLib::music::load(15, L"Data/Sounds/Attack_notes.wav", 0.1f); //�m�[�c���ĉ�(�O���C�g)
    GameLib::music::load(16, L"Data/Sounds/Attack_notes.wav", 0.05f); //�m�[�c���ĉ�(�O�b�h)
    GameLib::music::load(17, L"Data/Sounds/damaged.wav", 0.5f);      //�_���[�W��
    GameLib::music::load(18, L"Data/Sounds/long_nots.wav", 0.5f);      //�������m�[�c��

}

void Audio::deinit()
{
    //�N���A
    GameLib::music::clear();
}