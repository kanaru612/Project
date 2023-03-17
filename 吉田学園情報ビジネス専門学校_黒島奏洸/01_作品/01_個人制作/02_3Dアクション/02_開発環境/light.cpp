//=============================================================================
//
// Light.cpp
// Author : 黒島奏洸
//
//=============================================================================
#include"light.h"
#include"application.h"
#include"rendere.h"
//グローバル変数
CLight::CLight()
{
}

CLight::~CLight()
{
}
//------------------------------------------------------------------------
//ライトの初期化処理
//------------------------------------------------------------------------
void CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRendere()->GetDevice();

	D3DXVECTOR3 vecDir; //ライトの方向のベクトル
	//
	//1つめ
	//
	//ライトをクリアにする
	ZeroMemory(&m_light[0], sizeof(D3DLIGHT9));

	//ライトの種類を設定
	m_light[0].Type = D3DLIGHT_DIRECTIONAL;        //平行光源

	//ライトの拡散光を設定
	m_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);      //ライトの色

	//ライトの方向を設定
	vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);	//奥から手前
	//正規化する（大きさの１のベクトルにする）       
	D3DXVec3Normalize(&vecDir, &vecDir);

	//ライトを設定する
	m_light[0].Direction = vecDir;
	pDevice->SetLight(0, &m_light[0]);

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);

	//
	//2つめ
	//
	//ライトをクリアにする
	ZeroMemory(&m_light[1], sizeof(D3DLIGHT9));

	//ライトの種類を設定
	m_light[1].Type = D3DLIGHT_DIRECTIONAL;        //平行光源

	//ライトの拡散光を設定
	m_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);      //ライトの色
	//ライトの方向を設定
	vecDir = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);	//手前から奥
	//正規化する（大きさの１のベクトルにする）       
	D3DXVec3Normalize(&vecDir, &vecDir);
	//ライトを設定する
	m_light[1].Direction = vecDir;
	pDevice->SetLight(1, &m_light[1]);

	//ライトを有効にする
	pDevice->LightEnable(1, TRUE);
	//
	//3つめ
	//
	//ライトをクリアにする
	ZeroMemory(&m_light[2], sizeof(D3DLIGHT9));

	//ライトの種類を設定
	m_light[2].Type = D3DLIGHT_DIRECTIONAL;        //平行光源

	//ライトの拡散光を設定
	m_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);      //ライトの色
	//ライトの方向を設定
	vecDir = D3DXVECTOR3(1.0f, -1.0f, 1.0f);	//手前から奥
	//正規化する（大きさの１のベクトルにする）       
	D3DXVec3Normalize(&vecDir, &vecDir);
	//ライトを設定する
	m_light[2].Direction = vecDir;
	pDevice->SetLight(2, &m_light[2]);

	//ライトを有効にする
	pDevice->LightEnable(2, TRUE);
	//
	//4つめ
	//
	//ライトをクリアにする
	ZeroMemory(&m_light[3], sizeof(D3DLIGHT9));

	//ライトの種類を設定
	m_light[3].Type = D3DLIGHT_DIRECTIONAL;        //平行光源

	//ライトの拡散光を設定
	m_light[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);      //ライトの色
	//ライトの方向を設定
	vecDir = D3DXVECTOR3(0.5f, -1.0f, 0.5f);	//手前から奥
	//正規化する（大きさの１のベクトルにする）       
	D3DXVec3Normalize(&vecDir, &vecDir);
	//ライトを設定する
	m_light[3].Direction = vecDir;
	pDevice->SetLight(3, &m_light[3]);

	//ライトを有効にする
	pDevice->LightEnable(3, TRUE);

}

//------------------------------------------------------------------------
//ライトの終了処理
//------------------------------------------------------------------------
void CLight::Uninit(void)
{

}
//------------------------------------------------------------------------
//ライトの更新処理
//------------------------------------------------------------------------
void CLight::Update(void)
{

}
//------------------------------------------------------------------------
//ライトの更新処理
//------------------------------------------------------------------------
CLight *CLight::Create()
{
	CLight *plight = nullptr;

	//動的生成
	plight = new CLight;

	if (plight != nullptr)
	{
		plight->Init();
	}
	return plight;
}

