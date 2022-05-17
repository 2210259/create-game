//******************************************************************************
//
//
//      BG�N���X
//
//
//******************************************************************************

//------< �C���N���[�h >---------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

bool isDebugDraw;

//----------------------------------------------------------------------
//  �R���X�g���N�^
//----------------------------------------------------------------------
BG::BG()
    :scroll(VECTOR2(0, 0))
    , player_(nullptr)
{
}

//----------------------------------------------------------------------
//  �f�X�g���N�^
//----------------------------------------------------------------------
BG::~BG()
{
}

//----------------------------------------------------------------------
//  �����ݒ�
//----------------------------------------------------------------------
void BG::init(OBJ2D* player)
{
    player_ = player;

    // BG�p�f�[�^�̃N���A
    clear();
}

//----------------------------------------------------------------------
//  �����o�ϐ��̃N���A
//----------------------------------------------------------------------
void BG::clear()
{
    scroll = {}; // �X�N���[�����W�i��ʍ���̈ʒu�̃��[���h���W�j
}

//----------------------------------------------------------------------
//  �X�V����
//----------------------------------------------------------------------
void BG::update()
{
    scrollMap();
}

//----------------------------------------------------------------------
//  �}�b�v�̃X�N���[��
//----------------------------------------------------------------------
void BG::scrollMap()
{
    Transform* transform = player_->transform();
    Collider* collision = player_->collider();

    // �X�N���[������
    // if (player_) {
    //     // �E�����̃X�N���[������
    //     if (scroll.x < transform->position().x + collision->size().x - CLIENT_W + SCROLL_MERGIN_X)
    //         scroll.x = transform->position().x + collision->size().x - CLIENT_W + SCROLL_MERGIN_X;
    // 
    //     // �������̃X�N���[������
    //     if (scroll.x > transform->position().x - collision->size().x - SCROLL_MERGIN_X)
    //         scroll.x = transform->position().x - collision->size().x - SCROLL_MERGIN_X;
    // 
    //     // �������̃X�N���[������
    //     if (scroll.y < transform->position().y - CLIENT_H + SCROLL_MERGIN_Y)
    //         scroll.y = transform->position().y - CLIENT_H + SCROLL_MERGIN_Y;
    // 
    //     // ������̃X�N���[������
    //     if (scroll.y > transform->position().y - collision->size().y - SCROLL_MERGIN_Y)
    //         scroll.y = transform->position().y - collision->size().y - SCROLL_MERGIN_Y;
    // 
    //     // �G���A�����i�E�j
    //     if (scroll.x > BG::WIDTH - CLIENT_W)
    //         scroll.x = BG::WIDTH - CLIENT_W;
    // 
    //     // �G���A�����i���j
    //     if (scroll.x < 0)
    //         scroll.x = 0;
    // 
    //     // �G���A�����i���j
    //     if (scroll.y > BG::HEIGHT - CLIENT_H)
    //         scroll.y = BG::HEIGHT - CLIENT_H;
    // 
    //     // �G���A�����i��j
    //     if (scroll.y < 0)
    //         scroll.y = 0;
    // }

    using namespace input;
    if (TRG(0) & PAD_TRG2)
    {
        isDebugDraw = !isDebugDraw;
    }
    // TODO:debug
    // debug::setString("transform->position().x:%f", transform->position().x);
    // debug::setString("transform->position().y:%f", transform->position().y);
}

//----------------------------------------//
//              �w�i�`��   �@�@           //
//----------------------------------------//
void BG::drawBack()
{
    // const int REM_X = static_cast<int>(scroll.x);
    // const int REM_Y = static_cast<int>(scroll.y);

    texture::begin(TEXNO::MAP_BACK);
    texture::draw(TEXNO::MAP_BACK, 0, 0, 1, 1, 0, 0, 1920, 1080, 0, 0, 0);
    texture::end(TEXNO::MAP_BACK);
}