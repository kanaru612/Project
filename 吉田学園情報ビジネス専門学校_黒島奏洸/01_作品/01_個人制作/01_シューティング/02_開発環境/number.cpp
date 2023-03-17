//=============================================================================
//
// Tail.cpp
// Author : 
//
//=============================================================================
#include "application.h"
#include "number.h"
#include "rendere.h"

//静的メンバ変数宣言
LPDIRECT3DTEXTURE9	CNumber::m_ptex;

CNumber::CNumber()	: CObject2D(4)
{
}

//デストラクタ
CNumber::~CNumber()
{
}
//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CNumber::Init()
{
	CObject2D::Init();

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		setTexture(0.0f + nCnt / 10, nCnt / 10 + 1.0f / 10.0f, 0.0f, 1.0f);
	}

	BindTexture(m_ptex);

	return S_OK;
}
//=============================================================================
// ポリゴンの初期化
//=============================================================================
CNumber * CNumber::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	CNumber *pObject2D = new CNumber;

	pObject2D->Init();
	pObject2D->setpos(pos);
	pObject2D->setsize(size);

	return pObject2D;
}
//=============================================================================
// ポリゴンの初期化
//=============================================================================
void CNumber::Uninit(void)
{
	CObject2D::Uninit();
}
//=============================================================================
// ポリゴンの初期化
//=============================================================================
void CNumber::Update(void)
{
	CObject2D::Update();
}
//=============================================================================
// ポリゴンの初期化
//=============================================================================
void CNumber::Draw(void)
{
	CObject2D::Draw();
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
HRESULT CNumber::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //デバイスへのポイント		

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/number000.png",
		&m_ptex);

	return S_OK;
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
void CNumber::Unload(void)
{

	//テクスチャの破棄
	if (m_ptex != NULL)
	{
		m_ptex->Release();
		m_ptex = NULL;
	}

}