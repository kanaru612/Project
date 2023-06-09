//=============================================================================
//
// bg.cpp
// Author : 
//
//=============================================================================
#include"bg.h"
#include"application.h"
#include"Input.h"
#include"rendere.h"
#include"bullet.h"
#include"block.h"

LPDIRECT3DTEXTURE9 CBg::m_ptex = {};
//CBg * CBg::m_pbg[MAX_bg] = {};
CBg::CBg()	: CObject2D(0)
{
	//for (int nCnt = 0; nCnt < MAX_bg; nCnt++)
	//{
	//	if (m_pbg[nCnt] == nullptr)
	//	{
	//		m_pbg[nCnt] = this;
	//		break;
	//	}
	//}
}
CBg::~CBg()
{
}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CBg::Init()
{
	CObject2D::Init();
	BindTexture(m_ptex);
	return S_OK;
}
//=============================================================================
// ポリゴンの終了
//=============================================================================
void CBg::Uninit()
{
	CObject2D::Uninit();
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CBg::Update()
{
	CObject2D::Update();
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
void CBg::Draw()
{
	CObject2D::Draw();
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
CBg *CBg::Create(D3DXVECTOR3 pos)
{
	CBg *apbg = nullptr;

	//動的生成
	apbg = new CBg;
	apbg->Init();
	apbg->BindTexture(m_ptex);
	apbg->SetType(OBJTYPE_BG);
	apbg->setpos(D3DXVECTOR3(pos));
	D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	apbg->setsize(size);
	return apbg;
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
HRESULT CBg::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //デバイスへのポイント		

																			//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/bg.jpg",
		&m_ptex);
	return S_OK;
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
void CBg::Unload(void)
{

	//テクスチャの破棄
	if (m_ptex != NULL)
	{
		m_ptex->Release();
		m_ptex = NULL;
	}

}
//void CBg::Releasebg(void)
//{
//	for (int nCnt = 0; nCnt < MAX_bg; nCnt++)
//	{
//		if (m_pbg[nCnt] != nullptr)
//		{
//			m_pbg[nCnt]->Uninit();
//			m_pbg[nCnt] = nullptr;
//		}
//	}
//}