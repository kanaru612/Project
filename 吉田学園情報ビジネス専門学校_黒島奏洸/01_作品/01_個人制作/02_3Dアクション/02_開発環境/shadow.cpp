//============================================================================
//
// Shadow.cpp
// Author : 黒島　奏洸
//
//=============================================================================
#include "shadow.h"
#include"application.h"
#include"rendere.h"
#include"object3D.h"
CShadow::CShadow()
{
}

CShadow::~CShadow()
{
}
//-------------------------------------------------------------------------
//影の初期化処理
//-------------------------------------------------------------------------
HRESULT CShadow::Init(void)
{
	CObject3D::Init();
	LPDIRECT3DDEVICE9 pDevice;    //デバイスへのポイント			

	//デバイスの取得
	pDevice = CApplication::GetRendere()->GetDevice();
	
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/shadow000.jpg",
		&m_pTexture);

	return S_OK;
}

//-------------------------------------------------------------------------
//影の終了処理
//-------------------------------------------------------------------------
void CShadow::Uninit(void)
{
	CObject3D::Uninit();
}

//-------------------------------------------------------------------------
//影の更新処理
//-------------------------------------------------------------------------
void CShadow::Update(void)
{
	CObject3D::Update();
}
//-------------------------------------------------------------------------
//影の描画処理
//-------------------------------------------------------------------------
void CShadow::Draw(void)
{
	
	LPDIRECT3DDEVICE9 pDevice;    //デバイスへのポイント
								  //デバイスの取得
	pDevice = CApplication::GetRendere()->GetDevice();
	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	CObject3D::Draw();

	//設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//-------------------------------------------------------------------------
//影の設定処理
//-------------------------------------------------------------------------
CShadow *CShadow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CShadow *pshadow = nullptr;

	//動的生成
	pshadow = new CShadow;
	if (pshadow != nullptr)
	{
		pshadow->Init();
		pshadow->set(pos, rot);
		
	}
	return pshadow;
}
//-------------------------------------------------------------------------
//影の更新処理
//-------------------------------------------------------------------------
void CShadow::SetPos(int nIdxShadow, D3DXVECTOR3 pos)
{
	//引数で指定された番号の影のposを代入
	m_aShadow[nIdxShadow].pos = pos;
}
int CShadow::set(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntShadow;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (m_aShadow[nCntShadow].bUse == false)
		{
			m_aShadow[nCntShadow].pos = pos;
			m_aShadow[nCntShadow].rot = rot;
			m_aShadow[nCntShadow].bUse = true;
			break;
		}
	}
	return nCntShadow;
}