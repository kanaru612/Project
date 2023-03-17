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
// ƒ|ƒŠƒSƒ“‚Ì‰Šú‰»
//=============================================================================
HRESULT CTail::Init()
{
	CObject2D::Init();
	BindTexture(m_ptex);
	return S_OK;
}
//=============================================================================
// ƒ|ƒŠƒSƒ“‚ÌI—¹
//=============================================================================
void CTail::Uninit()
{
	CObject2D::Uninit();
}

//=============================================================================
// ƒ|ƒŠƒSƒ“‚ÌXV
//=============================================================================
void CTail::Update()
{
	CObject2D::Update();
}
//=============================================================================
// ƒ|ƒŠƒSƒ“‚Ì•`‰æ
//=============================================================================
void CTail::Draw()
{
	CObject2D::Draw();
}
//=============================================================================
// ƒ|ƒŠƒSƒ“‚Ì•`‰æ
//=============================================================================
CTail *CTail::Create(D3DXVECTOR3 pos)
{
	CTail *apTail = nullptr;

	//“®“I¶¬
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
// ƒ|ƒŠƒSƒ“‚Ì•`‰æ
//=============================================================================
HRESULT CTail::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //ƒfƒoƒCƒX‚Ö‚Ìƒ|ƒCƒ“ƒg		

	//ƒeƒNƒXƒ`ƒƒ‚Ì“Ç‚Ýž‚Ý
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/tail5.png",
		&m_ptex);
	return S_OK;
}
//=============================================================================
// ƒ|ƒŠƒSƒ“‚Ì•`‰æ
//=============================================================================
void CTail::Unload(void)
{

	//ƒeƒNƒXƒ`ƒƒ‚Ì”jŠü
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