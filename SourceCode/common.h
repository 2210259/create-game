#pragma once
#include <DirectXMath.h>

// 角度用
static float(* const ToRadian)(float) = DirectX::XMConvertToRadians;  // 角度をラジアンに
static float(* const ToDegree)(float) = DirectX::XMConvertToDegrees;  // ラジアンを角度に
static constexpr float PI = DirectX::XM_PI;

// スプライトデータ設定用
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // 画像の真ん中が中心
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // 画像の足元が中心
