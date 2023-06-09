//=============================================================================
//
// Tail.cpp
// Author : 
//
//=============================================================================
#include"tail.h"
#include"application.h"
#include"Input.h"
#include"rendere.h"
#include"bullet.h"
#include"block.h"

LPDIRECT3DTEXTURE9 CTail::m_ptex = {};
//CTail * CTail::m_ptail[MAX_TAIL] = {};
CTail::CTail() : CObject2D(2)
{
	//for (int nCnt = 0; nCnt < MAX_TAIL; nCnt++)
	//{
	//	if (m_ptail[nCnt] == nullptr)
	//	{
	//		m_ptail[nCnt] = this;
	//		break;
	//	}
	//}
}
CTail::~CTail()
{
}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CTail::Init()
{
	CObject2D::Init();
	BindTexture(m_ptex);
	return S_OK;
}
//=============================================================================
// ポリゴンの終了
//=============================================================================
void CTail::Uninit()
{
	CObject2D::Uninit();
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CTail::Update()
{
	CObject2D::Update();
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
void CTail::Draw()
{
	CObject2D::Draw();
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
CTail *CTail::Create(D3DXVECTOR3 pos)
{
	CTail *apTail = nullptr;

	//動的生成
	apTail = new CTail;
	apTail->Init();
	apTail->BindTexture(m_ptex);
	apTail->SetType(OBJTYPE_TAIL);
	apTail->setpos(D3DXVECTOR3(pos));
	D3DXVECTOR3 size = D3DXVECTOR3(MAX_SIZET / 2, MAX_SIZET / 4, 0.0f);
	apTail->setsize(size);
	return apTail;
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
HRESULT CTail::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //デバイスへのポイント		

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/tail5.png",
		&m_ptex);
	return S_OK;
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
void CTail::Unload(void)
{

	//テクスチャの破棄
	if (m_ptex != NULL)
	{
		m_ptex->Release();
		m_ptex = NULL;
	}

}
//void CTail::ReleaseTail(void)
//{
//	for (int nCnt = 0; nCnt < MAX_TAIL; nCnt++)
//	{
//		if (m_ptail[nCnt] != nullptr)
//		{
//			m_ptail[nCnt]->Uninit();
//			m_ptail[nCnt] = nullptr;
//		}
//	}
//}