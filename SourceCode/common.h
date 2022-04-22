#pragma once
#include <DirectXMath.h>

// �p�x�p
static float(* const ToRadian)(float) = DirectX::XMConvertToRadians;  // �p�x�����W�A����
static float(* const ToDegree)(float) = DirectX::XMConvertToDegrees;  // ���W�A�����p�x��
static constexpr float PI = DirectX::XM_PI;

// �X�v���C�g�f�[�^�ݒ�p
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // �摜�̐^�񒆂����S
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // �摜�̑��������S
