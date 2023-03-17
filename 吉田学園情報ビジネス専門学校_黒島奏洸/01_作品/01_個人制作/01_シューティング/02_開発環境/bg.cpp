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
// �|���S���̏�����
//=============================================================================
HRESULT CBg::Init()
{
	CObject2D::Init();
	BindTexture(m_ptex);
	return S_OK;
}
//=============================================================================
// �|���S���̏I��
//=============================================================================
void CBg::Uninit()
{
	CObject2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CBg::Update()
{
	CObject2D::Update();
}
//=============================================================================
// �|���S���̕`��
//=============================================================================
void CBg::Draw()
{
	CObject2D::Draw();
}
//=============================================================================
// �|���S���̕`��
//=============================================================================
CBg *CBg::Create(D3DXVECTOR3 pos)
{
	CBg *apbg = nullptr;

	//���I����
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
// �|���S���̕`��
//=============================================================================
HRESULT CBg::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //�f�o�C�X�ւ̃|�C���g		

																			//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/bg.jpg",
		&m_ptex);
	return S_OK;
}
//=============================================================================
// �|���S���̕`��
//=============================================================================
void CBg::Unload(void)
{

	//�e�N�X�`���̔j��
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