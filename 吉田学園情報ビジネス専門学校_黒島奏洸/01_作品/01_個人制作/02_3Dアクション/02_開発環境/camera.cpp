//=============================================================================
//
//  Camera.cpp
//  Author : 黒島　奏洸
//
//=============================================================================
#include "camera.h"
#include"input.h"
#include"application.h"
#include"rendere.h"
#include"player.h"
#include"game.h"
D3DXVECTOR3 CCamera::m_rot = {};

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}
//------------------------------------------------------------------------
//カメラの初期化処理
//-------------------------------------------------------------------------
void CCamera::Init(void)
{
	//視点,注視点,上方向,角度を設定する
	m_posV = D3DXVECTOR3(0.0f, 50.0f, 150.0f);
	//m_posV = D3DXVECTOR3(0.0f,200.0f,200.0f);
	m_posR = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_vecU = D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_rot  = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//posRとposVの距離を求める
	m_fDistance = sqrtf((m_posV.x - m_posR.x)*(m_posV.x - m_posR.x) 
		+ (m_posV.z - m_posR.z)*(m_posV.z - m_posR.z)) ;
}

//------------------------------------------------------------------------
//カメラの終了処理
//-------------------------------------------------------------------------
void CCamera::Uninit(void)
{

}

//------------------------------------------------------------------------
//カメラの更新処理
//-------------------------------------------------------------------------
void CCamera::Update(void)
{
	//注視点の旋回
	//角度は-n～n(-D3DX_PI ～D3DX_PI)-180～180の範囲に収まるようにする
	//(184度の場合-176にする)角度の正規化
	CInput *pInput = CApplication::GetKeyboard();
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = m_rot.y - D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = m_rot.y + D3DX_PI * 2;
	}

	if (CApplication::GetMode() == CApplication::MODE_GAME)
	{
		CPlayer *pPlayer = CGame::GetPlayer();

		m_posRDest.x = pPlayer->Getpos().x + sin(m_rot.y) * -5.0f;
		m_posRDest.y = 0.0f;
		m_posRDest.z = pPlayer->Getpos().z + cos(m_rot.y) * -5.0f;

		m_posVDest.x = pPlayer->Getpos().x - sin(m_rot.y) * m_fDistance;
		m_posVDest.y = 0.0f;
		m_posVDest.z = pPlayer->Getpos().z - cos(m_rot.y) * m_fDistance;

		m_posR.x += (m_posRDest.x - m_posR.x) * 1.0f;
		m_posR.z += (m_posRDest.z - m_posR.z) * 1.0f;

		m_posV.x += (m_posVDest.x - m_posV.x) * 1.0f;
		m_posV.z += (m_posVDest.z - m_posV.z) * 1.0f;
	}
}

//------------------------------------------------------------------------
//カメラの設定処理
//-------------------------------------------------------------------------
void CCamera::Set(void)
{
	LPDIRECT3DDEVICE9 pDevice;  //デバイスへのポイント

	pDevice = CApplication::GetRendere()->GetDevice();
	
	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの初期化
	D3DXMatrixLookAtLH(	&m_mtxView,
						&m_posV,
						&m_posR,
						&m_vecU);

	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//ぴろじぇくしょんマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		1.0f,
		1000.0f
	);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}