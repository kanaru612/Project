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
// �|���S���̏�����
//=============================================================================
HRESULT CTail::Init()
{
	CObject2D::Init();
	BindTexture(m_ptex);
	return S_OK;
}
//=============================================================================
// �|���S���̏I��
//=============================================================================
void CTail::Uninit()
{
	CObject2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CTail::Update()
{
	CObject2D::Update();
}
//=============================================================================
// �|���S���̕`��
//=============================================================================
void CTail::Draw()
{
	CObject2D::Draw();
}
//=============================================================================
// �|���S���̕`��
//=============================================================================
CTail *CTail::Create(D3DXVECTOR3 pos)
{
	CTail *apTail = nullptr;

	//���I����
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
// �|���S���̕`��
//=============================================================================
HRESULT CTail::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //�f�o�C�X�ւ̃|�C���g		

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/tail5.png",
		&m_ptex);
	return S_OK;
}
//=============================================================================
// �|���S���̕`��
//=============================================================================
void CTail::Unload(void)
{

	//�e�N�X�`���̔j��
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