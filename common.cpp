//******************************************************************************
//
//
//      common
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include <DirectXMath.h>

//------< 関数ポインタ >---------------------------------------------------------
float(*ToRadian)(float) = DirectX::XMConvertToRadians;  // 角度をラジアンに
float(*ToDegree)(float) = DirectX::XMConvertToDegrees;  // ラジアンを角度に

constexpr float PI = DirectX::XM_PI;
